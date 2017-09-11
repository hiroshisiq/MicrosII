;==============	HEADER =================;
	CN1 	EQU	P1
	CN2 	EQU	P2
;============== CN1 BITS ===============;
	RS	EQU	P1.0
	RW	EQU	P1.1
	EN	EQU	P1.2
	DB4	EQU	P1.4
	DB5	EQU	P1.5
	DB6	EQU	P1.6
	DB7	EQU	P1.7
;============== CN2 BITS ===============;
	DB0	EQU	P2.0
	DB1	EQU	P2.1
	DB2	EQU	P2.2
	DB3	EQU	P2.3
;============== Aux ====================;
;	BUFF	EQU	R7
;==============	END HEADER =============;

;====== CONFIGURE: 4-BITS MODE =========;
CONFIG:	MOV	DPTR, #COMMAND
	MOV	CN1, #00h
	ACALL	SEND4
;=======================================;

;============ WRITE LINE ===============;
	SETB	RS			

	MOV	DPTR, #LINE0
	ACALL	SEND4

	MOV	DPTR, #LINE1
	ACALL	SEND4
	
	SJMP	$			; Logic end
;=======================================;

;=============== SEND ==================;
SEND4:	MOV	A, CN1			; Save last instrution
	ANL	A, #0B0h		; Clear all but RS and R/W
	MOV	R6, A			; Save on R6

	CLR	A			; Clear
	MOVC	A, @A+DPTR		; Read char
LOOP1:	MOV	R7, A			; Save copy of the byte

	SWAP	A			; Get high nibble
	ANL	A, #0Fh			; Clear all but the nibble
	ORL	A, R6			; Get RS and R/W configuration
	MOV	CN1, A			; Copy to port

	MOV	A, R7			; Get low nibble
	ANL	A, #0Fh			; Clear all but the nibble
	ORL	A, R6			; Get RS and R/W configuration
	MOV	CN1, A			; Copy to port

	INC	DPTR			; DPTR++
	CLR	A			; Clear
	MOVC	A, @A+DPTR		; Read char
	CJNE	A, #'$', LOOP1		; Jump while A != $
	
	RET				; Return
;=======================================;

;============== TABLES =================;
COMMAND:
	DB 33h, 32h, '$'
LINE0:	
	DB	'u ve been hacked', '$'
LINE1:	
	DB	' by hasckyboi97 ', '$'
;=======================================;

	END