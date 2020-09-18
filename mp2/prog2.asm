;; partners: dhruvv2, sasinkg2, akshay5
; For this mp we decided to split the code into all the different operators
; We also implemented a print function and a bit shift function
; We had trouble with figuring out the exponents, division, multiplication, subtraction and sometimes
; our program would go into an infinite loop, so we had to step through it multiple times to find out our errors
; We also thought that we needed a stack pointer since R6 wasn’t doing anything
; We then figured out  that it was already implemented for us, but it was using a different register that we were changing the value of;
;
;
.ORIG x3000
	
;your code goes here
KBIN
	GETC
	OUT
	LD R1, SPACE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R0 ; check if keyboard was space
	BRz KBIN ; if space get a new input
	BRnzp EVALUATE	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

SETPRINT
	ST R7, SAVE_R7
	ST R5, SAVE_R5
	AND R2, R2, #0
	ADD R2, R2, #4

PRINT_HEX
	AND R0, R0, #0
	AND R1, R1, #0
	ADD R1, R1, #4

BITSET
	ADD R5, R5, #0 ; check R5 bit
	BRzp NOTHING ; if positive, add nothing and loop again
	ADD R0, R0, #1 ; add 1 to bit holder
NOTHING
	ADD R5, R5, R5 ; shift hist holder left
	ADD R0, R0, R0 ; shift bit value left
	ADD R1, R1, #-1 ; increment bitset loop
	BRnp BITSET ; loop BITSET 4 times

	ADD R0, R0, #0
	BRz ZERO
HALF
	ADD R1, R1, #1
	ADD R0, R0, #-2
	BRp HALF	; divide by 2 loop to get the correct hex value
	ADD R1, R1, #-10 ; check if value is larger than 10
	BRn READYPRINT
	ADD R1, R1, #7 ; if larger than 10 add 7 for correct ascii
READYPRINT
	ADD R1, R1, #10 ; add 10 to fix the subtract 10 above
ZERO
	LD R7, ASCII
	ADD R0, R1, R7 ; add ascii offset to get ascii numbers
	OUT
	ADD R2, R2, #-1; increment hex digit counter
	BRnp PRINT_HEX ; loop PRINT_HEX four times
	LD R5, SAVE_R5
	LD R7, SAVE_R7
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here
	LD R1, EQUAL
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R0 ; check if keyboard was equal
	BRnp #7 ; if not, check next symbol
	JSR POP ; pop expression answer value
	ADD R5, R5, #-1 ; check underflow
	BRz INVALID
	AND R5, R5, #0
	ADD R5, R0, #0 ; load value to R5 for print
	JSR SETPRINT ; go to print
	BRnzp DONE

	LD R1, MULT
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R0 ; check if keyboard was multiply operator
	BRnp #10 ; 
	AND R3, R3, #0
	AND R4, R4, #0
	JSR POP
	ADD R3, R3, R0
	JSR POP
	ADD R4, R4, R0 ; pop integer values to R3 and R4
	ADD R5, R5, #-1 ; check underflow
	BRz INVALID
	JSR MUL
	BRnzp KBIN

	LD R1, ADDS
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R0 ; check if keyboard was addition operator
	BRnp #10 ; 
	AND R3, R3, #0
	AND R4, R4, #0
	JSR POP
	ADD R4, R4, R0
	JSR POP
	ADD R3, R3, R0 ; pop integer values to R3 and R4
	ADD R5, R5, #-1 ; check underflow
	BRz INVALID
	JSR PLUS
	BRnzp KBIN

	LD R1, SUBT
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R0 ; check if keyboard was subtraction operator
	BRnp #10 ; 
	AND R3, R3, #0
	AND R4, R4, #0
	JSR POP
	ADD R4, R4, R0
	JSR POP
	ADD R3, R3, R0 ; pop integer values to R3 and R4
	ADD R5, R5, #-1 ; check underflow
	BRz INVALID
	JSR MIN
	BRnzp KBIN

	LD R1, DIVIDE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R0 ; check if keyboard was division operator
	BRnp #10 ; 
	AND R3, R3, #0
	AND R4, R4, #0
	JSR POP
	ADD R3, R3, R0	
	JSR POP
	ADD R4, R4, R0 ; pop integer values to R3 and R4
	ADD R5, R5, #-1 ; check underflow
	BRz INVALID
	JSR DIV
	BRnzp KBIN

	LD R1, EXPO
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R0 ; check if keyboard was exponential operator
	BRnp #10 ; 
	AND R3, R3, #0
	AND R4, R4, #0
	JSR POP
	ADD R4, R4, R0
	JSR POP
	ADD R3, R3, R0 ; pop integer values to R3 and R4
	ADD R5, R5, #-1 ; check underflow
	BRz INVALID
	JSR EXP
	BRnzp KBIN

	LD R1, ASCII
	NOT R1, R1
	ADD R1, R1, #1 ; make ascii offset negative to subtract
	ADD R2, R0, #0
	ADD R0, R1, R2 ; subtract ascii offset
	BRn INVALID
	AND R2, R2, #0 ; set R2 to check integer
	ADD R2, R2, R0
	ADD R2, R2, #-10 ; subtract 10 to check integer between 0-9
	BRzp #2; push for integer
	JSR PUSH
	BRnzp KBIN

	BRnzp INVALID

DONE
	HALT

INVALID ; handle invalid characters
	LEA R0, WRONG
	PUTS
	BRnzp DONE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ST R7, SAVE_R7
	ADD R0, R3, R4 ; add the two values
	JSR PUSH
	LD R7, SAVE_R7
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	ST R7, SAVE_R7
	NOT R4, R4
	ADD R4, R4, #1 ; make R4 integer value negative
	ADD R0, R3, R4 ; add the negative R4 value to R3 for subtraction
	JSR PUSH
	LD R7, SAVE_R7
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ST R7, SAVE_R7
	AND R0, R0, #0
MULTLOOP
	ST R7, SAVE_R7
	ADD R0, R0, R3 ; repeated addition loop for multiplication
	ADD R4, R4, #-1
	BRp MULTLOOP ; loop until R4 is 0
	JSR PUSH
	LD R7, SAVE_R7
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	ST R7, SAVE_R7
	AND R0, R0, #0
	NOT R3, R3
	ADD R3, R3, #1 ; get negative of R3
DIVLOOP
	ADD R4, R4, R3 ; subtraction loop for division
	BRnz #2
	ADD R0, R0, #1 ; division counter
	BRnzp DIVLOOP
	JSR PUSH
	LD R7, SAVE_R7
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	STI R7, SAVE_R7
	AND R0, R0, #0
EXPLOOP2
	LDR R1, R3, #0
EXPLOOP1
	ADD R0, R0, R3
	AND R1, R1, #-1
	BRp EXPLOOP1 ; loop multiplication for R3*R3
	ADD R4, R4, #-1 
	BRp EXPLOOP2 ; loop the mult loop R4 times
	JSR PUSH
	LD R7, SAVE_R7
	RET


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

SPACE 		.FILL x0020
SAVE_R5		.FILL x0000
SAVE_R7 	.FILL x0000
STACK_TOP	.FILL x4000	;
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
ASCII 		.FILL x0030
EQUAL 		.FILL x003D
MULT 		.FILL x002A
ADDS 		.FILL x002B
SUBT 		.FILL x002D
DIVIDE 		.FILL x002F
EXPO 		.FILL x005E
WRONG 		.STRINGZ "Invalid Expression"



.END

