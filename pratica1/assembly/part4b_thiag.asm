;;;;;;;;;;;;;;;	HEADER ;;;;;;;;;;;;;;;;;;
	BX	EQU P2
	LX	EQU P0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	ORG 0

	MOV 	TMOD, #01H
	
MAIN:	MOV 	A, BX
	CJNE 	A, #0FFH, LOOP
	SJMP 	MAIN

LOOP:	MOV 	LX, A
	ACALL 	ATRASO
	RL 	A
	CJNE 	A, #11111110B, LOOP
	SJMP 	MAIN

;ATRASO:		MOV 	R2, #45D		; 251.6MS DELAY
;ATRASO2:	MOV	R1, #50D		;
;ATRASO1:	MOV 	R0, #50D		;((((R0*2)+3)*R1+3)*R2+3)*12/(f)
;		DJNZ	R0, $
;		DJNZ	R1, ATRASO1
;		DJNZ 	R2, ATRASO2	
;		RET

ATRASO:	ACALL 	DELAY
	ACALL 	DELAY
	ACALL 	DELAY
	ACALL 	DELAY
	ACALL 	DELAY
	RET
	
DELAY:	MOV	TH0, #high(19455D-11D)		; this is for the number of cycles for th1 interrupt
	MOV	TL0, #low(19455D-11D)		; 50ms delay
	SETB	TR0
	JNB	TF0, $
	CLR	TF0
	CLR 	TR0
	RET

	END