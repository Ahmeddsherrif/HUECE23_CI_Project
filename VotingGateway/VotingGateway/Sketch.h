/*
 * Sketch.h
 *
 * Created: 6/17/2023 10:27:25 PM
 *  Author: Master
 */ 


#ifndef SKETCH_H_
#define SKETCH_H_

#include <Arduino.h>

#include <SPI.h>
#include <mcp2515.h>


#define SS_PIN							10

#define CAN_MSG_DLC						2

#define CAN_MSG_VOTE_ID					0x11
#define CAN_MSG_RESPONSE_ID				0x10

#define RESPONSE_START					0x01
#define RESPONSE_STOP					0x02


typedef enum{
	STATE_IDLE,
	STATE_ACTIVE
}State_t;

typedef enum{
	EVENT_IDLE,
	EVENT_START_VOTE,
	EVENT_STOP_VOTE
}Event_t;

void stateIDLE_handler();
void stateACTIVE_handler();

typedef struct can_frame Frame; 

extern MCP2515 mcp2515;
extern Frame responseFrame;
extern Frame voteFrame;
extern State_t mainState;
extern Event_t mainEvent;
extern bool stateEntry, stateExit;



#endif /* SKETCH_H_ */