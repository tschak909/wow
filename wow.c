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
 * dungeon_red() - Turn dungeon red
 */
void dungeon_red()
{
  pal_col(1,0x16);
}

/**
 * dungeon_blue() - Turn dungeon blue
 */
void dungeon_blue()
{
  pal_col(1,0x11);
}

/**
 * double_score_win() - turn screen colors and set "DOUBLE SCORE" text on radar.
 */
void double_score_win(void)
{
  clear_update_buffer();
  update_buffer[0]=MSB(NTADR_A(10,20))|NT_UPD_HORZ;
  update_buffer[1]=LSB(NTADR_A(10,20));
  update_buffer[2]=12;
  update_buffer[3]=0x0e; // D
  update_buffer[4]=0x29; // O
  update_buffer[5]=0x2f; // U
  update_buffer[6]=0x0c; // B
  update_buffer[7]=0x26; // L
  update_buffer[8]=0x0f; // E
  update_buffer[9]=0x00; // 
  update_buffer[10]=0x2D; // S
  update_buffer[11]=0x0d;// C
  update_buffer[12]=0x29;// O
  update_buffer[13]=0x2C;// R
  update_buffer[14]=0x0f;// E
  
  update_buffer[15]=MSB(NTADR_A(10,21))|NT_UPD_HORZ;
  update_buffer[16]=LSB(NTADR_A(10,21));
  update_buffer[17]=12;
  update_buffer[18]=0x1e; // D
  update_buffer[19]=0x39; // O
  update_buffer[20]=0x3f; // U
  update_buffer[21]=0x1c; // B
  update_buffer[22]=0x36; // L
  update_buffer[23]=0x1f; // E
  update_buffer[24]=0x00; //
  update_buffer[25]=0x3D; // S
  update_buffer[26]=0x1d; // C
  update_buffer[27]=0x39; // O
  update_buffer[28]=0x3C; // R
  update_buffer[29]=0x1f; // E
  
  dungeon_red();   // Leave the dungeon red.
  j=0x20;
  for (i=0;i<150;i++) // This effect lasts for 150 frames (or 3 seconds at our 50 drop rate)
    {
      pal_col(0,j);
      if (j==0x3C)
	{
	  j=0x20;
	}
      else
	{
	  ++j;
	}
      ppu_wait_frame();
    }
  pal_col(0,0x0f);
}

/**
 * ready_blue_player() - Ready the blue player
 */
void ready_blue_player(void)
{
  stamps[STAMP_TIMER(1)]=3; // Player is in the box.
  stamps[STAMP_X(1)]=PIXEL_BOX_X(0);
  stamps[STAMP_Y(1)]=PIXEL_BOX_Y(6)-1; // 6 is the special spawn box.
  stamps[STAMP_TYPE(1)]=STAMP_TYPE_BLUE_WORRIOR;
  stamps[STAMP_STATE(1)]=1; // Facing right Idle
  stamps[STAMP_FRAME(1)]=0;
  stamps[STAMP_DELAY(1)]=0;
  blue_door_state=OPEN;
}

/**
 * ready_yellow_player() - Ready the blue player
 */
void ready_yellow_player(void)
{
  stamps[STAMP_TIMER(0)]=6;
  stamps[STAMP_X(0)]=PIXEL_BOX_X(9);
  stamps[STAMP_Y(0)]=PIXEL_BOX_Y(6)-1; // 6 is the special spawn box.
  stamps[STAMP_TYPE(0)]=STAMP_TYPE_YELLOW_WORRIOR;
  stamps[STAMP_STATE(0)]=3; // Facing left Idle
  stamps[STAMP_FRAME(0)]=0;
  stamps[STAMP_DELAY(0)]=0;
  yellow_door_state=OPEN;
}

/**
 * setup_enemy_sprites() - Set up enemy sprite spawn points
 */
