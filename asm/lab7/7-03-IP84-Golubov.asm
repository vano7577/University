.686           
.model flat,stdcall          
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
 
        ;розкоментувати для виводу проміжних результатів
extrn third@0:near
;public var_a, var3, temp6, temp7
public var_a, var3; закоментувати для виводу проміжних результатів
.data         
	    
    var_a        DQ    ?;
    var_b        DQ    ?;
    var_c        DQ    ?;
    var_d        DQ    ?;
    Res    	     DQ    ?;
    printRes     DQ    ?;
    temp1		 DT    ?;
    temp2 		 DT    ?;
    temp3		 DT    ?;
    temp4		 DT    ?;
    temp5		 DT    ?;
    temp6		 DT    ?;
    temp7		 DT    ?;
    RES 		 DT    ?;
    it           DW    1;
    iter         DW    0;            

    arr_a        DQ     3.05,  1.92,  2.98,  2.79,   0.77;
    arr_b        DQ     8.10,  9.50,  4.01,  9.05,   5.0;
    arr_c        DQ     -1.1,  3.1,   1.0,  -3.26,    5.5;
    arr_d        DQ      2.2,   1.3,   2.1,  1.99,  10.63;

    buffa        DB    25 DUP (?);
    buffb        DB    25 DUP (?);
    buffc        DB    25 DUP (?);
    buffd        DB    25 DUP (?);
    buff8        DB    250 DUP (?);
    buff1        DB    250 DUP (?);
    buff2        DB    250 DUP (?);
    buff3        DB    250 DUP (?);
    buff4        DB    250 DUP (?);
    buff5        DB    250 DUP (?);
    buff6        DB    250 DUP (?);
    buff7        DB    250 DUP (?);
    buff9        DB    250 DUP (?);

    buff           DB    1000 DUP(?), 0;
    mainbuff       DB    1000 DUP(?), 0;
    linetemplate   DB    5 DUP("%s"), 0;
    ;template       DB    "%s",13,"%s",13, "%s",13, "%s",13, "%s",13, "%s",13, "%s",13, "%s",13
	template       DB    "%s",13; закоментувати для виводу проміжних результатів
    maintemplate   DB    "%s",13
	
    li       DW    50 DUP(?), 0;
	line1    DW    50 DUP(?), 0;
    line2    DW    50 DUP(?), 0;
    line3    DW    50 DUP(?), 0;
    line4    DW    50 DUP(?), 0;
    line5    DW    50 DUP(?), 0;
    line6    DW    50 DUP(?), 0;
    line7    DW    50 DUP(?), 0;
    line8    DW    50 DUP(?), 0;
    line9    DW    100 DUP(?), 0;
	counter  DB    50 DUP(?);
.const	
    var1     DQ    4.0;
    var2     DQ    123.0;
    var3     DQ    2.0; 
	var4     DQ    0.0;
	
    head     DB    "Лаб. робота №7 Голубов Вираз №%d", 0;  
	headerr	 DB    "Помилка!Лаб. робота №7 Голубов Вираз №%d",0
	text2	 DB    "Від'ємний вираз під знаком кореня! Виправте параметр d", 0;
	text1	 DB    "Ділення на нуль! Виправте параметр a", 0;
    headtask DB    "N", 0;
	head1    DB    "Початкові параметри:" , 0;
    head2    DB    "Проміжні підрахунки:", 0;
	head3    DB    "Результат підрахунків:", 0;
	head4 	 DB    "(c + 4 *b - sqrt(123 * d)) / (1 - a / 2 ) =", 0;
	letter	 DB    "%s",13, "a = %s",13,"b = %s", 13, "c = %s", 13,"d = %s", 0;

    formate        DB    "%s", 0;
    template1      DB    "%s",13, "1. 4 * b = 4 * %s = %s", 0
    template2      DB    "2. c + 4 * b = %s + 4 * %s = %s", 0;
    template3      DB    "3. 123 * d = 123 * %s = %s", 0;
    template4      DB    "4. sqrt(123 * d) = sqrt(123 * %s) = %s", 0;
    template5      DB    "5. c + 4 * b - sqrt(123 * d) = %s + 4 * %s - sqrt(123 * %s) = %s", 0;
    template6      DB    "6. a / 2 = %s / 2 = %s", 0;
    template7      DB    "7. 1 - a / 2 = 1 - %s / 2 = %s", 0;
    template8      DB    "%s",13, "%s",13,"= (%s + 4 * %s - sqrt(123 * %s)) / (1 - %s / 2) = %s ", 0; 

