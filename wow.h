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
const unsigned char palette[16]={ 0x0f,0x11,0x16,0x28,0x0f,0x16,0x21,0x31,0x0f,0x28,0x16,0x11,0x0f,0x0c,0x1c,0x2c };

/* metasprites */
#include "metasprites.h"

/* metasprite animations */
#include "metasprite_animations.h"

/******************************************************
 * Variables                                          *
 ******************************************************/

/* BG Update Buffer */
static unsigned char update_buffer[48]; 

/* Score registers */
static unsigned char score0[7]={1,1,1,1,1,1,2};
static unsigned char score1[7]={1,1,1,1,1,1,1};
static unsigned char score2[7]={1,1,1,1,1,1,1};

/**
 * 8 objects on screen, two players and 6 enemies.
 *
 * [0] - Sprite X position
 * [1] - Sprite Y position
 * [2] - Sprite Type - (worrior, burwor, thurwor, gorwor... Bit 7 means empty.)
 * [3] - Sprite frame (0 to 3)
 * [4] - Sprite number of frames to delay
 * [5] - Dungeon Box X coordinate
 * [6] - Dungeon Box Y coordinate
 */
static unsigned char stamps[48]; // 8 slots

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
static unsigned char* dungeon;         // Dungeon pointer.
static unsigned char* ptr;             // Generic reusable pointer.
/****************************************************
 * Prototypes                                       *
 ****************************************************/

/**
 * pal_fade_to(unsigned to) - smoothly fade palette
 * to the given brightness value.
 */
void pal_fade_to(unsigned to);

/**
 * dungeon_red() - Turn dungeon red
 */
void dungeon_red();

/**
 * dungeon_blue() - Turn dungeon blue
 */
void dungeon_blue();

/**
 * double_score_win() - turn screen colors and set "DOUBLE SCORE" text on radar.
 */
void double_score_win(void);


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
 * set_door(player, openclose)
 * player = Player 0 (blue) or Player 1 (yellow) door.
 * openclose = 0 for open, 1 for close.
 */
void set_door(unsigned char player, unsigned char openclose);

/**
 * set_teleport(openclose)
 * openclose = 0 for open, 1 for close
 */
void set_teleport(unsigned char openclose);

/**
 * clear_update_buffer() - Clear the update buffer
 */
void clear_update_buffer(void);

/**
 * init() - just as it says.
 */
void init(void);

/**
 * update_scores() - Update the score data for both players
 */
void update_scores(void);

/**
 * add_points(player)
 * player = scoreX to add points in score0 to
 */
void add_points(unsigned char player);

/**
 * clear_stamps() - Clear the on screen stamp buffer
 */
void clear_stamps(void);

/**
 * place_stamps() - Update the on-screen stamps
 */
void place_stamps(void);


#endif /* WOW_H */

/* Notes */

// ULDR
// 1111
