#include <dma.h>
#include <io.h>
#include <lcd.h>
#include <stdio.h>
#include <timer.h>
#include <cpu.h>

static char serial_data[2];

u8 io_read (u16 addr) {
    if (addr == 0xFF01) return serial_data[0];
    if (addr == 0xFF02) return serial_data[1];
    if (BETWEEN(addr, 0xFF04, 0xFF07))
        return timer_read(addr);
    if (addr == 0xFF0F)
        return cpu_get_int_flags();
    if (BETWEEN(addr, 0xFF40, 0xFF4B))
        return lcd_read(addr);
    printf("UNSUPPORTED bus_write(%04X)\n", addr);
    return 0;
}

void io_write (u16 addr, u8 val) {
    if (addr == 0xFF01) {
        serial_data[0] = val;
        return;
    }
    if (addr == 0xFF02) {
        serial_data[1] = val;
        return;
    }
    if (BETWEEN(addr, 0xFF04, 0xFF07)) {
        timer_write(addr, val);
        return;
    } if (addr == 0xFF0F) {
        cpu_set_int_flags(val);
        return;
    }
    if (BETWEEN(addr, 0xFF40, 0xFF4B)) {
        timer_write(addr, val);
        return;
    }

    printf("UNSUPPORTED: bus_write(%04X)\n", addr);
}
