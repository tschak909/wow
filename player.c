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
extern unsigned char teleport_state;
#pragma zpsym("teleport_state")
extern unsigned char teleport_timer;
#pragma zpsym("teleport_timer")
extern unsigned char sec;
#pragma zpsym("sec")
extern unsigned char player_trigger[2];
#pragma zpsym("player_trigger")
extern unsigned char player_last_trigger[2];
#pragma zpsym("player_last_trigger")
extern unsigned char player_shooting_last_state[2];
#pragma zpsym("player_shooting_last_state")

extern unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];
extern unsigned char lasers[LASER_NUM_FIELDS*LASER_NUM_SLOTS];
extern unsigned char score0[7];
extern unsigned char score1[7];
extern unsigned char score2[7];

extern void get_current_box(void);
extern void get_current_laser_box(void);

/**
 * player_blue_ready() - Ready the blue player
 */
void player_blue_ready(void)
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
 * player_yellow_ready() - Ready the blue player
 */
void player_yellow_ready(void)
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
 * player_handle_idle()
 */
void player_handle_idle(void)
{
  // Change to idle state if pad is idle.
  switch(stamps[STAMP_LAST_STATE(i)])
    {
    case STATE_PLAYER_RIGHT:
      stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_RIGHT_IDLE_SHOOTING:STATE_PLAYER_RIGHT_IDLE);
      break;
    case STATE_PLAYER_LEFT:
      stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_LEFT_IDLE_SHOOTING:STATE_PLAYER_LEFT_IDLE);
      break;
    case STATE_PLAYER_UP:
      stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_UP_IDLE_SHOOTING:STATE_PLAYER_UP_IDLE);
      break;
    case STATE_PLAYER_DOWN:
      stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_DOWN_IDLE_SHOOTING:STATE_PLAYER_DOWN_IDLE);
      break;
    }
}

/**
 * player_in_field()
 * Handle when player is on the playfield
 */
