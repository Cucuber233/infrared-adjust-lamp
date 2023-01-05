/*********************************************************************
 * INCLUDES
 */
#include "app.h"
#include "ble.h"
#include "gapm_task.h"
#include "nvds_in_ram.h"

#include "user_advertising.h"
#include "aba_protocol.h"

static void userAdvertisingStart(void);
static void advertising_advdata_update(void);

/*********************************************************************
 * GLOBAL VARIABLES
 */
// 广播数据
uint8_t g_advertisingData[] =
{
    0x1B, 																
    GAP_AD_TYPE_MANU_SPECIFIC_DATA, 												
    0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
	
};
// 扫描响应数据BLE_GAP_ADV_SET_DATA_SIZE_MAX
uint8_t g_scanResponseData[] =
{
    0x12,
	GAP_AD_TYPE_MANU_SPECIFIC_DATA,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	
    0x08, 
    GAP_AD_TYPE_COMPLETE_NAME,
    'B','r','i','g','h','t','#'
};

/*********************************************************************
 * LOCAL VARIABLES
 */
// 广播状态, 0 - 未广播 1 - 正在广播
static bool s_advertisingFlag = false;
// 连接状态, 0 - 未连接 1 - 连接
static bool s_isConnectedFlag = false;

// 广播参数
static struct gapm_start_advertise_cmd advParam =
{
    .op.addr_src    = GAPM_STATIC_ADDR,
    .channel_map    = ADV_ALL_CHNLS_EN,//ADV_ALL_CHNLS_EN,ADV_CHNL_37_EN
    .intv_max   = 800,                              //unit is 625 us
    .intv_min   = 800,                              //unit is 625 us
    .op.code    = GAPM_ADV_UNDIRECT,//GAPM_ADV_UNDIRECT,GAPM_ADV_NON_CONN
    .info.host.mode = GAP_GEN_DISCOVERABLE,
    .info.host.adv_data_len = sizeof(g_advertisingData),
    .info.host.scan_rsp_data_len  = sizeof(g_scanResponseData),
    .info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY,
};

/*********************************************************************
 * EXTERN FUNCTIONS
 */


/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/**
 @brief 初始化广播数据包
 @param pInit - 广播数据初始化结构体
 @return 无
*/
void InitAdvertisingData(void)
{   
#if 0
    uint8_t addr[6] ={0};
    uint8_t addrLen = NVDS_LEN_BD_ADDRESS;             
    if(nvds_get(NVDS_TAG_BD_ADDRESS, &addrLen, addr) == NVDS_OK)       // 获取本机地址
    {
        
    }
    
    g_advertisingData[2] = 0xC7;//0x4C;
    g_advertisingData[3] = 0x00;
    uint8_t uuid[16] = {0xFD, 0xA5, 0x06, 0x93, 0xA4, 0xE2, 0x4F, 0xB1, 0xAF, 0xCF, 0xC6, 0xEB, 0x07, 0x64, 0x78, 0x25};
	g_advertisingData[4] = 0x01;//0x02;
	g_advertisingData[5] = 0x20;//0x15;
//	memcpy(&g_advertisingData[6], uuid, sizeof(uuid));
    g_advertisingData[6] = 0x15;
    memcpy(&g_advertisingData[7], addr, 6);
    
    uint8_t temp[15] = {0x79,0x67,0xf7,0xdb,0x34,0xc4,0x03,0x8e,0x5c,0x0b,0xaa,0x97,0x30,0x56,0xe6};
    memcpy(&g_advertisingData[13], temp, sizeof(temp));

#if 0
	g_advertisingData[22] = 0x27;
	g_advertisingData[23] = 0xC4;
	
#if defined BEACON_A
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0x33;
#elif defined BEACON_B
	g_advertisingData[24] = 0xB5;
	g_advertisingData[25] = 0x3E;
#elif defined BEACON_C
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0x3F;
#elif defined BEACON_D
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0xA4;
#elif defined BEACON_E
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0xA3;
#elif defined BEACON_F
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0x32;
#endif	

	g_advertisingData[26] = 0xA5;
#endif
#endif

#if 0
    advParam.info.host.adv_data_len = sizeof(g_advertisingData)-1;
    g_advertisingData[0] = advParam.info.host.adv_data_len-1;
    g_advertisingData[2] = 0x4C;
    g_advertisingData[3] = 0x00;
    uint8_t uuid[16] = {0xFD, 0xA5, 0x06, 0x93, 0xA4, 0xE2, 0x4F, 0xB1, 0xAF, 0xCF, 0xC6, 0xEB, 0x07, 0x64, 0x78, 0x25};
	g_advertisingData[4] = 0x02;
	g_advertisingData[5] = 0x15;
	memcpy(&g_advertisingData[6], uuid, sizeof(uuid));
	g_advertisingData[22] = 0x27;
	g_advertisingData[23] = 0xC4;
	
#if defined BEACON_A
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0x33;
#elif defined BEACON_B
	g_advertisingData[24] = 0xB5;
	g_advertisingData[25] = 0x3E;
#elif defined BEACON_C
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0x3F;
#elif defined BEACON_D
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0xA4;
#elif defined BEACON_E
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0xA3;
#elif defined BEACON_F
	g_advertisingData[20] = 0xB5;
	g_advertisingData[21] = 0x32;
#endif	

	g_advertisingData[26] = 0xA5;
#endif
}

