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
  56,58,60,60, // Worluk Right-Left
  57,59,61,61, // Worluk Up-Down
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

const unsigned char* const metasprite_animation_list[]={
  metasprite_animation_data+0,   // [0]  Worrior Blue Right
  metasprite_animation_data+4,   // [1]  Worrior Blue Right Idle
  metasprite_animation_data+8,   // [2]  Worrior Blue Left
  metasprite_animation_data+12,  // [3]  Worrior Blue Left Idle
  metasprite_animation_data+16,  // [4]  Worrior Blue Up
  metasprite_animation_data+20,  // [5]  Worrior Blue Up Idle
  metasprite_animation_data+24,  // [6]  Worrior Blue Down
  metasprite_animation_data+28,  // [7]  Worrior Blue Down Idle
  metasprite_animation_data+32,  // [8]  Worrior Blue Right Shooting
  metasprite_animation_data+36,  // [9]  Worrior Blue Left Shooting
  metasprite_animation_data+40,  // [10] Worrior Blue Up Shooting
  metasprite_animation_data+44,  // [11] Worrior Blue Down Shooting
  // -------------------------------------------------
  metasprite_animation_data+48,  // [12] Burwor Right
  metasprite_animation_data+52,  // [13] Burwor Left
  metasprite_animation_data+56,  // [14] Burwor Up
  metasprite_animation_data+60,  // [15] Burwor Down
  // -------------------------------------------------
  metasprite_animation_data+64,  // [16] Gorwor Right
  metasprite_animation_data+68,  // [17] Gorwor Left
  metasprite_animation_data+72,  // [18] Gorwor Up
  metasprite_animation_data+76,  // [19] Gorwor Down
  // -------------------------------------------------
  metasprite_animation_data+80,  // [20] Thorwor Right
  metasprite_animation_data+84,  // [21] Thorwor Left
  metasprite_animation_data+88,  // [22] Thorwor Up
  metasprite_animation_data+92,  // [23] Thorwor Down
  // -------------------------------------------------
  metasprite_animation_data+96,  // [24] Worluk Right-Left
  metasprite_animation_data+100, // [25] Worluk Up-Down
  // -------------------------------------------------
  metasprite_animation_data+104, // [26] Worrior Yellow Right
  metasprite_animation_data+108, // [27] Worrior Yellow Right Idle
  metasprite_animation_data+112, // [28] Worrior Yellow Left
  metasprite_animation_data+116, // [29] Worrior Yellow Left Idle
  metasprite_animation_data+120, // [30] Worrior Yellow Up
  metasprite_animation_data+124, // [31] Worrior Yellow Up Idle
  metasprite_animation_data+128, // [32] Worrior Yellow Down
  metasprite_animation_data+132, // [33] Worrior Yellow Down Idle
  metasprite_animation_data+136, // [34] Worrior Yellow Right Shooting
  metasprite_animation_data+140, // [35] Worrior Yellow Left Shooting
  metasprite_animation_data+144, // [36] Worrior Yellow Up Shooting
  metasprite_animation_data+148  // [37] Worrior Yellow Down Shooting
  // ------------------------------------------------
};

const unsigned char metasprite_animation_type[]={
  0,12,16,20,24,26
};

#define STAMP_TYPE_BLUE_WORRIOR     0
#define STAMP_TYPE_BURWOR           12
#define STAMP_TYPE_GORWOR           16
#define STAMP_TYPE_THORWOR          20
#define STAMP_TYPE_WORLUK           24
#define STAMP_TYPE_YELLOW_WORRIOR   26

#endif /* METASPRITE_ANIMATIONS_H */
