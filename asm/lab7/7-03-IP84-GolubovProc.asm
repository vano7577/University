.686
.model flat, stdcall
option casemap: none


	extern var_a:QWORD, const3:QWORD, intermedRes6:QWORD , intermedRes7:QWORD
		public three
.data
.code
three proc
	  fld1;                   ST(0) <- c+4*b - sqrt(123*d), ST(1) <- 1
        fld var_a;              ST(0) <- c+4*b - sqrt(123*d), ST(1) <- 1, ST(2) <- a
        fld const3;             ST(0) <- c+4*b - sqrt(123*d), ST(1) <- 1, ST(2) <- a, ST(3) <-2
        fdiv;                   ST(0) <- c+4*b - sqrt(123*d), ST(1) <- 1, ST(2) <- a/2
        fstp intermedRes6; проміжні результати ( не впливає на результат обрахунків, не є параметром обрахунку і результатом)
        fld intermedRes6
        fsub;                   ST(0) <- c+4*b - sqrt(123*d), ST(1) <- 1-a/2
        fld intermedRes6
		ret 
three endp
end