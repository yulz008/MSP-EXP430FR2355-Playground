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
;------ Setup of LED
			bis.b	#BIT0, &P1DIR			; set LED1 to output
			bic.b	#BIT0,	&P1OUT			; clear LED1 initially
			bic.b	#LOCKLPM5, &PM5CTL0		; turn on digital I/O

;------ Setup of Timer
			bis.w	#TBCLR, &TB0CTL			; resets the timer
			bis.w   #TBSSEL__SMCLK, &TB0CTL	; choose SMCLK (1mhz) as source
			bis.w	#MC__CONTINUOUS, &TB0CTL ; put timer into continuous mode

;------- Setup IRQ
			bis.w	#TBIE, &TB0CTL			; local enable for overflow IRQ
			eint							; global enable for maskable IRQs
			bic.w	#TBIFG, &TB0CTL			; clear overflow flag
main:
			jmp		main

;-------------------------------------------------------------------------------
; Interrupted Service Routine
;-------------------------------------------------------------------------------
ISR_TB0_Overflow:
			xor.b	#BIT0, &P1OUT			;toggle LED1
			bic.w	#TBIFG, &TB0CTL			; clear overflow flag
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
            
            .sect   ".int42"				; Timer B0 OVerflow Vector
            .short  ISR_TB0_Overflow
