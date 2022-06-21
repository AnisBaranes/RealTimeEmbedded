#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

typedef struct _button{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}BUTTON;


void ButtonInit(BUTTON* btn, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void PressBtn(BUTTON* btn);

#endif
