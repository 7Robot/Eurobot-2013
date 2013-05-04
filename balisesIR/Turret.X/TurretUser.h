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

#define led1            _LATA0
#define led2            _LATA1

#define TSOP1		_RC9
#define TSOP2		_RB5
#define TSOP3           _RB6
#define TSOP4           _RB7
#define TSOP5           _RB8
#define TSOP6           _RB9
#define TSOP7           _RB10
#define TSOP8           _RB11
#define TSOP9           _RC7
#define TSOP10          _RC8
#define TSOP11          _RA7
#define TSOP12          _RA8
#define TSOP13          _RC3
#define TSOP14          _RC4
#define TSOP15          _RC5
#define TSOP16          _RC6

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void ConfigureOscillator(void); // Oscillator configuration