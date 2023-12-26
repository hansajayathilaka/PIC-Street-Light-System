/*
 * File:   main.c
 * Author: hansa
 *
 * Created on 26 December 2023, 19:07
 */


#include "main_config.h"
#include "lcd.h"
#include "analog.h"
#include <xc.h>

#define S_COUNT 8
#define LED_VARIANT 1

typedef struct _Pin {
    volatile unsigned char *port;
    int pin;
} Pin;

void main(void) {
    unsigned int a;
    
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Welcome to Light");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Powered by SLTC");
    
    ADC_Init();
    
    TRISA = 0xff; // Mark as input pin
    TRISB = 0x00; // Mark as output pin
    TRISC0 = 0; // Mark as output pin
    
    PORTB = 0x00;
    RC0 = 0;
    
    Pin s[S_COUNT] = {
        {&PORTA, 0},
        {&PORTA, 1},
        {&PORTA, 2},
        {&PORTA, 3},
        {&PORTA, 4},
        {&PORTA, 5},
        {&PORTE, 0},
        {&PORTE, 1},
        {&PORTE, 2},
    };
    
    Pin led[S_COUNT] = {
        {&PORTB, 0},
        {&PORTB, 1},
        {&PORTB, 2},
        {&PORTB, 3},
        {&PORTB, 4},
        {&PORTB, 5},
        {&PORTB, 6},
        {&PORTB, 7},
        {&PORTC, 0},
    };
    
    while(1)
    {
        for(int i = 0; i < S_COUNT; i++) {
            *led[i].port = 0x00;
        }
        
        for(int i = 0; i < S_COUNT; i++) {
            int val = ADC_Read(i);
            
            if(val > 512) {
                for(int j = i; (j <= i + LED_VARIANT) && j < S_COUNT; j++) {
                    *led[j].port |= (1 << led[j].pin);
                }
                for(int j = i; (j >= i - LED_VARIANT) && j >= 0; j--) {
                    *led[j].port |= (1 << led[j].pin);
                }
            }
        }
        __delay_ms(1000);
    }
    
    return;
}
