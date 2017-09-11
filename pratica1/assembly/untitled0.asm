;;;;;;;;;;;;;;;	HEADER ;;;;;;;;;;;;;;;;;;
	D1 	EQU P2.4
	D2 	EQU P2.5
	D3 	EQU P2.6
	D4 	EQU P2.7
	DISPLAY	EQU P2
	NUMBER	EQU P1
	FLAG1	EQU 40H
	FLAG2	EQU 41H
	WORD 	EQU 31H
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


	ORG 0
	SJMP CONFIG

	ORG 0023H		; Serial Interruption
	JMP SERIAL 

CONFIG:	MOV SCON, #01010000B 	; Serial Mode 1 + Receiver Enable 
	MOV TMOD, #00100000B 	; Timer Mode 2 (auto reload)
	MOV TH1,  #253D      	; Baud Rate 9600
	MOV IE,   #10010000B 	; Enable interrupt
	SETB TR1		; Start timer

	MOV	R7, #00010001B		; Used for display blinking


MAIN:	CLR FLAG2
	JNB FLAG2, $

GO:	MOV 	A, 31H
	ACALL 	WRITE

	MOV 	A, 32H
	ACALL 	WRITE
	
	MOV 	A, 33H
	ACALL 	WRITE

	MOV 	A, 34H
	ACALL 	WRITE

	SJMP GO

	
WRITE:	PUSH	A
	MOV 	A, 	R7
	RR 	A
	MOV 	R7,	A		; Roll R7 right
	POP A
	
	MOV 	P2,	#0FFH		; Making sure all leds are off
	MOV 	DPTR,	#DATA1		; Get data header adress
	MOVC 	A, 	@A+DPTR		; Convert hex to 7 segments code
	MOV 	NUMBER, A		; Write number to display
	MOV 	DISPLAY,R7		; Turn the display on
	ACALL	ATRASO			; Delay

	RET

ATRASO:		MOV 	R2, #80D		; 30.2MS DELAY
ATRASO2:	MOV	R1, #15D		;
ATRASO1:	MOV 	R0, #10D		;((((R0*2)+3)*R1+3)*R2+3)*12/(f)
		DJNZ	R0, $
		DJNZ	R1, ATRASO1
		DJNZ 	R2, ATRASO2	
		RET

SERIAL:	CLR ES
	CLR RI
	CLR FLAG2
	JB FLAG1, CONT1
	MOV R3, #31H				; R3 will be used as header adress of the users word
	MOV R4, #00H
	SETB FLAG1

CONT1:	MOV A, R3
	MOV R0, A
	MOV @R0, SBUF
	INC R3
	INC R4
	CJNE R4, #04H, SEREND
	SETB FLAG2
	CLR FLAG1
	MOV R7, #11101110B

SEREND:	SETB ES
	RETI
	
;;;;;;;;;;;;;;;; TABLE ;;;;;;;;;;;;;;;;;;;;;;;;;
DATA1:	DB 01111110B,0110000B,1101101B,1111001B,0110011B,1011011B,0011111B,1110000B,1111111B
	DB 1110011B
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		

	END



