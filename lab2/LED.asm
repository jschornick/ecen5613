;; File: led.asm
;; Author: Jeff Schornick
;;
;; ECEN5613 Lab #2
;;
;; Use a timer ISR to blink an LED on P1.2 every 0.4s.


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Constants
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; With a 11.0592MHz oscillator, machine cycle frequency is 921.6 KHz
TIMER_COUNT: EQU 9216   ; 16-bit counter value, 9216 cycles = 0.01s until overflow

;; The 8051 timers count up and overflow from all 1s to all 0s.
;; Calculate reset values that trigger overflow after exactly TIMER_COUNT cycles
TL0_RESET:   EQU ((65535-TIMER_COUNT)+1)&0FFh ; Lower 8 bits
TH0_RESET:   EQU ((65535-TIMER_COUNT)+1)>8    ; Upper 8 bits

ISR_ITERS:   EQU 40     ; number of ISR iterations before toggling LED (0.4s)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Register definitions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; TMOD: Timer mode setting flags (resets to 00h)
TMOD_T0_8BIT:     EQU 000h      ; 8-bit mode
TMOD_T0_16BIT:    EQU 001h      ; 16-bit mode
TMOD_T0_8BITR:    EQU 002h      ; 8-bit mode w/reload
TMOD_T0_MODE3:    EQU 003h      ; Mode 3
TMOD_T0_TIMER:    EQU 000h      ; Timer mode
TMOD_T0_COUNTER:  EQU 004h      ; Counter mode
TMOD_T0_NOGATE:   EQU 000h      ; Timer 0 not gated
TMOD_T0_GATED:    EQU 008h      ; Timer 0 gated by INT0


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Reset / program entry point
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ORG $0000
Start:
  AJMP  Init                    ; Jump over ISRs to main routine

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Interrupt Service Routines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ORG $000B
T0_ISR:
  ;; NB: TF0 is automatically cleared upon entry
  SETB P1.1                     ; ISR status pin high
  DJNZ R0,End_T0_ISR            ; Decrement ISR tally and exit if nonzero
  CPL  P1.2                     ; Toggle LED pin
  MOV  R0,#ISR_ITERS            ; Reset ISR counter to max value

End_T0_ISR:
  MOV  TL0,#TL0_RESET           ; Reload lower 8-bits
  MOV  TH0,#TH0_RESET           ; Reload upper 8-bits
  CLR  P1.1                     ; ISR status pin low
  RETI


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Initialization
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Init:
  CLR  P1.1                     ; ISR status pin low
  MOV  R0,#ISR_ITERS            ; Initialize the ISR tally (downcount)
  ;; Timer0 mode setting for simple 16-bit timer
  MOV  TMOD,#TMOD_T0_16BIT|TMOD_T0_TIMER|TMOD_T0_NOGATE
  MOV  TL0,#TL0_RESET           ; Reload lower 8-bits
  MOV  TH0,#TH0_RESET           ; Reload upper 8-bits
  SETB IE.7                     ; Enable interrupts (EA=1)
  SETB IE.1                     ; Enable timer 0 overflow interrupts (ET0=1)
  SETB TCON.4                   ; Start timer 0 (TR0=1)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EndLoop:
  AJMP EndLoop
