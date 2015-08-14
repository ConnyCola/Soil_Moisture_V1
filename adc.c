#include "adc.h"
#include <msp430G2452.h>
#include "defines.h"
#include "global.h"

//READ ADC                                                    
int read_ADC(unsigned char adc_mode)
  {
    int adc_value;
    int *ptr_adc_value;
    ptr_adc_value = &adc_value;
    
    ADC10CTL0 &= ~ENC;                   /* S_SETADC */
    switch(adc_mode)
      {
        case ADC_TEMP:  ADC10CTL0 = REFON + SREF_1 + ADC10SHT_3 + ADC10ON;
                        ADC10CTL1 = INCH_10 + ADC10DIV_3; 
                        __delay_cycles (128);             // let Vref settle
                        break;
        case ADC_MOIS:  ADC10CTL0 = SREF_6 + ADC10SHT_0 + ADC10ON;
                        ADC10CTL1 = INCH_1 + ADC10SSEL_3 + ADC10DIV_4;
                        ADC10AE0 = BIT1;
                        __delay_cycles (128);             // let Vref settle
                        break;
        case ADC_VCC:   ADC10CTL0 = REFON + SREF_1 + ADC10SHT_3 + ADC10ON;
                        ADC10CTL1 = INCH_0 + ADC10DIV_3;   
                        ADC10AE0 = BIT0;
                        __delay_cycles (128);             // let Vref settle
      default:        break;
      }                                                              /* E_SETADC */
                                                                     /* S_READADC */
    while(TA0R != 14){};                // trigger ADC @\label{ln:adc_trigger}@
    ADC10CTL0 |= ENC + ADC10SC;         // start sampling and conversion @\label{ln:adc_conv_start}@
    while (ADC10CTL1 & ADC10BUSY){};    // wait for conversion completion @\label{ln:adc_conv_end}@
    *ptr_adc_value = ADC10MEM;          // refresh ADC value
    ADC10CTL0 &= ~ENC;                  // disable ADC
    
    return *ptr_adc_value;                                           /* E_READADC */
  }
                                                                     