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
init:
; setup LED1
			bis.b	#BIT0, &P1DIR			; set P1.0 to output (LED1)
			bic.b	#BIT0, &P1OUT			; LED1 off initially
			bic.b   #LOCKLPM5, &PM5CTL0		; turn on digital I/O

; setup timer b0
			bis.w	#TBCLR, &TB0CTL			; clear timer
			bis.w	#TBSSEL__ACLK, &TB0CTL	; choose ACLK as source
			bis.w	#MC__UP, &TB0CTL		; put timer into UP mode
                                            
; setup compare
			mov.w	#16384, &TB0CCR0		; setup compare VALUE
			bis.w	#CCIE, &TB0CCTL0		; local enable for CCR0 in TB0
			eint							; global enable
			bic.w	#CCIFG, &TB0CCTL0		; clear CCIFG flag

main
			jmp		main

;-------------------------------------------------------------------------------
; ISRs
;-------------------------------------------------------------------------------
ISR_TB0_CCR0:
			xor.b	#BIT0, &P1OUT			; toggle LED1
			bic.w	#CCIFG, &TB0CCTL0		; clear CCIFG flag
			reti

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
            
            .sect   ".int43"				; TB0 CCR0 Vector
            .short  ISR_TB0_CCR0

