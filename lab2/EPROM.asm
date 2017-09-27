;; File: eprom.asm
;; Author: Jeff Schornick
;;
;; ECEN5613 Lab #2
;;
;; Run a simple loop that continously toggles Pin P1.1 to verify that we are
;; actually running code out of EPROM.
;;
;; Based on "LogicPort Logic Analyzer Example" from the class notes.


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main program entry point
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ORG $0000
Start:
  AJMP  Toggle                  ; Jump to toggle code

  ORG $0040
Toggle:
  NOP                           ; 1 cycle delay
  CPL  P1.1                     ; Toggle Pin P1.1
  NOP                           ; 1 cycle delay
  AJMP Start                    ; Loop back to start
