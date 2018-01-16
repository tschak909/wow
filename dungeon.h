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
 * dungeon_run() - dungeon code
 * dungeon_num - Dungeon Number to run
 */
void dungeon_run(unsigned char dungeon_num);

#endif /* DUNGEON_H */
