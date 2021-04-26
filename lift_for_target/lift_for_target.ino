#define SERIAL_SPEED 115200

#define DIR_STEPPER_PIN 13
#define STEP_STEPPER_PIN 12

#define TONE_PIN 2

#define VOLT_PIN A3
#define SENSOR_PIN A7

int closedSensorValue = 0;
const int stepsOneWay = 1200;
int battVoltValue = 0;

void setup() {
  //Serial.begin(SERIAL_SPEED);
  pinMode(DIR_STEPPER_PIN, OUTPUT);
  pinMode(STEP_STEPPER_PIN, OUTPUT);
  pinMode(TONE_PIN, OUTPUT);
  battVoltValue = takeVoltValue();
  closedSensorValue = takeSensorValue();
  delay(2000);
  moveMechanDown();
  makeNoise(50);
  delay(50);
  makeNoise(50);
}

void loop() {
  checkSensorAndMoveMechan();

  battVoltValue = takeVoltValue();
  
  if (battVoltValue < 105) {
    while(1) {
      makeNoise(70);
      delay(2000);
    }
  }
}

void checkSensorAndMoveMechan() {
  if ((closedSensorValue - 500) > takeSensorValue()) {
    makeNoise(200);
    delay(10000);
    makeNoise(50);
    delay(50);
    makeNoise(50);
    delay(300);
    moveMechanUp();
    delay(100);
    closedSensorValue = takeSensorValue();
    moveMechanDown();
    delay(100);
    makeNoise(50);
    delay(50);
    makeNoise(50);
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

void makeNoise(int longNoise){
  PORTD |= B00000100;
  delay(longNoise);
  PORTD &= ~B00000100;
}
