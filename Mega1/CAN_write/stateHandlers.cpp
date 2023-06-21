/*
 * stateHandlers.cpp
 *
 * Created: 6/17/2023 8:26:33 PM
 *  Author: Master
 */ 

#include "Sketch.h"

void stateIDLE_handler(){
	if(stateEntry == true){
		stateEntry = false;
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("STATE: IDLE");
		
		lcd.setCursor(0,1);
		lcd.print("Device ID: ");
		lcd.print(deviceID);
		
		vote = 0;
	}
	
	if(mcp2515.readMessage(&responseFrame) == MCP2515::ERROR_OK && responseFrame.can_id == CAN_MSG_RESPONSE_ID){
		switch(responseFrame.data[1]){
			case RESPONSE_START:{
				mainEvent = EVENT_START_VOTE;
				break;
			}
			default:{
					
			}
		}
	}
	
	if(mainEvent == EVENT_START_VOTE){
		mainEvent = EVENT_IDLE;
		
		mainState = STATE_ACTIVE;
		stateExit = true;
	}
	
	
	if(stateExit == true){
		stateEntry = true;
		
		
		stateExit = false;
	}
	
}


void stateACTIVE_handler(){
	if(stateEntry == true){
		stateEntry = false;
		
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("STATE: ACTIVE");
		
		lcd.setCursor(0,1);
		lcd.print("SELECTION: ");
		lcd.print("-");
	}
	
	
	lcd.setCursor(11,1);
	if(vote != 0){
		lcd.print((char)vote);
	}
	
	getBTN();
	
	if(mcp2515.readMessage(&responseFrame) == MCP2515::ERROR_OK && responseFrame.can_id == CAN_MSG_RESPONSE_ID){
		switch(responseFrame.data[1]){
			case RESPONSE_STOP:{
				mainEvent = EVENT_STOP_VOTE;
				break;
			}
			default:{
				
			}
		}
	}
	
	switch(mainEvent){
		case EVENT_STOP_VOTE:{
			mainEvent = EVENT_IDLE;
			
			mainState = STATE_IDLE;
			stateExit = true;	
			break;
		}

		case EVENT_DONE_VOTE:{
			mainEvent = EVENT_IDLE;
			
			mainState = STATE_VOTED;
			stateExit = true;
		}
		
		default:{
			
		}
	}
	
	if(stateExit == true){
		stateExit = false;
		
		stateEntry = true;
	}
}

void stateVOTED_handler(){
	if(stateEntry == true){
		stateEntry = false;
		
		voteFrame.can_id = CAN_MSG_VOTE_ID;
		voteFrame.can_dlc = CAN_MSG_DLC;
		voteFrame.data[0] = deviceID;
		voteFrame.data[1] = vote;
		
		mcp2515.sendMessage(&voteFrame);
		
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("STATE: VOTED");
		
		lcd.setCursor(0,1);
		lcd.print("SELECTION: ");
		lcd.print((char)vote);
	}
	
	if(mcp2515.readMessage(&responseFrame) == MCP2515::ERROR_OK && responseFrame.can_id == CAN_MSG_RESPONSE_ID){
		switch(responseFrame.data[1]){
			case RESPONSE_STOP:{
				mainEvent = EVENT_STOP_VOTE;
				break;
			}
			default:{
				
			}
		}
	}
	
	switch(mainEvent){
		case EVENT_STOP_VOTE:{
			mainEvent = EVENT_IDLE;
			stateExit = true;
			
			mainState = STATE_IDLE;
			break;
		}
		default:{
			
		}
	}
	
	if(stateExit == true){
		stateExit = false;
		
		stateEntry = true;
	}
}