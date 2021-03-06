// URepairEvent.h
// 1.5
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

#ifndef UREPAIREVENT_H
#define UREPAIREVENT_H

#include "UnitAnimEvent.h"

class Unit;
class UnitOrStructure;

/**
 * Anim to repair a Unit
 */
class URepairEvent : public UnitAnimEvent {
 public:
  URepairEvent(uint32_t p, Unit *un);
  virtual ~URepairEvent();

  void stop();
  virtual void update();
  virtual void run();

 private:
  uint32_t fix_str_num;
  uint16_t fix_str_pos;
  uint8_t moveCounter;
  /** Total cost of damage remaining */
  uint16_t dmg_cost;

  uint8_t ReturnStep;
  Unit* un;
  bool stopping;
  UnitOrStructure * FixStr;
  int index;
  int delay;
  int facing;
  uint32_t MoveTargePos;
  uint32_t OrgImage;
};

#endif //UREPAIREVENT_H
