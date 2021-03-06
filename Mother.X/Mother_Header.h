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
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000 //7370000L
#define FCY             SYS_FREQ/2

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

//Baud Rate pour la liaison UART AX_12
#define BAUDRATEAX12 57600
#define BRGVALAX12 ((FCY / BAUDRATEAX12 / 16) - 1)

#define led _LATA0
#define led2 _LATA1

#define AX_BOUGIES_1 13
#define AX_BOUGIES_2 10
#define AX_BOUGIES_3 4

#define BOUGIE_ON (1<<1)
#define BOUGIE_OFF (1<<2)
#define BOUGIE_TOP (1<<3)
#define BOUGIE_BOT (1<<4)

#define SORTIR_PINCE (1<<1)
#define CHOPPER_VERRE (1<<2)
#define LACHER_VERRE (1<<3)

#define AX_BG 8
#define AX_BD 11
#define AX_HG1 16
#define AX_HG2 17
#define AX_HD1 6
#define AX_HD2 7

#define microswitch_bas_de_pince _RC5
//etat du microswitch bas de course pour la pince : 1 = pince en bas, 0 = pas detecte

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

void ConfigureOscillator(); /* Handles clock switching/osc initialization */
void InitApp();             /* I/O and Peripheral Initialization          */

//protos AX12 pince
void Cinematique_inverse();
void Ouvrir_pince_bas();
int Serrer_verre_en_bas();
void Serrer_verre_en_haut();
void Serrer_stockage();
void Semi_ouvrir_stockage();
void Ouvrir_stockage();
void Rangement_stockage();
void Rangement_pince();
void Sortir_Pince();
void Chopper_verre();
void Lacher_verres();
void GetAXnoWait();

//protos de asserv pince
void Set_Vitesse(int);
void Set_Consigne_Hauteur(long);
void Set_Asserv_h(float, float);
void reset_pince();
void Init_PWM();
void Set_Vitesse_MoteurH(long);
void pince_en_descente();
void pince_en_montee();

//protos bras
void DoOnBougie();
void DoOffBougie();
void DoHitBotBougie();
void DoHitTopBougie();
