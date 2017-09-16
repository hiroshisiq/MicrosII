; 			HEADER					;
;			LCD 4 BITS MODE				;
	DB0	EQU	P1.0
	DB1	EQU	P1.1
	DB2	EQU	P1.2
	DB3	EQU	P1.3
	DB4	EQU	P1.4
	DB5	EQU	P1.5
	DB6	EQU	P1.6
	DB7	EQU	P1.7
	BUS	EQU	P0
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

	
	
	MOV 	A, #06H
	LCALL	POS			; Move o cursor para a posição desejada

	MOV	DPTR, #FRASE

	LCALL	WRITE_FRASE		; Escreve a sequencia de caracteres q esta em #FRASE
	MOV	A, #44H			; Muda o cursor de posição
	LCALL 	POS
	LCALL	WRITE_FRASE		; Escreve a proxima sequencia de caracters
	SJMP 	$


WRITE_FRASE:	MOV	A, #00H
	MOVC	A, @A+DPTR
	INC	DPTR			; Incrementa o DPTR para a próxima iteração
	CJNE	A, '$', LOOP2		; Chama a função WRITE até encontrar o caractere $
	SJMP	STOP
LOOP2:	LCALL 	WRITE
	SJMP	WRITE_FRASE
STOP:	RET


CONV:	MOV 	R6, A			; Junta o nibble de configuração, para a escrita, com o nibble de dados 
	ANL	A, #0F0H
	ANL	BUS, #0FH
	ORL	A, BUS
	MOV	BUS, A
	MOV	A, R6
	RET

SEND:	SETB 	ENAB			; Envia o dado para o LCD
	LCALL	CONV
	CLR	ENAB
	LCALL	WAIT
	RET
	
WRITE:	CLR	RW			; Configura a escrita e envia o caractere a 
	SETB 	ENAB			; ser escrito no LCD
	SETB 	RS
	
	LCALL	SEND
	SWAP	A
	LCALL	SEND
	
	RET

CLEAR:	CLR	RW		
	SETB 	ENAB
	CLR 	RS

	MOV 	A, #01H			; Este comando apaga todo o display do LCD
	LCALL 	SEND			; E coloca o cursor no início
	SWAP 	A
	LCALL	SEND
	RET
	
POS:	CLR	RW			
	SETB 	ENAB
	CLR 	RS
	ADD 	A, #80H			; Esse comando faz com que o cursor seja movido
	LCALL 	SEND			; para a posição #A
	SWAP 	A
	LCALL 	SEND
	RET
	
INIT:	CLR	RW
	SETB 	ENAB
	CLR 	RS

	MOV	A, #28H			; Configura para o modo 4 bits
	LCALL 	SEND
	SWAP 	A
	LCALL 	SEND
	
	SETB 	ENAB
	CLR 	RS
	MOV	A, #0EH			; Liga o display e o cursor
	LCALL	SEND
	SWAP 	A
	LCALL 	SEND

	CLR 	RS
	MOV	A, #06H			; Configura o cursor andar para a direita
	LCALL	SEND
	SWAP 	A
	LCALL	SEND
	RET

WAIT:	SJMP DELAY

DELAY:	MOV	TH0, #6CH		; this is for the number of cycles for th1 interrupt
	MOV	TL0, #00H		; Delay de 2.5ms
	SETB	TR0
	JNB	TF0, $
	CLR	TF0
	CLR 	TR0
	RET

DELAY_30:	MOV	R5, #08H	; delay de 20ms
LOOP_30:	LCALL 	WAIT
		DJNZ	R5, LOOP_30
		
FRASE:	DB	'MODO', '$','4 BITS','$'

	END

