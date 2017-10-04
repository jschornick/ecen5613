;; File: debug.asm
;; Author: Jeff Schornick
;;
;; ECEN5613 Lab #2, supplemental
;;
;; Use a timer ISR to blink an LED on P1.2 every 0.4s.
;; Send debug information to the external debug register via MOVX.


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

;; High bit of debug register value
;;  - cleared for Main (0x00 - 0x7F)
;;  - set for ISR (0x80 - 0xFF)
DBG_MASK:  EQU 080h           ; High bit of debug value


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Memory reservations
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

DBG_MAIN:  EQU $20            ; Main loop debug counter
DBG_ISR:   EQU $21            ; ISR debug counter


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
  AJMP  Init                  ; Jump over ISRs to main routine


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Interrupt Service Routines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ORG $000B
T0_ISR:
  ;; NB: TF0 is automatically cleared upon entry
  SETB  P1.1                  ; ISR status pin high
  DJNZ  R0,End_T0_ISR         ; Decrement ISR tally and exit if nonzero
  CPL   P1.2                  ; Toggle LED pin
  MOV   R0,#ISR_ITERS         ; Reset ISR counter to max value

End_T0_ISR:
  MOV   TL0,#TL0_RESET        ; Reload lower 8-bits
  MOV   TH0,#TH0_RESET        ; Reload upper 8-bits
  INC   DBG_ISR               ; Increment debug counter
  ACALL Store_ISR_DBG         ; Write the debug value
  CLR   P1.1                  ; ISR status pin low
  RETI


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Debug routines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Stores debug value for the Main loop by taking the least significant 7 bits
;; and sending them as data for an external write to 0x0000
Store_Main_DBG:
  MOV   A,DBG_MAIN            ; Load debug counter into ACC
  ANL   A,#~DBG_MASK          ; Clear the highest bit to signify Main (00h-7Fh)
  MOVX  @DPTR,A               ; Write debug counter to external memory
  RET

;; Stores debug value for the ISR by setting the high bit and sending that
;; value as data for an external write to 0x0000
Store_ISR_DBG:
  MOV   R1,A                  ; Save accumulator
  MOV   A,DBG_ISR             ; Load debug counter into ACC
  ORL   A,#DBG_MASK           ; Set the highest bit to signify ISR (80h-FFh)
  MOVX  @DPTR,A               ; Write debug counter to external memory
  MOV   A,R1                  ; Restore accumulator
  RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Initialization
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Init:
  CLR   P1.1                  ; ISR status pin low
  MOV   R0,#ISR_ITERS         ; Initialize the ISR tally (downcount)
  ;; Timer0 mode setting for simple 16-bit timer
  MOV   TMOD,#TMOD_T0_16BIT|TMOD_T0_TIMER|TMOD_T0_NOGATE
  MOV   TL0,#TL0_RESET        ; Reload lower 8-bits
  MOV   TH0,#TH0_RESET        ; Reload upper 8-bits
  SETB  IE.7                  ; Enable interrupts (EA=1)
  SETB  IE.1                  ; Enable timer 0 overflow interrupts (ET0=1)
  MOV   DPTR,#0                 ; Set data pointer to 0x0000 to trigger debug
  MOV   DBG_MAIN,#0           ; Zero Debug counters
  MOV   DBG_ISR,#0
  SETB  TCON.4                ; Start timer 0 (TR0=1)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EndLoop:
  INC   DBG_MAIN              ; Increment debug counter (7-bit)
  ACALL Store_Main_DBG        ; Write the debug value
  AJMP  EndLoop
