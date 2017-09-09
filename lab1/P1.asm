; File: P1.asm
; Author: Jeff Schornick
;
; ECEN5613 Lab #1, P1
;
; Calculates the result of the following equation using integer division:
;   Z = ((X+1)/Y)*4
;
; The parameters X and Y should be assigned as follows:
;   X (addend) - > A (accumluator)
;   Y (divisor) -> B

; Address locations for results / errors
SUM_ADDR:  EQU $20
QUOT_ADDR: EQU $21
REM_ADDR:  EQU $22
Z_ADDR:    EQU $23
ERR_ADDR:  EQU $30

; Error codes
NO_ERR:   EQU $00
ERR_ADD:  EQU $01
ERR_DIVZ: EQU $02
ERR_MUL:  EQU $03

; Main program entry point

      ORG $0000
Init:
  MOV  A,#0FFh               ; Addend (X)
  MOV  B,#07h               ; Divisor (Y)

; Calculate (X+1), store result at 0x20
DoAdd:
  ADD A,#1                 ; Perform addition which sets carry on overflow
  JNC DoDiv                ; Continue if no overflow

  ; Overflow error
  MOV R0,#ERR_ADD
  JC  ERROR

; Calculate (X+1)/Y, store quotient at 0x21, remainder at 0x22
DoDiv:

; Calculate ((X+1)/Y)*4, store final result at 0x23
DoMul:
  AJMP ENDLOOP

; Generic error handling
  ; Error code should be set in R0
ERROR:
  MOV  ERR_ADDR,R0

ENDLOOP:
	AJMP ENDLOOP                   ; Infinite loop
