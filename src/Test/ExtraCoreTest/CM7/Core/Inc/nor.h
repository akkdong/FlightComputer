/*
 * node.h
 *
 *  Created on: 2021. 12. 24.
 *      Author: akkdong
 */

#ifndef INC_NOR_H_
#define INC_NOR_H_


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




int32_t BSP_NOR_EraseBlock(uint32_t Instance, uint32_t BlockAddress);
int32_t BSP_NOR_ReadData(uint32_t Instance, uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize);
int32_t BSP_NOR_WriteData(uint32_t Instance, uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize);


#endif /* INC_NOR_H_ */
