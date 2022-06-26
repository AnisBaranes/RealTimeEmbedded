#include <stdio.h>
#include "string.h"
#include "stdint.h"
#include "stdlib.h"
#include "mymain.h"
#include "main.h"
#include "clock.h"
#include "led.h"
#include "button.h"
#include "buzzer.h"


extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;

#define MAX_BUFFER_LENGTH 100

uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int cmdcount = 0;
int cmdprint = 0;

int autoReload[] = {381, 361, 340, 321, 303, 289, 270, 255, 240, 227, 214, 202};
int autoReloadIndex = 0;
int autoReloadLen = sizeof(autoReload) / sizeof(autoReload[0]);
int _level = 0;

CLOCK clock;
LED ledRed;
LED ledBlue;
BUTTON d2;
BUTTON d3;

void mainloop()
{
	startTimer(&htim6, &clock);
	buttonsInit();
	ledsInit();

	//OnButtonClickTurnOnLed(&d2, &ledRed);

	StartPWM();

	while (1)
	{
		if (commTask())
		{
			handleCommand();
		}
	}
}


void ledsInit()
{
	LedInit(&ledRed, LD3_GPIO_Port, LD3_Pin);
	LedInit(&ledBlue, GPIOA, LD2_Pin);
}


void buttonsInit()
{
	ButtonInit(&d2, B2_GPIO_Port, B2_Pin);
	ButtonInit(&d3, B3_GPIO_Port, B3_Pin);
}

void OnButtonClickTurnOnLed(BUTTON* btn, LED* led)
{
	GPIO_PinState resPin = getButtonState(btn);
	if(resPin == GPIO_PIN_RESET)
	{
		LedOn(led);
	}
}


void pressBuzzer(TIM_HandleTypeDef *timer, BUTTON* btn)
{
	GPIO_PinState resPin = HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin);
	if(resPin == GPIO_PIN_RESET)
	{
		StartBuzzer(timer);
	}
	else
	{
		StopBuzzer(timer);
	}
}

int _write(int fd, char* ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6)
	{
//		tick(&clock);
//
//		music(&htim3, autoReload[autoReloadIndex]);
//		if(autoReloadIndex < autoReloadLen)
//		{
//			autoReloadIndex++;
//		}
//		else
//		{
//			autoReloadIndex = 0;
//		}
	}

	else if(htim == &htim2) //Brightness
	{
		LedOn(&ledBlue);
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//pressBuzzer(&htim3, &d2);

	//Brightness
	_level = (_level + 10) % 100;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, _level);
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2) //Brightness
	{
		LedOff(&ledBlue);
	}
}


int commTask()
{
	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK)
	{
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0)
		{
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (cmdprint < cmdcount)
		{
			HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch != '\r' && ch != '\n')
	{
		//HAL_UART_Transmit(&huart2, &ch, 1, 0xFFFF);

		if (cmdcount >= MAX_BUFFER_LENGTH)
		{
			cmdcount = 0;
			cmdprint = 0;
		}

		cmdbuffer[cmdcount++] = ch;
		return 0;
	}

	// here we have a time to print the command
	while (cmdprint < cmdcount)
	{
		HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	cmdprint = 0;
	return 1;
}

void handleCommand()
{
  char cmd[20];
  int maxCount;

  int params = sscanf((const char*)cmdbuffer, "%s %d", cmd, &maxCount);

  if (params == 0)
  {
	  return;
  }

  if (strcmp(cmd, "full") == 0)
  {
	  //turning_on_led();
  }
  else if (strcmp(cmd, "half") == 0)
  {
	  //half_brightness();
  }
  else if(strcmp(cmd, "blink") == 0)
  {
	  //start_blink();
  }
  else if(strcmp(cmd, "off") == 0)
  {
	  //turning_off_led();
  }
  else if(strcmp(cmd, "time") == 0)
  {
	  getFullTime(&clock);
  }
  else
  {
	  printf("Invalid command\r\n");
  }
}


