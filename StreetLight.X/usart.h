#ifndef USART_HEADER
#define	USART_HEADER

#include <xc.h>

void usart_init()
{
    TRISC6=TRISC7=1;
}

int rx_ready() {
    if (RCIF) {
        RCIF = 0;
        return 1;
    } else {
        return 0;
    }
}

void ser_int()
{
    TXSTA=0x20; //BRGH=0, TXEN = 1, Asynchronous Mode, 8-bit mode
    RCSTA=0b10010000; //Serial Port enabled,8-bit reception
    SPBRG=17;           //9600 baudrate for 11.0592Mhz
    TXIF=RCIF=0;
}
    
void tx(unsigned char a)
{
    TXREG=a;
    while(!TXIF);
    TXIF = 0;
}

unsigned char rx_wait()
{
    while(!RCIF);
    RCIF=0;
    return RCREG;
}

unsigned char rx_val()
{
    return RCREG;
}

#endif