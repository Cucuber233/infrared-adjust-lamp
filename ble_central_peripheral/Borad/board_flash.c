/*********************************************************************
 * INCLUDES
 */
#include "stdint.h"
#include "flash_wrapper.h"
#include "board_flash.h"

static void flashReadOrWriteContrl(uint32_t flashAddr, uint8_t readWriteFlag, uint8_t *pData, uint16_t dataLen);

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/**
 @brief flash读
 @param pData -[out] 指向需要操作的数据
 @param dataLen -[in] 数据长度
 @return 无
*/
void Flash_UserRead(uint8_t *pData, uint16_t dataLen)
{
    flashReadOrWriteContrl(USER_FLASH_ADDR, FLASH_READ, pData, dataLen);
}

/**
 @brief flash写
 @param pData -[in] 指向需要操作的数据
 @param dataLen -[in] 数据长度
 @return 无
*/
void Flash_UserWrite(uint8_t *pData, uint16_t dataLen)
{
    flashReadOrWriteContrl(USER_FLASH_ADDR, FLASH_WRITE, pData, dataLen);
}

/*********************************************************************
 * LOCAL FUNCTIONS
 */
/**
 @brief flash读写内存操作
 @param flashAddr -[in] 闪存地址
 @param readWriteFlag -[in] 读写操作标志
 @param pData -[in&out] 指向需要操作的数据
 @param dataLen -[in] 数据长度
 @return 无
*/
static void flashReadOrWriteContrl(uint32_t flashAddr, uint8_t readWriteFlag, uint8_t *pData, uint16_t dataLen)
{
    if(readWriteFlag == FLASH_READ)                       							    // 读取数据
    {
		flash_multi_read(flashAddr, dataLen, pData);
    }
    else 																				// 写入数据
    {
		flash_erase(flashAddr, Sector_Erase);
        flash_program(flashAddr, dataLen, pData);
    }
}
/****************************************************END OF FILE****************************************************/
