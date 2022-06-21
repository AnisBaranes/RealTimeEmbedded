#include <stdio.h>
#include "buzzer.h"
#include "main.h"
#include "button.h"


void StartBuzzer(TIM_HandleTypeDef *timer)
{
	HAL_TIM_Base_Start(timer);
	HAL_TIM_PWM_Start(timer, TIM_CHANNEL_1);
}

void StopBuzzer(TIM_HandleTypeDef *timer)
{
	HAL_TIM_PWM_Stop(timer, TIM_CHANNEL_1);
}

void pressBuzzer(TIM_HandleTypeDef *timer, BUTTON* btn)
{
	GPIO_PinState resPin = HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin);  //(B2_GPIO_Port, B2_Pin);
	if(resPin == GPIO_PIN_RESET)
	{
		StartBuzzer(timer);
	}
	else
	{
		StopBuzzer(timer);
	}
}

void music(TIM_HandleTypeDef *timer, int autoReload, int autoReloadTim6)
{
	__HAL_TIM_SET_COUNTER(timer, 0);
	__HAL_TIM_SET_AUTORELOAD(timer, autoReload);
	__HAL_TIM_SET_COMPARE(timer, TIM_CHANNEL_1,   (autoReload / 2));

//	__HAL_TIM_SET_COUNTER(&htim6, 0);
//	__HAL_TIM_SET_AUTORELOAD(&htim6, autoReloadTim6);

}
