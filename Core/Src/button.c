#include <stdio.h>
#include "button.h"
#include "main.h"

extern TIM_HandleTypeDef htim6;
extern uint32_t prevTick;


void ButtonInit(BUTTON* btn, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	btn->GPIO_Pin = GPIO_Pin;
	btn->GPIOx = GPIOx;
}


void PressBtn(BUTTON* btn)
{
	GPIO_PinState resPin = HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin);
	if(resPin == GPIO_PIN_RESET)
	{
		if(HAL_GetTick() - prevTick < 500)
		{
			printf("Short press\n\r");
		}
		else
		{
			printf("Long press\n\r");
		}
	}
	else
	{
		prevTick = HAL_GetTick();
	}
}
