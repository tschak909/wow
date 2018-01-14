#ifndef VARIABLES_H
#define VARIABLES_H

#include "constants.h"

/******************************************************
 * Non-Zero Page Variables                            *
 ******************************************************/

/* BG Update Buffer */
static unsigned char update_buffer[80]; 

/* Score registers */
static unsigned char score0[7]={1,1,1,1,1,1,2};
static unsigned char score1[7]={1,1,1,1,1,1,1};
static unsigned char score2[7]={1,1,1,1,1,1,1};

static unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];

/******************************************************
 * Zero Page Variables                                *
 ******************************************************/
#pragma bssseg (push,"ZEROPAGE")

static unsigned char i,j,a,b,c,d;          // Index counters or temporary
static unsigned char spr;                // Pointers
static unsigned char frame_cnt;         // Frame counter (up to 256 frames)
static unsigned char sec;               // counts from 49 to 0 (one second)
static unsigned char bright;            // Brightness counter.
static unsigned int adr;                // Address
static unsigned char* str;              // String
static unsigned char* dungeon;         // Dungeon pointer.
static unsigned char* ptr;             // Generic reusable pointer.
static unsigned char blue_door_state;  // Blue door state
static unsigned char yellow_door_state; // Yellow door state
static unsigned char teleport_state;   // Teleport state
static unsigned char teleport_timer;   // Teleport timer
// static unsigned char player_shooting[2];          // Player shooting this frame?
// static unsigned char player_last_shooting[2];     // Player shooting last frame?

#endif /* VARIABLES_H */
