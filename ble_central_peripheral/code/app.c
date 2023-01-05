/**
  ******************************************************************************
  * @file   :   main.c
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* includes ------------------------------------------------------------------*/
#include "app.h"
#include "ble.h"
#include "bxd_gpio.h"
#include "bxd_adc.h"
#include "bxd_pwm.h"
#include "bxd_tim.h"
#include "bx_pm.h"
#include "app_dis.h"
#include "flash_wrapper.h"
#include "app_bxotas.h"
#include "board_pwm.h"
#include "alm_profile.h"
#include "user_advertising.h"
#include "user_scan.h"
#include "alm_profile_task.h"
#include "board_gpio.h"
#include "board_key.h"
#include "user_control.h"
/* private define ------------------------------------------------------------*/
static uint32_t flg16HZ = 0;
static uint32_t flg100HZ = 0;
static uint32_t flg50HZ = 0;
static uint32_t flg160HZ = 0;
static uint8_t flgBt0 = 0;
static uint8_t flgBt1 = 0;
static uint32_t systick = 0;

void TimerInit( void );
void bx_tim0_intr_handler(void);
void bx_tim1_intr_handler(void);
/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );
/* private variables ---------------------------------------------------------*/
uint8_t user_scan_rsp_data[] = {
    
    0x07, 
    GAP_AD_TYPE_COMPLETE_NAME,
    'B','X','-','S','D','K'
};

// GAP - Advertisement data (max size = (28) bytes)
uint8_t user_adv_data[] = {
    0x07, 
    GAP_AD_TYPE_SHORTENED_NAME,
    'B','X','-','S','D','K'
};

/*********************************************************************
 * GLOBAL VARIABLES
 */
bool led_status = true;


static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    ( appm_add_svc_func_t )app_dis_add_dis,
#ifdef CFG_PRF_BXOTAS
    (appm_add_svc_func_t)app_bxotas_add_ota,		// 列表里添加OTA服务
#endif
#if ALM_PROFILE
    (appm_add_svc_func_t)User_Add_AlmProfile,       // 添加ALM初始化服务
#endif
	
	
};

/* exported variables --------------------------------------------------------*/
/*============================= private function =============================*/

s32 user_service_id;

bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 );

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_set_dev_cfg( struct gapm_set_dev_config_cmd * cmd )
{
    cmd->operation = GAPM_SET_DEV_CONFIG;
    cmd->role      = GAP_ROLE_ALL;
    cmd->pairing_mode = GAPM_PAIRING_LEGACY;
    cmd->sugg_max_tx_octets = BLE_MAX_OCTETS;
    cmd->sugg_max_tx_time   = BLE_MAX_TIME;
	cmd->max_mtu = 258;                     //连接读写的长度
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool app_add_svc( void )
{
    bool more_svc = false;
    if ( app_env.next_svc != sizeof( appm_add_svc_func_list ) / sizeof( appm_add_svc_func_t ) ) 
	{
        appm_add_svc_func_list[app_env.next_svc]();
        app_env.next_svc++;
        more_svc = true;
    }
    return more_svc;
}


/** ---------------------------------------------------------------------------
 * @brief   :Scan callback function
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int app_on_scan_adv_report( ke_msg_id_t const msgid, adv_report_t const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{

//    LOG_RAW( "adv or rsp data:" );
//    for( u8 i = 0; i < param->data_len; i++ ) {
//        LOG_RAW( "%02x ", param->data[i] );

//    }
//    LOG_RAW( "RSSI=%d\n", param->rssi );
//    LOG_RAW( "\r\n\r\n" );

    return ( KE_MSG_CONSUMED );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_init( void )
{
    app_dis_init();
#ifdef CFG_PRF_BXOTAS
    app_bxotas_init();		//OTA初始化
#endif
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_ready( void )
{
//    struct gapm_start_advertise_cmd adv_data;
//    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
//    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
//    adv_data.intv_max   = 800;//unit is 625 us
//    adv_data.intv_min   = 800;//unit is 625 us
//    adv_data.op.code    = GAPM_ADV_UNDIRECT;
//    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
//    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
//    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
//    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
//    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
//    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

//    ble_advertising_start( &adv_data );	
}


void app_ble_scan( void )
{
    struct gapm_start_scan_cmd * cmd = KE_MSG_ALLOC( GAPM_START_SCAN_CMD,
                                       TASK_GAPM, TASK_APP,
                                       gapm_start_scan_cmd );

    cmd->op.code = GAPM_SCAN_ACTIVE;
    cmd->op.addr_src = GAPM_STATIC_ADDR;
    cmd->op.state = 0;
    cmd->interval = 160;
    cmd->window = 160;
    cmd->mode = GAP_OBSERVER_MODE;
    cmd->filter_duplic = SCAN_ALLOW_ADV_ALL;
    cmd->filt_policy = SCAN_FILT_DUPLIC_DIS;

    ke_msg_send( cmd );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_disconnect( void )
{
    struct gapm_start_advertise_cmd adv_data;
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160; //unit is 625 us
    adv_data.intv_min   = 160; //unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

    ble_advertising_start( &adv_data );
}
void gpio_callback(void *hd,u8 pin_num,u8 reason);
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{	
    LOG_I("%s", __FUNCTION__);
    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    user_service_id = bx_register(&svc);

	LOG_RAW("Init\n");
    InitAdvertisingData();
    InitScanResponseData();	
	
	Flash_UserRead((uint8_t*)&pwm_data, sizeof(pwm_data));    //灯光数据初始化
	pwm_Init();    //pwm初始化
	GPIOInit();    //GPIO初始化	
	TimerInit();   //定时器初始化
	
	bx_defer(user_service_id, USM_APP_START_ADV, 0, 0, 1);    //开启广播
}

void gpio_callback(void *hd,u8 pin_num,u8 reason)
{
 //   int16_t x,y,z;
//    bxd_gpio_write(BX_GPIOA, 2, 1); 
//	LOG_RAW("pin_num=%d reason=%d\n",pin_num,reason);
//    bxd_gpio_write(BX_GPIOA, 2, 0); 
//    Mir3da_Read_Data(&x,&y,&z);
//    LOG_RAW("x=%ld y=%ld z=%ld\r\n", x,y,z);
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{
    s32 msg_src = bx_msg_source();
    if(msg_src == user_service_id) 
    {
        switch(msg) 
        {
            case USM_APP_STOP_ADV:
            {
                DisableAdvertising();
				bx_defer( user_service_id, USM_APP_START_SCAN, 0, 0, 1);
//                DisableAdvertising();
            }break;
            
            case USM_APP_START_SCAN:
            {
//                bx_defer(user_service_id, USM_APP_STOP_SCAN, 0, 0, 2000);
				EnableScan();
//                StartScanTimer();
            }break;
            
            case USM_APP_STOP_SCAN:
            {
                DisableScan();
                bx_defer(user_service_id, USM_APP_START_ADV, 0, 0, 1);
            }break;
			
            /* 本事件不可修改，不可用作其他用途 */
            case USM_APP_START_ADV:
            {
                EnableAdvertising();		
				//bx_defer( user_service_id, USM_APP_STOP_ADV, 0, 0, 400);
            }break;
            default:
                break;
        }
    }
    return BX_OK;
}




