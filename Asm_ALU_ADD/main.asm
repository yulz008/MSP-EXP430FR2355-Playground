;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

main:
			; Add#1
			mov.w	#371, R4				; put 371 into R4
			mov.w   #465, R5				; put 465 into R5
			add.w	R4, R5					; R5 = R4 + R5

			; Add#2
			mov.w   #0FFFEh, R6				; put FFFEh into R6
			add.w   #0001h, R6				; R6 = 1 + R6

			; Add#3
			mov.w	#0FFFFh, R7				; put FFFFh into R7
			add.w   #1h, R7					; R7 = R7 + 1


			; Add#4
			mov.b	#255, R8
			mov.b	#1, R9
			add.b 	R8, R9


			; Add #5
			mov.b	#-1, R10
			add.b   #1, R10


			; Add #6
			mov.b   #127, R11
			add.b	#127, R11



			jmp main						; forms the infinite loop

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
