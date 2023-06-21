/*
 * stateHandlers.cpp
 *
 * Created: 6/17/2023 10:36:31 PM
 *  Author: Master
 */ 


#include "Sketch.h"

#define PERIODICITY				1000


static uint32_t currentTime;

void stateIDLE_handler(){
	if(stateEntry == true){
		stateEntry = false;
		
		responseFrame.can_id = CAN_MSG_RESPONSE_ID;
		responseFrame.can_dlc = CAN_MSG_DLC;
		responseFrame.data[1] = RESPONSE_STOP;
		
		mcp2515.sendMessage(&responseFrame);
		
		currentTime = millis();
	}
	
	
	// Keep Sending STOP Frame Every 1 Second
	if(millis() - currentTime >= PERIODICITY){
		mcp2515.sendMessage(&responseFrame);
		currentTime = millis();
	}
	
	
	if(mainEvent == EVENT_START_VOTE){
		mainEvent = EVENT_IDLE;
		
		mainState = STATE_ACTIVE;
		stateExit = true;
	}
	
	if(stateExit == true){
		stateExit = false;
		
		stateEntry = true;
	}
}

void stateACTIVE_handler(){
	if(stateEntry == true){
		stateEntry = false;
		
		responseFrame.can_id = CAN_MSG_RESPONSE_ID;
		responseFrame.can_dlc = CAN_MSG_DLC;
		responseFrame.data[1] = RESPONSE_START;
		
		mcp2515.sendMessage(&responseFrame);
		
		uint32_t currentTime = millis();
		
	}
	
	
	// Keep Sending START Frame Every 1 Second
	if(millis() - currentTime >= PERIODICITY){
		mcp2515.sendMessage(&responseFrame);
		currentTime = millis();
	}
	
	
	if (mcp2515.readMessage(&voteFrame) == MCP2515::ERROR_OK && voteFrame.can_id == CAN_MSG_VOTE_ID){
		for (int i = 0; i<voteFrame.can_dlc; i++)  {  // print the data
			Serial.print(voteFrame.data[i],HEX);
			Serial.print(" ");
		}

		Serial.println();
	}
	
	if(mainEvent == EVENT_STOP_VOTE){
		mainEvent = EVENT_IDLE;
		
		mainState = STATE_IDLE;
		stateExit = true;
	}
	
	if(stateExit == true){
		stateExit = false;
		
		stateEntry = true;
	}
}