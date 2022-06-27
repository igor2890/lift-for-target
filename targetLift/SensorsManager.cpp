#include <Arduino.h>
#include "SensorsManager.h"
#include "config.h"

SensorsManager::SensorsManager() {
}

void SensorsManager::configurePins() {
  pinMode(VOLT_PIN, INPUT);
  pinMode(LASER_SENS_PIN, INPUT);
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
}

void SensorsManager::storeLaserSensorLevel() {
  _laserSensorLevel = _laserSignalLevel();
}

bool SensorsManager::isBatteryNotConnected() {
  return (batteryVoltage() < 6.0) ? true : false;
}

double SensorsManager::batteryVoltage(){
  return (analogRead(VOLT_PIN) / 43.0);
}

bool SensorsManager::isAllTargetsDown() {
  return (_laserSensorLevel - 500) > _laserSignalLevel();
}

int SensorsManager::_laserSignalLevel() {
  return analogRead(LASER_SENS_PIN);
}