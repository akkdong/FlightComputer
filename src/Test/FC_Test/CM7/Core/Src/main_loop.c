// main_loop.c
//

#include <string.h>
#include "UART.h"
#include "qspi_drv.h"
#include "sdram.h"
#include "fatfs.h"
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

#define MASK_PERIPH			0x01
#define MASK_PMIC			0x02
#define MASK_WAKEUP			0x04
#define MASK_PWRUP			0x08
#define MASK_VCOM			0x10
#define MASK_REGISTER		0x80

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


void test_sdram(void);
void test_fatfs(const char* cmd);


void cmd_tokenize(char* str, char** tok1, char** tok2, char** tok3, char** tok4)
{
	*tok1 = strtok(str, " ");
	*tok2 = strtok(NULL, " ");
	*tok3 = strtok(NULL, " ");
	*tok4 = strtok(NULL, " ");
}


void makeLower(char *str)
{
	if (!str)
		return;

	char *ptr = str;
	while(*ptr)
	{
		if ('A' <= *ptr && *ptr <= 'Z')
			*ptr = (*ptr - 'A') + 'a';
		ptr++;
	}
}

int toNumber(char ch, int base)
{
	if (base == 16)
	{
		if ('a' <= ch && ch <= 'f')
			return (ch - 'a') + 10;
	}

	if (ch < '0' || '9' < ch)
		return -1;

	int num = ch - '0';
	if (num >= base)
		return -1;

	return num;
}

int validateNumber(const char* str)
{
	if (!str)
		return 0; // INVALID

	int base = 10;
	const char* ptr = str;
	if (*ptr == '-')
		ptr++;

	if (strncmp(ptr, "0x", 2) == 0)
	{
		base = 16;
		ptr += 2;
	}
	else if (strncmp(ptr, "0b", 2) == 0)
	{
		base = 2;
		ptr += 2;
	}

	while (*ptr)
	{
		int value = toNumber(*ptr, base);
		if (value < 0)
			return 0; // INVALID

		ptr++;
	}

	return 1; // OK
}

int parseNumber(const char* str)
{
	if (!str)
		return 0;

	int sign = 1;
	int base = 10;
	const char* ptr = str;
	if (*ptr == '-')
	{
		sign = -1;
		ptr++;
	}

	if (strncmp(ptr, "0x", 2) == 0)
	{
		base = 16;
		ptr += 2;
	}
	else if (strncmp(ptr, "0b", 2) == 0)
	{
		base = 2;
		ptr += 2;
	}

	int num = 0;
	while (*ptr)
	{
		int value = toNumber(*ptr, base);
		if (value < 0)
			break;

		num = num * base + value;
		ptr++;
	}

	return num * sign;
}


// on [all, pmic, periph, 5v, wakeup, pwrup, vcom]
// off [all, pmic, periph, 5v, wakeup, pwrup, vcom]
// read reg{ister} [all, 0x00 ~ 0x10]
// read port [all, pmic, periph, 5v, wakeup, pwrup, vcom]
// write reg-no value
//

