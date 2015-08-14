#include "global.h"

//___GLOBAL VARIABLES___
volatile float vref_h;      // Vref+ for ADC10 (calibrated sensor)
volatile float *ptr_vref_h;
    
volatile float vref_l;       // Vref- for ADC10 (calibrated sensor)
volatile float *ptr_vref_l;

volatile float vref_vcc;          // VCC at Vref
volatile float *ptr_vref_vcc;
