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

;------ Setup LED

			bis.b	#BIT0, &P1DIR			; set P1.0 to make output (LED1)
			bis.b	#BIT0, &P1OUT			; set LED1 initially
			bic.b	#LOCKLPM5, &PM5CTL0		; turn on digital I/O

;------- Setup timer B0
			bis.w	#TBCLR,  &TB0CTL		; clears timer B0
			bis.w	#TBSSEL__ACLK, &TB0CTL	; choose as source
			bis.w 	#MC__UP, &TB0CTL		; put in up mode

;-------- setup compares
			mov.w   #32768, &TB0CCR0		; sets up the period CCR0 = 32,768
			mov.w   #1638, &TB0CCR1			; sets up the on time CCR1 = 1,638

;-------- Setup IRQ
			bis.w	#CCIE,  TB0CCTL0		; local IRQ Enable for CCR0
			bic.w	#CCIFG, TB0CCTL0		; clear the CCR0 flag

			bis.w	#CCIE,  TB0CCTL1		; local IRQ Enable for CCR1
			bic.w	#CCIFG, TB0CCTL1		; clear the CCR1 flag

			eint							; global enable

main:
			jmp 	main


;-------------------------------------------------------------------------------
; ISRs
;-------------------------------------------------------------------------------
                                            
ISR_TB0_CCR1:
			bic.b   #BIT0, &P1OUT			; led1 = 0
			bic.w	#CCIFG, TB0CCTL1		; clear the CCR1 flag
			reti

ISR_TB0_CCR0:
			bis.b   #BIT0, &P1OUT			; led1 = 1
			bic.w	#CCIFG, TB0CCTL0		; clear the CCR0 flag
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
            
            .sect   ".int43"				; CCR0 vector
            .short  ISR_TB0_CCR0

            .sect   ".int42"				; CCR1 vector
            .short  ISR_TB0_CCR1


