#ifndef PLAYER_H
#define PLAYER_H

/**
 * player_blue_ready() - Ready the blue player
 */
void player_blue_ready(void);

/**
 * player_yellow_ready() - Ready the blue player
 */
void player_yellow_ready(void);

/**
 * player_idle()
 */
void player_idle(void);

/**
 * player_in_field()
 * Handle when player is on the playfield
 */
void player_in_field(void);

/**
 * player_in_box()
 * Handle when player is in box.
 */
void player_in_box(void);

/**
 * player_move_all()
 */
void player_move_all(void);

#endif /* PLAYER_H */
