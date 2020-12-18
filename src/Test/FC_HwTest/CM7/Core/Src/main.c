/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "TPS65186.h"
#include "MPU9250.h"
#include "bmp280_port.h"
#include "qspi_drv.h"

#include "usb_host.h"
#include "hid_host.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define HSEM_ID_0 (0U) /* HW semaphore 0*/

#define SDRAM_BANK_ADDR                 ((uint32_t)0xD0000000)

#define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_16
#define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3

#define SDRAM_TIMEOUT     	((uint32_t)0xFFFF)

#define BUFFER_SIZE         ((uint32_t)0x0100)
#define WRITE_READ_ADDR     ((uint32_t)0x0800)
//#define REFRESH_COUNT       ((uint32_t)0x056A)   /* SDRAM refresh counter (90MHz SDRAM clock) */
#define REFRESH_COUNT ((uint32_t)0x0603)/* SDRAM refresh counter (100Mhz SD clock) */

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

#define TEST_SLEEP		0
#define TEST_SDRAM 		0
#define TEST_QSPI 		0
#define TEST_PMIC 		0
#define TEST_MPU9250 	0
#define TEST_BMP280 	0
#define TEST_MPU9250_I2C 	0
#define TEST_BMP280_I2C 	0
#define TEST_GPS		0
#define TEST_MSC		0
#define TEST_USB_HOST	1
#define TEST_USB_DEVICE 0
#define TEST_SPISLAVE	0
#define TEST_UART3		0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc3;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

QSPI_HandleTypeDef hqspi;
MDMA_HandleTypeDef hmdma_quadspi_fifo_th;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi4;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */
FMC_SDRAM_CommandTypeDef command;

__IO uint8_t CmdCplt, RxCplt, TxCplt, StatusMatch;
uint8_t aTxBuffer[] = " ****Memory-mapped QSPI communication****  ****Memory-mapped QSPI communication****  ****Memory-mapped QSPI communication****  ****Memory-mapped QSPI communication****  ****Memory-mapped QSPI communication****  ****Memory-mapped QSPI communication**** ";
uint8_t aRxBuffer[256];

PMIC_HandleTypeDef hpmic;

MPU9250_CONFIG_t mpu9250_conf;
MPU9250_DATA_t	 mpu9250_data;

BMP280_HandleTypeDef bmp280;

uint8_t rx_buf[64];
volatile int rx_done;


#if TEST_USB_HOST
#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FMC_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_DMA_Init(void);
static void MX_MDMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_ADC3_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);

#if TEST_QSPI
static void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi);
static void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi);
static void QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi);
static void QSPI_EnterFourBytesAddress(QSPI_HandleTypeDef *hqspi);
#endif

static void Error_HandlerQSPI(const char* msg);


void imu_init(void);
void imu_run(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch)
{
	//ITM_SendChar(ch);
	uint8_t data = (uint8_t)ch;
	HAL_UART_Transmit(&huart1, &data, 1, 1000);
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

#define NO_SAMPLE 100
uint16_t adc_buff[NO_SAMPLE];
uint16_t user_buff[NO_SAMPLE];

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
 memcpy(&user_buff[0], & adc_buff[0], NO_SAMPLE/2);
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
 memcpy(&user_buff[NO_SAMPLE/2], & adc_buff[NO_SAMPLE/2], NO_SAMPLE/2);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* Enable the CPU Cache */
  /* Enable I-Cache */
  //SCB_EnableICache();
  /* Enable D-Cache */
  //SCB_EnableDCache();

  /* USER CODE END 1 */

/* USER CODE BEGIN Boot_Mode_Sequence_0 */
  int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /* Wait until CPU2 boots and enters in stop mode or timeout*/
#if !TEST_SLEEP
  timeout = 0xFFFF;
  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
  if ( timeout < 0 )
  {
  Error_Handler();
  }
#endif
/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  /* USER CODE BEGIN Boot_Mode_Sequence_2 */
#if !TEST_SLEEP
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
#endif
  /* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();


  //
  HAL_GPIO_WritePin(PWR_EN_PERIPH_GPIO_Port, PWR_EN_PERIPH_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(PWR_EN_BAT_GPIO_Port, PWR_EN_BAT_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(PWR_EN_5V_GPIO_Port, PWR_EN_5V_Pin, GPIO_PIN_SET);
  HAL_Delay(20);
  //
  MX_DMA_Init();
  MX_MDMA_Init();
  MX_FMC_Init();
  MX_QUADSPI_Init();
  MX_SPI1_Init();
  MX_SPI4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
#if TEST_USB_DEVICE
  MX_USB_DEVICE_Init();
#endif
#if TEST_USB_HOST
  /* Enable the USB voltage level detector */
  HAL_PWREx_EnableUSBVoltageDetector();

  MX_USB_HOST_Init();
#endif
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_FATFS_Init();
  MX_ADC3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  printf("FC_HwTest...\n");


  // check power on
#if TEST_SLEEP
  if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
  {
	  printf("Wakeup from STANDBY\n");

	  // Clear system Standby flag
	  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);

	  // turn on LED...
	  HAL_GPIO_WritePin(PWR_LED_GPIO_Port, PWR_LED_Pin, GPIO_PIN_RESET);

	  /* The Following Wakeup sequence is highly recommended prior to each Standby mode entry
	    mainly  when using more than one wakeup source this is to not miss any wakeup event.
	    - Disable all used wakeup sources,
	    - Clear all related wakeup flags,
	    - Re-enable all used wakeup sources,
	    - Enter the Standby mode.
	  */
	  /* Disable all used wakeup sources*/
	  HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN1);

	  /* Re-enable all used wakeup sources*/
	  /* Configure Wakeup pin */
	  PWREx_WakeupPinTypeDef sPinParams;
	  HAL_StatusTypeDef ret = HAL_OK;

	  sPinParams.WakeUpPin    = PWR_WAKEUP_PIN1;
	  sPinParams.PinPolarity  = PWR_PIN_POLARITY_HIGH;
	  sPinParams.PinPull      = PWR_PIN_NO_PULL;
	  HAL_PWREx_EnableWakeUpPin(&sPinParams);

	  /* Clear all related wakeup flags */
