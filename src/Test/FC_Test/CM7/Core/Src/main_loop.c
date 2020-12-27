// main_loop.c
//

#include <string.h>
#include "UART.h"
#include "main.h"

#define PMIC_ADDR			(0x48 << 1)

#define REG_TMST_VALUE		0x00
#define REG_ENABLE			0x01
#define REG_VADJ			0x02
#define REG_VCOM1			0x03
#define REG_VCOM2			0x04
#define REG_INT_EN1			0x05
#define REG_INT_EN2			0x06
#define REG_INT1			0x07
#define REG_INT2			0x08
#define REG_UPSEQ0			0x09
#define REG_UPSEQ1			0x0A
#define REG_DWNSEQ0			0x0B
#define REG_DWNSEQ1			0x0C
#define REG_TMST1			0x0D
#define REG_TMST2			0x0E
#define REG_PG				0x0F
#define REG_REVID			0x10

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;


UARTDriver UART1;
UARTDriver UART2;
UARTDriver UART3;

char cmd_buf[64];
int  cmd_len = 0;


void cmd_tokenize(char* str, char** tok1, char** tok2, char** tok3, char** tok4)
{
	*tok1 = strtok(str, " ");
	*tok2 = strtok(NULL, " ");
	*tok3 = strtok(NULL, " ");
	*tok4 = strtok(NULL, " ");
}

