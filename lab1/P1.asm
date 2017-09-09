;; File: P1.asm
;; Author: Jeff Schornick
;;
;; ECEN5613 Lab #1, P1
;;
;; Calculates the result of the following equation using integer division:
;;   Z = ((X+1)/Y)*4
;;
;; The parameters X and Y should be assigned as follows:
;;   X (addend) - > A (accumluator)
;;   Y (divisor) -> B

;; Address locations for results / errors
SUM_ADDR:  EQU $20              ; Sum of X+1
QUOT_ADDR: EQU $21              ; Quotient of (X+1)/Y
REM_ADDR:  EQU $22              ; Remainder of (X+1)/Y
Z_ADDR:    EQU $23              ; Result of ((X+1)/Y)*4
ERR_ADDR:  EQU $30              ; Error code

; Error codes
NO_ERR:   EQU 00h               ; No error
ERR_ADD:  EQU 01h               ; Overflow on addition
ERR_DIVZ: EQU 02h               ; Division by zero
ERR_MUL:  EQU 03h               ; Overflow on multiplication

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main program entry point
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ORG $0000
Init:
  MOV  A,#02Ah                  ; Addend (X)
  MOV  B,#07h                   ; Divisor (Y)
  MOV  ERR_ADDR,#0              ; Initialize to no error

;; Summation sub-calculation of (X+1)
;; Pre:  X set in ACC
;; Post: Sum stored at SUM_ADDR, or error on overflow
DoAdd:
  ADD  A,#1                     ; Perform addition which sets carry on overflow
  MOV  SUM_ADDR,A               ; Store result
  JNC  DoDiv                    ; Continue if no overflow

  ; Overflow occurred
  MOV  R0,#ERR_ADD              ; Overflow, set error code
  SJMP Error

;; Division sub-calculation of (X+1)/Y
;; Pre:  Divisor set in B, dividend in ACC
;; Post: Quotent stored in QUOT_ADDR, remainder stored in REM_ADDR,
;;       or error on divide-by-zero
DoDiv:
  MOV  R1,B                     ; Load divisor into register for comparison
  CJNE R1,#0,Div2               ; Check if divisor is zero

  ; Divisor was zero
  MOV  R0,#ERR_DIVZ             ; Divide by zero error code
  SJMP Error

;; Parameters valid, continue with divide
;; Divisor now set in R1, divident still in ACC
Div2:
  MOV  R2,#0                    ; Initialize quotient counter
  CLR  C                        ; Clear carry so it isn't subtracted
DivLoop:
  SUBB A,R1                     ; Subtract divisor from current remainder
  INC  R2                       ; Increment quotient
  JNC  DivLoop                  ; Continue until we've subtracted too many times

  ; We've subtracted past zero, so add back one to correct
  ADD  A,R1                     ; Correct remainder
  MOV  REM_ADDR,A               ; Store final remainder result
  DEC  R2                       ; Correct quotient
  MOV  QUOT_ADDR,R2             ; Store final quotient result

  XCH  A,R2                     ; Swap quotient into ACC for next section

;; Multiplication calculation of ((X+1)/Y)*4
;; Pre:  First factor stored in A
;; Post: Final result stored at Z_ADDR, or error on overflow
DoMul:
  CLR  C
  RLC  A                        ; Multiply by 2
  MOV  PSW.6,C                  ; Save carry bit of first multiply in alternate-carry
  CLR  C                        ; Clear carry so it doesn't rotate a 1 to bit 0
  RLC  A                        ; Multiply by 2 again (4x total)
  ORL  C,PSW.6                  ; Set carry if either operation overflowed
  MOV  Z_ADDR,A                 ; Store final result
  JNC  EndLoop

  ; Overflow occured
  MOV  R0,#ERR_MUL              ; Overflow, set error code

; Generic error handling
; Pre:  Error code set in R0
; Post: Error code stored at ERR_ADDR
Error:
  MOV  ERR_ADDR,R0

EndLoop:
	SJMP EndLoop                  ; Infinite loop
