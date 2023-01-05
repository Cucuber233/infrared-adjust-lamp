#ifndef __BOARD_KEY_H__
#define __BOARD_KEY_H__

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
/* key value */
#define	KEY_1					1UL		// Button A: Back
#define	KEY_2					2UL		// Ref/Def


#define	BUTTON_ALL					0xFF

#define BT_STAT_RELEASE				0x0000
#define BT_STAT_PRESS					0x0100
#define BT_STAT_LONG_PRESS		0x0200
#define BT_STAT_CLICK					0x0400


/* Exported types ------------------------------------------------------------*/
typedef enum 
{
	//--- press key ---
	PRESS_BUTTON_1	= 1,
	PRESS_BUTTON_2,
	PRESS_BUTTON_POWER,
	PRESS_BUTTON_SET,
	PRESS_BUTTON_UP,
	PRESS_BUTTON_BELOW,
	PRESS_BUTTON_SET_POWER,
	PRESS_BUTTON_SET_BELOW,
	//--- hold key ---
	HOLD_BUTTON_1,       //9
	HOLD_BUTTON_2,
	HOLD_BUTTON_POWER,
	HOLD_BUTTON_SET,
	HOLD_BUTTON_UP,
	HOLD_BUTTON_BELOW,
	HOLD_BUTTON_SET_POWER,
	HOLD_BUTTON_SET_BELOW,
	//--- click key ---
	CLICK_BUTTON_1,
	CLICK_BUTTON_2,
	CLICK_BUTTON_POWER,
	CLICK_BUTTON_SET,
	CLICK_BUTTON_UP,
	CLICK_BUTTON_BELOW,
	CLICK_BUTTON_SET_POWER,
	//--- long press key ---
	LONG_PRESS_BUTTON_1,
	LONG_PRESS_BUTTON_2,
	LONG_PRESS_BUTTON_POWER,
	LONG_PRESS_BUTTON_SET,
	LONG_PRESS_BUTTON_UP,
	LONG_PRESS_BUTTON_BELOW,
	LONG_BUTTON_SET_POWER,
	LONG_BUTTON_SET_BELOW,
	LONG_BUTTON_BELOW_UP,
	//--- release key ---
	RELEASE_BUTTON_1,         //33
	RELEASE_BUTTON_2,
	RELEASE_BUTTON_POWER,
	RELEASE_BUTTON_SET,
	RELEASE_BUTTON_UP,
	RELEASE_BUTTON_BELOW,
}KEY_CODE_DEFINE;

typedef struct {
	uint8_t holdkey						:1;
	uint8_t processed					:1;
	uint8_t backlight					:1;
	uint8_t lock						:1;
	uint8_t 						:1;
	uint8_t 						:1;
	uint8_t 						:1;
	uint8_t 						:1;
	uint8_t clickDelay;
}KEY_Status;
	
typedef enum
{
	KEYBOARD_UNLOCK=0,
	KEYBOARD_LOCK,
	KEYBOARD_TRIGGER,
}LOCK_STAT_E;

uint8_t getKeyLock(void);
void setKeyLock(uint8_t lock);
void Key_Init(void);
void key_scan(void);
uint8_t getButton(void);
uint8_t getKeyClick(void);
#endif 
