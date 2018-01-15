#include "utils.h"
#include "constants.h"
#include "neslib.h"

extern unsigned char stamps[STAMP_NUM_FIELDS*STAMP_NUM_SLOTS];
extern unsigned char update_buffer[80];

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
