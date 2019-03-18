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
mov r8, 0 ;; counter
mov r9, array
jmp loop
 
loop:
cmp r8, 16
jge done
 
;; Print a string ("(" )
mov rdi,lpstr
mov al,0
call printf
 
mov rsi, [r9 + r8]
push word [rsi]
 
;; Print a the first integer
mov rdi,intf
mov al,0
call printf
 
;; Print a string (" + ")
mov rdi,addstr
mov al,0
call printf
 
mov rsi, [r9 +r8 + 2]
push word [rsi]

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
 
mov rsi, [r9+r8+4]
push word [rsi]

;; Print a the next int from array
mov rdi,intf
mov al,0
call printf
 
;; Print a string (" - ")
mov rdi,substr
mov al,0
call printf
 
mov rsi, [r9+r8+6]
push word [rsi]

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
 
call binom_mult
 
;; Print a the product obtained in binom_mult
mov rsi, rax
mov rdi,intf
mov al,0
call printf
 
 ;; Print a string ("newline")
mov rdi,newln
mov al,0
call printf
 
add r8, 8
jmp loop
 
binom_mult:
;; get numbers from stack (reverse order)
pop rdi
pop rsi
;; addition of ints
sub rdi,rsi
;; rdi now contains sum
pop rsi
pop rdx
;;  subtraction of ints
add rsi, rdx
;; difference now stored in rsi
mov rax, rsi
mul rdi
ret

done:
call exit
 
exit:
; exit(0)
        mov     eax, 60            ; system call 60 is exit
        mov     rdi, 0               ; exit code 0
        syscall                         ; invoke operating system to exit
 

segment .data
array: 	dw 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
intf 		db "%ld",0
eqlstr 	db " = ",0
mulstr 	db " x ",0
addstr	db " + ",0
substr 	db " - ",0
lpstr 	db "(",0
rpstr		db ")",0
newln	db 10,0