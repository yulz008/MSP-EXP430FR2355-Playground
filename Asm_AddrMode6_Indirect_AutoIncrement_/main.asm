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

			mov.w   #Block1, R4				; setup initial addresss pointer

			mov.w	@R4+, R5				; a .w will auto increment by 2
			mov.w   @R4+, R6
			mov.w   @R4+, R7


			mov.b	@R4+, R8
			mov.b   @R4+, R9
			mov.b   @R4+, R10


			jmp main


;-------------------------------------------------------------------------------
; Memory Allocation
;-------------------------------------------------------------------------------


			.data							; go to data memory @2000h
			.retain							; please leave alone optimizer


Block1:		.short	1122h, 3344h, 5566h, 7788h, 99AAh	; create block of constant data



                                            

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
            
