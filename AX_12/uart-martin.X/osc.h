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
* http://www.leobodnar.com/dsPIC33%20PLL%20settings.xls
*/



// Oscillator selection.
// Options : FRCPLL, PRIPLL, FRC.
#define PRIPLL


#ifdef FRCPLL
    #define SYS_FREQ        79227500L
#elif defined(PRIPLL)
    #define SYS_FREQ        80000000L // For 12 MHz crystal.
#else // FRC
    #define SYS_FREQ       7370000L
#endif

// Microcontroller MIPs (FCY)
#define FCY             (SYS_FREQ/2)

// Configuration bits can only be declared in one "Source File (*.c), but it
// seems better to group all oscillator config in this file. So we only declare
// the configuration bits when included from main.
#ifdef MAIN_C

    
    // Watchdog Timer.
    _FWDT(FWDTEN_OFF);
    // Select debug channel.
    _FICD(ICS_PGD1 & JTAGEN_OFF);

    #ifdef FRCPLL
        // Select Oscillator and switching.
        _FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
        // Select clock.
        _FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_ON & FCKSM_CSDCMD);

        void ConfigureOscillator()
        {
            // Configure PLL prescaler, PLL postscaler, PLL divisor
            PLLFBDbits.PLLDIV = 41; // M=43
            CLKDIVbits.PLLPOST = 0; // N1=2
            CLKDIVbits.PLLPRE  = 0; // N2=2
            // Fosc = M/(N1.N2)*Fin
        }
    #elif defined(PRIPLL)
        // Select Oscillator and switching.
        _FOSCSEL(FNOSC_PRIPLL & IESO_OFF);
        // Select clock.
        _FOSC(POSCMD_HS & OSCIOFNC_ON & IOL1WAY_ON & FCKSM_CSDCMD);

        void ConfigureOscillator()
        {
            // Configure PLL prescaler, PLL postscaler, PLL divisor
            PLLFBDbits.PLLDIV = 38; // M=40
            CLKDIVbits.PLLPOST = 0; // N1=2
            CLKDIVbits.PLLPRE  = 1; // N2=3
            // Fosc = M/(N1.N2)*Fin
        }
    #else // FRC
        // Select Oscillator and switching.
        _FOSCSEL(FNOSC_FRC & IESO_OFF);
        // Select clock.
        _FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_ON & FCKSM_CSDCMD);

        void ConfigureOscillator()
        {
            // Nothing to do.
        }
    #endif

#endif // MAIN_C
