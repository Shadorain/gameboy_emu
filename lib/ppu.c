#include <ppu.h>

static ppu_context ctx;

void ppu_init() {

}

void ppu_tick() {

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
