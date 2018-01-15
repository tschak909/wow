#include "attract_monsters.h"

extern void pal_fade_to(unsigned to);

extern const unsigned char metasprite_data[];
extern const unsigned char* const metasprite_list[];
extern const unsigned char palette[16];

extern unsigned char spr;
#pragma zpsym("spr")
extern unsigned char i;
#pragma zpsym("i")
extern unsigned char frame_cnt;
#pragma zpsym("frame_cnt")

/**
 * attract_monsters() - shown while game isn't playing
 */
void attract_monsters(void)
{
  // Clear nametable C
  vram_adr(NAMETABLE_C);
  vram_fill(0,1024);

  pal_bright(0);
  
  // Dump monster screen into nametable A
  vram_adr(NAMETABLE_A);
  vram_unrle(wow_monsters);
  pal_bg(palette);
  pal_spr(palette);
  ppu_on_all();
  ppu_wait_frame();
  bank_spr(1);
  bank_bg(0);

  spr=OAM_OFFSET_TOP;
  spr = oam_meta_spr(120,8,spr,metasprite_list[21]);
  spr = oam_meta_spr(120,36,spr,metasprite_list[33]);
  spr = oam_meta_spr(120,68,spr,metasprite_list[45]);
  spr = oam_meta_spr(120,98,spr,metasprite_list[67]);
  spr = oam_meta_spr(120,132,spr,metasprite_list[5]);
  spr = oam_meta_spr(120,164,spr,metasprite_list[58]);
  spr = oam_meta_spr(120,204,spr,metasprite_list[83]);
  
  pal_fade_to(4);

  i=0;
  
  while(1)
    {
      ppu_wait_frame();
      ++frame_cnt;
      if (frame_cnt==255) break;
    }

  pal_fade_to(0);
  oam_clear();
  
}
