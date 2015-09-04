/*
 * Original Michael Oberacher Code for Soil_moisture Sensor SMS50-v1
 * - flash fixup
 */

#include <msp430G2452.h>
#include "defines.h"
#include "init.h"
#include "global.h"
#include "flash.h"
#include "spi.h"
#include "adc.h"
#include "data_proc.h"
#include "pulse.h"
#include "user_interf.h"
#include "measure.h"

//VARIABLES

volatile int temperature;			// temperature for compensation
volatile int *ptr_temperature;

volatile int temp_raw;				// temperature for compensation
volatile int *ptr_temp_raw;

volatile char moisture;          	// relative moisture
volatile char *ptr_mois_perc;

volatile char spi_data;				// converted data for SPI message
volatile char *ptr_spi_data;

unsigned int meas_mois_raw;
unsigned int *ptr_mois_raw;

float test_mois_volt;				//test variable

//PROGRAMMCODE

void main(void)
  {
    ptr_temp_raw = &temp_raw;		// pointer allocations
    ptr_temperature = &temperature;  
    
    ptr_mois_raw = &meas_mois_raw;
    
    ptr_mois_perc = &moisture;
    
    ptr_spi_data = &spi_data;
    
    init_system();					// init. system
    __delay_cycles(128);
        
    _EINT();						// enable general interrupts
    
    while(1)						// continous program cycle
      { 
        
        //-------------TEMPERATURE-----------
        *ptr_temp_raw = read_ADC(ADC_TEMP);
        *ptr_temperature = conv_temp(*ptr_temp_raw);

        //send to output
        _DINT();
        spi_send(DAC_OUT_TEMP, *ptr_temperature);
        _EINT();


        //-------------MOISTURE--------------
<<<<<<< Updated upstream
        *ptr_meas_mois = meas_moisture();
        test_mois_volt = *ptr_meas_mois * ((*ptr_vref_h - *ptr_vref_l)/1024) + *ptr_vref_l;
        *ptr_moisture = conv_mois(*ptr_meas_mois);
        *ptr_moisture = conv_mois_dac(*ptr_moisture);
=======
        *ptr_mois_raw = meas_moisture();
        test_mois_volt = *ptr_mois_raw * ((*ptr_vref_h - *ptr_vref_l)/1024) + *ptr_vref_l;
        *ptr_mois_perc = conv_mois(*ptr_mois_raw);
        *ptr_mois_perc = conv_mois_dac(*ptr_mois_perc);
>>>>>>> Stashed changes

        //send to output
        _DINT();
        spi_send(DAC_OUT_MOIS, *ptr_mois_perc);
        _EINT();
      };
  }


//---------------------------------------INTERRUPTS-----------------------------------------------------------

// CALIBRATION INTERRUPT FROM SWITCH
// Port 1 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
  {
        unsigned int adc_value;
        unsigned int  *ptr_adc_value;
        ptr_adc_value = &adc_value;
        
        _DINT();                                   // disable interrupt
                     
        *ptr_adc_value = read_ADC(ADC_VCC);        // measure supply voltage
        
        *ptr_vref_vcc = conv_vcc(*ptr_adc_value);  // convert to absolute voltage and save
        
        *ptr_spi_data = 0;                         // set VREF- to GND
        spi_send(DAC_VREF_L, *ptr_spi_data);
        *ptr_spi_data = 255;                       // set Vref+ to Vcc
        spi_send(DAC_VREF_H, *ptr_spi_data);
        
        // meas moisture with maximum delta_Volt DRY
        blink_led_poll_sw(LED_YE);
<<<<<<< Updated upstream
        *ptr_meas_mois = meas_moisture();
        *ptr_vref_h = (*ptr_meas_mois) * (*ptr_vref_vcc / 1024.0);// save high reference (absolute)
=======
        *ptr_mois_raw = meas_moisture();
        *ptr_vref_h = (*ptr_mois_raw) * (*ptr_vref_vcc / 1024.0);		// save high reference (absolute)
>>>>>>> Stashed changes
        
        confirm_led(LED_YE);
        
        // meas moisture with maximum delta_Volt MOIST
        blink_led_poll_sw(LED_GR);
<<<<<<< Updated upstream
        *ptr_meas_mois = meas_moisture();
        *ptr_vref_l = (*ptr_meas_mois) * (*ptr_vref_vcc / 1024.0);// save high reference (absolute)
        
        erase_flash(FLASH_VREF_L);
        
        write_flash_float(*ptr_vref_l, *ptr_vref_h, *ptr_vref_vcc); // write config values to info flash
=======
        *ptr_mois_raw = meas_moisture();
        *ptr_vref_l = (*ptr_mois_raw) * (*ptr_vref_vcc / 1024.0);		// save high reference (absolute)
        
        erase_flash(FLASH_VREF_L);
        
        write_flash_float(*ptr_vref_l, *ptr_vref_h, *ptr_vref_vcc); 	// write config values to info flash
>>>>>>> Stashed changes

        confirm_led(LED_GR);                
        
        // set references for ADC10
        *ptr_spi_data = conv_dac(*ptr_vref_l);
        spi_send(DAC_VREF_L, *ptr_spi_data);
        *ptr_spi_data = conv_dac(*ptr_vref_h);
        spi_send(DAC_VREF_H, *ptr_spi_data);
        
        P2IFG &= ~CAL_SW;                     // clear interrupt flag
        _EINT();                              // enable interrupt
  }
