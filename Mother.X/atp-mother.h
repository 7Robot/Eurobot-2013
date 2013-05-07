// Generated from version 1305070329 of semantic

#ifndef _MOTHER_H_
#define _MOTHER_H_

#define BOARD_ID 6
#define BOARD_NAME Mother


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

void SendStartLaisseState(unsigned char state);

void OnChopperVerre();

void SendEmergencyState(unsigned char emergency_state);

void OnGetEmergencyState();

void OnGetNombreVerres();

void OnGetStartLaisseState();

void SendGetSwitchOneState();

void SendGetSwitchThreeState();

void SendGetSwitchTwoState();

void OnLacherVerres();

void SendNombreVerres(unsigned int n);

void OnSortirPince();

void SendSwitchOne(unsigned char state);

void SendSwitchThree(unsigned char state);

void SendSwitchTwo(unsigned char state);


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _MOTHER_H_