#define PWR_WAKEUP_FLAGS  (PWR_WAKEUP_FLAG1 | PWR_WAKEUP_FLAG2 | PWR_WAKEUP_FLAG3 | \
                           PWR_WAKEUP_FLAG4 | PWR_WAKEUP_FLAG5 | PWR_WAKEUP_FLAG6)


	  ret = HAL_PWREx_ClearWakeupFlag(PWR_WAKEUP_FLAGS);
	  if(ret != HAL_OK)
	  {
	    Error_Handler();
	  }

	  uint32_t lastTick = HAL_GetTick();
	  HAL_Delay(100);
	  while (1)
	  {
		  GPIO_PinState state = HAL_GPIO_ReadPin(PWR_WKUP0_KEY_ENTER_GPIO_Port, PWR_WKUP0_KEY_ENTER_Pin);
		  if (state == GPIO_PIN_RESET)
			  break;
	  }

	  if ((HAL_GetTick() - lastTick) < 2000)
	  {
		  //if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) == RESET)
		  {
			  // deep sleep again
			  printf("Deep sleep again~\n");

		    /* Allocate the Flash memory to the CM4 to be able to execute code when CM7 enter STOP mode */
		    //__HAL_RCC_FLASH_C2_ALLOCATE();

		    /* Turn OFF LED1 */
		    HAL_GPIO_WritePin(PWR_LED_GPIO_Port, PWR_LED_Pin, GPIO_PIN_SET);

   			if(__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET)
			{
				printf("D2 Domain not in Standby mode\n");
			}

			printf("PWR->CPUCR = %X\n", PWR->CPUCR);
			printf("PWR->CPU2CR = %X\n", PWR->CPU2CR);

		    /* Enter D3 to DStandby mode */
		    HAL_PWREx_EnterSTANDBYMode(PWR_D3_DOMAIN);
		    /* Enter D1 to DStandby mode */
		    HAL_PWREx_EnterSTANDBYMode(PWR_D1_DOMAIN);


		    printf("Never come here~ It sleep deeply...\n");
		  }
	  }
	  else
	  {
		  printf("Normal Bootup...\n");
	  }
  }
#endif


  /* Program the SDRAM external device */
  SDRAM_Initialization_Sequence(&hsdram1, &command);
  HAL_Delay(100);

#if 0 // READ MPU9520 DEVICE ID
  {
	  uint8_t data[2] = { 0x75 | 0x80, 0x00 };

	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
	  HAL_Delay(1);
	  uint8_t addr = 0x75 | 0x80;
	  uint8_t id = 0x00;
	  HAL_SPI_TransmitReceive(&hspi4, &addr, &id, 2, 1000);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
  }
#endif

#if TEST_PMIC
  hpmic.i2c = &hi2c1;
  //hpmic.wakeup_port = PMIC_WAKEUP_GPIO_Port;
  //hpmic.wakeup_pin = PMIC_WAKEUP_Pin;
  //hpmic.pwrup_port = PMIC_PWRUP_GPIO_Port;
  //hpmic.pwrup_pin = PMIC_PWRUP_Pin;
  //hpmic.vcom_port = PMIC_VCOM_GPIO_Port;
  //hpmic.vcom_pin = PMIC_VCOM_Pin;
  //hpmic.pwrgood_port = PMIC_PWR_GOOD_GPIO_Port;
  //hpmic.pwrgood_pin = PMIC_PWR_GOOD_Pin;
  //hpmic.int_port = PMIC_nINT_GPIO_Port;
  //hpmic.int_pin = PMIC_nINT_Pin;

  HAL_GPIO_WritePin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin, GPIO_PIN_RESET);
  HAL_Delay(2);

  {
	  // READ Registers
	  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET); // WAKEUP
	  HAL_Delay(100);

		uint8_t i2c_addr = (0x48 << 1);
		uint8_t reg_addr = 0x00;
		uint8_t data[17];
		uint8_t done = 1;

		//HAL_I2C_Master_Transmit(&hi2c1, i2c_addr, &reg_addr, 1, 1000);
		//HAL_I2C_Master_Receive(&hi2c1, i2c_addr, &data[0], 17, 1000);
		HAL_I2C_Mem_Read(&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, &data[0], 17, 1000);

		printf("READ PMIC Registers:\n");
		for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
		 printf("  REG #%02d: %02X\n", i, data[i]);

		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET); // SLEEP
		HAL_Delay(100);
  }
#endif

#if TEST_BMP280
#if USE_SPI
  bmp280.spi = &hspi4;
  bmp280.cs_port = IMU1_nCS2_GPIO_Port;
  bmp280.cs_pin = IMU1_nCS2_Pin; // IMU1_nCS2
#else
  bmp280.i2c = &hi2c2;
#endif

  BMP280_Init(&bmp280);
#endif

