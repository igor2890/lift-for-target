#include "SensorsManager.h"
#include "LiftManager.h"
#include "Beep.h"
#include "config.h"

SensorsManager sensors;
LiftManager lift = LiftManager(&sensors, 1050);
volatile bool isVibrated = false;

void setup() {
  sensors.configurePins();
  lift.configurePins();
  pinMode(TONE_PIN, OUTPUT);

  if (sensors.isBatteryNotConnected()) {
    while(1) {
      makeBeep(10,5000,10);
    }
  }
  delay(1500);
  lift.calibrationLift();
  delay(500);
  vibrationIntrerruptOn();
  makeBeep(30, 30, 2);
}

void loop() {
  if (isVibrated) {
    delay(500);
    if (sensors.isTargetsStatesChanges()) {
      makeBeep(5, 5, 10);
    } else {
      makeBeep(10, 200, 3);
    }
    isVibrated = false;
  }
    
  if (sensors.isAllTargetsDown()) {
    vibrationIntrerruptOff();
    lift.moveTargetsUp();
    vibrationIntrerruptOn();
  }

  while(sensors.batteryVoltage() < 10.5) {
    makeBeep(5, 50, 1);
  }
}

void vibrationIntrerruptOn() {
  attachInterrupt(INTERRUPT_N, vibrationSensorSignaled, RISING);
  delay(50);
  isVibrated = false;
}

void vibrationIntrerruptOff() {
  detachInterrupt(INTERRUPT_N);
}


void vibrationSensorSignaled() {
  isVibrated = true;
}
