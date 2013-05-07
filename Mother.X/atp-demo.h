// Generated from version 1303020239 of semantic

#ifndef _DEMO_H_
#define _DEMO_H_

//#define BOARD_ID 1
//#define BOARD_NAME Demo


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void OnBlinkOff();

void OnBlinkOn();

void SendCallback();

void OnLedOff();

void OnLedOn();

void OnSetCallback(unsigned char nbloop);

void OnSetDelay(unsigned int delay);


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _DEMO_H_
