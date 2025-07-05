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

			mov.b	#10101010b,	R4
			inv.b	R4

			mov.b   #11110000b, R5
			and.b	#00111111b, R5			; clear bit6 and bit7


			mov.b   #00010000b, R6			; ist bit 7 a 1 or 0?
			and.b	#10000000b, R6			; test position bit7


			mov.b	#00010000b, R7			; is bit 4 a 1 or 0?
			mov.b   R7,R8
			and.b	#00010000b, R8



			mov.b   #11000001b, R9
			mov.b	R9, R10
			or.b   #00011111b, R10			; set bits 4:0


			mov.b	#01010101b, R11
			mov.b   R11,R12
			mov.b   R11,R13
			xor.b   #11110000b, R12			; Toggle
			xor.b   #00001111b, R13			; Toggle

			jmp		main

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
            
