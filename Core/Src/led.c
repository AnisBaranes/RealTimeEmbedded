#include <stdio.h>
#include "led.h"
#include "main.h"

extern TIM_HandleTypeDef htim6, htim2;
extern int brightnessValue;
extern uint32_t prevTick;


void LedInit(LED* led, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	led->counter = 0;
	led->GPIOx = GPIOx;
	led->GPIO_Pin = GPIO_Pin;
	led->peroid = 0;
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

void LedOn(LED* led)
{
	led->state = LED_ON;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, GPIO_PIN_SET);
}

void LedOff(LED* led)
{
	led->state = LED_OFF;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, GPIO_PIN_RESET);
}

void LedBlink(LED* led, int period)
{
	led->state = LED_BLINK;
	led->peroid = period;
	led->counter = 0;
}

void LedOnTimerInterrupt(LED* led)
{
	if(led->counter == led->peroid)
	{
		HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
		led->counter = 0;
	}
	else
	{
		led->counter ++;
	}
}

void StartPWM()
{
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
}



