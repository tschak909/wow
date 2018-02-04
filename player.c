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
extern unsigned char blue_worrior_ai;
#pragma zpsym("blue_worrior_ai")
extern unsigned char j;
#pragma zpsym("j")
extern unsigned char frame_cnt;
#pragma zpsym("frame_cnt")
extern unsigned char k;
#pragma zpsym("k")
extern unsigned char player_shot_loop[2];
#pragma zpsym("player_shot_loop")

extern unsigned char score0[7];
extern unsigned char score1[7];
extern unsigned char score2[7];
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
extern unsigned char stamp_move_delay[8]; // Stamp move delay
#pragma zpsym("stamp_move_delay")

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

extern void get_current_box(void);
extern void get_current_laser_box(void);
extern void add_points(unsigned char player);

/**
 * player_blue_ready() - Ready the blue player
 */
void player_blue_ready(void)
{
  stamp_timer[1]=3; // Player is in the box.
  stamp_x[1]=PIXEL_BOX_X(0);
  stamp_y[1]=PIXEL_BOX_Y(6)-1; // 6 is the special spawn box.
  stamp_type[1]=STAMP_TYPE_BLUE_WORRIOR;
  stamp_state[1]=stamp_last_state[1]=1; // Facing right Idle
  stamp_frame[1]=0;
  stamp_delay[1]=0;
  blue_door_state=OPEN;
}

/**
 * player_yellow_ready() - Ready the blue player
 */
void player_yellow_ready(void)
{
  stamp_timer[0]=6;
  stamp_x[0]=PIXEL_BOX_X(9);
  stamp_y[0]=PIXEL_BOX_Y(6)-1; // 6 is the special spawn box.
  stamp_type[0]=STAMP_TYPE_YELLOW_WORRIOR;
  stamp_state[0]=stamp_last_state[0]=3; // Facing left Idle
  stamp_frame[0]=0;
  stamp_delay[0]=0;
  yellow_door_state=OPEN;
}

/**
 * player_handle_idle()
 */
void player_handle_idle(void)
{
  // Change to idle state if pad is idle.
  switch(stamp_last_state[i])
    {
    case STATE_PLAYER_RIGHT:
      stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_RIGHT_IDLE_SHOOTING:STATE_PLAYER_RIGHT_IDLE);
      break;
    case STATE_PLAYER_LEFT:
      stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_LEFT_IDLE_SHOOTING:STATE_PLAYER_LEFT_IDLE);
      break;
    case STATE_PLAYER_UP:
      stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_UP_IDLE_SHOOTING:STATE_PLAYER_UP_IDLE);
      break;
    case STATE_PLAYER_DOWN:
      stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_DOWN_IDLE_SHOOTING:STATE_PLAYER_DOWN_IDLE);
      break;
    }
}

/**
 * player_in_field()
 * Handle when player is on the playfield
 */
