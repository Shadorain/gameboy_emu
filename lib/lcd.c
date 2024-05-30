#include <lcd.h>
#include <ppu.h>
#include <dma.h>

static lcd_context ctx;

static unsigned long colors_default[4] = { 0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000 };

void lcd_init () {
    ctx.lcdc = 0x91;
    ctx.scroll_x = 0;
    ctx.scroll_y = 0;
    ctx.ly = 0;
    ctx.ly_compare = 0;
    ctx.bg_pallate = 0xFC;
    ctx.obj_pallate[0] = 0xFF;
    ctx.obj_pallate[1] = 0xFF;
    ctx.win_x = 0;
    ctx.win_y = 0;

    for (int i = 0; i < 4; i++) {
        ctx.bg_colors[i] = colors_default[i];
        ctx.sp1_colors[i] = colors_default[i];
        ctx.sp2_colors[i] = colors_default[i];
    }
}

lcd_context *lcd_get_context () {
    return &ctx;
}

u8 ldc_read (u16 addr) {
    u8 offset = (addr - 0xFF40);
    u8 *p = (u8 *)&ctx; 
    return p[offset];
}

void update_pallate (u8 pallate_data, u8 pal) {
    u8 *p_colors = ctx.bg_colors;
    switch (pal) {
        case 1: p_colors = ctx.sp1_colors; break;
        case 2: p_colors = ctx.sp2_colors; break;
    }

    p_colors[0] = colors_default[pallate_data & 0b11];
    p_colors[1] = colors_default[(pallate_data >> 2) & 0b11];
    p_colors[2] = colors_default[(pallate_data >> 4) & 0b11];
    p_colors[3] = colors_default[(pallate_data >> 6) & 0b11];
}

void lcd_write (u16 addr, u8 val) {
    u8 offset = (addr - 0xFF40);
    u8 *p = (u8 *)&ctx;
    p[offset] = val;

    if (offset == 6)
        dma_start(val);

    if (addr == 0xFF47)
        update_pallate(val, 0);
    else if (addr == 0xFF48)
        update_pallate(val & 0b11111100, 1);
    else if (addr == 0xFF49)
        update_pallate(val & 0b11111100, 2);
}
