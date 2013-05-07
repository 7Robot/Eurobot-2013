/*
* Asserv dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC804
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
#include <math.h>

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include "timer.h"         /* Include timer fonctions                         */
#include "qei.h"           /* Includes qei functions                          */
#include "AsservHeader.h"  /* Function / Parameters  */
#include "atp.h"
#include "atp-asserv.h"

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

    //On ouvre le Timer2 qui gère l'asservissement toutes les 10ms
    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_OFF & T2_SOURCE_INT, 0x600);
    ConfigIntTimer2(T2_INT_PRIOR_3 & T2_INT_ON); //Interruption ON et priorité 3

    //On ouvre le module QEI qui compte les tics
    OpenQEI1(QEI_DIR_SEL_QEB & QEI_INT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_1 & QEI_NORMAL_IO & QEI_MODE_x4_MATCH & QEI_UP_COUNT,0);
    OpenQEI2(QEI_DIR_SEL_QEB & QEI_INT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_1 & QEI_NORMAL_IO & QEI_MODE_x4_MATCH & QEI_UP_COUNT,0);
    _QEA1R = 9;     //Module QEI 1 phase A sur RP9, RB9
    _QEB1R = 22;    //Module QEI 1 phase B sur RP22, RC6
    _QEA2R = 23;    //Module QEI 2 phase A sur RP23, RC7
    _QEB2R = 24;    //Module QEI 2 phase B sur RP24, RC8
    POS1CNT = 0;    // 0 tic pour l'instant
    POS2CNT = 0;

    Init_PWM();     //Fonction d'initialisation du PWM
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
    volatile float Consigne_Vitesse = 0.0, Consigne_Omega = 0.0, Consigne_Distance = 0.0, Consigne_Theta = 0.0, Consigne_Theta2 = 0.0;
    volatile float Consigne_PosX = 0, Consigne_PosY = 0, Consigne_Thet = 0;
    volatile char Mode_Consigne = 0;
    volatile char etat =0;
    volatile float Distance_Obj = 0;

    //Coeffs vitesse
    volatile float KPv = 0, KDv = 0, KIv = 0;
    volatile float Vitesse_Actu = 0;
    volatile float Diff_Vitesse_Actu = 0, Diff_Vitesse_Old = 0, Diff_Vitesse_All = 0, Diff_Vitesse_point = 0;
    //Coeffs Omega
    volatile float KPo = 0, KDo = 0, KIo = 0;
    volatile float Omega_Actu = 0;
    volatile float Diff_Omega_Actu = 0, Diff_Omega_Old = 0, Diff_Omega_All = 0, Diff_Omega_point = 0;
    //Coeffs Distance
    volatile float KPd = 0, KDd = 0, KId = 0;
    volatile float Distance_Actu = 0;
    volatile float Diff_Distance_Actu = 0, Diff_Distance_Old = 0, Diff_Distance_All = 0, Diff_Distance_point = 0;
    //Coeffs Theta
    volatile float KPt = 0, KDt = 0, KIt = 0;
    volatile float Theta_Actu = 0;
    volatile float Diff_Theta_Actu = 0, Diff_Theta_Old = 0, Diff_Theta_All = 0, Diff_Theta_point = 0;

