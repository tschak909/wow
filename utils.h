#ifndef UTILS_H
#define UTILS_H

/**
 * clear_update_buffer() - Clear the update buffer
 */
void clear_update_buffer(void);

/**
 * clear_stamps() - Clear the on screen stamp buffer
 */
void clear_stamps(void);

/**
 * pal_fade_to(unsigned to) - smoothly fade palette
 * to the given brightness value.
 */
void pal_fade_to(unsigned to);

/**
 * add_points(player)
 * player = scoreX to add points in score0 to
 */
void add_points(unsigned char player);

/**
 * stamp_type_to_radar(t) - Choose radar sprite to use 
 */
unsigned char stamp_type_to_radar(unsigned char t);

/**
 * is_stamp_visible()
 * given stamp i, see if it actually is visible, or needs to be moved offscreen.
 */
unsigned char is_stamp_visible(void);


#endif
