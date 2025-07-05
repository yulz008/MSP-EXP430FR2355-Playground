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
        bis.b    #BIT0, &P1DIR              ; sets P1.0 to output (Led1)
        bic.b    #BIT0, &P1OUT              ; clear LED1 initially

        bic.b    #BIT1, &P4DIR              ; set P4.1 to input (SW1)
        bis.b    #BIT1, &P4REN              ; enabled pull up/down resistor
        bis.b    #BIT1, &P4OUT              ; make the resistor a pull up

        ; Choose one of these sensitivity options:
        bis.b    #BIT1, &P4IES             ; sensitivity is HIGH-to-LOW (button press)
        ;bic.b   #BIT1, &P4IES             ; sensitivity is LOW-to-HIGH (button release)

        bic.b    #LOCKLPM5, &PM5CTL0        ; enable Digital I/O

        bic.b    #BIT1, &P4IFG              ; clear P4IFG
        bis.b    #BIT1, &P4IE               ; local enable for P4.1
        eint                                ; enable global maskables

main:
        jmp     main


;-------------------------------------------------------------------------------
; Interrupt Service Routines
;-------------------------------------------------------------------------------

ISR_S1:
        bit.b    #BIT1, &P4IN               ; test P4.1 state
        jnz      button_released            ; if high (button released)

button_pressed:
        bis.b    #BIT0, &P1OUT              ; turn LED ON
        jmp      clear_flag

button_released:
        bic.b    #BIT0, &P1OUT              ; turn LED OFF

clear_flag:
        bic.b    #BIT1, &P4IFG              ; clear P4IFG
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
            
            .sect  ".int22"                 ; port 4 vector address
            .short  ISR_S1
