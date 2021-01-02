/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * @file    qspi_diskio.c
  * @brief   This file includes a diskio driver skeleton to be completed by the user.
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

#ifdef USE_OBSOLETE_USER_CODE_SECTION_0
/*
 * Warning: the user section 0 is no more in use (starting from CubeMx version 4.16.0)
 * To be suppressed in the future.
 * Kept to ensure backward compatibility with previous CubeMx versions when
 * migrating projects.
 * User code previously added there should be copied in the new user sections before
 * the section contents can be deleted.
 */
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */
#endif

/* USER CODE BEGIN DECL */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "ff_gen_drv.h"
#include "qspi_drv.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;

/* USER CODE END DECL */

/* Private function prototypes -----------------------------------------------*/
DSTATUS QSPI_initialize (BYTE pdrv);
DSTATUS QSPI_status (BYTE pdrv);
DRESULT QSPI_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
  DRESULT QSPI_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  DRESULT QSPI_ioctl (BYTE pdrv, BYTE cmd, void *buff);
#endif /* _USE_IOCTL == 1 */

Diskio_drvTypeDef  QSPIDISK_Driver =
{
  QSPI_initialize,
  QSPI_status,
  QSPI_read,
#if  _USE_WRITE
  QSPI_write,
#endif  /* _USE_WRITE == 1 */
#if  _USE_IOCTL == 1
  QSPI_ioctl,
#endif /* _USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes a Drive
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS QSPI_initialize (
	BYTE pdrv           /* Physical drive nmuber to identify the drive */
)
{
  /* USER CODE BEGIN INIT */
    Stat = STA_NOINIT;

	if (QSPI_Driver_locked())
	{
		Stat &= ~STA_NOINIT;
	}
	else if(QSPI_Driver_state() == 1)
	{
		Stat &= ~STA_NOINIT;
	}
	else if(  QSPI_Driver_init() == QSPI_STATUS_OK)
	{
		Stat &= ~STA_NOINIT;
	}

    return Stat;
  /* USER CODE END INIT */
}

/**
  * @brief  Gets Disk Status
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS QSPI_status (
	BYTE pdrv       /* Physical drive number to identify the drive */
)
{
  /* USER CODE BEGIN STATUS */
    Stat = STA_NOINIT;

    if(QSPI_Driver_state())
    {
        Stat &= ~STA_NOINIT;
    }

    return Stat;
  /* USER CODE END STATUS */
}

/**
  * @brief  Reads Sector(s)
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT QSPI_read (
	BYTE pdrv,      /* Physical drive nmuber to identify the drive */
	BYTE *buff,     /* Data buffer to store read data */
	DWORD sector,   /* Sector address in LBA */
	UINT count      /* Number of sectors to read */
)
{
  /* USER CODE BEGIN READ */
    uint32_t bufferSize = (BLOCK_SIZE * count);
    uint32_t address =  (sector * BLOCK_SIZE);
    uint32_t data_read = 0;
    //printf("read %d blocks, sector %d\n",count,sector);
    while(data_read < bufferSize)
    {
        uint32_t incr = bufferSize < MAX_READ_SIZE ? bufferSize : MAX_READ_SIZE;
        if(QSPI_Driver_read(&buff[data_read],address,incr) != QSPI_STATUS_OK)
        {
            return RES_ERROR;
        }
        data_read += incr;
        address += incr;
    }

    return RES_OK;
  /* USER CODE END READ */
}

/**
  * @brief  Writes Sector(s)
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if _USE_WRITE == 1
DRESULT QSPI_write (
	BYTE pdrv,          /* Physical drive nmuber to identify the drive */
	const BYTE *buff,   /* Data to be written */
	DWORD sector,       /* Sector address in LBA */
	UINT count          /* Number of sectors to write */
)
{
  /* USER CODE BEGIN WRITE */
  /* USER CODE HERE */
	for (UINT i = 0; i < count; i++)
	{
		uint32_t addr = sector * BLOCK_SIZE;
		if (QSPI_Driver_erase_subsector(addr) != QSPI_STATUS_OK)
			return RES_ERROR;

		const BYTE* dest = buff + (i * BLOCK_SIZE);
		if (QSPI_Driver_write((uint8_t *)dest, addr, BLOCK_SIZE) != QSPI_STATUS_OK)
			return RES_ERROR;
	}
    return RES_OK;
  /* USER CODE END WRITE */
}
#endif /* _USE_WRITE == 1 */

/**
  * @brief  I/O control operation
  * @param  pdrv: Physical drive number (0..)
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if _USE_IOCTL == 1
DRESULT QSPI_ioctl (
	BYTE pdrv,      /* Physical drive nmuber (0..) */
	BYTE cmd,       /* Control code */
	void *buff      /* Buffer to send/receive control data */
)
{
  /* USER CODE BEGIN IOCTL */
    DRESULT res = RES_ERROR;

    if (Stat & STA_NOINIT) return RES_NOTRDY;

    switch (cmd)
    {
        /* Make sure that no pending write process */
    case CTRL_SYNC :
        res = RES_OK;
        break;

        /* Get number of sectors on the disk (DWORD) */
    case GET_SECTOR_COUNT :
        *(DWORD*)buff = QSPI_SUBSECTOR_COUNT;
        res = RES_OK;
        break;

        /* Get R/W sector size (WORD) */
    case GET_SECTOR_SIZE :
        *(WORD*)buff = QSPI_SUBSECTOR_SIZE;
        res = RES_OK;
        break;

        /* Get erase block size in unit of sector (DWORD) */
    case GET_BLOCK_SIZE :
        *(DWORD*)buff = QSPI_SUBSECTOR_SIZE;
        break;

    default:
        res = RES_PARERR;
    }

    return res;
  /* USER CODE END IOCTL */
}
#endif /* _USE_IOCTL == 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
