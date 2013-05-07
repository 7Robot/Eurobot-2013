// Generated from version 1305071419 of semantic

#ifndef _TURRET_H_
#define _TURRET_H_

#define BOARD_ID 8
#define BOARD_NAME Turret


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void OnGetPos(unsigned char id);

void OnOff();

void OnOn();

void SendPos(unsigned char id, unsigned char distance, unsigned char angle);


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _TURRET_H_
