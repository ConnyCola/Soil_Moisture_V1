#ifndef GLOBAL_H
#define GLOBAL_H

extern volatile float vref_h;       // Vref+ for ADC10 (calibrated sensor)
extern volatile float *ptr_vref_h;

extern volatile float vref_l;       // Vref- for ADC10 (calibrated sensor)
extern volatile float *ptr_vref_l;

extern volatile float vref_vcc;     // VCC at Vref
extern volatile float *ptr_vref_vcc;

#endif