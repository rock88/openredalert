// Talkback.cpp
// 1.0
//    This file is part of OpenRedAlert.
//
//    OpenRedAlert is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, version 2 of the License.
//
//    OpenRedAlert is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with OpenRedAlert.  If not, see <http://www.gnu.org/licenses/>.

#include "Talkback.h"

#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <iterator>

#include "Logger.h"
#include "misc/INIFile.h"
#include "audio/SoundEngine.h"
#include "UnitAndStructurePool.h"
#include "TalkbackType.h"
#include "misc/common.h"

using Sound::SoundEngine;

namespace pc {
  /** SoundEngine of the game */
  extern SoundEngine* sfxeng;
  extern ConfigType Config;
}

std::map<std::string, TalkbackType> Talkback::talktype;
bool Talkback::talktype_init;

Talkback::Talkback() {
  if (!talktype_init) {
    talktype["report"] = TB_report;
    talktype["ack"] = TB_ack;
    talktype["die"] = TB_die;
    talktype["postkill"] = TB_postkill;
    talktype["attackunit"] = TB_atkun;
    talktype["attackstruct"] = TB_atkst;
    talktype_init = true;
  }
}

/**
 */
void Talkback::load(std::string talkback, INIFile *tbini) {
  //logger->debug("Loading %s\n", talkback.c_str());
  //logger->indent();

  try {
    tbini->readKeyValue(talkback.c_str(), 0);
  } catch(...) {
    Logger::getInstance()->Warning("Could not find talkback '" + talkback + "', reverting to default");
    talkback = "Generic";
  }

  try {
    for (int keynum=0;;++keynum) {
      // Still @todo: stringify rest of code
      char* first;
      INIFile::KeyNode key = tbini->readKeyValue(talkback.c_str(), keynum);
      first = stripNumbers(key.name.c_str());
      if (std::string(first) == "include") {
        if (key.value != talkback) {
          merge(p::uspool->getTalkback(key.value.c_str()));
        } else {
          Logger::getInstance()->Warning("skipping self-referential include in " + talkback);
        }
      } else {
        if (std::string(first) == "delete") {
          TalkbackType tbt = getTypeNum(key.value);
          if (tbt == TB_invalid) {
            continue;
          }
          talkstore[tbt].clear();
          continue;
        }
        TalkbackType tbt = getTypeNum(first);
        if (tbt == TB_invalid) {
          continue;
        }
        pc::sfxeng->LoadSound(key.value.c_str());
        //logger->debug("Pushing back %s\n", key->second.c_str());
        talkstore[tbt].push_back(key.value);
      }
      delete[] first;
    }
  } catch(...) {}
  //logger->unindent();
  //logger->debug("report is %i big\n", talkstore[TB_report].size());
}

/**
 */
const char* Talkback::getRandTalk(TalkbackType type) {
  std::vector<std::string>& talk = getTypeVector(type);
  if (talk.empty()) {
    //		logger->warning ("%s line %i: Talkback store empty\n", __FILE__, __LINE__);
    return "";
  }
  double sze = static_cast<double>(talk.size());
  int rnd = static_cast<int>(floor((sze*rand()/(RAND_MAX+1.0))));
  return talk[rnd].c_str();
}

/**
 */
std::vector<std::string>& Talkback::getTypeVector(TalkbackType type) {
  if (talkstore[type].empty()){
    if ( type == TB_atkun || type == TB_atkst ) {
      return talkstore[TB_ack];
    }
    //logger->warning ("%s line %i: Talkback store empty\n", __FILE__, __LINE__);
    return talkstore[type];
  }

  t_talkstore::iterator ret = talkstore.find(type);
  if (ret == talkstore.end()) {
    // @todo : change it assert(0 && "Unknown talkback type");
  }
  return ret->second;
}

/**
 */
void Talkback::merge(Talkback *mergee) {
  typedef std::map<std::string, TalkbackType>::iterator TBI;
  TBI t = talktype.begin();
  TBI end = talktype.end();
  while (t != end) {
    std::vector<std::string>& src = mergee->talkstore[t->second];
    std::vector<std::string>& dest = talkstore[t->second];
    //logger->debug("Copying %s/%i %i new into %i\n", t->first.c_str(), t->second, src.size(), dest.size());
    copy(src.begin(), src.end(), back_inserter(dest));
    ++t;
  }
}

TalkbackType Talkback::getTypeNum(std::string name) {
  // lower the string
  transform(name.begin(), name.end(), name.begin(), tolower);
  typedef std::map<std::string, TalkbackType>::const_iterator TBCI;

  TBCI tbtype = talktype.find(name);
  if (tbtype == talktype.end()) {
    Logger::getInstance()->Error(__FILE__, __LINE__, "Unknown type: " + name);
    return TB_invalid;
  }
  return tbtype->second;
}

