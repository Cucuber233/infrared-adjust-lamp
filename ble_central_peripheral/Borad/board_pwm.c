/*********************************************************************
 * INCLUDES
 */
#include "bxd_gpio.h"
#include "bx_pm.h"
#include "plf.h"             

#include "board_pwm.h"
/*********************************************************************
* LOCAL VARIABLES
*/
static void SavePwmValue(pwm_ch_t *pwm_ch);

//相关配置
//pwm_ch_t pwm0_Confing = {
//	.pwmPin = BOARD_LED_0,
//	.pwmFlag = 1,
//	.value = 15
//};

//pwm_ch_t pwm1_Confing = {
//	.pwmPin = BOARD_LED_1,
//	.pwmFlag = 1,
//	.value = 15
//};

pwm_ch_data pwm_data = {0};

 /*********************************************************************
 * PUBLIC FUNCTIONS
 */
 /**
 @brief PWM初始化
 @param None
 @return None
*/
void pwm_Init()
{
	if(pwm_data.pwm0_Confing.pwmPin == 0xFF)
	{
		pwm_data.pwm0_Confing.pwmPin = BOARD_LED_0;
		pwm_data.pwm0_Confing.value = 1;
		
		pwm_data.pwm1_Confing.pwmPin = BOARD_LED_1;
		pwm_data.pwm1_Confing.value = 1;
	}
	pwm_data.pwm0_Confing.pwmFlag = 0;
	pwm_data.pwm1_Confing.pwmFlag = 0;
	
	bx_pm_lock(BX_PM_PWM);  //打开pwm时钟
	bxd_pwm_open(BX_PWM0);	//打开pwm0的驱动
	bxd_pwm_open(BX_PWM1);	//打开pwm0的驱动
	bxd_pwm_set_clock_div( 2 );
	bxd_pwm_set_pin(BX_PWM0, pwm_data.pwm0_Confing.pwmPin);	//设置pwm0控制的是引脚是LED_IO_0
	bxd_pwm_set_pin(BX_PWM1, pwm_data.pwm1_Confing.pwmPin);	//设置pwm0控制的是引脚是LED_IO_1

	bxd_pwm_start(BX_PWM0, freq, 0);
	bxd_pwm_start(BX_PWM1, freq, 0);
	
//	LOG_RAW("pwm0_Confing->value: %d\n", pwm_data.pwm0_Confing.value);
//	LOG_RAW("pwm1_Confing->value: %d\n", pwm_data.pwm1_Confing.value);
}
 
 
/**
 @brief 占空比设置
 @param brightness -[in] 0 ~ 100
 @return None
*/
void SetRGBWColorRatioValue(pwm_ch_t *pwm_ch, uint8_t add)
{		
	static uint8_t flag_count = 0;
	const uint8_t THRESORD_max = 99;
	const uint8_t THRESORD_0   = 50;
	const uint8_t THRESORD_1   = 14;
	const uint8_t THRESORD_2   = 1;
	
	if(pwm_ch->pwmFlag)
	{
		flag_count++;
		if(add)
		{
			if(flag_count % 2 != 0 && (pwm_ch->value < THRESORD_0 && pwm_ch->value > THRESORD_2))
				return;
			
			if(pwm_ch->value < 99)
			{
				pwm_ch->value++;
			}				
		}
		else 
		{		
			if(pwm_ch->value > THRESORD_2)
			{
				pwm_ch->value--;
			}
		}		
//		LOG_RAW("pwm_ch->pwmPin: %d\n", pwm_ch->pwmPin);
//		LOG_RAW("pwm_ch->value: %d\n", pwm_ch->value);
		if(pwm_ch->pwmPin == BOARD_LED_0)
			bxd_pwm_start(BX_PWM0, freq, pwm_ch->value);	 //PWM0输出设置，包括频率、占空比 
		
		else if(pwm_ch->pwmPin == BOARD_LED_1)
			bxd_pwm_start(BX_PWM1, freq, pwm_ch->value);	
		
		bx_dwork((void (*)(void *))SavePwmValue, pwm_ch, 5000, 1 );   //保持不变5秒后保存
	}	
}

/**
 @brief pwm值保存
 @param pwm_ch -[in] 
 @return None
*/
static void SavePwmValue(pwm_ch_t *pwm_ch)
{
	LOG_RAW("\n*****Save*****\n");
	LOG_RAW("pwm_ch->pwmPin: %d\n", pwm_ch->pwmPin);
	LOG_RAW("pwm_ch->value: %d\n", pwm_ch->value);
	
	Flash_UserWrite((uint8_t*)&pwm_data, sizeof(pwm_data));
}

/**
 @brief pwm开关
 @param brightness -[in] 0~255
 @return None
*/
void pwmSwitch(uint8_t p_button)
{
	LOG_RAW("button: %d\n", p_button);

	if(!IR_pin_value)
	{
		if(p_button == key_0)                      //13
		{
			LOG_RAW("\npwm0_Confing.value: %d\n", pwm_data.pwm0_Confing.value);
			LOG_RAW("pwm0_Confing.pwmFlag: %d\n", pwm_data.pwm0_Confing.pwmFlag);
			if(pwm_data.pwm0_Confing.pwmFlag) 
			{
	//			LOG_RAW("close_pwm_0\n");
				pwm_data.pwm0_Confing.pwmFlag = 0;
	//			bxd_pwm_start(BX_PWM0, freq, 0);
				bxd_pwm_stop( BX_PWM0 );
			}
			else
			{
	//			LOG_RAW("open_pwm_0\n");
				pwm_data.pwm0_Confing.pwmFlag = 1;
				bxd_pwm_start(BX_PWM0, freq, pwm_data.pwm0_Confing.value);
			}		
		}
		else if(p_button == key_1)                  //15
		{
			LOG_RAW("\npwm1_Confing.value: %d\n", pwm_data.pwm1_Confing.value);
			LOG_RAW("pwm1_Confing.pwmFlag: %d\n", pwm_data.pwm1_Confing.pwmFlag);
			if(pwm_data.pwm1_Confing.pwmFlag) 
			{
	//			LOG_RAW("close_pwm_1\n");
				pwm_data.pwm1_Confing.pwmFlag = 0;
	//			bxd_pwm_start(BX_PWM1, freq, 0);
				bxd_pwm_stop( BX_PWM1 );
			}
			else
			{
	//			LOG_RAW("open_pwm_1\n");
				pwm_data.pwm1_Confing.pwmFlag = 1;
				bxd_pwm_start(BX_PWM1, freq, pwm_data.pwm1_Confing.value);
			}
		}
	}
}

/**
 @brief 获取当前占空比值
 @param 无
 @return 无
*/
uint8_t GetCurrentRGBWValue(void)
{
	return 1;
}
/****************************************************END OF FILE****************************************************/
