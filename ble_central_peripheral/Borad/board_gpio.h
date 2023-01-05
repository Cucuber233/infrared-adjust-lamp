/**
 *****************************************************************************
 * @file    board_gpio.h
 *
 * @brief    -
 *
 *****************************************************************************
*/
#ifndef __BOARD_GPIO_H__
#define __BOARD_GPIO_H__
/*********************************************************************
* INCLUDES
*/
#include "bx_pm.h"
#include "bxd_gpio.h"
#include "bx_dbg.h"

/*********************************************************************
* DEFINITIONS
*/           
#define IR_IO                   12      //ºìÍâIO
#define key_0                  	13      //°´¼ü0
#define key_1                  	15      //°´¼ü1
#define BOARD_LED_0				22		// LED_IO_0
#define BOARD_LED_1				23		// LED_IO_1
/*********************************************************************
* API FUNCTIONS
*/
void GPIOInit(void);
#endif
