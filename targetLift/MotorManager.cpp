#include <Arduino.h>
#include "MotorManager.h"
#include "config.h"

MotorManager::MotorManager() {
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
}

void MotorManager::configurePins() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
}

void MotorManager::moveMechan(Direction direction, int steps) {
  direction ? _dirMoveUp() : _dirMoveDown();

  for (int i=0; i<steps; ++i) {
    _makeStep();
  }
}

void MotorManager::_dirMoveDown() {
  PORTB |= B00100000; //digitalWrite(DIR_PIN, HIGH);
}

void MotorManager::_dirMoveUp() {
  PORTB &= ~B00100000; //digitalWrite(DIR_PIN, LOW);
}

void MotorManager::_makeStep() {
  PORTB |= B00010000;
  delayMicroseconds(500);
  PORTB &= ~B00010000;
  delayMicroseconds(500);
}