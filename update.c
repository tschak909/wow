#include "update.h"
#include "constants.h"
#include "macros.h"
#include "neslib.h"

extern unsigned char spr;
#pragma zpsym("spr")
extern unsigned char i;
#pragma zpsym("i")
extern unsigned char teleport_state;
#pragma zpsym("teleport_state")
extern unsigned char teleport_timer;
#pragma zpsym("teleport_timer")
extern unsigned char sec;
#pragma zpsym("sec")
extern unsigned char blue_door_state;
#pragma zpsym("blue_door_state")
extern unsigned char yellow_door_state;
#pragma zpsym("yellow_door_state")
extern unsigned char a;
#pragma zpsym("a")
extern unsigned char b;
#pragma zpsym("b")
extern unsigned char c;
#pragma zpsym("c")
extern unsigned char frame_cnt;
#pragma zpsym("frame_cnt");

extern const unsigned char* metasprite_list[];
extern unsigned char score0[7];
extern unsigned char score1[7];
extern unsigned char score2[7];
extern unsigned char update_buffer[80];
extern const unsigned char metasprite_animation_data[];
extern unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];
extern unsigned char lasers[LASER_NUM_FIELDS*LASER_NUM_SLOTS];

extern unsigned char stamp_type_to_radar(unsigned char t);
extern void clear_update_buffer(void);
extern unsigned char is_stamp_visible(void);

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
 * update_stamps() - Update the on-screen stamps
 */
void update_stamps(void)
{
  spr=OAM_OFFSET_TOP;
  oam_clear();
  for (i=0;i<STAMP_NUM_SLOTS;i++)
    {
      if (stamps[STAMP_X(i)] == 0)
	  continue;
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
 * update_lasers() - Update the on-screen lasers
 */
void update_lasers(void)
{
  spr=OAM_OFFSET_LASERS;
  for (i=0;i<LASER_NUM_SLOTS;i++)
    {
      spr = oam_spr(lasers[LASER_X(i)]+lasers[LASER_OFFSET_X(i)],lasers[LASER_Y(i)]+lasers[LASER_OFFSET_Y(i)],lasers[LASER_TYPE(i)],(frame_cnt&0x01?0x00:0x40),spr);	  
    }
}
