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
			mov.w	#2000h, R4				; put 2000h into R4 to act as pointer
			mov.w   @R4, R5					; put the contents of address held in R4 into R5

			mov.w   #Const2, R6				; put 2002h into R6 to act as a pointer
			mov.w   @R6, R7					; put contents of address held in R6 into R7

			;in the events we forgot the indirect address
			mov.w	Const2, R6				; put contents of Const2 to R6
			mov.w   @R6, R7					; put contents of address held in R6 into R7

			jmp main




;-------------------------------------------------------------------------------
; Memory Allocation
;-------------------------------------------------------------------------------
            .data							; go to program memory @ 2000h
            .retain							; leave this section alone please

Const1:		.short		0DEADh				; put DEADh into address 2000h
Const2:		.short		0BEEFh				; put BEEF into address 2002h

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
            
