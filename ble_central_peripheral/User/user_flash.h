/**===========================================================================
  Copyright (C) ALMSound Technologies Co., Ltd. All rights reserved.

  @file     user_flash.h
  @brief    本文件是用户flash数据
  @author   wude
  @version  r0.1
  @date     2021/11/10
  @license ALMSound (ALM)
----------------------------------------------------------------------------
  Remark: (备注描述)
----------------------------------------------------------------------------
                                History
----------------------------------------------------------------------------
  <Date>     | <Version> | <Author>       | <Description>
-------------|-----------|----------------|---------------------------------
  2021/11/10 | r0.1      | wude           | 创建
-------------|-----------|----------------|---------------------------------
             |           |                |
-------------|-----------|----------------|---------------------------------
             |           |                |
-------------|-----------|----------------|---------------------------------
             |           |                |
============================================================================*/

#ifndef _USER_FLASH_H_
#define _USER_FLASH_H_

/*********************************************************************
 * INCLUDES
 */
#include "app.h"

#include "user_config.h"

/*********************************************************************
 * DEFINITIONS
 */


#define ADV_INTERVAL_UNIT                   		100             // 广播间隔默认单位 100ms

#define BEACON_STATUS_SET							0x01			// 信标状态值置1操作
#define BEACON_STATUS_CLEAR							0x02			// 信标状态值置0操作
#define BEACON_ADV_STATUS							0x01			// 信标广播状态
#define BEACON_SCAN_STATUS							0x02			// 信标扫描状态
#define BEACON_LOW_BATTERY							0x04			// 信标低电量告警

#define ADV_INTERVAL_M_UINT                         10              // 广播间隔时间倍率单位(*10ms)

#define SEND_ADDR_ADV

#define USER_FALSH_SIZE     (sizeof(TotalConfigData_t))
	
#define NOT_ERASE				1			// 未擦
#define YES_ERASE				0			// 已擦

/*********************************************************************
 * TYPEDEFS
 */
 /* 初始化数据 */
typedef struct
{
    uint8_t length;												// 长度
    uint8_t name[11];											// 设备名称	
} BleNameData_t;

typedef struct
{
    uint8_t length;							        // 长度
    uint8_t advType;                                // 过滤的广播类型,0-广播数据，1-扫描响应，2-广播+扫描响应
    uint8_t name[10];								// 过滤名字	
} BleNameFilter_t;

typedef struct
{
    uint8_t length;							        // 长度
    uint8_t advType;                                // 过滤的广播类型,0-广播数据，1-扫描响应，2-广播+扫描响应
    uint8_t addr[6];								// 蓝牙地址	
} BleMacAddrData_t;

typedef struct 
{
	BleNameFilter_t deviceNameFilter[FILTER_DEV_NUM_MAX];	    // 设备名过滤数据
    BleMacAddrData_t deviceAddrFilter[FILTER_DEV_NUM_MAX];      // 设备地址过滤数据
} FilterDeviceData_t;

typedef struct
{
    uint8_t length;
	uint8_t data[31];
} ConfigurationAdvData_t;										// 配置广播数据

typedef struct
{
    uint16_t advInterval;                                        // 广播间隔
    uint8_t txPower;                                            // 发射功率
} AdvIntervalData_t;	

// 广播参数
typedef struct 
{
    AdvIntervalData_t advIntervalData;
	ConfigurationAdvData_t configurationAdvData;
} AdvParamsData_t;

