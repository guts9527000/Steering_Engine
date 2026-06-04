#include "global.h"

static void Led(LedColor color) {
    switch (color) {
        case RED:
            HAL_GPIO_WritePin(GPIOA, RED_PIN, GPIO_PIN_RESET);
            break;
        case GREEN:
            HAL_GPIO_WritePin(GPIOA, GREEN_PIN, GPIO_PIN_RESET);
            break;
        case BLUE:
            HAL_GPIO_WritePin(GPIOA, BLUE_PIN, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

void Led_Mode(Mode mode) {
    switch (mode) {
        case Manual:
            HAL_GPIO_WritePin(GPIOA,RED_PIN|GREEN_PIN|BLUE_PIN, GPIO_PIN_SET);
            Led(GREEN);
            break;
        case Middle:
            HAL_GPIO_WritePin(GPIOA,RED_PIN|GREEN_PIN|BLUE_PIN, GPIO_PIN_SET);
            Led(BLUE);
            break;
        case Scan:
            HAL_GPIO_WritePin(GPIOA,RED_PIN|GREEN_PIN|BLUE_PIN, GPIO_PIN_SET);
            Led(GREEN);
            Led(BLUE);
            break;
        default:
            break;
    }
}