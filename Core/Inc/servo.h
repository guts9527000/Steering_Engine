//
// Created by 24547 on 2026/6/3.
//

#ifndef STEERING_ENGINE_SERVO_H
#define STEERING_ENGINE_SERVO_H

void Servo_SetAngle(uint8_t angle);

extern volatile uint16_t pulse;
extern volatile uint8_t angle;

#endif //STEERING_ENGINE_SERVO_H
