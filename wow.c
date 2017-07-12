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
 * pal_fade_to(unsigned to) - smoothly fade palette
 * to the given brightness value.
 */
void pal_fade_to(unsigned to)
{
	if(!to) music_stop();

	while(bright!=to)
	{
		delay(4);
		if(bright<to) ++bright; else --bright;
		pal_bright(bright);
	}

	if(!bright)
	{
		ppu_off();
		set_vram_update(NULL);
		scroll(0,0);
	}
}


/**
 * attract_dungeontest() - show scores
 */
void attract_dungeontest(void)
{
  
  vram_adr(NAMETABLE_C);
  vram_fill(0,1024);

  pal_bright(0);

  // Dump scores into nametable A
  vram_adr(NAMETABLE_A);
  vram_unrle(wow_dungeon);
  pal_bg(palette);
  pal_spr(palette);
  vram_adr(NTADR_A(0,0));
  
  for (i=0;i<6;++i)
    {
      for (j=0;j<10;++j)
	{
	  vram_adr(NTADR_A((j*3)+1,(i*3)+1));
	  vram_put(0x74);
	  vram_put(0x63);
	  vram_put(0x75);
	  vram_adr(NTADR_A((j*3)+1,(i*3)+2));
	  vram_put(0x65);
	  vram_put(0x00);
	  vram_put(0x66);
	  vram_adr(NTADR_A((j*3)+1,(i*3)+3));
	  vram_put(0x76);
	  vram_put(0x64);
	  vram_put(0x77);
	}
    }

  ppu_on_all();
  ppu_wait_frame();
  bank_spr(1);
  bank_bg(0);

  spr=0;

  // 208, 169 - Yellow Player spawn.
  /* spr = oam_meta_spr(YELLOW_SPAWN_X,YELLOW_SPAWN_Y,spr,metasprite_list[6]); */
  /* spr = oam_meta_spr(22,9,spr,metasprite_list[9]); */
  /* spr = oam_meta_spr(51,9,spr,metasprite_list[5]); */
  
  pal_fade_to(4);

  while(1)
    {
      ppu_wait_frame();
      /* ++frame_cnt; */
      /* if (frame_cnt==255) break; */
    }

  pal_fade_to(0);
  
}

/**
 * attract_score() - show scores
 */
void attract_scores(void)
{
  vram_adr(NAMETABLE_C);
  vram_fill(0,1024);

  pal_bright(0);

  // Dump scores into nametable A
  vram_adr(NAMETABLE_A);
  vram_unrle(wow_scores);
  pal_bg(palette);
  pal_spr(palette);
  ppu_on_all();
  ppu_wait_frame();
  bank_spr(1);
  bank_bg(0);
  pal_fade_to(4);

  while(1)
    {
      ppu_wait_frame();
      ++frame_cnt;
      if (frame_cnt==255) break;
    }

  pal_fade_to(0);
  
}

/**
 * attract_monsters() - shown while game isn't playing
 */
void attract_monsters(void)
{
  // Clear nametable C
  vram_adr(NAMETABLE_C);
  vram_fill(0,1024);

  pal_bright(0);
  
  // Dump monster screen into nametable A
  vram_adr(NAMETABLE_A);
  vram_unrle(wow_monsters);
  pal_bg(palette);
  pal_spr(palette);
  ppu_on_all();
  ppu_wait_frame();
  bank_spr(1);
  bank_bg(0);

  spr=0;
  spr = oam_meta_spr(120,8,spr,metasprite_list[0]);
  spr = oam_meta_spr(120,36,spr,metasprite_list[1]);
  spr = oam_meta_spr(120,68,spr,metasprite_list[2]);
  spr = oam_meta_spr(120,100,spr,metasprite_list[6]);
  spr = oam_meta_spr(120,132,spr,metasprite_list[5]);
  spr = oam_meta_spr(120,164,spr,metasprite_list[3]);
  spr = oam_meta_spr(120,204,spr,metasprite_list[4]);

  pal_fade_to(4);
  
  while(1)
    {
      ppu_wait_frame();
      ++frame_cnt;
      if (frame_cnt==255) break;
    }

  pal_fade_to(0);
  oam_clear();
}

/**
 * main() function - Program starts here
 */
void main(void)
{
  while(1)
    {
      /* attract_scores(); */
      /* attract_monsters(); */
      attract_dungeontest();
    }
}
