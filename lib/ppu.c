#include <ppu.h>
#include <lcd.h>
#include <string.h>
#include <ppu_sm.h>

static ppu_context ctx;

ppu_context *ppu_get_context () {
    return &ctx;
}

void ppu_init() {
    ctx.current_frame = 0;
    ctx.line_ticks = 0;
    ctx.video_buffer = malloc(YRES*XRES * sizeof(u32));

    lcd_init();
    LCDS_MODE_SET(MODE_OAM);

    memset(ctx.oam_ram, 0, sizeof(ctx.oam_ram));
    memset(ctx.video_buffer, 0, YRES*XRES * sizeof(u32));
}

void ppu_tick() {
    ctx.line_ticks++;
    switch (LCDS_MODE) {
        case MODE_OAM: ppu_mode_oam(); break;
        case MODE_XFER: ppu_mode_xfer(); break;
        case MODE_VBLANK: ppu_mode_vblank(); break;
        case MODE_HBLANK: ppu_mode_hblank(); break;
    }
}

void ppu_oam_write (u16 addr, u8 val) {
    if (addr >= 0xFE00) addr -= 0xFE00;
    u8 *p = (u8 *)ctx.oam_ram;
    p[addr] = val;
}

u8 ppu_oam_read (u16 addr) {
    if (addr >= 0xFE00) addr -= 0xFE00;
    u8 *p = (u8 *)ctx.oam_ram;
    return p[addr];
}

void ppu_vram_write (u16 addr, u8 val) {
    ctx.vram[addr - 0x8000] = val;
}

u8 ppu_vram_read (u16 addr) {
    return ctx.vram[addr - 0x8000];
}
