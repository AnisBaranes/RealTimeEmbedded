#ifndef __MYMAIN_H
#define __MYMAIN_H

#include "main.h"
#include "clock.h"
#include "button.h"
#include "led.h"
#include "buzzer.h"

void mainloop();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim);
int _write(int fd, char* ptr, int len);
int commTask();
void handleCommand();
void ledsInit();
void buttonsInit();
void OnButtonClickTurnOnLed(BUTTON* btn, LED* led);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void pressBuzzer(TIM_HandleTypeDef *timer, BUTTON* btn);
void checkPress(BUTTON* btn);
void togglePin(LED *led);

#endif

