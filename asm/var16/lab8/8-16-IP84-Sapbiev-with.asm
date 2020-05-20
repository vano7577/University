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

    printRes     dq    ?; 
    intermedRes1 DT    ?;
    intermedRes2 DT    ?;
    intermedRes3 DT    ?;
    intermedRes4 DT    ?;
    intermedRes5 DT    ?;
    intermedRes6 DT    ?;
    intermedRes7 DT    ?;
    RES 		 DT    ?;
	temp         DT    ?;
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
	fi           dt    ?;
    buff         db    1000 DUP(?), 0;
    mainbuff     db    1000 DUP(?), 0;
    lineFormat   db    5 DUP("%s"), 0;
    format       db    "%s",13,"%s",13, "%s",13, "%s",13, "%s",13, "%s",13
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

    count        db    150 DUP(?);
.const	
    const1       dq    3.0;
    const2       dq    2.0; 
	const3       dq    0.0;
	
    head         db    "��� �8. ������. ��������� � ������������� ����� �����", 0;   
	headerror 	 db    "�������!��� �8. ������.",0
	text1error   db    "³�'����� ����� �� ����������", 0;
	text2error	 db    "ĳ����� �� ����", 0;
    headtask     db    "TN", 0;
    head1        db    "������ �����:" , 0;
    head2        db    "������� ���������:", 0;
    head3        db    "���������� �����:", 0;
	head4 	     db    "(c/d + ln(3*a/2))/(c-b+1))=", 0;
	letter	     db    "%s",13, "a = %s",13,"b = %s", 13, "c = %s", 13,"d = %s", 0;

    forma        db    "%s", 0;
    format1      db    "%s",13, "3 * a / 2 = %s", 0
    format2      db    "ln(3 * a / 2) = %s", 0;
    format3      db    "c / d + ln(3 * a / 2) = %s", 0;
    format4      db    "b - 1 = %s", 0;
    format5      db    "c - (b - 1) = c - b + 1 = %s", 0;
 
    format6      db    "%s",13, "%s",13,"= ((%s / %s + ln(3 * %s /2))/(%s - %s + 1) = %s ", 0;  
.code
	DLLEntry proc hInstDLL: HINSTANCE,
		reason: DWORD,
		reserved: DWORD
		
		mov eax,TRUE
		ret
	DLLEntry endp

	WithPoint proc 
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

		fld var_a
		fcom const3
		fstsw ax 
        sahf
	    jc eror1
		xor eax, eax
		jmp starting1
		eror1:
		invoke wsprintf, addr count, addr headerror
		invoke MessageBox,NULL, addr text1error, addr count, MB_OK;
		jmp ending
		
		starting1:
		
        fstp var_a;
		
		fld var_c
		fld1; 
		fadd;
		fcom var_b
		fstsw ax
        sahf
		jz eror2
		xor eax, eax
		jmp starting2
			eror2:
		invoke wsprintf, addr count, addr headerror
        invoke MessageBox,NULL, addr text2error, addr count, MB_OK;
		jmp ending		
		fstp fi;
		fstp fi;
		fstp fi;
		fstp fi;
		starting2:
        fld var_d
		fcom const3
		fstsw ax 
        sahf
		jz eror3
		xor eax, eax
		jmp starting3
			eror3:
		invoke wsprintf, addr count, addr headerror
        invoke MessageBox,NULL, addr text2error, addr count, MB_OK;
		jmp ending

		starting3:

		fstp var_d;
		fstp fi
		fld var_c
		fld var_d
		fdiv;

		fld var_a
		fmul const1
		fdiv const2
	
		fstp intermedRes1
        fld intermedRes1
		fstp temp;
        fldln2
		fld temp;
	    fyl2x
		
        fstp intermedRes2
		fld intermedRes2
		fadd 
		fstp intermedRes3
        fld intermedRes3
		fld var_c
		fld var_b
		fld1
		fsub
		fstp intermedRes4
        fld intermedRes4
		fsub
		fstp intermedRes5
        fld intermedRes5
		fdiv    
        fstp printRes;    DQ    printRes <- ST(0)
		
	window proc
	    
		invoke wsprintf, addr count, addr head
        invoke FloatToStr, var_c, addr buffc;
        invoke FloatToStr, var_b, addr buffb;
        invoke FloatToStr, var_d, addr buffd;
        invoke FloatToStr, var_a, addr buffa;
        invoke FloatToStr, printRes, addr buff8;   
       
        invoke FpuFLtoA,offset  intermedRes1, 15,offset  buff1, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes2, 15,offset  buff2, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes3, 15,offset  buff3, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes4, 15,offset  buff4, SRC1_REAL
        invoke FpuFLtoA,offset  intermedRes5, 15,offset  buff5, SRC1_REAL

		
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
                         addr buff1
        invoke wsprintf, addr lineBuff3,
                         addr format2,
                         addr buff2
        invoke wsprintf, addr lineBuff4,
                         addr format3,
                         addr buff3
        invoke wsprintf, addr lineBuff5,
                         addr format4,
                         addr buff4
        invoke wsprintf, addr lineBuff6,
                         addr format5,
                         addr buff5,
                         addr buffb,
                         addr buffd,
                         addr buff5;
        invoke wsprintf, addr lineBuff7,
                         addr format6,
						 addr head3,
						 addr head4,
                         addr buffc,
                         addr buffd,
                         addr buffa,
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
                         addr lineBuff7
  

	invoke MessageBox,NULL, addr buff, addr count, MB_OK;
		 pop ebp
	 ret 0
	window endp

	call window
	jmp ending
	ending:
 WithPoint   endp
end DLLEntry