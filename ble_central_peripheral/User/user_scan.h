/**
 *****************************************************************************
 * @file    user_scan.h
 *
 * @brief    -
 *
 *****************************************************************************
*/
#ifndef _USER_SCAN_H_
#define _USER_SCAN_H_

/*********************************************************************
 * INCLUDES
 */
#include "app.h"

/*********************************************************************
 * DEFINITIONS
 */
#define PRESENT_SCAN						0x01			// 正在侦测
#define NOT_PRESENT_SCAN 					0x00			// 未在侦测

#define RSSI_EXPECT_VALUE            		60            	// 恢复出厂设置信号强度值

// 获取设备名称
#define GET_DEVICE_NAME(inData, inLen, outData)				FindAdTypeDataFromScanResulte(GAP_AD_TYPE_COMPLETE_NAME,inData,inLen,outData) || FindAdTypeDataFromScanResulte(GAP_AD_TYPE_SHORTENED_NAME,inData,inLen,outData)
// 获取AD_TYPE为用户自定义类型的广播包内容
#define GET_USER_DEFAULT_DATA(inData, inLen, outData)		FindAdTypeDataFromScanResulte(GAP_AD_TYPE_MANU_SPECIFIC_DATA,inData,inLen,outData)

/*********************************************************************
 * TYPEDEFS
 */
typedef struct
{
    uint8_t macAddr[6];
	uint8_t rssi;
    uint8_t len;
	uint8_t data[31];
}ScanData_Msg_t;

typedef struct
{
    uint8_t length;
	uint8_t data[31];
	uint8_t macAddr[6];
	uint8_t rssi;	
} AdTypeData_t;

typedef struct
{
    uint8_t macAddr[6];
	uint8_t rssi;
}ScanFilterData_t;


/*********************************************************************
 * API FUNCTIONS
 */
void EnableScan(void);
void DisableScan(void);
bool GetScanStatus(void);
int GetAdvReport(ke_msg_id_t const msgid, adv_report_t const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id);
bool FindAdTypeDataFromScanResulte(uint8_t adType, uint8_t *advData, uint8_t len, AdTypeData_t *typeData);
bool CheckDeviceStatusIfForward(void);

#endif /* _USER_SCAN_H_ */
