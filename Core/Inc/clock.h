#ifndef __CLOCK_H
#define __CLOCK_H

#include <stdio.h>
#include "mymain.h"
#include "main.h"

typedef struct _clock
{
	int timCounterms;
	int hours, minuts, seconds;
}CLOCK;

void startTimer(TIM_HandleTypeDef *timer, CLOCK* clock);
CLOCK* getFullTime(CLOCK* clock);
void tick(CLOCK* clock);

#endif
