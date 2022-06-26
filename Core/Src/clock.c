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

CLOCK* getFullTime(CLOCK* clock)
{
	//int hours, minuts, seconds;

	clock-> hours = clock -> timCounterms/3600;
	clock-> minuts = (clock -> timCounterms - clock->hours*3600)/60;
    clock-> seconds = clock -> timCounterms - clock->hours*3600 - clock->minuts*60;

    return clock;
	//printf("%d seconds = %d hours : %d minutes : %d seconds\n\r", clock -> timCounterms, hours, minuts, seconds);
}