void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    float Consigne_Commune, Consigne_Diff, Consigne_Vitesse_Commune, Consigne_Vitesse_Diff;
    char Overshoot = 0;

    // On lit l'encodeur droit (qui est en fait le gauche)
    ticd = (uint16_t) POS1CNT;// ReadQEI2();
    diffd = ticd-old_ticd;
    old_ticd = ticd;
    compteur_ticd += diffd;

    // On lit l'encodeur gauche (qui est en fait le droit)
    ticg = (uint16_t) POS2CNT;// ReadQEI1();
    diffg = ticg-old_ticg;
    old_ticg = ticg;
    compteur_ticg += diffg;

    //if(Mode_Consigne == 5) Distance_Actu =0;

    // Mise à jour de la position actuelle, récupération des vitesses et position
    Incremente_Position(diffd, diffg, &Vitesse_Actu, &Omega_Actu, &Distance_Actu, &Theta_Actu);

    //On choisit le mode de déplacement et on met à jour les consignes si besoin
    Mise_A_Jour_Consignes();

    /*      PID sur la position     */

    // Calcul de l'erreur de position
    Diff_Distance_Actu = Consigne_Distance - Distance_Actu;
    Diff_Theta_Actu = Consigne_Theta - Theta_Actu;

    // Intégral de l'erreur de position
    Diff_Distance_All += Diff_Distance_Actu;
    Diff_Theta_All += Diff_Theta_Actu;

    // Dérivé de l'erreur de position
    Diff_Distance_point = Diff_Distance_Old - Diff_Distance_Actu;
    Diff_Theta_point = Diff_Theta_Old - Diff_Theta_Actu;

        if (Diff_Distance_All > 1500.0)
        {   Diff_Distance_All = 1500.0;  Overshoot = 1;  }
        if (Diff_Distance_All < -1500.0)
        {   Diff_Distance_All = -1500.0; Overshoot = 1;  } // 1500 = 3m/S * 1/2 seconde ? 1000 coups d'interupti/s
        if (Diff_Theta_All > 1500.0)
        {   Diff_Theta_All = 1500.0;    Overshoot = 1;  }
        if (Diff_Theta_All < -1500.0)
        {   Diff_Theta_All = -1500.0;   Overshoot = 1;  }       // 1500 ~=  PI * 1/2 seconde ? 1000 coups d'interrupt/s



    // Calcul des consignes de poisition
    Consigne_Commune = KPd * Diff_Distance_Actu + KId * Diff_Distance_All + KDd * Diff_Distance_point;
    Consigne_Diff = KPt * Diff_Theta_Actu + KIt * Diff_Theta_All + KDt * Diff_Theta_point;

    //Consigne_Diff *= Distance_Actu/Distance_Obj;

    Diff_Omega_Actu = Consigne_Diff - Omega_Actu;
    Diff_Omega_All += Diff_Omega_Actu;
    Diff_Omega_point = Diff_Omega_Old - Diff_Omega_Actu;
    Consigne_Vitesse_Diff = KPo * Diff_Omega_Actu + KIo * Diff_Omega_All + KDo * Diff_Omega_point;

    // Calcul des consignes moteurs
    Set_Vitesse_MoteurD(Consigne_Commune - Consigne_Vitesse_Diff); //ou Diff/2
    Set_Vitesse_MoteurG(Consigne_Commune + Consigne_Vitesse_Diff);

    /*
    //      PID sur la vitesse     //

    // Calcul de l'erreur de vitesse
    Diff_Vitesse_Actu = Consigne_Vitesse - Vitesse_Actu;
    Diff_Omega_Actu = Consigne_Omega - Omega_Actu;

    // Intégral de l'erreur de vitesse
    Diff_Vitesse_All += Diff_Vitesse_Actu;
    Diff_Omega_All += Diff_Omega_Actu;

    // Dérivé de l'erreur de vitesse
    Diff_Vitesse_point = Diff_Vitesse_Old - Diff_Vitesse_Actu;
    Diff_Omega_point = Diff_Omega_Old - Diff_Omega_Actu;

        if (Diff_Vitesse_All > 1500.0)
        {   Diff_Vitesse_All = 1500.0;  Overshoot = 1;  }
        if (Diff_Vitesse_All < -1500.0)
        {   Diff_Vitesse_All = -1500.0; Overshoot = 1;  } // 1500 = 3m/S * 1/2 seconde ? 1000 coups d'interupti/s
        if (Diff_Omega_All > 1500.0)
        {   Diff_Omega_All = 1500.0;    Overshoot = 1;  }
        if (Diff_Omega_All < -1500.0)
        {   Diff_Omega_All = -1500.0;   Overshoot = 1;  }       // 1500 ~=  PI * 1/2 seconde ? 1000 coups d'interrupt/s



    // Calcul des consignes de vitesse
    Consigne_Vitesse_Commune = KPv * Diff_Vitesse_Actu + KIv * Diff_Vitesse_All + KDv * Diff_Vitesse_point;
    Consigne_Vitesse_Diff = KPo * Diff_Omega_Actu + KIo * Diff_Omega_All + KDo * Diff_Omega_point;

//    // Calcul des consignes moteurs
//    Set_Vitesse_MoteurD(Consigne_Vitesse_Commune - Consigne_Vitesse_Diff); //ou Diff/2
//    Set_Vitesse_MoteurG(Consigne_Vitesse_Commune + Consigne_Vitesse_Diff);
      */

    // Mise à jour de la precedente valeur (pour le terme differentiel)
    Diff_Vitesse_Old = Diff_Vitesse_Actu;
    Diff_Omega_Old = Diff_Omega_Actu;
    Diff_Distance_Old = Diff_Distance_Actu;
    Diff_Theta_Old = Diff_Theta_Actu;

    _T2IF = 0;      // On baisse le FLAG
}

