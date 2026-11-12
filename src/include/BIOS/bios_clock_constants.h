/**
 * @author      Jeremy Simon Thornton
 * @copyright   2024 Jeremy Simon Thornton
 *
 * The IBM PC timer (8253/8254 PIT) runs at 1.193180 MHz.
 * Channel 0 divides this by 65536 to generate IRQ 0 (INT 08h):
 * clock updates at 1193180/65536 = 18.20649803161621... Hz ticks per second.
 * counts per second ? 18
 * counts per minute ? 1092
 * counts per hour   ? 65543
 * counts per day    ? 1573040
 */
#ifndef BIOS_CLOCK_CONSTANTS_H
#define BIOS_CLOCK_CONSTANTS_H

#define BIOS_CLOCK_SERVICES			    1Ah
#define BIOS_READ_SYSTEM_CLOCK_COUNTER	0
#define BIOS_SET_SYSTEM_CLOCK_COUNTER	1

#define BIOS_PIT_FREQUENCY              1.193180 // MHz
// Tick Period    = 65536 / 1193180 = 0.054925471... seconds (~54.925 ms)
#define BIOS_CLOCK_PERIOD               0.054925493219799
// Tick Frequency = 1193180 / 65536 = 18.20649803161621... Hz
#define BIOS_TICKS_PER_SECOND			18.20649803161621
#define BIOS_TICKS_PER_24HR				1800B0h

#endif
