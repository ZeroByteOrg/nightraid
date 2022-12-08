#include <conio.h>
#include <cbm.h>

extern char __fastcall__ getmouse();

unsigned char mbut;
unsigned char dx;
unsigned char dy;

static const char sprdat[] = {
  1,0,0,0,0,0,0,1,
  0,1,0,0,0,0,1,0,
  0,0,1,0,0,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,1,0,0,
  0,1,0,0,0,0,1,0,
  1,0,0,0,0,0,0,1,
  0,0,0,0,0,0,0,0
};

void main() {
  char i;
  while(kbhit()) cgetc();
  VERA.address = 0;
  VERA.address_hi = 1 | VERA_INC_1;
  for (i=0 ; i<64 ; i++) VERA.data0 = sprdat[i];
  clrscr();
  VERA.display.video = 0x61;
  VERA.address = 0xfc00;
  VERA.data0 = (0x10000  >>  5) & 0xff;
  VERA.data0 = ((0x10000 >> 13) & 0x0f) | (1<<7);
  VERA.data0 = 320 & 0xff;
  VERA.data0 = 320 >> 8;
  VERA.data0 = 240;
  VERA.data0 = 0;
  VERA.data0 = 3 << 2;
  VERA.data0 = 0;

  while(!kbhit()) {
    waitvsync();
    getmouse();
    gotoxy(0,0);
    cprintf("%02x %d %d %d\n\r",mbut,mbut&1,(mbut>>2)&1,(mbut>>1)&1);
    cprintf("%02x\n\r",dx);
    cprintf("%02x",dy);
  }
  VERA.display.video = 0x21;
}
