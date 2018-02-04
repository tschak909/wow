#ifndef VARIABLES_H
#define VARIABLES_H

#include "constants.h"

/******************************************************
 * Non-Zero Page Variables                            *
 ******************************************************/

/* BG Update Buffer */
unsigned char update_buffer[80]; 

/* Score registers */
unsigned char score0[7];
unsigned char score1[7]={1,1,1,1,1,1,1};
unsigned char score2[7]={1,1,1,1,1,1,1};

/**
 * PIXEL_BOX_X and PIXEL_BOX_Y multiply table.
 */
const unsigned char pixel_box_x[11]={12,36,60,84,108,132,156,180,204,228,252};
const unsigned char pixel_box_y[7]={18,42,66,90,114,138,162};

/******************************************************
 * Zero Page Variables                                *
 ******************************************************/
#pragma bssseg (push,"ZEROPAGE")

unsigned char i,j,a,b,c,d,e,f,g,h,k;          // Index counters or temporary
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
unsigned char monster_laser_count;           // Number of active monster lasers
unsigned char blue_worrior_ai;               // Is blue worrior under AI control?
unsigned char double_score_dungeon;          // Double score dungeon?
unsigned char player_shot_loop[2];           // player shot animation loop counters for each player.

unsigned char stamp_x[8];          // Stamp X position
unsigned char stamp_y[8];          // Stamp Y position
unsigned char stamp_type[8];       // Stamp type
unsigned char stamp_state[8];      // Stamp state
unsigned char stamp_last_state[8]; // Stamp last state
unsigned char stamp_frame[8];      // Stamp frame
unsigned char stamp_delay[8];      // STamp delay
unsigned char stamp_timer[8];      // Stamp timer
unsigned char stamp_pad[8];        // Stamp pad
unsigned char stamp_shooting[8];   // Stamp shooting
unsigned char stamp_move_delay[8]; // Stamp move delay

unsigned char laser_x[8];          // Laser X position
unsigned char laser_y[8];          // Laser Y position
unsigned char laser_type[8];       // Laser type
unsigned char laser_shooting[8];   // Laser shooting
unsigned char laser_direction[8];  // Laser direction
unsigned char laser_offset_x[8];   // Laser X offset
unsigned char laser_offset_y[8];   // Laser Y offset

#endif /* VARIABLES_H */
