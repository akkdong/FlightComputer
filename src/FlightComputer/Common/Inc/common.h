// common.h
//

#ifndef __COMMON_H__
#define __COMMON_H__

#include "stm32h7xx.h"
#include "lwrb/lwrb.h"
#include "lwgps/lwgps.h"
#include "lwshell/lwshell.h"


/* Align X to 4 bytes */
#define MEM_ALIGN(x)                        (((x) + 0x00000003) & ~0x00000003)

/* Shared RAM between 2 cores is SRAM4 in D3 domain */
#define SHD_RAM_START_ADDR                  0x38000000
#define SHD_RAM_LEN                         0x0000FFFF

/* Shared RAM memory map */
/*
+----------------+--------------------------+
| sizeof(lwrb_t) | CM4 TO CM7 Buffer header |
+----------------+--------------------------+
| 10000          | CM4 TO CM7 Buffer        |
+----------------+--------------------------+
| sizeof(lwrb_t) | CM7 TO CM4 Buffer header |
+----------------+--------------------------+
| 10000          | CM7 TO CM4 Buffer        |
+----------------+--------------------------+
| 10000          | Vario state Buffer       |
+----------------+--------------------------+
| 10000          | GPS state Buffer         |
+----------------+--------------------------+
*/

/* Buffer from CM4 to CM7 */
#define BUFF_CM4_TO_CM7_ADDR                MEM_ALIGN(SHD_RAM_START_ADDR)
#define BUFF_CM4_TO_CM7_LEN                 MEM_ALIGN(sizeof(lwrb_t))
#define BUFFDATA_CM4_TO_CM7_ADDR            MEM_ALIGN(BUFF_CM4_TO_CM7_ADDR + BUFF_CM4_TO_CM7_LEN)
#define BUFFDATA_CM4_TO_CM7_LEN             MEM_ALIGN(0x00001000)

/* Buffer from CM7 to CM4 */
#define BUFF_CM7_TO_CM4_ADDR                MEM_ALIGN(BUFFDATA_CM4_TO_CM7_ADDR + BUFFDATA_CM4_TO_CM7_LEN)
#define BUFF_CM7_TO_CM4_LEN                 MEM_ALIGN(sizeof(lwrb_t))
#define BUFFDATA_CM7_TO_CM4_ADDR            MEM_ALIGN(BUFF_CM7_TO_CM4_ADDR + BUFF_CM7_TO_CM4_LEN)
#define BUFFDATA_CM7_TO_CM4_LEN             MEM_ALIGN(0x00001000)

/*
 * Vario state buffer
 *
 * - CM4 fill this buffer
 * - CM7 reference this buffer
 *
 */
#define BUFF_VARIO_STATE_ADDR               MEM_ALIGN(BUFFDATA_CM7_TO_CM4_ADDR + BUFFDATA_CM7_TO_CM4_LEN)
#define BUFF_VARIO_STATE_LEN                MEM_ALIGN(0x00001000)

/*
 * GPS state buffer
 *
 * - CM4 fill this buffer
 * - CM7 reference this buffer
 *
 */
#define BUFF_GPS_STATE_ADDR 	            MEM_ALIGN(BUFF_VARIO_STATE_ADDR + BUFF_VARIO_STATE_LEN)
#define BUFF_GPS_STATE_LEN                  MEM_ALIGN(0x00001000)


/* Define semaphores */
#if UNDEFINE
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0 */
#endif

#ifndef HSEM_ID_1
#define HSEM_ID_1 (1U) /* HW semaphore 1 */
#endif

#ifndef HSEM_ID_2
#define HSEM_ID_2 (2U) /* HW semaphore 2 */
#endif

#ifndef HSEM_ID_3
#define HSEM_ID_3 (3U) /* HW semaphore 3 */
#endif

#ifndef HSEM_ID_4
#define HSEM_ID_4 (4U) /* HW semaphore 4 */
#endif
#endif


#define HSEM_TAKE_RELEASE(_id_)             do { HAL_HSEM_FastTake((_id_)); HAL_HSEM_Release((_id_), 0); } while (0)

#define HSEM_WAKEUP_CPU2                    0
#define HSEM_WAKEUP_CPU2_MASK               __HAL_HSEM_SEMID_TO_MASK(HSEM_WAKEUP_CPU2)

#define HSEM_CM4_TO_CM7                     1
#define HSEM_CM4_TO_CM7_MASK                __HAL_HSEM_SEMID_TO_MASK(HSEM_CM4_TO_CM7)

#define HSEM_CM7_TO_CM4                     2
#define HSEM_CM7_TO_CM4_MASK                __HAL_HSEM_SEMID_TO_MASK(HSEM_CM7_TO_CM4)

#define HSEM_VAIO_UPDATE					3	// CM4 vario-update event
#define HSEM_VAIO_UPDATE_MASK                __HAL_HSEM_SEMID_TO_MASK(HSEM_VAIO_UPDATE)

#define HSEM_GPS_UPDATE						4	// CM4 gps-update event
#define HSEM_GPS_UPDATE_MASK                __HAL_HSEM_SEMID_TO_MASK(HSEM_GPS_UPDATE)

#define HSEM_LOCK_VARIO_STATE				5
#define HSEM_LOCK_VARIO_STATE_MASK			__HAL_HSEM_SEMID_TO_MASK(HSEM_LOCK_VARIO_STATE)

#define HSEM_GOTO_STANDBY					11
#define HSEM_GOTO_STANDBY_MASK              __HAL_HSEM_SEMID_TO_MASK(HSEM_GOTO_STANDBY)


/* Flags management */
#define WAIT_COND_WITH_TIMEOUT(c, t)        do {        \
    int32_t timeout = (int32_t)(t);                     \
    while ((c) && timeout-- > 0) {}                     \
    if (timeout < 0) {                                  \
        Error_Handler();                                \
    }                                                   \
} while (0)

#endif // __COMMON_H__
