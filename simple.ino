// wire for i2c
#include <Wire.h>

// Hitachi HD44780 compatible LCD library
#include <LiquidCrystal.h>

// Hitachi HD44780 LCD
#include "lcd-setup.h"

// ds3231 is a real time clock 12c component
#include "ds3231.h"

// Trellis is an i2c buttons with LEDs system
#include "trellis-setup.h"
 
#include "misc-setup.h"

struct ts t; 

// overflows in about 49 days
uint32_t long uptime;

uint16_t backlight_time;

uint8_t count;
uint8_t state;
uint8_t off_button;
 int8_t buzzer;

void power_on_show();
void show_time_serial(struct ts *t);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  /* locally mod, different define */
  DS3231_init(DS3231_CONTROL_INTCN);

  // Trellis INT pin requires a pullup
  pinMode(TRELLIS_INTPIN, INPUT);
  digitalWrite(TRELLIS_INTPIN, HIGH);

  pinMode(BACKLIGHT_PIN, OUTPUT);
  pinMode(CONTRAST_PIN, OUTPUT);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(OFF_BUTTON_PIN, INPUT);
  digitalWrite(OFF_BUTTON_PIN, HIGH);

  digitalWrite(BACKLIGHT_PIN, HIGH);
  analogWrite(CONTRAST_PIN,  INIT_CONTRAST);

  lcd.begin(LCD_COL_COUNT, LCD_ROW_COUNT);
  lcd.createChar(1,   bell);
  lcd.createChar(2, nobell);

  //Serial.print("size of uptime : ");
  //Serial.print(sizeof(unsigned long));  == 4

  //lcd.print("Hello, alarm clock");
  lcd.print("Hello, ");
  //         12345678901234567890
  lcd.write(        2);
  lcd.write(         1);

  // boards listed in ADDRESS order, low to high
  trellis.begin( TRELLIS_RIGHT_ADDR, TRELLIS_LEFT_ADDR );
  power_on_show();

  lcd.print(              byte(2));
  lcd.print(               byte(1));

  backlight_time = INIT_BACKLIGHT_TIME;
  off_button = buzzer = count = state = 0;
}
 
void loop() {
  uint32_t loopstart, wait;
  uint16_t fraction;

  loopstart = uptime = millis();
  fraction  = loopstart % 1000;

  // time stuff needs to run every second, can't miss any
  // use state to not trigger twice during same second
  // 0 : just started
  // 16: ~480 ms
  // 33: ~990 ms
  if (fraction < 30) {
     count = 0;
     DS3231_get(&t);
     if((t.sec % 5) == 0) show_time_serial(&t);
     lcd.setCursor(0, 1);

     // demo time output, just seconds
     if(t.sec < 10) { lcd.print(" "); }
     lcd.print(t.sec);

     // show count down to backlight off
     lcd.setCursor(12, 1);
     lcd.print("        ");
     lcd.setCursor(12, 1);
     lcd.print(backlight_time);

     // show uptime millis
     lcd.setCursor(12, 2);
     lcd.print("        ");
     lcd.setCursor(12, 2);
     lcd.print(uptime);

     // demo alarm: one second every minute
     if(t.sec == 0) {
       lcd.setCursor(0, 3);
       lcd.print("alarm ...");
       buzzer = 1;
     } else {
       if (buzzer) {
         digitalWrite(BUZZER_PIN, LOW);
         buzzer = 0;
       }
     }
  }

  // check state of alarm turn off button
  // looking for both high and low having been seen, each for 2 intervals
  if (digitalRead(OFF_BUTTON_PIN) == LOW) {
    state = 1; // demo use of state; actual use will be more complicated
    if (off_button & OFF_PUSHED1) {
      off_button |= OFF_PUSHED2;
    } else {
      off_button |= OFF_PUSHED1;
    }
  } // if low
  else {
    state = 2;
    if (off_button & OFF_RELEASED1) {
      off_button |= OFF_RELEASED2;
    } else {
      off_button |= OFF_RELEASED1;
    }
  }

  // got both sets of two
  if ( off_button == ALL_SET ) {
    off_button = OFF_START;
    Serial.println("alarm off request");
    lcd.setCursor(0, 3);
    lcd.print("alarm off");
    analogWrite(BACKLIGHT_PIN, INIT_BACKLIGHT);
    backlight_time = INIT_BACKLIGHT_TIME;
  }

  // check the array of soft push buttons
  if (trellis.readSwitches()) {
    // go through every button
    for (uint8_t i=0; i<numKeys; i++) {
      // if it was pressed, turn it on
      if (trellis.justPressed(i)) {
	Serial.print("v"); Serial.println(i);
	trellis.setLED(i);
        lcd.setCursor(0, 2);
	lcd.print("pressed ");
	lcd.print(10 + i);   // ensure 2 digits
        analogWrite(BACKLIGHT_PIN, INIT_BACKLIGHT);
        backlight_time = INIT_BACKLIGHT_TIME;
      } 
      // if it was released, turn it off
      if (trellis.justReleased(i)) {
	Serial.print("^"); Serial.println(i);
	trellis.clrLED(i);
	lcd.print("release ");
	lcd.print(10 + i);   // ensure 2 digits
      }
    }
    // tell the trellis to set the LEDs we requested
    trellis.writeDisplay();
  }

  // when buzzing, toggle each loop
  if(buzzer) {
    if(buzzer > 0) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }
    buzzer *= -1;
  }

  // turn off light after an interval of no button pushes
  if(backlight_time > MIN_DELAY) {
    backlight_time -= MIN_DELAY;
    if (backlight_time < MIN_DELAY) {
      digitalWrite(BACKLIGHT_PIN, LOW);
    }
  }

  wait = loopstart - millis();
  if (wait < MIN_DELAY) {
    delay(wait);
  } else {
    // probably 49day wraparound
    delay(MIN_DELAY);
  }
  count ++;
} // end loop()

void power_on_show() {
  // light up all the LEDs in order
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(buttons[i]);
    trellis.writeDisplay();    
    delay(50);
  }
  // then turn them off
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(buttons[i]);
    trellis.writeDisplay();    
    delay(50);
  }
} // end power_on_show()

void show_time_serial(struct ts *t) {
  Serial.print("Date : ");
  Serial.print(t->mday);
  Serial.print("/");
  Serial.print(t->mon);
  Serial.print("/");
  Serial.print(t->year);
  Serial.print("\t Hour : ");
  Serial.print(t->hour);
  Serial.print(":");
  Serial.print(t->min);
  Serial.print(".");
  Serial.print(t->sec);
  Serial.print("    ");
  Serial.println(state);
} // end show_time_serial()
