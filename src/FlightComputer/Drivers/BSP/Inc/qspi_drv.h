//qspi_drv.h

#ifndef QSPI_DRV_H
#define QSPI_DRV_H

#include "stm32h7xx_hal.h"

#define MAX_READ_SIZE                        64
#define DUMMY_CLOCK_CYCLES_READ              8
#define DUMMY_CLOCK_CYCLES_READ_QUAD         10

#define WRITE_ENABLE_CMD                     0x06
#define READ_STATUS_REG_CMD                  0x05
#define ENTER_4_BYTE_ADD_CMD				 0xB7
#define WRITE_VOL_CFG_REG_CMD                0x81
#define SECTOR_ERASE_CMD                     0xD8
#define CHIP_ERASE_CMD						 0xC7 // BULK_RASE
#define QUAD_IN_FAST_PROG_CMD                0x32
#define READ_VOL_CFG_REG_CMD                 0x85 // READ_VOLATILE_CONFIGURAITON_REGISTER
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define RESET_NABLE_CMD						 0x66
#define RESET_EXECUTE_CMD					 0x99

#define QUAD_INOUT_FAST_READ_CMD             0xEB
#define WRITE_DISABLE_CMD                    0x04
#define WRITE_STATUS_REG_CMD                 0x01
#define SECTOR_ERASE_4_BYTE_ADDR_CMD         0xDC
#define SUBSECTOR_ERASE_CMD                  0x20
#define SUBSECTOR_ERASE_4_BYTE_ADDR_CMD      0x21
#define EXT_QUAD_IN_FAST_PROG_CMD            0x38 /*0x38*/
#define QUAD_IN_FAST_PROG_4_BYTE_ADDR_CMD    0x34



#define QSPI_BANK_ADDR						 (0x90000000)
#define QSPI_SECTOR_SIZE                     (1024*64)
#define QSPI_SUBSECTOR_SIZE                  (1024*4)
#define QSPI_SUBSECTOR_COUNT                 (16383)

#define BLOCK_SIZE                           QSPI_SUBSECTOR_SIZE

#define QSPI_FAT_SECTOR_COUNT 				 (64*1024*1024/512)

#define  QSPI_STATUS_OK 					1
#define  QSPI_STATUS_ERROR 					0

#define QSPI_COMMAND_TIMEOUT                 1000


typedef enum 
{
    _QSPI_STATUS_OK = QSPI_STATUS_OK,
    _QSPI_STATUS_ERROR = QSPI_STATUS_ERROR
} QSPI_STATUS;


#ifdef __cplusplus
extern "C"
{
#endif

QSPI_STATUS 	QSPI_Driver_init();
uint8_t 		QSPI_Driver_state();
uint8_t 		QSPI_Check_avaliable();
uint8_t 		QSPI_Driver_locked();

QSPI_STATUS 	QSPI_Driver_read(uint8_t* buff, uint32_t address, uint32_t size);
QSPI_STATUS 	QSPI_Driver_write(uint8_t *buf, uint32_t address, uint32_t size);
QSPI_STATUS 	QSPI_Driver_erase_subsector(uint32_t address);
QSPI_STATUS 	QSPI_Driver_erase(uint32_t address, uint32_t size);

//QSPI_STATUS 	QSPI_EnableMemoryMappedMode(void);


#ifdef __cplusplus
}
#endif


#endif
