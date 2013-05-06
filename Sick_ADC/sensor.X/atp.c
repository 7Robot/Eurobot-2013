#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <timer.h>         /* Include timer fonctions                         */
#include <libpic30.h>
#include <uart.h>
#include <string.h>

#include "atp.h"
#include "header.h"

#if SEND_PRIO <= RECV_PRIO
#error "SEND_PRIO must be strictely superior than RECV_PRIO"
#endif
#if SEND_PRIO > 7
#error "SEND_PRIO must be inferior or equal to 7"
#endif
#if RECV_PRIO < 1
#error "RECV_PRIO must be superior or equal to 1"
#endif

#define BRGVAL ((FCY / BAUDRATE / 16) - 1)

// Variables d?envoi
typedef struct {
    char buf[BUF_SIZE];
    int begin;
    int end;
    int full;
    int flag;
} buffer;
static volatile buffer buffers[SEND_PRIO];
static volatile int runLevel;

// Variables de réceptions

static int packetState;
static int packetId;
static int packetDataType;
static int packetData[16];
static int packetDataLen;
static int packetDataPtr;

static unsigned char ucharv[MAX_UCHAR];
static int ucharc;
static unsigned int ushortv[MAX_USHORT];
static int ushortc;
static unsigned long int uintv[MAX_UINT];
static int uintc;
static char charv[MAX_CHAR];
static int charc;
static int shortv[MAX_SHORT];
static int shortc;
static long int intv[MAX_INT];
static int intc;
static float floatv[MAX_FLOAT];
static int floatc;

void AtpInit() {

    // Init des variables d?envoi
    int i;
    for (i = 0 ; i < SEND_PRIO ; i++) {
        buffer buf = buffers[i];
        buf.begin = 0;
        buf.end = 0;
        buf.full = 0;
        buf.flag = 0;
    }
    runLevel = -1;

    // Init des variables de réception
    packetState = 1;
    packetId = 0;
    packetDataType = 0;
    packetDataLen = 0;
    packetDataPtr = 0;
    ucharc = 0;
    ushortc = 0;
    uintc = 0;
    charc = 0;
    shortc = 0;
    intc = 0;
    floatc = 0;

    // Init du port série

    OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGVAL);

    int config = UART_RX_INT_EN & UART_TX_INT_EN;
    switch (RECV_PRIO) {
        case 1:
            config &= UART_RX_INT_PR1;
            break;
        case 2:
            config &= UART_RX_INT_PR2;
            break;
        case 3:
            config &= UART_RX_INT_PR3;
            break;
        case 4:
            config &= UART_RX_INT_PR4;
            break;
        case 5:
            config &= UART_RX_INT_PR5;
            break;
        case 6:
            config &= UART_RX_INT_PR6;
            break;
        case 7:
            config &= UART_RX_INT_PR7;
            break;
    }
    switch (SEND_PRIO) {
        case 2:
            config &= UART_TX_INT_PR2;
            break;
        case 3:
            config &= UART_TX_INT_PR3;
            break;
        case 4:
            config &= UART_TX_INT_PR4;
            break;
        case 5:
            config &= UART_TX_INT_PR5;
            break;
        case 6:
            config &= UART_TX_INT_PR6;
            break;
        case 7:
            config &= UART_TX_INT_PR7;
            break;
    }
    ConfigIntUART1(config);

    __builtin_write_OSCCONL(OSCCON & 0xBF);
     _RP5R = 3; // RP5 (pin 14) = U1TX (p.167)
    _U1RXR = 6; // RP6 (pin 15) = U1RX (p.165)
    __builtin_write_OSCCONL(OSCCON | 0x40);
}

//##############################################################################

void SendBoardId() {
    SendId(BOARD_ID);
}

void AtpTest() {
    SendTest(200, 40500, 100200, -100, -20100, -100200, 1.2345);
}

void SendText(char *str)
{
    SendBytes(str, strlen(str));
}

void SendBytes(char *bytes, int count)
{
    if (count == 0) return; // no data !

    int prio = _IPL;

    int end = buffers[prio].end;
    int pos;
    for (pos = 0 ; pos < count ; pos++) {
        buffers[prio].buf[end++] = bytes[pos];
        if (end == BUF_SIZE) end = 0;
        if (end == buffers[prio].begin) {
            buffers[prio].full = 1;
            if (prio == RECV_PRIO) {
                buffers[prio].end = end;
                buffers[prio].flag = 1;
                IFS0bits.U1TXIF = 1;
            }
            //led = 1;
            while (buffers[prio].full);
            //led = 0;
        }
    }
    buffers[prio].end = end;
    buffers[prio].flag = 1;
    IFS0bits.U1TXIF = 1;
}


