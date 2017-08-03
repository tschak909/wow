/**
 * metasprite_animations
 */

// TODO: Fill in frames for Wizard

#ifndef METASPRITE_ANIMATIONS_H
#define METASPRITE_ANIMATIONS_H

const unsigned char metasprite_animation_data[]={
  0,4,8,8,     // Worrior Blue Right
  0,0,0,0,     // Worrior Blue Right Idle
  1,5,9,9,     // Worrior Blue Left
  1,1,1,1,     // Worrior Blue Left Idle
  2,6,10,10,   // Worrior Blue Up
  2,2,2,2,     // Worrior Blue Up Idle
  3,7,11,11,   // Worrior Blue Down
  3,3,3,3,     // Worrior Blue Down Idle
  4,12,16,16,  // Worrior Blue Right Shooting
  5,13,17,17,  // Worrior Blue Left Shooting
  6,14,18,18,  // Worrior Blue Up Shooting
  7,15,19,19,  // Worrior Blue Down Shooting
  // -------------------------------------------
  20,24,28,28, // Burwor Right
  21,25,29,29, // Burwor Left
  22,26,30,30, // Burwor Up
  23,27,31,31, // Burwor Down
  // -------------------------------------------
  32,36,40,40, // Gorwor Right
  33,37,41,41, // Gorwor Left
  34,38,42,42, // Gorwor Up
  35,39,43,43, // Gorwor Down
  // -------------------------------------------
  44,48,52,52, // Thorwor Right
  45,49,53,53, // Thorwor Left
  46,50,54,54, // Thorwor Up
  47,51,55,55, // Thorwor Down
  // -------------------------------------------
  56,58,60,60, // Worluk (Right) Right-Left
  56,58,60,60, // Worluk (Left) Right-Left
  57,59,61,61, // Worluk (Up) Up-Down
  57,59,61,61, // Workup (Down) Up-Down
  // -------------------------------------------
  62,66,70,70, // Worrior Yellow Right
  62,62,62,62, // Worrior Yellow Right Idle
  63,67,71,71, // Worrior Yellow Left
  63,63,63,63, // Worrior Yellow Left Idle
  64,68,72,72, // Worrior Yellow Up
  64,64,64,64, // Worrior Yellow Up Idle
  65,69,73,73, // Worrior Yellow Down
  65,65,65,65, // Worrior Yellow Down Idle
  66,70,74,74, // Worrior Yellow Right Shooting
  67,71,75,75, // Worrior Yellow Left Shooting
  68,72,76,76, // Worrior Yellow Up Shooting
  69,73,77,77, // Worrior Yellow Down Shooting
};

#define STAMP_TYPE_BLUE_WORRIOR     0
#define STAMP_TYPE_BURWOR           48
#define STAMP_TYPE_GORWOR           64
#define STAMP_TYPE_THORWOR          80
#define STAMP_TYPE_WORLUK           96
#define STAMP_TYPE_YELLOW_WORRIOR   112

#define STATE_MONSTER_RIGHT         0
#define STATE_MONSTER_LEFT          1
#define STATE_MONSTER_UP            2
#define STATE_MONSTER_DOWN          3

#endif /* METASPRITE_ANIMATIONS_H */
