// Generated from version 1303020239 of semantic

#ifndef _AX_H_
#define _AX_H_

#define BOARD_ID 3
#define BOARD_NAME Ax


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void OnBougiesHitBot();

void SendBougiesHitBotConfirm();

void OnBougiesHitTop();

void SendBougiesHitTopConfirm();

void OnBougiesOff();

void SendBougiesOffConfirm();

void OnBougiesOn();

void SendBougiesOnConfirm();

void OnGetPos(unsigned char idpic);

void SendPos(unsigned char id, float value);

void OnVerresCatch();

void SendVerresCatchConfirm();

void OnVerresEnd();

void SendVerresEndConfirm();

void OnVerresOff();

void SendVerresOffConfirm();

void OnVerresOn();

void SendVerresOnConfirm();


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _AX_H_