void player_in_field(void)
{
  if (frame_cnt==0)
    set_rand(stamp_x[0]);

  if (stamp_state[i]==STATE_DEAD)
    {
      goto no_move;
    }
  else if (stamp_state[i]>STATE_PLAYER_DOWN_IDLE_SHOOTING || stamp_state[i]==STATE_DYING)
    {
      player_shot();
    }
  else if ((stamp_x[i]==PIXEL_BOX_X(a)) && (stamp_y[i]==PIXEL_BOX_Y(b)))
    {
      // We are aligned.
      if (PLAYER_PAD_LEFT(i) && stamp_last_state[i] != STATE_PLAYER_RIGHT && stamp_x[i]==PIXEL_BOX_X(0) && stamp_y[i]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	{
	  stamp_x[i]=PIXEL_BOX_X(9);
	  teleport_state=CLOSED;
	  teleport_timer=2;	  
	}
      else if (PLAYER_PAD_RIGHT(i) && stamp_last_state[i] != STATE_PLAYER_LEFT && stamp_x[i]==PIXEL_BOX_X(9) && stamp_y[i]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	{
	  stamp_x[i]=PIXEL_BOX_X(0);
	  teleport_state=CLOSED;
	  teleport_timer=2;
	}
      else if (PLAYER_PAD_RIGHT(i) && (stamp_last_state[i] != STATE_PLAYER_RIGHT || stamp_last_state[i] != STATE_PLAYER_RIGHT_IDLE) && !BOX_WALL_RIGHT(d))
	stamp_state[i]=stamp_last_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_RIGHT_SHOOTING:STATE_PLAYER_RIGHT);
      else if (PLAYER_PAD_LEFT(i) && (stamp_last_state[i] != STATE_PLAYER_LEFT || stamp_last_state[i] != STATE_PLAYER_LEFT_IDLE) && !BOX_WALL_LEFT(d))
      	stamp_state[i]=stamp_last_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_LEFT_SHOOTING:STATE_PLAYER_LEFT);
      else if (PLAYER_PAD_UP(i) && (stamp_last_state[i] != STATE_PLAYER_UP || stamp_last_state[i] != STATE_PLAYER_UP_IDLE) && !BOX_WALL_UP(d))
	stamp_state[i]=stamp_last_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_UP_SHOOTING:STATE_PLAYER_UP);
      else if (PLAYER_PAD_DOWN(i) && (stamp_last_state[i] != STATE_PLAYER_DOWN || stamp_last_state[i] != STATE_PLAYER_DOWN_IDLE) && !BOX_WALL_DOWN(d))
      	stamp_state[i]=stamp_last_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_DOWN_SHOOTING:STATE_PLAYER_DOWN);
      else if (PLAYER_PAD_IDLE(i))
	player_handle_idle();
      
      if (stamp_last_state[i]==STATE_PLAYER_LEFT && stamp_x[i]==PIXEL_BOX_X(0) && stamp_y[i]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	stamp_state[i]=STATE_PLAYER_LEFT;
      else if (stamp_last_state[i]==STATE_PLAYER_RIGHT && stamp_x[i]==PIXEL_BOX_X(9) && stamp_y[i]==PIXEL_BOX_Y(2) && teleport_state == OPEN)
	stamp_state[i]=STATE_PLAYER_RIGHT;
      else if ((stamp_last_state[i]==STATE_PLAYER_RIGHT || stamp_last_state[i]==STATE_PLAYER_RIGHT_IDLE) && BOX_WALL_RIGHT(d))
      	stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_RIGHT_IDLE_SHOOTING:STATE_PLAYER_RIGHT_IDLE);
      else if ((stamp_last_state[i]==STATE_PLAYER_LEFT || stamp_last_state[i]==STATE_PLAYER_LEFT_IDLE) && BOX_WALL_LEFT(d))
      	stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_LEFT_IDLE_SHOOTING:STATE_PLAYER_LEFT_IDLE);
      else if ((stamp_last_state[i]==STATE_PLAYER_UP || stamp_last_state[i]==STATE_PLAYER_UP_IDLE) && BOX_WALL_UP(d))
	stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_UP_IDLE_SHOOTING:STATE_PLAYER_UP_IDLE);
      else if ((stamp_last_state[i]==STATE_PLAYER_DOWN || stamp_last_state[i]==STATE_PLAYER_DOWN_IDLE) && BOX_WALL_DOWN(d))
      	stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_DOWN_IDLE_SHOOTING:STATE_PLAYER_DOWN_IDLE);
    }
  else
    {
      // We are not aligned.
      if (PLAYER_PAD_IDLE(i))
      	player_handle_idle();
      else if (PLAYER_PAD_RIGHT(i) && (stamp_last_state[i]==STATE_PLAYER_LEFT))
      	stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_RIGHT_SHOOTING:STATE_PLAYER_RIGHT);
      else if (PLAYER_PAD_LEFT(i) && (stamp_last_state[i]==STATE_PLAYER_RIGHT))
      	stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_LEFT_SHOOTING:STATE_PLAYER_LEFT);
      else if (PLAYER_PAD_UP(i) && (stamp_last_state[i]==STATE_PLAYER_DOWN))
      	stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_UP_SHOOTING:STATE_PLAYER_UP);
      else if (PLAYER_PAD_DOWN(i) && (stamp_last_state[i]==STATE_PLAYER_UP))
      	stamp_state[i]=(stamp_shooting[i]==1?STATE_PLAYER_DOWN_SHOOTING:STATE_PLAYER_DOWN);
      else
	{
	  if (stamp_shooting[i]==1 && stamp_last_state[i]==STATE_PLAYER_LEFT)
	    stamp_state[i]=STATE_PLAYER_LEFT_SHOOTING;
	  else if (stamp_shooting[i]==1 && stamp_last_state[i]==STATE_PLAYER_RIGHT)
	    stamp_state[i]=STATE_PLAYER_RIGHT_SHOOTING;
	  else if (stamp_shooting[i]==1 && stamp_last_state[i]==STATE_PLAYER_DOWN)
	    stamp_state[i]=STATE_PLAYER_DOWN_SHOOTING;
	  else if (stamp_shooting[i]==1 && stamp_last_state[i]==STATE_PLAYER_UP)
	    stamp_state[i]=STATE_PLAYER_UP_SHOOTING;
	  else
	    stamp_state[i]=stamp_last_state[i];
	}
    }

  // Apply player movement. AI player moves at half speed.
  if (stamp_move_delay[i]==0)
    {
      switch(stamp_state[i])
	{
	case STATE_PLAYER_RIGHT:
	  stamp_x[i]+=(blue_worrior_ai==1&&i==1)?1:2;
	  break;
	case STATE_PLAYER_LEFT:
	  stamp_x[i]-=(blue_worrior_ai==1&&i==1)?1:2;
	  break;
	case STATE_PLAYER_UP:
	  stamp_y[i]-=(blue_worrior_ai==1&&i==1)?1:2;
	  break;
	case STATE_PLAYER_DOWN:
	  stamp_y[i]+=(blue_worrior_ai==1&&i==1)?1:2;
	  break;
	}
    }
  
  // And set last state, if we aren't idle.
  if (!PLAYER_PAD_IDLE(i) && stamp_shooting[i]==0)
    stamp_last_state[i]=stamp_state[i];  

  // Convert trigger press to shooting state.
  if (player_trigger[i]==player_last_trigger[i])
    {
      // Debounce
    }
  else
    {
      if (player_last_trigger[i]==0 && player_trigger[i]==1)
  	{
  	  stamp_shooting[i]=1;
  	  stamp_frame[i]=0;
	  player_laser_fire(i);
  	}
    }

  // Finally handle AI trigger. Naive and somewhat random, for now.
  if (rand8()>0xc0)
    if (blue_worrior_ai==1 && rand8()<0x08 && i==1 && laser_shooting[i]==0)
      {
  	stamp_shooting[1]=1;
  	stamp_frame[1]=0;
  	player_laser_fire(1);
      }
  
  // Stop shooting animation if we're done.
  if (stamp_shooting[i]==1 && stamp_frame[i]==3)
    stamp_shooting[i]=0;
    
  // Handle shooting.  
  if (laser_shooting[i]==1)
    {
      get_current_laser_box();

      if (laser_direction[i]==STATE_PLAYER_RIGHT_SHOOTING || laser_direction[i]==STATE_PLAYER_RIGHT || laser_direction[i]==STATE_PLAYER_RIGHT_IDLE || laser_direction[i]==STATE_PLAYER_RIGHT_IDLE_SHOOTING)
	{	    
	  if (BOX_WALL_RIGHT(h) && laser_x[i]==PIXEL_BOX_X(e))
	      player_laser_stop(i);
	  else
	    laser_x[i]+=frame_cnt&0x01?0:8;
	}
      else if (laser_direction[i]==STATE_PLAYER_LEFT_SHOOTING || laser_direction[i]==STATE_PLAYER_LEFT || laser_direction[i]==STATE_PLAYER_LEFT_IDLE || laser_direction[i]==STATE_PLAYER_LEFT_IDLE_SHOOTING)
	{
	  if (BOX_WALL_LEFT(h) && laser_x[i]==PIXEL_BOX_X(e))
	      player_laser_stop(i);
	  else
	      laser_x[i]-=frame_cnt&0x01?0:8;
	}
      else if (laser_direction[i]==STATE_PLAYER_DOWN_SHOOTING || laser_direction[i]==STATE_PLAYER_DOWN || laser_direction[i]==STATE_PLAYER_DOWN_IDLE || laser_direction[i]==STATE_PLAYER_DOWN_IDLE_SHOOTING)
	{
	  if (BOX_WALL_DOWN(h) && laser_y[i]==PIXEL_BOX_Y(f))
	      player_laser_stop(i);
	  else
	      laser_y[i]+=frame_cnt&0x01?0:8;
	}
      else if (laser_direction[i]==STATE_PLAYER_UP_SHOOTING || laser_direction[i]==STATE_PLAYER_UP || laser_direction[i]==STATE_PLAYER_UP_IDLE || laser_direction[i]==STATE_PLAYER_UP_IDLE_SHOOTING)
	{
	  if (BOX_WALL_UP(h) && laser_y[i]==PIXEL_BOX_Y(f))
	      player_laser_stop(i);
	  else
	      laser_y[i]-=frame_cnt&0x01?0:8;
	}

      if (BOX_PIXEL_X(stamp_x[0])==BOX_PIXEL_X(laser_x[1]) && BOX_PIXEL_Y(stamp_y[0])==BOX_PIXEL_Y(laser_y[1]) && stamp_state[0]<STATE_PLAYER_RIGHT_SHOT)
	{
	  player_die(0);
	  player_laser_stop(i);
	}
      else if (BOX_PIXEL_X(stamp_x[1])==BOX_PIXEL_X(laser_x[0]) && BOX_PIXEL_Y(stamp_y[1])==BOX_PIXEL_Y(laser_y[0]) && stamp_state[1]<STATE_PLAYER_RIGHT_SHOT)
	{
	  player_die(1);
	  player_laser_stop(i);
	}
      
      if (stamp_state[i]==STATE_DYING && stamp_frame[i]==3)
	{
	  stamp_state[i]=STATE_DEAD;
	  stamp_frame[i]=0;
	  stamp_shooting[i]=0;
	}

            
    }

 no_move:
  return;
}