#if TEST_MPU9250
  mpu9250_conf.hspi = &hspi4;
  mpu9250_conf.GPIOx = IMU1_nCS1_GPIO_Port;
  mpu9250_conf.GPIO_PIN = IMU1_nCS1_Pin; // IMU1_nCS1
  mpu9250_conf.ACCEL_SCALE = ACCEL_SCALE_2G;
  mpu9250_conf.GYRO_SCALE = GYRO_SCALE_1000dps;

  MPU9250_Initialize(&mpu9250_conf);
  MPU9250_Config(&mpu9250_conf);
  MPU9250_Calibrate(&mpu9250_conf);
#endif

#if TEST_MPU9250_I2C
  {
	  uint8_t i2c_addr = (0b1101000 << 1);
	  uint8_t reg_addr = 0x75;
	  uint8_t data = 0xFF;
	  HAL_I2C_Master_Transmit(&hi2c2, i2c_addr, &reg_addr, 1, 1000);
	  HAL_I2C_Master_Receive(&hi2c2, i2c_addr, &data, 1, 1000);
	  printf("MPU9650:WHO_AM_I: %d\n", data);
  }
#endif

#if TEST_BMP280_I2C
  {
	  uint8_t i2c_addr = (0x76 << 1);
	  uint8_t reg_addr = 0xD0;
	  uint8_t data = 0xFF;
	  HAL_I2C_Master_Transmit(&hi2c2, i2c_addr, &reg_addr, 1, 1000);
	  HAL_I2C_Master_Receive(&hi2c2, i2c_addr, &data, 1, 1000);
	  printf("BMP280:WHO_AM_I: %d\n", data);
  }
#endif

#if TEST_SDRAM
  volatile uint8_t* memPtr = (volatile uint8_t *)0xD0000000;
  printf("Test SDRAM ====\n");
  volatile uint8_t* tmpPtr = memPtr;
  uint32_t data = 0x55;
  {
	  uint32_t tickStart = HAL_GetTick();
	  for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
		  *tmpPtr++ = data;
	  printf("Clear All: elapsed %d msec\n", HAL_GetTick() - tickStart);
  }

  printf("Write Data ");
  tmpPtr = memPtr;
  data = 0x55;
  for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
  {
	  if ((i % (1024 * 1024)) == 0)
		  printf(".");
	  *tmpPtr++ = data++;
  }

  printf("\nCompare Data ");
  tmpPtr = memPtr;
  data = 0x55;
  uint8_t memOk = 1;
  for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
  {
	  if ((i % (1024 * 1024)) == 0)
		  printf(".");

	  uint8_t a = *tmpPtr;
	  uint8_t b = data;
	  if (a != b)
	  {
		  printf("\nMemory corrupt at %08X: %02X, %02X\n", (unsigned int)i, a, b);
		  memOk = 0;
		  break;
	  }
	  tmpPtr++;
	  data++;
  }
  if (memOk)
	  printf("\nMemory compare passed!!\n");
#endif


#if TEST_USB_HOST
#endif



  //volatile uint8_t* norPtr = (volatile uint8_t *)0x90000000;
  //printf("nor: %02X\n", norPtr[0]);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint32_t lastTick = HAL_GetTick();

#if TEST_PMIC
  uint8_t pmicStatus = 0;
  printf("Press F2 to start PMIC Test!\n");
#endif

#if TEST_QSPI
  QSPI_CommandTypeDef sCommand;
  QSPI_MemoryMappedTypeDef sMemMappedCfg;
  uint32_t address = 0;
  uint16_t index;
  volatile uint8_t* qspi_addr = (volatile uint8_t*)(0x9000000);
  volatile uint8_t step = 0;

  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  printf("Press F1 to start QSPI Test!\n");
#endif

#if TEST_SPISLAVE
  while(1)
  {
	  printf("SPI receiving...\n");
	  rx_done = 0;
	  HAL_StatusTypeDef res = HAL_SPI_Receive_IT(&hspi1, rx_buf, 5);
	  while (!rx_done);
  }
#endif

#if TEST_UART3
  while (1)
  {
	  if ((huart2.Instance->ISR & UART_FLAG_RXNE) /*&& (huart2.Instance->CR1 & USART_CR1_RXNEIE)*/)
	  {
		  uint8_t data = (uint8_t)huart2.Instance->RDR;
		  HAL_UART_Transmit(&huart3, &data, 1, 1000);
	  }

	  if ((huart3.Instance->ISR & UART_FLAG_RXNE))
	  {
		  uint8_t data = (uint8_t)huart3.Instance->RDR;
		  HAL_UART_Transmit(&huart1, &data, 1, 1000);
	  }
  }
#endif

#if 0
  {
	  HAL_ADC_Start_DMA(&hadc3, (uint32_t*)adc_buff, NO_SAMPLE);
	  HAL_TIM_Base_Start(&htim2);
  }
#endif

#if TEST_USB_HOST
  HID_InitApplication();
  HID_HOST_Start();
#endif


  while (1)
  {
#if TEST_USB_HOST
	  MX_USB_HOST_Process();
	  HID_HOST_Process();
#endif

#if TEST_MSC
	  // nop ...
#endif

    if (HAL_GPIO_ReadPin(KEY_ESCAPE_GPIO_Port, KEY_ESCAPE_Pin) != GPIO_PIN_RESET)
    {
    	HAL_Delay(200);
    	if (HAL_GPIO_ReadPin(KEY_ESCAPE_GPIO_Port, KEY_ESCAPE_Pin) != GPIO_PIN_RESET)
    	{
    		HAL_GPIO_TogglePin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin);
    		if (PMIC_WAKEUP_GPIO_Port->IDR & KEY_ESCAPE_Pin)
    			printf("PMIC WAKEUP\n");
    		else
    			printf("PMIC SLEEP\n");
    	}
    }

