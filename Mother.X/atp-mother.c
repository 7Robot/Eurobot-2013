// Generated from version 1305070329 of semantic

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
        13,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnBougiesHitTop() {}

void SendBougiesHitTopConfirm() {
    char bytes[] = {
        129,
        11,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnBougiesOff() {}

void SendBougiesOffConfirm() {
    char bytes[] = {
        129,
        15,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnBougiesOn() {}

void SendBougiesOnConfirm() {
    char bytes[] = {
        129,
        17,
        128
    };
    SendBytes(bytes, 3);
}

void SendStartLaisseState(unsigned char state) {
    char bytes[] = {
        129,
        41,
        1,
        state,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnChopperVerre() {}

void SendEmergencyState(unsigned char emergency_state) {
    char bytes[] = {
        129,
        21,
        1,
        emergency_state,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnGetEmergencyState() {}

// You should redefine this function
__attribute__((weak)) void OnGetNombreVerres() {}

// You should redefine this function
__attribute__((weak)) void OnGetStartLaisseState() {}

void SendGetSwitchOneState() {
    char bytes[] = {
        129,
        30,
        128
    };
    SendBytes(bytes, 3);
}

void SendGetSwitchThreeState() {
    char bytes[] = {
        129,
        34,
        128
    };
    SendBytes(bytes, 3);
}

void SendGetSwitchTwoState() {
    char bytes[] = {
        129,
        32,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnLacherVerres() {}

void SendNombreVerres(unsigned int n) {
    char bytes[] = {
        129,
        5,
        2,
        ((char*)&n)[0],
        ((char*)&n)[1],
        128
    };
    SendBytes(bytes, 6);
}

// You should redefine this function
__attribute__((weak)) void OnSortirPince() {}

void SendSwitchOne(unsigned char state) {
    char bytes[] = {
        129,
        31,
        1,
        state,
        128
    };
    SendBytes(bytes, 5);
}

void SendSwitchThree(unsigned char state) {
    char bytes[] = {
        129,
        35,
        1,
        state,
        128
    };
    SendBytes(bytes, 5);
}

void SendSwitchTwo(unsigned char state) {
    char bytes[] = {
        129,
        33,
        1,
        state,
        128
    };
    SendBytes(bytes, 5);
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
    if (id == 12) {
        OnBougiesHitBot();
        return 1;
    }
    if (id == 10) {
        OnBougiesHitTop();
        return 1;
    }
    if (id == 14) {
        OnBougiesOff();
        return 1;
    }
    if (id == 16) {
        OnBougiesOn();
        return 1;
    }
    if (id == 2) {
        OnChopperVerre();
        return 1;
    }
    if (id == 20) {
        OnGetEmergencyState();
        return 1;
    }
    if (id == 4) {
        OnGetNombreVerres();
        return 1;
    }
    if (id == 40) {
        OnGetStartLaisseState();
        return 1;
    }
    if (id == 3) {
        OnLacherVerres();
        return 1;
    }
    if (id == 1) {
        OnSortirPince();
        return 1;
    }
    return 0;
}

