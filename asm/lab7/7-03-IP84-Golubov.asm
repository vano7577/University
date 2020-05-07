.686           
.model flat,stdcall          
option casemap:none

include \masm32\include\windows.inc      ;MB_OK,NULL 
include \masm32\include\kernel32.inc     ;ExitProcess 
include \masm32\include\user32.inc       ;wsprintf, MessageBox
include \masm32\include\masm32.inc       ;FloatToStr
include \masm32\include\fpu.inc          ;FpuFLtoA
include \masm32\include\msvcrt.inc  

includelib \masm32\lib\kernel32.lib      ;ExitProcess
includelib \masm32\lib\user32.lib        ;MessageBox
includelib \masm32\lib\masm32.lib        ;FloatToStr  
includelib \masm32\lib\fpu.lib           ;FpuFLtoA
includelib \masm32\lib\msvcrt.lib      
 

extrn three@0:near
public var_a, const3, intermedRes6, intermedRes7
.data         

    arr_a        dq     2.98,  2.97,  2.96,  0.79,   0.77;
    arr_b        dq     9.02,  9.02,  9.03,  9.02,  10.02;
    arr_c        dq     -3.0,  -3.0,   5.0,  5.25,    5.5;
    arr_d        dq      1.1,   2.2,   3.0,  4.99,  15.63;
    
    var_a        dq    ?;
    var_b        dq    ?;
    var_c        dq    ?;
    var_d        dq    ?;

    printRes     dq    ?; В
    intermedRes1 DT    ?;
    intermedRes2 DT    ?;
    intermedRes3 DT    ?;
    intermedRes4 DT    ?;
    intermedRes5 DT    ?;
    intermedRes6 DT    ?;
    intermedRes7 DT    ?;
    RES 		 DT    ?;
    iter         dw   1;
    iterator     dw    -1;            

    buffa        db    25 DUP (?);
    buffb        db    25 DUP (?);
    buffc        db    25 DUP (?);
    buffd        db    25 DUP (?);
    buff8        db    250 DUP (?);
    buff1        db    250 DUP (?);
    buff2        db    250 DUP (?);
    buff3        db    250 DUP (?);
    buff4        db    250 DUP (?);
    buff5        db    250 DUP (?);
    buff6        db    250 DUP (?);
    buff7        db    250 DUP (?);
    buff9        db    250 DUP (?);

    buff         db    1000 DUP(?), 0;
    mainbuff     db    1000 DUP(?), 0;
    lineFormat   db    5 DUP("%s"), 0;
    format       db    "%s",13,"%s",13, "%s",13, "%s",13, "%s",13, "%s",13, "%s",13, "%s",13
    mainformat   db    "%s",13
    li           DW    50 DUP(?), 0;
	lineBuff1    DW    50 DUP(?), 0;
    lineBuff2    DW    50 DUP(?), 0;
    lineBuff3    DW    50 DUP(?), 0;
    lineBuff4    DW    50 DUP(?), 0;
    lineBuff5    DW    50 DUP(?), 0;
    lineBuff6    DW    50 DUP(?), 0;
    lineBuff7    DW    50 DUP(?), 0;
    lineBuff8    DW    50 DUP(?), 0;
    lineBuff9    DW    100 DUP(?), 0;

	count        db    50 DUP(?);
.const	
    const1       dq    4.0;
    const2       dq    123.0;
    const3       dq    2.0; 
	const4       dq    0.0;
	
    head         db    "Лабораторна робота №7 Вираз №%d", 0;   
	headerror 	 db    "Помилка!Лабораторна робота №7 Вираз №%d",0
	text1error   db    "Від'ємний вираз під знаком кореня", 0;
	text2error	 db    "Ділення на нуль", 0;
    headtask     db    "Task N", 0;
	head1        db    "Вхідні змінні:" , 0;
    head2        db    "Проміжні підрахунки:", 0;
	head3        db    "Остаточний вираз:", 0;
	head4 	     db    "(c + 4 *b - sqrt(123 * d)) / (1 - a / 2 ) =", 0;
	letter	     db    "%s",13, "a = %s",13,"b = %s", 13, "c = %s", 13,"d = %s", 0;

    forma        db    "%s", 0;
    format1      db    "%s",13, "4 * b = 4 * %s = %s", 0
    format2      db    "c + 4 * b = %s + 4 * %s = %s", 0;
    format3      db    "123 * d = 123 * %s = %s", 0;
    format4      db    "sqrt(123 * d) = sqrt(123 * %s) = %s", 0;
    format5      db    "c + 4 * b - sqrt(123 * d) = %s + 4 * %s - sqrt(123 * %s) = %s", 0;
    format6      db    "a / 2 = %s / 2 = %s", 0;
    format7      db    "1 - a / 2 = 1 - %s / 2 = %s", 0;
    format8      db    "%s",13, "%s",13,"= (%s + 4 * %s - sqrt(123 * %s)) / (1 - %s / 2) = %s ", 0; 

