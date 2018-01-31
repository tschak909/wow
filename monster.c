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

extern unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];
extern unsigned char lasers[LASER_NUM_FIELDS*LASER_NUM_SLOTS];
extern unsigned char score0[7];
extern unsigned char score1[7];

extern void add_points(unsigned char player);
extern void player_laser_stop(unsigned char player);
extern void get_current_box(void);
extern void get_current_laser_box(void);
extern unsigned char is_stamp_visible(void);

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
 * monster_move_all()
 * Move the monsters
 */
void monster_move_all(void)
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

      // Handle player laser to monster collision
      if (BOX_PIXEL_X(lasers[LASER_X(0)])==a && BOX_PIXEL_Y(lasers[LASER_Y(0)])==b)
	{
	  monster_die(0);
	}
      else if (BOX_PIXEL_X(lasers[LASER_X(1)])==a && BOX_PIXEL_Y(lasers[LASER_Y(1)])==b)
	{
	  monster_die(1);
	}

      if (stamps[STAMP_STATE(i)]==STATE_DYING && stamps[STAMP_FRAME(i)]==3)
	{
	  stamps[STAMP_STATE(i)]=STATE_DEAD;
	  stamps[STAMP_FRAME(i)]=0;
	  stamps[STAMP_SHOOTING(i)]=0;
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
      if (((rand8())<0x08) && lasers[LASER_SHOOTING(i)]==0 && monster_laser_count<4 && is_stamp_visible()) 
	{
	  monster_laser_fire(i);
	}
    }

  if (lasers[LASER_SHOOTING(i)]==1)
    {
      get_current_laser_box();
      if (lasers[LASER_DIRECTION(i)]==STATE_MONSTER_RIGHT)
	{
	  if (BOX_WALL_RIGHT(h) && lasers[LASER_X(i)]==PIXEL_BOX_X(e))
	    monster_laser_stop(i);
	  else
	    lasers[LASER_X(i)]+=4;
	}
      else if (lasers[LASER_DIRECTION(i)]==STATE_MONSTER_LEFT)
	{
	  if (BOX_WALL_LEFT(h) && lasers[LASER_X(i)]==PIXEL_BOX_X(e))
	    monster_laser_stop(i);
	  else
	    lasers[LASER_X(i)]-=4;
	}
      else if (lasers[LASER_DIRECTION(i)]==STATE_MONSTER_DOWN)
	{
	  if (BOX_WALL_DOWN(h) && lasers[LASER_Y(i)]==PIXEL_BOX_Y(f))
	    monster_laser_stop(i);
	  else
	    lasers[LASER_Y(i)]+=4;
	}
      else if (lasers[LASER_DIRECTION(i)]==STATE_MONSTER_UP)
	{
	  if (BOX_WALL_UP(h) && lasers[LASER_Y(i)]==PIXEL_BOX_Y(f))
	    monster_laser_stop(i);
	  else
	    lasers[LASER_Y(i)]-=4;
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
  lasers[LASER_SHOOTING(player)]=1;
  lasers[LASER_DIRECTION(player)]=stamps[STAMP_STATE(i)];
  lasers[LASER_X(player)]=PIXEL_BOX_X(a);
  lasers[LASER_Y(player)]=PIXEL_BOX_Y(b);

  switch(lasers[LASER_DIRECTION(player)])
    {
    case STATE_MONSTER_LEFT:
    case STATE_MONSTER_RIGHT:
      lasers[LASER_OFFSET_X(i)]=LASER_X_OFFSET_H;
      lasers[LASER_OFFSET_Y(i)]=LASER_Y_OFFSET_H;
      lasers[LASER_TYPE(player)]=87;
      break;
    case STATE_MONSTER_DOWN:
    case STATE_MONSTER_UP:
      lasers[LASER_OFFSET_X(i)]=LASER_X_OFFSET_V;
      lasers[LASER_OFFSET_Y(i)]=LASER_Y_OFFSET_V;
      lasers[LASER_TYPE(player)]=94;
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
  lasers[LASER_X(player)]=0xFF;
  lasers[LASER_Y(player)]=0xFF;
  lasers[LASER_TYPE(player)]=92;
  lasers[LASER_SHOOTING(player)]=0;
  lasers[LASER_DIRECTION(player)]=0;
  lasers[LASER_OFFSET_X(player)]=0;
  lasers[LASER_OFFSET_Y(player)]=0;
}

/** 
 * monster_dead_add_player_points(player)
 * Monster shot, add points to score
 * monster dead coming from i.
 */
void monster_dead_add_player_points(unsigned char player)
{
  memfill(&score0,1,sizeof(score0));
  switch(stamps[STAMP_TYPE(i)])
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
  stamps[STAMP_STATE(i)]=STATE_DYING;
  stamps[STAMP_FRAME(i)]=0;
  monster_dead_add_player_points(player);
  if (player==1 && blue_worrior_ai==1) 
    k=0; // Go tell AI to chase another monster, if applicable.
}
