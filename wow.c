/**
 * __      _____ ____  _   ___ ___     ___  ___
 * \ \    / /_ _|_  / /_\ | _ \   \   / _ \| __|
 *  \ \/\/ / | | / / / _ \|   / |) | | (_) | _|
 *   \_/\_/ |___/___/_/ \_\_|_\___/   \___/|_|
 *
 *           __      _____  ___
 *           \ \    / / _ \| _ \
 *            \ \/\/ / (_) |   /
 *             \_/\_/ \___/|_|_\
 *
 * Version: 0.0
 *
 * Author: 
 *  Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 *
 * Started:       2017-06-12
 * Code Started:  2017-07-05
 *
 */

/**************************************************
 * DISCLAIMER: This is not clean C code. It will  *
 * Never be clean C code. Everything here is done *
 * So that the result will either work, or fit    *
 * inside an NES, being that C was never an ideal *
 * language for the 6502. It is honestly a minor  * 
 * miracle that CC65 exists and that it does as   *
 * well as it does. It is a testament to the      * 
 * CC65 engineers to want to produce more than    *
 * a pidgin C compiler. Hats off to them, really. *
 * -Thom Cherryhomes 07/16/2017                   *
 **************************************************/

#include "wow.h"

/**
 * init() - just as it says.
 */
void init(void)
{
  ppu_mask(0x00);
  clear_update_buffer();
  clear_stamps();
  // blue_worrior_ai=1;
}

/**
 * main() function - Program starts here
 */
void main(void)
{
  init();
  
  while(1)
    {
      /* attract_scores(); */
      /* attract_monsters(); */
      dungeon_run(1);
    }
}
