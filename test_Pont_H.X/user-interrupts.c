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
#include "timer.h"         /* Include timer fonctions                         */
#include "qei.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void ConfigureOscillator(void)
{
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBDbits.PLLDIV = 41; // M=43
    CLKDIVbits.PLLPOST = 0; // N1=2
    CLKDIVbits.PLLPRE  = 0; // N2=2
    // Fosc = M/(N1.N2)*Fin
}

void InitApp(void)
{
    _TRISA0 = 0;
    led = 0;

    // activation de la priorité des interruptions
    _NSTDIS = 0;

    	/**** PTCON: PWM Time Base Control Register ****/
	PTCONbits.PTEN   = 0;   // Timer Enable bit:		    DISABLE MCPWM
	PWMCON1bits.PEN1H = 1;  // PWM1H (pin 37) is enabled for PWM output
	PWMCON1bits.PEN2H = 1;  // PWM2H (pin 35) is enabled for PWM output
	PTCONbits.PTCKPS = 1;   // Input Clock Prescale bits:   1:4
	PTCONbits.PTOPS  = 0;   // Output Clock Postscale bits: 1:1
	PTCONbits.PTSIDL = 1;	// Stop in Idle Mode:           YES
	PTCONbits.PTMOD  = 0;   // Mode Select bits:			Free Running Mode
	PTCONbits.PTEN   = 1;   // Timer Enable bit:		 	ENABLE MCPWM

	/**** PTPER: PWM Time Base Period Register ****/
	PTPERbits.PTPER = 0x01F4; // Period Value bits

        PDC1 = 0x1F4; // This sets the duty cycle, for or servo (or motor) 1875 is neutral.
        PDC2 = 0x1F4;

        _TRISB2 = 0;
        _TRISB3 = 0;
        _TRISB4 = 0;
        _TRISA4 = 0;

        //_ODCB5 = 1;
        //_ODCB6 = 1;

        _LATB2 = 1;
        _LATB3 = 0;
        _LATB4 = 1;
        _LATA4 = 0;

    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_ON & T2_SOURCE_INT, 0x09FF);
    ConfigIntTimer2(T2_INT_PRIOR_3 & T2_INT_ON); //Interruption ON et priorité 3/


    OpenQEI1(QEI_DIR_SEL_QEB & QEI_INT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_1 & QEI_NORMAL_IO & QEI_MODE_x4_MATCH & QEI_UP_COUNT,0);
    OpenQEI2(QEI_DIR_SEL_QEB & QEI_INT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_1 & QEI_NORMAL_IO & QEI_MODE_x4_MATCH & QEI_UP_COUNT,0);

    _QEA1R = 5;     //Module QEI 1 phase A sur RB5
    _QEB1R = 6;     //Module QEI 1 phase B sur RB6

    _QEA2R = 7;     //Module QEI 2 phase A sur RB7
    _QEB2R = 8;     //Module QEI 2 phase B sur RB8
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
/* _T5Interrupt        _U1ErrInterrupt                                        */
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

    volatile int16_t ticd = 0, old_ticd = 0, diffd = 0;
    volatile int16_t ticg = 0, old_ticg = 0, diffg = 0;
    volatile int32_t compteur_ticd = 0;
    volatile int32_t compteur_ticg = 0;

/* TODO Add interrupt routine code here. */

void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    led = led^1;    // On bascule l'état de la LED
    
    ticd = (int16_t) POS1CNT;// ReadQEI1();
    diffd = ticd-old_ticd;
    old_ticd = ticd;
    compteur_ticd += diffd;

    ticg = (int16_t) POS2CNT;// ReadQEI2();
    diffg = ticg-old_ticg;
    old_ticg = ticg;
    compteur_ticg += diffg;

    _T2IF = 0;      // On baisse le FLAG
}