.code  
	
	first proc
		fld qword ptr[eax];	    ST(0) <- 4
		fld qword ptr[edx];		ST(0) <- 4 ST(1) <- b
        fmul ;            ST(0) <- 4*b
        fstp intermedRes1; проміжні результати ( не впливає на результат обрахунків, не є параметром обрахунку і результатом)
        fld intermedRes1
		fld qword ptr[ecx]; ST(0) <- 4*b ST(1) <- c
        fadd ;             ST(0) <- c+4*b
        fstp intermedRes2; проміжні результати ( не впливає на результат обрахунків, не є параметром обрахунку і результатом)
		fld intermedRes2
        ret
	first endp
	
	second proc
	;prolog
	push ebp
	mov ebp, esp
	;prolog
	xor eax, eax
	mov eax, [ebp + 12]
	xor ecx, ecx
	mov ecx, [ebp + 8]
		fld qword ptr [eax];  ST(0) <- c+4*b ST(1) <- d
        fld qword ptr [ecx];  ST(0) <- c+4*b ST(1) <- d ST(2) <- 123
		fmul ;            ST(0) <- c+4*b ST(1) <- 123*d
        fstp intermedRes3; проміжні результати ( не впливає на результат обрахунків, не є параметром обрахунку і результатом)
        fld intermedRes3
        fsqrt;                  ST(0) <- c+4*b ST(1) <- sqrt(123*d)
        fstp intermedRes4; проміжні результати ( не впливає на результат обрахунків, не є параметром обрахунку і результатом)
        fld intermedRes4
		fsub;                   ST(0) <- c+4*b - sqrt(123*d)
        fstp intermedRes5; проміжні результати ( не впливає на результат обрахунків, не є параметром обрахунку і результатом)
        fld intermedRes5
	;epilog
		pop ebp
	;epilog
		ret 8
	second endp
	
start: 
    finit
    startLoop:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        xor ebx, ebx;
		xor eax, eax
        mov bx, iterator;
        inc bx;
        
		fld arr_a[ebx * 8];
		fcom const3
		fstsw ax ;сохранение swr в регистре ах
        sahf
	    jz eror1
		xor eax, eax
		jmp starting1
		eror1:
		invoke wsprintf, addr count, addr headerror, iter;
		invoke MessageBox,NULL, addr text1error, addr count, MB_OK;
		jmp ending
		
		starting1:
		
        fstp var_a;
        fld arr_b[ebx * 8];
        fstp var_b;
        fld arr_c[ebx * 8];
        fstp var_c;
        fld arr_d[ebx * 8];
		fcom const4
		fstsw ax ;сохранение swr в регистре ах
        sahf
		jc eror2
		xor eax, eax
		jmp starting2
			eror2:
		invoke wsprintf, addr count, addr headerror, iter;
        invoke MessageBox,NULL, addr text2error, addr count, MB_OK;
		jmp ending
		
		starting2:
        fstp var_d;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        xor eax, eax
		xor ecx, ecx
		xor edx, edx
		mov eax, offset const1
		mov ecx, offset var_c
		mov edx, offset var_b
		call first;
		
		push offset var_d
		push offset const2
		call second;
		
		call three@0
		fstp intermedRes6; проміжні результати (не впливає на обрахунки, не є параметром обрахунку і результатом)
		fstp intermedRes7; проміжні результати (не впливає на обрахунки, не є параметром обрахунку і результатом)
		fld intermedRes7
        fdiv;                   ST(0) <- (c+4*b- sqrt(123*d))/(1- a/2)
        fstp printRes;    DQ    printRes <- ST(0)
		
        invoke crt_sprintf, addr count, addr head, iter;
        invoke FloatToStr, var_c, addr buffc;
        invoke FloatToStr, var_b, addr buffb;
        invoke FloatToStr, var_d, addr buffd;
        invoke FloatToStr, var_a, addr buffa;
        invoke FloatToStr, printRes, addr buff8;   
       
        invoke FpuFLtoA,offset  intermedRes1, 10,offset  buff1, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes2, 10,offset  buff2, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes3, 10,offset  buff3, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes4, 10,offset  buff4, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes5, 10,offset  buff5, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes6, 10,offset  buff6, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes7, 10,offset  buff7, SRC1_REAL   
		
		invoke crt_sprintf, addr lineBuff1,
						 addr letter,
						 addr head1,
						 addr buffa, 
						 addr buffb, 
						 addr buffc, 
						 addr buffd
        invoke crt_sprintf, addr lineBuff2,
                         addr format1,
						 addr head2,
                         addr buffb,
                         addr buff1 
        invoke crt_sprintf, addr lineBuff3,
                         addr format2,
                         addr buffc,
                         addr buffb,
                         addr buff2;
        invoke crt_sprintf, addr lineBuff4,
                         addr format3,
                         addr buffd,
                         addr buff3;
        invoke crt_sprintf, addr lineBuff5,
                         addr format4,
                         addr buffd,
                         addr buff4;
        invoke crt_sprintf, addr lineBuff6,
                         addr format5,
                         addr buffc,
                         addr buffb,
                         addr buffd,
                         addr buff5;
        invoke crt_sprintf, addr lineBuff7,
                         addr format6,
                         addr buffa,
                         addr buff6;
        invoke crt_sprintf, addr lineBuff8,
                         addr format7,
                         addr buffa,
                         addr buff7;
        invoke crt_sprintf, addr lineBuff9,
                         addr format8,
						 addr head3,
						 addr head4,
                         addr buffc,
                         addr buffb,
                         addr buffd,
                         addr buffa,
                         addr buff8                                                                                                   
        invoke crt_sprintf, addr buff,
                         addr format,
						 addr lineBuff1,
                         addr lineBuff2,
                         addr lineBuff3,
                         addr lineBuff4,
                         addr lineBuff5,
                         addr lineBuff6,
                         addr lineBuff7,
                         addr lineBuff8,
                         addr lineBuff9;  
  
     invoke MessageBox,NULL, addr buff, addr count, MB_OK;
	jmp ending
	ending:
    inc iter;
    inc iterator;
	cmp iterator, 4
    jnz startLoop
        
    invoke ExitProcess, NULL;	

end start  
