/*
* Template dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC802
* Juillet 2012
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

#define MAIN_C

#include "header.h"        /* Function / Parameters                           */
#include <uart.h>
#include <timer.h>
#include <libpic30.h>




/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/



/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

volatile int received2 = 0;
int16_t main(void)
{
    InitApp();

    char * Txdata = "Coucou\n\r";

    while(1)
    {
        
        __delay_ms(1000);
        //WriteUART1('U');
        //while(BusyUART1());

        if(received){
        putsUART1 ((unsigned int *)Txdata);  
        }
        

     /* received2 = U1RXREG;
        if(received2 == 'A')
            led ^= 1;

        led ^=1 ;
    */
    }
}


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/


void InitApp(void)
{
    ConfigureOscillator();


    __builtin_write_OSCCONL(OSCCON & 0xBF);
    _RP3R = 3;  // RP3 (pin 7) = U1TX (p.167)
    _U1RXR = 5; // RP2 (pin 6) = U1RX (p.165)
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    // Initialize IO ports and peripherals.
    _TRISA0 = 0; // led

/*
    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_ON & T2_SOURCE_INT, 0x9FFF);
    ConfigIntTimer2(T2_INT_PRIOR_4 & T2_INT_ON);
    EnableIntT2;
*/

    OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          ((FCY / 9600 / 16) - 1));

    ConfigIntUART1(UART_RX_INT_PR5 & UART_RX_INT_EN
                 & UART_TX_INT_PR5 & UART_TX_INT_DIS);

}