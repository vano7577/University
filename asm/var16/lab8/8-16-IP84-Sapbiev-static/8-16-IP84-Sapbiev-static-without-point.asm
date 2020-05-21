.686           
.model flat,stdcall          
option casemap:none

include \masm32\include\masm32rt.inc

includelib \masm32\labs\labs8\8-16-IP84-Sapbiev-without.lib
WithoutPoint Proto 
.data         

    arr_a        dq     0.78,  1.78,  0.75,  1.75,  1.75;
    arr_b        dq     10.02,  10.03,  10.02,  -0.78,   -0.78;
    arr_c        dq     5.5,    4.5,    4.5,   5.5,  3.5;
    arr_d        dq      4.01,   5.01,  4.01,   15.01,  0.51;

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
		call WithoutPoint
		
	inc iter;
    inc iterator;
	cmp iterator, 4
    jnz startLoop
    
    invoke ExitProcess, NULL;
end start