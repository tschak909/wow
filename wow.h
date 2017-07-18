/*******************************************************
 * __      _____ ____  _   ___ ___     ___  ___
 * \ \    / /_ _|_  / /_\ | _ \   \   / _ \| __|
 *  \ \/\/ / | | / / / _ \|   / |) | | (_) | _|
 *   \_/\_/ |___/___/_/ \_\_|_\___/   \___/|_|
 *
 *           __      _____  ___
 *           \ \    / / _ \| _ \
 *            \ \/\/ / (_) |   /
 *             \_/\_/ \___/|_|_\
 *
 * Version: 0.0
 *
 * Author: 
 *  Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 *
 * Started:       2017-06-12
 * Code Started:  2017-07-05
 *
 ******************************************************/

#ifndef WOW_H
#define WOW_H

/******************************************************
 * Includes                                           *
 ******************************************************/

/* Libraries */
#include "neslib.h"

/* Nametables */
#include "wow_monsters.h"
#include "wow_scores.h"
#include "wow_dungeon.h"

/* Dungeons */
#include "dungeon1.h"
#include "dungeons.h"

/******************************************************
 * Constants                                          *
 ******************************************************/

#define YELLOW_SPAWN_X 208
#define YELLOW_SPAWN_Y 169

/* Door update, three tiles. */
#define NT_UPD_DOOR_BLUE 0
#define NT_UPD_DOOR_YELLOW 7 

/* Palettes */
const unsigned char palette[16]={ 0x0f,0x11,0x16,0x3a,0x0f,0x16,0x21,0x31,0x0f,0x3a,0x16,0x11,0x0f,0x0c,0x1c,0x2c };

/* Metasprites */

const unsigned char metasprite_data[]={

	  0,  0,0x17,0|OAM_FLIP_H,
	  8,  0,0x16,0|OAM_FLIP_H,
	  0,  8,0x27,0|OAM_FLIP_H,
	  8,  8,0x26,0|OAM_FLIP_H,
	  0, 16,0x37,0|OAM_FLIP_H,
	  8, 16,0x36,0|OAM_FLIP_H,
	128,

	  0,  0,0x1d,2|OAM_FLIP_H,
	  8,  0,0x1c,2|OAM_FLIP_H,
	  0,  8,0x2d,2|OAM_FLIP_H,
	  8,  8,0x2c,2|OAM_FLIP_H,
	  0, 16,0x3d,2|OAM_FLIP_H,
	  8, 16,0x3c,2|OAM_FLIP_H,
	128,

	  0,  0,0x43,1|OAM_FLIP_H,
	  8,  0,0x42,1|OAM_FLIP_H,
	  0,  8,0x53,1|OAM_FLIP_H,
	  8,  8,0x52,1|OAM_FLIP_H,
	  0, 16,0x63,1|OAM_FLIP_H,
	  8, 16,0x62,1|OAM_FLIP_H,
	128,

	  8,  0,0x4a,2|OAM_FLIP_H,
	  0,  0,0x4b,2|OAM_FLIP_H,
	  8,  8,0x5a,2|OAM_FLIP_H,
	  0,  8,0x5b,2|OAM_FLIP_H,
	  0, 16,0x6b,2|OAM_FLIP_H,
	  8, 16,0x6a,2|OAM_FLIP_H,
	128,

	  0,  0,0x4e,2,
	  8,  0,0x4f,2,
	  0,  8,0x5e,2,
	  8,  8,0x5f,2,
	  0, 16,0x6e,2,
	  8, 16,0x6f,2,
	128,

	  0,  0,0x11,0|OAM_FLIP_H,
	  8,  0,0x10,0|OAM_FLIP_H,
	  0,  8,0x21,0|OAM_FLIP_H,
	  8,  8,0x20,0|OAM_FLIP_H,
	  0, 16,0x31,0|OAM_FLIP_H,
	  8, 16,0x30,0|OAM_FLIP_H,
	128,

	  0,  0,0x11,2|OAM_FLIP_H,
	  8,  0,0x10,2|OAM_FLIP_H,
	  0,  8,0x21,2|OAM_FLIP_H,
	  8,  8,0x20,2|OAM_FLIP_H,
	  0, 16,0x31,2|OAM_FLIP_H,
	  8, 16,0x30,2|OAM_FLIP_H,
	128,

	  8,  0,0x12,2|OAM_FLIP_H,
	  0,  0,0x13,2|OAM_FLIP_H,
	  8,  8,0x22,2|OAM_FLIP_H,
	  0,  8,0x23,2|OAM_FLIP_H,
	  8, 16,0x32,2|OAM_FLIP_H,
	  0, 16,0x33,2|OAM_FLIP_H,
	128,

	  8,  0,0x14,2|OAM_FLIP_H,
	  0,  0,0x15,2|OAM_FLIP_H,
	  8,  8,0x24,2|OAM_FLIP_H,
	  0,  8,0x25,2|OAM_FLIP_H,
	  8, 16,0x34,2|OAM_FLIP_H,
	  0, 16,0x35,2|OAM_FLIP_H,
	128,

	 16,  8,0xa0,2|OAM_FLIP_H,
	 16,  0,0x90,2|OAM_FLIP_H,
	  8,  8,0xa1,2|OAM_FLIP_H,
	  8,  0,0x91,2|OAM_FLIP_H,
	  0,  8,0xa2,2|OAM_FLIP_H,
	  0,  0,0x92,2|OAM_FLIP_H,
	128,

	 16,  8,0x80,2|OAM_FLIP_H,
	 16,  0,0x70,2|OAM_FLIP_H,
	  8,  0,0x71,2|OAM_FLIP_H,
	  8,  8,0x81,2|OAM_FLIP_H,
	  0,  0,0x72,2|OAM_FLIP_H,
	  0,  8,0x82,2|OAM_FLIP_H,
	128,

	 16,  8,0x83,2|OAM_FLIP_H,
	 16,  0,0x73,2|OAM_FLIP_H,
	  8,  8,0x84,2|OAM_FLIP_H,
	  8,  0,0x74,2|OAM_FLIP_H,
	  0,  8,0x85,2|OAM_FLIP_H,
	  0,  0,0x75,2|OAM_FLIP_H,
	128,

	  0,  0,0x18,0,
	  8,  0,0x19,0,
	  0,  8,0x28,0,
	  8,  8,0x29,0,
	  0, 16,0x38,0,
	  8, 16,0x39,0,
	128,

	  0,  0,0x16,0,
	  8,  0,0x17,0,
	  0,  8,0x26,0,
	  8,  8,0x27,0,
	  0, 16,0x36,0,
	  8, 16,0x37,0,
	128

};

