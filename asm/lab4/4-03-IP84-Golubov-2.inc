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