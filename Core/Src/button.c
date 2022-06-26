#include <stdio.h>
#include "main.h"
#include "button.h"
#include "clock.h"

extern TIM_HandleTypeDef htim6;
extern uint32_t prevTick;

void ButtonInit(BUTTON* btn, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	btn->GPIO_Pin = GPIO_Pin;
	btn->GPIOx = GPIOx;
}


ButtonState getButtonState(BUTTON* btn)
{
	GPIO_PinState resPin = HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin);
	if(resPin == GPIO_PIN_RESET)
	{
		if(HAL_GetTick() - prevTick < 500)
		{
			return shortPress; //printf("Short press\n\r");
		}
		else
		{
			return longPress; //printf("Long press\n\r");
		}
	}
	else
	{
		prevTick = HAL_GetTick();
	}
	return noPress;
}


