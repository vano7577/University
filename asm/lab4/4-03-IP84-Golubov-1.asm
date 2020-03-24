.686

include c:\masm32\include\masm32rt.inc 
includelib \masm32\lib\user32.lib 
 
.data 
 
 ;///////////////////////////////////////////////////////////////////////////
 ;                                   Data                                   /
 ;///////////////////////////////////////////////////////////////////////////
  
    myName db "Golubov Ivan", 0 
    myDate db "12.05.2001", 0
    myNumb db "8404", 0 

    inputb db 128 dup (0), '$' 
 
    hConsoleInput  dd 0 
    ConsoleLen db 0 
 
	message0 db "Enter the password in console",0 
    message1 db "Correct password",10, 13, 0 
    message2 db "Incorrect password", 0 
	message3 db "Attention!",0
    caption db "Input", 0    
    password db 3Ah, 36h, 32h, 36h
    PassLen=$-password 
    key equ 02h
  
  MOutput macro info, msg ;; macros for output 
    invoke MessageBox, 0, offset info, offset msg ,MB_OK 
  endm
 
  MDecrypt macro key, len ; macros for encryption 
  xor esi, esi
  hash:
    xor password[esi], key
    inc esi
    cmp esi, len ; if len!=4 => hash 
    jne hash
  endm
 
  MCompare macro input,  pass, len ;; macros for comparing password 
    local righ  
    lea ebx, input 
    call stringlength  

    mov edi, esi  
  
    mov edi, len 
    sub edi, esi  
    cmp edi, 0    
    jne wrng  
   
    righ:  
      cld  
      mov ecx, len 
      lea esi,  input 
      lea edi,  pass 
      repe cmpsb  
      jne wrng 
  endm
 
.code 
start: 

  MDecrypt key, PassLen
  MOutput  message0, message3
  
  call AllocConsole    
  invoke SetConsoleTitle, offset caption 
 
  invoke GetStdHandle, STD_INPUT_HANDLE 
  mov hConsoleInput, eax 
 
  invoke ReadConsole, hConsoleInput,offset inputb, 128, offset ConsoleLen, NULL 
 
  MCompare inputb, password, PassLen
 
  MOutput myName, message1
  MOutput myDate, message1
  MOutput myNumb, message1
  invoke ExitProcess, 0 
 
wrng proc 

   MOutput message2, message2
  invoke ExitProcess, 0 
  
wrng endp  
;///////////////////////////////////////////////////////////////////////////
	stringlength proc 
 
      mov esi, 0                                               
      mov edx, 0 

      iter: 
	
      mov eax, [ebx+esi]                                         
      inc esi 
      cmp eax, edx                                              
      jne iter                                              
      sub esi, 3                                            
   ret 
 
stringlength endp 
;///////////////////////////////////////////////////////////////////////////

end start


