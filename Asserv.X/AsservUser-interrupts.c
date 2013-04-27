/*
* Asserv dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC802
* Avril 2013
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*                 7robot.fr
*/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
                       
#include "timer.h"         /* Include timer fonctions                         */
#include "qei.h"           /* Includes qei functions                          */
#include "AsservHeader.h"  /* Function / Parameters                           */

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
    //LEDs en sorties
    _TRISB4 = 0;
    _TRISA9 = 0;
    led1 = 0;
    led2 = 0;

    // activation de la priorité des interruptions
    _NSTDIS = 0;

    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_ON & T2_SOURCE_INT, 0x09FF);
    ConfigIntTimer2(T2_INT_PRIOR_3 & T2_INT_ON); //Interruption ON et priorité 3


    OpenQEI1(QEI_DIR_SEL_QEB & QEI_INT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_1 & QEI_NORMAL_IO & QEI_MODE_x4_MATCH & QEI_UP_COUNT,0);
    OpenQEI2(QEI_DIR_SEL_QEB & QEI_INT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_1 & QEI_NORMAL_IO & QEI_MODE_x4_MATCH & QEI_UP_COUNT,0);
//    ConfigIntQEI1(QEI_INT_DISABLE);
//    ConfigIntQEI2(QEI_INT_DISABLE);
    //WriteQEI1(65535);        //Valeur pour déclancher l'interruption du module QEI
    //WriteQEI2(65535);        //Valeur pour déclancher l'interruption du module QEI

    Init_PWM();

    _QEA1R = 9;     //Module QEI 1 phase A sur RP9, RB9
    _QEB1R = 22;     //Module QEI 1 phase B sur RP22, RC6

    _QEA2R = 23;     //Module QEI 2 phase A sur RP23, RC7
    _QEB2R = 24;     //Module QEI 2 phase B sur RP24, RC8



    POS1CNT = 0;
    POS2CNT = 0;


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
    volatile float Consigne_Vitesse = 0.0;
    volatile float Consigne_Theta = 0.0;

    volatile float KPv = 0, KDv = 0,KIv = 0;
    volatile float Diff_Vitesse_Actu = 0, Diff_Vitesse_Old = 0, Diff_Vitesse_All = 0;
    volatile float KPt = 0, KDt = 0, KIt = 0;
    volatile float Diff_Theta_Actu = 0, Diff_Theta_Old = 0, Diff_Theta_All = 0;
    //volatile float posx = 0.0, posy = 0.0;
   // volatile float posx = 0.0, posy = 0.0;

/* TODO Add interrupt routine code here. */

void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    float Vitesse_Actu, Theta_Actu;
    float Consigne_Commune, Consigne_Diff;
    char Overshoot = 0;

    led1 = led1^1;    // On bascule l'état de la LED

    compteur_ticd = (int16_t) POS2CNT;// ReadQEI2();
//    ticd = (int16_t) POS1CNT;// ReadQEI1();
//    diffd = ticd-old_ticd;
//    old_ticd = ticd;
//    compteur_ticd += diffd;

    compteur_ticg = (int16_t) POS1CNT;// ReadQEI1();
//    ticg = (int16_t) POS2CNT;// ReadQEI2();
//    diffg = ticg-old_ticg;
//    old_ticg = ticg;
//    compteur_ticg += diffg;

    Incremente_Position(diffd, diffg, &Vitesse_Actu, &Theta_Actu);      // mise à jour de la position actuelle, récupération de la vitesse et de l'angle

    Mise_A_Jour_Consignes(&Consigne_Vitesse, &Consigne_Theta, Vitesse_Actu);

    Vitesse_Actu *= 1000;       // (fournie en metres/milisecondes)

    Diff_Vitesse_Actu = Consigne_Vitesse - Vitesse_Actu;        // calcul de la difference entre réel et consigne
    Diff_Theta_Actu = Consigne_Theta - Theta_Actu;

    Diff_Theta_All += Diff_Theta_Actu;                  // mise à jour du terme intégral
    Diff_Vitesse_All += Diff_Vitesse_Actu;

    // overshoot

    if (Diff_Vitesse_All > 1500.0)
    {   Diff_Vitesse_All = 1500.0;  Overshoot = 1;  }
    if (Diff_Vitesse_All < -1500.0)
    {   Diff_Vitesse_All = -1500.0; Overshoot = 1;  } // 1500 = 3m/S * 1/2 seconde à 1000 coups d'interupti/s
    if (Diff_Theta_All > 1500.0)
    {   Diff_Theta_All = 1500.0;    Overshoot = 1;  }
    if (Diff_Theta_All < -1500.0)
    {   Diff_Theta_All = -1500.0;   Overshoot = 1;  }       // 1500 ~=  PI * 1/2 seconde à 1000 coups d'interrupt/s


    // calcul des consignes
    Consigne_Commune = KPv * Diff_Vitesse_Actu + KIv * Diff_Vitesse_All + KDv * (Diff_Vitesse_Old - Diff_Vitesse_Actu);
    Consigne_Diff = KPt * Diff_Theta_Actu + KIt * Diff_Theta_All + KDt * (Diff_Theta_Old - Diff_Theta_Actu);


    Diff_Theta_Old = Diff_Theta_Actu;               // mise à jour de la precedente valeur (pour le terme differentiel)
    Diff_Vitesse_Old = Diff_Vitesse_Actu;


//    Set_Vitesse_MoteurD(Consigne_Commune);        // calcul des consignes moteurs
//    Set_Vitesse_MoteurG(Consigne_Commune);

    Set_Vitesse_MoteurD(Consigne_Commune + Consigne_Diff);        // calcul des consignes moteurs
    Set_Vitesse_MoteurG(Consigne_Commune - Consigne_Diff);             // NIM: C'est pas Consigne_Diff/2 ?

    _T2IF = 0;      // On baisse le FLAG
}

void Set_Asserv_V(float KPv_new, float KDv_new, float KIv_new)
{
    KPv = KPv_new;
    KDv = KDv_new;
    KIv = KIv_new;
}

void Set_Asserv_T(float KPt_new, float KDt_new, float KIt_new)
{
    KPt = KPt_new;
    KDt = KDt_new;
    KIt = KIt_new;
}
