#define SERIAL_SPEED 115200

#define DIR_STEPPER_PIN 13
#define STEP_STEPPER_PIN 12

#define TONE_PIN 2

#define VOLT_PIN A3
#define SENSOR_PIN A7

int closedSensorValue = 0;
bool isMakeMove = false;
const int stepsOneWay = 1200;
const int timeBeforeUp = 3000;

void setup() {
  //Serial.begin(SERIAL_SPEED);
  pinMode(DIR_STEPPER_PIN, OUTPUT);
  pinMode(STEP_STEPPER_PIN, OUTPUT);
  pinMode(TONE_PIN, OUTPUT);
  checkBatteryConnection();
  closedSensorValue = takeSensorValue();
  delay(2000);
  moveMechanUpOrDown(false, stepsOneWay);
  makeBeep(50, 50, 2);
}

void loop() {
  isMakeMove = checkSensorAndMoveMechan(closedSensorValue);
  if (isMakeMove) {
    closedSensorValue = takeSensorValue();
    isMakeMove = false;
  }
}

bool checkSensorAndMoveMechan(int sensorValue) {
  if ((sensorValue - 500) > takeSensorValue()) {
    delay(1000);
    if ((sensorValue - 500) > takeSensorValue()) {
      makeBeep(200, 200, 1);

      checkBatteryVolt();
    
      delay(timeBeforeUp);
    
      makeBeep(50, 50, 2);
      moveMechanUpOrDown(true, stepsOneWay - 200);
      finishingUp(sensorValue);
      moveMechanUpOrDown(false, 200);
      
      while ((sensorValue - 500) > takeSensorValue()) {
        finishingUp(sensorValue);
        moveMechanUpOrDown(false, 200);
      }
      
      delay(500);
      moveMechanUpOrDown(false, stepsOneWay - 200);
      makeBeep(50, 50, 2);
      return true;
    }
  }
  return false;
}

void checkBatteryConnection() {
  if (takeVoltValue() < 50) {
    makeBeep(10, 10, 3);
    while(1) {
    }
  }
}

void checkBatteryVolt() {
  while (takeVoltValue() < 105) {
    makeBeep(20, 20, 5);
    delay(1000);
  }
}

int takeSensorValue() {
  return analogRead(SENSOR_PIN);
}

int takeVoltValue(int battVoltValue) {
  delay(50);
  return (takeVoltValue() + battVoltValue) / 2;
}

int takeVoltValue(){
  return (analogRead(VOLT_PIN) * 10) / 43;
}

void finishingUp(int sensorValue) {
  while ((sensorValue - 500) > takeSensorValue()) {
    delayMicroseconds(500);
    makeStep();
  }
  moveMechanUpOrDown(true, 20);
}

void moveMechanUpOrDown(bool isUp, int steps) {
  if (isUp) {
    dirMoveUp();
  }
  else {
    dirMoveDown();
  }
  for (int i=0; i<steps; ++i) {
    makeStep();
  }
}

void dirMoveDown() {
  PORTB |= B00100000; //digitalWrite(DIR_STEPPER_PIN, HIGH);
}

void dirMoveUp() {
  PORTB &= ~B00100000; //digitalWrite(DIR_STEPPER_PIN, LOW);
}

void makeStep() {
  PORTB |= B00010000;
  delayMicroseconds(500);
  PORTB &= ~B00010000;
  delayMicroseconds(500);
}

void makeBeep(int beepLength, int pauseBetweenBeep, int times){
  for(int i = 0; i < times; ++i){
    PORTD |= B00000100;
    delay(beepLength);
    PORTD &= ~B00000100;
    delay(pauseBetweenBeep);
  }
}
