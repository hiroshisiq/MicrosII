;==============	HEADER ==================;
	D1 	EQU P2.4
	D2 	EQU P2.5
	D3 	EQU P2.6
	D4 	EQU P2.7
	DISPLAY	EQU P2
	NUMBER	EQU P0
	COUNT 	EQU 31H
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


	ORG 0
	MOV TMOD, #00000001B		; MODE 1 FOTT TIMER 0: 16 BITS COUNTER
	;SETB 	ET0	
	MOV	R7, #11101110B		; Used for display blinking
	SJMP MAIN

MAIN:	MOV 	A, #09H
	ACALL 	WRITE

	MOV 	A, #07H
	ACALL 	WRITE
	
	MOV 	A, #06H
	ACALL 	WRITE

	MOV 	A, #00H
	ACALL 	WRITE

	SJMP MAIN

	
WRITE:	MOV	R6, A
	MOV 	A, 	R7
	RR 	A
	MOV 	R7,	A		; Roll R7 right
	MOV 	A, R6
	
	MOV 	P2,	#0FFH		; Making sure all leds are off
	MOV 	DPTR,	#DATA1		; Get data header adress
	MOVC 	A, 	@A+DPTR		; Convert hex to 7 segments code
	MOV 	NUMBER, A		; Write number to display
	MOV 	DISPLAY,R7		; Turn the display on
	ACALL	ATRASO			; Delay
	RET
;
;ATRASO:		MOV 	R2, #20D		; ATRASO DE 30.2MS
;ATRASO2:	MOV	R1, #15D		;CALCULADO POR
;ATRASO1:	MOV 	R0, #10D	 		;((((R0*2)+3)*R1+3)*R2+3)*12/(f)
;		DJNZ	R0, $
;		DJNZ	R1, ATRASO1
;		DJNZ 	R2, ATRASO2	
;		RET

ATRASO:	MOV	TH0, #high(37703D-9D)		; this is for the number of cycles for th1 interrupt
	MOV	TL0, #low(37703D-9D)		; 30.2 ms delay
	SETB	TR0
	JNB	TF0, $
	CLR	TF0
	CLR 	TR0
	RET

DATA1:	DB 11000000B,11111001B,10100100B,10110000B,10011001B,10010010B,10000011B,11111000B,10000000B
	DB 10011000B
		

	END

