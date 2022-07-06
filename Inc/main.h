/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_15
#define LED3_GPIO_Port GPIOC
#define MAIN_V_Pin GPIO_PIN_0
#define MAIN_V_GPIO_Port GPIOC
#define SYSTEM_V_Pin GPIO_PIN_1
#define SYSTEM_V_GPIO_Port GPIOC
#define LED5_Pin GPIO_PIN_2
#define LED5_GPIO_Port GPIOC
#define MAIN_I_Pin GPIO_PIN_3
#define MAIN_I_GPIO_Port GPIOC
#define TOUCH1_Pin GPIO_PIN_0
#define TOUCH1_GPIO_Port GPIOA
#define BATT_V_Pin GPIO_PIN_1
#define BATT_V_GPIO_Port GPIOA
#define IN_C_Pin GPIO_PIN_5
#define IN_C_GPIO_Port GPIOA
#define TAG_A_O_Pin GPIO_PIN_7
#define TAG_A_O_GPIO_Port GPIOA
#define IN_REED1_Pin GPIO_PIN_4
#define IN_REED1_GPIO_Port GPIOC
#define IN_REED2_Pin GPIO_PIN_5
#define IN_REED2_GPIO_Port GPIOC
#define LED2B0_Pin GPIO_PIN_0
#define LED2B0_GPIO_Port GPIOB
#define GPS_EN_Pin GPIO_PIN_12
#define GPS_EN_GPIO_Port GPIOB
#define SIM_S_Pin GPIO_PIN_14
#define SIM_S_GPIO_Port GPIOB
#define GSM_EN_Pin GPIO_PIN_15
#define GSM_EN_GPIO_Port GPIOB
#define SOL_CNTRL_Pin GPIO_PIN_7
#define SOL_CNTRL_GPIO_Port GPIOC
#define MAIN_PWR_Pin GPIO_PIN_8
#define MAIN_PWR_GPIO_Port GPIOC
#define VIBR_IN_Pin GPIO_PIN_9
#define VIBR_IN_GPIO_Port GPIOC
#define TAG_OUT_Pin GPIO_PIN_8
#define TAG_OUT_GPIO_Port GPIOA
#define TAG_IN_Pin GPIO_PIN_11
#define TAG_IN_GPIO_Port GPIOA
#define FLASH_CS2_Pin GPIO_PIN_12
#define FLASH_CS2_GPIO_Port GPIOA
#define FLASH_CS1_Pin GPIO_PIN_13
#define FLASH_CS1_GPIO_Port GPIOA
#define BCKLIGHT_Pin GPIO_PIN_14
#define BCKLIGHT_GPIO_Port GPIOA
#define CRG_STAT2_Pin GPIO_PIN_15
#define CRG_STAT2_GPIO_Port GPIOA
#define CRG_STAT1_Pin GPIO_PIN_10
#define CRG_STAT1_GPIO_Port GPIOC
#define CRG_EN_Pin GPIO_PIN_11
#define CRG_EN_GPIO_Port GPIOC
#define CRG_STOP_Pin GPIO_PIN_12
#define CRG_STOP_GPIO_Port GPIOC
#define TOUCH2_Pin GPIO_PIN_9
#define TOUCH2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
