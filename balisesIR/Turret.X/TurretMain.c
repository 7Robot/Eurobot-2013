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

#include "TurretSystem.h"  /* System funct/params, like osc/peripheral config */
#include "TurretUser.h"    /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#include <uart.h>
#include <ports.h>
#include <adc.h>
#include <libpic30.h>
#include <pwm12.h>
#include <libpic30.h>
#include <timer.h>

volatile unsigned int i;

int comparer(int donnees[], int adversaire[], int recepteur);

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    TRISAbits.TRISA0 = 0; // Microstick LED
    LATAbits.LATA0 = 1;   // affichage recepteur 1
    TRISAbits.TRISA1 = 0;
    LATAbits.LATA1 = 1;   // affichage recepteur 2
    TRISBbits.TRISB10 = 1;  // lecture recepteur 1
    TRISBbits.TRISB11 = 1;  // lecture recepteur 2


    /* __builtin_write_OSCCONL(OSCCON & 0xBF); // Unlock registers.
    //RPOR3bits.RP7R = 3; // U1TX sur RP7.
    //RPINR18bits.U1RXR = 10; // UART RX sur RP10
    __builtin_write_OSCCONL(OSCCON | 0x40); // Relock registers.*/

    int donnees[nombre_recepteurs*taille_uart];
    int adversaire[taille_uart] = {1,0,0,1,0,1,1,0}; //Mettre la donnée complémentée
    int recu = 0;
    
    __delay_ms(2000);

/*OpenUART1(UART_EN & UART_IDLE_STOP & UART_DIS_WAKE & UART_DIS_LOOPBACK
            & UART_DIS_ABAUD & UART_NO_PAR_8BIT & UART_1STOPBIT & UART_IrDA_DISABLE
            & UART_MODE_FLOW & UART_UEN_00 & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN,
              UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO & UART_SYNC_BREAK_DISABLED & UART_TX_DISABLE
            & UART_INT_RX_CHAR,
              ((FCY/9600)/16) - 1); // 9600 bauds
ConfigIntUART1(UART_RX_INT_DIS & UART_RX_INT_PR4 & UART_TX_INT_DIS);*/

    while(1)
    {
        if ((PORTBbits.RB10 == 0) || (PORTBbits.RB11 == 0)) // détection du bit de Start
        {
            __delay_us(bit_periode_us+bit_periode_us/2); // se place au millieu du 1er bit de Donnees
            for(i = 0;i<taille_uart;i++)
            {
                donnees[i] = PORTBbits.RB10;
                donnees[taille_uart+i] = PORTBbits.RB11;
                __delay_us(bit_periode_us);
            }
            recu = 1;
        }

        if(recu)
        {
            if (comparer(donnees,adversaire,1) && comparer(donnees,adversaire,2))
            {
                recu = 0;
                LATAbits.LATA0 = 1;
                LATAbits.LATA1 = 1;
            }
            else if (!comparer(donnees,adversaire,1) && comparer(donnees,adversaire,2))
            {
                recu = 0;
                LATAbits.LATA0 = 0;
                LATAbits.LATA1 = 1;
            }
            else if (comparer(donnees,adversaire,1) && !comparer(donnees,adversaire,2))
            {
                recu = 0;
                LATAbits.LATA0 = 1;
                LATAbits.LATA1 = 0;
            }
            else
            {
                recu = 0;
                LATAbits.LATA0 = 0;
                LATAbits.LATA1 = 0;
            }
        }
    }
}

int comparer(int donnees[], int adversaire[], int recepteur)
{
    int egal = 1;
    for(i = 0;i<taille_uart && egal;i++)
    {
        if(donnees[(recepteur-1)*taille_uart+i] != adversaire[i]){egal = 0;}
    }
    return egal;
}