.686           
.model flat,stdcall          
option casemap:none

include C:\masm32\include\windows.inc      ;MB_OK,NULL 
include C:\masm32\include\kernel32.inc     ;ExitProcess 
include C:\masm32\include\user32.inc       ;wsprintf, MessageBox
include C:\masm32\include\masm32.inc       ;FloatToStr
include C:\masm32\include\fpu.inc          ;FpuFLtoA

includelib C:\masm32\lib\kernel32.lib      ;ExitProcess
includelib C:\masm32\lib\user32.lib        ;MessageBox
includelib C:\masm32\lib\masm32.lib        ;FloatToStr  
includelib C:\masm32\lib\fpu.lib           ;FpuFLtoA

.data         

    arr_a        dq     2.98,  2.97,  2.96,  0.79,   0.77;
    arr_b        dq     9.02,  9.02,  9.03,  9.02,  10.02;
    arr_c        dq     -3.0,  -3.0,   5.0,  5.25,    5.5;
    arr_d        dq      1.1,   2.2,   3.0,  4.99,  15.63;
    
    var_a        dq    ?;
    var_b        dq    ?;
    var_c        dq    ?;
    var_d        dq    ?;
    
    printRes     dt    0; 
    iterator     dw    5;            

    buff1        db    25 DUP (?);
    buff2        db    25 DUP (?);
    buff3        db    25 DUP (?);
    buff4        db    25 DUP (?);
    buff5        db    25 DUP (?);
    buff         DW    250 DUP(?), 0;
    
    lineFormat   db    5 DUP("%s"), 0;
    format       db    "%s",13;
    lineBuff     DW    50 DUP(?), 0;

.const	
    const1       dq    4.0;
    const2       dq    123.0;
    const3       dq    2.0; 

    head         db    "Lab6", 0;   
    format1      db    "(%s + 4 * %s - sqrt(123 * %s)) / (1 - %s / 2) = %s ", 0; 

.code  
                    
start: 
    finit
    startLoop:
        xor eax, eax;
        xor ebx, ebx;

        mov bx, iterator;
        dec bx;
        fld arr_a[ebx * 8];
        fstp var_a;
        fld arr_b[ebx * 8];
        fstp var_b;
        fld arr_c[ebx * 8];
        fstp var_c;
        fld arr_d[ebx * 8];
        fstp var_d;

        fld var_b;              ST(0) <- b
        fmul const1;            ST(0) <- 4*b
        fadd var_c;             ST(0) <- c+4*b
        fld var_d;              ST(1) <- c+4*b ST(0) <- d
        fmul const2;            ST(1) <- c+4*b ST(0) <- 123*d
        fsqrt;                  ST(1) <- c+4*b ST(0) <- sqrt(123*d)
        fsub;                   ST(0) <- c+4*b - sqrt(123*d)
        fld1;                   ST(1) <- c+4*b - sqrt(123*d)
        fld var_a;              ST(2) <- c+4*b - sqrt(123*d), ST(1) <- 1, ST(0) <- a
        fld const3;             ST(3) <- c+4*b - sqrt(123*d), ST(2) <- 1, ST(1) <- a, ST(0) <-2
        fdiv;                   ST(2) <- c+4*b - sqrt(123*d), ST(1) <- 1, ST(0) <- a/2
        fsub;                   ST(1) <- c+4*b - sqrt(123*d), ST(0) <- 1-a/2
        fdiv;                   ST(0) <- (c+4*b- sqrt(123*d))/(1- a/2)
        fstp printRes;          printRes <- ST(0)
        
        invoke FloatToStr, var_c, addr buff1;
        invoke FloatToStr, var_b, addr buff2;
        invoke FloatToStr, var_d, addr buff3;
        invoke FloatToStr, var_a, addr buff4;
        invoke FpuFLtoA,offset  printRes,8,offset  buff5, SRC1_REAL
        invoke wsprintf, addr lineBuff,
                         addr format1,
                         addr buff1,
                         addr buff2,
                         addr buff3,
                         addr buff4,
                         addr buff5;
        invoke wsprintf, addr buff, addr format, addr buff, addr lineBuff;                                                               
    dec iterator;
    jnz startLoop
        
    invoke MessageBox,NULL, addr buff, addr head, MB_OK;
    invoke ExitProcess, NULL;

end start  