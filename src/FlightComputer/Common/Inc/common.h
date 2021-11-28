// common.h
//

#ifndef __COMMON_H__
#define __COMMON_H__

#include "stm32h7xx.h"
#include "lwrb/lwrb.h"

/* Align X to 4 bytes */
#define MEM_ALIGN(x)                        (((x) + 0x00000003) & ~0x00000003)

/* Shared RAM between 2 cores is SRAM4 in D3 domain */
#define SHD_RAM_START_ADDR                  0x38000000
#define SHD_RAM_LEN                         0x0000FFFF

/* Buffer from CM4 to CM7 */
#define BUFF_CM4_TO_CM7_ADDR                MEM_ALIGN(SHD_RAM_START_ADDR)
#define BUFF_CM4_TO_CM7_LEN                 MEM_ALIGN(sizeof(lwrb_t))
#define BUFFDATA_CM4_TO_CM7_ADDR            MEM_ALIGN(BUFF_CM4_TO_CM7_ADDR + BUFF_CM4_TO_CM7_LEN)
#define BUFFDATA_CM4_TO_CM7_LEN             MEM_ALIGN(0x00000400)

/* Buffer from CM7 to CM4 */
#define BUFF_CM7_TO_CM4_ADDR                MEM_ALIGN(BUFFDATA_CM4_TO_CM7_ADDR + BUFFDATA_CM4_TO_CM7_LEN)
#define BUFF_CM7_TO_CM4_LEN                 MEM_ALIGN(sizeof(lwrb_t))
#define BUFFDATA_CM7_TO_CM4_ADDR            MEM_ALIGN(BUFF_CM7_TO_CM4_ADDR + BUFF_CM7_TO_CM4_LEN)
#define BUFFDATA_CM7_TO_CM4_LEN             MEM_ALIGN(0x00000400)


/* Define semaphores */
#define HSEM_TAKE_RELEASE(_id_)             do { HAL_HSEM_FastTake((_id_)); HAL_HSEM_Release((_id_), 0); } while (0)
#define HSEM_WAKEUP_CPU2                    0
#define HSEM_WAKEUP_CPU2_MASK               __HAL_HSEM_SEMID_TO_MASK(HSEM_WAKEUP_CPU2)
#define HSEM_CM4_TO_CM7                     1
#define HSEM_CM4_TO_CM7_MASK                __HAL_HSEM_SEMID_TO_MASK(HSEM_CM4_TO_CM7)
#define HSEM_CM7_TO_CM4                     2
#define HSEM_CM7_TO_CM4_MASK                __HAL_HSEM_SEMID_TO_MASK(HSEM_CM7_TO_CM4)

/* Flags management */
#define WAIT_COND_WITH_TIMEOUT(c, t)        do {        \
    int32_t timeout = (int32_t)(t);                     \
    while ((c) && timeout-- > 0) {}                     \
    if (timeout < 0) {                                  \
        Error_Handler();                                \
    }                                                   \
} while (0)

#endif // __COMMON_H__
