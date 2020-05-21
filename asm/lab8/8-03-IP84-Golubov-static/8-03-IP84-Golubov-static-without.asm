.686           
.model flat,stdcall          
option casemap:none

include \masm32\include\masm32rt.inc

includelib \masm32\labs\lab8\8-03-IP84-Golubov-dll-without-point.lib
IterWithoutPoint Proto 

.data         

    arr_a        dq     2.98,  2.97,  2.96,  0.79,   0.77;
    arr_b        dq     9.02,  9.02,  9.03,  9.02,  10.02;
    arr_c        dq     -3.0,  -3.0,   5.0,  5.25,    5.5;
    arr_d        dq      1.1,   2.2,   3.0,  4.99,  15.63;

    var_a        dq    ?;
    var_b        dq    ?;
    var_c        dq    ?;
    var_d        dq    ?;

    iter         dw    1;
    iterator     dw    -1; 
.code  

start:
finit
 startLoop:
        xor ebx, ebx;
        mov bx, iterator;
        inc bx;
	       fld arr_a[ebx * 8];
        fstp var_a;
        fld arr_b[ebx * 8];
        fstp var_b;
        fld arr_c[ebx * 8];
        fstp var_c;
        fld arr_d[ebx * 8];
        fstp var_d;
	    push offset var_a
		push offset var_b
		push offset var_c
		push offset var_d
		call IterWithoutPoint

		
	inc iter;
    inc iterator;
	cmp iterator, 4
    jnz startLoop
    
    invoke ExitProcess, NULL;
end start