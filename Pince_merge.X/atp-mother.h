// Generated from version 1305062032 of semantic

#ifndef _MOTHER_H_
#define _MOTHER_H_

#define BOARD_ID 6
#define BOARD_NAME Mother


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void OnChopperVerre();

void OnGetNombreVerres();

void OnLacherVerres();

void SendNombreVerres(unsigned int n);

void OnSortirPince();


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _MOTHER_H_
