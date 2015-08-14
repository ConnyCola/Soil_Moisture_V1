#include <msp430G2452.h>
#include "defines.h"
#include "global.h"

void start_pulse(void)
  {
    P1DIR |= BIT2;                  // config P1.2 as TA0.1
    P1SEL |= BIT2;
  }

void stop_pulse(void)
  {
    P1DIR |= BIT2;                  // config P1.2 as TA0.1
    P1SEL &= ~BIT2;
    P1OUT &= ~BIT2;                 // pin low -> discharge
    __delay_cycles(120000);         // discharging
  }