void cmd_process(char* str)
{
	char *cmd, *param1, *param2, *param3;
	cmd_tokenize(str, &cmd, &param1, &param2, &param3);
	makeLower(cmd);
	makeLower(param1);
	makeLower(param2);
	makeLower(param3);

	if (strcmp(cmd, "on") == 0)
	{
		uint8_t mask = 0x00;

		if (param1 == NULL || strcmp(param1, "all") == 0)
			mask = 0xFF;
		else if (strcmp(param1, "pmic") == 0)
			mask = MASK_PMIC;
		else if (strcmp(param1, "periph") == 0)
			mask = MASK_PERIPH;
		else if (strcmp(param1, "wakeup") == 0)
			mask = MASK_WAKEUP;
		else if (strcmp(param1, "pwrup") == 0)
			mask = MASK_PWRUP;
		else if (strcmp(param1, "vcom") == 0)
			mask = MASK_VCOM;

		if (mask & MASK_PMIC)
		{
			HAL_GPIO_WritePin(PWR_EN_BAT__GPIO_Port, PWR_EN_BAT__Pin, GPIO_PIN_SET);
			UART_Printf(&UART1, "Port(PMIC) -> %d\n", HAL_GPIO_ReadPin(PWR_EN_BAT__GPIO_Port, PWR_EN_BAT__Pin));
			HAL_Delay(20);
		}
		if (mask & MASK_PERIPH)
		{
			HAL_GPIO_WritePin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin, GPIO_PIN_SET);
			UART_Printf(&UART1, "Port(PERIPH) -> %d\n", HAL_GPIO_ReadPin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin));
			HAL_Delay(20);
		}
		if (mask & MASK_WAKEUP)
		{
			HAL_GPIO_WritePin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin, GPIO_PIN_SET);
			UART_Printf(&UART1, "Port(WAKEUP) -> %d\n", HAL_GPIO_ReadPin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin));
			HAL_Delay(20);
		}
		if (mask & MASK_PWRUP)
		{
			HAL_GPIO_WritePin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin, GPIO_PIN_SET);
			UART_Printf(&UART1, "Port(PWRUP) -> %d\n", HAL_GPIO_ReadPin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin));
			HAL_Delay(20);
		}
		if (mask & MASK_VCOM)
		{
			HAL_GPIO_WritePin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin, GPIO_PIN_SET);
			UART_Printf(&UART1, "Port(VCOM) -> %d\n", HAL_GPIO_ReadPin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin));
			HAL_Delay(20);
		}
		if (mask == 0x00)
			UART_Printf(&UART1, "Invalid Port name: %s\n", param1);
	}
	else if (strcmp(cmd, "off") == 0)
	{
		uint8_t mask = 0x00;

		if (param1 == NULL || strcmp(param1, "all") == 0)
			mask = 0xFF;
		else if (strcmp(param1, "pmic") == 0)
			mask = MASK_PMIC;
		else if (strcmp(param1, "periph") == 0)
			mask = MASK_PERIPH;
		else if (strcmp(param1, "wakeup") == 0)
			mask = MASK_WAKEUP;
		else if (strcmp(param1, "pwrup") == 0)
			mask = MASK_PWRUP;
		else if (strcmp(param1, "vcom") == 0)
			mask = MASK_VCOM;

		if (mask & MASK_PMIC)
		{
			HAL_GPIO_WritePin(PWR_EN_BAT__GPIO_Port, PWR_EN_BAT__Pin, GPIO_PIN_RESET);
			UART_Printf(&UART1, "Port(PMIC) -> %d\n", HAL_GPIO_ReadPin(PWR_EN_BAT__GPIO_Port, PWR_EN_BAT__Pin));
			HAL_Delay(20);
		}
		if (mask & MASK_PERIPH)
		{
			HAL_GPIO_WritePin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin, GPIO_PIN_RESET);
			UART_Printf(&UART1, "Port(PERIPH) -> %d\n", HAL_GPIO_ReadPin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin));
			HAL_Delay(20);
		}
		if (mask & MASK_WAKEUP)
		{
			HAL_GPIO_WritePin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin, GPIO_PIN_RESET);
			UART_Printf(&UART1, "Port(WAKEUP) -> %d\n", HAL_GPIO_ReadPin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin));
			HAL_Delay(20);
		}
		if (mask & MASK_PWRUP)
		{
			HAL_GPIO_WritePin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin, GPIO_PIN_RESET);
			UART_Printf(&UART1, "Port(PWRUP) -> %d\n", HAL_GPIO_ReadPin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin));
			HAL_Delay(20);
		}
		if (mask & MASK_VCOM)
		{
			HAL_GPIO_WritePin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin, GPIO_PIN_RESET);
			UART_Printf(&UART1, "Port(VCOM) -> %d\n", HAL_GPIO_ReadPin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin));
			HAL_Delay(20);
		}
		if (mask == 0x00)
			UART_Printf(&UART1, "Invalid Port name: %s\n", param1);
	}
	else if (strcmp(cmd, "read") == 0)
	{
		if (strcmp(param1, "port") == 0)
		{
			uint8_t mask = 0x00;

			if (param2 == NULL || strcmp(param2, "all") == 0)
				mask = 0xFF;
			else if (strcmp(param2, "pmic") == 0)
				mask = MASK_PMIC;
			else if (strcmp(param2, "periph") == 0)
				mask = MASK_PERIPH;
			else if (strcmp(param2, "wakeup") == 0)
				mask = MASK_WAKEUP;
			else if (strcmp(param2, "pwrup") == 0)
				mask = MASK_PWRUP;
			else if (strcmp(param2, "vcom") == 0)
				mask = MASK_VCOM;

			if (mask & MASK_PMIC)
			{
				UART_Printf(&UART1, "Port(PMIC) -> %d\n", HAL_GPIO_ReadPin(PWR_EN_BAT__GPIO_Port, PWR_EN_BAT__Pin));
				HAL_Delay(20);
			}
			if (mask & MASK_PERIPH)
			{
				UART_Printf(&UART1, "Port(PERIPH) -> %d\n", HAL_GPIO_ReadPin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin));
				HAL_Delay(20);
			}
			if (mask & MASK_WAKEUP)
			{
				UART_Printf(&UART1, "Port(WAKEUP) -> %d\n", HAL_GPIO_ReadPin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin));
				HAL_Delay(20);
			}
			if (mask & MASK_PWRUP)
			{
				UART_Printf(&UART1, "Port(PWRUP) -> %d\n", HAL_GPIO_ReadPin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin));
				HAL_Delay(20);
			}
			if (mask & MASK_VCOM)
			{
				UART_Printf(&UART1, "Port(VCOM) -> %d\n", HAL_GPIO_ReadPin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin));
				HAL_Delay(20);
			}
			if (mask == 0x00)
				UART_Printf(&UART1, "Invalid Port name: %s\n", param2);
		}
		else if (strncmp(param1, "reg", 3) == 0)
		{
			uint8_t reg = (uint8_t)-1;

			if (param2 == NULL || validateNumber(param2))
			{
				if (param2 == NULL)
				{
					reg = 0x80;
				}
				else
				{
					reg = parseNumber(param2);
					if (reg < REG_TMST_VALUE || REG_REVID < reg)
						reg = (uint8_t)-1;
				}
			}

			if (reg != (uint8_t)-1)
			{
				for (int i = 0; i <= 0x10; i++)
				{
					if (reg == 0x80 || reg == i)
					{
						uint8_t data = 0xFF;
						HAL_I2C_Mem_Read(&hi2c1, PMIC_ADDR, i, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
						UART_Printf(&UART1, "Reg(#%02X) -> %02X\n", i, data);
						HAL_Delay(20);
					}
				}
			}
			else
			{
				UART_Printf(&UART1, "Invalid Register number: %s\n", param2);
			}
		}
		else
		{
			UART_Printf(&UART1, "Invalid read parameter: %s\n", param1);
		}
	}
	else if (strcmp(cmd, "write") == 0)
	{
		uint8_t reg = (uint8_t)-1;
		uint8_t val = 0x00;

		if (validateNumber(param1) && validateNumber(param2))
		{
			reg = parseNumber(param1);
			val = parseNumber(param2);

			if (reg < REG_TMST_VALUE || REG_REVID < reg)
				reg = (uint8_t)-1;
		}

		if (reg != (uint8_t)-1)
		{
			HAL_I2C_Mem_Write(&hi2c1, PMIC_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &val, 1, 1000);
			UART_Printf(&UART1, "Reg(#%02X) <-- %02X\n", reg, val);

			uint8_t data;
			HAL_I2C_Mem_Read(&hi2c1, PMIC_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
			UART_Printf(&UART1, "Reg(#%02X) --> %02X\n", reg, val);
		}
		else
		{
			UART_Printf(&UART1, "Invalid Register number: %s, %s\n", param1 ? param1 : "(nil)", param2 ? param2 : "(nil)");
		}
	}
	else if (strcmp(cmd, "test") == 0)
	{
		if (strcmp(param1, "sdram") == 0)
		{
			test_sdram();
		}
		else if (strcmp(param1, "dir") == 0)
		{
			test_fatfs(param2);
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

	// initialize qspi nor
	if (QSPI_Driver_locked())
	{
		UART_Printf(&UART1, "QSPI Driver locked\n");
		return;
	}

	if(QSPI_Driver_state() == 1)
	{
		UART_Printf(&UART1, "QSPI Driver have been ready\n");
		return;
	}

	if(  QSPI_Driver_init() == QSPI_STATUS_OK)
	{
		UART_Printf(&UART1, "QSPI Driver initialized\n");
	}
	else
	{
		UART_Printf(&UART1, "QSPI Driver initialization failed!!\n");
	}

	// initialize SDRAM
	SDRAM_Do_InitializeSequence(&hsdram1);

	//
	MX_FATFS_Init();

	test_fatfs("/");
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




void test_sdram(void)
{
	volatile uint8_t* memPtr = (volatile uint8_t *)SDRAM_BANK_ADDR; // 0xD0000000
	UART_Printf(&UART1, "Test SDRAM ====\n");
	volatile uint8_t* tmpPtr = memPtr;
	uint32_t data = 0x55;
	{
		uint32_t tickStart = HAL_GetTick();
		for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
			*tmpPtr++ = data;
		UART_Printf(&UART1, "Clear All: elapsed %d msec\n", HAL_GetTick() - tickStart);
	}

	UART_Printf(&UART1, "Write Data ");
	tmpPtr = memPtr;
	data = 0x55;
	for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
	{
		if ((i % (1024 * 1024)) == 0)
			UART_Printf(&UART1, ".");
		*tmpPtr++ = data++;
	}

	UART_Printf(&UART1, "\nCompare Data ");
	tmpPtr = memPtr;
	data = 0x55;
	uint8_t memOk = 1;
	for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
	{
		if ((i % (1024 * 1024)) == 0)
			UART_Printf(&UART1, ".");

		uint8_t a = *tmpPtr;
		uint8_t b = data;
		if (a != b)
		{
			UART_Printf(&UART1, "\nMemory corrupt at %08X: %02X, %02X\n", (unsigned int)i, a, b);
			memOk = 0;
			break;
		}
		tmpPtr++;
		data++;
	}
	if (memOk)
		UART_Printf(&UART1, "\nMemory compare passed!!\n");
}

DIR dir;
FILINFO finfo;

void test_fatfs(const char* cmd)
{
	if (f_mount(&USERFatFS, (const TCHAR *)USERPath, 0) == FR_OK)
	{
		if (f_opendir(&dir, "/") == FR_OK)
		{
			UART_Printf(&UART1, "DIR /\n");
			while (1)
			{
				if (f_readdir(&dir, &finfo) != FR_OK)
					break;

				UART_Printf(&UART1, "%s\n", finfo.fname);
			}
			f_closedir(&dir);
		}
	}
}

