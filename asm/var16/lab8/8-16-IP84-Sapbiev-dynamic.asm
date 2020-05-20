.686           
.model flat,stdcall          
option casemap:none

include \masm32\include\masm32rt.inc

.const
libNameWithoutPoint CHAR "8-16-IP84-Sapbiev-without", 0h 
funcNameWithoutPoint CHAR "WithoutPoint", 0h 
libNameWithPoint CHAR "8-16-IP84-Sapbiev-with", 0h 
funcNameWithPoint CHAR "WithPoint", 0h 
.data         

    arr_a        dq     0.78,  1.78,  0.75,  1.75,  1.75;
    arr_b        dq     10.02,  10.03,  10.02,  -0.78,   -0.78;
    arr_c        dq     5.5,    4.5,    4.5,   5.5,  3.5;
    arr_d        dq      4.01,   5.01,  4.01,   15.01,  0.51;
	
	count        db    50 DUP(?);
    var_a        dq    ?;
    var_b        dq    ?;
    var_c        dq    ?;
    var_d        dq    ?;
	buffc        db    25 DUP (?);
    head1        db    "Бібліотека не знайдена!" , 0;
    iter         dw    1;
    iterator     dw    -1; 
	    head         db    "Лаб №8", 0;   
.data?
hLibWithoutPoint DWORD ? 
lpFuncWithoutPoint DWORD ? 
hLibWithPoint DWORD ? 
lpFuncWithPoint DWORD ? 
.code  

start:
xor eax, eax
invoke LoadLibrary, ADDR libNameWithoutPoint
cmp eax,0
je @error
mov hLibWithoutPoint,eax
invoke GetProcAddress, hLibWithoutPoint, ADDR funcNameWithoutPoint
mov lpFuncWithoutPoint,eax

xor eax, eax
invoke LoadLibrary, ADDR libNameWithPoint
cmp eax,0
je @error
mov hLibWithPoint,eax
invoke GetProcAddress, hLibWithPoint, ADDR funcNameWithPoint
mov lpFuncWithPoint,eax
finit
    startLoop:
        xor ebx, ebx;
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
       	call [lpFuncWithoutPoint]
		
		push offset var_a
		push offset var_b
		push offset var_c
		push offset var_d
       	call [lpFuncWithPoint]
		
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