const unsigned char* const metasprite_list[]={
	metasprite_data+0,
	metasprite_data+25,
	metasprite_data+50,
	metasprite_data+75,
	metasprite_data+100,
	metasprite_data+125,
	metasprite_data+150,
	metasprite_data+175,
	metasprite_data+200,
	metasprite_data+225,
	metasprite_data+250,
	metasprite_data+275,
	metasprite_data+300,
	metasprite_data+325
};

/******************************************************
 * Variables                                          *
 ******************************************************/

/* Update Buffer */
static unsigned char update_buffer[48]; 

/******************************************************
 * Zero Page Variables                                *
 ******************************************************/
#pragma bssseg (push,"ZEROPAGE")
#pragma dataseg(push,"ZEROPAGE")

static unsigned char i,j,a,b,c,d;          // Index counters or temporary
static unsigned char spr;                // Pointers
static unsigned char frame_cnt;         // Frame counter (up to 256 frames)
static unsigned char bright;            // Brightness counter.
static unsigned int adr;                // Address
static unsigned char* str;              // String
static const unsigned char* dungeon;         // Dungeon pointer.
/****************************************************
 * Prototypes                                       *
 ****************************************************/

/**
 * pal_fade_to(unsigned to) - smoothly fade palette
 * to the given brightness value.
 */
void pal_fade_to(unsigned to);

/**
 * run_dungeon() - dungeon code
 * dungeon_num - Dungeon Number to run
 */
void run_dungeon(unsigned char dungeon_num);

/**
 * attract_score() - show scores
 */
void attract_scores(void);

/**
 * attract_monsters() - shown while game isn't playing
 */
void attract_monsters(void);

/**
 * clear_update_buffer() - Clear the update buffer
 */
void clear_update_buffer(void);

/**
 * init() - just as it says.
 */
void init(void);


#endif /* WOW_H */

/* Notes */

// ULDR
// 1111
