
#ifndef GLOBALS_H
#define GLOBALS_H

#include <Windows.h>
#include <vector>

typedef void(*VoidCallback)(void);

//Keyboard and mouse states
struct KeyState {
	CHAR rgKeys[256];
};

struct MouseState {
    LONG lX;
    LONG lY;
    LONG lZ;
    BYTE rgButtons[4];
};


#endif