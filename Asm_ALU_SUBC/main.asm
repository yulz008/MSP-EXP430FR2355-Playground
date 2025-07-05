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


			mov.w  #Var1, R4				; point to Var1. Var1 Address is 16 bit and R4 is 16bit register
			mov.w  #Var2, R5				; point to Var2
			mov.w  #Diff12, R6				; point to Diff12

			mov.w  0(R4), R7				; R7 = 1FFF
			mov.w  0(R5), R8				; R8 = 2222
			sub.w  R8, R7					; R7 = R7 - R8
			mov.w  R7, 0(R6)				; Mov lower 16bit to Diff12 lower 16 bit

			mov.w  2(R4), R7				; R7 = E465
			mov.w  2(R5), R8				; R8 = 1111
			subc.w  R8, R7					; R7 = R7 - R8
			mov.w  R7, 2(R6)				; Mov higher 16bit to Diff12 higher 16bit

			jmp     main

                                            
;-------------------------------------------------------------------------------
; Data Allocation
;-------------------------------------------------------------------------------

			.data							; go to data memory @ 2000h
			.retain							; leave this section alone

Var1:		.long   0E4651FFFh
Var2:		.long	11112222h
Diff12:		.space	4


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
            
