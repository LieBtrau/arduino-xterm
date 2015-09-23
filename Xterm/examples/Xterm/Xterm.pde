/*
  Xterm - Library for printing Xterm codes to serial console.
  Created by Janis Jakaitis, August 8, 2010.
  Released into the public domain.
*/

#include <Xterm.h>
Xterm xterm=Xterm();

int i = 0;

void setup() {
  Serial.begin(9600);
  xterm.init();          // if you forget about this line you will see lots of cursor related garbage
}

void loop() {
for (i=0; i<100;i++)
  {
  xterm.print(1,1,"This is normal text",NORMAL); 
  xterm.print(1,30,i,NORMAL);
  xterm.print(2,1,"This is bold text",BOLD);
  xterm.print(2,30,i,BOLD);
  xterm.print(3,1,"This is underlined text",UNDERLINED);
  xterm.print(3,30,i,UNDERLINED);
  xterm.print(4,1,"This is blinking text",BLINK);
  xterm.print(4,30,i,BLINK);
  xterm.print(5,1,"This is inverted text",INVERSE);
  xterm.print(5,30,i,INVERSE);  
  }
}


