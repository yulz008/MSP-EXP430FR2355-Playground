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

			mov.w  &2000h, &2004h				; Copy contents from 2000h into 2004h
			;mov.w  R4, &2004h

			mov.w  &2002h, &2006h			; Copy contents from 2002h into 2006h
			;mov.w  R5, &2006h

			jmp		main




;-------------------------------------------------------------------------------
; Memory Allocation
;-------------------------------------------------------------------------------

			.data							; go to  data memory 2000h
			.retain							; leave this in, to avoid optimization

Const1:		.short    1234h					; Setup constant 1234h, short is a 16bit word @2000h
Const2:		.short	  0CAFEh				; Setup constant 0CAFEh, 					  @2002h

Var1:		.space	  2						; reserve 2 bytes or 16 bit or 1 word		  @2004h
Var2:		.space	  2						; reserve 2 bytes or 16 bit or 1 word		  @2006h
                                            

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
            
