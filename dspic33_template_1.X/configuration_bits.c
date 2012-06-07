/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

/******************************************************************************/
/* Configuration Bits                                                         */
/*                                                                            */
/* This is not all available configuration bits for all dsPIC devices.        */
/* Refer to the dsPIC device specific .h file in the compiler                 */
/* support\dsPIC33F\h directory for complete options specific to the device   */
/* selected.  For additional information about what hardware configurations   */
/* mean in terms of device operation, refer to the device datasheet           */
/* 'Special Features' chapter.                                                */
/*                                                                            */
/******************************************************************************/

/* TODO Fill in your configuration bits here.  The general style is below:    */

#if 0

/* Selects internal oscillator with no switching */
_FOSCSEL(FNOSC_FRC & IESO_OFF);

/* Disables clock switching and selects pri osc of HS with OSCIO clock output */
_FOSC(FCKSM_CSECME & OSCIOFNC_ON & POSCMD_HS);

/* Turns off JTAG and selects debug channel */
_FICD(JTAGEN_OFF & ICS_PGD1);

#endif
