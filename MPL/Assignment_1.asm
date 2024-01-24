%macro readWrite 4
		mov rax, %1
		mov rdi, %2
		mov rsi, %3
		mov rdx, %4
		syscall
%endmacro

%macro loop 5
		mov rax, %1
		mov rdi, %2
		mov rsi, %3
		add rsi, %4
		mov rdx, %5
		syscall
%endmacro
				

section .data

		m1 db "Enter the numbers : "
		len1 equ $ - m1
		m2 db "Numbers : "
		len2 equ $ - m2
		endl db 0xA, 0xD
		len3 equ $ - endl
		count db 5
		count2 db 5
		
section .bss

		arr resb 90
		
section .text

		global _start
		
		_start:
				mov rbx, 0
				readWrite 1, 1, m1, len1
				
		loop1:
		
				loop 0, 0, arr, rbx, 17
				
				add rbx, 17
				dec byte[count]
				jnz loop1
				

				readWrite 1, 1, m2, len2
				mov rbx, 68
				
		loop2:
		
				loop 1, 1, arr, rbx, 17
				sub rbx, 17
				dec byte[count2]
				jnz loop2
				
				mov rax, 60
				mov rdi, 0
				syscall
				
			
		

