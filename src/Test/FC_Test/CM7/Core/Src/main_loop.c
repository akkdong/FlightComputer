// main_loop.c
//

#define USE_QSPIDRV (1)

#include <string.h>
#include "uart_drv.h"
#if USE_QSPIDRV
#include "qspi_drv.h"
#else
#include "quadspi.h"
#endif
#include "epd_drv.h"
#include "sdram.h"
#include "fatfs.h"
#include "main.h"

#if 1
#include "sample_image.h"
#else
#include "eagle.h"
#endif
#include "image_mono.h"
#include "landscape.h"


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

uint8_t*	imagePtr1;
uint8_t*	imagePtr2;
uint8_t*	imagePtrActive;


void test_sdram(void);
void test_nor(void);
void test_dump(void);
void test_fatfs(const char* cmd);
void test_erase_subsector(uint32_t addr);
void test_write_subsector(uint32_t addr);
void test_read_subsector(uint32_t addr);


int __io_putchar(int ch)
{
	//ITM_SendChar(ch);
	uint8_t data = (uint8_t)ch;
	UART_Write(&UART1, data);
	return(ch);
}

int _write(int file, char *ptr, int len)
{
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar( *ptr++ );
	}
	return len;
}


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
		else if (strcmp(param1, "nor") == 0)
		{
			test_nor();
		}
		else if (strcmp(param1, "dump") == 0)
		{
			test_dump();
		}
		else if (strcmp(param1, "dir") == 0)
		{
			test_fatfs(param2);
		}
		else if (strcmp(param1, "erase") == 0)
		{
			test_erase_subsector(parseNumber(param2));
		}
		else if (strcmp(param1, "write") == 0)
		{
			test_write_subsector(parseNumber(param2));
		}
		else if (strcmp(param1, "read") == 0)
		{
			test_read_subsector(parseNumber(param2));
		}
	}
	else if (strcmp(cmd, "epd") == 0)
	{
		if (strcmp(param1, "clear") == 0)
		{
			EPD_ClearScreen();
			//epd_clearScreen();
			UART_Printf(&UART1, "clear done!\n");
		}
		else if (strcmp(param1, "clear2") == 0)
		{
			epd_clearScreen();
			//epd_clearScreen();
			UART_Printf(&UART1, "clear done!\n");
		}
		else if (strcmp(param1, "draw") == 0)
		{
			EPD_Draw16Gray(img_bytes);
			UART_Printf(&UART1, "draw-16bit done!\n");
		}
		else if (strcmp(param1, "mono") == 0)
		{
			EPD_DrawMono(imagePtrActive);
			UART_Printf(&UART1, "draw active image done!\n");
		}
		else if (strcmp(param1, "mono1") == 0)
		{
			EPD_DrawMono(imagePtr1);
			imagePtrActive = imagePtr1;
			UART_Printf(&UART1, "draw image1 done!\n");
		}
		else if (strcmp(param1, "mono2") == 0)
		{
			EPD_DrawMono(imagePtr2);
			imagePtrActive = imagePtr2;
			UART_Printf(&UART1, "draw image2 done!\n");
		}
		else if (strcmp(param1, "partial") == 0)
		{
			uint8_t* imageAlt = imagePtrActive == imagePtr1 ? imagePtr2 : imagePtr1;
			EPD_DrawPartial(imageAlt, imagePtrActive);
			imagePtrActive = imageAlt;
			UART_Printf(&UART1, "draw partial done!\n");
		}
		else
		{
			int ok = 1;

			if (strcmp(param1, "ckv") == 0)
			{
				if (strcmp(param2, "on") == 0)
					EPD_Set_CKV();
				else if (strcmp(param2, "off") == 0)
					EPD_Reset_CKV();
				else
					ok = 0;
			}
			else if (strcmp(param1, "sph") == 0)
			{
				if (strcmp(param2, "on") == 0)
					EPD_Set_SPH();
				else if (strcmp(param2, "off") == 0)
					EPD_Reset_SPH();
				else
					ok = 0;
			}
			else if (strcmp(param1, "spv") == 0)
			{
				if (strcmp(param2, "on") == 0)
					EPD_Set_SPV();
				else if (strcmp(param2, "off") == 0)
					EPD_Reset_SPV();
				else
					ok = 0;
			}
			else if (strcmp(param1, "le") == 0)
			{
				if (strcmp(param2, "on") == 0)
					EPD_Set_LE();
				else if (strcmp(param2, "off") == 0)
					EPD_Reset_LE();
				else
					ok = 0;
			}
			else if (strcmp(param1, "cl") == 0)
			{
				if (strcmp(param2, "on") == 0)
					EPD_Set_CL();
				else if (strcmp(param2, "off") == 0)
					EPD_Reset_CL();
				else
					ok = 0;
			}
			else if (strcmp(param1, "oe") == 0)
			{
				if (strcmp(param2, "on") == 0)
					EPD_Set_OE();
				else if (strcmp(param2, "off") == 0)
					EPD_Reset_OE();
				else
					ok = 0;
			}
			else if (strcmp(param1, "gmode") == 0)
			{
				if (strcmp(param2, "on") == 0)
					EPD_Set_GMODE();
				else if (strcmp(param2, "off") == 0)
					EPD_Reset_GMODE();
				else
					ok = 0;
			}
			else if (strcmp(param1, "data") == 0)
			{
				int data = parseNumber(param2);
				EPD_Set_DATA(data);
			}
			else
			{
				ok = 0;
			}

			if (!ok)
				UART_Printf(&UART1, "Invalid command or parameter: %s, %s\n", param1 ? param1 : "(nil)", param2 ? param2 : "(nil)");
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
#if USE_QSPIDRV
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
		UART_Printf(&UART1, "QSPI Driver initialize failed!!\n");
	}

	//if (QSPI_EnableMemoryMappedMode() != QSPI_STATUS_OK)
	//{
	//	UART_Printf(&UART1, "Memory mapped mode EANBLE FAILED!\n");
	//}
#else
	CSP_QUADSPI_Init();

	//CSP_QSPI_EnableMemoryMappedMode();
#endif

	// EPD
	EPD_Init();
	//epd_init();


	// initialize SDRAM
	SDRAM_Do_InitializeSequence(&hsdram1);

	//
	MX_FATFS_Init();


	//
	imagePtr1 = (uint8_t *)(SDRAM_BANK_ADDR + 800 / 8 * 600 * 1);
	imagePtr2 = (uint8_t *)(SDRAM_BANK_ADDR + 800 / 8 * 600 * 2);
	imagePtrActive = imagePtr1;

	memcpy(imagePtr1, alien_bytes, 800 / 8 * 600);
	memcpy(imagePtr2, landscape_bytes, 800 / 8 * 600);
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


#define SECTORS_COUNT 10
#ifndef QSPI_SUBSECTOR_SIZE
#define QSPI_SUBSECTOR_SIZE MEMORY_SECTOR_SIZE
#endif

uint8_t buffer_test[QSPI_SUBSECTOR_SIZE];
char* prefix[SECTORS_COUNT] =
{
	 "A variometer is", // 0
	 "also known as 1", // 1
	 "rate of climb 2", // 2
	 "descent indicat", // 3
	 "rate of climb 3", // 4
	 "vertical veloci", // 5
	 "one of the flig", // 6
	 "some instrument", // 7
	 "inform to pilot", // 8
	 "descent o climb" // 9
};

void test_nor(void)
{
	uint32_t var = 0x55;

#if USE_QSPIDRV
	for (var = 0; var < QSPI_SUBSECTOR_SIZE; var++)
	{
		buffer_test[var] = (var & 0xff);
	}

	for (var = 0; var < SECTORS_COUNT; var++)
	{
		if (QSPI_Driver_erase(var * QSPI_SUBSECTOR_SIZE, QSPI_SUBSECTOR_SIZE) != QSPI_STATUS_OK)
		{
			UART_Printf(&UART1, "EraseSector(%X) FAILED!\n", var);
			return;
		}

		memcpy(&buffer_test[0], prefix[var], strlen(prefix[var]));

		if (QSPI_Driver_write(buffer_test, var * QSPI_SUBSECTOR_SIZE, sizeof(buffer_test)) != QSPI_STATUS_OK)
		{
			UART_Printf(&UART1, "WriteMemory(%X) FAILED!\n", var);
			return;
		}
	}

	/*
	if (QSPI_EnableMemoryMappedMode() != QSPI_STATUS_OK)
	{
		UART_Printf(&UART1, "Memory mapped mode EANBLE FAILED!\n");
		return;
	}
	*/

	for (var = 0; var < SECTORS_COUNT; var++)
	{
		memcpy(&buffer_test[0], prefix[var], strlen(prefix[var]));

		if (memcmp(buffer_test, (uint8_t*) (QSPI_BANK_ADDR + var * QSPI_SUBSECTOR_SIZE), QSPI_SUBSECTOR_SIZE) != HAL_OK)
		{
			UART_Printf(&UART1, "MemoryTest(%X) FAILED!\n", var);
			return;
		}
	}
#else
    for (var = 0; var < MEMORY_SECTOR_SIZE; var++)
    {
        buffer_test[var] = (var & 0xFF);
    }
    for (var = 0; var < SECTORS_COUNT; var++)
    {
        if (CSP_QSPI_EraseSector(var * MEMORY_SECTOR_SIZE, (var + 1) * MEMORY_SECTOR_SIZE - 1) != HAL_OK)
        {
        	UART_Printf(&UART1, "EraseSector(%X) FAILED!\n", var);
        	return;
        }
        if (CSP_QSPI_WriteMemory(buffer_test, var * MEMORY_SECTOR_SIZE, sizeof(buffer_test)) != HAL_OK)
        {
        	UART_Printf(&UART1, "WriteMemory(%X) FAILED!\n", var);
        	return;
        }
    }
    if (CSP_QSPI_EnableMemoryMappedMode() != HAL_OK)
    {
    	UART_Printf(&UART1, "Memory mapped mode EANBLE FAILED!\n");
    	return;
    }
    for (var = 0; var < SECTORS_COUNT; var++)
    {
        if (memcmp(buffer_test, (uint8_t*) (0x90000000 + var * MEMORY_SECTOR_SIZE), MEMORY_SECTOR_SIZE) != HAL_OK)
        {
        	UART_Printf(&UART1, "MemoryTest(%X) FAILED!\n", var);
        	return;
        }
    }
#endif
}

void test_dump(void)
{
	//
#if USE_QSPIDRV
	//
	QSPI_Driver_read(buffer_test, 0x0000000, 32);
	for (int i = 0; i< 32; i++)
	{
		UART_Printf(&UART1, "%02X ", buffer_test[i]);
		if ((i % 16) == 15)
		{
			UART_Write(&UART1,'\n');
			HAL_Delay(10);
		}
	}
	UART_Write(&UART1,'\n');

	QSPI_Driver_read(buffer_test, 0x00001F0, 32);
	for (int i = 0; i< 32; i++)
	{
		UART_Printf(&UART1, "%02X ", buffer_test[i]);
		if ((i % 16) == 15)
		{
			UART_Write(&UART1,'\n');
			HAL_Delay(10);
		}
	}
	UART_Write(&UART1,'\n');

	//
	QSPI_Driver_read(buffer_test, 0x0000800, 32);
	for (int i = 0; i< 32; i++)
	{
		UART_Printf(&UART1, "%02X ", buffer_test[i]);
		if ((i % 16) == 15)
		{
			UART_Write(&UART1,'\n');
			HAL_Delay(10);
		}
	}
	UART_Write(&UART1,'\n');

#else
	if (CSP_QSPI_ReadMemory(buffer_test, 0x0000000, 0x200) == HAL_OK)
	{
		for (int i = 0; i < 0x200; i++)
		{
			UART_Printf(&UART1, "%02X ", buffer_test[i]);
			if ((i % 16) == 15)
			{
				UART_Write(&UART1, '\n');
				HAL_Delay(10);
			}
		}

		UART_Write(&UART1, '\n');
	}
	else
	{
		UART_Printf(&UART1, "Bulk read FAILED!\n");
		HAL_Delay(10);
	}

    if (CSP_QSPI_EnableMemoryMappedMode() != HAL_OK)
    {
    	UART_Printf(&UART1, "Enable memory-mapped mode FAILED!\n");
    	return;
    }

	for (uint32_t var = 0; var < SECTORS_COUNT; var++)
	{
		uint32_t* nor = (uint32_t*)(0x90000000 + var * QSPI_SUBSECTOR_SIZE);
		UART_Printf(&UART1, "[%X]\n", (uint32_t)nor);
		HAL_Delay(10);

		for (int i = 0; i < 4; i++)
		{
			uint32_t data = *nor++;

			uint8_t* ptr = (uint8_t *)&data;
			uint8_t d1 = ptr[0];
			uint8_t d2 = ptr[1];
			uint8_t d3 = ptr[2];
			uint8_t d4 = ptr[3];
			UART_Printf(&UART1, "%02X %02X %02X %02X ", d1, d2, d3, d4);
			HAL_Delay(10);
		}

		UART_Printf(&UART1, "\n");
	}
#endif
}

DIR dir;
FILINFO finfo;

void test_fatfs(const char* cmd)
{
	if (f_mount(&QSPIDISKFatFS, (const TCHAR *)QSPIDISKPath, 0) == FR_OK)
	{
		if (f_opendir(&dir, cmd) == FR_OK) /* ex: "2:/" */
		{
			UART_Printf(&UART1, "DIR /\n");
			while (1)
			{
				if (f_readdir(&dir, &finfo) != FR_OK || !finfo.fname[0])
					break;

				UART_Printf(&UART1, "%s\n", finfo.fname);
			}
			f_closedir(&dir);
		}
	}
}

void test_erase_subsector(uint32_t addr)
{
	UART_Printf(&UART1, "Erase: %08X\n", addr);

	addr = addr & 0x7FFFFFFF;
	if (QSPI_Driver_erase_subsector(addr) == QSPI_STATUS_OK)
		UART_Printf(&UART1, "    OK\n");
	else
		UART_Printf(&UART1, "    FAILED\n");
}

void test_write_subsector(uint32_t addr)
{
	UART_Printf(&UART1, "Write: %08X\n", addr);

	addr = addr & 0x7FFFFFFF;
	if (QSPI_Driver_write(&buffer_test[0], addr, 64) == QSPI_STATUS_OK)
		UART_Printf(&UART1, "    OK\n");
	else
		UART_Printf(&UART1, "    FAILED\n");
}

void test_read_subsector(uint32_t addr)
{
	UART_Printf(&UART1, "Read: %08X\n", addr);

	addr = addr & 0x7FFFFFFF;
	if (QSPI_Driver_read(&buffer_test[0], addr, 64) == QSPI_STATUS_OK)
	{
		for (int i = 0; i< 64; i++)
		{
			UART_Printf(&UART1, "%02X ", buffer_test[i]);
			if ((i % 16) == 15)
			{
				UART_Write(&UART1,'\n');
				HAL_Delay(10);
			}
		}
	}
	else
		UART_Printf(&UART1, "    FAILED\n");
}
