;; File: xram.asm
;; Author: Jeff Schornick
;;
;; ECEN5613 Lab #3
;;
;; Verify XRAM reads/writes to NVRAM
;;
;; The AT89C51 data memory map
;;    0x0000 .. 0x00FF  Internal XRAM
;;    0x0100 .. 0x03FF  Internal NVRAM based on XSR settinh
;;    0x0400 .. 0x7FFF  External NVRAM

ISR_BASE:   EQU $2000           ; Paulmon user programs start address
PROG_BASE:  EQU ISR_BASE+0100h  ; first 256 byte boundary after last ISRs

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Constants
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; With a 11.0592MHz oscillator, machine cycle frequency is 921.6 KHz
TIMER_COUNT: EQU 9216   ; 16-bit counter value, 9216 cycles = 0.01s until overflow

;; The 8051 timers count up and overflow from all 1s to all 0s.
;; Calculate reset values that trigger overflow after exactly TIMER_COUNT cycles
TL0_RESET:   EQU ((65535-TIMER_COUNT)+1)&0FFh ; Lower 8 bits
TH0_RESET:   EQU ((65535-TIMER_COUNT)+1)>8    ; Upper 8 bits

ISR_ITERS:   EQU 50     ; number of ISR iterations before toggling LED (0.5s)

;; High bit of debug register value
;;  - cleared for Main (0x00 - 0x7F)
;;  - set for ISR (0x80 - 0xFF)
DBG_MASK:  EQU 080h           ; High bit of debug value


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Register definitions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; AUXR: Auxillary Register (reset: XX0X00Y0, Y=HSB.XRAM bit)
AUXR:             EQU $8E
AUXR_AO_NORMAL:   EQU 000h      ; Normal 8051 ALE signal
AUXR_AO_EXT:      EQU 001h      ; ALE onnly on MOVX/MOVC
AUXR_EXTRAM_INT:  EQU 000h      ; Use internal XRAM
AUXR_EXTRAM_EXT:  EQU 002h      ; All XRAM external
AUXR_XSR_256:     EQU 000h      ; 256 byte internal XRAM
AUXR_XSR_512:     EQU 004h      ; 512 byte internal XRAM
AUXR_XSR_768:     EQU 008h      ; 768 byte internal XRAM
AUXR_XSR_1024:    EQU 00Ch      ; 1024 byte internal XRAM
AUXR_M0_6CLK:     EQU 000h      ; 6 clock RD/WR for MOVX
AUXR_M0_30CLK:    EQU 020h      ; 30 clock RD/WR for MOVX
AUXR_DPU_ON:      EQU 000h      ; Enable weak pullups
AUXR_DPU_OFF:     EQU 080h      ; Disable weak pullups


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

  ORG PROG_BASE
  DB  0A5h,0E5h,0E0h,0A5h
  DB  35,255,0,0
  DB  0,0,0,0
  DB  0,0,0,0
  DB  0,0,0,0
  DB  0,0,0,0
  DB  0,0,0,0
  DB  255,255,255,255
  STR 'XRAM'
  DB  0
  ORG (PROG_BASE+64)

Start:
  AJMP  Init                  ; Jump over ISRs to main routine


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Interrupt Service Routines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Initialization
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Init:
  CLR   P1.1                  ; ISR status pin low
  MOV   AUXR,#AUXR_XSR_1024|AUXR_EXTRAM_INT ; Use 1024b internal XRAM

TimerInit:
  MOV   R0,#ISR_ITERS         ; Initialize the ISR tally (downcount)
  ;; Timer0 mode setting for simple 16-bit timer
  MOV   TMOD,#TMOD_T0_16BIT|TMOD_T0_TIMER|TMOD_T0_NOGATE
  MOV   TL0,#TL0_RESET        ; Reload lower 8-bits
  MOV   TH0,#TH0_RESET        ; Reload upper 8-bits
  SETB  IE.7                  ; Enable interrupts (EA=1)
  SETB  IE.1                  ; Enable timer 0 overflow interrupts (ET0=1)
  SETB  TCON.4                ; Start timer 0 (TR0=1)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Main:

  ;; Write tests
  ;;;;;;;;;;;;;;

  ;; 0x0000 - 0x00FF : always internal XRAM
  MOV   DPTR,#$00A0
  MOV   A,#023h
  MOVX  @DPTR,A

  ;; 0x0100 - 0x01FF : external XRAM when XRS >= 01
  MOV   DPTR,#$01B1
  MOV   A,#042h
  MOVX  @DPTR,A

  ;; 0x0200 - 0x02FF : external XRAM when XRS >= 10
  MOV   DPTR,#$02C2
  MOV   A,#055h
  MOVX  @DPTR,A

  ;; 0x0300 - 0x03FF : external XRAM when XRS == 11
  MOV   DPTR,#$03D3
  MOV   A,#077h
  MOVX  @DPTR,A

  ;; 0x0400 - 0x7FFF : always external XRAM
  MOV   DPTR,#$04A0
  MOV   A,#0DEh
  MOVX  @DPTR,A

  MOV   DPTR,#$7FAB
  MOV   A,#0ADh
  MOVX  @DPTR,A

  ;; 0x8000 - 0xFFFF : XRAM, but not mapped to NVRAM
  MOV   DPTR,#$8ABC
  MOV   A,#0EEh
  MOVX  @DPTR,A

  ;; Read tests
  ;;;;;;;;;;;;;;

  ;; 0x0000 - 0x00FF : always internal XRAM
  MOV   DPTR,#$00A0
  MOV   A,#023h
  MOVX  A,@DPTR

  ;; 0x0100 - 0x01FF : external XRAM when XRS >= 01
  MOV   DPTR,#$01B1
  MOV   A,#042h
  MOVX  A,@DPTR

  ;; 0x0200 - 0x02FF : external XRAM when XRS >= 10
  MOV   DPTR,#$02C2
  MOV   A,#055h
  MOVX  A,@DPTR

  ;; 0x0300 - 0x03FF : external XRAM when XRS == 11
  MOV   DPTR,#$03D3
  MOV   A,#077h
  MOVX  A,@DPTR

  ;; 0x0400 - 0x7FFF : always external XRAM
  MOV   DPTR,#$04A0
  MOV   A,#0DEh
  MOVX  A,@DPTR

  MOV   DPTR,#$7FAB
  MOV   A,#0ADh
  MOVX  A,@DPTR

  ;; 0x8000 - 0xFFFF : XRAM, but not mapped to NVRAM
  MOV   DPTR,#$8ABC
  MOV   A,#0ADh
  MOVX  A,@DPTR

  AJMP Main

  ORG (ISR_BASE+0Bh)
T0_ISR:
;; NB: TF0 is automatically cleared upon entry
  SETB  P1.1                  ; ISR status pin high
  DJNZ  R0,End_T0_ISR         ; Decrement ISR tally and exit if nonzero
  CPL   P1.2                  ; Toggle LED pin
  MOV   R0,#ISR_ITERS         ; Reset ISR counter to max value

End_T0_ISR:
  MOV   TL0,#TL0_RESET        ; Reload lower 8-bits
  MOV   TH0,#TH0_RESET        ; Reload upper 8-bits
  CLR   P1.1                  ; ISR status pin low
  RETI


