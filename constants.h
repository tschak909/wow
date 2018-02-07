#ifndef CONSTANTS_H
#define CONSTANTS_H

/******************************************************
 * Constants                                          *
 ******************************************************/

/* States */
#define OPEN 0
#define CLOSED 1

#define YELLOW_SPAWN_X 208
#define YELLOW_SPAWN_Y 169

/* Door update, three tiles. */
#define NT_UPD_DOOR_BLUE 0
#define NT_UPD_DOOR_YELLOW 7 

/* Radar Update Nametable tiles */
#define NT_RADAR_OFF_X 11
#define NT_RADAR_OFF_Y 22

/**
 * Current OAM allocation
 * ----------------------
 * 48 : 6 enemy 2 player sprites as 2x3 metasprite
 *  6 : 6 radar dots
 *  8 : 8 phaser shots
 * -----------------------------------------------
 * 62 : total sprites used
 *  2 : sprites free
 */ 

/**
 * 8 objects on screen, two players and 6 enemies.
 */
#define STAMP_NUM_FIELDS     10                    // Number of fields in each stamp slot
#define STAMP_NUM_SLOTS      8                    // Number of slots in stamp structure
#define STAMP_CENTER_BIAS_X  12                   // Offset to apply to box multiply to center sprite (X)
#define STAMP_CENTER_BIAS_Y  10                   // Offset to apply to box multiply to center sprite (Y)

#define RADAR_SPR_OFFSET_X   88                   // Radar sprite top-left offset X
#define RADAR_SPR_OFFSET_Y   176                  // Radar sprite top-left offset Y

/**
 * Metasprite to OAM calculations
 * 256 bytes, divided into 4 byte fields leave 64 possible OAM slots
 * and thus, the first 192 slots are used for the two worriors and 6 enemies
 * the next 6 entries are reserved for the radar blips for each enemy (players do not show up)
 * the next 8 entries are used for phasers
 * leaving 8 entries free. (whee)
 */
#define SPRITE_SIZE_W      2
#define SPRITE_SIZE_H      3
#define OAM_OFFSET_TOP     0
#define OAM_FIELD_SIZE     4 /* The size of each OAM field. */
#define OAM_OFFSET_LASERS   ( ( ( SPRITE_SIZE_W * SPRITE_SIZE_H ) * STAMP_NUM_SLOTS ) * OAM_FIELD_SIZE )
#define OAM_OFFSET_RADAR    OAM_OFFSET_LASERS + 24

/**
 * Metasprite constants
 */
#define STAMP_TYPE_BLUE_WORRIOR     0
#define STAMP_TYPE_BURWOR           96
#define STAMP_TYPE_GORWOR           112
#define STAMP_TYPE_THORWOR          128
#define STAMP_TYPE_WORLUK           144
#define STAMP_TYPE_YELLOW_WORRIOR   160
#define STAMP_TYPE_EXPLOSION        256
#define STAMP_TYPE_DEAD             257

#define STATE_MONSTER_RIGHT         0
#define STATE_MONSTER_LEFT          1
#define STATE_MONSTER_UP            2
#define STATE_MONSTER_DOWN          3

#define STATE_PLAYER_RIGHT                  0
#define STATE_PLAYER_RIGHT_IDLE             1
#define STATE_PLAYER_LEFT                   2
#define STATE_PLAYER_LEFT_IDLE              3
#define STATE_PLAYER_UP                     4
#define STATE_PLAYER_UP_IDLE                5
#define STATE_PLAYER_DOWN                   6
#define STATE_PLAYER_DOWN_IDLE              7
#define STATE_PLAYER_RIGHT_SHOOTING         8
#define STATE_PLAYER_RIGHT_IDLE_SHOOTING    9
#define STATE_PLAYER_LEFT_SHOOTING          10
#define STATE_PLAYER_LEFT_IDLE_SHOOTING     11
#define STATE_PLAYER_UP_SHOOTING            12
#define STATE_PLAYER_UP_IDLE_SHOOTING       13
#define STATE_PLAYER_DOWN_SHOOTING          14
#define STATE_PLAYER_DOWN_IDLE_SHOOTING     15
#define STATE_PLAYER_RIGHT_SHOT             16
#define STATE_PLAYER_RIGHT_IDLE_SHOT        17
#define STATE_PLAYER_LEFT_SHOT              18
#define STATE_PLAYER_LEFT_IDLE_SHOT         19
#define STATE_PLAYER_UP_SHOT                20
#define STATE_PLAYER_UP_IDLE_SHOT           21
#define STATE_PLAYER_DOWN_SHOT              22
#define STATE_PLAYER_DOWN_IDLE_SHOT         23
#define STATE_DYING                         254
#define STATE_DEAD                          255

#define STATE_ADD_SHOOTING                  8

/** 
 * Laser stamp fields 
 */

#define LASER_NUM_FIELDS     7
#define LASER_NUM_SLOTS      8

#define LASER_CENTER_BIAS_X  12
#define LASER_CENTER_BIAS_Y  10

/**
 * Laser sprite constants 
 */
#define SPRITE_LASER_PLAYER                0xC8
#define SPRITE_LASER_ENEMY                 0xC9
#define LASER_X_OFFSET_H                   0
#define LASER_Y_OFFSET_H                   5
#define LASER_X_OFFSET_V                   5
#define LASER_Y_OFFSET_V                   0
#define LASER_MONSTER_MAX                  2

#endif /* CONSTANTS_H */

