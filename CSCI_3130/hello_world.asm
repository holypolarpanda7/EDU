	;;
	;; Hello World Example
	;;
	
	global main
	
	segment	.text

main:
        ; write(1, message, 13)
        mov     rax, 1                  ; system call 1 is write
        mov     rdi, 1                  ; file handle 1 is stdout
        mov     rsi, message            ; address of string to output
        mov     rdx, 13                 ; number of bytes
	syscall		                ; invoke operating system

        ; exit(0)
        mov     rax, 60                 ; system call 60 is exit
        mov     rdi, 0                  ; exit code 0
        syscall                         ; invoke operating system to exit

segment .data
message:
        db      "Hello, World",10       ; note the newline/term at the end
	
