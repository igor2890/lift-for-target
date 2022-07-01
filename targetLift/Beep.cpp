#include <Arduino.h>
#include "Beep.h"
#include "config.h"

void makeBeep(int beepLength, int pauseBetweenBeep, int times){
  for(int i = 0; i < times; ++i){
    digitalWrite(TONE_PIN, HIGH); //PORTD |= B00000100;
    delay(beepLength);
    digitalWrite(TONE_PIN, LOW); //PORTD &= ~B00000100;
    delay(pauseBetweenBeep);
  }
}
