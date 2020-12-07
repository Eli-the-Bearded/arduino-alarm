#ifndef __misc_setup_h_
#define __misc_setup_h_

// use an analog capable one
// write to this for the alarm sound
// this connects to + pin on buzzer; other pin to ground
#define BUZZER_PIN       3

// digital only OK
// read from this for turning alarm off
#define OFF_BUTTON_PIN   2

#define OFF_START        0
#define OFF_PUSHED1      1
#define OFF_PUSHED2      2
#define OFF_RELEASED1    4
#define OFF_RELEASED2    8
#define ALL_SET          (OFF_RELEASED2|OFF_RELEASED1|OFF_PUSHED2|OFF_PUSHED1)

// Just over 60 seconds; resets to this every Trellis button push
// 16 bit unsigned type, so  65535 is max
#define INIT_BACKLIGHT_TIME  60001

// Trellis minium poll interval
#define MIN_DELAY            30

#endif
