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

  .equ PROG_BASE, 0x7100 


  ;; AUXR: Auxillary Register (reset: XX0X00Y0, Y=HSB.XRAM bit)
  .equ AUXR,          0x008E
  .equ AUXR_AO_NORMAL,  0x00      ; Normal 8051 ALE signal
  .equ AUXR_AO_EXT,     0x01      ; ALE onnly on MOVX/MOVC
  .equ AUXR_EXTRAM_INT, 0x00      ; Use internal XRAM
  .equ AUXR_EXTRAM_EXT, 0x02      ; All XRAM external
  .equ AUXR_XSR_256,    0x00      ; 256 byte internal XRAM
  .equ AUXR_XSR_512,    0x04      ; 512 byte internal XRAM
  .equ AUXR_XSR_768,    0x08      ; 768 byte internal XRAM
  .equ AUXR_XSR_1024,   0x0C      ; 1024 byte internal XRAM
  .equ AUXR_M0_6CLK,    0x00      ; 6 clock RD/WR for MOVX
  .equ AUXR_M0_30CLK,   0x20      ; 30 clock RD/WR for MOVX
  .equ AUXR_DPU_ON,     0x00      ; Enable weak pullups
  .equ AUXR_DPU_OFF,    0x80      ; Disable weak pullups


  .area PSEG  (PAG,XDATA)
  .area XSEG  (XDATA)
  .area HOME  (CODE)
  .area CABS  (ABS,CODE)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Reset / program entry point
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .org  PROG_BASE
  .db  0xA5,0xE5,0xE0,0xA5
  .db    35,255,0,0
  .ds    20
  .db    255,255,255,255
  .asciz "XRAM test"
  .org (PROG_BASE+64)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Initialization
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Init:
  MOV   AUXR,#AUXR_XSR_1024|AUXR_EXTRAM_INT ; Use 1024b internal XRAM


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Main:

  ;; Write tests
  ;;;;;;;;;;;;;;

  ;; 0x0000 - 0x00FF : always internal XRAM
  MOV   DPTR, #0x00A0
  MOV   A, #0x23
  MOVX  @DPTR, A

  ;; 0x0100 - 0x01FF : external XRAM when XRS >= 01
  MOV   DPTR, #0x01B1
  MOV   A, #0x042
  MOVX  @DPTR, A

  ;; 0x0200 - 0x02FF : external XRAM when XRS >= 10
  MOV   DPTR, #0x02C2
  MOV   A, #0x55
  MOVX  @DPTR, A

  ;; 0x0300 - 0x03FF : external XRAM when XRS == 11
  MOV   DPTR, #0x03D3
  MOV   A, #0x77
  MOVX  @DPTR, A

  ;; 0x0400 - 0x7FFF : always external XRAM
  MOV   DPTR, #0x04A0
  MOV   A, #0xDE
  MOVX  @DPTR, A

  MOV   DPTR, #0x7FAB
  MOV   A, #0xAD
  MOVX  @DPTR, A

  ;; 0x8000 - 0xFFFF : XRAM, but not mapped to NVRAM
  MOV   DPTR, #0x8ABC
  MOV   A, #0xEE
  MOVX  @DPTR, A

  ;; Read tests
  ;;;;;;;;;;;;;;

  ;; 0x0000 - 0x00FF : always internal XRAM
  MOV   DPTR, #0x00A0
  MOV   A, #0x23
  MOVX  A, @DPTR

  ;; 0x0100 - 0x01FF : external XRAM when XRS >= 01
  MOV   DPTR, #0x01B1
  MOV   A, #0x042
  MOVX  A, @DPTR

  ;; 0x0200 - 0x02FF : external XRAM when XRS >= 10
  MOV   DPTR, #0x02C2
  MOV   A, #0x55
  MOVX  A, @DPTR

  ;; 0x0300 - 0x03FF : external XRAM when XRS == 11
  MOV   DPTR, #0x03D3
  MOV   A, #0x77
  MOVX  A, @DPTR

  ;; 0x0400 - 0x7FFF : always external XRAM
  MOV   DPTR, #0x04A0
  MOV   A, #0xDE
  MOVX  A, @DPTR

  MOV   DPTR, #0x7FAB
  MOV   A, #0xAD
  MOVX  A, @DPTR

  ;; 0x8000 - 0xFFFF : XRAM, but not mapped to NVRAM
  MOV   DPTR, #0x8ABC
  MOV   A, #0xEE
  MOVX  A, @DPTR

  AJMP Main
