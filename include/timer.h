#pragma once

#include <common.h>

typedef struct {
    u16 div;
    u8 tima;
    u8 tma;
    u8 tac;
} timer_context;

void timer_init ();
void timer_tick ();

u8 timer_read (u16 addr);
void timer_write (u16 addr, u8 val);

timer_context *timer_get_context ();
