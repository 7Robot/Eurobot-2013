// Generated from version 1303020239 of semantic

#ifndef _FUNNY_H_
#define _FUNNY_H_

#define BOARD_ID 4
#define BOARD_NAME Funny


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendEndFunnyAction(unsigned char id);

void OnFunnyAction();

void OnSetThreshold(unsigned char id, float threshold);


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _FUNNY_H_
