/*
 * BTN.cpp
 *
 * Created: 6/17/2023 2:50:40 PM
 *  Author: Master
 */ 


/*
 * BTN.c
 *
 * Created: 6/17/2023 6:42:24 AM
 *  Author: Master
 */ 

#include <Arduino.h>

#include "BTN.h"
#include "lcd_assert.h"


#define BTN_RIGHT					0
#define BTN_UP						1
#define BTN_DOWN					2
#define BTN_LEFT					3
#define BTN_SELECT					4


#define BTN_RIGHT_VALUE				0
#define BTN_UP_VALUE				120
#define BTN_DOWN_VALUE				256
#define BTN_LEFT_VALUE				410
#define BTN_SELECT_VALUE			640

#define BTN_MARGIN					100


#define BTN_RIGHT_VALUE_MAX			(BTN_RIGHT_VALUE+BTN_MARGIN)

#define BTN_UP_VALUE_MAX			(BTN_UP_VALUE+BTN_MARGIN)
#define BTN_UP_VALUE_MIN			(BTN_UP_VALUE-BTN_MARGIN)

#define BTN_DOWN_VALUE_MAX			(BTN_DOWN_VALUE+BTN_MARGIN)
#define BTN_DOWN_VALUE_MIN			(BTN_DOWN_VALUE-BTN_MARGIN)

#define BTN_LEFT_VALUE_MAX			(BTN_LEFT_VALUE+BTN_MARGIN)
#define BTN_LEFT_VALUE_MIN			(BTN_LEFT_VALUE-BTN_MARGIN)

#define BTN_SELECT_VALUE_MAX		(BTN_SELECT_VALUE+BTN_MARGIN)
#define BTN_SELECT_VALUE_MIN		(BTN_SELECT_VALUE-BTN_MARGIN)


static void (*ptrFunc[5])(void) = {
	BTN_RIGHT_HANDLER,
	BTN_UP_HANDLER,
	BTN_DOWN_HANDLER,
	BTN_LEFT_HANDLER,
	BTN_SELECT_HANDLER
};


void getBTN(){
	
	int analogReading = analogRead(0);

	if(analogReading == 0){
		ptrFunc[BTN_RIGHT]();
	}
	else if(analogReading <= BTN_UP_VALUE_MAX && analogReading >= BTN_UP_VALUE_MIN){
		ptrFunc[BTN_UP]();
	}
	else if(analogReading <= BTN_DOWN_VALUE_MAX && analogReading >= BTN_DOWN_VALUE_MIN){
		ptrFunc[BTN_DOWN]();
	}
	else if(analogReading <= BTN_SELECT_VALUE_MAX && analogReading >= BTN_SELECT_VALUE_MIN){
		ptrFunc[BTN_SELECT]();
	}
	
	else if(analogReading <= BTN_LEFT_VALUE_MAX && analogReading >= BTN_LEFT_VALUE_MIN){
		ptrFunc[BTN_LEFT]();
	}
	else{
		/* return error */
	}
}