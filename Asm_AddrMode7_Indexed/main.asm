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
			mov.w	#Block1, R4				; Initialize R4 to point to 2000h

			mov.w	0(R4), 8(R4)			; copy contents at 2000h to 2008h
			mov.w   2(R4), 10(R4)			; copy contents at 2002h to 200Ah
			mov.w   4(R4), 12(R4)			; copy contents at 2004h to 200Ch
			mov.w   6(R4), 14(R4)			; copy contents at 2006h to 200Eh

			jmp main

;-------------------------------------------------------------------------------
; Data Allocation Memory
;-------------------------------------------------------------------------------
			.data							; go to data memory @ 2000h
			.retain							; keep this section

Block1:		.short	0AAAAh, 0BBBBh, 0CCCCh, 0DDDDh
Block2:     .space	8

                                            

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
            
