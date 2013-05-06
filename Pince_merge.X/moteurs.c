#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "PinceHeader.h"  /* Function / Parameters                           */
#include <libpic30.h>
#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <math.h>




void Init_PWM(void)
{

   /**** PTCON: PWM Time Base Control Register ****/
	PTCONbits.PTEN   = 0;   // Timer Enable bit:		    DISABLE MCPWM
	PWMCON1bits.PEN3H = 1;  // PWM3H is enabled for PWM output
	PTCONbits.PTCKPS = 1;   // Input Clock Prescale bits:   1:4
	PTCONbits.PTOPS  = 0;   // Output Clock Postscale bits: 1:1
	PTCONbits.PTSIDL = 1;	// Stop in Idle Mode:           YES
	PTCONbits.PTMOD  = 0;   // Mode Select bits:			Free Running Mode
	PTCONbits.PTEN   = 1;   // Timer Enable bit:		 	ENABLE MCPWM

	/**** PTPER: PWM Time Base Period Register ****/
	PTPERbits.PTPER = 500; // Period Value bits
    
        PDC3 = 0;          // rapport cycliques nuls pour le moteur
          
}

void Set_Vitesse_MoteurH(float Consigne)
{
    if (Consigne < 0.0)
    {
        Consigne = -Consigne;
        pince_en_descente();
    }
    else
    {
        pince_en_montee();
    }

    if (Consigne > 1000.0)        Consigne = 1000.0;
    P1DC3 = (int)(Consigne);
}


void pince_en_descente(void)
{
    _LATB9 = 0;
    _LATB11 = 1;
}
void pince_en_montee(void)
{
    _LATB9 = 1;
    _LATB11 = 0;
}
