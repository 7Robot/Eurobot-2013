/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000 //7370000L
#define FCY             SYS_FREQ/2

#define bit_periode_us      90
#define taille_uart         8
#define nombre_recepteurs   16


#define TSOP1		PORTCbits.RC9
#define TSOP2		PORTBbits.RB5
// ...
/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void ConfigureOscillator(void); // Oscillator configuration