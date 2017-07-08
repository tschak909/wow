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

#include "wow.h"

/**
 * attract_mode() - shown while game isn't playing
 */
void attract_mode(void)
{
  // Clear nametable C
  vram_adr(NAMETABLE_C);
  vram_fill(0,1024);

  // Dump monster screen into nametable A
  vram_adr(NAMETABLE_A);
  vram_unrle(wow_monsters);
  pal_bg(palette);
  ppu_on_bg();
  delay(20);
  
  while(1)
    {
      ppu_wait_frame();
    }
  
}

/**
 * main() function - Program starts here
 */
void main(void)
{
  while(1)
    {
      attract_mode();
    }
}