// 扫描参数
typedef struct 
{
    uint8_t scanEnble;
    uint8_t scanInterval;
    uint16_t scanWindows;
} ScanParamsData_t;
//--------------------------------------------------------------------------------------------
typedef struct
{
    /* 网络配置状态：0 初次配网（未发配网呼叫信标;未配网）;
     *               1 配网中（已配置发配网呼叫信标,等待发送;未配网）;
     *               2 配网中（收到应答,开始建立协同配网;未配网）;
     *               3 配网中（已配置发建立协同配网信标;已配网）;
     *               4 已配网 */
    uint8_t networkConfigState;
    uint8_t statusType;                                 				// 状态类型：0x01：尚未配网;0x02：已配网
    uint8_t networkVerificationCode[6];								    // 配网验证码
	/* 未配网时为配网参数;
     * 已配网时为选字节偏移 + 单字节位选码 + appId */
    uint8_t networkParameter[4];
	uint8_t domainAddress[6];											// 主机域地址
	uint8_t groupNumber;												// 群组序码
	uint8_t hostMac[6];												    // 主机地址
	uint8_t expansionParameter1;
	uint8_t expansionParameter2;
	uint8_t expansionParameter3;
} JoinNetworkData_t;

// 遥控器配网信息
typedef struct
{
	uint8_t networkConfigState;									// 配置状态 0-未配网 1-已配网
	uint8_t hostMac[6];											// Mac地址
	uint8_t touchPermissionCode[6];								// 触控权限码
	uint8_t groupNumber;											// 序码
	uint8_t byteOffset;											// 位选字节偏移
	uint8_t bitOffset;											// 单字节位选码
} TelecontrolData_t;


typedef struct 
{
	uint8_t red;													// RGBW-red红色
	uint8_t green;												// RGBW-green绿色
	uint8_t blue;													// RGBW-blue蓝色
	uint8_t white;												// RGBW-white白色
} RGBWData_t;

//typedef struct 
//{
////----【红色，绿色，蓝色，白色，频率, 持续时间】-----
//	uint8_t red;
//	uint8_t green;
//	uint8_t blue;
//	uint8_t white;
//	uint16_t frequency;               //频率
//	uint16_t time_of_duration;        //持续时间
//} CofingData;

typedef struct 
{
	RGBWData_t sceneMode[8];
	uint8_t DimmingDataCofing[16][5];                           //特征服务配置灯关数据
	uint8_t dimming_time_of_duration;                           //特征服务配置灯光闪烁持续时间
	uint8_t dimmingDataCofingFlag;                              //配置状态
} DimmingModeData_t;


typedef struct
{
	JoinNetworkData_t joinNetworkData;							// 配网数据
	TelecontrolData_t telecontrolData;							// 遥控数据
	DimmingModeData_t dimmingModeData;							// 调光数据
} InitData_t;

typedef struct
{
    InitData_t initData;
//	BleNameData_t bleNameData;
//	FilterDeviceData_t filterData;						// 过滤设备数据
//    AdvParamsData_t advParamsData;
//    ScanParamsData_t scanParam;
} TotalConfigData_t;
//---------------------------------------------------------------------------------------------

// 广播类型标志
typedef struct 
{
	bool tAdvTypeFlag;								// 开机定时更改广播类型标志
    bool bLinkFlag;                                 // 开机连接标志
} AdvTypeFlag_t;

/*********************************************************************
 * GLOBAL VARIABLES
 */
extern TotalConfigData_t g_totalConfigData;
extern uint8_t g_flashEraseStatus;

/*********************************************************************
 * API FUNCTIONS
 */
void LoadTotalConfigDataFromFlash(void);
void LoadBleAddress(uint8_t *address);
void LoadJoinNetworkData(void);
//void LoadBleNameData(void);
//void LoadFilterDeviceData(void);
void LoadAdvParamsData(void);
void LoadScanParamsData(void);

//void Flash_BleNameDataWrite(const BleNameData_t *bleNameData);
//void Flash_BleNameDataRead(BleNameData_t *bleNameData);
//void Flash_AdvParamDataWrite(const AdvParamsData_t *advParam);
//void Flash_AdvParamDataRead(AdvParamsData_t *advParam);
//void Flash_ScanParamDataWrite(const ScanParamsData_t *scanParam);
//void Flash_ScanParamDataRead(ScanParamsData_t *scanParam);
void Flash_FilterDataWrite(const FilterDeviceData_t *filterData);
void Flash_FilterDataRead(FilterDeviceData_t *filterData);

void Flash_all_erase(void);

void saveTotalConfigDataInFlash(void);

#endif /* _USER_FLASH_H_ */