void updateRunLevel() {
    int i;
    for (i = RECV_PRIO ; i >= 0 ; i--) {
        if (buffers[i].flag) {
            runLevel = i;
            //led = 1;
            return;
        }
    }
    //led = 0;
    runLevel = -1;
}

//##############################################################################

void processPacket() {
    led = led ^ 1;
    if (processProto(packetId, ucharv, ucharc,
            ushortv, ushortc,
            uintv, uintc,
            charv, charc,
            shortv, shortc,
            intv, intc,
            floatv, floatc)) {
        return;
    }
    if (BOARD_PROCESSOR(packetId, ucharv, ucharc,
            ushortv, ushortc,
            uintv, uintc,
            charv, charc,
            shortv, shortc,
            intv, intc,
            floatv, floatc)) {
        return;
    }
#ifdef REPORT_UNKNOW_PACKET
    SendError();
#endif
}

int checkDataType(unsigned int type) {
    switch (type) {
        case 1:
        case 2:
        case 4:
        case 17:
        case 18:
        case 20:
        case 36:
            return 1;
        default:
            return 0;
    }
}

void recv(unsigned int pending) {
    switch (packetState) {
        case 1:
            if (pending == 129) {
                packetState = 2;
                ucharc = 0;
            } else {
                // error
            }
            break;
        case 2:
            packetId = pending;
            packetState = 3;
            break;
        case 3:
            if (pending == 128) {
                processPacket();
                ucharc = 0;
                ushortc = 0;
                uintc = 0;
                charc = 0;
                shortc = 0;
                intc = 0;
                floatc = 0;
                packetState = 1;
            } else if (checkDataType(pending)) {
                packetDataType = pending;
                packetState = 4;
                packetDataLen = pending & 0b1111;
                packetDataPtr = 0;
            } else {
                // error
                ucharc = 0;
                ushortc = 0;
                uintc = 0;
                charc = 0;
                shortc = 0;
                intc = 0;
                floatc = 0;
                packetState = 1;
            }
            break;
        case 4:
            packetData[packetDataPtr++] = pending;
            if (packetDataPtr == packetDataLen) {
                long int i;
                float f;
                switch (packetDataType) {
                    case 1:
                        ucharv[ucharc++] = packetData[0];
                        break;
                    case 2:
                        ushortv[ushortc++] = packetData[1] << 8 | packetData[0];
                        break;
                    case 4:
                        uintv[uintc++] = (unsigned long int)packetData[3] << 24
                                        | (unsigned long int)packetData[2] << 16
                                        | packetData[1] << 8
                                        | packetData[0];
                        break;
                    case 17:
                        charv[charc++] = packetData[0];
                        break;
                    case 18:
                        shortv[shortc++] = packetData[1] << 8 | packetData[0];
                        break;
                    case 20:
                        ((char*)&i)[0] = packetData[0];
                        ((char*)&i)[1] = packetData[1];
                        ((char*)&i)[2] = packetData[2];
                        ((char*)&i)[3] = packetData[3];
                        intv[intc++] = i;
                        break;
                    case 36:
                        ((char*)&f)[0] = packetData[0];
                        ((char*)&f)[1] = packetData[1];
                        ((char*)&f)[2] = packetData[2];
                        ((char*)&f)[3] = packetData[3];
                        floatv[floatc++] = f;
                        break;
                }
                packetState = 3;
            }
            break;
    }
}

//##############################################################################

/*************************************************
 *          RX Interrupt
 *
 *************************************************/


void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    _U1RXIF = 0;      // On baisse le FLAG

    while(DataRdyUART1()) {
        recv(ReadUART1());
    }
}

/*************************************************
 *          TX Interrupt
 *
 *************************************************/

void __attribute__((__interrupt__, no_auto_psv)) _U1TXInterrupt(void)
{
    IFS0bits.U1TXIF = 0; // clear TX interrupt flag

    if (runLevel < 0) {
        updateRunLevel();
    }

    while (!U1STAbits.UTXBF && runLevel >= 0) {
        if (buffers[runLevel].begin != buffers[runLevel].end || buffers[runLevel].full) {
            buffers[runLevel].full = 0;
            WriteUART1(buffers[runLevel].buf[buffers[runLevel].begin++]);
            if (buffers[runLevel].begin == BUF_SIZE) buffers[runLevel].begin = 0;
        }
        if (buffers[runLevel].begin == buffers[runLevel].end) {
            buffers[runLevel].flag = 0;
            led = 0;
            updateRunLevel();
        }
    }
}