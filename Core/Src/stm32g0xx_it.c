/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "global.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile int32_t encoder_count = 0;
volatile uint8_t encoder_btn_pressed = 0;
volatile uint8_t flicker_bit = 0;
volatile int servo_speed = 0;
volatile uint16_t tim = 0;
volatile uint8_t double_click = 0;
volatile uint32_t last_click_time = 0;
volatile uint8_t scan_direction = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */

  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break, update, trigger and commutation interrupts.
  */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 0 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
  switch (mode) {
    case Manual:{
      if (GPIO_Pin == GPIO_PIN_6) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)) {
          if (encoder_count >= 0) {
            switch (flicker_bit) {
              case 0:
                encoder_count++;
                break;
              case 1:
                encoder_count += 100;
                break;
              case 2:
                encoder_count += 10;
                break;
              case 3:
                encoder_count += 1;
                break;
              default:
                break;
            }
          }
        }
        else {
          if (encoder_count >= 0) {
            switch (flicker_bit) {
              case 0:
                encoder_count--;
                break;
              case 1:
                encoder_count -= 100;
                break;
              case 2:
                encoder_count -= 10;
                break;
              case 3:
                encoder_count -= 1;
                break;
              default:
                break;
            }
          }
        }
      }
      if (encoder_count > 180) {
        encoder_count = 180;
      }
      if (encoder_count < 0) {
        encoder_count = 0;
      }
    }
      break;
    case Scan: {
      if (GPIO_Pin == GPIO_PIN_6) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)) {
          if (servo_speed >= 0) {
            servo_speed++;
          }
        }
        else {
          if (servo_speed >= 0) {
            servo_speed--;
          }
        }
      }
      if (servo_speed > 8) {
        servo_speed = 8;
      }
      if (servo_speed < 0) {
        servo_speed = 0;
      }
      break;
      default:
      break;
    }
  }
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_5) {
    if (HAL_GetTick() - last_click_time < 300) {
      double_click++;
      if (double_click > 2) {
        double_click = 0;
      }
    }
    else {
      encoder_btn_pressed = 1;
    }
    last_click_time = HAL_GetTick();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  static volatile uint32_t flick_cnt = 0;
  if (htim->Instance == TIM1) {
    cnt++;
    flick_cnt++;
    tim++;
    //数码管
    switch (cnt) {
      case 1:
        //亮百位;
        if (flicker_bit == 1) {
          if (flick_cnt < 200) {
            HAL_GPIO_WritePin(GPIOB, DIG1|DIG2|DIG3, GPIO_PIN_SET);
            Set_Segment(seg_code[hundred]);
            HAL_GPIO_WritePin(GPIOB, DIG1, GPIO_PIN_RESET);
          }
          if (flick_cnt > 400) {
            flick_cnt = 0;
          }
        }
        else {
          HAL_GPIO_WritePin(GPIOB, DIG1|DIG2|DIG3, GPIO_PIN_SET);
          Set_Segment(seg_code[hundred]);
          HAL_GPIO_WritePin(GPIOB, DIG1, GPIO_PIN_RESET);
        }
        break;
      case 3:
        //亮十位;
        if (flicker_bit == 2) {
          if (flick_cnt < 200) {
            HAL_GPIO_WritePin(GPIOB, DIG1|DIG2|DIG3, GPIO_PIN_SET);
            Set_Segment(seg_code[ten]);
            HAL_GPIO_WritePin(GPIOB, DIG2, GPIO_PIN_RESET);
          }
          if (flick_cnt > 400) {
            flick_cnt = 0;
          }
        }
        else {
          HAL_GPIO_WritePin(GPIOB, DIG1|DIG2|DIG3, GPIO_PIN_SET);
          Set_Segment(seg_code[ten]);
          HAL_GPIO_WritePin(GPIOB, DIG2, GPIO_PIN_RESET);
        }
        break;
      case 5:
        //亮个位;
        if (flicker_bit == 3) {
          if (flick_cnt < 200) {
            HAL_GPIO_WritePin(GPIOB, DIG1|DIG2|DIG3, GPIO_PIN_SET);
            Set_Segment(seg_code[one]);
            HAL_GPIO_WritePin(GPIOB, DIG3, GPIO_PIN_RESET);
          }
          if (flick_cnt > 400) {
            flick_cnt = 0;
          }
        }
        else {
          HAL_GPIO_WritePin(GPIOB, DIG1|DIG2|DIG3, GPIO_PIN_SET);
          Set_Segment(seg_code[one]);
          HAL_GPIO_WritePin(GPIOB, DIG3, GPIO_PIN_RESET);
        }
        break;
      case 7:
        cnt = 0;
      default:
        break;
    }
    switch (mode) {
      case Middle: {
        scan_direction = 0;
        //最慢的速度转动90度用1.8s转动 20ms转一度
        if (tim >= 20 && encoder_count < 90) {
          encoder_count++;
          tim = 0;
        }
      }
        break;
      case Scan: {
        //改变转动1度的时间实现速度的切换 7.2s~1.44s
        if (tim >= (20 - servo_speed * 2)) {
          if (scan_direction == 0) {
            encoder_count++;
            if (encoder_count >= 180) {
              scan_direction = 1;
            }
          }
          else {
            encoder_count--;
            if (encoder_count <= 0) {
              scan_direction = 0;
            }
          }
          tim = 0;
        }
      }
      default:
        break;
    }

  }
}
/* USER CODE END 1 */

