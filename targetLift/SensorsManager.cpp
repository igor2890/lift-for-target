#include <Arduino.h>
#include "SensorsManager.h"
#include "TargetsSwitchesState.h"
#include "config.h"

#define renewTargetSwitchesState isTargetsStatesChanges

SensorsManager::SensorsManager() {
}

void SensorsManager::configurePins() {
  pinMode(VOLT_PIN, INPUT);
  pinMode(LASER_SENS_PIN, INPUT);
  pinMode(SWITCH_PIN_STOP, INPUT_PULLUP);
  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(SWITCH_PIN_3, INPUT_PULLUP);
  pinMode(SWITCH_PIN_4, INPUT_PULLUP);
  pinMode(SWITCH_PIN_5, INPUT_PULLUP);
}

void SensorsManager::renewLaserSensorLevel() {
  this->_laserSensorLevel = this->_laserSignalLevel();
}

bool SensorsManager::isBatteryNotConnected() {
  return (this->batteryVoltage() < 6.0) ? true : false;
}

double SensorsManager::batteryVoltage(){
  return (analogRead(VOLT_PIN) / 43.0);
}

bool SensorsManager::isAllTargetsDown() {
  return (this->_laserSensorLevel - 500) > this->_laserSignalLevel();
}

bool SensorsManager::isSomeoneTargetDown() {
  this->renewTargetSwitchesState();
  return (!this->_targetsSwitchesState.isAllUp());
}

bool SensorsManager::isDownSwitchPressed() {
  return digitalRead(SWITCH_PIN_STOP) == LOW ? true : false;
}

int SensorsManager::_laserSignalLevel() {
  return analogRead(LASER_SENS_PIN);
}

bool SensorsManager::isTargetsStatesChanges() {
  TargetsSwitchesState tempState;
  tempState.target_1 = digitalRead(SWITCH_PIN_1) == LOW ? PRESSED : NOTPRESSED;
  tempState.target_2 = digitalRead(SWITCH_PIN_2) == LOW ? PRESSED : NOTPRESSED;
  tempState.target_3 = digitalRead(SWITCH_PIN_3) == LOW ? PRESSED : NOTPRESSED;
  tempState.target_4 = digitalRead(SWITCH_PIN_4) == LOW ? PRESSED : NOTPRESSED;
  tempState.target_5 = digitalRead(SWITCH_PIN_5) == LOW ? PRESSED : NOTPRESSED;

  bool result = tempState == this->_targetsSwitchesState;
  this->_targetsSwitchesState = tempState;

  return !result;
}

TargetsSwitchesState SensorsManager::targetsSwitchesState() {
  return this->_targetsSwitchesState;
}
