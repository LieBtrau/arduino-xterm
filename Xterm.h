/*
  Xterm.h - Library for printing Xterm codes.
  Created by Janis Jakaitis, August 8, 2010.
  Released into the public domain.

  Linux: use: minicom -d /dev/ttyACM0 -w -c on
*/


#ifndef Xterm_h
#define Xterm_h

#include "WProgram.h"

class Xterm
{
public:
    typedef enum{
        NORMAL=0,
        BOLD=1,
        UNDERLINED=4,
        BLINK=5,
        INVERSE=7,
    }CHARACTERTYPE;
    typedef enum{
        BLACK=0,
        RED=1,
        GREEN=2,
        YELLOW=3,
        BLUE=4,
        MAGENTA=5,
        CYAN=6,
        WHITE=7,
        DEFAULT=9
    }COLOR;
    Xterm(Stream* stream);
    bool init();
    void print(char);
    void print(uint8_t);
    void print(int);
    void print(unsigned int);
    void print(long);
    void print(unsigned long);
    void setCursorPos(int row, int col);
    void setCursorType(CHARACTERTYPE m);
    void setForegroundColor(COLOR c);
    void setBackgroundColor(COLOR c);
    bool getTerminalType(byte& terminalType);
    template<typename T> void print(int row, int col, T &t, CHARACTERTYPE m)
    {
        setCursorType(m);
        setCursorPos(row, col);
        _stream->print(t);          // text
    }
    void clear();
private:
    void setCharacterAttributes(byte m);
    Stream* _stream;
};

#endif

