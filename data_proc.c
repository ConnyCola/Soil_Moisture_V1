#include "global.h"
//---------------------------------------DATA CONVERSIONS--------------------------

//___TEMPERATURE VALUE CONVERSION___                                /* S_TEMPCON */
unsigned char conv_temp(unsigned int adc_value)
  {
    unsigned char temperature = (unsigned char)(adc_value * 1.70620438 - 1113.062693);
    return temperature;
  }
                                                                    /* E_TEMPCON */
//___SUPPLY VOLTAGE VALUE CONVERSION___
float conv_vcc(unsigned int adc_value)
  {
    float vcc = adc_value * 0.00366211;  //convert to absolute voltage
    return vcc;
  }

//___MOISTURE VALUE CONVERSION___
unsigned char conv_mois(unsigned int adc_value)
  {
    unsigned char moisture = (char)(100 - (0.09765625 * (adc_value)));
    return moisture;
  }

//___MOISTURE TO DAC CONVERSION___
unsigned char conv_mois_dac(unsigned char moisture_percent)
  {
    unsigned char converted_moisture = (char)(moisture_percent * 2.55);
    return converted_moisture;
  }

//___VALUE TO DAC CONVERSION___
unsigned char conv_dac(float voltage)
  {
    unsigned char spi_dac = (char)(voltage * 62.5);
    return spi_dac;
  }
