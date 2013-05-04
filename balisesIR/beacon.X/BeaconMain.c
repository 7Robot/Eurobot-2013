/*
* Beacon dsPIC33F
* Compiler : Microchip xC16
* �C : 33FJ64MC802
* Avril 2013
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

/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "BeaconSystem.h"  /* System funct/params, like osc/peripheral config */
#include "BeaconUser.h"    /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#include <uart.h>
#include <pwm.h>
#include <ports.h>
#include <adc.h>
#include <libpic30.h>
#include <pwm12.h>
#include <libpic30.h>
#include <timer.h>

volatile unsigned i = 1;
unsigned int config1;
unsigned int config2;
unsigned int config3;
unsigned int U1MODEvalue;
unsigned int U1STAvalue;
unsigned int sptime;
unsigned int period;

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    AD1PCFGL = 0xFFFF; //Putain, met ca en numerique, quoi !

    TRISAbits.TRISA0 = 0; //  LED1
    TRISAbits.TRISA1 = 0; //  LED1
    _TRISB2 = 1;
    _TRISB3 = 1;

    _TRISC1 = 1; //pin de CN9 qui recoit le TX donc rx

    UnlockRP; // Unlock registers.
    _RP16R = 3; // U1TX sur RP16
    LockRP; // Relock registers.
    
    ConfigIntCN(CHANGE_INT_ON & CHANGE_INT_PRI_4 & 0xFF000200); /*Interrupt sur CN1*/
    
    CloseUART1();
    ConfigIntUART1(UART_RX_INT_DIS & UART_TX_INT_DIS);
    
    OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          baud);


    OpenTimer1(T1_ON & T1_IDLE_STOP & T1_GATE_OFF & T1_PS_1_64 & T1_SYNC_EXT_OFF & T1_SOURCE_INT, 0x1FFF);
    ConfigIntTimer1(T1_INT_PRIOR_2 & T1_INT_ON);

    ConfigIntMCPWM1(PWM1_INT_DIS);
    SetDCMCPWM1(1,0,0);
    
    period = 86;
    sptime = 0;
    config1 = (PWM1_EN & PWM1_IDLE_STOP & PWM1_OP_SCALE1 & PWM1_IPCLK_SCALE1 & PWM1_MOD_FREE);
    config2 = (PWM1_MOD1_IND & PWM1_PDIS3H & PWM1_PDIS2H & PWM1_PEN1H & PWM1_PDIS3L & PWM1_PDIS2L & PWM1_PEN1L);
    config3 = (PWM1_SEVOPS1 & PWM1_OSYNC_PWM & PWM1_UEN);
    OpenMCPWM1(period,sptime,config1,config2,config3);
    //P1DC1 = 88;

    while(1)
    {
        WriteUART1(adversaire1);
        while(BusyUART1());
        __delay_ms(10);
    }

}