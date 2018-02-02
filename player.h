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

/**
 * player_laser_fire()
 */
void player_laser_fire(unsigned char player);

/**
 * player_laser_stop()
 */
void player_laser_stop(unsigned char player);

/**
 * player_change_ai_direction()
 * Change the direction of the blue player
 */
void player_change_ai_direction();

/**
 * player_blue_move_ai()
 * Move Player AI if needed.
 */
void player_blue_move_ai(void);

/**
 * player_die(player)
 * Player was killed by player
 */
void player_die(unsigned char player);

/**
 * player_shot()
 * Player has been shot by something.
 */
void player_shot(void);

#endif /* PLAYER_H */
