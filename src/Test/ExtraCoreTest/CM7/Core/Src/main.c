/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "is42s32800g.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* MT25TL01GHBA8ESF Micron memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE                      25
#define QSPI_PAGE_SIZE                       256

/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

/* Identification Operations */
#define READ_ID_CMD                          0x9E
#define READ_ID_CMD2                         0x9F
#define MULTIPLE_IO_READ_ID_CMD              0xAF
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5A

/* Read Operations */
#define READ_CMD                             0x03
#define READ_4_BYTE_ADDR_CMD                 0x13

#define FAST_READ_CMD                        0x0B
#define FAST_READ_DTR_CMD                    0x0D
#define FAST_READ_4_BYTE_ADDR_CMD            0x0C

#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_OUT_FAST_READ_DTR_CMD           0x3D
#define DUAL_OUT_FAST_READ_4_BYTE_ADDR_CMD   0x3C

#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define DUAL_INOUT_FAST_READ_DTR_CMD         0xBD
#define DUAL_INOUT_FAST_READ_4_BYTE_ADDR_CMD 0xBC

#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_OUT_FAST_READ_DTR_CMD           0x6D
#define QUAD_OUT_FAST_READ_4_BYTE_ADDR_CMD   0x6C

#define QUAD_INOUT_FAST_READ_CMD             0xEB
#define QUAD_INOUT_FAST_READ_DTR_CMD         0xED
#define QUAD_INOUT_FAST_READ_4_BYTE_ADDR_CMD 0xEC

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define WRITE_STATUS_REG_CMD                 0x01

#define READ_LOCK_REG_CMD                    0xE8
#define WRITE_LOCK_REG_CMD                   0xE5

#define READ_FLAG_STATUS_REG_CMD             0x70
#define CLEAR_FLAG_STATUS_REG_CMD            0x50

#define READ_NONVOL_CFG_REG_CMD              0xB5
#define WRITE_NONVOL_CFG_REG_CMD             0xB1

#define READ_VOL_CFG_REG_CMD                 0x85
#define WRITE_VOL_CFG_REG_CMD                0x81

#define READ_ENHANCED_VOL_CFG_REG_CMD        0x65
#define WRITE_ENHANCED_VOL_CFG_REG_CMD       0x61

#define READ_EXT_ADDR_REG_CMD                0xC8
#define WRITE_EXT_ADDR_REG_CMD               0xC5

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define PAGE_PROG_4_BYTE_ADDR_CMD            0x12

#define DUAL_IN_FAST_PROG_CMD                0xA2
#define EXT_DUAL_IN_FAST_PROG_CMD            0xD2

#define QUAD_IN_FAST_PROG_CMD                0x32
#define EXT_QUAD_IN_FAST_PROG_CMD            0x12 /*0x38*/
#define QUAD_IN_FAST_PROG_4_BYTE_ADDR_CMD    0x34

/* Erase Operations */
#define SUBSECTOR_ERASE_CMD                  0x20
#define SUBSECTOR_ERASE_4_BYTE_ADDR_CMD      0x21

#define SECTOR_ERASE_CMD                     0xD8
#define SECTOR_ERASE_4_BYTE_ADDR_CMD         0xDC

#define BULK_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

/* One-Time Programmable Operations */
#define READ_OTP_ARRAY_CMD                   0x4B
#define PROG_OTP_ARRAY_CMD                   0x42

/* 4-byte Address Mode Operations */
#define ENTER_4_BYTE_ADDR_MODE_CMD           0xB7
#define EXIT_4_BYTE_ADDR_MODE_CMD            0xE9

/* Quad Operations */
#define ENTER_QUAD_CMD                       0x35
#define EXIT_QUAD_CMD                        0xF5

/* Default dummy clocks cycles */
#define DUMMY_CLOCK_CYCLES_READ              8
#define DUMMY_CLOCK_CYCLES_READ_QUAD         8

#define DUMMY_CLOCK_CYCLES_READ_DTR          6
#define DUMMY_CLOCK_CYCLES_READ_QUAD_DTR     8

/* End address of the QSPI memory */
#define QSPI_END_ADDR              			(1 << QSPI_FLASH_SIZE)

/* Size of buffers */
#define BUFFERSIZE                 			(COUNTOF(aTxBuffer) - 1)

#define COUNTOF(__BUFFER__)        			(sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))




#define SDRAM_ADDRESS   					((uint32_t) 0xD0000000)

