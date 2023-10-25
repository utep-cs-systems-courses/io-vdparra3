//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN; //0000 0000
  P1OUT |= LED_RED;    //0100 0000

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state var to count time
int secondCount = 0;
int led_on = 0;
void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount ++;
  if (secondCount >= 250) { 	/* once each sec... */
    secondCount = 0;            /* reset count */
    P1OUT ^= LED_GREEN; //
    P1OUT ^= LED_RED;
    /*     led_on = !led_on;
    if(led_on)
      P1OUT ^= LED_GREEN;		/* toggle green LED */
    /* else
    P1OUT &= LED_RED;
    */
  }
} 

