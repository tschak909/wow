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

/******************************************************
 * Includes                                           *
 ******************************************************/

/* Libraries */
#include "neslib.h"

/* Nametables */
#include "wow-monsters.h"
#include "wow-scores.h"

/******************************************************
 * Constants                                          *
 ******************************************************/

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
	128

};

const unsigned char* const metasprite_list[]={
	metasprite_data+0,
	metasprite_data+25,
	metasprite_data+50,
	metasprite_data+75,
	metasprite_data+100,
	metasprite_data+125,
	metasprite_data+150
};

/******************************************************
 * Variables                                          *
 ******************************************************/


/******************************************************
 * Zero Page Variables                                *
 ******************************************************/
#pragma bssseg (push,"ZEROPAGE")
#pragma dataseg(push,"ZEROPAGE")

static unsigned char i,j;               // Index counters
static unsigned char spr,ptr;           // Pointers
static unsigned char frame_cnt;         // Frame counter (up to 256 frames)
static unsigned char bright;            // Brightness counter.
