#ifndef UPDATE_H
#define UPDATE_H

/**
 * update_doors()
 */
void update_doors(void);

/**
 * set_teleport(openclose)
 * openclose = 0 for open, 1 for close
 */
void set_teleport(unsigned char openclose);

/**
 * update_teleport_timer(void)
 */
void update_teleport_timer(void);

/**
 * update_scores() - Update the score data for both players
 */
void update_scores(void);

/**
 * update_stamps() - Update the on-screen stamps
 */
void update_stamps(void);

/**
 * update_lasers() - Update the on-screen laser
 */
void update_lasers(void);

/**
 * update_box_timers() - Update the box timers, if active
 */
void update_box_timers(void);

#endif /* UPDATE_H */
