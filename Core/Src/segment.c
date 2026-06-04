#include "global.h"

const uint8_t seg_code[] = {
     0x3F, // "0"
     0x06, // "1"
     0x5B, // "2"
     0x4F, // "3"
     0x66, // "4"
     0x6D, // "5"
     0x7D, // "6"
     0x07, // "7"
     0x7F, // "8"
     0x6F // "9"
 };

uint8_t hundred = 0;
uint8_t ten = 0;
uint8_t one = 0;
volatile uint8_t cnt = 0;

void Set_Segment(uint8_t digit) {
     HAL_GPIO_WritePin(GPIOB, A, digit & 0x01);
     HAL_GPIO_WritePin(GPIOB, B, digit & 0x02);
     HAL_GPIO_WritePin(GPIOB, C, digit & 0x04);
     HAL_GPIO_WritePin(GPIOB, D, digit & 0x08);
     HAL_GPIO_WritePin(GPIOB, E, digit & 0x10);
     HAL_GPIO_WritePin(GPIOB, F, digit & 0x20);
     HAL_GPIO_WritePin(GPIOB, G, digit & 0x40);
}

void Display_3Digit(uint16_t num) {
     hundred = num / 100;
     ten = (num % 100) / 10;
     one = num % 10;
}