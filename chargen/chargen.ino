
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
  analogWrite(CONTRAST_PIN,  HIGH);

  lcd.begin(20,4);

  digitalWrite(BACKLIGHT_PIN, HIGH);
  backlight_time = INIT_BACKLIGHT_TIME;
}
 
// this is everything, but you can edit it down to just defined
// characters and make it more meaningful
uint8_t charset[256] = {
        00, 01, 02, 03, 04, 05, 06, 07, 010, 011, 012, 013, 014,
        015, 016, 017, 020, 021, 022, 023, 024, 025, 026, 027,
        030, 031, 032, 033, 034, 035, 036, 037,
        ' ', '!', '"', '#', '$', '%', '&', ',', '(', ')', '*',
        '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5',
        '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a',
        'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
        'x', 'y', 'z', '{', '|', '}', '~',
        0177, 0200, 0201, 0202, 0203, 0204, 0205, 0206, 0207, 0210,
        0211, 0212, 0213, 0214, 0215, 0216, 0217, 0220, 0221, 0222,
        0223, 0224, 0225, 0226, 0227, 0230, 0231, 0232, 0233, 0234,
        0235, 0236, 0237, 0240, 0241, 0242, 0243, 0244, 0245, 0246,
        0247, 0250, 0251, 0252, 0253, 0254, 0255, 0256, 0257, 0260,
        0261, 0262, 0263, 0264, 0265, 0266, 0267, 0270, 0271, 0272,
        0273, 0274, 0275, 0276, 0277, 0300, 0301, 0302, 0303, 0304,
        0305, 0306, 0307, 0310, 0311, 0312, 0313, 0314, 0315, 0316,
        0317, 0320, 0321, 0322, 0323, 0324, 0325, 0326, 0327, 0330,
        0331, 0332, 0333, 0334, 0335, 0336, 0337, 0340, 0341, 0342,
        0343, 0344, 0345, 0346, 0347, 0350, 0351, 0352, 0353, 0354,
        0355, 0356, 0357, 0360, 0361, 0362, 0363, 0364, 0365, 0366,
        0367, 0370, 0371, 0372, 0373, 0374, 0375, 0376, 0377
};

#define lcd_setCursor(X,Y) delay(150); lcd.setCursor((X),(Y))
#define lcd_write(X)       lcd.write(X);

uint8_t
lcdchargen(uint8_t width, uint8_t height,
           uint8_t start, uint8_t stop,
	   uint8_t top, uint8_t offset)
{
  for(; height > top; top ++) {
    lcd_setCursor(0, top);
    for (uint8_t iterator = 0; iterator < width; iterator ++) {
      uint16_t index = start + offset + iterator;
      if(index > stop) { index = (index % (stop - start)) + start; }
      lcd_write(charset[index]);
      delay(5);
    }
    offset ++;
    if (offset >= stop) { offset = 0; }
  }
  return offset;
}

void loop() {
  uint8_t offseta = 0;
  uint8_t offsetb = 0;

  while( 1 ) {
                       // w  h    s    e  t,      o
    offseta = lcdchargen(20, 2,  32, 127, 0, offseta);
    offsetb = lcdchargen(20, 4, 160, 255, 2, offsetb);

  }
} // end loop()