void player_in_field(void)
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
      else if (PLAYER_PAD_RIGHT(i) && (stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_RIGHT || stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_RIGHT_IDLE) && !BOX_WALL_RIGHT(d))
	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_RIGHT_SHOOTING:STATE_PLAYER_RIGHT);
      else if (PLAYER_PAD_LEFT(i) && (stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_LEFT || stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_LEFT_IDLE) && !BOX_WALL_LEFT(d))
      	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_LEFT_SHOOTING:STATE_PLAYER_LEFT);
      else if (PLAYER_PAD_UP(i) && (stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_UP || stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_UP_IDLE) && !BOX_WALL_UP(d))
	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_UP_SHOOTING:STATE_PLAYER_UP);
      else if (PLAYER_PAD_DOWN(i) && (stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_DOWN || stamps[STAMP_LAST_STATE(i)] != STATE_PLAYER_DOWN_IDLE) && !BOX_WALL_DOWN(d))
      	stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_DOWN_SHOOTING:STATE_PLAYER_DOWN);
      else if (PLAYER_PAD_IDLE(i))
	player_handle_idle();
      
      if (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_LEFT && stamps[STAMP_X(i)]==PIXEL_BOX_X(0) && stamps[STAMP_Y(i)]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	stamps[STAMP_STATE(i)]=STATE_PLAYER_LEFT;
      else if (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_RIGHT && stamps[STAMP_X(i)]==PIXEL_BOX_X(9) && stamps[STAMP_Y(i)]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	stamps[STAMP_STATE(i)]=STATE_PLAYER_RIGHT;
      else if ((stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_RIGHT || stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_RIGHT_IDLE) && BOX_WALL_RIGHT(d))
      	stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_RIGHT_IDLE_SHOOTING:STATE_PLAYER_RIGHT_IDLE);
      else if ((stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_LEFT || stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_LEFT_IDLE) && BOX_WALL_LEFT(d))
      	stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_LEFT_IDLE_SHOOTING:STATE_PLAYER_LEFT_IDLE);
      else if ((stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_UP || stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_UP_IDLE) && BOX_WALL_UP(d))
	stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_UP_IDLE_SHOOTING:STATE_PLAYER_UP_IDLE);
      else if ((stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_DOWN || stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_DOWN_IDLE) && BOX_WALL_DOWN(d))
      	stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_DOWN_IDLE_SHOOTING:STATE_PLAYER_DOWN_IDLE);
    }
  else
    {
      // We are not aligned.
      if (PLAYER_PAD_IDLE(i))
      	player_handle_idle();
      else if (PLAYER_PAD_RIGHT(i) && (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_LEFT))
      	stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_RIGHT_SHOOTING:STATE_PLAYER_RIGHT);
      else if (PLAYER_PAD_LEFT(i) && (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_RIGHT))
      	stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_LEFT_SHOOTING:STATE_PLAYER_LEFT);
      else if (PLAYER_PAD_UP(i) && (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_DOWN))
      	stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_UP_SHOOTING:STATE_PLAYER_UP);
      else if (PLAYER_PAD_DOWN(i) && (stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_UP))
      	stamps[STAMP_STATE(i)]=(stamps[STAMP_SHOOTING(i)]==1?STATE_PLAYER_DOWN_SHOOTING:STATE_PLAYER_DOWN);
      else
	{
	  if (stamps[STAMP_SHOOTING(i)]==1 && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_LEFT)
	    stamps[STAMP_STATE(i)]=STATE_PLAYER_LEFT_SHOOTING;
	  else if (stamps[STAMP_SHOOTING(i)]==1 && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_RIGHT)
	    stamps[STAMP_STATE(i)]=STATE_PLAYER_RIGHT_SHOOTING;
	  else if (stamps[STAMP_SHOOTING(i)]==1 && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_DOWN)
	    stamps[STAMP_STATE(i)]=STATE_PLAYER_DOWN_SHOOTING;
	  else if (stamps[STAMP_SHOOTING(i)]==1 && stamps[STAMP_LAST_STATE(i)]==STATE_PLAYER_UP)
	    stamps[STAMP_STATE(i)]=STATE_PLAYER_UP_SHOOTING;
	  else
	    stamps[STAMP_STATE(i)]=stamps[STAMP_LAST_STATE(i)];
	}
    }

  switch(stamps[STAMP_STATE(i)])
    {
    case STATE_PLAYER_RIGHT:
      stamps[STAMP_X(i)]+=2;
      break;
    case STATE_PLAYER_LEFT:
      stamps[STAMP_X(i)]-=2;
      break;
    case STATE_PLAYER_UP:
      stamps[STAMP_Y(i)]-=2;
      break;
    case STATE_PLAYER_DOWN:
      stamps[STAMP_Y(i)]+=2;
      break;
    }
  
  // And set last state, if we aren't idle.
  if (!PLAYER_PAD_IDLE(i) && stamps[STAMP_SHOOTING(i)]==0)
    stamps[STAMP_LAST_STATE(i)]=stamps[STAMP_STATE(i)];  

  // Convert trigger press to shooting state.
  if (player_trigger[i]==player_last_trigger[i])
    {
      // Debounce
    }
  else
    {
      if (player_last_trigger[i]==0 && player_trigger[i]==1)
  	{
  	  stamps[STAMP_SHOOTING(i)]=1;
  	  stamps[STAMP_FRAME(i)]=0;
	  player_laser_fire(i);
  	}
    }

  if (stamps[STAMP_SHOOTING(i)]==1 && stamps[STAMP_FRAME(i)]==3)
    stamps[STAMP_SHOOTING(i)]=0;

  if (lasers[LASER_SHOOTING(i)]==1)
    {
      get_current_laser_box();
      if (lasers[LASER_DIRECTION(i)]==STATE_PLAYER_RIGHT_SHOOTING || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_RIGHT || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_RIGHT_IDLE || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_RIGHT_IDLE_SHOOTING)
	{	    
	  if (BOX_WALL_RIGHT(h) && lasers[LASER_X(i)]==PIXEL_BOX_X(e))
	      player_laser_stop(i);
	  else
 	      lasers[LASER_X(i)]+=8;
	}
      else if (lasers[LASER_DIRECTION(i)]==STATE_PLAYER_LEFT_SHOOTING || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_LEFT || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_LEFT_IDLE || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_LEFT_IDLE_SHOOTING)
	{
	  if (BOX_WALL_LEFT(h) && lasers[LASER_X(i)]==PIXEL_BOX_X(e))
	      player_laser_stop(i);
	  else
	      lasers[LASER_X(i)]-=8;
	}
      else if (lasers[LASER_DIRECTION(i)]==STATE_PLAYER_DOWN_SHOOTING || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_DOWN || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_DOWN_IDLE || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_DOWN_IDLE_SHOOTING)
	{
	  if (BOX_WALL_DOWN(h) && lasers[LASER_Y(i)]==PIXEL_BOX_Y(f))
	      player_laser_stop(i);
	  else
	      lasers[LASER_Y(i)]+=8;
	}
      else if (lasers[LASER_DIRECTION(i)]==STATE_PLAYER_UP_SHOOTING || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_UP || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_UP_IDLE || lasers[LASER_DIRECTION(i)]==STATE_PLAYER_UP_IDLE_SHOOTING)
	{
	  if (BOX_WALL_UP(h) && lasers[LASER_Y(i)]==PIXEL_BOX_Y(f))
	      player_laser_stop(i);
	  else
	      lasers[LASER_Y(i)]-=8;
	}
    }

  
  // REMOVE: Show yellow state in yellow score.
  score2[0]=e+1;
  score2[1]=f+1;
}

