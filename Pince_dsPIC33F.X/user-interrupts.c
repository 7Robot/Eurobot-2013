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

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "header.h"        /* Function / Parameters                           */
#include <timer.h>         /* Include timer fonctions                         */
#include <uart.h>
#include <libpic30.h>
#include "ax12.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/


void ConfigureOscillator()
{
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBDbits.PLLDIV = 41; // M=43
    CLKDIVbits.PLLPOST = 0; // N1=2
    CLKDIVbits.PLLPRE  = 0; // N2=2
    // Fosc = M/(N1.N2)*Fin
}

void InitApp()
{
    _TRISA0 = 0;

    OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGVAL);

    ConfigIntUART1(UART_RX_INT_PR4 & UART_RX_INT_EN
                 & UART_TX_INT_PR4 & UART_TX_INT_DIS);

    // activation de la priorité des interruptions
    _NSTDIS = 0;
            
    /*
    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_ON & T2_SOURCE_INT, 0x9FFF);
    ConfigIntTimer2()
    EnableIntT2;    // Activation de l'interruption T23
    _T2IP = 3;      // Priorité de l'interruption
    */

}

int valeur[6];

void Cinematique_inverse()
{
    GetAX(AX_BD, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[0] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_BG, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[1] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_HD1, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[2] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_HD2, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[3] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_HG1, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[4] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_HG2, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[5] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);
}

/******************************************************************************/
/* Interrupt Vector Options                                                   */
/******************************************************************************/
/*                                                                            */
/* Refer to the C30 (MPLAB C Compiler for PIC24F MCUs and dsPIC33F DSCs) User */
/* Guide for an up to date list of the available interrupt options.           */
/* Alternately these names can be pulled from the device linker scripts.      */
/*                                                                            */
/* dsPIC33F Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt      _C1Interrupt                                           */
/* _IC1Interrupt       _DMA3Interrupt                                         */
/* _OC1Interrupt       _IC3Interrupt                                          */
/* _T1Interrupt        _IC4Interrupt                                          */
/* _DMA0Interrupt      _IC5Interrupt                                          */
/* _IC2Interrupt       _IC6Interrupt                                          */
/* _OC2Interrupt       _OC5Interrupt                                          */
/* _T2Interrupt        _OC6Interrupt                                          */
/* _T3Interrupt        _OC7Interrupt                                          */
/* _SPI1ErrInterrupt   _OC8Interrupt                                          */
/* _SPI1Interrupt      _DMA4Interrupt                                         */
/* _U1RXInterrupt      _T6Interrupt                                           */
/* _U1TXInterrupt      _T7Interrupt                                           */
/* _ADC1Interrupt      _SI2C2Interrupt                                        */
/* _DMA1Interrupt      _MI2C2Interrupt                                        */
/* _SI2C1Interrupt     _T8Interrupt                                           */
/* _MI2C1Interrupt     _T9Interrupt                                           */
/* _CNInterrupt        _INT3Interrupt                                         */
/* _INT1Interrupt      _INT4Interrupt                                         */
/* _ADC2Interrupt      _C2RxRdyInterrupt                                      */
/* _DMA2Interrupt      _C2Interrupt                                           */
/* _OC3Interrupt       _DCIErrInterrupt                                       */
/* _OC4Interrupt       _DCIInterrupt                                          */
/* _T4Interrupt        _DMA5Interrupt                                         */
/* _T5Inint i=0terrupt        _U1ErrInterrupt                                        */
/* _INT2Interrupt      _U2ErrInterrupt                                        */
/* _U2RXInterrupt      _DMA6Interrupt                                         */
/* _U2TXInterrupt      _DMA7Interrupt                                         */
/* _SPI2ErrInterrupt   _C1TxReqInterrupt                                      */
/* _SPI2Interrupt      _C2TxReqInterrupt                                      */
/* _C1RxRdyInterrupt                                                          */
/*                                                                            */
/* For alternate interrupt vector naming, simply add 'Alt' between the prim.  */
/* interrupt vector name '_' and the first character of the primary interrupt */
/* vector name.  There is no Alternate Vector or 'AIVT' for the 33E family.   */
/*                                                                            */
/* For example, the vector name _ADC2Interrupt becomes _AltADC2Interrupt in   */
/* the alternate vector table.                                                */
/*                                                                            */
/* Example Syntax:                                                            */
/*                                                                            */
/* void __attribute__((interrupt,auto_psv)) <Vector Name>(void)               */
/* {                                                                          */
/*     <Clear Interrupt Flag>                                                 */
/* }                                                                          */
/*                                                                            */
/* For more comprehensive interrupt examples refer to the C30 (MPLAB C        */
/* Compiler for PIC24 MCUs and dsPIC DSCs) User Guide in the                  */
/* <compiler installation directory>/doc directory for the latest compiler    */
/* release.                                                                   */
/*                                                                            */
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* TODO Add interrupt routine code here. */
/*
void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    //led = led^1;    // On bascule l'état de la LED
    //_T2IF = 0;      // On baisse le FLAG
}
*/




/*************************************************
 *          RX Interrupt
 *
 *************************************************/


void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){

    led = led ^ 1;
    InterruptAX();

    _U1RXIF = 0;      // On baisse le FLAG
}

/*************************************************
 *          TX Interrupt
 *
 *************************************************/


void __attribute__((__interrupt__, no_auto_psv)) _U1TXInterrupt(void)
{

   IFS0bits.U1TXIF = 0; // clear TX interrupt flag

}