void setup_enemy_sprites(void)
{
  for (i=2;i<STAMP_NUM_SLOTS;i++)
    {
    randx:
      a=rand8()&0x0f;
      if (a>9)
	goto randx;

    randy:
      b=rand8()&0x07;
      if (b>5)
	goto randy;
      
      stamps[STAMP_X(i)]=PIXEL_BOX_X(a);
      stamps[STAMP_Y(i)]=PIXEL_BOX_Y(b);
      stamps[STAMP_TYPE(i)]=STAMP_TYPE_BURWOR;
      stamps[STAMP_STATE(i)]=rand8()&0x03; // Random initial state.
      stamps[STAMP_FRAME(i)]=rand8()&0x03; // Random enemy frame.
      stamps[STAMP_DELAY(i)]=4; // TODO: Change this per level.
    }
  // Temporary code to test all monster types
  stamps[STAMP_TYPE(5)]=stamps[STAMP_TYPE(6)]=STAMP_TYPE_GORWOR;
  stamps[STAMP_TYPE(7)]=STAMP_TYPE_THORWOR;
}

/**
 * animate_stamps() - increment the frame counters of each sprite, (0-7)
 * applying delay to the non-player sprites (2-7)
 */
void animate_stamps(void)
{
  for (i=0;i<STAMP_NUM_SLOTS;i++)
    {
      if (stamps[STAMP_DELAY(i)]==0)
	{
	  stamps[STAMP_FRAME(i)]=(stamps[STAMP_FRAME(i)]+1)&0x03;
	  if (i>1) // Delay only applies to enemies.
	    stamps[STAMP_DELAY(i)]=4;
	  else
	    stamps[STAMP_DELAY(i)]=1;
	}
      else
	{
	  --stamps[STAMP_DELAY(i)];
	}
    }
}

/**
 * stamp_type_to_radar() - Choose radar sprite to use 
 */
unsigned char stamp_type_to_radar(unsigned char t)
{
  switch (t)
    {
    case STAMP_TYPE_BURWOR:
      a=0xC5;
      break;
    case STAMP_TYPE_GORWOR:
    case STAMP_TYPE_WORLUK:
      a=0xC6;
      break;
    case STAMP_TYPE_THORWOR:
      a=0xC7;
      break;
    }
  return a;
}

 /**
 * update_radar()
 * a = the current update buffer subscript
 * b = the box X to check with get_radar_tile_byte()
 * c = the box Y to check with get_radar_tile_byte()
 */
void update_radar(void)
{
  spr=OAM_OFFSET_RADAR;
  for (i=2;i<STAMP_NUM_SLOTS;i++)
    {
      spr = oam_spr(STAMP_X_TO_RADAR(stamps[STAMP_X(i)]),STAMP_Y_TO_RADAR(stamps[STAMP_Y(i)]),stamp_type_to_radar(stamps[STAMP_TYPE(i)]),0,spr);
    }
}

/**
 * get_current_box()
 * Get the current dungeon box for player
 * i = the stamp to return in a,b,c,d
 * a = the X box
 * b = the Y box
 * c = the dungeon box #
 * d = the box data.
 */
void get_current_box(void)
{
  a=div24(stamps[STAMP_X(i)]+8);
  b=div24(stamps[STAMP_Y(i)]-8);
  c=(b*10)+a; // C is now the box #
  d=dungeon[c];
}

/**
 * monster_change_direction()
 * Change monster direction.
 */
void monster_change_direction(void)
{
 change_direction:
  stamps[STAMP_STATE(i)]=rand8()&0x03;
  if (stamps[STAMP_STATE(i)]==STATE_MONSTER_LEFT && stamps[STAMP_X(i)]==PIXEL_BOX_X(0) && stamps[STAMP_Y(i)]==PIXEL_BOX_Y(2) && teleport_state==OPEN)
    {
      teleport_timer=2;
      teleport_state=CLOSED;
      stamps[STAMP_X(i)]=PIXEL_BOX_X(9);
    }
  else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_RIGHT && stamps[STAMP_X(i)]==PIXEL_BOX_X(9) && stamps[STAMP_Y(i)]==PIXEL_BOX_Y(2) && teleport_state==OPEN)
    {
      teleport_timer=2;
      teleport_state=CLOSED;
      stamps[STAMP_X(i)]=PIXEL_BOX_X(0);
    }
  else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_LEFT && BOX_WALL_LEFT(d))
    goto change_direction;
  else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_RIGHT && BOX_WALL_RIGHT(d))
    goto change_direction;
  else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_UP && BOX_WALL_UP(d))
    goto change_direction;
  else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_DOWN && BOX_WALL_DOWN(d))
    goto change_direction;
}

