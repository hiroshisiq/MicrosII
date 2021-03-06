; 			HEADER					;
;			LCD 8 BITS MODE				;
	BUS1	EQU	P0
	BUS2	EQU	P2
	ENAB	EQU	P0.2
	RW	EQU	P0.1
	RS	EQU	P0.0


; RS 0/1	Instruction/Data
; RW 0/1	Write/Read
; ENAB 1->0	Instruction/Data acquire	
	MOV 	TMOD, #00000001B		; MODE 1 FOR TIMER 0: 16 BITS COUNTER

	LCALL 	DELAY_30		; Delay inivial de 30 ms
	LCALL 	INIT			; Inicializa o display
	LCALL	CLEAR			; Zera o display
	
	MOV 	A, #06H			; Coloca o display na posição inicial desejada
	LCALL	POS

	MOV	DPTR, #FRASE

	LCALL	WRITE_FRASE		; Escreve o que está em @DPTR até encontrar $
	MOV	A, #44H			
	LCALL 	POS			; Muda posição do cursor
	LCALL	WRITE_FRASE		; Escreve o que está em DPTR
	SJMP 	$


WRITE_FRASE:	MOV	A, #00H		; Chama a função WRITE até encontrar um $ na 'string'
	MOVC	A, @A+DPTR
	INC	DPTR			; Incrementa o DPTR para a próxima iteração
	CJNE	A, '$', LOOP2
	SJMP	STOP
LOOP2:	LCALL 	WRITE
	SJMP	WRITE_FRASE
STOP:	RET


	

SEND:	SETB 	ENAB			; Envia o caractere
	LCALL	CONV
	CLR	ENAB
	LCALL	WAIT
	RET

CONV:	MOV 	R6, A			; Essa subrotina junta o nibble de configuração 
	ANL 	A, #0F0H		; com o de dado
	ANL 	BUS1, #0FH
	ORL 	BUS1, A
	MOV	A, R6
	ANL 	A, #0FH
	MOV	BUS2, A
	MOV 	A, R6
	RET

WRITE:	CLR	RW			; Configura o LCD para escrita e envia o caractere
	SETB 	ENAB
	SETB 	RS
	LCALL 	SEND
	RET

CLEAR:	CLR	RW
	SETB 	ENAB
	CLR 	RS
	MOV 	A, #01H			; Esse comando zera todas as posições do LCD
	LCALL 	SEND
	RET
	
POS:	CLR	RW
	SETB 	ENAB
	CLR 	RS
	ADD 	A, #80H			; Esse comando faz com que o cursor seja movido
	LCALL 	SEND			; para a posição #A

	RET
	
INIT:	CLR	RW
	SETB 	ENAB
	CLR 	RS
	MOV	A, #38H			; Configura no modo 8 bits, 2 linhas
	LCALL	SEND
	
	CLR 	RS
	MOV	A, #0EH			; Liga o display e o cursor
	LCALL 	SEND
	
	MOV	A, #06H			; O cursor andará para a direita
	LCALL 	SEND
	
	RET

DELAY:	MOV	TH0, #6CH		; this is for the number of cycles for th1 interrupt
	MOV	TL0, #00H		; Delay de 2.5 ms
	SETB	TR0
	JNB	TF0, $
	CLR	TF0
	CLR 	TR0
	RET

DELAY_30:	MOV	R5, #08H	; Delay de 20ms
LOOP_30:	LCALL 	WAIT
		DJNZ	R5, LOOP_30

FRASE:	DB	'MODO','$','8 BITS','$'

	END
