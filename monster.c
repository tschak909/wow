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
extern unsigned char e;
#pragma zpsym("e")
extern unsigned char f;
#pragma zpsym("f")
extern unsigned char h;
#pragma zpsym("h")
extern unsigned char teleport_state;
#pragma zpsym("teleport_state")
extern unsigned char teleport_timer;
#pragma zpsym("teleport_timer")
extern unsigned char monster_laser_count;
#pragma zpsym("monster_laser_count")
extern unsigned char double_score_dungeon;
#pragma zpsym("double_score_dungeon")
extern unsigned char k;
#pragma zpsym("k")
extern unsigned char blue_worrior_ai;
#pragma zpsym("blue_worrior_ai")

extern unsigned char score0[7];
extern unsigned char score1[7];
extern const unsigned char pixel_box_x[11];
extern const unsigned char pixel_box_y[7];

extern unsigned char stamp_x[8];          // Stamp X position
#pragma zpsym("stamp_x")
extern unsigned char stamp_y[8];          // Stamp Y position
#pragma zpsym("stamp_y")
extern unsigned char stamp_type[8];       // Stamp type
#pragma zpsym("stamp_type")
extern unsigned char stamp_state[8];      // Stamp state
#pragma zpsym("stamp_state")
extern unsigned char stamp_last_state[8]; // Stamp last state
#pragma zpsym("stamp_last_state")
extern unsigned char stamp_frame[8];      // Stamp frame
#pragma zpsym("stamp_frame")
extern unsigned char stamp_delay[8];      // Stamp delay
#pragma zpsym("stamp_delay")
extern unsigned char stamp_timer[8];      // Stamp timer
#pragma zpsym("stamp_timer")
extern unsigned char stamp_pad[8];        // Stamp pad
#pragma zpsym("stamp_pad")
extern unsigned char stamp_shooting[8];   // Stamp shooting
#pragma zpsym("stamp_shooting")
extern unsigned char stamp_move_delay[8]; // stamp move delay

extern unsigned char laser_x[8];          // Laser X position
#pragma zpsym("laser_x")
extern unsigned char laser_y[8];          // Laser Y position
#pragma zpsym("laser_y")
extern unsigned char laser_type[8];       // Laser type
#pragma zpsym("laser_type")
extern unsigned char laser_shooting[8];   // Laser shooting
#pragma zpsym("laser_shooting")
extern unsigned char laser_direction[8];  // Laser direction
#pragma zpsym("laser_direction")
extern unsigned char laser_offset_x[8];   // Laser X offset
#pragma zpsym("laser_offset_x")
extern unsigned char laser_offset_y[8];   // Laser Y offset
#pragma zpsym("laser_offset_y")
extern unsigned char frame_cnt;
#pragma zpsym("frame_cnt")

extern void add_points(unsigned char player);
extern void player_laser_stop(unsigned char player);
extern void get_current_box(void);
extern void get_current_laser_box(void);
extern unsigned char is_stamp_visible(void);
extern void player_die(unsigned char player);

/**
 * monster_setup_all() - Set up enemy sprite spawn points
 */
void monster_setup_all(void)
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
      
      stamp_x[i]=PIXEL_BOX_X(a);
      stamp_y[i]=PIXEL_BOX_Y(b);
      stamp_type[i]=STAMP_TYPE_BURWOR;
      stamp_state[i]=rand8()&0x03; // Random initial state.
      stamp_frame[i]=rand8()&0x03; // Random enemy frame.
      stamp_delay[i]=4; // TODO: Change this per level.
    }
  // Temporary code to test all monster types
  stamp_type[5]=stamp_type[6]=STAMP_TYPE_GORWOR;
  stamp_type[7]=STAMP_TYPE_THORWOR;
}

/**
 * monster_change_direction()
 * Change monster direction.
 */
