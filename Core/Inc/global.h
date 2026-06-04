
#ifndef STEERING_ENGINE_GLOBAL_H
#define STEERING_ENGINE_GLOBAL_H

#include "main.h"
#include "tim.h"
#include "segment.h"
#include "led.h"
#include "mode.h"
#include "servo.h"

void Led_Mode(Mode mode);

extern volatile int32_t encoder_count;
extern volatile uint8_t encoder_btn_pressed;
extern volatile uint8_t flicker_bit;
extern volatile int servo_speed;
extern volatile uint16_t tim;
extern volatile uint8_t double_click;
extern volatile uint32_t last_click_time;
extern volatile uint8_t scan_direction;

#endif //STEERING_ENGINE_GLOBAL_H
