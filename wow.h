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
extern void dungeon_run(unsigned char dungeon_num);
extern void update_doors(void);
extern void set_teleport(unsigned char openclose);
extern void update_teleport_timer(void);
extern void update_scores(void);
extern void update_stamps(void);
extern void update_box_timers(void);
extern void get_current_box(void);

/****************************************************
 * Prototypes                                       *
 ****************************************************/

/**
 * init() - just as it says.
 */
void init(void);

#endif /* WOW_H */

/* Notes */

// ULDR
// 1111
