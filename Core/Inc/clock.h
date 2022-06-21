#ifndef __CLOCK_H
#define __CLOCK_H

#include <stdio.h>
#include "mymain.h"
#include "main.h"

typedef struct _clock
{
	int timCounterms;
}CLOCK;

void startTimer(TIM_HandleTypeDef *timer, CLOCK* clock);
void printFullTime(CLOCK* clock);
void tick(CLOCK* clock);

#endif
