//___PORT DEFINITIONS___                                            /* S_PORTDEF */
// calibration switch
#define CAL_SW BIT5
// SPI chip-select ports
#define CS1 BIT7
#define CS2 BIT7
#define CS3 BIT6
// user interface LEDs
#define LED_YE BIT4
#define LED_GR BIT3
// test signal on port 2.2 / pin10
#define TEST_TRIGGER BIT2
                                                                    /* E_PORTDEF */
//___DEVICE SETTINGS___                                              /* S_DEVSET */

// TEMPERATURE RANGE
#define TEMP_MIN -10            // min. measured temperature
#define TEMP_MAX 50             // max. measured temperature

// TEMPERATURE OUTPUT SETTINGS 
#define V_REF 4.096             // DAC reference voltage
#define V_MAX 2.5               // max DAC output voltage

// PULSE SETTINGS
#define PULSE_PERIOD 21  //21       // length of pulse period
#define PULSE_WIDTH  10         // width of pulse

// DAC DEVICE IDs
#define DAC_VREF_H 0x00         // DAC ID for Vref+
#define DAC_VREF_L 0x01         // DAC ID for Vref-
#define DAC_OUT_MOIS 0x02       // DAC ID for moisture output
#define DAC_OUT_TEMP 0x03       // DAC ID for temperature output

// FLASH DESTINATION
#define FLASH_VREF_L 0x1040     // address of Vref- data
#define FLASH_VREF_H 0x1045     // address of Vref+ data
#define FLASH_VCC    0x1050     // address of absolute Vcc

// ADC DEVICE IDs
#define ADC_TEMP 0x0           // temperature measurement settings
#define ADC_MOIS 0x1           // moisture measurement settings
#define ADC_VCC  0x2           // supply voltage measurement settings
                                                                     /* E_DEVSET */

//temperature
// #define CAL_ADC_15T30 *(unsigned int *) (0x10E2)
// #define CAL_ADC_15T85 *(unsigned int *) (0x10E4)