;;;;;;;;;;;;;;;	HEADER ;;;;;;;;;;;;;;;;;;
	D1 	EQU P2.4
	D2 	EQU P2.5
	D3 	EQU P2.6
	D4 	EQU P2.7
	DISPLAY	EQU P2
	NUMBER	EQU P1
	FN	EQU 40H		; Flag: first number
	AN	EQU 41H		; Flag: all 4 numbers
	WORD 	EQU 31H	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


	ORG 0
	SJMP CONFIG

	ORG 0023H		; Serial Interruption
	JMP SERIAL 

CONFIG:	MOV SCON, #01010000B 	; Serial Mode 1 + Receiver Enable 
	MOV TMOD, #00100001B 	; Timer Mode 2 (auto reload)
	MOV TH1,  #253D      	; Baud Rate 9600
	MOV IE,   #10010000B 	; Enable interrupt
	SETB TR1		; Start timer

	MOV	R7, #11101110B		; Used for display blinking


MAIN:	CLR 	AN
	CLR 	FN
	JNB 	AN, $

GO:	MOV 	A, 31H
	ACALL 	WRITE

	MOV 	A, 32H
	ACALL 	WRITE
	
	MOV 	A, 33H
	ACALL 	WRITE

	MOV 	A, 34H
	ACALL 	WRITE

	SJMP 	GO	

	
WRITE:	PUSH	ACC			; Write to the display the number stored in @A
	MOV 	A, 	R7
	RR 	A
	MOV 	R7,	A		; Roll R7 right
	POP 	ACC
	
	MOV 	P2,	#0FFH		; Making sure all leds are off
	MOV 	DPTR,	#DATA1		; Get data header adress

	MOV	R0, 	A
	MOV	A, 	@R0		; Get the number stored in @A

	MOVC 	A, 	@A+DPTR		; Convert hex to 7 segments code
	MOV 	NUMBER, A		; Write number to display
	MOV 	DISPLAY,R7		; Turn the display on
	ACALL	ATRASO			; Delay

	RET


ATRASO:	MOV	TH0, #high(37703D-9D)		; this is for the number of cycles for th1 interrupt
	MOV	TL0, #low(37703D-9D)		; 30.2MS DELAY
	SETB	TR0
	JNB	TF0, $
	CLR	TF0
	CLR 	TR0
	RET

SERIAL:	CLR 	ES
	CLR 	RI

	CLR 	AN		; Clear all-numbers flag			
	JNB 	FN, CONT1	; Flag1: check if its the first time the interruption is called
	MOV 	R3, #31H	; R3 will be used as header adress of the users word
	MOV 	R4, #00H		
	SETB 	FN

CONT1:	MOV 	A, R3			
	MOV 	R0, A		; Put Header adress on R0 (pointer)

	MOV	A, SBUF		
	SUBB	A, #30H		; Transform number (char) to number (binary)
	MOV 	@R0, A		; Put on @R0 (users numbers list)
	
	INC 	R3
	INC 	R4
	CJNE 	R4, #04H, SER_END
	SETB 	AN
	CLR 	FN
	MOV 	R7, #11101110B

SER_END:	SETB 	ES
		RETI
	
;;;;;;;;;;;;;;;; TABLE ;;;;;;;;;;;;;;;;;;;;;;;;;
DATA1:	DB 01111110B,0110000B,1101101B,1111001B,0110011B,1011011B,0011111B,1110000B,1111111B
	DB 1110011B
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		

	END