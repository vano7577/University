.686
.model flat, stdcall
option casemap: none

	;extern var_a:QWORD, var3:QWORD, temp6:QWORD , temp7:QWORD
	extern var_a:QWORD, var3:QWORD; закоментувати для виводу проміжних результатів
		public third
.data
.code
third proc
	  fld1;          
        fld var_a;        
        fld var3;       
        fdiv;    
     ;   fstp temp6;
     ;   fld temp6
        fsub;       
      ;  fld temp6
		ret 
third endp
end