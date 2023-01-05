/*********************************************************************
* INCLUDES
*/
#include "board_gpio.h"

/*********************************************************************
* LOCAL VARIABLES
*/


/*********************************************************************
* PUBLIC FUNCTIONS
*/
/**
 @brief GPIO初始化
 @param 无
 @return 无
*/
void GPIOInit()
{
//	bx_pm_lock( BX_PM_GPIO );
    bxd_gpio_open( BX_GPIOA );                                     //打开时钟
	bxd_gpio_set_mode( BX_GPIOA, key_0, BX_GPIO_MODE_INPUT );      //设置按键1引脚10为输入模式
	bxd_gpio_set_mode( BX_GPIOA, key_1, BX_GPIO_MODE_INPUT );      //设置按键2引脚15为输入模式
    bxd_gpio_set_mode( BX_GPIOA, IR_IO, BX_GPIO_MODE_INPUT );      //设置红外引脚16为输入模式
	
	bxd_gpio_set_pull( BX_GPIOA, key_0, BX_GPIO_PULLUP );
	bxd_gpio_set_pull( BX_GPIOA, key_1, BX_GPIO_PULLUP );
	bxd_gpio_set_pull( BX_GPIOA, IR_IO, BX_GPIO_PULLDOWN );
	
//    bxd_gpio_write( BX_GPIOA, IR_IO, 0 );                          //将引脚16电平拉低
//	bxd_gpio_write( BX_GPIOA, key_0, 1 );                          
//	bxd_gpio_write( BX_GPIOA, key_1, 1 );                          
	
//	bxd_gpio_set_mode( BX_GPIOA, IR_IO, BX_GPIO_MODE_IT_RISING );  //设置IR为上升沿触发中断
//	
//    bxd_gpio_enable_intr( BX_GPIOA );                              //使能中断
}

/**
 @brief GPIO中断函数
 @param 无
 @return 无
*/
//配置于bxd_gpio.c里的GPIO_IRQHandler中断函数

/**
 @brief 
 @param L_data [in] - 
 @return 无
*/
void keyCallback(uint8_t *L_data)
{
	
}