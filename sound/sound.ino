#include "../include/misc-setup.h"

uint16_t backlight_time;

// I have two tiny (~1cm tall ~1cm wide) cylinder "buzzers"
// One labeled "passive", one labeled "active". This is sample
// code I found to drive them. They work, but not great.
//
// Notable issues with this:
//  neither is very loud
//  while active works every time through the loop,
//  the passive only works the first time. I don't
//  know why.
//
// Both sound much better with an old 16ohm 0.5W 2.25" (56mm)
// speaker I have, and the "active" style tone buzzing is the
// way I'd prefer to code the alarm anyway.

#define PASSIVE_PIN 3		// side marked +
#define ACTIVE_PIN  4		// side marked +
// wire other side to ground on both

#define NOTE_COUNT 8
#define NOTE_TIME  500
uint16_t tune[NOTE_COUNT] = {
   523,
   587,
   659,
   698,
   784,
   880,
   988,
   1047,
};

void setup() {
  Serial.begin(9600);

  pinMode(PASSIVE_PIN, OUTPUT);
  pinMode(ACTIVE_PIN, OUTPUT);
  
  digitalWrite(PASSIVE_PIN, LOW);
  digitalWrite(ACTIVE_PIN, LOW);
}
 
void loop() {
  uint8_t count;


  count = 80;
  Serial.print("\r\nActive ");
  Serial.print(count);
  while(count) {
    digitalWrite(ACTIVE_PIN, HIGH);
    delay(1);//wait for 1ms
    digitalWrite(ACTIVE_PIN, LOW);
    delay(1);//wait for 1ms
    count --;
  }

  count = 100;
  Serial.print("\r\nActive ");
  Serial.print(count);
  while(count) {
    digitalWrite(ACTIVE_PIN, HIGH);
    delay(2);
    digitalWrite(ACTIVE_PIN, LOW);
    delay(2);
    count --;
  }

  count = 60;
  Serial.print("\r\nActive ");
  Serial.print(count);
  while(count) {
    digitalWrite(ACTIVE_PIN, HIGH);
    delay(4);
    digitalWrite(ACTIVE_PIN, LOW);
    delay(4);
    count --;
  }

  count = 80;
  Serial.print("\r\nActive ");
  Serial.print(count);
  while(count) {
    digitalWrite(ACTIVE_PIN, HIGH);
    delay(3);
    digitalWrite(ACTIVE_PIN, LOW);
    delay(3);
    count --;
  }

  Serial.print("\r\nPause ");
  delay(1000);

  Serial.print("\r\nPassive ");
  for (int out_note; out_note < NOTE_COUNT; out_note++) {
     tone(PASSIVE_PIN, tune[out_note], NOTE_TIME);
     delay(NOTE_TIME);
  }
  digitalWrite(PASSIVE_PIN, LOW);

  Serial.print("\r\nPause ");
  delay(1000);

} // end loop()