.code  
	
	one proc
		fld qword ptr[eax];	   
		fld qword ptr[edx];		
        fmul ;            
        ;fstp temp1; 
        ;fld temp1
		fld qword ptr[ecx]
        fadd ;          
        ;fstp temp2
		;fld temp2
        ret
	one endp
	
	two proc
	;prolog
	push ebp
	mov ebp, esp
	;prolog
	xor ecx, ecx
	mov ecx, [ebp + 8]
	xor eax, eax
	mov eax, [ebp + 12]
		fld qword ptr [eax]
        fld qword ptr [ecx]
		fmul 
        ;fstp temp3
        ;fld temp3
        fsqrt;                  
        ;fstp temp4
        ;fld temp4
		fsub;                  
        ;fstp temp5
        ;fld temp5
	;epilog
		pop ebp
	;epilog
		ret 8
	two endp
	
mainStart: 
    finit
    mainLoop:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        xor ebx, ebx;
		xor eax, eax
        mov bx, iter;
        
		fld arr_a[ebx * 8];
		fcom var3
		fstsw ax 
        sahf
	    jz eror1
		xor eax, eax
		jmp firstStart
		eror1:
		invoke wsprintf, addr counter, addr headerr, it;
		invoke MessageBox,NULL, addr text1, addr counter, MB_OK;
		jmp ending
		
		firstStart:
		
        fstp var_a;
        fld arr_b[ebx * 8];
        fstp var_b;
        fld arr_c[ebx * 8];
        fstp var_c;
        fld arr_d[ebx * 8];
		fcom var4
		fstsw ax 
        sahf
		jc eror2
		xor eax, eax
		jmp secondStart
			eror2:
		invoke wsprintf, addr counter, addr headerr, it;
        invoke MessageBox,NULL, addr text2, addr counter, MB_OK;
		jmp ending
		
		secondStart:
        fstp var_d;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        xor eax, eax
		xor ecx, ecx
		xor edx, edx
		mov eax, offset var1
		mov ecx, offset var_c
		mov edx, offset var_b
		call one;
		
		push offset var_d
		push offset var2
		call two;
		
		call third@0
		;fstp temp6
		;fstp temp7
		;fld temp7
        fdiv;                  
        fstp Res;    DQ   
		
        invoke wsprintf, addr counter, addr head, it;
		invoke FloatToStr, var_a, addr buffa;
		invoke FloatToStr, var_b, addr buffb;
        invoke FloatToStr, var_c, addr buffc;
        invoke FloatToStr, var_d, addr buffd;

        invoke FloatToStr, Res, addr buff8;   

        ;invoke FpuFLtoA,offset  temp1, 15,offset  buff1, SRC1_REAL
        ;invoke FpuFLtoA,offset  temp2, 15,offset  buff2, SRC1_REAL
        ;invoke FpuFLtoA,offset  temp3, 15,offset  buff3, SRC1_REAL
        ;invoke FpuFLtoA,offset  temp4, 15,offset  buff4, SRC1_REAL
        ;invoke FpuFLtoA,offset  temp5, 15,offset  buff5, SRC1_REAL
        ;invoke FpuFLtoA,offset  temp6, 15,offset  buff6, SRC1_REAL
        ;invoke FpuFLtoA,offset  temp7, 15,offset  buff7, SRC1_REAL   
		
		invoke wsprintf, addr line1, addr letter,    addr head1, addr buffa, addr buffb, addr buffc, addr buffd
        ; invoke wsprintf, addr line2, addr template1, addr head2, addr buffb, addr buff1 
        ; invoke wsprintf, addr line3, addr template2, addr buffc, addr buffb, addr buff2;
        ; invoke wsprintf, addr line4, addr template3, addr buffd, addr buff3;
        ; invoke wsprintf, addr line5, addr template4, addr buffd, addr buff4;
        ; invoke wsprintf, addr line6, addr template5, addr buffc, addr buffb, addr buffd, addr buff5;
        ; invoke wsprintf, addr line7, addr template6, addr buffa, addr buff6;
        ; invoke wsprintf, addr line8, addr template7, addr buffa, addr buff7;
         invoke wsprintf, addr line9, addr template8, addr head3, addr head4, addr buffc, addr buffb, addr buffd, addr buffa, addr buff8                                                                                                   
       ;  invoke wsprintf, addr buff,  addr template,  addr line1, addr line2, addr line3, addr line4, addr line5, addr line6, addr line7, addr line8, addr line9;  
		invoke wsprintf, addr buff,  addr template,  addr line1, addr line9; закоментувати для виводу проміжних результатів

		
     invoke MessageBox,NULL, addr buff, addr counter, MB_OK;
	jmp ending
	ending:
    inc it;
    inc iter;
	cmp iter, 5
    jnz mainLoop
        
    invoke ExitProcess, NULL;	

end mainStart  
