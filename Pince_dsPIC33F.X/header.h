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
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000 //7370000L
#define FCY             SYS_FREQ/2

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

//Baud Rate pour la liaison UART AX_12
#define BAUDRATE 57600
#define BRGVAL ((FCY / BAUDRATE / 16) - 1)

#define led _LATA0
#define AX_BG 8
#define AX_BD 11
#define AX_HG1 16
#define AX_HG2 17
#define AX_HD1 6
#define AX_HD2 7

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void ConfigureOscillator(void);    /* Handles clock switching/osc initialization */

void InitApp(void);             /* I/O and Peripheral Initialization          */

extern void InterruptAX(void);

void Cinematique_inverse();

