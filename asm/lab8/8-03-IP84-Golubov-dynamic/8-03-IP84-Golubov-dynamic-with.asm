.686           
.model flat,stdcall          
option casemap:none

include \masm32\include\masm32rt.inc


.const
libNameWith CHAR "8-03-IP84-Golubov-dll-with-point", 0h 
funcNameWith CHAR "IterWithPoint", 0h 
.data         

    arr_a        dq     2.98,  2.97,  2.96,  0.79,   0.77;
    arr_b        dq     9.02,  9.02,  9.03,  9.02,  10.02;
    arr_c        dq     -3.0,  -3.0,   5.0,  5.25,    5.5;
    arr_d        dq      1.1,   2.2,   3.0,  4.99,  15.63;
	
	count        db    50 DUP(?);
    var_a        dq    ?;
    var_b        dq    ?;
    var_c        dq    ?;
    var_d        dq    ?;
	buffc        db    25 DUP (?);
    head1        db    "Libruary not found!" , 0;
    iter         dw    1;
    iterator     dw    -1; 
	    head         db    "Лабораторна робота №8", 0;   
.data?

hLibWith DWORD ? 
lpFuncWith DWORD ? 
.code  

start:

xor eax, eax
invoke LoadLibrary, ADDR libNameWith
cmp eax,0
je @error
mov hLibWith,eax
invoke GetProcAddress, hLibWith, ADDR funcNameWith
mov lpFuncWith,eax
finit
    startLoop:
        xor ebx, ebx;
		;xor rax, rax;
        mov bx, iterator;
        inc bx;
		
		fld arr_d[ebx * 8];
		fstp var_d;
		fld arr_c[ebx * 8];
		fstp var_c;
		fld var_c
		fld arr_b[ebx * 8];
		fstp var_b;
	    fld arr_a[ebx * 8];   
        fstp var_a;
		
		push offset var_a
		push offset var_b
		push offset var_c
		push offset var_d
       	call [lpFuncWith]
		
	    inc iter;
        inc iterator;
	    cmp iterator, 4
    jnz startLoop

    jmp @exit
	@error:
	invoke MessageBox,NULL, addr head1, addr head, MB_OK;
	
	@exit:
	 invoke ExitProcess, NULL;
	
end start