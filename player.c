#include "player.h"
#include "constants.h"
#include "macros.h"
#include "neslib.h"

extern unsigned char blue_door_state;
#pragma zpsym("blue_door_state")
extern unsigned char yellow_door_state;
#pragma zpsym("yellow_door_state")
extern unsigned char i;
#pragma zpsym("i")
extern unsigned char a;
#pragma zpsym("a")
extern unsigned char b;
#pragma zpsym("b")
extern unsigned char teleport_state;
#pragma zpsym("teleport_state")
extern unsigned char teleport_timer;
#pragma zpsym("teleport_timer")
extern unsigned char d;
#pragma zpsym("d")
extern unsigned char sec;
#pragma zpsym("sec")

extern unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];
extern unsigned char score0[7];
extern unsigned char score1[7];
extern unsigned char score2[7];

extern void get_current_box(void);

/**
 * ready_blue_player() - Ready the blue player
 */
void ready_blue_player(void)
{
  stamps[STAMP_TIMER(1)]=3; // Player is in the box.
  stamps[STAMP_X(1)]=PIXEL_BOX_X(0);
  stamps[STAMP_Y(1)]=PIXEL_BOX_Y(6)-1; // 6 is the special spawn box.
  stamps[STAMP_TYPE(1)]=STAMP_TYPE_BLUE_WORRIOR;
  stamps[STAMP_STATE(1)]=stamps[STAMP_LAST_STATE(1)]=1; // Facing right Idle
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
  stamps[STAMP_STATE(0)]=stamps[STAMP_LAST_STATE(i)]=3; // Facing left Idle
  stamps[STAMP_FRAME(0)]=0;
  stamps[STAMP_DELAY(0)]=0;
  yellow_door_state=OPEN;
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

  stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)];

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

  // REMOVE: Show yellow state in yellow score.
  score2[0]=stamps[STAMP_STATE(0)]+1;

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
