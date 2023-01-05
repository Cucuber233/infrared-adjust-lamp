#ifndef _ABA_PROTOCOL_H_
#define _ABA_PROTOCOL_H_

/*********************************************************************
 * INCLUDES
 */
#include <stdint.h>

/*********************************************************************
 * DEFINITIONS
 */
#define ADV_DATA_TYPE_EVT_LOG					0x06	// ���ݰ����ͣ��¼���־�㲥

#define DEV_TYPE_SWITCH							0x01    // ����
#define DEV_TYPE_PLUG							0x02    // ����
#define DEV_TYPE_LOCK                   		0x03    // ��
#define DEV_TYPE_MAGNET_SWITCH					0x04    // �Ŵ�������
#define DEV_TYPE_MAGNET_COUNTER					0x40    // �Ÿм�����
#define DEV_TYPE_GATEWAY						0x80    // ����
#define DEV_TYPE_TEMP_SENSOR                    0x41    // �¶ȴ�����
#define DEV_TYPE_DIMMING						0x50	// �ƶ˵�����

#define EVT_TYPE_FIRST_OPEN						0x01    // ��һ·��
#define EVT_TYPE_SECOND_OPEN					0x02    // �ڶ�·��
#define EVT_TYPE_THIRD_OPEN						0x03    // ����·��
#define EVT_TYPE_FOURTH_OPEN					0x04    // ����·��
#define EVT_TYPE_FIRST_CLOSE					0x05    // ��һ·��
#define EVT_TYPE_SECOND_CLOSE					0x06    // �ڶ�·��
#define EVT_TYPE_THIRD_CLOSE					0x07    // ����·��
#define EVT_TYPE_FOURTH_CLOSE					0x08    // ����·��
#define EVT_TYPE_SECURITY_WARN					0x09    // ����ģʽ�澯
#define EVT_TYPE_LOW_POWER_WARN					0x21    // �͵����澯
#define EVT_TYPE_MAGNET_COUNT_WARN				0x31    // �Ÿм����澯

#define ADV_DEV_TYPE_LOCATION					3		// �㲥���ݰ����豸����λ��
#define EVT_TIME_STAMP_LEN						4		// ʱ�������
#define EVT_ONE_TYPE_LEN_LOCATION       		4		// ����ʵ�ʵ���
#define EVT_ONE_TYPE_LEN						5		// ����ʵ�ʵ���
#define EVT_TWO_TYPE_LEN_LOCATION				10		// ����ʵ�ʵ���
#define EVT_TWO_TYPE_LEN						5		// ����ʵ�ʵ���
#define EVT_THREE_TYPE_LEN_LOCATION				16		// ����ʵ�ʵ���
#define EVT_THREE_TYPE_LEN						6		// ����ʵ�ʵ���

#define STS_TYPE_SINGLE_SWITCH					0x01	// ����������
#define STS_TYPE_DOUBLE_SWITCH					0x02	// ˫��������
#define STS_TYPE_TREBLE_SWITCH					0x03	// ����������
#define STS_TYPE_FOURFOLD_SWITCH				0x04	// �ı�������
#define STS_TYPE_SWITCH_AND_DELAY				0x05	// ����+����ʱ״̬
#define STS_TYPE_COUNTER						0x06	// ����״̬
#define STS_TYPE_SECURITY_AND_SWITCH			0x07	// ����ģʽ+����
#define STS_TYPE_RMN_CY_PCT						0x21	// ʣ������ٷֱ�
#define STS_TYPE_RMN_CY_PCT_AND_SOC				0x22	// ʣ������ٷֱ�+���״̬
#define STS_TYPE_MAGNET_COUNT_1					0x31	// �Ÿм���1
#define STS_TYPE_MAGNET_COUNT_2					0x32	// �Ÿм���2
#define STS_TYPE_MAGNET_COUNT_3					0x33	// �Ÿм���3

#define SR_DEV_TYPE_LOCATION            		2		// ɨ����Ӧ�����豸����λ��
#define STS_ONE_TYPE_LOCATION					3		// ɨ����Ӧ����״̬һ����λ��
#define STS_ONE_PARAM_1_LOCATION				4		// ɨ����Ӧ����״̬һ����1λ��
#define STS_ONE_PARAM_2_LOCATION				5		// ɨ����Ӧ����״̬һ����2λ��
#define STS_TWO_TYPE_LOCATION					6		// ɨ����Ӧ����״̬������λ��
#define STS_TWO_PARAM_1_LOCATION				7		
#define STS_TWO_PARAM_2_LOCATION				8		
#define STS_THREE_TYPE_LOCATION					9		// ɨ����Ӧ����״̬������λ��
#define STS_THREE_PARAM_1_LOCATION				10
#define STS_THREE_PARAM_2_LOCATION				11
#define STS_THREE_PARAM_3_LOCATION				12
#define STS_THREE_PARAM_4_LOCATION				13
#define STS_FOUR_TYPE_LOCATION					14		// ɨ����Ӧ����״̬������λ��
#define STS_FOUR_PARAM_1_LOCATION				15
#define STS_FOUR_PARAM_2_LOCATION				16
#define STS_FOUR_PARAM_3_LOCATION				17
#define STS_FOUR_PARAM_4_LOCATION				18

