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
#include "ax12.h"
#include <libpic30.h>


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

#define BAUDRATE 57600
#define BRGVAL ((FCY / BAUDRATE / 16) - 1)

#define AX_BOUGIES_1 13
#define AX_BOUGIES_2 10
#define AX_BOUGIES_3 4

#define AX_PINCE_GAUCHE 8
#define AX_PINCE_DROITE 11

#define AX_GUIDE_GAUCHE_1 16
#define AX_GUIDE_GAUCHE_2 17
#define AX_GUIDE_DROIT_1 6
#define AX_GUIDE_DROIT_2 7

#define BOUGIE_ON (1<<1)
#define BOUGIE_OFF (1<<2)
#define BOUGIE_TOP (1<<3)
#define BOUGIE_BOT (1<<4)


volatile char actionAx =0;


extern void InterruptAX(void);


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

    OpenUART2(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGVAL);

    ConfigIntUART2(UART_RX_INT_PR5 & UART_RX_INT_EN
                 & UART_TX_INT_PR5 & UART_TX_INT_DIS);

    IFS2bits.SPI2IF = 0; // Flag SPI2 Event Interrupt Priority

    IPC8bits.SPI2IP = 2; // Priority SPI2 Event Interrupt Priority

    IEC2bits.SPI2IE = 1; //Enable SPI2 Event Interrupt Priority


    // activation de la priorité des interruptions
    _NSTDIS = 0;
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
void __int i=0attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    //led = led^1;    // On bascule l'état de la LED
    //_T2IF = 0;      // On baisse le FLAG
}
*/
//TODO TROUVER LES POSITION DES AX POUR REALISER LES ACTIONS

/*************************************************
 *                 Bougies
 *
 *************************************************/



void PosInitBougies(int Bot){

    if(Bot==1){
        PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x0358);
        __delay_ms(100);
        PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x029C);
        __delay_ms(300);
    }
    PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0207);
    __delay_ms(10);
    PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x029C);
    __delay_ms(10);
    PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x0180);
    __delay_ms(10);

}

//Taper sur les bougies du haut
void OnBougiesHitTop(){
   actionAx |= BOUGIE_TOP;
   IFS2bits.SPI2IF = 1;
}
void DoHitTopBougie(){
        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0207);
        __delay_ms(10);
        PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x0234);
        __delay_ms(10);
        PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x0158);
        __delay_ms(500);
        PosInitBougies(0);
        SendBougiesHitTopConfirm();
}

//Taper sur les bougies du bas

void OnBougiesHitBot(){
    actionAx |=  BOUGIE_BOT;
    IFS2bits.SPI2IF = 1;
}
void DoHitBotBougie(){
    PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0207);
    __delay_ms(10);
    PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x034E);
    __delay_ms(200);
    PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x00B9);
    __delay_ms(800);
    PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x02D9);
    __delay_ms(800);
    PosInitBougies(1);
    SendBougiesHitBotConfirm();
}

//Position pliée bras AX Bougies
void OnBougiesOff(){ //DONE
    actionAx |= BOUGIE_OFF;
    IFS2bits.SPI2IF = 1;
}
void DoOffBougie(){

        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0141);
        __delay_ms(50);
        PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x00D2);
        __delay_ms(10);
        PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x00AD);
        __delay_ms(800);
        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0086);
        __delay_ms(100);
        SendBougiesOffConfirm();
}



//Position dépliée bras AX Bougies
void OnBougiesOn(){
    actionAx |= BOUGIE_ON;
    IFS2bits.SPI2IF = 1;
}

void DoOnBougie(){

        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0141);
        __delay_ms(300);
        PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x029C);
        __delay_ms(10);
        PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x0180);
        __delay_ms(500);
        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0207);
        __delay_ms(100);
        SendBougiesOnConfirm();
}





/*************************************************
 *                 Verres
 *
 *************************************************/
/*
//TODO TROUVER LES POSITION DES AX POUR REALISER LES ACTIONS
//Lacher la totalité des verres (guide + pince)
void OnEndVerres(){

}

//Attraper Verre pince
void OnCatchVerres(){

}


//Position pliée pinces + guide
void OnOffVerres(){

        PutAX(AX_GUIDE_GAUCHE_1, AX_GOAL_POSITION, 710);
        __delay_ms(10);
        PutAX(AX_GUIDE_DROIT_1, AX_GOAL_POSITION, 200);
        __delay_ms(200);
        PutAX(AX_GUIDE_GAUCHE_2, AX_GOAL_POSITION, 710);
        __delay_ms(10);
        PutAX(AX_GUIDE_DROIT_2, AX_GOAL_POSITION, 560);

}

//Position dépliée pinces + guide
void OnOnVerres(){

        PutAX(AX_GUIDE_GAUCHE_1, AX_GOAL_POSITION, 710);
        __delay_ms(10);
        PutAX(AX_GUIDE_DROIT_1, AX_GOAL_POSITION, 200);
        __delay_ms(200);
        PutAX(AX_GUIDE_GAUCHE_2, AX_GOAL_POSITION, 710);
        __delay_ms(10);
        PutAX(AX_GUIDE_DROIT_2, AX_GOAL_POSITION, 560);


}


#define AX_GUIDE_GAUCHE_1 16
#define AX_GUIDE_GAUCHE_2 17
#define AX_GUIDE_DROIT_1 6
#define AX_GUIDE_DROIT_2 7
 *
#define AX_PINCE_GAUCHE 8
#define AX_PINCE_DROITE 11
 */

/*************************************************
 *                 Cadeaux
 *
 *************************************************/


/*************************************************
 *                 Autre
 *
 *************************************************/

//void OnGetPos(unsigned char idpic);
//void SendPos(unsigned char id, float value);





/*************************************************
 *          RX Interrupt
 *
 *************************************************/


void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void){
    InterruptAX();
    _U2RXIF = 0;      // On baisse le FLAG
}

void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void){
    led=1;
    IFS2bits.SPI2IF = 0;
    if((actionAx & BOUGIE_ON) == BOUGIE_ON){
        DoOnBougie();
        actionAx &= ~BOUGIE_ON;
    }else if((actionAx & BOUGIE_OFF) == BOUGIE_OFF){
        DoOffBougie();
        actionAx &= ~BOUGIE_OFF;
    }else if((actionAx & BOUGIE_BOT) == BOUGIE_BOT){
        DoHitBotBougie();
        actionAx &= ~BOUGIE_BOT;
    }else if((actionAx & BOUGIE_TOP) == BOUGIE_TOP){
        DoHitTopBougie();
        actionAx &= ~BOUGIE_TOP;
    }
    led=0;
}