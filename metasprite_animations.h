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
  20,24,28,28, // Burwor Right
  21,25,29,29, // Burwor Left
  22,26,30,30, // Burwor Up
  23,27,31,31, // Burwor Down
  32,36,40,40, // Gorwor Right
  33,37,41,41, // Gorwor Left
  34,38,42,42, // Gorwor Up
  35,39,43,43, // Gorwor Down
  44,48,52,52, // Thorwor Right
  45,49,53,53, // Thorwor Left
  46,50,54,54, // Thorwor Up
  47,51,55,55, // Thorwor Down
  56,58,60,60, // Worluk Right-Left
  57,59,61,61 // Worluk Up-Down
};

const unsigned char* const metasprite_animation_list[]={
  metasprite_animation_data+0,
  metasprite_animation_data+4,
  metasprite_animation_data+8,
  metasprite_animation_data+12,
  metasprite_animation_data+16,
  metasprite_animation_data+20,
  metasprite_animation_data+24,
  metasprite_animation_data+28,
  metasprite_animation_data+32,
  metasprite_animation_data+36,
  metasprite_animation_data+40,
  metasprite_animation_data+44,
  metasprite_animation_data+48,
  metasprite_animation_data+52,
  metasprite_animation_data+56,
  metasprite_animation_data+60,
  metasprite_animation_data+64,
  metasprite_animation_data+68,
  metasprite_animation_data+72,
  metasprite_animation_data+76,
  metasprite_animation_data+80,
  metasprite_animation_data+84,
  metasprite_animation_data+88,
  metasprite_animation_data+92,
  metasprite_animation_data+96,
  metasprite_animation_data+100,
  metasprite_animation_data+104
};

#endif /* METASPRITE_ANIMATIONS_H */