/**
 * player_shot()
 * Player has been shot by something.
 */
void player_shot(void)
{
  // Handle dying animation.
  if (stamp_state[i]!=STATE_DYING && player_shot_loop[i]>0 && stamp_frame[i]==3)
    {
      player_shot_loop[i]--;
    }
  else if (stamp_state[i]!=STATE_DYING && stamp_state[i]>STATE_PLAYER_DOWN_IDLE_SHOOTING && player_shot_loop[i]==0)
    {
      stamp_state[i]=STATE_DYING;
      stamp_frame[i]=0;
    }
}

/**
 * player_in_box()
 * Handle when player is in box.
 */
void player_in_box(void)
{
  if (stamp_timer[i]>0)
    {
      if (stamp_pad[i] != 0)
	{
	  stamp_timer[i]=0;
	}
      else
	{
	  stamp_y[i]=PIXEL_BOX_Y(6)-1; // 6 is the Y for the box.
	  if (sec==0) // 0 means approximately 1 second elapsed.
	    stamp_timer[i]--;         // Decrement timer
	}
    }
  else
    {
      stamp_y[i]=PIXEL_BOX_Y(5); // Pop out of box.
      if (i==0)
	{
	  stamp_state[i]=stamp_last_state[i]=STATE_PLAYER_LEFT_IDLE;
	  yellow_door_state=CLOSED;
	}
      else
	{
	  if (i==1 && blue_worrior_ai==0)
	    stamp_state[i]=stamp_last_state[i]=STATE_PLAYER_RIGHT_IDLE;
	  else
	    stamp_pad[1]=PAD_UP;
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

      if (blue_worrior_ai==1 && i==1)
	player_blue_move_ai();
      else
	stamp_pad[i]=pad_poll(i);
      
      player_trigger[i]=(PLAYER_PAD_A(i)?1:0);
      
      if (stamp_y[i]==PIXEL_BOX_Y(6)-1)
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
  laser_shooting[player]=1;
  laser_direction[player]=stamp_state[i];
  laser_x[player]=PIXEL_BOX_X(a);
  laser_y[player]=PIXEL_BOX_Y(b);

  switch(laser_direction[player])
    {
    case STATE_PLAYER_LEFT:
    case STATE_PLAYER_LEFT_IDLE:
    case STATE_PLAYER_LEFT_SHOOTING:
    case STATE_PLAYER_LEFT_IDLE_SHOOTING:
    case STATE_PLAYER_RIGHT:
    case STATE_PLAYER_RIGHT_IDLE:
    case STATE_PLAYER_RIGHT_SHOOTING:
    case STATE_PLAYER_RIGHT_IDLE_SHOOTING:
      laser_offset_x[i]=LASER_X_OFFSET_H;
      laser_offset_y[i]=LASER_Y_OFFSET_H;
      laser_type[player]=86;
      break;
    case STATE_PLAYER_DOWN:
    case STATE_PLAYER_DOWN_IDLE:
    case STATE_PLAYER_DOWN_SHOOTING:
    case STATE_PLAYER_DOWN_IDLE_SHOOTING:
    case STATE_PLAYER_UP:
    case STATE_PLAYER_UP_IDLE:
    case STATE_PLAYER_UP_SHOOTING:
    case STATE_PLAYER_UP_IDLE_SHOOTING:
      laser_offset_x[i]=LASER_X_OFFSET_V;
      laser_offset_y[i]=LASER_Y_OFFSET_V;
      laser_type[player]=93;
      break;
    }
}

/**
 * player_laser_stop()
 */
void player_laser_stop(unsigned char player)
{
  laser_x[player]=0xff;
  laser_y[player]=0xff;
  laser_type[player]=92;
  laser_shooting[player]=0;
  laser_direction[player]=0;
  laser_offset_x[player]=0;
  laser_offset_y[player]=0;
}

/**
 * player_change_ai_direction()
 * Change the direction of the blue player
 * TODO: if it isn't useful soon, remove it.
 */
void player_change_ai_direction()
{
  switch(rand8()&0x03)
    {
    case 0:
      stamp_pad[i]=PAD_RIGHT;
      break;
    case 1:
      stamp_pad[i]=PAD_LEFT;
      break;
    case 2:
      stamp_pad[i]=PAD_DOWN;
      break;
    case 3:
      stamp_pad[i]=PAD_UP;
      break;
    }
}

/**
 * Move blue worrior AI if needed.
 */
void player_blue_move_ai(void)
{
  pick_monster_rand:
  if (k==0) k=rand8()&0x07;

  // We don't want the blue worrior to chase the yellow player or himself.
  if (k<2)
    goto pick_monster_rand;
  else if (k>7)
    goto pick_monster_rand;

  /* if (stamp_state[k]==STATE_DEAD) */
  /*   goto pick_monster_rand; */
  
  // get enemy's target box
  e=BOX_PIXEL_X(stamp_x[k]);
  f=BOX_PIXEL_Y(stamp_y[k]);

  if (a==e && b>f)
    stamp_pad[i]=PAD_UP;
  else if (a<e && b>f)
    stamp_pad[i]=PAD_UP|PAD_RIGHT;
  else if (a<e && b==f)
    stamp_pad[i]=PAD_RIGHT;
  else if (a>e && b<f)
    stamp_pad[i]=PAD_DOWN|PAD_RIGHT;
  else if (a==e && b<f)
    stamp_pad[i]=PAD_DOWN;
  else if (a>e && b>f)
    stamp_pad[i]=PAD_DOWN|PAD_LEFT;
  else if (a>e && b==f)
    stamp_pad[i]=PAD_LEFT;
  else if (a>e&& b<f)
    stamp_pad[i]=PAD_UP|PAD_LEFT;  
  
}

/**
 * player_die(player)
 * Player was killed by player or monster, player=player shot.
 */
void player_die(unsigned char player)
{
  unsigned char new_state;
  memfill(&score0,1,sizeof(score0));
  
  switch(stamp_state[player])
    {
    case STATE_PLAYER_RIGHT:
    case STATE_PLAYER_RIGHT_SHOOTING:
      new_state=STATE_PLAYER_RIGHT_SHOT;
      break;
    case STATE_PLAYER_RIGHT_IDLE:
    case STATE_PLAYER_RIGHT_IDLE_SHOOTING:
      new_state=STATE_PLAYER_RIGHT_IDLE_SHOT;
      break;
    case STATE_PLAYER_LEFT:
    case STATE_PLAYER_LEFT_SHOOTING:
      new_state=STATE_PLAYER_LEFT_SHOT;
      break;
    case STATE_PLAYER_LEFT_IDLE:
    case STATE_PLAYER_LEFT_IDLE_SHOOTING:
      new_state=STATE_PLAYER_LEFT_IDLE_SHOT;
      break;
    case STATE_PLAYER_UP:
    case STATE_PLAYER_UP_SHOOTING:
      new_state=STATE_PLAYER_UP_SHOT;
      break;
    case STATE_PLAYER_UP_IDLE:
    case STATE_PLAYER_UP_IDLE_SHOOTING:
      new_state=STATE_PLAYER_UP_IDLE_SHOT;
      break;
    case STATE_PLAYER_DOWN:
    case STATE_PLAYER_DOWN_SHOOTING:
      new_state=STATE_PLAYER_DOWN_SHOT;
      break;
    case STATE_PLAYER_DOWN_IDLE:
    case STATE_PLAYER_DOWN_IDLE_SHOOTING:
      new_state=STATE_PLAYER_DOWN_IDLE_SHOT;
      break;
    }

  stamp_state[player]=new_state;
  stamp_frame[player]=0;
  player_shot_loop[player]=8;

  if (i<2) // Only deal with score if player shoots player.
    {
      score0[3]=2;  // 1000 points.
      add_points(i);
    }
  
  if (player==1 && blue_worrior_ai==1) 
    k=0; // Go tell AI to chase another player, if applicable.
}
