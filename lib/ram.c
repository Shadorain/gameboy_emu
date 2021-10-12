#include <ram.h>
#include <stdio.h>

typedef struct {
    u8 wram[0x2000];
    u8 hram[0x80];
} ram_context;

static ram_context ctx;

u8 wram_read (u16 addr) {
    addr -= 0xC000;
    if (addr >= 0x2000) {
        printf("INVALID WRAM ADDR: %08X\n", addr+0xC000);
        exit(-1);
    }
    return ctx.wram[addr];
}

void wram_write (u16 addr, u8 val) {
    addr -= 0xC000;
    ctx.wram[addr] = val;
}

u8 hram_read (u16 addr) {
    addr -= 0xFF80;
    return ctx.hram[addr];
}

void hram_write (u16 addr, u8 val) {
    addr -= 0xFF80;
    ctx.hram[addr] = val;
}
