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
  if (takeVoltValue() < 50) {
    makeBeep(10, 10, 3);
    while(1) {
    }
  }
  closedSensorValue = takeSensorValue();
  delay(2000);
  moveMechanDown();
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
    delay(200);
    makeBeep(200, 200, 1);

    while (takeVoltValue() < 105) {
      makeBeep(20, 20, 5);
      delay(1000);
    }
    
    delay(timeBeforeUp);
    
    makeBeep(50, 50, 2);
    moveMechanUp();
    moveMechanDown();
    makeBeep(50, 50, 2);
    return true;
  }
  return false;
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

void moveMechanUp(){
  turnStepperUp();
  for (int i=0; i<stepsOneWay; ++i) {
    makeStep();
  }
}

void moveMechanDown(){
  turnStepperDown();
  for (int i=0; i<stepsOneWay; ++i) {
    makeStep();
  }
}

void turnStepperDown() {
  PORTB |= B00100000; //digitalWrite(DIR_STEPPER_PIN, HIGH);
}

void turnStepperUp() {
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
