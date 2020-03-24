.686

include c:\masm32\include\masm32rt.inc 
includelib \masm32\lib\user32.lib 
include 4-03-IP84-Golubov-2.inc
 
.data 
 
  
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
 
end start


