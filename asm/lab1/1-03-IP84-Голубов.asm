.686

.MODEL flat, stdcall
option casemap:none

include C:\masm32\include\windows.inc     
include C:\masm32\include\kernel32.inc     
include C:\masm32\include\user32.inc       

includelib C:\masm32\lib\kernel32.lib     
includelib C:\masm32\lib\user32.lib      

.DATA

symbol db "12052001"

byte_A       db    12;
byte_m_A     db    -12;

word_A       dw    12;
word_m_A     dw    -12;
word_B       dw    1205;
word_m_B     dw    -1205;

short_A      dd    12;
short_m_A    dd    -12;
short_B      dd    1205;
short_m_B    dd    -1205;
short_C      dd    12052001;
short_m_C    dd    -12052001;

long_A       dq    12;
long_m_A     dq    -12;
long_B       dq    1205;
long_m_B     dq    -1205;
long_C       dq    12052001;
long_m_C     dq    -12052001;

single_D     dd   0.001;
single_m_D   dd    -0.001;

double_E     dq    0.143;
double_m_E   dq    -0.143;

ldouble_F    dt    1434.079;
ldouble_m_F  dt    -1434.079;
ldouble_m_G  dd    -111.636

head         db    "Lab1", 0;

formatA      db    "A = %x", 0;
formatB      db    "B = %x", 0;
formatC      db    "C = %x", 0;
formatD      db    "D = %x", 0;
formatE      db    "E = %x", 0;
formatF      db    "F = %x", 0;

buffA        db    15 DUP (?);
buffB        db    15 DUP (?);
buffC        db    15 DUP (?);
buffD        db    15 DUP (?);
buffE        db    15 DUP (?);
buffF        db    15 DUP (?);

format       db	   "%s",13,
                     "%s",13,
                     "%s",13,
                     "%s",13,
                     "%s",13,
                     "%s",0;

buff         db    90 DUP (?);

.CODE

start:
    invoke wsprintf, addr buffA, addr formatA, byte_A
    invoke wsprintf, addr buffB, addr formatB, word_B
    invoke wsprintf, addr buffC, addr formatC, short_C
    invoke wsprintf, addr buffD, addr formatD, single_D 
    invoke wsprintf, addr buffE, addr formatE, double_E
    invoke wsprintf, addr buffF, addr formatF, ldouble_F
	
    invoke wsprintf, addr buff,
                     addr format,
                     addr buffA,
                     addr buffB,
                     addr buffC,
                     addr buffD,
                     addr buffE,
                     addr buffF;

    invoke MessageBox,NULL, addr buff, addr head, MB_OK
    invoke ExitProcess, NULL 
    
end start
