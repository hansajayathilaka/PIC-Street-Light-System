#ifndef ANALOG_HEADER
#define	ANALOG_HEADER

#include <xc.h>

#define SBIT_ADON     0
#define SBIT_CHS0     3
#define SBIT_ADFM     7

void delay(int cnt)
{
    while(cnt--);
}

void ADC_Init()
 {
//   ADCON0=0x00;  // sampling freq=osc_freq/2,ADC off initially
//   ADCON1=(1<<SBIT_ADFM);  // All pins are configured as Analog pins and ADC result is right justified  
    ADCON0 = 0x41;  // Turn ADC ON, Select AN0 Channel, ADC Clock = Fosc/8
    ADCON1 = 0x80;  // All 8 Channels Are Analog, Result is "Right-Justified"
                    // ADC Clock = Fosc/8
}


//int ADC_Read(int adcChannel)
// {  
//    ADCON0 = (1<<SBIT_ADON) | (adcChannel<SBIT_CHS0);  //select required channel and turn ON adc
//
//    delay(1000);                   //Acquisition Time(Wait for Charge Hold Capacitor to get charged )
//   
//    GO=1;                           // Start ADC conversion
//    while(GO_DONE==1);              // Wait for the conversion to complete
//                                    // GO_DONE bit will be cleared once conversion is complete
//
//    return((ADRESH<<8) + ADRESL);   // return right justified 10-bit result
// }

int ADC_Read(int ANC)
{
    if(ANC<0 || ANC>7)    // Check Channel Number Validity
    { return 0;}
    ADCON0 &= 0b11000101; // Clear The Channel Selection Bits
    ADCON0 |= ANC<<3;     // Select The Required Channel (ANC)
                          // Wait The Aquisition Time
    __delay_us(30);       // The Minimum Tacq = 20us, So That should be enough
    GO_DONE = 1;          // Start A/D Conversion
    while(ADCON0bits.GO_DONE); // Polling GO_DONE Bit
                               // Provides Delay Until Conversion Is Complete
    return ((ADRESH << 8) + ADRESL); // Return The Right-Justified 10-Bit Result
}

//uint16_t ADC_Read(uint8_t ANC)
//{
//    if(ANC<0 || ANC>7)    // Check Channel Number Validity
//    { return 0;}
//    ADCON0 &= 0b11000101; // Clear The Channel Selection Bits
//    ADCON0 |= ANC<<3;     // Select The Required Channel (ANC)
//                          // Wait The Aquisition Time
//    __delay_us(30);       // The Minimum Tacq = 20us, So That should be enough
//    GO_DONE = 1;          // Start A/D Conversion
//    while(ADCON0bits.GO_DONE); // Polling GO_DONE Bit
//                               // Provides Delay Until Conversion Is Complete
//    return ((ADRESH << 8) + ADRESL); // Return The Right-Justified 10-Bit Result
//}

#endif
