#ifndef DUNGEON_H
#define DUNGEON_H

/**
 * dungeon_red() - Turn dungeon red
 */
void dungeon_red(void);

/**
 * dungeon_blue() - Turn dungeon blue
 */
void dungeon_blue(void);

/**
 * dungeon_double_score_win() - turn screen colors and set "DOUBLE SCORE" text on radar.
 */
void dungeon_double_score_win(void);

/**
 * dungeon_print_name(unsigned char dungeon_num)
 * Print the dungeon name given dungeon number
 */
void dungeon_print_name(unsigned char dungeon_num);

/**
 * dungeon_draw(unsigned char dungeon_num)
 * Draw the requested dungeon into VRAM
 */
void dungeon_draw(unsigned char dungeon_num);

/**
 * dungeon_update_counters() - Update dungeon counter(s)
 * Update the frame and second counters to be used for timers etc.
 */
void dungeon_update_counters(void);

/**
 * dungeon_run() - dungeon code
 * dungeon_num - Dungeon Number to run
 */
void dungeon_run(unsigned char dungeon_num);

#endif /* DUNGEON_H */
