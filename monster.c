#include "monster.h"
#include "neslib.h"
#include "constants.h"
#include "macros.h"

extern unsigned char i;
#pragma zpsym("i")
extern unsigned char a;
#pragma zpsym("a")
extern unsigned char b;
#pragma zpsym("b")
extern unsigned char d;
#pragma zpsym("d")
extern unsigned char teleport_state;
#pragma zpsym("teleport_state")
extern unsigned char teleport_timer;
#pragma zpsym("teleport_timer")

extern unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];

extern void get_current_box(void);

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
