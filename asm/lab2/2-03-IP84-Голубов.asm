.model  tiny
.data
    password db 03Ah, 036h, 032h, 036h;
    PassLen=$-password
    key  equ 002h;
    Data db 13, "Golubov Ivan, ",
    13, 10, "12.05.2001, ", 13, 10, "8404$";
    InpMassage db "Enter your password:$ ";
    MaxInput db 5;
    InputLen db 0;
    buffer db 5 dup (0);
	error db 13, "Incorrect password$";
.code
org 100h
 
main:

	mov ax, 03h
    int 10h
	
	xor di, di
	hash:
    xor password[di], key
    inc di
    cmp di, 4
    jne hash 	

	xor di, di
	cycle:
    xor buffer[di], key
    inc di
    cmp di, 4
    jne cycle 
	
    mov dx, offset InpMassage;
    mov ah,09h;
    int 21h
    
    mov dx, offset MaxInput;
    mov ah, 0Ah;
    int 21h
    
    mov ah, PassLen;
    mov bh, InputLen;
    cmp ah, bh;
    jne false

    mov si, offset buffer;
    mov di, offset password;
    mov cx, PassLen;
    repe cmpsb;
    je true       
    jmp false
     
    true:
    mov ax, 03h
    int 10h
    mov dx, offset Data;
    
    jmp exit
       
    false:
	mov ax, 03h
    int 10h
    mov dx, offset error;
       
    exit:
	mov ah, 09h;
    int 21h
    
    mov ah, 0;
    int 21h;
    
end main
