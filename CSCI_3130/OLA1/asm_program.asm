;; Greg Wagner
;; CSCI-3130 Dr. Phillips
;; OLA1
;; asm_program.asm

	global main
	extern c_function

	segment .text

main:
	mov		rdi, haiku
	mov		rsi, 62; ..................
	call		c_function	; ..................
	ret

	segment .data
haiku:
	db	"From time to time",10,"The clouds give rest",10,"To the moon-beholders.",10