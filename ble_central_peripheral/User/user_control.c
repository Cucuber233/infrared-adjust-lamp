/*********************************************************************
 * INCLUDES
 */
#include "user_control.h"

static void pwmIRClose(void);
static uint8_t LightFlag_0 = 0;
static uint8_t LightFlag_1 = 0;

uint8_t IR_pin_value = 0;
/*********************************************************************
 * LOCAL VARIABLES
 */
/**
@brief 红外开灯:定时
 @param 无
 @return 无
*/
void pwmItrProcess()
{
	uint32_t IR_val;
	bxd_gpio_read(BX_GPIOA, &IR_val);
	
	IR_pin_value = IR_val >> IR_IO & 0x01;
	if(IR_pin_value)
	{
		if(!pwm_data.pwm0_Confing.pwmFlag)
		{
			LightFlag_0 = 1;
			pwm_data.pwm0_Confing.pwmFlag = 1;
			bxd_pwm_start(BX_PWM0, freq, pwm_data.pwm0_Confing.value);
		}
		
		if(!pwm_data.pwm1_Confing.pwmFlag)
		{
			LightFlag_1 = 1;
			pwm_data.pwm1_Confing.pwmFlag = 1;
			bxd_pwm_start(BX_PWM1, freq, pwm_data.pwm1_Confing.value);
		}
		bx_dwork((void (*)(void *))pwmIRClose, NULL, IR_TIME, 1 );   //(15 + 5)秒关闭
	}
	else
		IR_pin_value = 0;
}

/**
@brief 红外开灯: 中断
 @param 无
 @return 无
*/
void pwmItrProcess_itr(uint32_t *Data)
{
	uint8_t IR_pin_value = *Data >> IR_IO & 0x01;
	if( IR_pin_value )
	{
		LOG_RAW("IR_open\n");
		if(!pwm_data.pwm0_Confing.pwmFlag)
		{
			LightFlag_0 = 1;
			pwm_data.pwm0_Confing.pwmFlag = 1;
			bxd_pwm_start(BX_PWM0, freq, pwm_data.pwm0_Confing.value);
		}
		
		if(!pwm_data.pwm1_Confing.pwmFlag)
		{
			LightFlag_1 = 1;
			pwm_data.pwm1_Confing.pwmFlag = 1;
			bxd_pwm_start(BX_PWM1, freq, pwm_data.pwm1_Confing.value);
		}
		bx_dwork((void (*)(void *))pwmIRClose, NULL, IR_TIME, 1 );   //15秒关闭
	}
}


/**
 @brief  红外关灯
 @param 无
 @return 无
*/
static void pwmIRClose()
{	
	if(LightFlag_0)
	{
		LightFlag_0 = 0;
		pwm_data.pwm0_Confing.pwmFlag = 0;
		bxd_pwm_start(BX_PWM0, freq, 0);
	}
	
	if(LightFlag_1)
	{
		LightFlag_1 = 0;
		pwm_data.pwm1_Confing.pwmFlag = 0;
		bxd_pwm_start(BX_PWM1, freq, 0);
	}
}