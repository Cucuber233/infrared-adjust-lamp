/**
 ****************************************************************************************
 *
 * @file hfp_task.c
 *
 * @brief Glucose Profile Sensor Task Implementation.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup GLPSTASK
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#include "gap.h"
#include "gattc_task.h"
#include "alm_profile.h"
#include "alm_profile_task.h"
#include "prf_utils.h"
#include "ke_mem.h"
#include "co_utils.h"
#include "bx_dbg.h"
#include "bx_kernel.h"
#include "app.h"


static uint8_t user_get_att_db_idx_from_handle(struct user_profile_env_tag *user_env,uint16_t handle);
static void ble_send_data_notify(u8 *data, u8 length, u16 handle);

/*
 *  GLUCOSE PROFILE ATTRIBUTES
 ****************************************************************************************
 */
 
 
/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATT_CODE_ATT_WR_CMD_IND message.
 * The handler compares the new values with current ones and notifies them if they changed.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_write_req_ind_handler(ke_msg_id_t const msgid,
                                      struct gattc_write_req_ind *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
#if SERVICE_DEBUG
    LOG_RAW("__user gattc_write_req_ind_handler__\n");
#endif
    uint8_t state  = ke_state_get(dest_id);
    if(state == USER_PROFILE_IDLE)
    {
        struct user_profile_env_tag *user_env = PRF_ENV_GET(ALMPROFILE, user_profile);
        
        uint8_t att_db_idx = user_get_att_db_idx_from_handle(user_env, param->handle);
#if SERVICE_DEBUG
        bx_logln("att_db_idx:%d",att_db_idx);
#endif
        switch(att_db_idx)
        {
            case PTS_SVC_IDX_ALM_ATT_VAL:                   // 0xFE20,设备属性设置特征
            {
//                GetAlmAttDataFromAlmProfile(param->value, param->length);
                
            }break;
			
			case PTS_SVC_IDX_ALM_ATT_VAL_1:                   // 0xFE40,设备属性设置特征
            {
//				DownloadServiceDimmingData(param->value, param->length);      //灯光配置数据下发       				
            }break;
			
			case PTS_SVC_IDX_TX_NTF_CFG:
            {
//				g_notifyHandle = param->handle-1;        //通知句柄
//				UploadServiceDimmingData();              //灯光配置上传
            }break;
			
            
//            case PTS_SVC_IDX_SET_ADV_VAL:                   // 0xFE51,配置自定义广播特征
//            {
//                GetConfigurationAdvDataFromAlmProfile(param->value, param->length);
//            }break;
//            
//            case PTS_SVC_IDX_SET_FILTER_VAL:                // 0xFE52,配置过滤信息特征
//            {
//                GetFilterDataFromAlmProfile(param->value, param->length);
//            }break;
            
            default:
                break;
        }
          
        
        uint8_t status = GAP_ERR_NO_ERROR;
        struct gattc_write_cfm * cfm;

        //Send write response
        cfm = KE_MSG_ALLOC(GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
        cfm->handle = param->handle;
        cfm->status = status;
        ke_msg_send(cfm);
        
    }
    return (KE_MSG_CONSUMED);
}


static uint8_t user_get_att_db_idx_from_handle(struct user_profile_env_tag *user_env,uint16_t handle)
{
    return handle - user_env->start_hdl;
}


static void ble_send_data_notify(u8 *data, u8 length, u16 handle)
{
    struct gattc_send_evt_cmd * notify_cmd = KE_MSG_ALLOC_DYN( GATTC_SEND_EVT_CMD,
											TASK_GATTC, TASK_APP,
											gattc_send_evt_cmd,length);

    static u16 notify_seq_num = 0;
    notify_cmd->operation = GATTC_NOTIFY;
    notify_cmd->seq_num = notify_seq_num++;
    notify_cmd->length = length;
    notify_cmd->handle = handle;
    
    memcpy( notify_cmd->value,data, length );
    	
    ke_msg_send( notify_cmd );
}

void AlmInitProfileNotifySend(uint8_t *data, uint8_t length, uint16_t handle)
{
	ble_send_data_notify(data, length, handle);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the read request from peer device
 *
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_read_req_ind_handler(ke_msg_id_t const msgid,
                                      struct gattc_read_req_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
#if SERVICE_DEBUG
    LOG_RAW("__user gattc_read_req_ind_handler %d__\n", param->handle);
#endif
    ke_state_t state = ke_state_get(dest_id);
    if(state == USER_PROFILE_IDLE)
    {
        struct user_profile_env_tag *user_env = PRF_ENV_GET(ALMPROFILE, user_profile);
        
        uint8_t att_db_idx = user_get_att_db_idx_from_handle(user_env, param->handle);
#if SERVICE_DEBUG       
        bx_logln("read hdl:%d",att_db_idx);
#endif
        
        switch(att_db_idx)
        {
			case PTS_SVC_IDX_ALM_ATT_VAL:
            {
				
            }break;
			
            case PTS_SVC_IDX_ALM_ATT_VAL_1:                //0xFE40
            {
				
            }break;
			
			case PTS_SVC_IDX_ALM_ATT_VAL_2:
			{
//				struct gattc_read_cfm* cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, sizeof(BLE_RELAY_VERSION)-1);
//                cfm->handle = param->handle;
//                cfm->status = ATT_ERR_NO_ERROR;
//                cfm->length = sizeof(BLE_RELAY_VERSION) - 1;
//                //memcpy(cfm->value, BLE_RELAY_VERSION, BLE_RELAY_VERSION_LENGTH);
//				memcpy(cfm->value, BLE_RELAY_VERSION, sizeof(BLE_RELAY_VERSION)-1);
//                ke_msg_send(cfm);
			}break;
				
            
//            case PTS_SVC_IDX_SET_ADV_VAL:
//            {
////                uint8_t temp[4] = {0x01,0x02,0x03,0x04};
////                ble_send_data_notify(temp, 4, param->handle);
//            }break;
			
            default:
                break;
        }
        // Send value to peer device.
//        struct gattc_read_cfm* cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, 1);
//        cfm->handle = param->handle;
//        cfm->status = ATT_ERR_NO_ERROR;
//        cfm->length = 3;
//        cfm->value[0] = 0; 
//        cfm->value[1] = 6;
//        cfm->value[2] = 6;   
//        ke_msg_send(cfm);
    }

    return (KE_MSG_CONSUMED);
}


/**
 ****************************************************************************************
 * @brief Handles @ref GATTC_CMP_EVT for GATTC_NOTIFY and GATT_INDICATE message meaning
 * that Measurement notification/indication has been correctly sent to peer device
 *
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_cmp_evt_handler(ke_msg_id_t const msgid, struct gattc_cmp_evt const *param,
                                 ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    bx_logln("gattc_cmp_evt_handler");

    return (KE_MSG_CONSUMED);
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler user_default_handler[] =
{
    {GATTC_WRITE_REQ_IND,                 (ke_msg_func_t) gattc_write_req_ind_handler},
    {GATTC_READ_REQ_IND,                  (ke_msg_func_t) gattc_read_req_ind_handler},
    {GATTC_CMP_EVT,                       (ke_msg_func_t) gattc_cmp_evt_handler},
};

/// Specifies the message handlers that are common to all states.
const struct ke_state_handler userp_default_handler = KE_STATE_HANDLER(user_default_handler);


/// @} GLPSTASK