/**
 @brief 初始化扫描应答包
 @param pInit - 广播数据初始化结构体
 @return 无
*/
void InitScanResponseData(void)
{
//    uint8_t addr[6] = {0};
//    LoadBleAddress(addr);
//	g_scanResponseData[2] = 0xA0; 
//    memcpy(&g_scanResponseData[3], addr, 6);
	
	
//	if(g_totalConfigData.initData.joinNetworkData.networkConfigState == COMPLETE_JOIN_NETWORK )
//	{
//		g_scanResponseData[2] = 0x02;           //已配网
////		memset(&g_scanResponseData[3], g_totalConfigData.initData.joinNetworkData.networkVerificationCode, 6);   //配网码初始化
////		g_scanResponseData[9] = g_totalConfigData.initData.joinNetworkData.networkParameter[0];         //序码初始化
////		g_scanResponseData[10] = g_totalConfigData.initData.joinNetworkData.networkParameter[0];;             //单字节位选码初始化
//	}		
//	else
//	{
	g_scanResponseData[2] = 0x01;            //未配网
//		memset(&g_scanResponseData[3], 0, 6);   //配网码初始化
//		g_scanResponseData[9] = 0;              //序码初始化
//		g_scanResponseData[10] = 0;             //单字节位选码初始化
//	}	
	g_scanResponseData[15] = 0x00;    //1状态
	g_scanResponseData[16] = 0x00;     //2状态
	g_scanResponseData[17] = 0x00;    //3状态
	g_scanResponseData[18] = 0x00;     //4状态
	
	g_scanResponseData[11] = 0x00;      //状态变化累计

	g_scanResponseData[13] = 0x50;     // 设备类型: 灯端调控器
	g_scanResponseData[14] = 0x04;     // 状态类型: 信标状态	
	
//	if(g_totalConfigData.initData.joinNetworkData.statusType == 0x02)
//	{
//		update_network(); 
//		return ;
//	}
//	else if(g_totalConfigData.initData.telecontrolData.networkConfigState == 0x01)
//	{
//		UpdateSetNetworkResponseData();
//		return ;
//	}
	memset(g_scanResponseData + JOIN_NETWORK_INFO_STARTING_LOCATION , 0, 8);
	
//	LOG_RAW("networkConfigState:%x\t %x", g_totalConfigData.initData.joinNetworkData.networkConfigState, g_scanResponseData[2] );
//	LOG_RAW("g_totalConfigData.initData.joinNetworkData.networkParameter:%x\n", g_scanResponseData[SINGLE_BIT_SELECT_CODE_LOCATION] );
}

/**
 @brief 开启广播
 @param 无
 @return 无
*/
void EnableAdvertising(void)
{
	if(!GetBleConnectStatus())		// 非连接状态
	{
		advertising_advdata_update();
        userAdvertisingStart();
		s_advertisingFlag = true;
	}
}

/**
 @brief 关闭广播
 @param 无
 @return 无
*/
void DisableAdvertising(void)
{
	if(!GetBleConnectStatus())		// 非连接状态
	{
        ble_advertising_stop();
		s_advertisingFlag = false;
	}
}

/**
 @brief 获取广播状态
 @param 无
 @return 1 - 正在广播, 0 - 未在广播
*/
bool GetAdvertisingStatus(void)
{
	return s_advertisingFlag;
}

/**
 @brief 更新广播内容并开启广播
 @param 无
 @return 无
*/
void UpdateAdvData(void)
{
	if(!GetBleConnectStatus())		// 非连接状态
	{
        ble_advertising_stop();

//		advertising_advdata_update();

//		userAdvertisingStart();
        bx_defer(user_service_id, USM_APP_START_ADV, 0, 0, 1);      // 注意：RF04芯片关闭广播后再开启广播需要延时一段时间才能重新启动广播
		s_advertisingFlag = true;
	}
}

