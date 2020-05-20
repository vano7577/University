.686
.model flat, stdcall
option casemap: none

	extern var_c:QWORD, var_b:QWORD, intermedRes4:QWORD , intermedRes5:QWORD
		public three
.data
.code
three proc
		fld var_c
		fld var_b
		fld1
		fsub
		fstp intermedRes4
        fld intermedRes4
		fsub
		fstp intermedRes5
        fld intermedRes4
		fld intermedRes5
		ret 
three endp
end