#include "clock.h"
#include "mymain.h"
#include "main.h"


extern TIM_HandleTypeDef htim6;

uint16_t timer_val;


void startTimer(TIM_HandleTypeDef *timer, CLOCK* clock)
{
	clock-> timCounterms = 0;
	HAL_NVIC_EnableIRQ(TIM6_IRQn);
	HAL_TIM_Base_Start_IT(timer);
}

void tick(CLOCK* clock)
{
	clock-> timCounterms++;
}

void printFullTime(CLOCK* clock)
{
	int hours, minuts, seconds;

	hours = clock -> timCounterms/3600;
	minuts = (clock -> timCounterms - hours*3600)/60;
    seconds = clock -> timCounterms - hours*3600 - minuts*60;

	printf("%d seconds = %d hours : %d minutes : %d seconds\n\r", clock -> timCounterms, hours, minuts, seconds);
}




