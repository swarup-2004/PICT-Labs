section .data
		msg db "Your name is :"
		endl db 0xA

section .bss
		name resb 10

section .text
		global _start
		_start:
				mov rax, 0
				mov rdi, 0
				mov rsi, name
				mov rdx, 10
				syscall
				
				mov rax, 1
				mov rdi, 1
				mov rsi, msg
				mov rdx, 14
				syscall
				
				mov rax, 1
				mov rdi, 1
				mov rsi, name
				mov rdx, 10
				syscall
				
				
				mov rax, 60
				mov rdi, 0
				syscall
