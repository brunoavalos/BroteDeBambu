/*
 * app_DebBtn.c
 *
 *  Created on: 24 mar 2020
 *      Author: OmarSevilla
 */
#include "app_DebBtn.h"

typedef enum
{
	BTN_MEASSURE,
	BTN_DEBOUNCING,
	BTN_DEBOUNCED,
	N_BTN_STATES
}T_BTN_STATES;

T_BTN_STATES re_DebBtnState = BTN_MEASSURE;
unsigned char rub_DebCounter = 0u;
static unsigned char lub_ActualBtnState = 0u;
static unsigned char lub_PreviousBtnState = 0u;
unsigned char rub_ValidBtnState = 0u;

void app_DebBtn_SM_ButtonDebounce(void)
{
	//Action: Measure Button State
	lub_ActualBtnState = APP_DEBBTN_GET_BUTTON_STATE();

	switch(re_DebBtnState)
	{
	default:
	{
		re_DebBtnState = BTN_MEASSURE;
	}
	case BTN_MEASSURE:
	{
	    //Reset Button Debounce Counter
		rub_DebCounter = 0u;

		//Trigger: Button State Change
		if(lub_ActualBtnState != lub_PreviousBtnState)
		{
			re_DebBtnState = BTN_DEBOUNCING;
		}else{ /* Do Nothing */ };

	}break;
	case BTN_DEBOUNCING:
	{
		//Trigger: Any Change in Button State
		if(lub_ActualBtnState != lub_PreviousBtnState)
		{
			re_DebBtnState = BTN_MEASSURE;
		}
		else
		{
			//Increase Deb Counter
			rub_DebCounter++;
			if(rub_DebCounter >= T_DEBOUNCE)
			{//Trigger: Deb Counter Reach Debounce Time
				re_DebBtnState = BTN_DEBOUNCED;
			}else{/* Do Nothing */}
		}
	}break;
	case BTN_DEBOUNCED:
	{
		//Reset Button Debounce Counter
		rub_DebCounter = 0u;

		if(lub_ActualBtnState != lub_PreviousBtnState)
		{//Trigger: Button State Change
			re_DebBtnState = BTN_DEBOUNCING;
		}
		else
		{
			//Save Button State
			rub_ValidBtnState = lub_ActualBtnState;
		}

	}break;
	}

	lub_PreviousBtnState = lub_ActualBtnState;
}
