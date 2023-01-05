#ifndef _ABA_PROTOCOL_H_
#define _ABA_PROTOCOL_H_

/*********************************************************************
 * INCLUDES
 */
#include <stdint.h>

/*********************************************************************
 * DEFINITIONS
 */
#define ADV_DATA_TYPE_EVT_LOG					0x06	// 数据包类型：事件日志广播

#define DEV_TYPE_SWITCH							0x01    // 开关
#define DEV_TYPE_PLUG							0x02    // 插座
#define DEV_TYPE_LOCK                   		0x03    // 锁
#define DEV_TYPE_MAGNET_SWITCH					0x04    // 门窗传感器
#define DEV_TYPE_MAGNET_COUNTER					0x40    // 磁感计数器
#define DEV_TYPE_GATEWAY						0x80    // 网关
#define DEV_TYPE_TEMP_SENSOR                    0x41    // 温度传感器
#define DEV_TYPE_DIMMING						0x50	// 灯端调光器

#define EVT_TYPE_FIRST_OPEN						0x01    // 第一路开
#define EVT_TYPE_SECOND_OPEN					0x02    // 第二路开
#define EVT_TYPE_THIRD_OPEN						0x03    // 第三路开
#define EVT_TYPE_FOURTH_OPEN					0x04    // 第四路开
#define EVT_TYPE_FIRST_CLOSE					0x05    // 第一路关
#define EVT_TYPE_SECOND_CLOSE					0x06    // 第二路关
#define EVT_TYPE_THIRD_CLOSE					0x07    // 第三路关
#define EVT_TYPE_FOURTH_CLOSE					0x08    // 第四路关
#define EVT_TYPE_SECURITY_WARN					0x09    // 防护模式告警
#define EVT_TYPE_LOW_POWER_WARN					0x21    // 低电量告警
#define EVT_TYPE_MAGNET_COUNT_WARN				0x31    // 磁感计数告警

#define ADV_DEV_TYPE_LOCATION					3		// 广播数据包中设备类型位置
#define EVT_TIME_STAMP_LEN						4		// 时间戳长度
#define EVT_ONE_TYPE_LEN_LOCATION       		4		// 根据实际调整
#define EVT_ONE_TYPE_LEN						5		// 根据实际调整
#define EVT_TWO_TYPE_LEN_LOCATION				10		// 根据实际调整
#define EVT_TWO_TYPE_LEN						5		// 根据实际调整
#define EVT_THREE_TYPE_LEN_LOCATION				16		// 根据实际调整
#define EVT_THREE_TYPE_LEN						6		// 根据实际调整

#define STS_TYPE_SINGLE_SWITCH					0x01	// 单变量开关
#define STS_TYPE_DOUBLE_SWITCH					0x02	// 双变量开关
#define STS_TYPE_TREBLE_SWITCH					0x03	// 三变量开关
#define STS_TYPE_FOURFOLD_SWITCH				0x04	// 四变量开关
#define STS_TYPE_SWITCH_AND_DELAY				0x05	// 开关+倒计时状态
#define STS_TYPE_COUNTER						0x06	// 反锁状态
#define STS_TYPE_SECURITY_AND_SWITCH			0x07	// 防护模式+开关
#define STS_TYPE_RMN_CY_PCT						0x21	// 剩余电量百分比
#define STS_TYPE_RMN_CY_PCT_AND_SOC				0x22	// 剩余电量百分比+充电状态
#define STS_TYPE_MAGNET_COUNT_1					0x31	// 磁感计数1
#define STS_TYPE_MAGNET_COUNT_2					0x32	// 磁感计数2
#define STS_TYPE_MAGNET_COUNT_3					0x33	// 磁感计数3