#if TEST_SLEEP
    if (HAL_GPIO_ReadPin(PWR_WKUP0_KEY_ENTER_GPIO_Port, PWR_WKUP0_KEY_ENTER_Pin) != GPIO_PIN_RESET)
    {
    	HAL_Delay(100);
    	if (HAL_GPIO_ReadPin(PWR_WKUP0_KEY_ENTER_GPIO_Port, PWR_WKUP0_KEY_ENTER_Pin) != GPIO_PIN_RESET)
    	{
    		while (HAL_GPIO_ReadPin(PWR_WKUP0_KEY_ENTER_GPIO_Port, PWR_WKUP0_KEY_ENTER_Pin) != GPIO_PIN_RESET);

    		  //if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) == RESET)
    		  {
    			  printf("ENTER Deep Sleep\n");

    			  /* The Following Wakeup sequence is highly recommended prior to each Standby mode entry
    			    mainly  when using more than one wakeup source this is to not miss any wakeup event.
    			    - Disable all used wakeup sources,
    			    - Clear all related wakeup flags,
    			    - Re-enable all used wakeup sources,
    			    - Enter the Standby mode.
    			  */
    			  /* Disable all used wakeup sources*/
    			  HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN1);

    			  /* Re-enable all used wakeup sources*/
    			  /* Configure Wakeup pin */
    			  PWREx_WakeupPinTypeDef sPinParams;
    			  HAL_StatusTypeDef ret = HAL_OK;

    			  sPinParams.WakeUpPin    = PWR_WAKEUP_PIN1;
    			  sPinParams.PinPolarity  = PWR_PIN_POLARITY_HIGH;
    			  sPinParams.PinPull      = PWR_PIN_NO_PULL;
    			  HAL_PWREx_EnableWakeUpPin(&sPinParams);


    		    /* Allocate the Flash memory to the CM4 to be able to execute code when CM7 enter STOP mode */
    		    //__HAL_RCC_FLASH_C2_ALLOCATE();

    		    /* Turn OFF LED */
    		    //HAL_GPIO_WritePin(PWR_LED_GPIO_Port, PWR_LED_Pin, GPIO_PIN_SET);

    			if(__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET)
    			{
    				printf("D2 Domain not in Standby mode\n");
    			}

    			printf("PWR->CPUCR = %X\n", PWR->CPUCR);
    			printf("PWR->CPU2CR = %X\n", PWR->CPU2CR);

			    /* Enter D3 to DStandby mode */
			    HAL_PWREx_EnterSTANDBYMode(PWR_D3_DOMAIN);

    		    /* Enter D1 to DStandby mode */
    		    HAL_PWREx_EnterSTANDBYMode(PWR_D1_DOMAIN);

    		    printf("Never come here~ I Think...\n");
    		  }
    	}
    }
#endif

    /* USER CODE BEGIN 3 */
	if (HAL_GetTick() - lastTick > 1000)
	{
		HAL_GPIO_TogglePin(PWR_LED_GPIO_Port, PWR_LED_Pin);
		lastTick = HAL_GetTick();



		// ADC
		if (0)
		{

			  /* Run the ADC calibration in single-ended mode */
			  if (HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
			  {
				/* Calibration Error */
				Error_Handler();
			  }

			  /*##-3- Start the conversion process #######################################*/
			  if (HAL_ADC_Start(&hadc3) != HAL_OK)
			  {
				/* Start Conversation Error */
				Error_Handler();
			  }

			  /*##-4- Wait for the end of conversion #####################################*/
			  /*  For simplicity reasons, this example is just waiting till the end of the
				  conversion, but application may perform other tasks while conversion
				  operation is ongoing. */
			  if (HAL_ADC_PollForConversion(&hadc3, 10) != HAL_OK)
			  {
				/* End Of Conversion flag not set on time */
				Error_Handler();
			  }
			  else
			  {
				/* ADC conversion completed */
				/*##-5- Get the converted value of regular channel  ########################*/
				uint32_t uhADCxConvertedValue = HAL_ADC_GetValue(&hadc3);

				// 0xFFFF : 3.3v = measured-value : voltage
				float voltage_m = 3.3 * uhADCxConvertedValue / 0xFFFF;
				// voltage_i * 1000 / (560 + 1000) = voltage_m
				float voltage_i = voltage_m * 1.56;

				printf("VOL: %d, %d.%d --> %d.%d\n",
						uhADCxConvertedValue,
						(int)voltage_m, ((int)(voltage_m * 10)) % 10,
						(int)voltage_i, ((int)(voltage_i * 10)) % 10);
			  }
		}


#if TEST_PMIC
		if (pmicStatus)
		{
			uint8_t status = PMIC_ReadPowerStatus(&hpmic);
			printf("PMIC Power status: %02X\n", status);
		}
#endif

#if TEST_BMP280
		BMP280_Update(&bmp280);

		printf("BMP: %d(P) %d(T)\n", bmp280.pres32, bmp280.temp32);
#endif

#if TEST_MPU9250
			MPU9250_Update7DOF(&mpu9250_conf, &mpu9250_data);
			MPU9250_UpdateMAG(&mpu9250_conf, &mpu9250_data);

			printf("MPU: %x,%x,%x,%x,%x,%x\n",
					mpu9250_data.accel[0], mpu9250_data.accel[1], mpu9250_data.accel[2],
					mpu9250_data.gyro[0], mpu9250_data.gyro[1], mpu9250_data.gyro[2]);
#endif
	}

#if TEST_PMIC
	if (HAL_GPIO_ReadPin(KEY_FUNC2_GPIO_Port, KEY_FUNC2_Pin) != GPIO_PIN_RESET)
	{
		HAL_Delay(100); // prevent debounce

		if (pmicStatus == 0)
		{
			HAL_GPIO_WritePin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin, GPIO_PIN_SET); // wake-up --> standby
			HAL_Delay(300);

			//PMIC_Init(&hpmic);
			//HAL_Delay(100);

			PMIC_EnableRegulators(&hpmic, 0b10111111);
			HAL_Delay(100);

			//HAL_GPIO_WritePin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin, GPIO_PIN_SET); // power-up --> active
			//HAL_GPIO_WritePin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
			pmicStatus = 1;

			printf("TURN ON EINK-PMIC\n");

			  {
				// READ Registers
				uint8_t i2c_addr = (0x48 << 1);
				uint8_t reg_addr = 0x00;
				uint8_t data[17];
				uint8_t done = 1;

				//HAL_I2C_Master_Transmit(&hi2c1, i2c_addr, &reg_addr, 1, 1000);
				//HAL_I2C_Master_Receive(&hi2c1, i2c_addr, &data[0], 17, 1000);
				HAL_I2C_Mem_Read(&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, &data[0], 17, 1000);

				printf("READ PMIC Registers:\n");
				for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
					printf("  REG #%02d: %02X\n", i, data[i]);
			  }
		}
		else
		{
			//HAL_GPIO_WritePin(PMIC_VCOM_GPIO_Port, PMIC_VCOM_Pin, GPIO_PIN_RESET);
			//HAL_Delay(100);

			PMIC_EnableRegulators(&hpmic, 0b01000000);
			HAL_Delay(100);


			  {
				// READ Registers
				uint8_t i2c_addr = (0x48 << 1);
				uint8_t reg_addr = 0x00;
				uint8_t data[17];
				uint8_t done = 1;

				//HAL_I2C_Master_Transmit(&hi2c1, i2c_addr, &reg_addr, 1, 1000);
				//HAL_I2C_Master_Receive(&hi2c1, i2c_addr, &data[0], 17, 1000);
				HAL_I2C_Mem_Read(&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, &data[0], 17, 1000);

				printf("READ PMIC Registers:\n");
				for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
					printf("  REG #%02d: %02X\n", i, data[i]);
			  }

			//HAL_GPIO_WritePin(PMIC_PWRUP_GPIO_Port, PMIC_PWRUP_Pin, GPIO_PIN_RESET); // power-down --> standby
			//HAL_Delay(100);
			HAL_GPIO_WritePin(PMIC_WAKEUP_GPIO_Port, PMIC_WAKEUP_Pin, GPIO_PIN_RESET); // go to sleep
			pmicStatus = 0;

			printf("TURN OFF EINK-PMIC\n");
		}
	}
