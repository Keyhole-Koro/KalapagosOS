#include <stdio.h>
#include <stdint.h>

#include "main.hpp" // just for debugging
#include "./console/console.hpp"
Console *console;

void interrupt_handler();

struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));

struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define IDT_ENTRIES 256

struct idt_entry idt[IDT_ENTRIES];

struct idtr idtr;

void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

void setup_timer_interrupt() {
    // Calculate divisor for 100Hz
    uint16_t divisor = 1193180 / 100;

    // Send the command byte to the control port (0x43)
    outb(0x43, 0x36); // 0x36 sets mode 3, square wave generator, and binary counter

    // Split the divisor into low and high bytes
    uint8_t lo = (uint8_t)(divisor & 0xFF);
    uint8_t hi = (uint8_t)((divisor >> 8) & 0xFF);

    // Send the divisor bytes to channel 0 (0x40)
    outb(0x40, lo);
    outb(0x40, hi);
}

void init_idt_entry(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void setup_idt() {
    uint64_t handler_addr = (uint64_t)interrupt_handler;

    init_idt_entry(32, handler_addr, 0x08, 0x8E); // Timer interrupt entry (interrupt number 32)

    idtr.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
    idtr.base = (uint64_t)&idt;

    __asm__ __volatile__("lidt %0" : : "m"(idtr));
}

void interrupt_handler() {
    console->Show("interrupted\n");
}
