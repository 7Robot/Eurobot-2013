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
#include "PinceHeader.h"  /* Function / Parameters                           */
#include "timer.h"         /* Include timer fonctions                         */
#include "qei.h"           /* Includes qei functions                          */

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

    //ODCBbits.ODCB5 = 1;

    //Sortie enable avec Open Drain
    _TRISB9 = 0;
    _TRISB11 = 0;

    _ODCB9 = 1;
    _ODCB11 = 1;

    _ODCB10 = 1;

//    _TRISB2 = 1;
//    _TRISB3 = 1;
//    _TRISB6 = 1;
//    _TRISB7 = 1;


    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_ON & T2_SOURCE_INT, 0x8FF);
    ConfigIntTimer2(T2_INT_PRIOR_3 & T2_INT_ON); //Interruption ON et priorité 3


    OpenQEI1(QEI_DIR_SEL_QEB & QEI_INT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_1 & QEI_NORMAL_IO & QEI_MODE_x4_MATCH & QEI_UP_COUNT,0);
//    ConfigIntQEI1(QEI_INT_DISABLE);
//    WriteQEI1(65535);        //Valeur pour déclancher l'interruption du module QEI

    _QEA1R = 5;     //Module QEI 1 phase A sur RB5
    _QEB1R = 6;     //Module QEI 1 phase B sur RB6

  


    POS1CNT = 0;
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

    volatile int16_t tich = 0, old_tich = 0, diffh = 0;
    volatile int32_t compteur_tich = 0;
    volatile float inth = 0;
    volatile float Kph = 0, Kih=0;
    volatile char etat = 0;
    volatile int32_t consigne_hauteur = 0;
    volatile int vitesse_max = 0;
    //volatile float posx = 0.0, posy = 0.0;
    // volatile float posx = 0.0, posy = 0.0;

/* TODO Add interrupt routine code here. */

void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    led = led^1;    // On bascule l'état de la LED

    //Inutile
    tich = (int16_t) POS1CNT;// ReadQEI1();
    diffh = tich-old_tich;
    old_tich = tich;
    compteur_tich =tich;
    
    if (etat == 0)      // etat normal de fonctionnement
    {
        inth = 0;// inth + (float) (consigne_hauteur - compteur_tich);
        Set_Vitesse_MoteurH(( -Kph * (consigne_hauteur - compteur_tich) + Kih * inth ));
    }
    else//(etat == 1)     // etat reset vers le bas
    {
        if (microswitch_bas_de_pince() != 0)
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

void reset_pince(void)
{
    etat = 1;
}

void Set_Asserv_h(float Kph_new, float Kih_new)
{
    Kph = Kph_new;
    Kih = Kih_new;
}

void Set_Consigne_Hauteur(int Hauteur_mm)
{
    consigne_hauteur = 10 * Hauteur_mm;  // on cosidère 10 tics by mm
    //if (consigne_hauteur > 10000) consigne_hauteur = 10000;
}

void Set_Vitesse(int vitesse)
{
    vitesse_max = vitesse;
}

char microswitch_bas_de_pince(void)
{
    // renvoyer l'état du microswitch bas de course pour la pince : 1 = pince en bas, 0 = pas détecté
    return _RB3;
}