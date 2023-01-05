#include "board_key.h"

KEY_Status  key_status;
int  new_key_status = 0;
int old_key_status = 0;
int key_code;
int key_hold_16hz_counter;

#define KEY_LONG_PRESS_THRESHOLD_LOW	10//30
#define KEY_LONG_PRESS_THRESHOLD_HIGH	48


#define LOG_STRING	LOG_I

/*******************************************************************************
*Function	:Read_keyboard
*Descriptor	:read key value
*Input		:none
*Return		:none
*Hist		:
*******************************************************************************/
void Key_Init(void)
{
	
}


/*******************************************************************************
*Function	:Read_keyboard
*Descriptor	:read key value
*Input		:none
*Return		:none
*Hist		:
*******************************************************************************/

int Read_keyboard(void)
{
	int temp = 0;
	u32 key_val;
	uint8_t gpioValue;
//	if(bxd_gpio_read(BX_GPIOA, &key_val)==0)
//	{
//		temp += KEY_1;
//	}
	//	if(bxd_gpio_read(BX_GPIOA, &key_1)==0)
//	{
//		temp += KEY_2;
//	}
	
	gpioValue = key_val >> key_0 & 0x01;

	if(gpioValue==0)
	{
		temp += KEY_1;
//		LOG_STRING("gpioValue	key_0	%d\n",gpioValue);
	}
	gpioValue = key_val >> key_1 & 0x01;

	if(gpioValue==0)
	{
		temp += KEY_2;
//		LOG_STRING("gpioValue	key_1	%d\n",gpioValue);

	}
	
///	LOG_STRING("Read_keyboard	%d\n",temp);
	return (temp);
}  

/*******************************************************************************
*Function	:key_scan
*Descriptor	:read key value
*Input		:none
*Return		:none
*Hist		:
*******************************************************************************/
void key_scan(void)
{
	key_hold_16hz_counter++;
	new_key_status = Read_keyboard();
	
	if(key_status.clickDelay)
	{
		key_status.clickDelay--;
	}
	//×éºÏ°´¼ü	
	//===================================================================================
	if(new_key_status != 0)			// any key press
	{
//		LOG_STRING("key_scan  :%d\r\n",(int)new_key_status);
	//	LOG_STRING("old_key_status  :%d\r\n",(int)old_key_status);

		//===============================================================================
		if(old_key_status==0)	// just press
		{
			switch(new_key_status)
			{
				case KEY_1:
					key_code = PRESS_BUTTON_1;
//					LOG_STRING("PRESS_BUTTON_POWER\r\n");
					break;
				
				case KEY_2:
					key_code = PRESS_BUTTON_2;
//					LOG_STRING("PRESS_BUTTON_2\r\n");
					break;
				
				default:
					break;
			}
			key_status.clickDelay = 3*16;
			key_hold_16hz_counter = 0;
			old_key_status=new_key_status;		//update keyboard status
		}
		else if (old_key_status==new_key_status)	//hold
		{
//			if(key_status.holdkey==0)
			{
//				LOG_STRING("HOLD_BUTTON  -------%d\r\n",key_hold_16hz_counter);
				key_status.holdkey = 1;
				switch(new_key_status)
				{
					case KEY_1:
						if(key_hold_16hz_counter>KEY_LONG_PRESS_THRESHOLD_LOW )
						{
							key_code = LONG_PRESS_BUTTON_1;
//							LOG_STRING("LONG_PRESS_BUTTON_1\r\n");
						}
//						else if(key_hold_16hz_counter>KEY_LONG_PRESS_THRESHOLD_HIGH)
//						{
//							key_code = HOLD_BUTTON_1;
////							LOG_STRING("HOLD_BUTTON_1\r\n");
//						}
						break;
					case KEY_2:
						if(key_hold_16hz_counter>KEY_LONG_PRESS_THRESHOLD_LOW )
						{
							key_code = LONG_PRESS_BUTTON_2;
//							LOG_STRING("LONG_PRESS_BUTTON_2\r\n");
						}
//						else if(key_hold_16hz_counter>KEY_LONG_PRESS_THRESHOLD_HIGH)
//						{
//							key_code = HOLD_BUTTON_2;
////							LOG_STRING("HOLD_BUTTON_2\r\n");
//						}
						break;
				}
			}
		}
		else	// press key irregularly
		{
			key_hold_16hz_counter=0;
			old_key_status=new_key_status;		//update
		}
	}
	else	//all keys release
	{
		key_status.holdkey = 0;
		key_hold_16hz_counter = 0;
		if(old_key_status == 0)	// already release
		{
			key_status.processed = 0;
			key_code = 0;
		}
		else
		{
//			LOG_STRING("key_code:%d\r\n",key_code );
			switch(old_key_status)
			{
				case KEY_1:
					if(key_code == PRESS_BUTTON_1)
					{
						key_code = CLICK_BUTTON_1;
//						LOG_STRING("CLICK_BUTTON_1\r\n");
					}
					else 
					{
						key_code = RELEASE_BUTTON_1;
//						LOG_STRING("RELEASE_BUTTON_1\r\n");
					}
					break;
					
				case KEY_2:
					if(key_code == PRESS_BUTTON_2)
					{
						key_code = CLICK_BUTTON_2;
//						LOG_STRING("CLICK_BUTTON_2\r\n");
					}
					else 
					{
						key_code = RELEASE_BUTTON_2;
//					LOG_STRING("RELEASE_BUTTON_2\r\n");
					}
					break;
					
				default:
					break;
			}
			old_key_status = new_key_status;	//update
		}
	}
}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
uint8_t getButton(void)
{
	return key_code;
}

/**
  * @brief  
  * @param  argument: Not used 
  * @retval None
  */
uint8_t getKeyLock(void)
{
	return key_status.lock;
}


/**
  * @brief  
  * @param  argument: Not used 
  * @retval None
  */
void setKeyLock(uint8_t lock)
{
	switch(lock)
	{
		case KEYBOARD_LOCK:
			key_status.lock = 1;
			break;
		
		case KEYBOARD_UNLOCK:
			key_status.lock = 0;
			break;
		
		case KEYBOARD_TRIGGER:
			key_status.lock = !key_status.lock;
			break;
	}
	LOG_STRING("key_status  :%d\r\n",key_status.lock);
}



/**
  * @brief  
  * @param  argument: Not used 
  * @retval None
  */
uint8_t getKeyClick(void)
{
	return key_status.clickDelay;
}