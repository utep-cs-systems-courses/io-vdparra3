
//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int blinkLimit  = 5;  // duty cycle = 1/blinkLimit
int blinkCount  = 0;  // cycles 0...blinkLimit-1
int secondCount = 0; // state var representing repeating time 0…1s

int greenLimit  = 0;
int redLimit    = 0;
void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking 
  /*blinkCount ++;
   if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
    P1OUT |= LED_RED;
  } else{		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
    //when green reaches limit -> STOP
    // RED starts blinking
   
  }*/
  greenLimit++;
   if(greenLimit >= blinkLimit){
     // greenLimit = 0;
     P1OUT |= LED_GREEN;
   } else{
     P1OUT &= ~LED_GREEN;
   }
   if(greenLimit == 3){
     P1OUT &= ~LED_GREEN;

   }
  
  // 1 sec red 1 sec green
  /* if(blinkCount >= blinkLimit){
    blinkCount = 0;
    P1OUT |= LED_GREEN;
    P1OUT |= LED_RED;
    //enters once a sec has been reached
    if(blinkCount >= blinkLimit){
      blinkCount = 0;
      P1OUT &= ~LED_RED;
    }
    }*/
  // measure a second
  secondCount ++;
  if (secondCount >= 250) {  // once each second
    secondCount = 0;
    blinkLimit ++;            // reduce duty cycle
    //  P1OUT ^= LED_GREEN;
    // P1OUT ^= LED_RED;
    if (blinkLimit >= 8)     // but don't let duty cycle go below 1/7.
      blinkLimit = 0;
  }
} 

