#ifndef VARIABLES_H
#define VARIABLES_H

#include "constants.h"

/******************************************************
 * Non-Zero Page Variables                            *
 ******************************************************/

/* BG Update Buffer */
unsigned char update_buffer[80]; 

/* Score registers */
unsigned char score0[7]={1,1,1,1,1,1,2};
unsigned char score1[7]={1,1,1,1,1,1,1};
unsigned char score2[7]={1,1,1,1,1,1,1};

unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];

/******************************************************
 * Zero Page Variables                                *
 ******************************************************/
#pragma bssseg (push,"ZEROPAGE")

unsigned char i,j,a,b,c,d;          // Index counters or temporary
unsigned char spr;                // Pointers
unsigned char frame_cnt;         // Frame counter (up to 256 frames)
unsigned char sec;               // counts from 49 to 0 (one second)
unsigned char bright;            // Brightness counter.
unsigned int adr;                // Address
unsigned char* str;              // String
unsigned char* dungeon;         // Dungeon pointer.
unsigned char* ptr;             // Generic reusable pointer.
unsigned char blue_door_state;  // Blue door state
unsigned char yellow_door_state; // Yellow door state
unsigned char teleport_state;   // Teleport state
unsigned char teleport_timer;   // Teleport timer
unsigned char player_trigger[2];          // Player shooting this frame?
unsigned char player_last_trigger[2];     // Player shooting last frame?
unsigned char player_shooting_last_state[2]; // State before player started shooting.

#endif /* VARIABLES_H */