void Mise_A_Jour_Consignes(void)
{
    float D, Alpha;

    switch(Mode_Consigne)
    {
        float Dist_Freinage_D;
        float Dist_Freinage_T;

        case 0:

            D = Get_Distance_Obj(Consigne_PosX, Consigne_PosY);
            Alpha = Get_Angle_Obj(Consigne_PosX, Consigne_PosY) - Get_Angle();
            if (Alpha < -PI) {
                Alpha += PI;
            }
            Dist_Freinage_D = pow(Vitesse_Actu, 2)/(2*DECELERATION_V);
            Dist_Freinage_T = pow(Omega_Actu, 2)/(2*DECELERATION_O);

            if (D < Dist_Freinage_D)
            {
                Consigne_Vitesse -= DECELERATION_V;
            }
            else if(Vitesse_Actu < VITESSE_MAX)
            {
                Consigne_Vitesse += ACCELERATION_V;
            }
            if(fabs(Alpha) > PI/2)    Consigne_Vitesse = -Consigne_Vitesse;

            if (fabs(Alpha) < Dist_Freinage_T)
            {
                Consigne_Omega -= DECELERATION_O;//SIGN(Alpha)*DECELERATION_O;
            }
            else if(fabs(Omega_Actu) < OMEGA_MAX)
            {
                Consigne_Omega += ACCELERATION_O;// SIGN(Alpha)*ACCELERATION_O;
            }
            if(fabs(Alpha) > PI/2)  Consigne_Omega = -Consigne_Omega;
            break;

        case 1:
            D = Consigne_Distance - Distance_Actu;
            Dist_Freinage_D = pow(Vitesse_Actu, 2)/(2*DECELERATION_V);

            if(!etat)
            {
                if(D > 0) Consigne_Vitesse += ACCELERATION_V;
                else if(D < 0) Consigne_Vitesse -= ACCELERATION_V;
                if(fabs(Vitesse_Actu) > VITESSE_MAX)
                {
                    Consigne_Vitesse = VITESSE_MAX;
                    etat = 1;
                }
                else if(fabs(D) <= Dist_Freinage_D) etat = 2;
            }
            else if(etat)
            {
                if(fabs(D) <= Dist_Freinage_D) etat = 2;
            }
            else if(etat == 2)
            {
                if((Vitesse_Actu > -1 && Vitesse_Actu < 1))
                {
                    Consigne_Vitesse = 0;
                }
                else if(D > 0) Consigne_Vitesse -= DECELERATION_V;
                else if(D < 0) Consigne_Vitesse += DECELERATION_V;
            }
            break;

        case 2:

            Alpha = Consigne_Theta - Get_Angle();
//            if (Alpha < -PI) {
//                Alpha += 2*PI;
//            }
            Dist_Freinage_T = pow(Omega_Actu, 2)/(2*DECELERATION_O);

            if (fabs(Alpha) < Dist_Freinage_T)
            {
                Consigne_Omega -= SIGN(Alpha)*DECELERATION_O;
            }
            else if(fabs(Omega_Actu) < OMEGA_MAX)
            {
                Consigne_Omega += SIGN(Alpha)*ACCELERATION_O;
            }
            //if(fabs(Alpha) > PI/2)  Consigne_Omega = -Consigne_Omega;

            led2 = led2^1;

            break;

        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            Distance_Actu = 0;
            Theta_Actu = 0;
            Consigne_Distance = Get_Distance_Obj(Consigne_PosX, Consigne_PosY);
            Consigne_Theta = Get_Angle_Obj(Consigne_PosX, Consigne_PosY) - Get_Angle();
//            while (Consigne_Theta < -PI)    Consigne_Theta += 2*PI;
//            while (Consigne_Theta > PI)     Consigne_Theta -= 2*PI;
//            if(fabs(Consigne_Theta) > PI/2)
//            {
//                Consigne_Distance = -Consigne_Distance;
//                Consigne_Theta = fmod(Consigne_Theta + PI, 2*PI);
//            }
            //Consigne_Theta = Consigne_Theta2*pow(Consigne_Distance/Distance_Obj,3);
            if(fabs(Consigne_Theta) > PI/2) Consigne_Distance = -Consigne_Distance;
                        
            break;
    }
}

