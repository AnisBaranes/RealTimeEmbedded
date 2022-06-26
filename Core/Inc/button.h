#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

typedef enum {
	noPress,
	shortPress,
	longPress,
}ButtonState;

typedef struct _button{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	ButtonState buttonState;
}BUTTON;


void ButtonInit(BUTTON* btn, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
ButtonState getButtonState(BUTTON* btn);

#endif
