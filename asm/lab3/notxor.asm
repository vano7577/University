.686

include \masm32\include\masm32rt.inc 
includelib \masm32\lib\user32.lib 
 
.data 
 
 ;///////////////////////////////////////////////////////////////////////////
 ;                                   Data                                   /
 ;///////////////////////////////////////////////////////////////////////////
    password db 038h, 034h, 030h, 034h  ;8404
    PassLen=$-password 
  
    info db "Golubov Ivan,", 10, 
            "12.05.2001", 10, 
            "8404", 0 
    buffer db 128 dup (0) 
 
    hConsoleInput  dd 0 
    bufferLen db 0 
    
	message0 db "Enter the password:",0 
    message1 db "Correct password",10, 13, 0 
    message2 db "Incorrect password", 0 
    caption db "Input", 0                    
 
.code 
start: 
 ;///////////////////////////////////////////////////////////////////////////
 ;                                   Console						        /
 ;///////////////////////////////////////////////////////////////////////////
 
  call AllocConsole   
  invoke SetConsoleTitle, offset caption 
 
  invoke GetStdHandle, STD_INPUT_HANDLE 
  mov hConsoleInput, eax 
 
  invoke ReadConsole, hConsoleInput,offset buffer, 128, offset bufferLen, NULL 
  	

 
 ;///////////////////////////////////////////////////////////////////////////
 ;                                   compare password				       	/
 ;///////////////////////////////////////////////////////////////////////////
 
    lea ebx, buffer   
    call stringlength 
	
    mov edi, esi      
 
    mov edi, PassLen  
    sub edi, esi 		
    cmp edi, 0 			
    jne wrng 			
  
    mov ecx, PassLen 	
    lea esi, password  	
    lea edi, buffer  	
    repe cmpsb     		
	je right			
	jmp wrng			
 ;///////////////////////////////////////////////////////////////////////////
stringlength proc 
	xor esi, esi
	xor edx, edx
    iter: 
      mov eax, [ebx+esi]                                     
      inc esi 						
      cmp eax, edx                                              
      jne iter                                             
   sub esi, 3                 
   ret 								
stringlength endp 
;///////////////////////////////////////////////////////////////////////////
	right proc
		invoke MessageBox, 0, offset info, offset message1 ,MB_OK 
		invoke ExitProcess, 0 
	right endp 
 
  wrng proc 
    invoke MessageBox, 0, offset message2, offset message2 ,MB_OK 
    invoke ExitProcess, 0 
  wrng endp 
;///////////////////////////////////////////////////////////////////////////
end start

