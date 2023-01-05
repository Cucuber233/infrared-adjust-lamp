/**
 *****************************************************************************
 * @file    board_pwm.h
 *
 * @brief    -
 *
 *****************************************************************************
*/
#ifndef _BOARD_PWM_H_
#define _BOARD_PWM_H_
/*********************************************************************
 * INCLUDES
 */
#include "bx_kernel.h"
#include "bxd_pwm.h"
#include "bx_dbg.h"
#include "board_gpio.h"
#include "board_flash.h"
#include "user_control.h"
/*********************************************************************
 * DEFINITIONS
 */
 #define  freq                      3000
 
typedef struct 
{
	uint8_t pwmPin;   //控制的io口
	uint8_t pwmFlag;  //pwm开关
	uint16_t value;    //pwm值
} pwm_ch_t;

typedef struct
{
	pwm_ch_t pwm0_Confing;
	pwm_ch_t pwm1_Confing;
} pwm_ch_data;

/*********************************************************************
* GLOBAL VARIABLES
*/
//extern pwm_ch_t pwm0_Confing;
//extern pwm_ch_t pwm1_Confing;
extern pwm_ch_data pwm_data;
/*********************************************************************
 * API FUNCTIONS
 */
void pwm_Init(void);
uint8_t GetCurrentRGBWValue(void);
void SetRGBWColorRatioValue(pwm_ch_t *pwm_ch,uint8_t add);
void pwmSwitch(uint8_t p_button);
#endif /* _BOARD_PWM_H_ */
