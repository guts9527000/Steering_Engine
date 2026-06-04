
#ifndef STEERING_ENGINE_DISPLAY_H
#define STEERING_ENGINE_DISPLAY_H

#define A GPIO_PIN_0
#define B GPIO_PIN_1
#define C GPIO_PIN_2
#define D GPIO_PIN_3
#define E GPIO_PIN_4
#define F GPIO_PIN_5
#define G GPIO_PIN_6
#define DIG1 GPIO_PIN_7
#define DIG2 GPIO_PIN_8
#define DIG3 GPIO_PIN_9

void Set_Segment(uint8_t digit);
void Display_3Digit(uint16_t num);

extern const uint8_t seg_code[];

extern uint8_t hundred;
extern uint8_t ten;
extern uint8_t one;
extern volatile uint8_t cnt;

#endif //STEERING_ENGINE_DISPLAY_H
