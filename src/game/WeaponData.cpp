// WeaponData.cpp
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

#include "WeaponData.h"

#include <string>
#include <iostream>

#include "misc/INIFile.h"

std::string WeaponData::getAnim()
{
  return anim;
}

int WeaponData::getBurst()
{
  return burst;
}

void WeaponData::setBurst(int burst)
{
  this->burst = burst;
}

int WeaponData::getTurboBoost()
{
  return turboBoost;
}

void WeaponData::setTurboBoost(int turboBoost)
{
  this->turboBoost = turboBoost;
}

int WeaponData::getSupress()
{
  return supress;
}

void WeaponData::setSupress(int supress)
{
  this->supress = supress;
}

std::string WeaponData::getWarhead()
{
  return warhead;
}

void WeaponData::setWarhead(std::string warhead)
{
  this->warhead = warhead;
}

int WeaponData::getSpeed()
{
  return speed;
}

void WeaponData::setSpeed(int speed)
{
  this->speed = speed;
}

std::string WeaponData::getReport()
{
  return report;
}

void WeaponData::setReport(std::string report)
{
  this->report = report;
}

int WeaponData::getRange()
{
  return range;
}

void WeaponData::setRange(int range)
{
  this->range = range;
}

int WeaponData::getRof()
{
  return rof;
}

void WeaponData::setRof(int rof)
{
  this->rof = rof;
}

std::string WeaponData::getProjectile()
{
  return projectile;
}

void WeaponData::setProjectile(std::string projectile)
{
  this->projectile = projectile;
}

int WeaponData::getDamage()
{
  return damage;
}

void WeaponData::setDamage(int damage)
{
  this->damage = damage;
}

int WeaponData::getCharges()
{
  return charges;
}

void WeaponData::setCharges(int charges)
{
  this->charges = charges;
}

int WeaponData::getCamera()
{
  return camera;
}

void WeaponData::setCamera(int camera)
{
  this->camera = camera;
}

void WeaponData::setAnim(std::string anim)
{
  this->anim = anim;
}

WeaponData* WeaponData::loadWeaponData(INIFile * file, const std::string& name)
{
  // Create the WeaponData object
  WeaponData* ptrWeaponData = new WeaponData();

  // Anim = animation to display as a firing effect
  ptrWeaponData->setAnim(file->readString(name, std::string("Anim"), "NONE"));

  // Burst = number of rapid succession shots from this weapon (def=1)
  unsigned int tmpBurst = file->readInt(name, "Burst", 1);
  ptrWeaponData->setBurst(tmpBurst);

  // Camera = Reveals area around firer (def=no)?
  ptrWeaponData->setCamera(file->readYesNo(name, "Camera", 0));

  // Charges = Does it have charge-up-before-firing logic (def=no)?
  ptrWeaponData->setCharges(file->readYesNo(name, "Charges", 0));

  // Damage = the amount of damage (unattenuated) dealt with every bullet
  ptrWeaponData->setDamage(file->readInt(name, "Damage", 0));

  // Projectile = projectile characteristic to use
  ptrWeaponData->setProjectile(file->readString(name, "Projectile", "Invisible"));

  // ROF = delay between shots [15 = 1 second at middle speed setting]
  ptrWeaponData->setRof(file->readInt(name, "ROF", 15));

  // Range = maximum cell range
  ptrWeaponData->setRange(file->readInt(name, "Range", 1));

  // Report = sound to play when firing
  ptrWeaponData->setReport(file->readString(name, "Report", "NONE"));

  // Speed = speed of projectile to target (100 is maximum)
  ptrWeaponData->setSpeed(file->readInt(name, "Speed", 100));

  // Warhead = warhead to attach to projectile
  ptrWeaponData->setWarhead(file->readString(name, "Warhead"));

  // Supress = Should nearby friendly buildings be scanned for and if found, discourage firing on target (def=no)?
  ptrWeaponData->setSupress(file->readYesNo(name, "Supress", 0));

  // TurboBoost = Should the weapon get a boosted speed bonus when firing upon aircraft?
  ptrWeaponData->setTurboBoost(file->readYesNo(name, "TurboBoost", 0));

  // Returns the constructed object
  return ptrWeaponData;
}

/**
 * Print the Data
 */
void WeaponData::print() {
  std::cout << "Anim=" << getAnim() << std::endl;
  std::cout << "Burst=" << getBurst() << std::endl;
  std::cout << "Camera=" << getCamera() << std::endl;
  std::cout << "Charges=" << getCharges() << std::endl;
  std::cout << "Damage=" << getDamage() << std::endl;
  std::cout << "Projectile=" << getProjectile() << std::endl;
  std::cout << "ROF=" << getRof() << std::endl;
  std::cout << "Range=" << getRange() << std::endl;
  std::cout << "Report=" << getReport() << std::endl;
  std::cout << "Speed=" << getSpeed() << std::endl;
  std::cout << "Warhead=" << getWarhead() << std::endl;
  std::cout << "Supress=" << getSupress() << std::endl;
  std::cout << "TurboBoost=" << getTurboBoost() << std::endl;
}