#endif

	//
#if TEST_QSPI
	switch(step)
	{
	  case 0:
		  if (HAL_GPIO_ReadPin(KEY_FUNC1_GPIO_Port, KEY_FUNC1_Pin) == GPIO_PIN_RESET)
			  break;

		CmdCplt = 0;

		/* Initialize QuadSPI ------------------------------------------------ */
		printf("Initialize QuadSPI\n");
		HAL_QSPI_DeInit(&hqspi);
		if (HAL_QSPI_Init(&hqspi) != HAL_OK)
		{
		  Error_HandlerQSPI("HAL_QSPI_Init");
		}

		/* Enable 4 bytes Address mode */
		printf("Enable 4 bytes Address mode\n");
		QSPI_EnterFourBytesAddress(&hqspi);

		HAL_Delay(10);
		/* Enable write operations ------------------------------------------- */
		printf("Enable write operations\n");
		QSPI_WriteEnable(&hqspi);

		/* Erasing Sequence -------------------------------------------------- */
		sCommand.Instruction = SECTOR_ERASE_CMD;
		sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
		sCommand.Address     = address;
		sCommand.DataMode    = QSPI_DATA_NONE;
		sCommand.DummyCycles = 0;

		printf("Erasing Sequence : %u\n", address);
		if (HAL_QSPI_Command_IT(&hqspi, &sCommand) != HAL_OK)
		{
			Error_HandlerQSPI("SECTOR_ERASE_CMD");
		}

		step++;
		break;

	  case 1:
		if(CmdCplt != 0)
		{
		  CmdCplt = 0;
		  StatusMatch = 0;

		  /* Configure automatic polling mode to wait for end of erase ------- */
		  printf("Configure automatic polling mode to wait for end of erase\n");
		  QSPI_AutoPollingMemReady(&hqspi);

		  step++;
		}
		break;

	  case 2:
		if(StatusMatch != 0)
		{
		  StatusMatch = 0;
		  TxCplt = 0;

		  /* Enable write operations ----------------------------------------- */
		  printf("Enable write operations\n");
		  QSPI_WriteEnable(&hqspi);

		  /* Writing Sequence ------------------------------------------------ */
		  sCommand.Instruction = QUAD_IN_FAST_PROG_CMD;
		  sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
		  sCommand.DataMode    = QSPI_DATA_4_LINES;
		  sCommand.NbData      = BUFFERSIZE;

		  printf("Writing Sequence\n");
		  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		  {
			  Error_HandlerQSPI("QUAD_IN_FAST_PROG_CMD");
		  }

		  printf(" --> Transmit\n");
		  if (HAL_QSPI_Transmit_IT(&hqspi, aTxBuffer) != HAL_OK)
		  {
			  Error_HandlerQSPI("Transmit data");
		  }

		  step++;
		}
		break;

	  case 3:
		if(TxCplt != 0)
		{
		  TxCplt = 0;
		  StatusMatch = 0;

		  /* Configure automatic polling mode to wait for end of program ----- */
		  printf("Configure automatic polling mode to wait for end of program\n");
		  QSPI_AutoPollingMemReady(&hqspi);

		  step++;
		}
		break;

	  case 4:
		if(StatusMatch != 0)
		{
		  StatusMatch = 0;
		  RxCplt = 0;

#if TEST_MEMORY_MAPPED
		  /* Configure Volatile Configuration register (with new dummy cycles) */
		  printf("Configure Volatile Configuration register (with new dummy cycles)\n");
		  QSPI_DummyCyclesCfg(&hqspi);

		  /* Reading Sequence ------------------------------------------------ */
		  sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
		  sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_READ_QUAD;

		  sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;

		  printf("Configure memory mapped\n");
		  if (HAL_QSPI_MemoryMapped(&hqspi, &sCommand, &sMemMappedCfg) != HAL_OK)
		  {
			  Error_HandlerQSPI("MemoryMapped");
		  }

		  RxCplt = 1;
#else
		    // Reading sequence
		    printf("Reading Sequence: Direct\n");
		    sCommand.Instruction = QUAD_INOUT_FAST_READ_CMD;
		    sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
		    sCommand.DataMode    = QSPI_DATA_4_LINES;
		    sCommand.NbData      = BUFFERSIZE;
			sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_READ_QUAD;

			if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
			{
				Error_HandlerQSPI("QUAD_INOUT_FAST_READ_CMD");
			}

			if (HAL_QSPI_Receive_IT(&hqspi, aRxBuffer) != HAL_OK)
			{
				Error_HandlerQSPI("Receive_IT");
			}
#endif
			step++;
		}
		break;

	  case 5:
		  if (RxCplt != 0)
		  {
			RxCplt = 0;

			/* Result comparison ----------------------------------------------- */
#if TEST_MEMORY_MAPPED
			  printf("Reading Sequence: Memory mapped\n");
			  for (index = 0; index < BUFFERSIZE; index++)
			  {
				if (*qspi_addr != aTxBuffer[index])
				{
				  printf(" --> Mismatch at %d\n", index);
				  Error_HandlerQSPI("");
				}
				else
				{

					  HAL_UART_Transmit(&huart1, &aTxBuffer[index], 1, 1000);
				}
				qspi_addr++;
			  }
			  printf(" --> OK\n");
#else
			for (index = 0; index < BUFFERSIZE; index++)
			{
			  if (aRxBuffer[index] != aTxBuffer[index])
			  {
				  printf(" --> Mismatch at %d\n", index);
				  Error_HandlerQSPI("");
			  }
			  else
			  {
				  HAL_UART_Transmit(&huart1, &aRxBuffer[index], 1, 1000);
			  }
			}
			printf(" --> OK\n");
#endif

			address += QSPI_PAGE_SIZE;
			if(address >= QSPI_END_ADDR)
			{
			  address = 0;
			}
			step = 0;
		  }
		  break;

	  default :
		Error_Handler();
	}
