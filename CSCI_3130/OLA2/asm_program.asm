;; Greg Wagner
;; CSCI-3130 Dr. Phillips
;; OLA2
;; asm_program.asm
;; Note: RDI, RSI, RDX, RCX, R8, R9 (order of passing int/pointer)
;; RAX, RDX (return values)

global main
extern printf

segment .text

main:

loop:

mov r13, [counter]
cmp r13, 128
jge exit
;; Print a string ("(" )
mov rdi,lpstr
mov al,0
call printf

mov r12, array
mov rsi,[r12 + r13]
;; Print a the first integer
mov rdi,intf
mov al,0
call printf

;; Print a string (" + ")
mov rdi,addstr
mov al,0
call printf
 
mov rsi, [r12 + r13 + 8]

;; Print a the next int from array
mov rdi,intf
mov al,0
call printf
 
;; Print a string (")" )
mov rdi,rpstr
mov al,0
call printf
 
;; Print a string (" * ")
mov rdi,mulstr
mov al,0
call printf
 
;; Print a string ("(" )
mov rdi,lpstr
mov al,0
call printf

mov rsi, [r12+ r13 + 16]

;; Print a the next int from array
mov rdi,intf
mov al,0
call printf
 
;; Print a string (" - ")
mov rdi,substr
mov al,0
call printf

mov rsi, [r12 + r13 + 24]

;; Print a the next int from array
mov rdi,intf
mov al,0
call printf
 
;; Print a string (")" )
mov rdi,rpstr
mov al,0
call printf
 
;; Print a string (" = ")
mov rdi,eqlstr
mov al,0
call printf

mov rsi,[r12 + r13]
mov rdi, [r12 + r13 + 8]
mov rdx, [r12+ r13 + 16]
mov rcx, [r12 + r13 + 24]
call binom_mult

mov rsi, [product]

;; Print a the next int from array
mov rdi,intf
mov al,0
call printf

;; Print a newline
mov rdi,newln
mov al,0
call printf

mov rsi, [counter]
add rsi, 32
mov [counter], rsi
jmp loop

binom_mult:
;; get numbers from stack (reverse order)
;; addition of ints
add rdi,rsi
;; rdi now contains sum

sub rdx, rcx
;; difference now stored in rsi
mov rax, rdi
mul rdx
mov [product], rax
ret

exit:
; exit(0)
        mov     eax, 60            ; system call 60 is exit
        mov     rdi, 0               ; exit code 0
        syscall                         ; invoke operating system to exit
 

segment .data
array: 	dq 1,2,4,3,5,6,8,7,9,10,20,11,13,14,35,16
intf 		db "%ld",0
eqlstr 	db " = ",0
mulstr 	db " x ",0
addstr	db " + ",0
substr 	db " - ",0
lpstr 	db "(",0
rpstr		db ")",0
newln	db 10,0
counter	dq 0
product	dq 0