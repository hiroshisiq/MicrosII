;;;;;;;;;;;;;;;	HEADER ;;;;;;;;;;;;;;;;;;
	BX	EQU P2
	LX	EQU P0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	ORG 0

	MOV 	TMOD, #01H
	
MAIN:	MOV 	A, BX			
	CJNE 	A, #0FFH, LOOP		; Verifica se algum botao foi apertado
	SJMP 	MAIN

LOOP:	MOV 	LX, A			; Escreve no LED de mesmo número da sequência
	ACALL 	ATRASO
	RL 	A			; Liga o próximo LED, na próxima iteração
	CJNE 	A, #11111110B, LOOP	; Liga LED por LED até o ultimo, neste caso, desliga todos e sai do loop
	SJMP 	MAIN

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