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
	btn->counterDoublePress = 0;
}


void setButtonState(BUTTON* btn)
{
	GPIO_PinState resPin = HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin);
	if(resPin == GPIO_PIN_RESET)
	{
		if(btn->buttonState == shortPress && btn->counterDoublePress < 500) //if last press was short press and there is another press less than 500 ms
		{
			btn->buttonState = doublePress;
		}
		else if(HAL_GetTick() - prevTick < 500)
		{
			btn->buttonState = shortPress;
		}
		else
		{
			btn->buttonState = longPress;
		}
	}
	else
	{
		prevTick = HAL_GetTick();
	}
}


int ButtonOnTimerInterrupt(BUTTON* btn)
{
	if(btn->counterDoublePress == 500)
	{
		btn->counterDoublePress = 0;
	}
	else
	{
		btn->counterDoublePress ++;
	}
	return btn->counterDoublePress;
}