/**
 * player_in_box()
 * Handle when player is in box.
 */
void player_in_box(void)
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
 * player_move_all()
 */
void player_move_all(void)
{
  for (i=0;i<2;i++)
    {
      get_current_box();
      stamps[STAMP_PAD(i)]=pad_poll(i);
      player_trigger[i]=(PLAYER_PAD_A(i)?1:0);
      
      if (stamps[STAMP_Y(i)]==PIXEL_BOX_Y(6)-1)
	{
	  player_in_box();
	}
      else
	{
	  player_in_field();
	}

      player_last_trigger[i]=player_trigger[i];
      
    }
}

/**
 * player_laser_fire()
 */
void player_laser_fire(unsigned char player)
{
  // Position laser in player box.
  lasers[LASER_SHOOTING(player)]=1;
  lasers[LASER_DIRECTION(player)]=stamps[STAMP_STATE(i)];
  lasers[LASER_X(player)]=PIXEL_BOX_X(a);
  lasers[LASER_Y(player)]=PIXEL_BOX_Y(b);

  switch(lasers[LASER_DIRECTION(player)])
    {
    case STATE_PLAYER_LEFT:
    case STATE_PLAYER_LEFT_IDLE:
    case STATE_PLAYER_LEFT_SHOOTING:
    case STATE_PLAYER_LEFT_IDLE_SHOOTING:
    case STATE_PLAYER_RIGHT:
    case STATE_PLAYER_RIGHT_IDLE:
    case STATE_PLAYER_RIGHT_SHOOTING:
    case STATE_PLAYER_RIGHT_IDLE_SHOOTING:
      lasers[LASER_OFFSET_X(i)]=LASER_X_OFFSET_H;
      lasers[LASER_OFFSET_Y(i)]=LASER_Y_OFFSET_H;
      lasers[LASER_TYPE(player)]=0xC8;
      break;
    case STATE_PLAYER_DOWN:
    case STATE_PLAYER_DOWN_IDLE:
    case STATE_PLAYER_DOWN_SHOOTING:
    case STATE_PLAYER_DOWN_IDLE_SHOOTING:
    case STATE_PLAYER_UP:
    case STATE_PLAYER_UP_IDLE:
    case STATE_PLAYER_UP_SHOOTING:
    case STATE_PLAYER_UP_IDLE_SHOOTING:
      lasers[LASER_OFFSET_X(i)]=LASER_X_OFFSET_V;
      lasers[LASER_OFFSET_Y(i)]=LASER_Y_OFFSET_V;
      lasers[LASER_TYPE(player)]=0xCA;
      break;
    }
}

/**
 * player_laser_stop()
 */
void player_laser_stop(unsigned char player)
{
  lasers[LASER_X(player)]=0;
  lasers[LASER_Y(player)]=0;
  lasers[LASER_TYPE(player)]=0;
  lasers[LASER_SHOOTING(player)]=0;
  lasers[LASER_DIRECTION(player)]=0;
  lasers[LASER_OFFSET_X(player)]=0;
  lasers[LASER_OFFSET_Y(player)]=0;
}
