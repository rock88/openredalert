// WarheadDataList.cpp
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

#include "WarheadDataList.h"

#include <iostream>
#include <string>

#include "misc/INIFile.h"
#include "Logger.h"
#include "DataLoader.h"
#include "WarheadData.h"

#include "misc/INIFile.h"

extern Logger * logger;

size_t WarheadDataList::size() {
  return data.size();
}

WarheadData* WarheadDataList::getData(std::string name) {
  std::map<std::string, WarheadData*>::iterator itRecherche;


  itRecherche=data.find(name);
  if (itRecherche != data.end()) {
    std::cout << (*itRecherche).second->getWall() << std::endl;
    return (*itRecherche).second;
  }
  //return this->data[name];
  Logger::getInstance()->Error("Unenable to load [" + name + "] WARHEAD !!!");

  // Return new Warhead by default
  Logger::getInstance()->Warning("New virtual warhead was returned...");
  return new WarheadData();
}


void WarheadDataList::loadWarheadData(INIFile* file, std::string name) {
  // Load the Warhead
  WarheadData* ptrWaH = WarheadData::loadWarheadData(file, name);

  // @todo DEBUG
  if (ptrWaH == NULL) {

  }

  // Put it in the DataList
  //this->data[name] = ptrWaH;

  //this->data.insert(map < string, WarheadData * >::value_type(name, ptrWaH));
  data[name]=ptrWaH;
}

void WarheadDataList::print() {
  std::map<std::string, WarheadData*>::iterator itRecherche;

  itRecherche = data.begin();
  while (itRecherche != data.end()) {
    std::cout << "[" << (*itRecherche).first << "]" << std::endl;
    (*itRecherche).second->print();

    itRecherche++;
  }
}