/** ---------------------------------------------------------------------------
 * @brief   : 
 * @note    :add by Barney 
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void TimerInit( void )
{
	bx_err_t rt;
	bx_pm_lock( BX_PM_TIM );
    bxd_timer_open( BX_TIM0 );
    bxd_timer_open( BX_TIM1 );
	bxd_timer_start( BX_TIM0, 10000 );               //10ms	
//	bxd_timer_start( BX_TIM0, 6250 );        //160hz
	
//		LOG_I("TimerInit		%d\n",rt);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void TIMER_IRQHandler( void )
{
    uint32_t timer_isr_status0, timer_isr_status1;
    timer_isr_status0 = BX_TIM0->IS & 0x01;
    timer_isr_status1 = BX_TIM1->IS & 0x01;
	
    if( timer_isr_status0 ) {
        BX_READ_REG( BX_TIM0->EOI );
//			LOG_I("TIMER_IRQHandler\n");
			systick++;
//			flg100HZ = 1;
			if(systick%2==0)
			{
				flg50HZ = 1;
			}
//			flg100HZ = 1;
//			flg160HZ = 1;
			if(systick%6 == 0)
			{
				flg16HZ = 1;
			}
			
			if(systick%10 == 0)         //10hz
				pwmItrProcess();
			
//        bxd_gpio_toggle( BX_GPIOA, 2 );
    }
//    if( timer_isr_status1 ) 
//	{
//        BX_READ_REG( BX_TIM1->EOI );
//        bxd_gpio_toggle( BX_GPIOA, 3 );
//    }
}

/*============================= private function =============================*/
void bx_it_init( void )
{
        bxd_timer_set_intr_callback(BX_TIM0, bx_tim0_intr_handler);
    bxd_timer_set_intr_callback(BX_TIM1, bx_tim1_intr_handler);
}

/*========================= end of private function ==========================*/

/*============================ interrupt function ============================*/
void bx_tim0_intr_handler(void)
{
    BX_READ_REG( BX_TIM0->EOI );
	
//	LOG_I("bx_tim0_intr_handler\n");
}

void bx_tim1_intr_handler(void)
{
    BX_READ_REG( BX_TIM1->EOI );
//    bxd_gpio_toggle( BX_GPIOA, 3 );
}


void KeyEvent(void)
{
	uint8_t key = 0;
	
		key_scan();
		key = getButton();
		switch(key)
		{
			case CLICK_BUTTON_1:                  //10
				pwmSwitch(key_0);
//				LOG_I("CLICK_BUTTON_1\n");
			break;
			
			case LONG_PRESS_BUTTON_1:
			{
				flgBt0 = 1;
//				LOG_I("LONG_PRESS_BUTTON_1\n");
			}break;
			
			case CLICK_BUTTON_2:                   //15
			{
				pwmSwitch(key_1);
//				LOG_I("CLICK_BUTTON_2\n");
			}break;
			
			case LONG_PRESS_BUTTON_2:
			{
				flgBt1 = 1; 
//				LOG_I("LONG_PRESS_BUTTON_2\n");
			}break;	
			
			case RELEASE_BUTTON_1:
			{
				flgBt0 = 0; 
//				LOG_I("RELEASE_BUTTON_1\n");
			}break;	
			
			case RELEASE_BUTTON_2:
				flgBt1 = 0; 
//				LOG_I("RELEASE_BUTTON_2\n");
			break;
		}
}

void SystemTickEvent(void)
{
	static uint8_t oldState0 = 0, oldState1 = 0;
	static uint8_t dirc0 =0, dirc1 =0;
	if(flg16HZ)
	{
		KeyEvent();
		flg16HZ = 0;
	}
	
	if(flg50HZ)
//	if(flg160HZ)
//	if(flg100HZ)
	{
		if(flgBt0!=oldState0)
		{
			oldState0 = flgBt0;
			if(flgBt0)
			{
				dirc0 = !dirc0;
			}
		}
		if(flgBt1!=oldState1)
		{
			oldState1 = flgBt1;
			if(flgBt1)
			{
				dirc1 = !dirc1;
			}
		}
		if(flgBt0)
		{
			SetRGBWColorRatioValue(&pwm_data.pwm0_Confing, dirc0);
		}
		if(flgBt1)
		{
			SetRGBWColorRatioValue(&pwm_data.pwm1_Confing, dirc1);
		}
		flg50HZ = 0;
//		flg100HZ = 0;
//		flg160HZ = 0;
	}
}


/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/