
// Hitachi HD44780 compatible LCD library
#include <LiquidCrystal.h>

// Hitachi HD44780 LCD
#include "../include/lcd-setup.h"

#include "../include/misc-setup.h"

uint16_t backlight_time;

void setup() {
  Serial.begin(9600);

  pinMode(BACKLIGHT_PIN, OUTPUT);
  pinMode(CONTRAST_PIN, OUTPUT);
  
  digitalWrite(BACKLIGHT_PIN, LOW);

  lcd.begin(20,4);
  // up to 8 custom characters can be defined
  lcd.createChar(1,     bell);
  lcd.createChar(2,   nobell);
  lcd.createChar(3, setupper);
  lcd.createChar(4, setlower);
  lcd.createChar(5,  setboth);

  analogWrite(CONTRAST_PIN,  INIT_CONTRAST);

  lcd.setCursor(0,0);
  lcd.print("Hello, alarm clock");
  //         12345678901234567890
  lcd.write(                   2);
  lcd.write(                    1);

// show three characters in a space 6 chars wide
#define charsample(X,Y,Z) \
	lcd.write(X); lcd.print("  "); \
	lcd.write(Y); lcd.write('/'); lcd.write(Z)
  
  lcd.setCursor( 0, 1);   charsample('%',  0xDF, 0xA1);
  lcd.setCursor(10, 1);   charsample(0xDB, 0xA2, 0xA3);
  lcd.setCursor( 0, 2);   charsample('O',  '^',  'v' );
  lcd.setCursor(10, 2);   charsample(':',  0xA5, '.' );
  lcd.setCursor( 0, 3);   charsample('/',  '`',  0xA4);
  lcd.setCursor(10, 3);   charsample(05,    03,    04);

  digitalWrite(BACKLIGHT_PIN, HIGH);
  backlight_time = INIT_BACKLIGHT_TIME;
}
 
void loop() {
  uint8_t count = 99;
  while(count) {
    Serial.print("\r\nLoop");
    Serial.print(count);

    // throb contrast to see how it works
    //   -> answer, higher is better looking
    analogWrite(CONTRAST_PIN,  count);
    count -= 5; delay(500);
    if (count < 5) { count = 99; }
  }
} // end loop()