#endif

#if TEST_GPS
	while ((huart2.Instance->ISR & UART_FLAG_RXNE) /*&& (huart2.Instance->CR1 & USART_CR1_RXNEIE)*/)
	{
		uint8_t data = (uint8_t)huart2.Instance->RDR;
		HAL_UART_Transmit(&huart1, &data, 1, 1000);
	}
#endif

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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 8;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_SPI4
                              |RCC_PERIPHCLK_SPI1|RCC_PERIPHCLK_I2C2
                              |RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_USB|RCC_PERIPHCLK_QSPI
                              |RCC_PERIPHCLK_FMC|RCC_PERIPHCLK_CKPER;
  PeriphClkInitStruct.PLL3.PLL3M = 5;
  PeriphClkInitStruct.PLL3.PLL3N = 192;
  PeriphClkInitStruct.PLL3.PLL3P = 8;
  PeriphClkInitStruct.PLL3.PLL3Q = 20;
  PeriphClkInitStruct.PLL3.PLL3R = 8;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
  PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
  PeriphClkInitStruct.CkperClockSelection = RCC_CLKPSOURCE_HSI;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL3;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_CLKP;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable USB Voltage detector
  */
  HAL_PWREx_EnableUSBVoltageDetector();
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
  hi2c1.Init.Timing = 0x00B03FDB; // 0x00B03FDB(400KHz), 0x307075B1(100KHz)
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
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00B03FDB;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

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
  hqspi.Init.ClockPrescaler = 5; // 240MHz / (prescaler + 1) = 40
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE; // QSPI_SAMPLE_SHIFTING_NONE, QSPI_SAMPLE_SHIFTING_HALFCYCLE
  hqspi.Init.FlashSize = 25; // 64MB = 2 ^ 26 = 2 ^ (FlashSize + 1)
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_3_CYCLE; //
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

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}

/**
  * Enable MDMA controller clock
  */
