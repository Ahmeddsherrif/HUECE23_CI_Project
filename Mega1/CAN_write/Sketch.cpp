#include "Sketch.h"


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MCP2515 mcp2515(SS_PIN);

uint8_t deviceID;

Frame responseFrame;
Frame voteFrame;

uint8_t vote;

State_t mainState;
Event_t mainEvent;
bool stateEntry, stateExit;




void setup() {
	mainState = STATE_IDLE;
	mainEvent = EVENT_IDLE;
	
	stateEntry = true;
	stateExit = false;
	
	srand(analogRead(ADC_RANDOM_GENERATOR_CHANNEL));
	deviceID = rand() % 0xFF;
	
	lcd.begin(LCD_COLUMNS, LCD_ROWS);
	lcd.clear();
	
	mcp2515.reset();
	mcp2515.setBitrate(CAN_125KBPS);
	mcp2515.setNormalMode();
	
	lcd.setCursor(0,0);
	lcd.print("4.5 Leaders");
	delay(2000);
	lcd.clear();
}

void loop() {
	
	switch(mainState){
		case STATE_IDLE:{
			stateIDLE_handler();
			break;
		}
		
		case STATE_ACTIVE:{
			stateACTIVE_handler();
			break;
		}
		
		case STATE_VOTED:{
			stateVOTED_handler();
			break;
		}
		
		default:{
			
		}
	}
}




void BTN_left_handler(){
	vote = 'A';
}

void BTN_up_handler(){
	vote = 'B';
}

void BTN_down_handler(){
	vote = 'C';
}

void BTN_right_handler(){
	vote = 'D';
}

void BTN_select_handler(){
	if(vote != 0){
		mainEvent = EVENT_DONE_VOTE;
	}
}