/**
 * move_monsters()
 * Move the monsters
 */
void move_monsters(void)
{
  for (i=2;i<STAMP_NUM_SLOTS;i++)
    {
      get_current_box();
      if ((stamps[STAMP_X(i)]==PIXEL_BOX_X(a)) && (stamps[STAMP_Y(i)]==PIXEL_BOX_Y(b)))
	{
	  monster_change_direction();
	}
      else
	{
	  // We are not aligned.
	  if (stamps[STAMP_STATE(i)]==STATE_MONSTER_RIGHT && stamps[STAMP_LAST_STATE(i)]==STATE_MONSTER_LEFT)
	    stamps[STAMP_STATE(i)]=STATE_MONSTER_RIGHT;
	  else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_LEFT && stamps[STAMP_LAST_STATE(i)]==STATE_MONSTER_RIGHT)
	    stamps[STAMP_STATE(i)]=STATE_MONSTER_LEFT;
	  else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_UP && stamps[STAMP_LAST_STATE(i)]==STATE_MONSTER_DOWN)
	    stamps[STAMP_STATE(i)]=STATE_MONSTER_UP;
	  else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_DOWN && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_UP)
	    stamps[STAMP_STATE(i)]=STATE_MONSTER_DOWN;
	  else
	    stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)];
	  
	}
      
      // Handle state movement
      if (stamps[STAMP_STATE(i)]==STATE_MONSTER_RIGHT)
	stamps[STAMP_X(i)]++;
      else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_LEFT)
	stamps[STAMP_X(i)]--;
      else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_UP)
	stamps[STAMP_Y(i)]--;
      else if (stamps[STAMP_STATE(i)]==STATE_MONSTER_DOWN)
	stamps[STAMP_Y(i)]++;

      stamps[STAMP_LAST_STATE(i)]=stamps[STAMP_STATE(i)];  
      
    }
}

/**
 * handle_pad_idle()
 */
void handle_pad_idle(void)
{
  // Change to idle state if pad is idle.
  switch(stamps[STAMP_LAST_STATE(i)])
    {
    case STATE_PLAYER_RIGHT:
      stamps[STAMP_STATE(i)]=STATE_PLAYER_RIGHT_IDLE;
      break;
    case STATE_PLAYER_LEFT:
      stamps[STAMP_STATE(i)]=STATE_PLAYER_LEFT_IDLE;
      break;
    case STATE_PLAYER_UP:
      stamps[STAMP_STATE(i)]=STATE_PLAYER_UP_IDLE;
      break;
    case STATE_PLAYER_DOWN:
      stamps[STAMP_STATE(i)]=STATE_PLAYER_DOWN_IDLE;
      break;
    }
}

/**
 * handle_player_in_field()
 * Handle when player is on the playfield
 */
