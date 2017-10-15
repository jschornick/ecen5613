;; File: dump.asm
;; Author: Jeff Schornick
;;
;; ECEN5613 Lab #3
;;
;; Paulmon command to dump all XRAM
;;
;; The AT89C51 data memory map
;;    0x0000 .. 0x00FF  Internal XRAM
;;    0x0100 .. 0x03FF  Internal NVRAM based on XSR settinh
;;    0x0400 .. 0x7FFF  External NVRAM
;; Code memory map
;;    0x0000 .. 0x0FFF  Paulmon
;;    0x1000 .. 0x1FFF  Paulmon extras
;;    0x2000 .. 0x2053  Vectored ISRs

.equ  PROG_BASE, 0x3000


;; Paulmon subroutines
.equ	cout, 0x0030		;print Acc to Serial Port
.equ    pHex, 0x0034            ;Print Hex value of Acc
.equ    pHex16, 0x0036          ;Print Hex value of DPTR
.equ    newline, 0x0048         ;print CR/LF (13 and 10)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Register definitions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; AUXR: Auxillary Register (reset: XX0X00Y0, Y=HSB.XRAM bit)
.equ AUXR, 0x008E
.equ AUXR_AO_NORMAL, 0x00h      ; Normal 8051 ALE signal
.equ AUXR_AO_EXT, 0x01h      ; ALE onnly on MOVX/MOVC
.equ AUXR_EXTRAM_INT, 0x00h      ; Use internal XRAM
.equ AUXR_EXTRAM_EXT, 0x02h      ; All XRAM external
.equ AUXR_XSR_256, 0x00h      ; 256 byte internal XRAM
.equ AUXR_XSR_512, 0x04h      ; 512 byte internal XRAM
.equ AUXR_XSR_768, 0x08h      ; 768 byte internal XRAM
.equ AUXR_XSR_1024, 0x0Ch      ; 1024 byte internal XRAM
.equ AUXR_M0_6CLK, 0x00h      ; 6 clock RD/WR for MOVX
.equ AUXR_M0_30CLK, 0x20h      ; 30 clock RD/WR for MOVX
.equ AUXR_DPU_ON, 0x00h      ; Enable weak pullups
.equ AUXR_DPU_OFF, 0x80h      ; Disable weak pullups


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Paulmon program header
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.org PROG_BASE
  .db  0xA5,0xE5,0xE0,0xA5
  .db  35,255,0,0
  .db  0,0,0,0
  .db  0,0,0,0
  .db  0,0,0,0
  .db  0,0,0,0
  .db  0,0,0,0
  .db  255,255,255,255
  .db "XRAM dump",0
.org (PROG_BASE+64)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main program entry point
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Init:
  mov   AUXR,#AUXR_XSR_1024|AUXR_EXTRAM_INT ; Use 1024b internal XRAM

  mov dptr,#0
  mov R2, #8
  mov R1, #0

Line:
  lcall newline
  lcall pHex16
  mov A, #':'
  lcall cout
  mov R0, #16

Value:
  mov A, #' '
  lcall cout

  movx A, @dptr
  lcall pHex
  inc dptr

  djnz R0, Value
  djnz R1, Line
  djnz R2, Line

  ret
