#include <msp430G2452.h>
#include "defines.h"
#include "pulse.h"
#include "adc.h"

unsigned int meas_moisture(void)
  {
    unsigned int mois_raw;
    unsigned int *ptr_mois_raw; 
    ptr_mois_raw = &mois_raw;
    
    start_pulse();
     __delay_cycles(40000);   // let measure voltage settle
     *ptr_mois_raw = 0;
     int j=0;
     for (j=0; j<30; j++)    // averaged moisture value
       {
         *ptr_mois_raw = *ptr_mois_raw + read_ADC(ADC_MOIS);
       }
       *ptr_mois_raw = *ptr_mois_raw / 30;
       stop_pulse();
       return *ptr_mois_raw;
  }