#define SDRAM_BANK_ADDR                 		 ((uint32_t)0xD0000000)

#define SDRAM_MEMORY_WIDTH            			 FMC_SDRAM_MEM_BUS_WIDTH_16
#define SDCLOCK_PERIOD                			 FMC_SDRAM_CLOCK_PERIOD_3

#define SDRAM_TIMEOUT     						 ((uint32_t)0xFFFF)

#define BUFFER_SIZE         					 ((uint32_t)0x0100)
#define WRITE_READ_ADDR     					 ((uint32_t)0x0800)
//#define REFRESH_COUNT      				 	 ((uint32_t)0x056A)   /* SDRAM refresh counter (90MHz SDRAM clock) */
#define REFRESH_COUNT 							 ((uint32_t)0x0603)/* SDRAM refresh counter (100Mhz SD clock) */

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)



#define SDRAM_DEVICE_ADDR         		0xD0000000U

#define NOR_DEVICE_ADDR  				0x60000000U
#define NOR_DEVICE_SIZE  				0x4000000U

#define BLOCKERASE_TIMEOUT   			0x00A00000U  /* NOR block erase timeout */
#define CHIPERASE_TIMEOUT    			0x30000000U  /* NOR chip erase timeout  */
#define PROGRAM_TIMEOUT      			0x00004400U  /* NOR program timeout     */

#define NOR_READY_BUSY_PIN    GPIO_PIN_6
#define NOR_READY_BUSY_GPIO   GPIOC
#define NOR_READY_STATE       GPIO_PIN_SET
#define NOR_BUSY_STATE        GPIO_PIN_RESET

/* Common Error codes */
#define BSP_ERROR_NONE                    0
#define BSP_ERROR_NO_INIT                -1
#define BSP_ERROR_WRONG_PARAM            -2
#define BSP_ERROR_BUSY                   -3
#define BSP_ERROR_PERIPH_FAILURE         -4
#define BSP_ERROR_COMPONENT_FAILURE      -5
#define BSP_ERROR_UNKNOWN_FAILURE        -6
#define BSP_ERROR_UNKNOWN_COMPONENT      -7
#define BSP_ERROR_BUS_FAILURE            -8
#define BSP_ERROR_CLOCK_FAILURE          -9
#define BSP_ERROR_MSP_FAILURE            -10
#define BSP_ERROR_FEATURE_NOT_SUPPORTED  -11

/* BSP OSPI error codes */
#define BSP_ERROR_QSPI_ASSIGN_FAILURE     -24
#define BSP_ERROR_QSPI_SETUP_FAILURE      -25
#define BSP_ERROR_QSPI_MMP_LOCK_FAILURE   -26
#define BSP_ERROR_QSPI_MMP_UNLOCK_FAILURE -27

/* BSP TS error code */
#define BSP_ERROR_TS_TOUCH_NOT_DETECTED   -30

/* BSP BUS error codes */
#define BSP_ERROR_BUS_TRANSACTION_FAILURE    -100
#define BSP_ERROR_BUS_ARBITRATION_LOSS       -101
#define BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE    -102
#define BSP_ERROR_BUS_PROTOCOL_FAILURE       -103

#define BSP_ERROR_BUS_MODE_FAULT             -104
#define BSP_ERROR_BUS_FRAME_ERROR            -105
#define BSP_ERROR_BUS_CRC_ERROR              -106
#define BSP_ERROR_BUS_DMA_FAILURE            -107




#define ENABLE_QSPI_TEST				(0)
#define ENABLE_SDRAM_TEST				(0)
#define ENABLE_NOR_TEST					(0)


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef hlpuart1;

LTDC_HandleTypeDef hltdc;

QSPI_HandleTypeDef hqspi;

NOR_HandleTypeDef hnor1;
SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */
#if ENABLE_QSPI_TEST
__IO uint8_t CmdCplt, RxCplt, TxCplt, StatusMatch, TimeOut;
/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT**** ";

/* Buffer used for reception */
uint8_t aRxBuffer[BUFFERSIZE];
#endif

#if ENABLE_SDRAM_TEST
uint32_t aTable[1024];

__IO uint32_t uwTabAddr;
__IO uint32_t MSPValue = 0;
#endif


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FMC_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_LTDC_Init(void);
/* USER CODE BEGIN PFP */

#if ENABLE_QSPI_TEST
static void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi);
static void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi);
static void QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi);
#endif

static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLength, uint16_t uwOffset);

