#include <Arduino.h>
#include "LiftManager.h"
#include "Beep.h"
#include "config.h"

LiftManager::LiftManager(SensorsManager * sensorManager, int stepsOneWay) {
  this->_sensorManager = sensorManager;
  this->_stepsOneWay = stepsOneWay;
}

void LiftManager::configurePins() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
}

void LiftManager::calibrationLift() {
  this->moveLiftDown();
  delay(500);
  int correction = 0;
  while(this->_sensorManager->isSomeoneTargetDown()) {
    makeBeep(10, 10, 10);
    this->_stepsOneWay += correction;
    this->moveLiftUp(_stepsOneWay);
    this->moveLiftDown();
    correction += 10;
    delay(200);
  }
  this->_sensorManager->renewLaserSensorLevel();
}

void LiftManager::moveTargetsUp() {
  delay(500);
  if (this->_sensorManager->isSomeoneTargetDown()) {
    makeBeep(200, 200, 1);
    delay(2000);
    makeBeep(50, 50, 2);
    
    this->moveLiftUp(_stepsOneWay);
    this->moveLiftDown();

    makeBeep(50, 50, 2);
    this->calibrationLift();
  }
}

void LiftManager::moveLiftUp(int steps) {
  this->_setDirectionUp();
  for(int i = 0; i < steps; ++i) {
    this->_makeStep();
  }
}

void LiftManager::moveLiftDown() {
  this->_setDirectionDown();
  while(!this->_sensorManager->isDownSwitchPressed()) {
    this->_makeStep();
  }
}

void LiftManager::_setDirectionDown() {
  //PORTB |= B00100000;
  digitalWrite(DIR_PIN, HIGH);
}

void LiftManager::_setDirectionUp() {
  //PORTB &= ~B00100000;
  digitalWrite(DIR_PIN, LOW);
}

void LiftManager::_makeStep() {
  PORTB |= B00010000; //digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(500);
  PORTB &= ~B00010000; //digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(500);
}
