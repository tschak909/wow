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

#include "constants.h"
#include "variables.h"
#include "macros.h"
#include "neslib.h"
#include "palette.h"
#include "metasprites.h"
#include "metasprite_animations.h"

/****************************************************
 * Externs                                          *
 ****************************************************/
extern void attract_monsters(void);
extern void attract_scores(void);
extern void clear_stamps(void);
extern void clear_update_buffer(void);
extern void run_dungeon(unsigned char dungeon_num);
extern void update_doors(void);
extern void set_teleport(unsigned char openclose);
extern void update_teleport_timer(void);
extern void update_scores(void);
extern void update_stamps(void);
extern void update_box_timers(void);

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
void dungeon_red(void);

/**
 * dungeon_blue() - Turn dungeon blue
 */
void dungeon_blue(void);

/**
 * double_score_win() - turn screen colors and set "DOUBLE SCORE" text on radar.
 */
void double_score_win(void);

/**
 * move_monsters()
 * Move the monsters
 */
void move_monsters(void);

/**
 * get_current_box()
 * Get the current dungeon box for player
 * i = the stamp to return in a,b,c,d
 * a = the X box
 * b = the Y box
 * c = the dungeon box #
 * d = the box data.
 */
void get_current_box(void);

/**
 * init() - just as it says.
 */
void init(void);

/**
 * add_points(player)
 * player = scoreX to add points in score0 to
 */
void add_points(unsigned char player);


#endif /* WOW_H */

/* Notes */

// ULDR
// 1111