void cmd_process(char* str)
{
	char *cmd, *param1, *param2, *param3;
	cmd_tokenize(str, &cmd, &param1, &param2, &param3);

	if (stricmp(cmd, "status") == 0)
	{
		uint8_t show = 0x03;
		if (param1 && stricmp(param1, "port") == 0)
		{
			show = 0x01;
		}
		else if (param1 && stricmp(param1, "pmic") == 0)
		{
			show = 0x02;
		}

		if (show & 0x01)
		{
			UART_Printf(&UART1, "BAT: %d\n", HAL_GPIO_ReadPin(PWR_EN_BAT__GPIO_Port, PWR_EN_BAT__Pin));
			HAL_Delay(10);
			UART_Printf(&UART1, "PERRIH: %d\n", HAL_GPIO_ReadPin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin));
			HAL_Delay(10);
			UART_Printf(&UART1, "5V: %d\n", HAL_GPIO_ReadPin(PWR_5V_EN_GPIO_Port, PWR_5V_EN_Pin));
			HAL_Delay(10);

			UART_Printf(&UART1, "WAKEUP: %d\n", HAL_GPIO_ReadPin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin));
			HAL_Delay(10);
			UART_Printf(&UART1, "PWRUP: %d\n", HAL_GPIO_ReadPin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin));
			HAL_Delay(10);
			UART_Printf(&UART1, "VOM: %d\n", HAL_GPIO_ReadPin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin));
			HAL_Delay(10);
		}

		if (show & 0x02)
		{
			// READ Registers
			uint8_t data[17];
			HAL_I2C_Mem_Read(&hi2c1, PMIC_ADDR, REG_TMST_VALUE, I2C_MEMADD_SIZE_8BIT, &data[0], 17, 1000);

			//
			UART_Printf(&UART1, "Dump PMIC register\n");
			for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
			{
				UART_Printf(&UART1, "  REG #%02X: %02X\n", i, data[i]);
				HAL_Delay(10);
			}

		}
	}
	else if (stricmp(cmd, "port") == 0)
	{
		if (param1 && param2 && param3)
		{
			if (stricmp(param1, "on") == 0)
			{
				if (stricmp(param2, "power") == 0)
				{
					if (stricmp(param3, "bat") == 0)
					{
						HAL_GPIO_WritePin(PWR_EN_BAT__GPIO_Port, PWR_EN_BAT__Pin, GPIO_PIN_SET);
						UART_Puts(&UART1, "Turn on BAT\n");
					}
					else if (stricmp(param3, "periph") == 0)
					{
						HAL_GPIO_WritePin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin, GPIO_PIN_SET);
						UART_Puts(&UART1, "Turn on PERIPH\n");
					}
					else if (stricmp(param3, "5v") == 0)
					{
						HAL_GPIO_WritePin(PWR_5V_EN_GPIO_Port, PWR_5V_EN_Pin, GPIO_PIN_SET);
						UART_Puts(&UART1, "Turn on 5V\n");
					}
				}
				else if (stricmp(param2, "pmic") == 0)
				{
					if (stricmp(param3, "wakeup") == 0)
					{
						HAL_GPIO_WritePin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin, GPIO_PIN_SET);
						UART_Puts(&UART1, "Turn on PMIC WAKEUP\n");
					}
					else if (stricmp(param3, "pwrup") == 0)
					{
						HAL_GPIO_WritePin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin, GPIO_PIN_SET);
						UART_Puts(&UART1, "Turn on PMIC PWRUP\n");
					}
					else if (stricmp(param3, "vcom") == 0)
					{
						HAL_GPIO_WritePin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin, GPIO_PIN_SET);
						UART_Puts(&UART1, "Turn on PMIC VCOM\n");
					}
				}
			}
			else if (stricmp(param1, "off") == 0)
			{
				if (stricmp(param2, "power") == 0)
				{
					if (stricmp(param3, "bat") == 0)
					{
						HAL_GPIO_WritePin(PWR_EN_BAT__GPIO_Port, PWR_EN_BAT__Pin, GPIO_PIN_RESET);
						UART_Puts(&UART1, "Turn off BAT\n");
					}
					else if (stricmp(param3, "periph") == 0)
					{
						HAL_GPIO_WritePin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin, GPIO_PIN_RESET);
						UART_Puts(&UART1, "Turn off PERIPH\n");
					}
					else if (stricmp(param3, "5v") == 0)
					{
						HAL_GPIO_WritePin(PWR_5V_EN_GPIO_Port, PWR_5V_EN_Pin, GPIO_PIN_RESET);
						UART_Puts(&UART1, "Turn off 5V\n");
					}
				}
				else if (stricmp(param2, "pmic") == 0)
				{
					if (stricmp(param3, "wakeup") == 0)
					{
						HAL_GPIO_WritePin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin, GPIO_PIN_RESET);
						UART_Puts(&UART1, "Turn off PMIC WAKEUP\n");
					}
					else if (stricmp(param3, "pwrup") == 0)
					{
						HAL_GPIO_WritePin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin, GPIO_PIN_RESET);
						UART_Puts(&UART1, "Turn off PMIC POWERUP\n");
					}
					else if (stricmp(param3, "vcom") == 0)
					{
						HAL_GPIO_WritePin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin, GPIO_PIN_RESET);
						UART_Puts(&UART1, "Turn off PMIC VCOM\n");
					}
				}
			}
		}
	}

}

void main_loop_begin(void)
{
	UART_Begin(&UART1, UART_Driver1, &huart1);
#if FORWARD_GPS
	UART_Begin(&UART2, UART_Driver2, &huart2);
#endif

	UART_Printf(&UART1, "Start flight computer test...\n");

	cmd_buf[0] = '\0';
	cmd_len = 0;
}


void main_loop(void)
{
	while (UART_Available(&UART1))
	{
		int ch = UART_Read(&UART1);
		if (ch == '\r' || ch == '\n')
		{
			if (cmd_len > 0)
			{
				UART_Printf(&UART1, "CMD: %s\n", cmd_buf);
				cmd_process(cmd_buf);
			}

			cmd_len = 0;
			cmd_buf[0] = '\0';
		}
		else if (cmd_len < sizeof(cmd_buf) / sizeof(cmd_buf[0]) - 1)
		{
			cmd_buf[cmd_len] = ch;
			cmd_len += 1;
			cmd_buf[cmd_len] = '\0';
		}
	}

#if FORWARD_GPS
	while (UART_Available(&UART2))
	{
		int ch = UART_Read(&UART2);
		UART_Write(&UART1, ch);
	}
#endif
}

void main_loop_end(void)
{
	UART_End(&UART1);
}