void handle_player_in_field(void)
{
  if ((stamps[STAMP_X(i)]==PIXEL_BOX_X(a)) && (stamps[STAMP_Y(i)]==PIXEL_BOX_Y(b)))
    {
      // We are aligned.
      if (PLAYER_PAD_LEFT(i) && stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_RIGHT && stamps[STAMP_X(i)]==PIXEL_BOX_X(0) && stamps[STAMP_Y(i)]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	{
	  stamps[STAMP_X(i)]=PIXEL_BOX_X(9);
	  teleport_state=CLOSED;
	  teleport_timer=2;	  
	}
      else if (PLAYER_PAD_RIGHT(i) && stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_LEFT && stamps[STAMP_X(i)]==PIXEL_BOX_X(9) && stamps[STAMP_Y(i)]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	{
	  stamps[STAMP_X(i)]=PIXEL_BOX_X(0);
	  teleport_state=CLOSED;
	  teleport_timer=2;
	}
      else if (PLAYER_PAD_RIGHT(i) && stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_RIGHT && !BOX_WALL_RIGHT(d))
      	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=STATE_PLAYER_RIGHT;
      else if (PLAYER_PAD_LEFT(i) && stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_LEFT && !BOX_WALL_LEFT(d))
      	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=STATE_PLAYER_LEFT;
      else if (PLAYER_PAD_UP(i) && stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_UP && !BOX_WALL_UP(d))
	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=STATE_PLAYER_UP;
      else if (PLAYER_PAD_DOWN(i) && stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_DOWN && !BOX_WALL_DOWN(d))
      	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=STATE_PLAYER_DOWN;
      else if (PLAYER_PAD_IDLE(i))
	handle_pad_idle();
      
      if (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_LEFT && stamps[STAMP_X(i)]==PIXEL_BOX_X(0) && stamps[STAMP_Y(i)]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	{
 	  stamps[STAMP_STATE(i)]=STATE_PLAYER_LEFT;
	}
      else if (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_RIGHT && stamps[STAMP_X(i)]==PIXEL_BOX_X(9) && stamps[STAMP_Y(i)]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	{
	  stamps[STAMP_STATE(i)]=STATE_PLAYER_RIGHT;
	}
      else if (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_RIGHT && BOX_WALL_RIGHT(d))
      	stamps[STAMP_STATE(i)]=STATE_PLAYER_RIGHT_IDLE;
      else if (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_LEFT && BOX_WALL_LEFT(d))
      	stamps[STAMP_STATE(i)]=STATE_PLAYER_LEFT_IDLE;
      else if (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_UP && BOX_WALL_UP(d))
	stamps[STAMP_STATE(i)]=STATE_PLAYER_UP_IDLE;
      else if (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_DOWN && BOX_WALL_DOWN(d))
      	stamps[STAMP_STATE(i)]=STATE_PLAYER_DOWN_IDLE;
    }
  else
    {
      // We are not aligned.
      if (PLAYER_PAD_IDLE(i))
	handle_pad_idle();
      else if (PLAYER_PAD_RIGHT(i) && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_LEFT)
	stamps[STAMP_STATE(i)]=STATE_PLAYER_RIGHT;
      else if (PLAYER_PAD_LEFT(i) && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_RIGHT)
	stamps[STAMP_STATE(i)]=STATE_PLAYER_LEFT;
      else if (PLAYER_PAD_UP(i) && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_DOWN)
	stamps[STAMP_STATE(i)]=STATE_PLAYER_UP;
      else if (PLAYER_PAD_DOWN(i) && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_UP)
	stamps[STAMP_STATE(i)]=STATE_PLAYER_DOWN;
      else
	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)];
      
    }
  
  // Handle state movement
  if (stamps[STAMP_STATE(i)]==STATE_PLAYER_RIGHT)
    stamps[STAMP_X(i)]+=2;
  else if (stamps[STAMP_STATE(i)]==STATE_PLAYER_LEFT)
    stamps[STAMP_X(i)]-=2;
  else if (stamps[STAMP_STATE(i)]==STATE_PLAYER_UP)
    stamps[STAMP_Y(i)]-=2;
  else if (stamps[STAMP_STATE(i)]==STATE_PLAYER_DOWN)
    stamps[STAMP_Y(i)]+=2;
  
  // And set last state, if we aren't idle.
  if (!PLAYER_PAD_IDLE(i))
    stamps[STAMP_LAST_STATE(i)]=stamps[STAMP_STATE(i)];  
}

/**
 * handle_player_in_box()
 * Handle when player is in box.
 */
void handle_player_in_box(void)
{
  if (stamps[STAMP_TIMER(i)]>0)
    {
      if (stamps[STAMP_PAD(i)] != 0)
	{
	  stamps[STAMP_TIMER(i)]=0;
	}
      else
	{
	  stamps[STAMP_Y(i)]=PIXEL_BOX_Y(6)-1; // 6 is the Y for the box.
	  if (sec==0) // 0 means approximately 1 second elapsed.
	    stamps[STAMP_TIMER(i)]--;         // Decrement timer
	}
    }
  else
    {
      stamps[STAMP_Y(i)]=PIXEL_BOX_Y(5); // Pop out of box.
      if (i==0)
	{
	  stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=STATE_PLAYER_LEFT_IDLE;
	  yellow_door_state=CLOSED;
	}
      else
	{
	  stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=STATE_PLAYER_RIGHT_IDLE;
	  blue_door_state=CLOSED;
	}
    }
}

/**
 * move_players()
 */
void move_players(void)
{
  for (i=0;i<2;i++)
    {
      get_current_box();
      stamps[STAMP_PAD(i)]=pad_poll(i);
     
      if (stamps[STAMP_Y(i)]==PIXEL_BOX_Y(6)-1)
	{
	  handle_player_in_box();
	}
      else
	{
	  handle_player_in_field();
	}
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

  for (i=0;i<2;i++)
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

  for (i=0;i<6;i++)
    {
      for (j=0;j<10;++j)
  	{
  	  /* Tile 1 */
  	  vram_adr(NTADR_A((j*3)+1,(i*3)+2));
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

  	  vram_adr(NTADR_A((j*3)+1,(i*3)+3));
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
	  

  	  vram_adr(NTADR_A((j*3)+1,(i*3)+4));
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
  
  pal_fade_to(4);

  // Set up the stamps for this initial run of the dungeon.
  setup_enemy_sprites();
  ready_yellow_player();
  ready_blue_player();
  a=spr=OAM_OFFSET_TOP;

  music_play(1);
  
  // At this point, we loop around and handle frame scheduling
  
  ////////////////////////////////////////////////////////////

  while(1)
    {
      
      // Set Game State

      /* blue_door_state=OPEN; */
      /* yellow_door_state=OPEN; */
      /* add_points(0); */
      /* add_points(1); */

      animate_stamps();
      move_monsters();
      move_players();
      
      // End Set Game State

      ppu_wait_frame();
      
      // Update counters
      ++frame_cnt;
      if (sec==0xff)
	{
	  sec=49;
	}
      else
	{
	  sec--;
	}

      // Update sprites
      
      update_stamps();
      update_radar();
      update_teleport_timer();
     
      // VRAM update scheduler
      
      a=frame_cnt&0x03;
      switch (a)
	{
	case 0:
	  update_doors();
	  break;
	case 1:
	  update_box_timers();
	  break;
	case 2:
	  set_teleport(teleport_state);
	  break;
	case 3:
	  update_scores();
	  break;
	}

      // End VRAM update scheduler
      
    }

  ////////////////////////////////////////////////////////////

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

  spr=OAM_OFFSET_TOP;
  spr = oam_meta_spr(120,8,spr,metasprite_list[21]);
  spr = oam_meta_spr(120,36,spr,metasprite_list[33]);
  spr = oam_meta_spr(120,68,spr,metasprite_list[45]);
  spr = oam_meta_spr(120,98,spr,metasprite_list[67]);
  spr = oam_meta_spr(120,132,spr,metasprite_list[5]);
  spr = oam_meta_spr(120,164,spr,metasprite_list[58]);
  spr = oam_meta_spr(120,204,spr,metasprite_list[83]);
  
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
  update_buffer[0]=MSB(NTADR_A(1,8))|NT_UPD_VERT;
  update_buffer[1]=LSB(NTADR_A(1,8));
  update_buffer[2]=3;

  update_buffer[6]=MSB(NTADR_A(30,8))|NT_UPD_VERT;
  update_buffer[7]=LSB(NTADR_A(30,8));
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
 * update_teleport_timer()
 */
void update_teleport_timer(void)
{
  if (teleport_state==CLOSED)
    {
      if (teleport_timer==0)
	teleport_state=OPEN;
      else if (sec==0)
	teleport_timer--;
    }
  else if (teleport_state==OPEN)
    {
      // don't do anything...yet.
    }
  else
    {
      teleport_state=OPEN;
    }
}

/**
 * set_doors()
 */
void update_doors()
{
  // Clear the update buffer
  clear_update_buffer();

  // Update VRAM reflecting door states, two rows, two sets of 3 tiles each row.
  update_buffer[0]=MSB(NTADR_A(1,19))|NT_UPD_HORZ;
  update_buffer[1]=LSB(NTADR_A(1,19));
  update_buffer[2]=3;
  update_buffer[3]=(blue_door_state==0?0x65:0x76);
  update_buffer[4]=(blue_door_state==0?0x00:0x64);
  update_buffer[5]=(blue_door_state==0?0x00:0x64);
  update_buffer[6]=MSB(NTADR_A(28,19))|NT_UPD_HORZ;
  update_buffer[7]=LSB(NTADR_A(28,19));
  update_buffer[8]=3;
  update_buffer[9]=(yellow_door_state==0?0x00:0x64);
  update_buffer[10]=(yellow_door_state==0?0x00:0x64);
  update_buffer[11]=(yellow_door_state==0?0x66:0x77);
  update_buffer[12]=MSB(NTADR_A(1,20))|NT_UPD_HORZ;
  update_buffer[13]=LSB(NTADR_A(1,20));
  update_buffer[14]=3;
  update_buffer[15]=(blue_door_state==0?0x61:0x67);
  update_buffer[16]=(blue_door_state==0?0x00:0x63);
  update_buffer[17]=(blue_door_state==0?0x00:0x63);
  update_buffer[18]=MSB(NTADR_A(28,20))|NT_UPD_HORZ;
  update_buffer[19]=LSB(NTADR_A(28,20));
  update_buffer[20]=3;
  update_buffer[21]=(yellow_door_state==0?0x00:0x62);
  update_buffer[22]=(yellow_door_state==0?0x00:0x62);
  update_buffer[23]=(yellow_door_state==0?0x60:0x68);
}

/**
 * add_points(player)
 * player = scoreX to add points in score0 to
 */
void add_points(unsigned char player)
{
  ptr=(player==0 ? score1 : score2);
  a=0; // clear carry
  
  for (i=7;i-->0; )
    {
      score0[i]=(score0[i])-1;
      ptr[i]=(ptr[i])-1;
    }

  // Add each piece
  for (i=7;i-->0; )
    {
      ptr[i]=score0[i]+ptr[i]+a;
      a=(ptr[i]>9);
      if (a)
  	ptr[i]-=10;
    }
  
  for (i=7;i-->0; )
    {
      score0[i]=score0[i]+1;
      ptr[i]=(ptr[i])+1;
    }

}

/**
 * update_scores() - Update the score data for both players
 */
void update_scores(void)
{
  // Clear the update buffer
  clear_update_buffer();

  // Set the addresses for the update regions.
  update_buffer[0]=MSB(NTADR_A(2,25))|NT_UPD_HORZ;           // Blue player Line 1
  update_buffer[1]=LSB(NTADR_A(2,25));
  update_buffer[2]=7;

  update_buffer[10]=MSB(NTADR_A(2,26))|NT_UPD_HORZ;          // Blue player Line 2
  update_buffer[11]=LSB(NTADR_A(2,26));
  update_buffer[12]=7;

  update_buffer[20]=MSB(NTADR_A(23,25))|NT_UPD_HORZ;         // Yellow player Line 1
  update_buffer[21]=LSB(NTADR_A(23,25));
  update_buffer[22]=7;

  update_buffer[30]=MSB(NTADR_A(23,26))|NT_UPD_HORZ;        // Yellow player Line 2
  update_buffer[31]=LSB(NTADR_A(23,26));
  update_buffer[32]=7;

  // and finally, set the data for each.
  for (i=0;i<7;++i)
    {
      update_buffer[i+3]=score1[i];
      update_buffer[i+13]=score1[i]+16;
      update_buffer[i+23]=score2[i];
      update_buffer[i+33]=score2[i]+16;
    }
}

/**
 * update_box_timers() - Update the box timers, if active
 */
void update_box_timers(void)
{
  a=0xff;
  clear_update_buffer();
  for (i=0;i<2;i++)
    {
      update_buffer[++a]=MSB(NTADR_A((i==1?5:26),20))|NT_UPD_VERT;
      update_buffer[++a]=LSB(NTADR_A((i==1?5:26),20));
      update_buffer[++a]=2;
      
      if (stamps[STAMP_TIMER(i)]>0)
	{
	  update_buffer[++a]=stamps[STAMP_TIMER(i)];
	  update_buffer[++a]=stamps[STAMP_TIMER(i)]+0x10;
	}
      else
	{
	  update_buffer[++a]=0;
	  update_buffer[++a]=0;
	}
    }
}

/**
 * clear_stamps() - Clear the on screen stamp buffer
 */
void clear_stamps(void)
{
  memfill(&stamps,0,sizeof(stamps));
}

/**
 * clear_update_buffer() - Clear the update buffer
 */
void clear_update_buffer(void)
{
  memfill(&update_buffer,NT_UPD_EOF,sizeof(update_buffer));
}

/**
 * is_stamp_visible()
 * given stamp i, see if it actually is visible, or needs to be moved offscreen.
 */
unsigned char is_stamp_visible(void)
{
  if (stamps[STAMP_TYPE(i)]==STAMP_TYPE_BURWOR ||
      stamps[STAMP_TYPE(i)]==STAMP_TYPE_BLUE_WORRIOR ||
      stamps[STAMP_TYPE(i)]==STAMP_TYPE_YELLOW_WORRIOR ||
      stamps[STAMP_TYPE(i)]==STAMP_TYPE_WORLUK)
    return TRUE;

  // utterly naive proximity detection, but it should be fast.
  if ( (BOX_PIXEL_X(stamps[STAMP_X(0)]) == BOX_PIXEL_X(stamps[STAMP_X(i)])) ||
       (BOX_PIXEL_Y(stamps[STAMP_Y(0)]) == BOX_PIXEL_Y(stamps[STAMP_Y(i)])) ||
       (BOX_PIXEL_X(stamps[STAMP_X(1)]) == BOX_PIXEL_X(stamps[STAMP_X(i)])) ||
       (BOX_PIXEL_Y(stamps[STAMP_Y(1)]) == BOX_PIXEL_Y(stamps[STAMP_X(i)])) )
    return TRUE;
 
  
  return FALSE;
}

/**
 * update_stamps() - Update the on-screen stamps
 */
void update_stamps(void)
{
  spr=OAM_OFFSET_TOP;
  oam_clear();
  for (i=0;i<STAMP_NUM_SLOTS;i++)
    {
      if (stamps[STAMP_X(i)] == 0)
	{
	  continue;
	}
      else
	{
	  a=metasprite_animation_data[stamps[STAMP_TYPE(i)]+(stamps[STAMP_STATE(i)]*4)+stamps[STAMP_FRAME(i)]];
	  if (is_stamp_visible())
	    {
	      b=stamps[STAMP_X(i)];
	      c=stamps[STAMP_Y(i)];
	    }
	  else
	    b=c=0xF8; // Offscreen
  
	  spr = oam_meta_spr(b,c,spr,metasprite_list[a]);
	}
    }
}

/**
 * init() - just as it says.
 */
void init(void)
{
  ppu_mask(0x00);
  clear_update_buffer();
  clear_stamps();
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
      run_dungeon(1);
    }
}
