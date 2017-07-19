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
 * run_dungeon() - dungeon code
 * dungeon_num - Dungeon Number to run
 */
void run_dungeon(unsigned char dungeon_num)
{
  
  vram_adr(NAMETABLE_C);
  vram_fill(0,1024);

  pal_bright(0);

  // Dump dungeon template into Nametable A
  vram_adr(NAMETABLE_A);
  vram_unrle(wow_dungeon);
  pal_bg(palette);
  pal_spr(palette);
  vram_adr(NTADR_A(0,0));
  
  // Print dungeon name
  str=(unsigned char*)dungeon_names[dungeon_num-1];
  b=10;
  adr=(NTADR_A(11,20));
  vram_adr(adr);
  a=c=d=0;

  for (i=0;i<2;++i)
    {
      for (j=0;j<b;++j)
  	{
  	  d=str[j];
  	  if ((d>0x5B) && (d<0x55))
  	    {
  	      c=0x36;
  	    }
  	  else if ((d>0x45) && (d<0x56))
  	    {
  	      c=0x26;
  	    }
  	  else if ((d>0x40) && (d<0x46))
  	    {
  	      c=0x36;
  	    }
  	  else if ((d>0x29) && (d<0x40))
  	    {
  	      c=0x2F; // Needed because charset doesn't have '@'
  	    }
  	  else if (d==0x20)
  	    {
  	      c=0x20; // Get tiles 0x00 and 0x10 for space.
  	    }
  	  else
  	    {
  	      c=0x16;
  	    }
  	  vram_put(d-c+a);
  	}
      a=a+0x10;  // second part of letter is 16 cells apart.
      vram_adr(adr+0x20);
    }
  
  dungeon=(unsigned char*)dungeons[dungeon_num-1];
  
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
  		  vram_put(0x78);
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
  		  vram_put(0x78);
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
  		  vram_put(0x78);
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
  		  vram_put(0x78);
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
  		  vram_put(0x78);
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

  // Point to vram update buffer for further updates.
  set_vram_update(update_buffer);
  
  ppu_on_all();
  ppu_wait_frame();
  bank_spr(1);
  bank_bg(0);

  spr=0;
  
  pal_fade_to(4);

  set_door(0,0);
  ppu_wait_frame();
  set_teleport(1);
  a=spr=0;
  i=0;
  
  while(1)
    {
      ppu_wait_frame();
      ++frame_cnt;
      if (frame_cnt==255)
	{
	  /* ++i; */
	  /* i=i&1; */
	  /* set_door(0,i); */
	  break;
	}
    }

  pal_fade_to(0);
  oam_clear();
  clear_update_buffer();
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
  clear_update_buffer();
  
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
  spr = oam_meta_spr(120,98,spr,metasprite_list[6]);
  spr = oam_meta_spr(120,132,spr,metasprite_list[5]);
  spr = oam_meta_spr(120,164,spr,metasprite_list[3]);
  spr = oam_meta_spr(120,204,spr,metasprite_list[4]);
  
  pal_fade_to(4);

  i=0;
  
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
 * set_teleport(openclose)
 * openclose = 0 for open, 1 for close
 */
void set_teleport(unsigned char openclose)
{
  // Clear the update buffer
  clear_update_buffer();

  // Set the addresses for the two teleport regions.
  update_buffer[0]=MSB(NTADR_A(1,7))|NT_UPD_VERT;
  update_buffer[1]=LSB(NTADR_A(1,7));
  update_buffer[2]=3;

  update_buffer[6]=MSB(NTADR_A(30,7))|NT_UPD_VERT;
  update_buffer[7]=LSB(NTADR_A(30,7));
  update_buffer[8]=3;

  // and fill in the tiles in the data section.
  update_buffer[3]=(openclose==0?0x73:0x79);
  update_buffer[4]=(openclose==0?0x73:0x79);
  update_buffer[5]=(openclose==0?0x73:0x79);

  update_buffer[9]=(openclose==0?0x78:0x7A);
  update_buffer[10]=(openclose==0?0x78:0x7A);
  update_buffer[11]=(openclose==0?0x78:0x7A);  
}

/**
 * set_door(player, openclose)
 * player = Player 0 (blue) or Player 1 (yellow) door.
 * openclose = 0 for open, 1 for close.
 */
void set_door(unsigned char player, unsigned char openclose)
{
  // Clear the update buffer
  clear_update_buffer();

  // Set the addresses for the two rows of tiles that make up the door
  update_buffer[0]=(player==0?MSB(NTADR_A(1,18))|NT_UPD_HORZ:MSB(NTADR_A(28,18))|NT_UPD_HORZ);
  update_buffer[1]=(player==0?LSB(NTADR_A(1,18)):LSB(NTADR_A(28,18)));
  update_buffer[2]=3;

  update_buffer[6]=(player==0?MSB(NTADR_A(1,19))|NT_UPD_HORZ:MSB(NTADR_A(28,19))|NT_UPD_HORZ);
  update_buffer[7]=(player==0?LSB(NTADR_A(1,19)):LSB(NTADR_A(28,19)));
  update_buffer[8]=3;
  
  // And then set the tiles for each update depending on desired door state.
  if (openclose==0 && player==0)
    {
      update_buffer[3]=0x65;
      update_buffer[4]=0x00;
      update_buffer[5]=0x00;
      update_buffer[9]=0x65;
      update_buffer[10]=0x00;
      update_buffer[11]=0x00;
    }
  else if (openclose==1 && player==0)
    {
      update_buffer[3]=0x76;
      update_buffer[4]=0x64;
      update_buffer[5]=0x64;
      update_buffer[9]=0x74;
      update_buffer[10]=0x63;
      update_buffer[11]=0x63;      
    }
  else if (openclose==0 && player==1)
    {
      update_buffer[3]=0x00;
      update_buffer[4]=0x00;
      update_buffer[5]=0x66;
      update_buffer[9]=0x00;
      update_buffer[10]=0x00;
      update_buffer[11]=0x66;            
    }
  else if (openclose==1 && player==1)
    {
      update_buffer[3]=0x64;
      update_buffer[4]=0x64;
      update_buffer[5]=0x77;
      update_buffer[9]=0x63;
      update_buffer[10]=0x63;
      update_buffer[11]=0x75;                  
    }
  
}

/**
 * clear_update_buffer() - Clear the update buffer
 */
void clear_update_buffer(void)
{
  memfill(&update_buffer,NT_UPD_EOF,sizeof(update_buffer));
}

/**
 * init() - just as it says.
 */
void init(void)
{
  clear_update_buffer();
}

/**
 * main() function - Program starts here
 */
void main(void)
{
  init();
  
  while(1)
    {
      attract_scores(); 
      attract_monsters(); 
      run_dungeon(1);
    }
}
