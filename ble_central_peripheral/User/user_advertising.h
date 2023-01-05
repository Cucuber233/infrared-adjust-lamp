/**
 *****************************************************************************
 * @file    user_advertising.h
 *
 * @brief    -
 *
 *****************************************************************************
*/
#ifndef _USER_ADVERTISING_H_
#define _USER_ADVERTISING_H_

/*********************************************************************
 * INCLUDES
 */
#include <stdbool.h>
#include "app.h"

/*********************************************************************
 * DEFINITIONS
 */
#define PRESENT_ADVERTISING							0x01			// 正在广播
#define NOT_PRESENT_ADVERTISING 					0x00			// 未在广播

#define BEACON_B

#if ROLE_DEVICE > 0
#define ADV_INTERVAL                    160          
#else
#define ADV_INTERVAL                    1280
#endif

/*********************************************************************
 * GLOBAL VARIABLES
 */
extern uint8_t g_advertisingData[];
extern uint8_t g_scanResponseData[];

/*********************************************************************
 * API FUNCTIONS
 */
void InitAdvertisingData(void);
void InitScanResponseData(void);
void SetBleConnectStatus(bool status);
bool GetBleConnectStatus(void);
void EnableAdvertising(void);
void DisableAdvertising(void);
void UpdateAdvData(void);
void SetConfigurationAdvData(uint8_t *advData, uint8_t len);
void SetAdvInterval(uint16_t advInterval);
void SetBleName(uint8_t *name, uint8_t len);
void SetForwardAdvData(uint8_t *pData, uint8_t len);
void SetAdvertiseMode(uint8_t type);
void SetStatusVariety(void);
void SetStatesRelay(uint8_t *data_relay_state);

#endif /* _USER_ADVERTISING_H_ */
