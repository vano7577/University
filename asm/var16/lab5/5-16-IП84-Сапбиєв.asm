.386           
.model flat,stdcall          
option casemap:none

include C:\masm32\include\windows.inc 
include C:\masm32\include\kernel32.inc
include C:\masm32\include\user32.inc  

includelib C:\masm32\lib\kernel32.lib
includelib C:\masm32\lib\user32.lib

.data          

    arr_a        dd    4, 8, 4, 4, 16
	arr_b        dd    2, 3, -8, 4, 3;
    arr_c        dd    3, 15, 3, 3, 16;
    

    var_a        dd    ?;
    var_c        dd    ?;
    var_b        dd    ?;
    buffer1          dd    ?;
	buffer2          dd    ?;
	buffer3          dd    ?;
    iterator     dd    5;
    
    const1       dd    4;
    const2       dd    2;    
    const3       dd    5;                   

    head         db    "Ћаб 5. —апбиЇв", 0;

    format1p      db    "(%u ", 0;
	format1m     db    "(-%u ", 0;
	format2p     db    "+ %u * ", 0;
    format2m     db    "- %u * ", 0;
	format8      db     "%u ",0;
    format3      db    "- %u / 4) / (", 0;
    format4p      db    "%u *", 0;
	format4m      db    "-%u *", 0;
    format5      db    "%d - 1)) / 2", 0;
    format7      db    "%d - 1)) * 5", 0;
    format6      db    " = %u", 0;

    buff1        db    15 DUP (?);
    buff2        db    15 DUP (?);
    buff3        db    15 DUP (?);
    buff4        db    15 DUP (?);
    buff5        db    15 DUP (?);
    buff6        db    15 DUP (?);
    buff7        db    15 DUP (?);
    lineFormat   db    7 DUP("%s"), 0;
    format       db    "%s",13;
    lineBuff     db    150 DUP(?), 0;
    buff         db    ?;

.code  
                    
start: 
   xor ebx, ebx;
    startLoop:
        mov ebx, iterator;
        dec ebx;
        mov eax, arr_a[ebx * 4];
        mov var_a, eax;
        
		mov eax, arr_b[ebx * 4];
        mov var_b, eax;
		
        mov eax, arr_c[ebx * 4];
        mov var_c, eax;
          
        add var_b, 0;
        ; перев≥рка на знак
        js negative
		     invoke wsprintf, addr buff1, addr format1p, var_b
		     invoke wsprintf, addr buff2, addr format2p, var_b
			 invoke wsprintf, addr buff4, addr format4p, var_a
		mov edx, 0;
            mov eax, var_c;
            mov ecx, var_b;
            mul ecx;                 
            add eax, var_b; 
		  mov buffer1, eax 

        xor eax, eax
		xor ecx, ecx
        xor edx, edx

        mov edx, 0
        mov eax, var_a;
        mov ecx, const1
        div ecx;
	    sub buffer1, eax	
		xor eax, eax
		xor ecx, ecx
        xor edx, edx
		
        mov eax, var_b
		mov ecx, var_a
		mul ecx
        dec eax; 
		mov buffer3, eax  

            jmp positive    
        negative:
            neg var_b
			invoke wsprintf, addr buff1, addr format1m, var_b
			 invoke wsprintf, addr buff2, addr format2m, var_b
			 invoke wsprintf, addr buff4, addr format4m, var_a
				mov edx, 0;
            mov eax, var_c;
            mov ecx, var_b;
            mul ecx;                
            add eax, var_b;
		  mov buffer1, eax ;

        xor eax, eax
		xor ecx, ecx
        xor edx, edx
 
           
        mov edx, 0
        mov eax, var_a; 
        mov ecx, const1
        div ecx;
	    add buffer1, eax	
		xor eax, eax
		xor ecx, ecx
        xor edx, edx
		
        mov eax, var_b
		mov ecx, var_a
		mul ecx
        inc eax; ecx = c+1
		mov buffer3, eax
		
        positive:
        mov edx, 0
        mov eax, buffer1;(b + c*b - a/4)
        mov ecx, buffer3; (a*b - 1)
        div ecx;
		 mov buffer2, eax; 

        test eax, 1;перев≥рка на парн≥сть

        jz evenNumb
        jnz unevenNumb
        unevenNumb:
            xor ecx, ecx
            mov eax, eax;
            mov ecx, const3; const3=5
            mul ecx; ecx=ecx*5
            invoke wsprintf, addr buff6, addr format6, eax;
            invoke wsprintf, addr buff5, addr format7, var_b
            jmp Numb
        evenNumb: 
            xor ecx, ecx
            mov edx, 0
            mov eax, eax
            mov ecx, const2; const2=2
            div ecx; ecx=ecx/2
            invoke wsprintf, addr buff6, addr format6, eax;
            invoke wsprintf, addr buff5, addr format5, var_b;                    

        Numb:
        
		invoke wsprintf, addr buff3, addr format3, var_a;
		invoke wsprintf, addr buff7, addr format8, var_c;
        invoke wsprintf, addr lineBuff,
                         addr lineFormat,
                         addr buff1,
                         addr buff2,
						 addr buff7,
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