/*
  Xterm.cpp - Library for printing Xterm codes.
  Created by Janis Jakaitis, August 8, 2010.
  Released into the public domain.
  Data from http://invisible-island.net/xterm/ctlseqs/ctlseqs.html
  http://ascii-table.com/ansi-escape-sequences-vt-100.php
*/


#include "WProgram.h"
#include "Xterm.h"

Xterm::Xterm(Stream* stream): _stream(stream){
}

bool Xterm::init()
{
    byte type;
    if(!getTerminalType(type))
    {
        return false;
    }
    _stream->print("\eSP F");  	// tell to use 7-bit control codes (will be echoed back)
    _stream->print("\e[?25l"); 	// hide cursor
    _stream->print("\e[?12l");	// disable cursor highlighting
    clear(); 	// clear entire screen
    return true;
}

//\e[?62;3c    //VT220 with ReGIS graphics (response from GTKTerm)
//\e[?1;2c     //VT100 with Advanced Video Option (response from minicom)
bool Xterm::getTerminalType(byte& terminalType)
{
    while(_stream->available()>0)_stream->read();       //clear input buffer
    _stream->print("\e[c");                             // request attributes from terminal
     String response=_stream->readStringUntil('c');
    if(response.length()==0 || response.charAt(0)!='\e' ||
            response.charAt(1)!='[' || response.charAt(2)!='?')
    {
        return false;
    }
    byte semicolonPos=response.indexOf(';');
    if(semicolonPos<0){
        return false;
    }
    response=response.substring(3,semicolonPos);
    terminalType=response.toInt();
}

void Xterm::clear()
{
    _stream->print("\e[2J"); // clear screen
}

void Xterm::setCursorPos(int row, int col){
    _stream->print("\e[");  	// CSI (control sequence initializer)
    _stream->print(row);
    _stream->print(";");
    _stream->print(col);
    _stream->print("f");
}

void Xterm::setForegroundColor(COLOR c)
{
    if(c>=BLACK && c!=DEFAULT){
        setCharacterAttributes(c+30);
    }
}

void Xterm::setBackgroundColor(COLOR c)
{
    if(c>=BLACK && c!=DEFAULT){
        setCharacterAttributes(c+40);
    }

}

void Xterm::setCursorType(CHARACTERTYPE m){
    switch (m) // m = mode
    {
    case 1: // Bold
    case 4: // Underlined
    case 5: // Blink
    case 7: // Inverse
        setCharacterAttributes(m);
        break;
    default: // Normal
        setCharacterAttributes(0);

    }
}

void Xterm::setCharacterAttributes(byte m){
    String cmd="\e[";
    cmd+= String(m);
    cmd+='m';
    _stream->print(cmd);
}