static HAL_StatusTypeDef SDRAM_Do_InitializeSequence();
static void MPU_Config(void);


int32_t BSP_NOR_EraseBlock(uint32_t Instance, uint32_t BlockAddress);
int32_t BSP_NOR_ReadData(uint32_t Instance, uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize);
int32_t BSP_NOR_WriteData(uint32_t Instance, uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize);

static void NOR_MspWait(NOR_HandleTypeDef *hnor, uint32_t Timeout);
static int32_t NOR_GetStatus(uint32_t Instance, uint32_t Address, uint32_t Timeout, uint32_t ProgramTimeout);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch)
{
	HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ch, 1, 100);
	return 1;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
#if ENABLE_QSPI_TEST
	  QSPI_CommandTypeDef sCommand;
	  uint32_t address = 0;
	  uint16_t index;
	  __IO uint8_t step = 0;
#endif

#if ENABLE_NOR_TEST || 1
  MPU_Config();
#endif

  /* USER CODE END 1 */
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
  int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /* Wait until CPU2 boots and enters in stop mode or timeout*/
  timeout = 0xFFFF;
  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
  if ( timeout < 0 )
  {
  Error_Handler();
  }
/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
/* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
HSEM notification */
/*HW semaphore Clock enable*/
__HAL_RCC_HSEM_CLK_ENABLE();
/*Take HSEM */
HAL_HSEM_FastTake(HSEM_ID_0);
/*Release HSEM in order to notify the CPU2(CM4)*/
HAL_HSEM_Release(HSEM_ID_0,0);
/* wait until CPU2 wakes up from stop mode */
timeout = 0xFFFF;
while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
if ( timeout < 0 )
{
Error_Handler();
}
/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
#if ENABLE_SDRAM_TEST || ENABLE_NOR_TEST
  MX_FMC_Init();
#endif
#if ENABLE_QUADSPI_TEST
  MX_QUADSPI_Init();
#endif
  MX_LPUART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
#if ENABLE_QSPI_TEST
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
#endif


  // Initialize SDRAM
  // ...


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint32_t count = 0;
  while (count++ < 20)
  {
	  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	  HAL_Delay(100);
  }
  // turn-off
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

  printf("STM32H745 CoreBoard Test....\r\n");

#if ENABLE_SDRAM_TEST

	// initialize SDRAM
  	HAL_Delay(1000);
  	{
  	  int32_t ret;
  	  static IS42S32800G_Context_t pRegMode;

      /* External memory mode register configuration */
      pRegMode.TargetBank      = FMC_SDRAM_CMD_TARGET_BANK2;
      pRegMode.RefreshMode     = IS42S32800G_AUTOREFRESH_MODE_CMD;
      pRegMode.RefreshRate     = REFRESH_COUNT;
      pRegMode.BurstLength     = IS42S32800G_BURST_LENGTH_1;
      pRegMode.BurstType       = IS42S32800G_BURST_TYPE_SEQUENTIAL;
      pRegMode.CASLatency      = IS42S32800G_CAS_LATENCY_3;
      pRegMode.OperationMode   = IS42S32800G_OPERATING_MODE_STANDARD;
      pRegMode.WriteBurstMode  = IS42S32800G_WRITEBURST_MODE_SINGLE;

      /* SDRAM initialization sequence */
      if(IS42S32800G_Init(&hsdram1, &pRegMode) != IS42S32800G_OK)
      {
    	  printf("SDRAM initialize failed!!\r\n");
      }
      else
      {
  		printf("SDRAM initialized\r\n");

  		volatile uint32_t* ptr = (volatile uint32_t *)0xD0000000;
  		Fill_Buffer((uint32_t *)ptr, 1024, 0);

  	    uint32_t data1 = *((volatile uint32_t *)0xD0000010);
  	    uint32_t data2 = *((volatile uint32_t *)0xD0000014);
  	    uint8_t b1 = *((volatile uint8_t *)0xD0000018);
  	    uint8_t b2 = *((volatile uint8_t *)0xD0000019);
  	    uint8_t b3 = *((volatile uint8_t *)0xD000001A);
  	    uint8_t b4 = *((volatile uint8_t *)0xD000001B);
  	    printf("%lu, %lu, %u, %u, %u, %u\r\n", data1, data2, b1, b2, b3, b4);

  		const char* str = (const char *)"SDRAM Test!!";
  		volatile char* dst = (volatile char *)0xD0001000;
  		while(*str)
  			*dst++ = *str++;
  		*dst = '\0';

  		volatile char* src = (volatile char *)0xD0001000;
  		for (int i = 0; i < 10; i++)
  			printf("%X ", src[i]);
  		printf("\r\n");

  		printf("%s\r\n", src);
      }

  	}