static void MX_MDMA_Init(void)
{

  /* MDMA controller clock enable */
  __HAL_RCC_MDMA_CLK_ENABLE();
  /* Local variables */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x0;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA; // SPI_FIFO_THRESHOLD_16DATA;
  hspi1.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI4_Init(void)
{

  /* USER CODE BEGIN SPI4_Init 0 */

  /* USER CODE END SPI4_Init 0 */

  /* USER CODE BEGIN SPI4_Init 1 */

  /* USER CODE END SPI4_Init 1 */
  /* SPI4 parameter configuration*/
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW; // SPI_POLARITY_HIGH, SPI_POLARITY_LOW
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE; // SPI_PHASE_2EDGE, SPI_PHASE_1EDGE
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; // SPI_BAUDRATEPRESCALER_2;
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 0x0;
  hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi4.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi4.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi4.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi4.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi4.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi4.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi4.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi4.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi4.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI4_Init 2 */

  /* USER CODE END SPI4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */
  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
  hadc3.Init.Resolution = ADC_RESOLUTION_16B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN; // ADC_OVR_DATA_PRESERVED;
  hadc3.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc3.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_8CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_2;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_3;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_4;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_5;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_6;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_7;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_8;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_9;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_10;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_11;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_12;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_13;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_14;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_15;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Rank = ADC_REGULAR_RANK_16;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 239; // 240000000 / 240 = 1000000 (1MHz)
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000 - 1; // 1us * 10000 = 10ms -> 100Hz
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/* FMC initialization function */
void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9; // FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3; // FMC_SDRAM_CAS_LATENCY_1, FMC_SDRAM_CAS_LATENCY_2, FMC_SDRAM_CAS_LATENCY_3
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2; // FMC_SDRAM_CLOCK_DISABLE, FMC_SDRAM_CLOCK_PERIOD_2, FMC_SDRAM_CLOCK_PERIOD_3
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE; // FMC_SDRAM_RBURST_DISABLE, FMC_SDRAM_RBURST_ENABLE
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1; // FMC_SDRAM_RPIPE_DELAY_0, FMC_SDRAM_RPIPE_DELAY_1, FMC_SDRAM_RPIPE_DELAY_2
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2; // 2
  SdramTiming.ExitSelfRefreshDelay = 7; // 7
  SdramTiming.SelfRefreshTime = 4; // 4
  SdramTiming.RowCycleDelay = 7; // 7
  SdramTiming.WriteRecoveryTime = 4; // 2
  SdramTiming.RPDelay = 2; // 2
  SdramTiming.RCDDelay = 2; // 2

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EINK_BUSY_GPIO_Port, EINK_BUSY_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, EPD_D6_Pin|EPD_D7_Pin|USB_OTG_HS_PWR_EN_Pin|EPD_D0_Pin
                          |EPD_D1_Pin|EPD_D2_Pin|EPD_D3_Pin|EPD_D4_Pin
                          |EPD_D5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOJ, EPD_CKV_Pin|EPD_CL_Pin|EPD_GMODE_Pin|EPD_LE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOK, EPD_OE_Pin|EPD_SPH_Pin|EPD_SPV_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, PWR_EN_BAT_Pin|PWR_EN_PERIPH_Pin|PMIC_VCOM_Pin|PMIC_WAKEUP_Pin
                          |PMIC_PWRUP_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOG, PWR_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PWR_EN_5V_GPIO_Port, PWR_EN_5V_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : KEY_ESCAPE_Pin EINK_CMD_Pin LOW_BATTERY_Pin KEY_LEFT_Pin
                           KEY_RIGHT_Pin KEY_UP_Pin KEY_DOWN_Pin KEY_FUNC1_Pin
                           KEY_FUNC2_Pin USB_OTG_FS_VBUS_Pin */
  GPIO_InitStruct.Pin = KEY_ESCAPE_Pin|EINK_CMD_Pin|LOW_BATTERY_Pin|KEY_LEFT_Pin
                          |KEY_RIGHT_Pin|KEY_UP_Pin|KEY_DOWN_Pin|KEY_FUNC1_Pin
                          |KEY_FUNC2_Pin|USB_OTG_FS_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : EINK_BUSY_Pin */
  GPIO_InitStruct.Pin = EINK_BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EINK_BUSY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY_MENU_Pin USB_OTG_HS_OVCR_Pin */
  GPIO_InitStruct.Pin = KEY_MENU_Pin|USB_OTG_HS_OVCR_Pin | PWR_WKUP0_KEY_ENTER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : EPD_D6_Pin EPD_D7_Pin USB_OTG_HS_PWR_EN_Pin EPD_D0_Pin
                           EPD_D1_Pin EPD_D2_Pin EPD_D3_Pin EPD_D4_Pin
                           EPD_D5_Pin */
  GPIO_InitStruct.Pin = EPD_D6_Pin|EPD_D7_Pin|USB_OTG_HS_PWR_EN_Pin|EPD_D0_Pin
                          |EPD_D1_Pin|EPD_D2_Pin|EPD_D3_Pin|EPD_D4_Pin
                          |EPD_D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : EPD_CKV_Pin EPD_CL_Pin EPD_GMODE_Pin EPD_LE_Pin */
  GPIO_InitStruct.Pin = EPD_CKV_Pin|EPD_CL_Pin|EPD_GMODE_Pin|EPD_LE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

  /*Configure GPIO pins : EPD_OE_Pin EPD_SPH_Pin EPD_SPV_Pin */
  GPIO_InitStruct.Pin = EPD_OE_Pin|EPD_SPH_Pin|EPD_SPV_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

  /*Configure GPIO pins : PWR_EN_BAT_Pin PWR_EN_PERIPH_Pin PMIC_VCOM_Pin PMIC_WAKEUP_Pin
                           PMIC_PWRUP_Pin PWR_LED_Pin */
  GPIO_InitStruct.Pin = PWR_EN_BAT_Pin|PWR_EN_PERIPH_Pin|PMIC_VCOM_Pin|PMIC_WAKEUP_Pin
                          |PMIC_PWRUP_Pin|PWR_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PMIC_PWR_GOOD_Pin PMIC_nINT_Pin */
  GPIO_InitStruct.Pin = PMIC_PWR_GOOD_Pin|PMIC_nINT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PWR_EN_5V_Pin */
  GPIO_InitStruct.Pin = PWR_EN_5V_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PWR_EN_5V_GPIO_Port, &GPIO_InitStruct);



  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, IMU1_nCS1_Pin|IMU1_nCS2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : IMU1_nCS1_Pin IMU1_nCS2_Pin */
  GPIO_InitStruct.Pin = IMU1_nCS1_Pin|IMU1_nCS2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : IMU_DRDY_Pin IMU_FSYNC_Pin IMU_nINT_Pin */
  GPIO_InitStruct.Pin = IMU_DRDY_Pin|IMU_FSYNC_Pin|IMU_nINT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Perform the SDRAM exernal memory inialization sequence
  * @param  hsdram: SDRAM handle
  * @param  Command: Pointer to SDRAM command structure
  * @retval None
  */
static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
  __IO uint32_t tmpmrd =0;
  /* Step 3:  Configure a clock configuration enable command */
  Command->CommandMode 			 = FMC_SDRAM_CMD_CLK_ENABLE;
  Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber 	 = 1;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 4: Insert 100 ms delay */
  HAL_Delay(100);

  /* Step 5: Configure a PALL (precharge all) command */
  Command->CommandMode 			 = FMC_SDRAM_CMD_PALL;
  Command->CommandTarget 	     = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber 	 = 1;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 6 : Configure a Auto-Refresh command */
  Command->CommandMode 			 = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber 	 = 4;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 7: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber 	 = 1;
  Command->ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 8: Set the refresh rate counter */
  /* (15.62 us x Freq) - 20 */
  /* Set the device refresh counter */
  HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT);
}


