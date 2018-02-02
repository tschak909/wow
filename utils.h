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
unsigned char stamp_type_to_radar(unsigned int t);

/**
 * is_stamp_visible()
 * given stamp i, see if it actually is visible, or needs to be moved offscreen.
 */
unsigned char is_stamp_visible(void);

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
 * get_current_laser_box()
 * Get the current dungeon box for a laser
 * i = the stamp to return in e,f,g,h
 * e = the X box
 * f = the Y box
 * g = the dungeon box #
 * h = the box data.
 */
void get_current_laser_box(void);

/**
 * animate_stamps() - increment the frame counters of each sprite, (0-7)
 * applying delay to the non-player sprites (2-7)
 */
void animate_stamps(void);

#endif /* UTILS_H */