#if 0
	if (SDRAM_Do_InitializeSequence() == HAL_OK)
	{
		printf("SDRAM initialized\r\n");

		volatile uint32_t* ptr = (volatile uint32_t *)0xD0000000;
		Fill_Buffer((uint32_t *)ptr, 1024, 0);

		const char* str = (const char *)"SDRAM Test!!";
		volatile char* dst = (volatile char *)0xD0001000;
		while(*str)
			*dst++ = *str++;

		volatile char* src = (volatile char *)0xD0001000;
		for (int i = 0; i < 10; i++)
			printf("%X ", *src++);
		printf("\r\n");
	}
	else
	{
		printf("SDRAM initialize failed!!\r\n");
	}
#endif


#if 0
  /*##-1- Fill the buffer in the SDRAM device ##########################################*/
  Fill_Buffer(aTable, 1024, 0);

  /*##-2- Read address of the buffer and stack pointer address ########################*/
  uwTabAddr = (uint32_t)aTable; /* should be above 0xD0000000 */

  /* Get main stack pointer value */
  MSPValue = __get_MSP(); /* should be above 0xD0000000 */

  /*##-3- Activate LEDs pending on read values ########################################*/
  if ((uwTabAddr >= SDRAM_ADDRESS) && (MSPValue >= SDRAM_ADDRESS))
  {
    printf("SDRAM Test: PASSED!!\r\n");
  }
  else
  {
	  printf("SDRAM Test: FAILED!!\r\n");
  }
  printf("   uwTabAddr = 0X%x\r\n", uwTabAddr);
  printf("   MSPValue = 0X%x\r\n", MSPValue);
#endif

#endif

#ifdef DATA_IN_ExtSDRAM
  {
	  char buf[4];
	  uint32_t uwTabAddr = (uint32_t)buf; /* should be above 0xD0000000 */
	  uint32_t MSPValue = __get_MSP(); /* should be above 0xD0000000 */

	  printf("uwTabAddr = %x\r\n", (unsigned int)uwTabAddr);
	  printf("MSPValue = %x\r\n", (unsigned int)MSPValue);
  }
#endif


