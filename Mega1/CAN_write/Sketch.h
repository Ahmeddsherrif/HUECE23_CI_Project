/*
 * Sketch.h
 *
 * Created: 6/17/2023 6:48:25 AM
 *  Author: Master
 */ 


#ifndef SKETCH_H_
#define SKETCH_H_


/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <SPI.h>
#include <mcp2515.h>
#include <LiquidCrystal.h>


#include "BTN.h"
#include "lcd_assert.h"



#include <stdlib.h>

#define SS_PIN							49
#define ADC_RANDOM_GENERATOR_CHANNEL	2

#define LCD_ROWS						2
#define	LCD_COLUMNS						16

#define CAN_MSG_DLC						2

#define CAN_MSG_VOTE_ID					0x11
#define CAN_MSG_RESPONSE_ID				0x10

#define RESPONSE_START					0x01
#define RESPONSE_STOP					0x02

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;


typedef struct can_frame Frame; 

typedef enum{
	STATE_IDLE,
	STATE_ACTIVE,
	STATE_VOTED
}State_t;

typedef enum{
	EVENT_IDLE,
	EVENT_START_VOTE,
	EVENT_DONE_VOTE,
	EVENT_STOP_VOTE
}Event_t;


void stateIDLE_handler();
void stateACTIVE_handler();
void stateVOTED_handler();


void BTN_right_handler();
void BTN_up_handler();
void BTN_down_handler();
void BTN_left_handler();
void BTN_select_handler();

extern uint8_t deviceID;
extern Frame responseFrame;
extern Frame voteFrame;
extern LiquidCrystal lcd;
extern MCP2515 mcp2515;
extern uint8_t vote;
extern State_t mainState;
extern Event_t mainEvent;
extern bool stateEntry, stateExit;


#endif /* SKETCH_H_ */