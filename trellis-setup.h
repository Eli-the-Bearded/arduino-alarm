#ifndef __trellis_setup_h_
#define __trellis_setup_h_
#include "Adafruit_Trellis.h"

#define NUMTRELLIS 2
#define numKeys (NUMTRELLIS * 16)

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_Trellis matrix1 = Adafruit_Trellis();

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1);

// left board has orange column (1x4), and white red yellow, blue rows (3x1)
#define TRELLIS_LEFT_ADDR  0x72
// right board has white red yellow, blue rows (4x1)
#define TRELLIS_RIGHT_ADDR 0x70

#define ALARM_1 31
#define ALARM_2 27
#define ALARM_3 23
#define ALARM_4 19

#define SUN_1 30
#define SUN_2 26
#define SUN_3 22
#define SUN_4 18

#define MON_1 29
#define MON_2 25
#define MON_3 21
#define MON_4 17

#define TUE_1 28
#define TUE_2 24
#define TUE_3 20
#define TUE_4 16

#define WED_1 15
#define WED_2 11
#define WED_3 7
#define WED_4 3

#define THU_1 14
#define THU_2 10
#define THU_3 6
#define THU_4 2

#define FRI_1 13
#define FRI_2 9
#define FRI_3 5
#define FRI_4 1

#define SAT_1 12
#define SAT_2 8
#define SAT_3 4
#define SAT_4 0

// Left (orange LED) to right, top (white) to bottom order
uint8_t buttons[numKeys] = {
//  left board                    |  right board
    ALARM_1, SUN_1, MON_1, TUE_1,    WED_1, THU_1, FRI_1, SAT_1,
    ALARM_2, SUN_2, MON_2, TUE_2,    WED_2, THU_2, FRI_2, SAT_2,
    ALARM_3, SUN_3, MON_3, TUE_3,    WED_3, THU_3, FRI_3, SAT_3,
    ALARM_4, SUN_4, MON_4, TUE_4,    WED_4, THU_4, FRI_4, SAT_4
};


// Connect the INT wire to pin #A2 (can change later!)
#define TRELLIS_INTPIN A2
// Connect Trellis Vin to 5V and Ground to ground.
// Connect I2C SDA pin to your Arduino SDA line
// Connect I2C SCL pin to your Arduino SCL line

#endif
