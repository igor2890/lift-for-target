#include "SensorsManager.h"
#include "MotorManager.h"
#include "config.h"

const int stepsOneWay = 1200;
SensorsManager sensors;
MotorManager motor;

void setup() {
  // Serial.begin(SERIAL_SPEED);
  sensors.configurePins();
  sensors.storeLaserSensorLevel();
  motor.configurePins();
  pinMode(TONE_PIN, OUTPUT);
  if (sensors.isBatteryNotConnected()) {
    while(1) {
      makeBeep(10,5000,10);
    }
  }
  delay(2000);
  motor.moveMechan(Down, stepsOneWay);
  makeBeep(30, 30, 2);
}

void loop() {
  if (isMoveTargetsUp()) {
    sensors.storeLaserSensorLevel();
  }

  while(sensors.batteryVoltage() < 10.5) {
        makeBeep(10, 500, 1);
  }
}

bool isMoveTargetsUp() {
  if (sensors.isAllTargetsDown()) {
    delay(500);
    if (sensors.isAllTargetsDown()) {
      makeBeep(200, 200, 1);
    
      delay(2000);
    
      makeBeep(50, 50, 2);
      motor.moveMechan(Up, stepsOneWay - 200);
      finishingUp();
      motor.moveMechan(Down, 200);
      
      while(sensors.isAllTargetsDown()) {
        finishingUp();
        motor.moveMechan(Up, 200);
      }
      
      delay(500);
      motor.moveMechan(Down, stepsOneWay - 200);

      makeBeep(50, 50, 2);
      return true;
    }
  }
  return false;
}

void finishingUp() {
  while (sensors.isAllTargetsDown()) {
    motor.moveMechan(Up, 1);
  }
  motor.moveMechan(Up, 20);
}

void makeBeep(int beepLength, int pauseBetweenBeep, int times){
  for(int i = 0; i < times; ++i){
    PORTD |= B00000100;
    delay(beepLength);
    PORTD &= ~B00000100;
    delay(pauseBetweenBeep);
  }
}
