#ifndef MACROS_H
#define MACROS_H

#define STAMP_NUM(x)         (x*STAMP_NUM_FIELDS) // Stamp Number
#define STAMP_X(x)           (STAMP_NUM(x)+0)     // Stamp Field: X pixel position
#define STAMP_Y(x)           (STAMP_NUM(x)+1)     // Stamp Field: Y pixel position
#define STAMP_TYPE(x)        (STAMP_NUM(x)+2)     // Stamp Field: Type
#define STAMP_STATE(x)       (STAMP_NUM(x)+3)     // Stamp Field: state (which frames to use).
#define STAMP_LAST_STATE(x)  (STAMP_NUM(x)+4)
#define STAMP_FRAME(x)       (STAMP_NUM(x)+5)     // Stamp Field: Current frame
#define STAMP_DELAY(x)       (STAMP_NUM(x)+6)     // Stamp Field: Delay
#define STAMP_TIMER(x)       (STAMP_NUM(x)+7)     // Stamp Field: Extra A (Player Timer)
#define STAMP_PAD(x)         (STAMP_NUM(x)+8)     // Stamp Field: Extra B (Player Pad Data)
#define STAMP_SHOOTING(x)    (STAMP_NUM(x)+9)     // Stamp Field: Is stamp shooting?

#define PLAYER_PAD(x)        (stamps[STAMP_PAD(x)])    // Alias for reading stored player pad value.
#define PLAYER_PAD_RIGHT(x)  (PLAYER_PAD(x)&PAD_RIGHT) // is player pressing right?
#define PLAYER_PAD_LEFT(x)   (PLAYER_PAD(x)&PAD_LEFT) // is player pressing left?
#define PLAYER_PAD_DOWN(x)   (PLAYER_PAD(x)&PAD_DOWN) // is player pressing down?
#define PLAYER_PAD_UP(x)     (PLAYER_PAD(x)&PAD_UP) // is player pressing up?
#define PLAYER_PAD_A(x)      (PLAYER_PAD(x)&PAD_A)  // is player pressing A
#define PLAYER_PAD_B(x)      (PLAYER_PAD(x)&PAD_B)  // is player pressing B
#define PLAYER_PAD_SELECT(x) (PLAYER_PAD(x)&PAD_SELECT) // is player pressing select?
#define PLAYER_PAD_START(x)  (PLAYER_PAD(x)&PAD_START)  // is player pressing start?
#define PLAYER_PAD_IDLE(x)   ((PLAYER_PAD(x)&0x0F)==0)  // is player idle?
  
#define PIXEL_BOX_X(x)       ((x*24)+STAMP_CENTER_BIAS_X)             // Convert Box X coordinates to pixels
#define PIXEL_BOX_Y(x)       (((x*24)+8)+STAMP_CENTER_BIAS_Y)             // Convert Box Y coordinates to pixels
#define BOX_PIXEL_X(x)       (div24(x-STAMP_CENTER_BIAS_X))           // Convert Stamp X coordinates to Box X
#define BOX_PIXEL_Y(x)       ((div24(x-STAMP_CENTER_BIAS_Y)))           // Convert Stamp Y coordinates to Box Y

#define STAMP_X_TO_RADAR(x)  RADAR_SPR_OFFSET_X+BOX_PIXEL_X(x)*8          // Convert box position to radar sprite position
#define STAMP_Y_TO_RADAR(x)  RADAR_SPR_OFFSET_Y+BOX_PIXEL_Y(x)*8          // Convert box position to radar sprite position

#define BOX_WALL_RIGHT(x)    (x&1<<4)            // Box has right wall
#define BOX_WALL_DOWN(x)     (x&1<<5)            // Box has down wall
#define BOX_WALL_LEFT(x)     (x&1<<6)            // Box has left wall
#define BOX_WALL_UP(x)       (x&1<<7)            // Box has up wall
#define BOX_NO_WALLS(x)      x==0x00             // Box has no walls. (TBD: Replace with an upper 4-bit AND)

#define LASER_NUM(x)         (x*LASER_NUM_FIELDS)
#define LASER_X(x)           (LASER_NUM(x)+0)
#define LASER_Y(x)           (LASER_NUM(x)+1)
#define LASER_TYPE(x)        (LASER_NUM(x)+2)
#define LASER_SHOOTING(x)    (LASER_NUM(x)+3)
#define LASER_DIRECTION(x)   (LASER_NUM(x)+4)

#define LASER_POSITION_X_START_H(x) x+LASER_X_OFFSET_H
#define LASER_POSITION_Y_START_H(x) x+LASER_Y_OFFSET_H

#define LASER_POSITION_X_START_V(x) x+LASER_X_OFFSET_V
#define LASER_POSITION_Y_START_V(x) x+LASER_Y_OFFSET_V

#endif /* MACROS_H */
