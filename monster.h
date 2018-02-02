#ifndef MONSTER_H
#define MONSTER_H

/**
 * monster_move_all()
 * Move the monsters
 */
void monster_move_all(void);

/**
 * monster_setup_all() - Set up enemy sprite spawn points
 */
void monster_setup_all(void);

/**
 * monster_change_direction()
 * Change monster direction.
 */
void monster_change_direction(void);

/**
 * monster_shoot()
 * Fire phasor if worrior is nearby
 */
void monster_shoot(void);

/**
 * monster_laser_fire(i)
 * Start laser fire
 */
void monster_laser_fire(unsigned char player);

/**
 * monster_laser_stop(i);
 * Stop laser fire.
 */
void monster_laser_stop(unsigned char player);

/** 
 * monster_dead_add_player_points(player)
 * Monster shot, add points to score
 * monster dead coming from i.
 */
void monster_dead_add_player_points(unsigned char player);

/**
 * monster_die(player)
 * Monster was killed by player
 */
void monster_die(unsigned char player);

#endif /* MONSTER_H */
