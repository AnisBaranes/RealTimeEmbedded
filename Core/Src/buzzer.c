#include <stdio.h>
#include "buzzer.h"
#include "main.h"
#include "button.h"


void BuzzerInit(BUZZER* buzzer, int* autoReload, int autoReloadLen)
{
	buzzer->autoReload = autoReload;
	buzzer->autoReloadLen =  autoReloadLen;
}

void StartBuzzer(TIM_HandleTypeDef *timer)
{
	HAL_TIM_Base_Start(timer);
	HAL_TIM_PWM_Start(timer, TIM_CHANNEL_1);
}

void StopBuzzer(TIM_HandleTypeDef *timer)
{
	HAL_TIM_PWM_Stop(timer, TIM_CHANNEL_1);
}

void music(TIM_HandleTypeDef *timer, int autoReload)
{
	__HAL_TIM_SET_COUNTER(timer, 0);
	__HAL_TIM_SET_AUTORELOAD(timer, autoReload);
	__HAL_TIM_SET_COMPARE(timer, TIM_CHANNEL_1,   (autoReload / 2));

//	__HAL_TIM_SET_COUNTER(&htim6, 0);
//	__HAL_TIM_SET_AUTORELOAD(&htim6, autoReloadTim6);

}
