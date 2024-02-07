%macro IO 4  ; simple macro ,
mov rax,%1   ;  param 1 ->  system call number                             
mov rdi,%2    ;  param 2 ->  file descriptor                              
mov rsi,%3     ;  param 3 ->  message                       
mov rdx,%4      ;  param 4 ->  length                         
syscall                                     
%endmacro  
section .data
    m1 db "Enter String :", 0xA
    l1 equ $-m1                         
    m2 db "Entered String :", 0xA    
    l2 equ $-m2                         
    m3 db "Length is ", 0xA           
    l3 equ $-m3 
    
section .bss
    string resb 50                      
    strl equ $-string 
    count resb 1
    _output resb 20
section .text
    global _start

_start:  
    IO 1,1,m1,l1    
 input:
    IO 0,0,string,strl
    dec rax
    mov [count],rax 
 output:
    IO 1,1,m2,l2    
    IO 1,1,string,strl
    IO 1,1,m3,l3  
    mov rax,[count]  
    call hex_to_dec
    IO 1,1,_output,16
 exit:    
    mov rax, 60    
    mov rdi, 0      
    syscall

hex_to_dec:
        mov rsi,_output+15  ; max size of display , for convinience set to 16 and rsipoints to output[16]
        mov rcx,2           ; loop count , or number of digits displayed , 2 digits (unlikely we will enter string > 99)(prints preceding zeros otherwise)
    letter2:	
        xor rdx,rdx         ; setting rdx to null without setting a null byte (a tip i saw on reddit) needed to clean dl for use 
        mov rbx,10          ; conversion base
        div rbx             ; dividing by conversion base
        cmp dl,09h          ; comparing 09h with dl , since the division remainder ends up in dx and since its one digits its in dl
        jbe add30           ; if value under in 0-9 , we directly add 30h to get ascii 0-9
    add30:	
        add dl,30h          ; adding 30h
        mov [rsi],dl        ; moving the ascii we generated to rsi
        dec rsi             ; rsi now points to the next place in display or output[n-1]
        dec rcx             ; loop 
        jnz letter2
ret
		
				
