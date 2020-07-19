 .386           
.model flat,stdcall          
option casemap:none

include C:\masm32\include\windows.inc 
include C:\masm32\include\kernel32.inc
include C:\masm32\include\user32.inc  

includelib C:\masm32\lib\kernel32.lib
includelib C:\masm32\lib\user32.lib

.data          

    arr_a        dd    2, 2, 2, 16, 12 
    arr_c        dd    2, 3, 8, 18, 16;
    arr_d        dd    -1, -3, 2, 6, 8;

    var_a        dd    ?;
    var_c        dd    ?;
    var_d        dd    ?;
    bu1          dd    ?;
    iterator     dd    5;
    
    const1       dd    3;
    const2       dd    2;    
    const3       dd    5;                   

    head         db    "Lab5", 0;

    format1      db    "(%u / ", 0;
    format2p     db    "%u + 3 * ", 0;
    format2m     db    "(-%u) + 3 * ", 0;
    format3      db    "%u / 2) / (", 0;
    format4      db    "%u - ", 0;
    format5      db    "%d + 1)) / 2", 0;
    format7      db    "%d + 1)) * 5", 0;
    format6      db    " = %u", 0;

    buff1        db    15 DUP (?);
    buff2        db    15 DUP (?);
    buff3        db    15 DUP (?);
    buff4        db    15 DUP (?);
    buff5        db    15 DUP (?);
    buff6        db    15 DUP (?);
    
    lineFormat   db    6 DUP("%s"), 0;
    format       db    "%s",13;
    lineBuff     db    50 DUP(?), 0;
    buff         db    ?;

.code  
                    
start: 
   xor ebx, ebx;
    startLoop:
        mov ebx, iterator;
        dec ebx;
        mov eax, arr_a[ebx * 4];
        mov var_a, eax;
        
        mov eax, arr_c[ebx * 4];
        mov var_c, eax;
       
        mov eax, arr_d[ebx * 4];
        mov var_d, eax;
        
        xor eax, eax
        mov eax, var_a;       
        mul const1;    3*a       
        div const2;    3*a/2      
        mov bu1, eax ;bu1=3*a/2

        add var_d, 0;
        ; sign check
        js negative
            invoke wsprintf, addr buff2, addr format2p, var_d;
            mov edx, 0;
            mov eax, var_c;
            mov ecx, var_d;
            div ecx;       c/d            
            add eax, bu1; c/d+3*a/2
            jmp positive    
        negative:
            neg var_d
            invoke wsprintf, addr buff2, addr format2m, var_d;
            mov edx, 0;
            mov eax, var_c;
            mov ecx, var_d;
            div ecx;       c/d              
            sub bu1, eax;   c/d+3*a/2
            ; sub because var_d is neg
            mov eax, bu1 ; eax=c/d+3*a/2  
        positive:
        xor ecx, ecx
        xor edx, edx

        mov ecx, var_c
        inc ecx; ecx = c+1
        mov edx, var_a

        sub ecx, edx ; ecx = c-d+1

        mov edx, 0
        mov eax, eax
        mov ecx, ecx
        div ecx;eax=(c/d+3*a/2)/(c-d+1)
        test eax, 1;parity check

        jz evenNumb
        jnz unevenNumb
        unevenNumb:
            xor ecx, ecx
            mov eax, eax;
            mov ecx, const3; const3=5
            mul ecx; ecx=ecx*5
            invoke wsprintf, addr buff6, addr format6, eax;
            invoke wsprintf, addr buff5, addr format7, var_a;
            jmp Numb
        evenNumb: 
            xor ecx, ecx
            mov edx, 0
            mov eax, eax
            mov ecx, const2; const2=2
            div ecx; ecx=ecx/2
            invoke wsprintf, addr buff6, addr format6, eax;
            invoke wsprintf, addr buff5, addr format5, var_a;                    

        Numb:
        invoke wsprintf, addr buff1, addr format1, var_c;
        invoke wsprintf, addr buff3, addr format3, var_a;
        invoke wsprintf, addr buff4, addr format4, var_c;

        invoke wsprintf, addr lineBuff,
                         addr lineFormat,
                         addr buff1,
                         addr buff2,
                         addr buff3,
                         addr buff4,
                         addr buff5,
                         addr buff6;
        
        invoke wsprintf, addr buff, addr format, addr buff, addr lineBuff;
                                                                 
    dec iterator;
    jnz startLoop
        
    invoke MessageBox,NULL, addr buff, addr head, MB_OK;
    invoke ExitProcess, NULL;

end start  