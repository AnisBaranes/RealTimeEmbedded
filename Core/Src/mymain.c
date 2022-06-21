#include <stdio.h>
#include "string.h"
#include "stdint.h"
#include "stdlib.h"
#include "mymain.h"
#include "main.h"
#include "clock.h"
#include "led.h"


extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;

#define MAX_BUFFER_LENGTH 100

uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int cmdcount = 0;
int cmdprint = 0;
CLOCK clock;

void mainloop()
{
	startTimer(&htim6, &clock);

	while (1)
	{
		if (commTask())
		{
			handleCommand();
		}
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
		tick(&clock);
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
	  printFullTime(&clock);
  }
  else
  {
	  printf("Invalid command\r\n");
  }
}


