#include "SensorsManager.h"
#include "LiftManager.h"
#include "Beep.h"
#include "config.h"

SensorsManager sensors;
LiftManager lift = LiftManager(&sensors, 1050);

void setup() {
//  Serial.begin(SERIAL_SPEED);
  sensors.configurePins();
  lift.configurePins();
  pinMode(TONE_PIN, OUTPUT);
  if (sensors.isBatteryNotConnected()) {
    while(1) {
      makeBeep(10,5000,10);
    }
  }
  delay(2000);
  lift.calibrationLift();
  makeBeep(30, 30, 2);
}

void loop() {
  delay(500);
  if (sensors.isAllTargetsDown()) {
    lift.moveTargetsUp();
  }

  if (sensors.isTargetsStatesChanges()) {
    makeBeep(10, 10, 2);
  }

  while(sensors.batteryVoltage() < 10.5) {
    makeBeep(5, 500, 1);
  }
}
