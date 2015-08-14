#include "init.h"
#include <msp430G2452.h>
#include "defines.h"
#include "global.h"
#include "spi.h"
#include "flash.h"
#include "data_proc.h"

//---------------------------------------INITIALIZATIONS---------------------------

//SYSTEM INITIALIZATION
void init_system(void)
  {
    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer

    ptr_vref_h = &vref_h;
    ptr_vref_l = &vref_l;
    ptr_vref_vcc = &vref_vcc;
    
    init_clk();                         // init. internal clocks
    init_pulse();                       // init. pulse for cap_meas
    init_ADC();                         // init. ADC10
    init_spi();                         // init. SPI module
    init_led();                         // init. LED
    init_switch();                      // init. switch for calibration
    init_flash();                       // init. flash for write operation
    load_cal();                         // load calibration data
    __delay_cycles(128);
  }

//CLOCK INITIALIZATION
void init_clk(void)
  {
    BCSCTL1 = CALBC1_8MHZ;		//config internal clocks DCO => 100kHz
    DCOCTL = CALDCO_8MHZ;
  }

//FLASH INITIALIZATION
void init_flash(void)
  {
    while(FCTL3 & BUSY){};               // wait till timing gen is ready
    FCTL2 = FWKEY + FSSEL_2 + FN0 + FN1 + FN2 + FN4; // Clk = SMCLK/24 => 333kHz
  }

//PULSE INITIALIZATION
void init_pulse(void)
  {
    P1DIR |= BIT2;                  // config P1.2 as TA0.1
    P1SEL |= BIT2;

    TA0CCR0 = PULSE_PERIOD;         // PULSE Period
    TA0CCR1 = PULSE_WIDTH;
    TACCTL1 = OUTMOD_7;             // Toggle Mode
    TA0CTL = TASSEL_2 + MC_1;       // SMCLK, up mode
    TA0CTL &= ~TAIE;
  }

//ADC10 INITIALIZATION
void init_ADC(void)
  {
    ADC10CTL0 &= ~ADC10IE; // disable interrupts on ADC10
    ADC10AE0 = BIT0 + BIT1; // activate analog input config
  }

//SWITCH INITIALIZATION
void init_switch()
  {
    P2DIR &= ~CAL_SW;                     // P1.0 = input
    P2REN |= CAL_SW;                      // Pullup/down resistor enabled
    P2OUT |= CAL_SW;                      // Pin is pulled enabled
    P2IES |= CAL_SW;                      // rising edge
    P2IE |= CAL_SW;                       // interrupt enable
    P2IFG &= ~CAL_SW;                     // clear interrupt flag
  }

//LED INITIALIZATION
void init_led(void)
  {
    P2DIR |= LED_GR + LED_YE;             // conifg LED output pins
    P2OUT &= ~LED_GR + ~LED_YE;           // turn off LEDs
  }

//SPI INITIALIZATION
void init_spi(void)
  {
    P1DIR |= CS1;                      // P1.7 = output (CS1)
    P1SEL &= ~CS1;
    P1OUT |= CS1;                      // P1.7 hi
    P2DIR |= CS2;                      // P2.7 = output (CS2)
    P2SEL &= ~CS2;
    P2OUT |= CS2;                      // P2.7 hi

    // Setup USI -> SPI Master
    USICTL0 &= ~USISWRST;                          // USI released for operation
    USICTL0 |= USIPE6 + USIPE5 + USIMST + USIOE;   // Port, SPI master
    USICTL0 &= ~USIPE7;
    USICTL1 &= ~USIIFG + ~USIIE;                   // clear IRQ flag, turn off interrupt
    USICTL1 |= USICKPH;                            // Data is captured on the first SCLK edge and changed on the following edge
    USICNT = USI16B;                               // set Buffer to 16 Bit and preload counter to 16 Bit
    USICKCTL = USIDIV_4 + USISSEL_2;               // /16 SMCLK
    USICTL1 &= ~USIIFG;                            // clear IRQ flag  
  }

//LOAD CALIBRATION DATA
void load_cal(void)
  {
    unsigned char spi_volt_data;
    unsigned char *ptr_spi_volt_data;
    ptr_spi_volt_data = &spi_volt_data;
        
    vref_l = read_flash_float(FLASH_VREF_L);         // load calibration
    *ptr_spi_volt_data = conv_dac(vref_l);           // assign Vref-
    spi_send(DAC_VREF_L, *ptr_spi_volt_data);
    
    vref_h = read_flash_float(FLASH_VREF_H);         // load calibration
    *ptr_spi_volt_data = conv_dac(vref_h);           // assign Vref-
    spi_send(DAC_VREF_H, *ptr_spi_volt_data);
    
    vref_vcc = read_flash_float(FLASH_VCC);          // load calibration
  }
