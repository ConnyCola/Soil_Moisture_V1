#include <msp430G2452.h>
#include "defines.h"
#include "global.h"
#include "soft_uart.h"

unsigned char *ptr_Tx;
unsigned char BiTcntr;
unsigned char txByte;

void initIO(void);
void initTA1(void);
void uartTx(unsigned char byte);

void initIO(void){
    P2SEL &= ~TxD;
    P2SEL2 &= ~TxD;
    P2DIR |= TxD;
    P2OUT |= TxD;
}

void initTA1(void){
//    TA1CTL = TACLR;
//    TA1CTL = TASSEL_2 + ID_0;
//    TA1CCR0 = Baudrate;
//    TA1CCTL0 |= CCIE;
}

void uartTx(unsigned char byte){
    *(ptr_Tx) = byte;
    BiTcntr = 9;
    //TA1CTL |= MC_1;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void){
    switch (BiTcntr){
    case 9:
        P2OUT &= ~TxD;              //uart operation
        txByte = *(ptr_Tx);
        BiTcntr--;
        break;
    default:
        if (txByte & 0x01){
            P2OUT |= TxD;           //uart operation
        }else{
            P2OUT &= ~TxD;          //uart operation
        }
        txByte = txByte>>1;
        BiTcntr--;
        break;
    case 0:
        ptr_Tx++;
        P2OUT |= TxD;               //uart operation
        //TA1CTL &= ~MC_1;
//      _BIC_SR_IRQ(CPUOFF);        // Exit LPM0 Use if needed
        break;
    }
}
