#ifndef __LED_H
#define __LED_H

#include "main.h"

typedef enum {
	LED_ON = 1,
	LED_OFF = 2,
	LED_BLINK = 3
}LED_STATE;

typedef struct _led{
	LED_STATE state;
	int counter;
	int peroid;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}LED;

void LedInit(LED* led, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void LedOn(LED* led);
void LedOff(LED* led);
void LedBlink(LED* led, int period);
void LedOnTimerInterrupt(LED* led);
void LedOnPeriodicTask(LED* led);

void StartPWM();
#endif
