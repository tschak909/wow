#include "utils.h"
#include "constants.h"
#include "macros.h"
#include "neslib.h"

extern unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];
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
extern unsigned char* ptr;
#pragma zpsym("ptr")
extern unsigned char* dungeon;
#pragma zpsym("dungeon")
extern unsigned char i;
#pragma zpsym("i")

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

