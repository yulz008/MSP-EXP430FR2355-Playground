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

			mov.w	#0, R4		; Initialize First Loop Variable

for1:
			mov.w	R4, Var1	; R4: 0 -> 1 -> 2 -> 3

			inc		R4
			cmp.w	#4, R4
			jnz		for1


			mov.w	#10, R4		; Initialize Second Loop Variable

for2:
			mov.w	R4,	Var1

			decd	R4
			tst.w	R4				; cmp.w  #0,  R4
			jge		for2

done:
			jmp		main



;-------------------------------------------------------------------------------
; Data Memory Allocation
;-------------------------------------------------------------------------------

			.data
			.retain

Var1:		.space 2
                                            

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
            