/******************* Consignes ******************************/

void Set_Rampe_Position(float ConsigneX, float ConsigneY)
{
    Consigne_PosX = ConsigneX;
    Consigne_PosY = ConsigneY;
    Mode_Consigne = 0;
}

void Set_Rampe_Distance(float Consigne)
{
    //A verifier
    Distance_Actu = 0;
    etat = 0;
    Consigne_Distance = Consigne;
    Consigne_Theta = Get_Angle();
    Mode_Consigne = 1;
}

void Set_Rampe_Angle(float Consigne)
{

    Consigne_Theta = Consigne;
    Mode_Consigne = 2;
}

void Set_Consigne_Distance(float Consigne)
{
    Consigne_Theta = Get_Angle();
    Consigne_Distance = Consigne;
    Mode_Consigne = 3;
}

void Set_Consigne_Angle(float Consigne)
{
    Consigne_Distance = 0;
    Consigne_Theta = Consigne;
    Mode_Consigne = 4;
}

void Set_Consigne_Position(float Consigne_X, float Consigne_Y)
{
    Consigne_PosX = Consigne_X;
    Consigne_PosY = Consigne_Y;
    Distance_Obj = Get_Distance_Obj(Consigne_PosX, Consigne_PosY);
    Mode_Consigne = 5;
}

/****************** bridge atp ********************************/

// GETs position
void OnGetPos() {
    float x, y, theta;
    Get_Position(&x, &y, &theta);
    SendPos(x, y, theta);
}
void OnGetAngle() { SendAngle(Theta_Actu); }

// GETs vitesse
void OnGetVit() { SendVit(Vitesse_Actu); }
void OnGetOmega() { SendOmega(Omega_Actu); }
void OnGetCourbe() { SendCourbe(Vitesse_Actu, Omega_Actu); }

// GETs coefs
void OnGetAsservD() { SendAsservD(KPd, KId, KDd); }
void OnGetAsservO() { SendAsservO(KPo, KIo, KDo); }
void OnGetAsservT() { SendAsservT(KPt, KIt, KDt); }
void OnGetAsservV() { SendAsservV(KPv, KIv, KDv); }

// SETs position
void OnStop() { Set_Consigne_Distance(0); }
void OnSetPos(float x, float y) { Set_Consigne_Position(x, y); }
void OnSetAngle(float theta) { Set_Consigne_Angle(theta); }
void OnSetDist(float dist) { Set_Consigne_Distance(dist); }

// SETs vitesse
//void OnSetVit(float v) { Set_Consigne_Vitesse(v); }
//void OnSetOmega(float omega) { Set_Consigne_Omega(omega); }
//void OnSetCourbe(float v, float omega) { Set_Consigne_Courbe(v, omega); }

// SETs coefs
void OnSetAsservD(float KPd_new, float KId_new, float KDd_new) { Set_Asserv_D(KPd_new, KDd_new, KId_new); }
void OnSetAsservO(float KPo_new, float KIo_new, float KDo_new) { Set_Asserv_O(KPo_new, KDo_new, KIo_new); }
void OnSetAsservT(float KPt_new, float KIt_new, float KDt_new) { Set_Asserv_T(KPt_new, KDt_new, KIt_new); }
void OnSetAsservV(float KPv_new, float KIv_new, float KDv_new) { Set_Asserv_V(KPv_new, KDv_new, KIv_new); }

/****************** Coefs asserv ******************************/

void Set_Asserv_V(float KPv_new, float KDv_new, float KIv_new)
{
    //Coeffs de l'asserv sur la vitesse linéaire
    KPv = KPv_new;
    KDv = KDv_new;
    KIv = KIv_new;
}

void Set_Asserv_O(float KPo_new, float KDo_new, float KIo_new)
{
    //Coeffs de l'asserv sur la vitesse angulaire
    KPo = KPo_new;
    KDo = KDo_new;
    KIo = KIo_new;
}

void Set_Asserv_D(float KPd_new, float KDd_new, float KId_new)
{
    //Coeffs de l'asserv sur la distance
    KPd = KPd_new;
    KDd = KDd_new;
    KId = KId_new;
}

void Set_Asserv_T(float KPt_new, float KDt_new, float KIt_new)
{
    //Coeffs de l'asserv sur theta
    KPt = KPt_new;
    KDt = KDt_new;
    KIt = KIt_new;
}
