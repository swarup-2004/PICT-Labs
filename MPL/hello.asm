 section .data
  	msg db "Hello World"
  	endl db 0xA, 0xD 
  	msglen equ $-msg
 section .text
 		global _start
 				_start:
 						;printing message
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, msg
 						mov rdx, 6
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, endl
 						mov rdx, 2
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, msg + 6
 						mov rdx, 5
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, endl
 						mov rdx, 2
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, msg + 4
 						mov rdx, 1
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, msg + 3
 						mov rdx, 1
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, msg + 2
 						mov rdx, 1
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, msg + 1
 						mov rdx, 1
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, msg
 						mov rdx, 1
 						syscall
 						
 						mov rax, 1
 						mov rdi, 1
 						mov rsi, endl
 						mov rdx, 2
 						syscall
 						
 						
 						
 						;exiting
 						mov rax, 60
 						mov rdi, 0
 						syscall
 						
 						
  
