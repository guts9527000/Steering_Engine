#include "global.h"

volatile uint16_t pulse = 500;
volatile uint8_t angle = 0;

void Servo_SetAngle(uint8_t set_angle)
{
	angle = set_angle;
	pulse = 500 + set_angle * 2000 / 180;
	__HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, pulse);
}