/* --------------- ͬ�� --------------- */
// ����
#define ADV_SYNC_OFFSET_LOCATION				3		// �㲥���ݰ���ͬ��ƫ����λ��
#define ADV_APPID_STARTING_LOCATION				4		// �㲥���ݰ���APPID��ʼλ�ã���2�ֽ�
#define ADV_SYNC_PARAM_STARTING_LOCATION		12		// �㲥���ݰ���ͬ��������ʼλ�ã���6�ֽ�

/* --------------- ���� --------------- */
// �ӻ�
#define STS_JOIN_NETWORK_LOCATION				2		// ɨ����Ӧ����״̬����������ʶλ��
#define JOIN_NETWORK_INFO_STARTING_LOCATION		3		// ɨ����Ӧ��������ƥ�������MAC��ַ/������֤����ʼλ�ã���6�ֽ�
#define BITWISE_OFFSET_LOCATION					9		// ɨ����Ӧ����λѡ�ֽ�ƫ��λ��
#define SINGLE_BIT_SELECT_CODE_LOCATION			10		// ɨ����Ӧ���е��ֽ�λѡ��λ��
#define NO_JOIN_NETWORK_YET						0x01	// �ӻ�δ����
#define JOIN_NETWORK_ALREADY					0x02	// �ӻ�������
// ����
#define ADV_DOMAIN_ADDR_STARTING_LOCATION		6		// �㲥���ݰ��������루���ַ����ʼλ�ã���6�ֽ�
#define ADV_MAC_1_STARTING_LOCATION				14		// �㲥���ݰ�������MAC��ַ1��ʼλ�ã���6�ֽ�
#define ADV_GROUP_SERIAL_NUM_1_LOCATION			20		// �㲥���ݰ���Ⱥ�����1λ��
#define ADV_MAC_2_STARTING_LOCATION				21		// �㲥���ݰ�������MAC��ַ2��ʼλ�ã���6�ֽ�
#define ADV_GROUP_SERIAL_NUM_2_LOCATION			27		// �㲥���ݰ���Ⱥ�����2λ��
#define PRIMARY_SYNC_JOIN_NETWORK				0x80	// ��ͬ������
#define SECONDARY_SYNC_JOIN_NETWORK				0x00	// ��ͬ������
#define PRIMARY_SYNC_NO_JOIN_NETWORK			0x81	// ��ͬ��δ����
#define SECONDARY_SYNC_NO_JOIN_NETWORK			0x01	// ��ͬ��δ����

// �ֻ�
#define RESTORE_FACTORY_SETING_NETWORK			0xA0	// ��������
#define MOBILE_SET_JOIN_NETWORK					0xB0	// ��������ID������

/* --------------- Ⱥ�� --------------- */
// �ӻ�
#define SR_SWITCH_TYPE_LOCATION					14		// ɨ����Ӧ���п���״̬����λ��
#define SR_SWITCH_VALUE_STARTING_LOCATION		15		// ɨ����Ӧ���п���״ֵ̬��ʼλ�ã����ȸ��ݿ������ͱ仯
// ����
#define ADV_GROUP_CTRL_CODE_STARTING_LOCATION	12		// �㲥���ݰ���Ⱥ�ض�ѡ����ʼλ�ã���8�ֽ�
#define ADV_SWITCH_TYPE_LOCATION				21		// �㲥���ݰ��п���״̬����λ��
#define ADV_SWITCH_VALUE_STARTING_LOCATION		22		// �㲥���ݰ��п���״ֵ̬��ʼλ�ã����ȸ��ݿ������ͱ仯
#define PRIMARY_SYNC_GROUP_CTRL					0x85	// ��ͬ��Ⱥ��
#define SECONDARY_SYNC_GROUP_CTRL				0x05	// ��ͬ��Ⱥ��
#define SECONDARY_SYNC_SIGLE_CTRL				0x03	// ��ͬ������
#define PRIMARY_SYNC_SIGLE_CTRL					0x83	// ��ͬ������

/*********************************************************************
 * TYPEDEFS
 */
typedef struct
{
    uint8_t countValue[2];								// �Ÿм���ֵ
} MagnetCount_t;

#endif /* _ABA_PROTOCOL_H_ */

