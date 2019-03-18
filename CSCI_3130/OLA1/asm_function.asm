	;; Greg Wagner
	;; CSCI 3130
	;; asm_function
	;; creating a function that prints a haiku that can be applied to a c program
	
	global asm_function
	
	segment	.text

asm_function:
        ; write(1, haiku, ....)
	mov     rsi, rdi                 ; retieve pointer for function parameter
	mov	    rax, 1			 ; system call 1 is write
        mov     rdi, 1                  ; file handle 1 is stdout
	syscall		                ; invoke operating system
	ret					; return to c program
       
