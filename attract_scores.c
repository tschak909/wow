#include "attract_scores.h"

extern void pal_fade_to(unsigned to);
extern void clear_update_buffer();
extern const unsigned char palette[16];
extern unsigned char spr;
#pragma zpsym("spr")
extern unsigned char i;
#pragma zpsym("i")
extern unsigned char frame_cnt;
#pragma zpsym("frame_cnt")

/**
 * attract_scores() - show scores
 */
void attract_scores(void)
{
  vram_adr(NAMETABLE_C);
  vram_fill(0,1024);

  pal_bright(0);

  // Dump scores into nametable A
  vram_adr(NAMETABLE_A);
  vram_unrle(wow_scores);
  pal_bg(palette);
  pal_spr(palette);
  ppu_on_all();
  ppu_wait_frame();
  bank_spr(1);
  bank_bg(0);
  pal_fade_to(4);

  while(1)
    {
      ppu_wait_frame();
      ++frame_cnt;
      if (frame_cnt==255) break;
    }

  pal_fade_to(0);
  clear_update_buffer();
  
}
