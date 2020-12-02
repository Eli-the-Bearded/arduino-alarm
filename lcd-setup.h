#ifndef __lcd_setup_h_
#define __lcd_setup_h_


// On Hitachi
// Pin           1    2   3  4   5  6   7   8   9  10  11  12  13  14  15  16
// Pin name    VSS  VDD  V0 RS  RW  E  D0  D1  D2  D3  D4  D5  D6  D7   A   K
//
// VSS, RW, K       all connect to ground
// VDD                  connect to 5v
// V0 is contast        connect as below
// RS is reg select     connect as below
// E is enable          connect as below
// D0-D3 data        NO CONNECT
// D4-D7 data       all connect as below
// A is backlight       connect as below


// Name the Arduino outputs for the Hitachi functions
#define RS_PIN      7
#define ENABLE_PIN  8
#define D4_PIN      9
#define D5_PIN     10
#define D6_PIN     11
#define D7_PIN     12

// These are all simple digital out
LiquidCrystal lcd(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

// Analog out
// Backlight is labeled "A"
#define BACKLIGHT_PIN    5
#define INIT_BACKLIGHT  50
#define STOP_BACKLIGHT   0

// Contrast is labeled V0
// might not use, might use trim pot instead
#define CONTRAST_PIN    6
#define INIT_CONTRAST  50

// 16x2 is common side, this is a bigger screen
#define LCD_COL_COUNT 20
#define LCD_ROW_COUNT  4

/*
page 17 of data sheet has font reference
Looking for good matched pairs of upper / lower
  %     DF / A1
  DB    A2 / A3
  O     ^  / v
  :     A5 / .
  \     `  / A4
  ^whoops, is yen sign
*/

byte bell[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b10001,
  0b10101,
  0b11111,
  0b00100,
};

byte nobell[8] = {
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
};

byte setupper[8] = {
  0b01100,
  0b11110,
  0b10010,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

byte setlower[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10010,
  0b11110,
  0b01100,
};

byte setboth[8] = {
  0b01100,
  0b11110,
  0b10010,
  0b00000,
  0b10010,
  0b11110,
  0b01100,
};

#endif
