/*
 * shell.c
 *
 *  Created on: 2021. 12. 25.
 *      Author: akkdong
 */


#include "main.h"
#include "shell.h"
#include "serial.h"
#include "beep.h"
#include "lwshell/lwshell.h"

#include <stdio.h>
#include <string.h>


static int32_t cmdproc_beep(int32_t argc, char** argv);
static int32_t cmdproc_power(int32_t argc, char** argv);
static int32_t cmdproc_echo(int32_t argc, char** argv);

static void shell_output(const char* str, struct lwshell* lw);



//
//
//

void shell_init()
{
	lwshell_init();
	lwshell_set_output_fn(shell_output);

	lwshell_register_cmd("beep", cmdproc_beep, "beep [{frequency} | mute]");
	lwshell_register_cmd("power", cmdproc_power, "power [reset | sleep]");
	lwshell_register_cmd("echo", cmdproc_echo, "echo {message}");
}


void shell_process()
{
	while (serial_available())
	{
		int ch = serial_read();
		lwshell_input(&ch, 1);
	}
}



//
//
//

static int _is_number(const char* str)
{
	const char* ptr = str;
	while (*ptr)
	{
		if (*ptr <'0' || *ptr > '9')
			return 0;

		ptr++;
	}

	return 1;
}

static int32_t cmdproc_beep(int32_t argc, char** argv)
{
	if (argc == 2 && strcmp(argv[1], "mute") == 0)
	{
		beep_mute();
		serial_printf("[BEEP] mute!!!\r\n");
	}
	else if (argc == 2 && _is_number(argv[1]))
	{
		int freq = atoi(argv[1]);
		beep_setFreq(freq);
		serial_printf("[BEEP] set frequency %d\r\n", freq);
	}
	else
	{
		serial_println("Invalid parameter: beep [{frequency} | mute]");
	}

	return 0;
}

static int32_t cmdproc_power(int32_t argc, char** argv)
{
    if (argc == 2 && strcmp(argv[1], "reset") == 0)
    {
    	serial_println("reset!!");
    }
    else if (argc == 2 && strcmp(argv[1], "sleep") == 0)
    {
    	serial_println("enter standby mode!!");

    	// signal
    	HAL_HSEM_FastTake(HSEM_ID_1);
    	//HAL_HSEM_Release(HSEM_ID_1, 0);

    	// wait Core2 standby
    	serial_println("wait Core2 standby");
    	int wait = 10;
    	while(__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) && wait > 0)
    	{
    		HAL_Delay(100);
    		--wait;
    	}
    	serial_printf("wait: %d\r\n", wait);
    	HAL_Delay(1000);
    	for (int i = 0; i < 10; i++)
    	{
    		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    		HAL_Delay(200);
    	}
    	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

    	// enter standby mode
    	HAL_PWREx_EnterSTANDBYMode(PWR_D1_DOMAIN);
    }
	else
	{
		serial_println("Invalid parameter: power [reset | sleep]");
	}

	return 0;
}

static int32_t cmdproc_echo(int32_t argc, char** argv)
{
	if (argc > 1)
	{
		serial_print(">> ");
		for (int32_t i = 1; i < argc; ++i)
			serial_printf(" %s", (int)i, argv[i]);
		serial_println("");
    }

	return 0;
}


static void shell_output(const char* str, struct lwshell* lw)
{
	serial_print(str);
}
