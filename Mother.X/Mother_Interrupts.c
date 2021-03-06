/*
* Template dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC804
* Juillet 2012
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*                 7robot.fr
*/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <qei.h>           /* Includes qei functions                          */
#include <timer.h>         /* Include timer fonctions                         */
#include <uart.h>
#include "ax12.h"
#include <libpic30.h>
#include "Mother_Header.h"

/******************************************************************************/
/*                            Global variables                                */
/******************************************************************************/

extern unsigned char num_ax;
extern unsigned char data;
extern volatile char actionBras;
extern volatile char actionPince;

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
    _TRISA0 = 0; //led en sortie
    _TRISA1 = 0;
    led = 0;
    led2 = 0;

    //Sortie enable
    _TRISB9 = 0;
    _TRISB11 = 0;
    _ODCB9 = 1; //Open drain RB9 (dir 1)
    _ODCB11 = 1; //Open drain RB11 (dir 2)
    _ODCB10 = 1; //open drain RB10 PWM1H3

     //Le microswicth sur la pin RC5 (par exemple), on la met en entrée
    _TRISC5 = 1; //bumper bas de pince
    //Et on active la pullup qui va bien (registres CNPU1 et CNPU2)
    _CN26PUE = 1;

    _ODCC9 = 1; // Open drain sur la pin RC9 (pour les AX12)

    _TRISA4 = 1;
    _TRISA8 = 1;
    _TRISA9 = 1;
    _TRISB2 = 1; //RTS ?
    _TRISB3 = 1; //FLush ?
    _TRISA2 = 1; //CLK12 ?

    _TRISB4 = 1; // Arret d'urgence
    _CN1PUE = 1; // avec pullup
    _TRISB12 = 1; // switch 1
    _CN14PUE = 1; // avec pullup
    _TRISB13 = 1; // switch 2
    _CN13PUE = 1; // avec pullup
    _TRISB14 = 1; // switch 3
    _CN12PUE = 1; // avec pullup
    _TRISB15 = 1; // Laisse
    _CN11PUE = 1; // avec pullup

    OpenUART2(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGVALAX12);

    ConfigIntUART2(UART_RX_INT_PR4 & UART_RX_INT_EN
                 & UART_TX_INT_PR4 & UART_TX_INT_DIS);

    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_OFF & T2_SOURCE_INT, 1500);
    ConfigIntTimer2(T2_INT_PRIOR_3 & T2_INT_ON); //Interruption ON et priorite 3

    OpenTimer5(T5_OFF & T5_GATE_OFF & T5_PS_1_1 & T5_SOURCE_INT, 40000);
    ConfigIntTimer5(T5_INT_PRIOR_2 & T5_INT_ON);

    OpenQEI1(QEI_DIR_SEL_QEB & QEI_INT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_1
            & QEI_NORMAL_IO & QEI_MODE_x4_MATCH & QEI_UP_COUNT,0);
//    ConfigIntQEI1(QEI_INT_DISABLE);
//    WriteQEI1(65535);        //Valeur pour declencher l'interruption du module QEI

    _QEA1R = 5;     //Module QEI 1 phase A sur RB5
    _QEB1R = 6;     //Module QEI 1 phase B sur RB6
    POS1CNT = 0; //valeur QEI

    IFS2bits.SPI2IF = 0; // Flag SPI2 Event Interrupt Priority
    IPC8bits.SPI2IP = 2; // Priority SPI2 Event Interrupt Priority
    IEC2bits.SPI2IE = 1; //Enable SPI2 Event Interrupt Priority

    // activation de la priorité des interruptions
    _NSTDIS = 0;
}

//variables globales d'asserv

    volatile int16_t tich = 0, old_tich = 0, diffh = 0;
    volatile int32_t compteur_tich = 0;
    volatile float inth = 0;
    volatile float Kph = 0, Kih=0;
    volatile char etat = 0;
    volatile long consigne_hauteur = 0;
    volatile int vitesse_max = 0;
    //volatile float posx = 0.0, posy = 0.0;
    // volatile float posx = 0.0, posy = 0.0;

//fonctions asserv

void reset_pince(void)
{
    etat = 1;
}

void Set_Asserv_h(float Kph_new, float Kih_new)
{
    Kph = Kph_new;
    Kih = Kih_new;
}

void Set_Consigne_Hauteur(long Hauteur_mm)
{
    consigne_hauteur = (long)(10 * Hauteur_mm);  // on cosid�re 10 tics by mm
    //if (consigne_hauteur > 10000) consigne_hauteur = 10000;
}

void Set_Vitesse(int vitesse)
{
    vitesse_max = vitesse;
}

/******************************************************************************/
/*    interrupt routine code                                                  */
/******************************************************************************/
void __attribute__((interrupt,auto_psv)) _T5Interrupt(void)
{
    _T5IF = 0;
    GetAX(num_ax, data);
}

void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    led2 = led2^1;    // On bascule l'etat de la LED

    //Inutile
    tich = (int16_t) POS1CNT;// ReadQEI1();
    POS1CNT = 0;
//    diffh = tich-old_tich;
//    old_tich = tich;
//    compteur_tich += diffh;

    if (!etat)      // etat normal de fonctionnement
    {
        inth = inth + (float) (consigne_hauteur - compteur_tich);
        Set_Vitesse_MoteurH(( Kph * (consigne_hauteur - tich) + Kih * inth ));
    }
    else if (etat)     // etat reset vers le bas
    {
        if (!microswitch_bas_de_pince)
        {
            Set_Vitesse_MoteurH(0);
            consigne_hauteur = 0;
            POS1CNT = 0;
            inth = 0;
            old_tich = 0;
            compteur_tich = 0;
            etat = 0;
        }
        else
        {
            Set_Vitesse_MoteurH(-vitesse_max);
        }
    }
    //Set_Vitesse_MoteurH(-vitesse_max);
    _T2IF = 0;      // On baisse le FLAG
}

//AX12 INTS
/*************************************************
 *          RX Interrupt                         *
 *************************************************/


void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void){

    led = led ^ 1;
    InterruptAX();

    _U2RXIF = 0;      // On baisse le FLAG
}

/*************************************************
 *          TX Interrupt                         *
 *************************************************/


void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt(void)
{

   _U2TXIF = 0; // clear TX interrupt flag

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
/* _T5Inint i=0terrupt _U1ErrInterrupt                                        */
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
/******************************************************************************/


void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void){
    led=1;
    IFS2bits.SPI2IF = 0;
    if ((actionBras & BOUGIE_ON) == BOUGIE_ON) {
        DoOnBougie();
        actionBras &= ~BOUGIE_ON;
    } else if ((actionBras & BOUGIE_OFF) == BOUGIE_OFF) {
        DoOffBougie();
        actionBras &= ~BOUGIE_OFF;
    } else if ((actionBras & BOUGIE_BOT) == BOUGIE_BOT) {
        DoHitBotBougie();
        actionBras &= ~BOUGIE_BOT;
    } else if ((actionBras & BOUGIE_TOP) == BOUGIE_TOP) {
        DoHitTopBougie();
        actionBras &= ~BOUGIE_TOP;
    } else if ((actionPince & SORTIR_PINCE) == SORTIR_PINCE) {
        Sortir_Pince();
        actionPince &= ~SORTIR_PINCE;
    } else if ((actionPince & CHOPPER_VERRE) == CHOPPER_VERRE) {
        Chopper_verre();
        actionPince &= ~CHOPPER_VERRE;
    } else if ((actionPince & LACHER_VERRE) == LACHER_VERRE) {
        Lacher_verres();
        actionPince &= ~LACHER_VERRE;
    }
    led=0;
}