/**
 @brief 设置广播间隔
 @param size -[in] 间隔时间
 @return 无
*/
void SetAdvInterval(uint16_t advInterval)
{
    advInterval = advInterval / 0.625;
    advParam.intv_min = advInterval;
    advParam.intv_max = advInterval;
}

/**
 @brief 设置总状态变化累加
 @param 无
 @return 无
*/
void SetStatusVariety(void)
{
	static uint8_t switchStatus;
	
	switchStatus += 1;
	if(switchStatus == 0xff)
	{
		switchStatus = 1;
	}
	// 更新总状态
	*(g_scanResponseData + SR_SWITCH_TYPE_LOCATION - 3) = switchStatus;
}

///**
// @brief 更新开关状态变化
// @param 无
// @return 无
//*/
//void SetStatesRelay(uint8_t *data_relay_state)
//{
//	memcpy( g_scanResponseData + 15, data_relay_state, 2);
//}

/**
 @brief 设置BLE连接状态
 @param status -[in] true - 已连接；false - 已断开
 @return 无
*/
void SetBleConnectStatus(bool status)
{
	s_isConnectedFlag = status;
}

/**
 @brief 获取BLE连接状态
 @param 无
 @return true - 已连接；false - 已断开
*/
bool GetBleConnectStatus(void)
{
	return s_isConnectedFlag;
}

/**
 @brief 设置蓝牙名字
 @param name -[in] 蓝牙名字
 @param len -[in] 长度
 @return 无
*/
void SetBleName(uint8_t *name, uint8_t len)
{
    if(len == 0)
        return;
    advParam.info.host.scan_rsp_data_len = g_scanResponseData[0]+1+len+2;
    *(g_scanResponseData + 19) = len+1;             // AD_Len
    
    memcpy(&g_scanResponseData[21], name, len);     // AD_Data
}

/**
 @brief 设置广播数据
 @param advData -[in] 广播数据
 @param len -[in] 长度
 @return 无
*/
void SetConfigurationAdvData(uint8_t *advData, uint8_t len)
{
    if(len > 26)
        len = 26;
    advParam.info.host.adv_data_len = len+2;
    g_advertisingData[0] = len+1;
    memcpy(&g_advertisingData[2], advData, len);
}

/**
 @brief 设置转发广播数据(扫描响应包)
 @param pData -[in] 数据
 @param len -[in] 数据长度
 @return 无
*/
void SetForwardAdvData(uint8_t *pData, uint8_t len)
{
    if(len > 29)
        len = 29;
    advParam.info.host.scan_rsp_data_len = len+2;
    g_scanResponseData[0] = len+1;
    memcpy(&g_scanResponseData[2], pData, len);     // AD_Data
}

/**
 @brief 设置广告类型
 @param type -[in] 类型
 @return 无
*/
void SetAdvertiseMode(uint8_t type)
{
    advParam.op.code = type;
}

/*********************************************************************
* LOCAL FUNCTIONS
*/
/**
 @brief 用户广播开启
 @param 无
 @return 无
*/
static void userAdvertisingStart(void)
{
//    struct gapm_start_advertise_cmd adv_data;
//    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
//    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
//    adv_data.intv_max   = 160;//unit is 625 us
//    adv_data.intv_min   = 160;//unit is 625 us
//    adv_data.op.code    = GAPM_ADV_UNDIRECT;
//    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
//    adv_data.info.host.adv_data_len = sizeof(g_advertisingData);
//    adv_data.info.host.scan_rsp_data_len  = sizeof(g_scanResponseData);
//    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    
//    advParam.info.host.adv_data_len = sizeof(g_advertisingData)-1;
//    g_advertisingData[0] = advParam.info.host.adv_data_len - 1;
//    memcpy(advParam.info.host.adv_data, g_advertisingData, sizeof(g_advertisingData));
//    memcpy(advParam.info.host.scan_rsp_data, g_scanResponseData, sizeof(g_scanResponseData));
	
    ble_advertising_start(&advParam);
}

/**
 @brief 更新广播数据
 @param 无
 @return 无
*/
static void advertising_advdata_update(void)
{
    memcpy(advParam.info.host.adv_data, g_advertisingData, sizeof(g_advertisingData));
    memcpy(advParam.info.host.scan_rsp_data, g_scanResponseData, sizeof(g_scanResponseData));
}

/****************************************************END OF FILE****************************************************/
