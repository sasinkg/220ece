;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

; partners: Dhruv Vishwanath (dhruvv2), Sasin Gudipati (sasinkg2), Akshay Sundaram (akshay5)

PRINT_HIST

; My approach to this MP was to convert the starting position of the
; histogram’s memory and then into a ASCII value. I used loops to achieve this,
; looping the conversion over until the R0 became a null character. 
; Here is the register table for printing
; R0 takes values to print
; R1 holds address of histogram
; R2 holds bin labels
; R3 holds a print counter set to 27
; R4 holds a set of 4 bits
; R5 holds value of histogram
; R6 is a temp register
    
    AND R0, R0, #0
    AND R1, R1, #0
    AND R2, R2, #0
    AND R3, R3, #0
    AND R4, R4, #0
    AND R5, R5, #0
    AND R6, R6, #0
    AND R7, R7, #0 ; clear registers
    
    LD R3, NUM_BINS
    LD R2, ATSYMBOL
    LD R1, HIST_ADDR

LINELOOP
    AND R0, R0, #0
    ADD R0, R0, R2 ; print bin label
    OUT
    AND R0, R0, #0
    LD R6, SPACE
    ADD R0, R0, R6 ; print space
    OUT
    LDR R5, R1, #0 ; load hist value from hist address
    AND R4, R4, #0
    ADD R4, R4, #4 ; set up counter for HEXPRINTER
    BRnzp HEXPRINTER ; branch to HEXPRINTER

FINISHPRINT
    AND R0, R0, #0
    LD R6, NEWLINE
    ADD R0, R0, R6 ; print newline char
    OUT
    ADD R2, R2, #1 ; increment bin label value
    ADD R1, R1, #1 ; increment hist address
    ADD R3, R3, #-1 ; increment print counter by -1
    BRp LINELOOP ; start printing a new line otherwise,
    BRnzp DONE ; end program

HEXPRINTER
    AND R0, R0, #0
    AND R6, R6, #0
    ADD R6, R6, #4

BITSET
    ADD R5, R5, #0 ; check R5 bit
    BRzp NOTHING ; if positive, add nothing and loop again
    ADD R0, R0, #1 ; add 1 to bit holder
NOTHING
    ADD R5, R5, R5 ; shift hist holder left
    ADD R0, R0, R0 ; shift bit value left
    ADD R6, R6, #-1 ; increment bitset loop
    BRnp BITSET ; loop BITSET 4 times

    ADD R0, R0, #0
    BRz ZERO
DIVIDE
    ADD R6, R6, #1
    ADD R0, R0, #-2
    BRp DIVIDE    
    ADD R6, R6, #-10
    BRn READYPRINT
    ADD R6, R6, #7
READYPRINT
    ADD R6, R6, #10
ZERO
    LD R7, ASCII
    ADD R0, R6, R7 ; add ascii offset to get ascii numbers
    OUT
    ADD R4, R4, #-1; increment hex digit counter
    BRnp HEXPRINTER ; loop HEXPRINTER four times
    BRnzp FINISHPRINT ; branch to FINISHPRINT







; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done

SPACE        .FILL x0020
NEWLINE        .FILL x000A
ATSYMBOL     .FILL x0040
ASCII         .FILL x0030

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
