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

#include <uart.h>
#include "ax12.h"


/******************************************************************************
 * Global Variables
 ******************************************************************************/
byte checksumAX;
int posAX = -5;

/*
 * Public global variables, which have to be declared volatile.
 */
volatile int responseReadyAX = 0;
responseAXtype responseAX;

/******************************************************************************
 * Wiring dependent functions, that you should customize
 ******************************************************************************/

void SetTX() {
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    _U2RXR = 31;
    _RP25R = 0b00101;  // RP25 = U2TX (p.167)
    __builtin_write_OSCCONL(OSCCON | 0x40);
}

void SetRX() {
    __builtin_write_OSCCONL(OSCCON & 0xBF);
     _RP25R = 0;
    _U2RXR = 25; // RP25 = U2RX (p.165)
    __builtin_write_OSCCONL(OSCCON | 0x40);
}

/******************************************************************************
 * Functions to read and write command and return packets
 ******************************************************************************/

void PushUART(byte b) {
    while (U2STAbits.UTXBF); // UART2 TX Buffer Full
    WriteUART2(b);
    checksumAX += b;
}

/*
 * Write the first bytes of a command packet, assuming a <len> parameters will
 * follow.
 */
void PushHeaderAX(byte id, byte len, byte inst) {
    SetTX();

    PushUART(0xFF);
    PushUART(0xFF);

    checksumAX = 0; // The first two bytes don't count.
    PushUART(id);
    PushUART(len + 2); // Bytes to go : instruction + buffer (len) + checksum.
    PushUART(inst);
}

/* Write a buffer of given length to the body of a command packet. */
void PushBufferAX(byte len, byte* buf) {
    byte i;
    for (i = 0; i < len; i++) {
        PushUART(buf[i]);
    }
}

/* Finish a command packet by sending the checksum. */
void PushFooterAX() {
    PushUART(~checksumAX);
    while (BusyUART1()); // UART1 Transmit Shift Register Empty
    SetRX();
}

int expected = 0;
int received = 0;
/**/
void InterruptAX() {
    while(DataRdyUART2()) {
        byte b = ReadUART2();

        if(posAX == -5 && b == 0xFF)
            posAX = -4;
        else if(posAX == -4 && b == 0xFF) {
            posAX = -3;
            checksumAX = 0;
            responseAX.len = 1;
        }
        else if(posAX == -3) {
            posAX = -2;
            responseAX.id = b;
        }
        else if(posAX == -2 && b < 2 + 4 /*taille de ax.parameters*/) {
            posAX = -1;
            checksumAX = responseAX.id + b;
            responseAX.len = b - 2;
        }
        else if(posAX == -1) {
            posAX = 0;
            responseAX.error = *((errorAX*)&b);
        }
        else if(0 <= posAX && posAX < responseAX.len) {
            ((byte*)&responseAX.params)[posAX++] = b;
            checksumAX += b;
        }
        else if(posAX == responseAX.len && (b & checksumAX) == 0) {
            responseReadyAX = 1;
            posAX = -5;
        }
        else
            posAX = -5; // Erreur.
    }
}


/******************************************************************************
 * Instructions Implementation
 ******************************************************************************/

void PingAX(byte id) {
    PushHeaderAX(id, 2, AX_INST_PING);
    PushFooterAX();
}

void ReadAX(byte id, byte address, byte len) {
    PushHeaderAX(id, 2, AX_INST_READ_DATA);
    PushUART(address);
    PushUART(len);
    PushFooterAX();
}

void WriteAX(byte id, byte address, byte len, byte* buf) {
    PushHeaderAX(id, 1 + len, AX_INST_WRITE_DATA);
    PushUART(address);
    PushBufferAX(len, buf);
    PushFooterAX();
}

void RegWriteAX(byte id, byte address, byte len, byte* buf) {
    PushHeaderAX(id, 1 + len, AX_INST_REG_WRITE);
    PushUART(address);
    PushBufferAX(len, buf);
    PushFooterAX();
}

void ActionAX(byte id) {
    PushHeaderAX(id, 0, AX_INST_ACTION);
    PushFooterAX();
}

void ResetAX(byte id) {
    PushHeaderAX(id, 0, AX_INST_RESET);
    PushFooterAX();
}


/******************************************************************************
 * Convenience Functions
 ******************************************************************************/

byte RegisterLenAX(byte address) {
    switch (address) {
        case  2: case  3: case  4: case  5: case 11: case 12: case 13: case 16:
        case 17: case 18: case 19: case 24: case 25: case 26: case 27: case 28:
        case 29: case 42: case 43: case 44: case 46: case 47:
            return 1;
        case  0: case  6: case  8: case 14: case 20: case 22: case 30: case 32:
        case 34: case 36: case 38: case 40: case 48:
            return 2;
    }
    return 0; // Unexpected.
}

/* Write a value to a registry, guessing its width. */
void PutAX(byte id, byte address, int value) {
    responseReadyAX = 0;
    WriteAX(id, address, RegisterLenAX(address),
                   (byte*)&value /* C18 and AX12 are little-endian */);
}

/* Read a value from a registry, guessing its width. */
void GetAX(byte id, byte address) {
    responseReadyAX = 0;
    ReadAX(id, address, RegisterLenAX(address));
}
