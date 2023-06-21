#include "Sketch.h"

MCP2515 mcp2515(SS_PIN);
Frame responseFrame;
Frame voteFrame;
State_t mainState;
Event_t mainEvent;
bool stateEntry, stateExit;

void setup() {
	Serial.begin(9600);
	
	mcp2515.reset();
	mcp2515.setBitrate(CAN_125KBPS);
	mcp2515.setNormalMode();

	mainState = STATE_IDLE;
	mainEvent = EVENT_IDLE;
	
	stateEntry = true;
	stateExit = false;
}


void loop() {

	if (Serial.available() > 0) { 
		char input = Serial.read(); 

		switch(input){
			case 's':
			case 'S':{
				mainEvent = EVENT_START_VOTE;
				break;
			}
			case 'x':
			case 'X':{
				mainEvent = EVENT_STOP_VOTE;
				break;
			}
		}
	}
	
	
	switch(mainState){
		case STATE_IDLE:{
			stateIDLE_handler();
			break;
		}
			
		case STATE_ACTIVE:{
			stateACTIVE_handler();
			break;
		}
		default:{
			
		}
	}
}