#define SR_DEV_TYPE_LOCATION            		2		// 扫描响应包中设备类型位置
#define STS_ONE_TYPE_LOCATION					3		// 扫描响应包中状态一类型位置
#define STS_ONE_PARAM_1_LOCATION				4		// 扫描响应包中状态一参数1位置
#define STS_ONE_PARAM_2_LOCATION				5		// 扫描响应包中状态一参数2位置
#define STS_TWO_TYPE_LOCATION					6		// 扫描响应包中状态二类型位置
#define STS_TWO_PARAM_1_LOCATION				7		
#define STS_TWO_PARAM_2_LOCATION				8		
#define STS_THREE_TYPE_LOCATION					9		// 扫描响应包中状态三类型位置
#define STS_THREE_PARAM_1_LOCATION				10
#define STS_THREE_PARAM_2_LOCATION				11
#define STS_THREE_PARAM_3_LOCATION				12
#define STS_THREE_PARAM_4_LOCATION				13
#define STS_FOUR_TYPE_LOCATION					14		// 扫描响应包中状态四类型位置
#define STS_FOUR_PARAM_1_LOCATION				15
#define STS_FOUR_PARAM_2_LOCATION				16
#define STS_FOUR_PARAM_3_LOCATION				17
#define STS_FOUR_PARAM_4_LOCATION				18

/* --------------- 同步 --------------- */
// 主机
#define ADV_SYNC_OFFSET_LOCATION				3		// 广播数据包中同步偏移量位置
#define ADV_APPID_STARTING_LOCATION				4		// 广播数据包中APPID起始位置，长2字节
#define ADV_SYNC_PARAM_STARTING_LOCATION		12		// 广播数据包中同步参数起始位置，长6字节

/* --------------- 配网 --------------- */
// 从机
#define STS_JOIN_NETWORK_LOCATION				2		// 扫描响应包中状态类型配网标识位置
#define JOIN_NETWORK_INFO_STARTING_LOCATION		3		// 扫描响应包中申请匹配的主机MAC地址/配网验证码起始位置，长6字节
#define BITWISE_OFFSET_LOCATION					9		// 扫描响应包中位选字节偏移位置
#define SINGLE_BIT_SELECT_CODE_LOCATION			10		// 扫描响应包中单字节位选码位置
#define NO_JOIN_NETWORK_YET						0x01	// 从机未配网
#define JOIN_NETWORK_ALREADY					0x02	// 从机已配网
// 主机
#define ADV_DOMAIN_ADDR_STARTING_LOCATION		6		// 广播数据包中配网码（域地址）起始位置，长6字节
#define ADV_MAC_1_STARTING_LOCATION				14		// 广播数据包中蓝牙MAC地址1起始位置，长6字节
#define ADV_GROUP_SERIAL_NUM_1_LOCATION			20		// 广播数据包中群组序号1位置
#define ADV_MAC_2_STARTING_LOCATION				21		// 广播数据包中蓝牙MAC地址2起始位置，长6字节
#define ADV_GROUP_SERIAL_NUM_2_LOCATION			27		// 广播数据包中群组序号2位置
#define PRIMARY_SYNC_JOIN_NETWORK				0x80	// 主同步配网
#define SECONDARY_SYNC_JOIN_NETWORK				0x00	// 子同步配网
#define PRIMARY_SYNC_NO_JOIN_NETWORK			0x81	// 主同步未配网
#define SECONDARY_SYNC_NO_JOIN_NETWORK			0x01	// 子同步未配网

// 手机
#define RESTORE_FACTORY_SETING_NETWORK			0xA0	// 出厂设置
#define MOBILE_SET_JOIN_NETWORK					0xB0	// 设置网络ID和序码

/* --------------- 群控 --------------- */
// 从机
#define SR_SWITCH_TYPE_LOCATION					14		// 扫描响应包中开关状态类型位置
#define SR_SWITCH_VALUE_STARTING_LOCATION		15		// 扫描响应包中开关状态值起始位置，长度根据开关类型变化
// 主机
#define ADV_GROUP_CTRL_CODE_STARTING_LOCATION	12		// 广播数据包中群控多选码起始位置，长8字节
#define ADV_SWITCH_TYPE_LOCATION				21		// 广播数据包中开关状态类型位置
#define ADV_SWITCH_VALUE_STARTING_LOCATION		22		// 广播数据包中开关状态值起始位置，长度根据开关类型变化
#define PRIMARY_SYNC_GROUP_CTRL					0x85	// 主同步群控
#define SECONDARY_SYNC_GROUP_CTRL				0x05	// 子同步群控
#define SECONDARY_SYNC_SIGLE_CTRL				0x03	// 子同步单控
#define PRIMARY_SYNC_SIGLE_CTRL					0x83	// 主同步单控

/*********************************************************************
 * TYPEDEFS
 */
typedef struct
{
    uint8_t countValue[2];								// 磁感计数值
} MagnetCount_t;

#endif /* _ABA_PROTOCOL_H_ */

