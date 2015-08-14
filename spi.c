#include <msp430G2452.h>
#include "defines.h"
#include "global.h"

//___SPI DATA TRANSMISSION___
void spi_send(unsigned char device, unsigned char data)
  {
    int *ptr_message;                           // reset all message bits
    int message = 0;
    ptr_message = &message;
    unsigned char *ptr_data;
    ptr_data = &data;
                                                                  /* S_SPI_SWITCH */
    switch(device)                                                
      {
        case DAC_VREF_H:    P1OUT &= ~CS1;            // select DAC1, CS1 lo
                            P2OUT |= CS2;
                            break;
        case DAC_VREF_L:    P1OUT &= ~CS1;            // select DAC1, CS1 lo
                            P2OUT |= CS2;
                            *ptr_message |=(1<<15);   // DAC module B
                            break;
        case DAC_OUT_MOIS:  P1OUT |= CS1;             // select DAC2, CS2 lo
                            P2OUT &= ~CS2;
                            *ptr_message |=(1 << 13); // DAC gain 1x (2.048V)
                            break;
        case DAC_OUT_TEMP:  P1OUT |= CS1;             // select DAC2, CS2 lo
                            P2OUT &= ~CS2;
                            *ptr_message |=(1<<15);   // DAC module B
                            *ptr_message |=(1 << 13); // DAC gain 1x (2.048V)
                            break;
        default:            break;
      }                                                         /* E_SPI_SWITCH */
                                                                 /* S_SPI_MOUNT */
    *ptr_message |=(1 << 12);               // activate DAC
    *ptr_message |=(*ptr_data << 4);        // add voltage level information
    USISR = *ptr_message;                   // write data to send into fifo
    USICNT |= 16;                           // reload counter
    while (!(USICTL1 & USIIFG)){};          // wait for transmission end
    P1OUT |= CS1;                           // CSs hi
    P2OUT |= CS2;                                                /* E_SPI_MOUNT */
  }