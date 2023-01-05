#ifndef _BOARD_FLASH_H_
#define _BOARD_FLASH_H_

/*********************************************************************
 * INCLUDES
 */
#include "stdint.h"

/*********************************************************************
 * DEFINITIONS
 */
#define FLASH_READ            	    0x00
#define FLASH_WRITE				    0x01

#define USER_FLASH_ADDR		        0x20000

/*********************************************************************
 * API FUNCTIONS
 */
void Flash_UserRead(uint8_t *pData, uint16_t dataLen);
void Flash_UserWrite(uint8_t *pData, uint16_t dataLen);

#endif /* _BOARD_FLASH_H_ */
