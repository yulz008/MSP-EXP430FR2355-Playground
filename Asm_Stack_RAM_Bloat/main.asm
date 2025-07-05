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


		    mov.w   #Var1, R4
		    mov.w	#Var2, R5
		    mov.w   #Sum12, R6

		    mov.w	0(R4), R7
		    mov.w   0(R5), R8
		    add.w   R7, R8					; add lower 16-bits
		    mov.w   R8, 0(R6)

		    mov.w	2(R4), R7
		    mov.w   2(R5), R8
		    addc.w  R7,R8					; add upper 16bits with carry
		    mov.w   R8, 2(R6)


			jmp  	main




;-------------------------------------------------------------------------------
; Data Memory Allocation
;-------------------------------------------------------------------------------

			.data							; go to data memory at @ 2000h
			.retain							; leave this alone


Var1:		.long   0E371FFFFh				; long 32 bit word
Var2:		.long	11112222h
Sum12:		.space	4000					; reserved  nbytes


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
            