#if TEST_QSPI

/**
  * @brief  Command completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_CmdCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  CmdCplt++;
  printf("HAL_QSPI_CmdCpltCallback: %d\n", CmdCplt);
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  RxCplt++;
  printf("HAL_QSPI_RxCpltCallback: %d\n", RxCplt);
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  TxCplt++;
  printf("HAL_QSPI_TxCpltCallback: %d\n", TxCplt);
}

/**
  * @brief  Status Match callbacks
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
  StatusMatch++;
  printf("HAL_QSPI_StatusMatchCallback: %d\n", StatusMatch);
}


/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     s_command;
  QSPI_AutoPollingTypeDef s_config;

  /* Enable write operations */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = WRITE_ENABLE_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	  Error_HandlerQSPI("QSPI_INSTRUCTION_1_LINE");
  }

  /* Configure automatic polling mode to wait for write enabling */
  s_config.Match           = 0x0202;
  s_config.Mask            = 0x0202;
  s_config.MatchMode       = QSPI_MATCH_MODE_AND;
  s_config.StatusBytesSize = 2;
  s_config.Interval        = 0x10;
  s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  s_command.Instruction    = READ_STATUS_REG_CMD;
  s_command.DataMode       = QSPI_DATA_1_LINE;

  if (HAL_QSPI_AutoPolling(hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	  Error_HandlerQSPI("AutoPolling");
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
  sConfig.Mask            = 0x0101;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 2;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling_IT(hqspi, &sCommand, &sConfig) != HAL_OK)
  {
	  Error_HandlerQSPI("AutoPolling_IT");
  }
}

/**
  * @brief  This function configure the dummy cycles on memory side.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef s_command;
  uint16_t reg=0;

  /* Initialize the read volatile configuration register command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = READ_VOL_CFG_REG_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_1_LINE;
  s_command.DummyCycles       = 0;
  s_command.NbData            = 2;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	  Error_HandlerQSPI("READ_VOL_CFG_REG_CMD");
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(hqspi, (uint8_t *)(&reg), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	  Error_HandlerQSPI("ReceiveData");
  }

  /* Enable write operations */
  QSPI_WriteEnable(hqspi);

  /* Update volatile configuration register (with new dummy cycles) */
  s_command.Instruction = WRITE_VOL_CFG_REG_CMD;
  MODIFY_REG(reg, 0xF0F0, ((DUMMY_CLOCK_CYCLES_READ_QUAD << 4) |
                           (DUMMY_CLOCK_CYCLES_READ_QUAD << 12)));

  /* Configure the write volatile configuration register command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	  Error_HandlerQSPI("WRITE_VOL_CFG_REG_CMD");
  }

  /* Transmission of the data */
  if (HAL_QSPI_Transmit(hqspi, (uint8_t *)(&reg), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	  Error_HandlerQSPI("Transmit data");
  }

}

/**
  * @brief  This function set the QSPI memory in 4-byte address mode
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_EnterFourBytesAddress(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef s_command;

  /* Initialize the command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = ENTER_4_BYTE_ADDR_MODE_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* Enable write operations */
  QSPI_WriteEnable(hqspi);

  /* Send the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	  Error_HandlerQSPI("EnterFourBytesAddress");
  }

  /* Configure automatic polling mode to wait the memory is ready */
  QSPI_AutoPollingMemReady(hqspi);

}

#endif


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	rx_done = 1;

	HAL_UART_Transmit(&huart1, (uint8_t *)"RECV\n", 5, HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1, rx_buf, sizeof(rx_buf) / sizeof(rx_buf[0]), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1, (uint8_t *)"\n", 1, HAL_MAX_DELAY);
}


#if TEST_USB_HOST

#endif

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	printf("!!!! ERROR !!!!\n");
	//while(1);
  /* USER CODE END Error_Handler_Debug */
}

void Error_HandlerQSPI(const char* msg)
{
	printf("QSPI ERROR: %s\n", msg);
	while(1);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