#if ENABLE_NOR_TEST
  {
	  NOR_IDTypeDef pNOR_ID;

	    if(HAL_NOR_Read_ID(&hnor1, &pNOR_ID) != HAL_OK)
	    {
	    	printf("NOR Test FAILED!!!\r\n");
	    }
	    else
	    {
	    	printf("NOR Test.....\r\n");
	    	printf("  Manufacturer_Code: %04X\r\n", pNOR_ID.Manufacturer_Code);
	    	printf("  Device_Code1: %04X\r\n", pNOR_ID.Device_Code1);
	    	printf("  Device_Code2: %04X\r\n", pNOR_ID.Device_Code2);
	    	printf("  Device_Code3: %04X\r\n", pNOR_ID.Device_Code3);


#define NOR_BUFFER_SIZE     	((uint32_t)0x0100)
#define NOR_WRITE_READ_ADDR     ((uint32_t)0x0800)

	    	volatile uint16_t* nor_aRxBuffer = (volatile uint16_t *)0xD0000100;
	    	volatile uint16_t* nor_aTxBuffer = (volatile uint16_t *)0xD0000800;

	    	  /*##-3- Erase NOR memory ###################################################*/
	    	  /* Return to read mode */
	    	  if(HAL_NOR_ReturnToReadMode(&hnor1) != HAL_OK)
	    	  {
	    		  printf("NOR Test: Failed HAL_NOR_ReturnToReadMode\r\n");
	    		  Error_Handler();
	    	  }

	    	  if(BSP_NOR_EraseBlock(0, NOR_WRITE_READ_ADDR) != BSP_ERROR_NONE)
	    	  {
	    		  printf("NOR Test: Failed BSP_NOR_EraseBlock\r\n");
	    		  Error_Handler();
	    	  }

	    	  /* Read back data from the NOR memory */
	    	  if(BSP_NOR_ReadData(0, NOR_WRITE_READ_ADDR, (uint16_t *)nor_aRxBuffer, NOR_BUFFER_SIZE) != BSP_ERROR_NONE)
	    	  {
	    		  printf("NOR Test: Failed BSP_NOR_ReadData #1\r\n");
	    		  Error_Handler();
	    	  }
	    	  /*##-4- NOR memory read/write access  ######################################*/
	    	  /* Fill the buffer to write */
	    	  //Fill_Buffer((uint16_t *)nor_aTxBuffer, NOR_BUFFER_SIZE, 0xD20F);
	    	  {
	    	    uint32_t tmpIndex = 0;

	    	    /* Put in global buffer different values */
	    	    for (tmpIndex = 0; tmpIndex < NOR_BUFFER_SIZE; tmpIndex++ )
	    	    {
	    	    	nor_aTxBuffer[tmpIndex] = tmpIndex + 0xD20F;
	    	    }
	    	  }

	    	  /* Write data to the NOR memory */
	    	  if(BSP_NOR_WriteData(0, NOR_WRITE_READ_ADDR, (uint16_t *)nor_aTxBuffer, NOR_BUFFER_SIZE) != BSP_ERROR_NONE)
	    	  {
	    		  printf("NOR Test: Failed BSP_NOR_WriteData\r\n");
	    		  Error_Handler();
	    	  }

	    	  /* Read back data from the NOR memory */
	    	  if(BSP_NOR_ReadData(0, NOR_WRITE_READ_ADDR, (uint16_t *)nor_aRxBuffer, NOR_BUFFER_SIZE) != BSP_ERROR_NONE)
	    	  {
	    		  printf("NOR Test: Failed BSP_NOR_ReadData #2\r\n");
	    		  Error_Handler();
	    	  }
	    	  else
	    	  {
	    		  int mismatch = -1;
	    		  for (int i = 0; i < NOR_BUFFER_SIZE; i++)
	    		  {
	    			  printf("compare: %04X, %04X\r\n", nor_aTxBuffer[i], nor_aRxBuffer[i]);

	    			  if (nor_aTxBuffer[i] != nor_aRxBuffer[i])
	    			  {
	    				  mismatch = i;
	    			  }

	    			  if (i > 50)
	    				  break;
	    		  }

    			  if (mismatch >= 0)
    			  {
    				  printf("NOR Test: memory compare failed at %d\r\n", mismatch);
    				  Error_Handler();
    			  }


	    		  printf("NOR Test: SUCCESS!!\r\n");
	    	  }
	    }
  }

