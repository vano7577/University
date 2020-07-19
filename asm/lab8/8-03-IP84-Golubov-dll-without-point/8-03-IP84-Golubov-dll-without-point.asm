.686
.model flat, stdcall
option casemap:none

include \masm32\include\windows.inc      ;MB_OK,NULL 
include \masm32\include\kernel32.inc     ;ExitProcess 
include \masm32\include\user32.inc       ;wsprintf, MessageBox
include \masm32\include\masm32.inc       ;FloatToStr
include \masm32\include\fpu.inc          ;FpuFLtoA

includelib \masm32\lib\kernel32.lib      ;ExitProcess
includelib \masm32\lib\user32.lib        ;MessageBox
includelib \masm32\lib\masm32.lib        ;FloatToStr  
includelib \masm32\lib\fpu.lib           ;FpuFLtoA

.data         

	
    var_a        dq    ?;
    var_b        dq    ?;
    var_c        dq    ?;
    var_d        dq    ?;

    printRes     dq    ?; ГђвЂ™
    intermedRes1 DT    ?;
    intermedRes2 DT    ?;
    intermedRes3 DT    ?;
    intermedRes4 DT    ?;
    intermedRes5 DT    ?;
    intermedRes6 DT    ?;
    intermedRes7 DT    ?;
    RES 		 DT    ?;
           

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

    count        db    150 DUP(?);
.const	
    const1       dq    4.0;
    const2       dq    123.0;
    const3       dq    2.0; 
	const4       dq    0.0;
	
    head         db    "Лаб №8. Процедура без вказівки точки входу.", 0;   
	headerror 	 db    "Помилка!Лабораторна робота №8",0
	text1error   db    "Від'ємний вираз під знаком кореня", 0;
	text2error	 db    "Ділення на нуль", 0;
    headtask     db    "Task N", 0;
    head1        db    "Вхідні змінні:" , 0;
    head2        db    "Проміжні підрахунки:", 0;
    head3        db    "Остаточний вираз:", 0;
    head4        db    "(c + 4 *b - sqrt(123 * d)) / (1 - a / 2 ) =", 0;
    letter       db    "%s",13, "a = %s",13,"b = %s", 13, "c = %s", 13,"d = %s", 0;

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
 IterWithoutPoint proc 
        push ebp
		mov ebp, esp
	;prolog
		finit

		xor ecx, ecx
		xor edx, edx
		mov ecx, [ebp + 20]
		fld qword ptr [ecx];   
        fstp var_a;
		
		xor ecx, ecx
		mov ecx, [ebp + 12]
		mov edx, [ebp + 8]
		fld qword ptr [edx];
		fstp var_d;
	
		fld qword ptr [ecx];
		fstp var_c;

		xor ecx, ecx
		mov ecx, [ebp + 16]
		fld qword ptr [ecx];
		fstp var_b;

		fld var_a;
		fcom const3
		fstsw ax ;Г±Г®ГµГ°Г Г­ГҐГ­ГЁГҐ swr Гў Г°ГҐГЈГЁГ±ГІГ°ГҐ Г Гµ
        sahf
	    jz eror1
		xor eax, eax
		jmp starting1
		eror1:
		invoke wsprintf, addr count, addr headerror;
		invoke MessageBox,NULL, addr text1error, addr count, MB_OK;
		 pop ebp
	     ret 0
		 jmp ending
		 
		starting1:
		
        fstp var_a;
        
        fld var_d;
		fcom const4
		fstsw ax ;Г±Г®ГµГ°Г Г­ГҐГ­ГЁГҐ swr Гў Г°ГҐГЈГЁГ±ГІГ°ГҐ Г Гµ
        sahf
		jc eror2
		xor eax, eax
		jmp starting2
			eror2:
		invoke wsprintf, addr count, addr headerror;
        invoke MessageBox,NULL, addr text2error, addr count, MB_OK;
		pop ebp
	     ret 0
		 jmp ending
		
		starting2:

        fld var_b ;              ST(0) <- b
        fmul const1;            ST(0) <- 4*b
        fstp intermedRes1
        fld intermedRes1
        fadd var_c;             ST(0) <- c+4*b
        fstp intermedRes2
        fld intermedRes2
        fld var_d;              ST(1) <- c+4*b ST(0) <- d
        fmul const2;            ST(1) <- c+4*b ST(0) <- 123*d
        fstp intermedRes3
        fld intermedRes3
        fsqrt;                  ST(1) <- c+4*b ST(0) <- sqrt(123*d)
        fstp intermedRes4;
        fld intermedRes4
        fsub;                   ST(0) <- c+4*b - sqrt(123*d)
        fstp intermedRes5
        fld intermedRes5
        fld1;                   ST(1) <- c+4*b - sqrt(123*d), ST(0) <- 1
        fld var_a;              ST(2) <- c+4*b - sqrt(123*d), ST(1) <- 1, ST(0) <- a
        fld const3;             ST(3) <- c+4*b - sqrt(123*d), ST(2) <- 1, ST(1) <- a, ST(0) <-2
        fdiv;                   ST(2) <- c+4*b - sqrt(123*d), ST(1) <- 1, ST(0) <- a/2
        fstp intermedRes6
        fld intermedRes6
        fsub;                   ST(1) <- c+4*b - sqrt(123*d), ST(0) <- 1-a/2
        fstp intermedRes7
        fld intermedRes7
        fdiv;                   ST(0) <- (c+4*b- sqrt(123*d))/(1- a/2)
        fstp printRes;    DQ    printRes <- ST(0)
		
	wind proc
	   
		invoke wsprintf, addr count, addr head
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
		
		invoke wsprintf, addr lineBuff1,
						 addr letter,
						 addr head1,
						 addr buffa, 
						 addr buffb, 
						 addr buffc, 
						 addr buffd
        invoke wsprintf, addr lineBuff2,
                         addr format1,
						 addr head2,
                         addr buffb,
                         addr buff1 
        invoke wsprintf, addr lineBuff3,
                         addr format2,
                         addr buffc,
                         addr buffb,
                         addr buff2;
        invoke wsprintf, addr lineBuff4,
                         addr format3,
                         addr buffd,
                         addr buff3;
        invoke wsprintf, addr lineBuff5,
                         addr format4,
                         addr buffd,
                         addr buff4;
        invoke wsprintf, addr lineBuff6,
                         addr format5,
                         addr buffc,
                         addr buffb,
                         addr buffd,
                         addr buff5;
        invoke wsprintf, addr lineBuff7,
                         addr format6,
                         addr buffa,
                         addr buff6;
        invoke wsprintf, addr lineBuff8,
                         addr format7,
                         addr buffa,
                         addr buff7;
        invoke wsprintf, addr lineBuff9,
                         addr format8,
						 addr head3,
						 addr head4,
                         addr buffc,
                         addr buffb,
                         addr buffd,
                         addr buffa,
                         addr buff8                                                                                                   
        invoke wsprintf, addr buff,
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
		 pop ebp
	 ret 0
	wind endp

	call wind
	 jmp ending
	ending:
 IterWithoutPoint   endp
end 