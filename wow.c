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
      attract_scores();
      attract_monsters();
      dungeon_run(1);
    }
}
