//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;           // SET LEDS TO 0100 0001
  P1OUT &= ~LED_GREEN;     // Invert Green BITS and & arithmetic
  P1OUT |= LED_RED;        // Turn on Red LED
  or_sr(0x18);		/* CPU off, GIE on */
}
