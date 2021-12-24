/*
 * sdram.h
 *
 *  Created on: 2021. 12. 24.
 *      Author: akkdong
 */

#ifndef INC_SDRAM_H_
#define INC_SDRAM_H_



#define SDRAM_ADDRESS   							((uint32_t) 0xD0000000)
#define SDRAM_BANK_ADDR                 		 	((uint32_t)0xD0000000)
#define SDRAM_DEVICE_ADDR         					0xD0000000U

#define SDRAM_MEMORY_WIDTH            			 	FMC_SDRAM_MEM_BUS_WIDTH_16
#define SDCLOCK_PERIOD                			 	FMC_SDRAM_CLOCK_PERIOD_3

#define SDRAM_TIMEOUT     						 	((uint32_t)0xFFFF)

#define BUFFER_SIZE         					 	((uint32_t)0x0100)
#define WRITE_READ_ADDR     					 	((uint32_t)0x0800)
//#define REFRESH_COUNT      				 	 	((uint32_t)0x056A)   /* SDRAM refresh counter (90MHz SDRAM clock) */
#define REFRESH_COUNT 							 	((uint32_t)0x0603)/* SDRAM refresh counter (100Mhz SD clock) */

#define SDRAM_MODEREG_BURST_LENGTH_1             	((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             	((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             	((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             	((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      	((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     	((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              	((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              	((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    	((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED 	((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     	((uint16_t)0x0200)




HAL_StatusTypeDef SDRAM_Do_InitializeSequence();


void test_sdram();


#endif /* INC_SDRAM_H_ */
