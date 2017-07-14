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

  // ULDR
  // 1111

  dungeon=(char*)dungeon1;
  
  b=0;  // dungeon array index

  for (i=0;i<6;++i)
    {
      for (j=0;j<10;++j)
  	{
	  /* Tile 1 */
  	  vram_adr(NTADR_A((j*3)+1,(i*3)+1));
	  if (( (dungeon[b] & 1<<7) ) && ( (dungeon[b] & 1<<6) ))            /* UP AND LEFT */
	    {
	      if ( (dungeon[b] & 1<<3) )                          /* LEFT WITH TELEPORT */
		{
		  vram_put(0x73);                                    
		}
	      else
		{
		  vram_put(0x74);                               
		}
	    }
	  else if ( (dungeon[b] & 1<<7) )                           /* UP */
	    {
	      vram_put(0x63);
	    }
	  else if ( (dungeon[b] & 1<<6) )                           /* LEFT */
	    {
	      if ( (dungeon[b] & 1<<3) )                          /* LEFT WITH TELEPORT */
		{
		  vram_put(0x73);                                    
		}
	      else
		{
		  vram_put(0x65);                               
		}
	    }
	  else
	    {
	      vram_put(0x00);
	    }

	  // Tile 2
	  if (dungeon[b] & (1<<7))            /* UP */
	    {
	      vram_put(0x63);
	    }
	  else
	    {
	      vram_put(0x00);
	    }
	  
	  // Tile 3
	  if (( (dungeon[b] & 1<<7) ) && ( (dungeon[b] & 1<<4) ))            /* UP AND RIGHT */
	    {
	      if ( (dungeon[b] & 1<<3) )                          /* RIGHT WITH TELEPORT */
		{
		  vram_put(0x98);
		}
	      else
		{
		  vram_put(0x75);
		}
	    }
	  else if ( (dungeon[b] & 1<<7) )                           /* UP */
	    {
	      vram_put(0x63);
	    }
	  else if ( (dungeon[b] & 1<<4) )                           /* RIGHT */
	    {
	      if ( (dungeon[b] & 1<<3) )                          /* RIGHT WITH TELEPORT */
		{
		  vram_put(0x98);
		}
	      else
		{
		  vram_put(0x66);
		}
	    }
	  else
	    {
	      vram_put(0x00);
	    }

  	  vram_adr(NTADR_A((j*3)+1,(i*3)+2));
	  // Tile 4
	  if (dungeon[b] & (1<<6))            /* LEFT */
	    {
	      if (dungeon[b] & (1<<3))      /* LEFT WITH TELEPORT */
		{
		  vram_put(0x73);
		}
	      else
		{
		  vram_put(0x65);
		}
	    }
	  else
	    {
	      vram_put(0x00);
	    }

	  // Tile 5 is always empty.
	  vram_put(0x00);

	  // Tile 6
	  if (dungeon[b] & (1<<4))            /* RIGHT */
	    {
	      if (dungeon[b] & (1<<3))      /* RIGHT WITH TELEPORT */
		{
		  vram_put(0x98);
		}
	      else
		{
		  vram_put(0x66);
		}
	    }
	  else
	    {
	      vram_put(0x00);
	    }
	  

	  vram_adr(NTADR_A((j*3)+1,(i*3)+3));
	  // Tile 7
	  if (( (dungeon[b] & 1<<6) ) && ( (dungeon[b] & 1<<5) ))            /* LEFT AND DOWN */
	    {
	      if ( (dungeon[b] & 1<<3) )                          /* LEFT WITH TELEPORT */
		{
		  vram_put(0x73);
		}
	      else
		{
		  vram_put(0x76);
		}
	    }
	  else if ( (dungeon[b] & 1<<6) )                           /* LEFT */
	    {
	      if ( (dungeon[b] & 1<<3) )                          /* LEFT WITH TELEPORT */
		{
		  vram_put(0x73);
		}
	      else
		{
		  vram_put(0x65);
		}
	    }
	  else if ( (dungeon[b] & 1<<5) )                           /* DOWN */
	    {
	      vram_put(0x64);
	    }
	  else
	    {
	      vram_put(0x00);
	    }

	  // Tile 8
	  if (dungeon[b] & (1<<5))            /* DOWN */
	    {
	      vram_put(0x64);
	    }
	  else
	    {
	      vram_put(0x00);
	    }

	  // Tile 9
	  if (( (dungeon[b] & 1<<4) ) && ( (dungeon[b] & 1<<5) ))            /* DOWN AND RIGHT */
	    {
	      if ( (dungeon[b] & 1<<3) )                          /* RIGHT WITH TELEPORT */
		{
		  vram_put(0x98);
		}
	      else
		{
		  vram_put(0x77);
		}
	    }
	  else if ( (dungeon[b] & 1<<5) )                           /* DOWN */
	    {
	      vram_put(0x64);
	    }
	  else if ( (dungeon[b] & 1<<4) )                           /* RIGHT */
	    {
	      if ( (dungeon[b] & 1<<3) )                          /* RIGHT WITH TELEPORT */
		{
		  vram_put(0x98);
		}
	      else
		{
		  vram_put(0x66);
		}
	    }
	  else
	    {
	      vram_put(0x00);
	    }
	  ++b;	  	  
  	}
    }

  ppu_on_all();
  ppu_wait_frame();
  bank_spr(1);
  bank_bg(0);

  spr=0;

  // 208, 169 - Yellow Player spawn.
  spr = oam_meta_spr(22,9,spr,metasprite_list[5]);
  spr = oam_meta_spr(180,80,spr,metasprite_list[6]);
  spr = oam_meta_spr(50,34,spr,metasprite_list[0]);
  spr = oam_meta_spr(120,81,spr,metasprite_list[1]);
  spr = oam_meta_spr(78,81,spr,metasprite_list[2]);
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