void monster_change_direction(void)
{
 change_direction:
  stamp_state[i]=rand8()&0x03;
  if (stamp_state[i]==STATE_MONSTER_LEFT && stamp_x[i]==PIXEL_BOX_X(0) && stamp_y[i]==PIXEL_BOX_Y(2) && teleport_state==OPEN)
    {
      teleport_timer=2;
      teleport_state=CLOSED;
      stamp_x[i]=PIXEL_BOX_X(9);
    }
  else if (stamp_state[i]==STATE_MONSTER_RIGHT && stamp_x[i]==PIXEL_BOX_X(9) && stamp_y[i]==PIXEL_BOX_Y(2) && teleport_state==OPEN)
    {
      teleport_timer=2;
      teleport_state=CLOSED;
      stamp_x[i]=PIXEL_BOX_X(0);
    }
  else if (stamp_state[i]==STATE_MONSTER_LEFT && BOX_WALL_LEFT(d))
    goto change_direction;
  else if (stamp_state[i]==STATE_MONSTER_RIGHT && BOX_WALL_RIGHT(d))
    goto change_direction;
  else if (stamp_state[i]==STATE_MONSTER_UP && BOX_WALL_UP(d))
    goto change_direction;
  else if (stamp_state[i]==STATE_MONSTER_DOWN && BOX_WALL_DOWN(d))
    goto change_direction;
}

/**
 * monster_move_all()
 * Move the monsters
 */
void monster_move_all(void)
{
  for (i=2;i<STAMP_NUM_SLOTS;i++)
    {
      get_current_box();
      if ((stamp_x[i]==PIXEL_BOX_X(a)) && (stamp_y[i]==PIXEL_BOX_Y(b)))
	{
	  monster_change_direction();
	}
      else
	{
	  // We are not aligned.
	  if (stamp_state[i]==STATE_MONSTER_RIGHT && stamp_last_state[i]==STATE_MONSTER_LEFT)
	    stamp_state[i]=STATE_MONSTER_RIGHT;
	  else if (stamp_state[i]==STATE_MONSTER_LEFT && stamp_last_state[i]==STATE_MONSTER_RIGHT)
	    stamp_state[i]=STATE_MONSTER_LEFT;
	  else if (stamp_state[i]==STATE_MONSTER_UP && stamp_last_state[i]==STATE_MONSTER_DOWN)
	    stamp_state[i]=STATE_MONSTER_UP;
	  else if (stamp_state[i]==STATE_MONSTER_DOWN && stamp_last_state[i]==STATE_PLAYER_UP)
	    stamp_state[i]=STATE_MONSTER_DOWN;
	  else
	    stamp_state[i]=stamp_last_state[i];
	  
	}

      // Handle player laser to monster collision
      if (BOX_PIXEL_X(laser_x[0])==a && BOX_PIXEL_Y(laser_y[0])==b)
	{
	  if (stamp_state[i]==STATE_DYING)
	    {
	      // This is here to prevent perpetual point grabbage
	    }
	  else
	    monster_die(0);
	}
      else if (BOX_PIXEL_X(laser_x[1])==a && BOX_PIXEL_Y(laser_y[1])==b)
	{
	  if (stamp_state[i]==STATE_DYING)
	    {
	      // This is here to prevent perpetual point grabbage
	    }
	  else
	    monster_die(1);
	}

      if (stamp_state[i]==STATE_DYING && stamp_frame[i]==3)
	{
	  stamp_state[i]=STATE_DEAD;
	  stamp_frame[i]=0;
	  stamp_shooting[i]=0;
	}
      
      // Handle state movement
      if (stamp_move_delay[i]==0)
	{
	  if (stamp_state[i]==STATE_MONSTER_RIGHT)
	    stamp_x[i]++;
	  else if (stamp_state[i]==STATE_MONSTER_LEFT)
	    stamp_x[i]--;
	  else if (stamp_state[i]==STATE_MONSTER_UP)
	    stamp_y[i]--;
	  else if (stamp_state[i]==STATE_MONSTER_DOWN)
	    stamp_y[i]++;
	}
      stamp_last_state[i]=stamp_state[i];
      monster_shoot();
    }
}

/**
 * monster_shoot()
 * Fire phasor if worrior is nearby
 */
