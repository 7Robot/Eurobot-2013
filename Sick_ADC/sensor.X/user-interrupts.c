/*
* Code ADC Capteur Sick
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
#include <adc.h>
#include "atp.h"




/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/


//Nombre de capteur branché sur les AN
#define NB_SENSOR         4

#define AN0  0
#define AN1  1
#define AN2  2
#define AN3  3
#define AN4  4
#define AN5  5
#define AN6  6
#define AN7  7


extern void InterruptAX(void);

char channel = 0;


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

    // activation de la priorité des interruptions
    _NSTDIS = 0;


    ConfigIntTimer2(T2_INT_PRIOR_2 & T2_INT_ON);

    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_ON & T2_SOURCE_INT, 0x1FFF);

    EnableIntT2;


}
void InitAdc()
{

   //Configuration du convertisseur Analog to Digital (ADC) du dspic33f
   //Cf page 286 dspic33f Data Sheet
   //Eteindre A/D converter pour la configuration
   AD1CON1bits.ADON = 0;
   //Configure le format de la sortie de l'ADC ( 3=signed float, 2=unsigned float, 1=signed integer, 0=unsigned integer
   AD1CON1bits.FORM = 0;
   //Config de l'échantillonnage : auto-convert
   AD1CON1bits.SSRC = 7;
   //Début d'échantillonnage (1=tout de suite  0=dès que AD1CON1bits.SAMP est activé)
   AD1CON1bits.ASAM = 0;
   //Choix du type de converter (10 ou 12 bits) 0 = 10 bits , 1 = 12bits
   AD1CON1bits.AD12B = 0;
   //Choix du type de clock interne (=1) ou externe (=0)
   AD1CON3bits.ADRC = 1;
   //Choix des références liées à la mesure analogique sur le channel 0
   AD1CHS0bits.CH0SA = 0;	// Choix du (+) de la mesure pour le channel CH0 (0 = AN0) par défault
   AD1CHS0bits.CH0NA = 0;	// Choix du (-) de la mesure pour le channel CH0 (0 = Masse interne pic)

   //Met tous les ports AN en Digital Input
   AD1PCFGL = 0xFFFF;

   //Selectionne quelles pins sont analogiques
   AD1PCFGLbits.PCFG0 = 0;
   AD1PCFGLbits.PCFG1 = 0;
   AD1PCFGLbits.PCFG2 = 0;
   AD1PCFGLbits.PCFG3 = 0;
   AD1PCFGLbits.PCFG4 = 0;
   AD1PCFGLbits.PCFG5 = 0;
   /* COM A ENLEVER SUR DSPIC AVEC 8 PINS ANALOGIQUES
   AD1PCFGLbits.PCFG6 = 0;
   AD1PCFGLbits.PCFG7 = 0;
    */

   //Mise à 0 du flag d'interrupt de ADC1
   IFS0bits.AD1IF = 0;
   //Enable les interruptions d'ADC1
   IEC0bits.AD1IE = 1;
   //Et les prioritées (ici prio = 3)
   IPC3bits.AD1IP = 3;

   AD1CON1bits.SAMP = 0;
   AD1CON1bits.ADON = 1;		// Turn on the A/D converter
}


void TestZone (short adc,char channel)
{    
    unsigned char zone = adc>>6;
    if (floodOn || zone != lastZone[channel]) {
        lastZone[channel] = zone;
        SendZone(channel, zone);
    }      
}

void OnFloodOn()
{
    floodOn = 1;
}

void OnFloodOff()
{
    floodOn = 0;
}

void OnGetValue(unsigned char id)
{
   SendValue(id, Buff_adc_value[channel]);
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

void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{


    // Balayage des chans AN. A chaque interruption du timer 2, le pic définit sur quel pin il sample
    //le changement de la cariable "channel" se fait dans l'interruption de l'ADC

    /* /!\ ordre des déclarations de pin à changer si tout les pins ne sont pas utilisés /!\ */

    switch(channel){
        case 0:
            AD1CHS0bits.CH0SA = AN0;
        break;
        case 1:
            AD1CHS0bits.CH0SA = AN1;
        break;
        case 2:
            AD1CHS0bits.CH0SA = AN2;
        break;
        case 3:
            AD1CHS0bits.CH0SA = AN3;
        break;
        case 4:
            AD1CHS0bits.CH0SA = AN4;
        break;
        case 5:
            AD1CHS0bits.CH0SA = AN5;
        break;
        case 6:
            AD1CHS0bits.CH0SA = AN6;
        break;
        case 7:
            AD1CHS0bits.CH0SA = AN7;
        break;


        default:
            AD1CHS0bits.CH0SA = AN0;
        break;
    }   

    AD1CON1bits.SAMP = 1; //Start sampling
    _T2IF = 0;            // On baisse le FLAG
}


void __attribute__ ((interrupt, auto_psv)) _ADC1Interrupt(void)
 {

    Buff_adc_value[channel]  = ADC1BUF0;

    TestZone(Buff_adc_value[channel],channel);

    channel++;
    channel=channel%NB_SENSOR;

    AD1CON1bits.SAMP = 0;      //Stop sampling
    IFS0bits.AD1IF = 0;        //Clear the interrupt flag
 }


