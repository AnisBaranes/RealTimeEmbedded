#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

typedef enum {
	noPress,
	shortPress,
	longPress,
	doublePress
}ButtonState;

typedef struct _button{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	ButtonState buttonState;
	int counterDoublePress;
}BUTTON;


void ButtonInit(BUTTON* btn, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void setButtonState(BUTTON* btn);
int ButtonOnTimerInterrupt(BUTTON* btn);

#endif
