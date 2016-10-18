/**
  ******************************************************************************
  * File Name          : TIM.h
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

/* USER CODE BEGIN Private defines */

typedef enum{
	FWD=0,//正转/向前
	REV//反转/向后
} dirType;//方向类型枚举

typedef struct _motor{
	dirType dir;//记录电机方向
	uint32_t channelN;//电机红线对应的定时器通道
	uint32_t channelP;//电机黑线对应的定时器通道
	uint16_t speed;//电机速度
	void * ops;//电机操作函数,此处由于motorOpsType类型尚未定义所以必须用void *类型进行代替
}* Motor;//电机类

typedef struct{
	void (*setSpeed)(Motor motor,uint16_t speed);//设置速度，满速为999
	void (*setDir)(Motor motor,dirType dir);//设置方向
	void (*stop)(Motor motor);//设置speed为0因此没有对应的run方法
} motorOpsType;//电机操作函数接口


typedef struct _car{
	Motor motorL;//左电机
	Motor motorR;//右电机
	void * ops;//小车的操作函数
}* Car;//小车类

typedef struct{
	void (*runAsSpeed)(Car car,uint16_t speed,dirType dir);//以speed的速度向前/后跑
	void (*turnedToLeft)(Car car,uint16_t value);//向左 value为两个电机速度之间的差值此时会右电机加速，左电机速度不变
	void (*turnedToRight)(Car car,uint16_t value);//向右 value为两个电机速度之间的差值此时会左电机加速，右电机速度不变
	void (*stop)(Car car);//停下来
} carOpsType;//小车操作函数类
/* USER CODE END Private defines */

extern void Error_Handler(void);

void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
                    
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