#endif



  while (1)
  {
#if ENABLE_QSPI_TEST && 0
	switch(step)
	{
	  case 0:
		printf("Start QSPI Flash Test....\r\n");
		CmdCplt = 0;

		/* Initialize Reception buffer --------------------------------------- */
		for (index = 0; index < BUFFERSIZE; index++)
		{
		  aRxBuffer[index] = 0;
		}

		/* Enable write operations ------------------------------------------- */
		QSPI_WriteEnable(&hqspi);

		/* Erasing Sequence -------------------------------------------------- */
		sCommand.Instruction = SECTOR_ERASE_CMD;
		sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
		sCommand.Address     = address;
		sCommand.DataMode    = QSPI_DATA_NONE;
		sCommand.DummyCycles = 0;

		if (HAL_QSPI_Command_IT(&hqspi, &sCommand) != HAL_OK)
		{
		  Error_Handler();
		}

		step++;
		printf("Pass Step #%d\r\n", step);
		break;

	  case 1:
		if(CmdCplt != 0)
		{
		  CmdCplt = 0;
		  StatusMatch = 0;

		  /* Configure automatic polling mode to wait for end of erase ------- */
		  QSPI_AutoPollingMemReady(&hqspi);

		  step++;
		  printf("Pass Step #%d\r\n", step);
		}
		break;

	  case 2:
		if(StatusMatch != 0)
		{
		  StatusMatch = 0;
		  TxCplt = 0;

		  /* Enable write operations ----------------------------------------- */
		  QSPI_WriteEnable(&hqspi);

		  /* Writing Sequence ------------------------------------------------ */
		  sCommand.Instruction = QUAD_IN_FAST_PROG_CMD;
		  sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
		  sCommand.DataMode    = QSPI_DATA_4_LINES;
		  sCommand.NbData      = BUFFERSIZE;

		  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		  {
			Error_Handler();
		  }

		  if (HAL_QSPI_Transmit_IT(&hqspi, aTxBuffer) != HAL_OK)
		  {
			Error_Handler();
		  }

		  step++;
		  printf("Pass Step #%d\r\n", step);
		}
		break;

	  case 3:
		if(TxCplt != 0)
		{
		  TxCplt = 0;
		  StatusMatch = 0;

		  /* Configure automatic polling mode to wait for end of program ----- */
		  QSPI_AutoPollingMemReady(&hqspi);

		  step++;
		  printf("Pass Step #%d\r\n", step);
		}
		break;

	  case 4:
		if(StatusMatch != 0)
		{
		  StatusMatch = 0;
		  RxCplt = 0;

		  /* Configure Volatile Configuration register (with new dummy cycles) */
		  QSPI_DummyCyclesCfg(&hqspi);

		  /* Reading Sequence ------------------------------------------------ */
		  sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
		  sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_READ_QUAD;

		  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		  {
			printf("FAILED on Step #%d: FAST_READ_CMD\r\n", step);
			Error_Handler();
		  }

		  if (HAL_QSPI_Receive_IT(&hqspi, aRxBuffer) != HAL_OK)
		  {
			printf("FAILED on Step #%d: Receive_IT\r\n", step);
			Error_Handler();
		  }
		  step++;
		}
		break;

	  case 5:
		if (RxCplt != 0)
		{
		  RxCplt = 0;

		  /* Result comparison ----------------------------------------------- */
		  for (index = 0; index < BUFFERSIZE; index++)
		  {
			if (aRxBuffer[index] != aTxBuffer[index])
			{
				printf("FAILED on Step #%d: Mismatch reading data\r\n", step);
				  while (1)
				  {
					  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
					  HAL_Delay(100);
				  }
			}
		  }

		  address += QSPI_PAGE_SIZE;
		  if(address >= QSPI_END_ADDR)
		  {
			address = 0;
		  }
		  printf("Finished QSPI Flash Test: SUCCESS!!\r\n");
		  step = 0;
		  while (1)
		  {
			  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			  HAL_Delay(400);
		  }
		}
		break;

	  default :
		Error_Handler();
	}
#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_Delay(200);
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_Delay(800);

	printf("Hello world!\r\n");
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /*
  Note : The activation of the I/O Compensation Cell is recommended with communication  interfaces
  (GPIO, SPI, FMC, QSPI ...)  when  operating at  high frequencies(please refer to product datasheet)
  The I/O Compensation Cell activation  procedure requires :
  - The activation of the CSI clock
  - The activation of the SYSCFG clock
  - Enabling the I/O Compensation Cell : setting bit[0] of register SYSCFG_CCCSR
  */

  /*activate CSI clock mondatory for I/O Compensation Cell*/
  __HAL_RCC_CSI_ENABLE() ;

  /* Enable SYSCFG clock mondatory for I/O Compensation Cell */
  __HAL_RCC_SYSCFG_CLK_ENABLE() ;

  /* Enables the I/O Compensation Cell */
  HAL_EnableCompensationCell();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FMC|RCC_PERIPHCLK_QSPI;
  PeriphClkInitStruct.PLL2.PLL2M = 5;
  PeriphClkInitStruct.PLL2.PLL2N = 160;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 8;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_PLL2;
  PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x009034B6;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 7;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 14;
  hltdc.Init.AccumulatedVBP = 5;
  hltdc.Init.AccumulatedActiveW = 814;
  hltdc.Init.AccumulatedActiveH = 485;
  hltdc.Init.TotalWidth = 820;
  hltdc.Init.TotalHeigh = 487;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 799;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 479;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
  pLayerCfg.Alpha = 0;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xD0000000;
  pLayerCfg.ImageWidth = 800;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 255;
  pLayerCfg.Backcolor.Green = 255;
  pLayerCfg.Backcolor.Red = 255;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  /* QUADSPI parameter configuration*/
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 4;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 25;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

/* FMC initialization function */
void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_NORSRAM_TimingTypeDef Timing = {0};
  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the NOR1 memory initialization sequence
  */
  hnor1.Instance = FMC_NORSRAM_DEVICE;
  hnor1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  /* hnor1.Init */
  hnor1.Init.NSBank = FMC_NORSRAM_BANK1;
  hnor1.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
  hnor1.Init.MemoryType = FMC_MEMORY_TYPE_NOR;
  hnor1.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
  hnor1.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
  hnor1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hnor1.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
  hnor1.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
  hnor1.Init.WaitSignal = FMC_WAIT_SIGNAL_ENABLE; // FMC_WAIT_SIGNAL_DISABLE;
  hnor1.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
  hnor1.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_ENABLE;
  hnor1.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
  hnor1.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hnor1.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
  hnor1.Init.PageSize = FMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime = 9;
  Timing.AddressHoldTime = 1; // 15;
  Timing.DataSetupTime = 5;
  Timing.BusTurnAroundDuration = 4;
  Timing.CLKDivision = 4; //16;
  Timing.DataLatency = 2; //17;
  Timing.AccessMode = FMC_ACCESS_MODE_B; // FMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_NOR_Init(&hnor1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 4;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */

  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TOUCH_INT_Pin */
  GPIO_InitStruct.Pin = TOUCH_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TOUCH_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_BL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_BL_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

#if ENABLE_QSPI_TEST

/**
  * @brief  Command completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_CmdCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  CmdCplt++;
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  RxCplt++;
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  TxCplt++;
}

/**
  * @brief  Status Match callbacks
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
  StatusMatch++;
}


/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  /* Enable write operations ------------------------------------------ */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = WRITE_ENABLE_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_NONE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure automatic polling mode to wait for write enabling ---- */
  sConfig.Match           = 0x02;
  sConfig.Mask            = 0x02;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  sCommand.Instruction    = READ_STATUS_REG_CMD;
  sCommand.DataMode       = QSPI_DATA_1_LINE;

  if (HAL_QSPI_AutoPolling(hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function read the SR of the memory and wait the EOP.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  /* Configure automatic polling mode to wait for memory ready ------ */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = READ_STATUS_REG_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_1_LINE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  sConfig.Match           = 0x00;
  sConfig.Mask            = 0x01;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling_IT(hqspi, &sCommand, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function configure the dummy cycles on memory side.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef sCommand;
  uint8_t reg;

  /* Read Volatile Configuration register --------------------------- */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = READ_VOL_CFG_REG_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_1_LINE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.NbData            = 1;

  if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_QSPI_Receive(hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  /* Enable write operations ---------------------------------------- */
  QSPI_WriteEnable(hqspi);

  /* Write Volatile Configuration register (with new dummy cycles) -- */
  sCommand.Instruction = WRITE_VOL_CFG_REG_CMD;
  MODIFY_REG(reg, 0xF0, (DUMMY_CLOCK_CYCLES_READ_QUAD << POSITION_VAL(0xF0)));

  if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_QSPI_Transmit(hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
}

#endif

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the buffer to fill
  * @param  uwBufferLenght: size of the buffer to fill
  * @param  uwOffset: first value to fill on the buffer
  * @retval None
  */
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLength, uint16_t uwOffset)
{
  uint16_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLength; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}


/**
  * @brief  Perform the SDRAM exernal memory inialization sequence
  * @param  hsdram: SDRAM handle
  * @param  &command: Pointer to SDRAM command structure
  * @retval None
  */
static HAL_StatusTypeDef SDRAM_Do_InitializeSequence()
{
  FMC_SDRAM_CommandTypeDef command;
  HAL_StatusTypeDef result;
  __IO uint32_t tmpmrd =0;

  /* Step 3:  Configure a clock configuration enable command */
  command.CommandMode 			 = FMC_SDRAM_CMD_CLK_ENABLE;
  command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 1;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  result = HAL_SDRAM_SendCommand(&hsdram1, &command, 0x1000);
  if (result != HAL_OK)
	  return result;

  /* Step 4: Insert 100 ms delay */
  HAL_Delay(100);

  /* Step 5: Configure a PALL (precharge all) command */
  command.CommandMode 			 = FMC_SDRAM_CMD_PALL;
  command.CommandTarget 	     = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 1;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  result = HAL_SDRAM_SendCommand(&hsdram1, &command, 0x1000);
  if (result != HAL_OK)
	  return result;

  /* Step 6 : Configure a Auto-Refresh command */
  command.CommandMode 			 = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 4;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  result = HAL_SDRAM_SendCommand(&hsdram1, &command, 0x1000);
  if (result != HAL_OK)
	  return result;

  /* Step 7: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 1;
  command.ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  result = HAL_SDRAM_SendCommand(&hsdram1, &command, 0x1000);
  if (result != HAL_OK)
	  return result;

  /* Step 8: Set the refresh rate counter */
  /* (15.62 us x Freq) - 20 */
  /* Set the device refresh counter */
  result = HAL_SDRAM_ProgramRefreshRate(&hsdram1, REFRESH_COUNT);
  if (result != HAL_OK)
	  return result;

  return HAL_OK;
}

static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SDRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = SDRAM_DEVICE_ADDR;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Configure the MPU attributes as WT for NOR */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = NOR_DEVICE_ADDR;
  MPU_InitStruct.Size = MPU_REGION_SIZE_16MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}


/**
  * @brief  Erases the specified block of the NOR device.
  * @param  Instance  NOR Instance
  * @param  BlockAddress  Block address to erase
  * @retval BSP status
  */
int32_t BSP_NOR_EraseBlock(uint32_t Instance, uint32_t BlockAddress)
{
  int32_t ret = BSP_ERROR_NONE;

  /* Send NOR erase block operation */
  if(HAL_NOR_Erase_Block(&hnor1, BlockAddress, NOR_DEVICE_ADDR) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    if(NOR_GetStatus(Instance, NOR_DEVICE_ADDR, PROGRAM_TIMEOUT, BLOCKERASE_TIMEOUT) != BSP_ERROR_NONE)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  Reads an amount of data from the NOR device.
  * @param  Instance  NOR Instance
  * @param  uwStartAddress  Read start address
  * @param  pData  Pointer to data to be read
  * @param  uwDataSize  Size of data to read
  * @retval BSP status
  */
int32_t BSP_NOR_ReadData(uint32_t Instance, uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize)
{
  int32_t ret;

  if(HAL_NOR_ReadBuffer(&hnor1, NOR_DEVICE_ADDR + uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Writes an amount of data to the NOR device.
  * @param  Instance  NOR Instance
  * @param  uwStartAddress  Write start address
  * @param  pData  Pointer to data to be written
  * @param  uwDataSize  Size of data to write
  * @retval BSP status
  */
int32_t BSP_NOR_WriteData(uint32_t Instance, uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize)
{
  int32_t ret = BSP_ERROR_NONE;
  uint32_t index = uwDataSize;
  uint32_t write_addr;
  uint16_t* write_data;

	write_data = pData;
	write_addr = uwStartAddress;
	while((index > 0UL) && (ret == BSP_ERROR_NONE))
	{
	  /* Write data to NOR */
	  if(HAL_NOR_Program(&hnor1, (uint32_t *)(NOR_DEVICE_ADDR + write_addr), write_data) != HAL_OK)
	  {
		ret = BSP_ERROR_PERIPH_FAILURE;
	  }
	  else if(NOR_GetStatus(Instance, NOR_DEVICE_ADDR, PROGRAM_TIMEOUT, PROGRAM_TIMEOUT) != BSP_ERROR_NONE)
	  {
		ret = BSP_ERROR_PERIPH_FAILURE;
	  }
	  else
	  {
		/* Update the counters */
		index--;
		write_addr += 2UL;
		write_data++;
	  }
	}

  return ret;
}


/**
  * @brief  NOR BSP Wait for Ready/Busy signal.
  * @param  hnor     Pointer to NOR handle
  * @param  Timeout  Timeout duration
  * @retval None
  */
static void NOR_MspWait(NOR_HandleTypeDef *hnor, uint32_t Timeout)
{
  uint32_t timeout = Timeout;
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hnor);

  /* Polling on Ready/Busy signal */
  while((HAL_GPIO_ReadPin(NOR_READY_BUSY_GPIO, NOR_READY_BUSY_PIN) != NOR_BUSY_STATE) && (timeout > 0U))
  {
    timeout--;
  }

  timeout = Timeout;

  /* Polling on Ready/Busy signal */
  while((HAL_GPIO_ReadPin(NOR_READY_BUSY_GPIO, NOR_READY_BUSY_PIN) != NOR_READY_STATE) && (timeout > 0U))
  {
    timeout--;
  }
}

/**
  * @brief  Returns the NOR operation status.
  * @param  Instance  NOR Instance
  * @param  Address Device address
  * @param  Timeout NOR Timeout for Ready/Busy signal
  * @param  ProgramTimeout NOR programming Timeout
  * @retval BSP status
  */
static int32_t NOR_GetStatus(uint32_t Instance, uint32_t Address, uint32_t Timeout, uint32_t ProgramTimeout)
{
  int32_t ret = BSP_ERROR_NONE;


    /* NOR BSP Wait for Ready/Busy signal */
    NOR_MspWait(&hnor1, Timeout);

    /* Return the NOR memory status */
    if(HAL_NOR_GetStatus(&hnor1, Address, ProgramTimeout) != HAL_NOR_STATUS_SUCCESS)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }

  return ret;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
