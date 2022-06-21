#ifndef __BUZZER_H
#define __BUZZER_H

#include "main.h"
#include "button.h"

void StartBuzzer(TIM_HandleTypeDef *timer);
void StopBuzzer(TIM_HandleTypeDef *timer);
void pressBuzzer(TIM_HandleTypeDef *timer, BUTTON* btn);
void music(TIM_HandleTypeDef *timer, int autoReload, int autoReloadTim6);

#endif
