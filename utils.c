#include "utils.h"
#include "constants.h"
#include "macros.h"
#include "neslib.h"

extern unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];
extern unsigned char lasers[LASER_NUM_FIELDS*LASER_NUM_SLOTS];
extern unsigned char update_buffer[80];
extern unsigned char score0[7];
extern unsigned char score1[7];
extern unsigned char score2[7];

extern unsigned char bright;
#pragma zpsym("bright")
extern unsigned char a;
#pragma zpsym("a")
extern unsigned char b;
#pragma zpsym("b")
extern unsigned char c;
#pragma zpsym("c")
extern unsigned char d;
#pragma zpsym("d")
extern unsigned char e;
#pragma zpsym("e")
extern unsigned char f;
#pragma zpsym("f")
extern unsigned char g;
#pragma zpsym("g")
extern unsigned char h;
#pragma zpsym("h")

extern unsigned char* ptr;
#pragma zpsym("ptr")
extern unsigned char* dungeon;
#pragma zpsym("dungeon")
extern unsigned char i;
#pragma zpsym("i")
extern unsigned char j;
#pragma zpsym("j")

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
 * stamp_type_to_radar() - Choose radar sprite to use 
 */
unsigned char stamp_type_to_radar(unsigned int t)
{
  switch (t)
    {
    case STAMP_TYPE_BURWOR:
      return 0xC5;
    case STAMP_TYPE_GORWOR:
    case STAMP_TYPE_WORLUK:
      return 0xC6;
    case STAMP_TYPE_THORWOR:
      return 0xC7;
    case STAMP_TYPE_DEAD:
      return 0xff;
    }
}

/**
 * add_points(player)
 * player = scoreX to add points in score0 to
 */
void add_points(unsigned char player)
{
  j=i; // save I
  ptr=(player==0 ? score2 : score1);
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
  
  i=j; // Restore I
}

/**
 * is_stamp_visible()
 * given stamp i, see if it actually is visible, or needs to be moved offscreen.
 */
unsigned char is_stamp_visible(void)
{
  /* return TRUE; */
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
 * get_current_laser_box()
 * Get the current dungeon box for a laser
 * i = the stamp to return in e,f,g,h
 * e = the X box
 * f = the Y box
 * g = the dungeon box #
 * h = the box data.
 */
void get_current_laser_box(void)
{
  e=div24(lasers[LASER_X(i)]+8);
  f=div24(lasers[LASER_Y(i)]-8);
  g=(f*10)+e; // G is now the box #
  h=dungeon[g];
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
	  
	  // If monster is dying and on last frame, set state to dead.
	  if (stamps[STAMP_STATE(i)]==STATE_DYING && stamps[STAMP_FRAME(i)]==3)
	    {
	      stamps[STAMP_STATE(i)]=STATE_DEAD;
	      stamps[STAMP_X(i)]=0xFF;
	      stamps[STAMP_Y(i)]=0xFF;
	    }
	  
	  if (stamps[STAMP_STATE(i)]==STATE_DYING) // Dying plays at max speed.
	    stamps[STAMP_DELAY(i)]=1;
	  else if (i>1) // Delay only applies to enemies.
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
