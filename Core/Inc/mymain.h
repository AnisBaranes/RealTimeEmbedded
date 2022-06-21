#ifndef __MYMAIN_H
#define __MYMAIN_H

#include "main.h"
#include "clock.h"

void mainloop();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim);
int _write(int fd, char* ptr, int len);
int commTask();
void handleCommand();

#endif