void monster_shoot(void)
{
  // This is holy shit naive. The previous naive implementation took too much CPU time.
  if (rand8()>0xC0)
    {
      if (((rand8())<0x08) && laser_shooting[i]==0 && monster_laser_count<4 && is_stamp_visible())
  	{
  	  monster_laser_fire(i);
  	}
    }

  if (laser_shooting[i]==1)
    {
      get_current_laser_box();

      if (stamp_state[0]<STATE_PLAYER_DOWN_IDLE_SHOOTING && e==BOX_PIXEL_X(stamp_x[0]) && f==BOX_PIXEL_Y(stamp_y[0]))
	{
	  // Monster laser hit yellow worrior
	  player_die(0);
	  monster_laser_stop(i);
	}
      else if (stamp_state[1]<STATE_PLAYER_DOWN_IDLE_SHOOTING && e==BOX_PIXEL_X(stamp_x[1]) && f==BOX_PIXEL_Y(stamp_y[1]))
	{
	  // Monster laser hit blue worrior
	  player_die(1);
	  monster_laser_stop(i);
	}
      else if (laser_direction[i]==STATE_MONSTER_RIGHT)
	{
	  if (BOX_WALL_RIGHT(h) && laser_x[i]==PIXEL_BOX_X(e))
	    monster_laser_stop(i);
	  else
	    laser_x[i]+=2;
	}
      else if (laser_direction[i]==STATE_MONSTER_LEFT)
	{
	  if (BOX_WALL_LEFT(h) && laser_x[i]==PIXEL_BOX_X(e))
	    monster_laser_stop(i);
	  else
	    laser_x[i]-=2;
	}
      else if (laser_direction[i]==STATE_MONSTER_DOWN)
	{
	  if (BOX_WALL_DOWN(h) && laser_y[i]==PIXEL_BOX_Y(f))
	    monster_laser_stop(i);
	  else
	    laser_y[i]+=2;
	}
      else if (laser_direction[i]==STATE_MONSTER_UP)
	{
	  if (BOX_WALL_UP(h) && laser_y[i]==PIXEL_BOX_Y(f))
	    monster_laser_stop(i);
	  else
	    laser_y[i]-=2;
	}
    }
}

/**
 * monster_laser_fire(i)
 * Start laser fire
 */
void monster_laser_fire(unsigned char player)
{
  // Position laser in monster box.
  monster_laser_count++;
  laser_shooting[player]=1;
  laser_direction[player]=stamp_state[i];
  laser_x[player]=PIXEL_BOX_X(a);
  laser_y[player]=PIXEL_BOX_Y(b);

  switch(laser_direction[player])
    {
    case STATE_MONSTER_LEFT:
    case STATE_MONSTER_RIGHT:
      laser_offset_x[i]=LASER_X_OFFSET_H;
      laser_offset_y[i]=LASER_Y_OFFSET_H;
      laser_type[player]=87;
      break;
    case STATE_MONSTER_DOWN:
    case STATE_MONSTER_UP:
      laser_offset_x[i]=LASER_X_OFFSET_V;
      laser_offset_y[i]=LASER_Y_OFFSET_V;
      laser_type[player]=94;
      break;
    }
}

/**
 * monster_laser_stop(i);
 * Stop laser fire.
 */
void monster_laser_stop(unsigned char player)
{
  monster_laser_count--;
  laser_x[player]=0xFF;
  laser_y[player]=0xFF;
  laser_type[player]=92;
  laser_shooting[player]=0;
  laser_direction[player]=0;
  laser_offset_x[player]=0;
  laser_offset_y[player]=0;
}

/** 
 * monster_dead_add_player_points(player)
 * Monster shot, add points to score
 * monster dead coming from i.
 */
void monster_dead_add_player_points(unsigned char player)
{
  memfill(&score0,1,sizeof(score0));
  switch(stamp_type[i])
    {
    case STAMP_TYPE_BURWOR:
      score0[4]=2; // 100 points.
      break;
    case STAMP_TYPE_GORWOR:
      score0[4]=3; // 200 points
      break;
    case STAMP_TYPE_THORWOR:
      score0[4]=6; // 500 points
      break;
    case STAMP_TYPE_WORLUK:
      score0[3]=3; // 2000 points
      double_score_dungeon=1;
      break;
    }

  add_points(player);
}

/**
 * monster_die(player)
 * Monster was killed by player
 */
void monster_die(unsigned char player)
{
  player_laser_stop(player);
  if (laser_shooting[i]==1)
    monster_laser_stop(i); // Stop any laser that might be firing from monster.
  stamp_state[i]=STATE_DYING;
  stamp_frame[i]=0;
  monster_dead_add_player_points(player);

  if (player==1 && blue_worrior_ai==1) 
    k=0; // Go tell AI to chase another monster, if applicable.
}
