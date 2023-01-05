/*********************************************************************
 * INCLUDES
 */
#include "stdlib.h"
#include "app.h"
#include "ble.h"

#include "user_scan.h"
#include "user_advertising.h"
#include "aba_protocol.h"
#include "board_pwm.h"

/*********************************************************************
 * vlaue
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
// 侦测标志, 0 - 未侦测 1 - 正在侦测
bool s_scanFlag = false;

/* 扫描参数 */
static struct gapm_start_scan_cmd scanParam = 
{
    .op.code = GAPM_SCAN_ACTIVE,   //set scan params
    .op.addr_src = GAPM_STATIC_ADDR,
    .op.state = 0,
    .interval = 80,
    .window = 80,
    .mode = GAP_OBSERVER_MODE,//GAP_GEN_DISCOVERY,GAP_OBSERVER_MODE
    .filter_duplic = SCAN_FILT_DUPLIC_DIS,//SCAN_FILT_DUPLIC_DIS, //filtering rule
    .filt_policy = SCAN_ALLOW_ADV_ALL,
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/**
 @brief 开启扫描
 @param 无
 @return 无
*/
void EnableScan(void)
{
	if(GetBleConnectStatus() == false)		// 非连接状态
	{
		ble_scan_start(&scanParam);
		s_scanFlag = true;
	}
}

/**
 @brief 关闭扫描
 @param 无
 @return 无
*/
void DisableScan(void)
{
	if(GetBleConnectStatus() == false)		// 非连接状态
	{
		ble_scan_stop();
		s_scanFlag = false;
	}
}

/**
 @brief 获取侦测状态
 @param 无
 @return 1 - 正在侦测,0 - 未侦测
*/
bool GetScanStatus(void)
{
	return s_scanFlag;
}

/**
 @brief 获取广播数据
 @param pInit - 广播数据初始化结构体
 @return 无
*/
int GetAdvReport(ke_msg_id_t const msgid, adv_report_t const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id)
{	
//    ScanData_Msg_t scanDataMsg;
//    AdTypeData_t userData = {0};
    uint8_t advType = 0xFE;
    if(param->evt_type == ADV_CONN_DIR_LDC)  // 扫描响应包
        advType = 1;
    else                                     //控制类广播包
	{	

	}
    return (KE_MSG_CONSUMED);
}

/**
 @brief 查找AD_Type数据从扫描到的广播数据中,根据AD_Type提取数据内容
 @param adType -[in] 要查找的AD_Type类型
 @param advData -[in] 广播数据
 @param len -[in] 广播数据总长度
 @param typeData -[out] 如果在广播数据中发现查找的数据类型，数据长度和数据内容将在这里填充
 @return 查找成功返回true，失败返回false
*/
bool FindAdTypeDataFromScanResulte(uint8_t adType, uint8_t *advData, uint8_t len, AdTypeData_t *typeData)
{
	uint8_t index = 0;
	uint8_t *pData;
	
	pData = advData;
	while(index < len)
	{
		uint8_t length = pData[index];
		uint8_t type = pData[index + 1];
		
		if(len < length + 1 || length < 2 || length > 0x1e)
		{
			return false;
		}
		else
		{
			if(type == adType)
			{
				memcpy(&typeData->data, &pData[index + 2], length - 1);
				typeData->length = length - 1;
				return true;
			}
			index += length + 1;
		}	
	}
	return false;
}

/****************************************************END OF FILE****************************************************/
