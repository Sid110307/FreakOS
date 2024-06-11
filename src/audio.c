#include "include/audio.h"

void playSound(uint32_t frequency, uint32_t duration)
{
    uint32_t divisor = CLOCK_RATE / frequency;
    outPort(0x43, 0xB6);
    outPort(0x42, divisor & 0xFF);
    outPort(0x42, divisor >> 8);

    delay(duration);
    outPort(0x61, inPort(0x61) & 0xFC);
}
