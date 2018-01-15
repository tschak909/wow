#ifndef PLAYER_H
#define PLAYER_H

/**
 * ready_blue_player() - Ready the blue player
 */
void ready_blue_player(void);

/**
 * ready_yellow_player() - Ready the blue player
 */
void ready_yellow_player(void);

/**
 * handle_pad_idle()
 */
void handle_pad_idle(void);

/**
 * handle_player_in_field()
 * Handle when player is on the playfield
 */
void handle_player_in_field(void);

/**
 * handle_player_in_box()
 * Handle when player is in box.
 */
void handle_player_in_box(void);

/**
 * move_players()
 */
void move_players(void);

#endif /* PLAYER_H */
