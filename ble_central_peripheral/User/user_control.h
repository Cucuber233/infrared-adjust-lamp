/**
 *****************************************************************************
 * @file    user_control.h
 *
 * @brief    -
 *
 *****************************************************************************
*/
#ifndef __USER_BOARD_H__
#define __USER_BOARD_H__

#include "bx_kernel.h"
#include "bx_type_def.h"
#include "board_gpio.h"
#include "bxd_gpio.h"
#include "board_pwm.h"
#include "plf.h"

/*********************************************************************
* DEFINITIONS
*/     
#define    IR_TIME                              15000

extern uint8_t IR_pin_value;
/*********************************************************************
* API FUNCTIONS
*/
void pwmItrProcess(void);	
void pwmItrProcess_itr(uint32_t *Data);
#endif
