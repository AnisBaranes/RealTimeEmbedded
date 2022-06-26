#ifndef __BUZZER_H
#define __BUZZER_H

#include "main.h"

typedef enum
{
	buzzerOn,
	buzzerOff
}BuzzerState ;

typedef struct _buzzer
{
	int* autoReload;
	int  autoReloadLen;
	BuzzerState buzzerState;
}BUZZER;

void BuzzerInit(BUZZER* buzzer, int* autoReload, int autoReloadLen);
void StartBuzzer(TIM_HandleTypeDef *timer);
void StopBuzzer(TIM_HandleTypeDef *timer);
void music(TIM_HandleTypeDef *timer, int autoReload);

#endif
