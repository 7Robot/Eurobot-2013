// Generated from version 1303020239 of semantic

#include "atp.h"


void SendError() {
    char bytes[] = {
        129,
        253,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnGetId() { SendBoardId(); }

void SendId(unsigned char id) {
    char bytes[] = {
        129,
        255,
        1,
        id,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f) { SendTest(B, H, I, b, h, i, f); }

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f) {
    char bytes[] = {
        129,
        252,
        1,
        B,
        2,
        ((char*)&H)[0],
        ((char*)&H)[1],
        4,
        ((char*)&I)[0],
        ((char*)&I)[1],
        ((char*)&I)[2],
        ((char*)&I)[3],
        17,
        b,
        18,
        ((char*)&h)[0],
        ((char*)&h)[1],
        20,
        ((char*)&i)[0],
        ((char*)&i)[1],
        ((char*)&i)[2],
        ((char*)&i)[3],
        36,
        ((char*)&f)[0],
        ((char*)&f)[1],
        ((char*)&f)[2],
        ((char*)&f)[3],
        128
    };
    SendBytes(bytes, 28);
}

// You should redefine this function
__attribute__((weak)) void OnBougiesHitBot() {}

void SendBougiesHitBotConfirm() {
    char bytes[] = {
        129,
        6,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnBougiesHitTop() {}

void SendBougiesHitTopConfirm() {
    char bytes[] = {
        129,
        4,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnBougiesOff() {}

void SendBougiesOffConfirm() {
    char bytes[] = {
        129,
        8,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnBougiesOn() {}

void SendBougiesOnConfirm() {
    char bytes[] = {
        129,
        10,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnGetPos(unsigned char idpic) {}

void SendPos(unsigned char id, float value) {
    char bytes[] = {
        129,
        2,
        1,
        id,
        36,
        ((char*)&value)[0],
        ((char*)&value)[1],
        ((char*)&value)[2],
        ((char*)&value)[3],
        128
    };
    SendBytes(bytes, 10);
}

// You should redefine this function
__attribute__((weak)) void OnVerresCatch() {}

void SendVerresCatchConfirm() {
    char bytes[] = {
        129,
        14,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnVerresEnd() {}

void SendVerresEndConfirm() {
    char bytes[] = {
        129,
        12,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnVerresOff() {}

void SendVerresOffConfirm() {
    char bytes[] = {
        129,
        16,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnVerresOn() {}

void SendVerresOnConfirm() {
    char bytes[] = {
        129,
        18,
        128
    };
    SendBytes(bytes, 3);
}


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc)
{
    if (id == 254) {
        OnGetId();
        return 1;
    }
    if (id == 252) {
        OnTest(ucharv[0], ushortv[0], uintv[0], charv[0], shortv[0], intv[0], floatv[0]);
        return 1;
    }
    if (id == 5) {
        OnBougiesHitBot();
        return 1;
    }
    if (id == 3) {
        OnBougiesHitTop();
        return 1;
    }
    if (id == 7) {
        OnBougiesOff();
        return 1;
    }
    if (id == 9) {
        OnBougiesOn();
        return 1;
    }
    if (id == 1) {
        OnGetPos(ucharv[0]);
        return 1;
    }
    if (id == 13) {
        OnVerresCatch();
        return 1;
    }
    if (id == 11) {
        OnVerresEnd();
        return 1;
    }
    if (id == 15) {
        OnVerresOff();
        return 1;
    }
    if (id == 17) {
        OnVerresOn();
        return 1;
    }
    return 0;
}

