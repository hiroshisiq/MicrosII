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


	MOV 	DPTR, #DATA1
	LCALL	WRITE_TEXT
	MOV	A, #40H
	LCALL	POS
	MOV	DPTR, #DATA2
	LCALL	WRITE_TEXT
	SJMP 	$

SEND:	SETB 	ENAB			; Envia o caracter a ser escrito
	LCALL	CONV
	CLR	ENAB
	LCALL	WAIT
	RET

CONV:	MOV 	R6, A			; Junta o nibble de configuração, para a escrita, com o nibble de dados
	ANL 	A, #0F0H
	ANL 	BUS1, #0FH
	ORL 	BUS1, A
	MOV	A, R6
	ANL 	A, #0FH
	MOV	BUS2, A
	MOV 	A, R6
	RET

WRITE:	CLR	RW
	SETB 	ENAB
	SETB 	RS
	LCALL 	SEND
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

	MOV	A, #28H			; Configura para o modo 8 bits, 2 linhas
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

WRITE_TEXT:
LOOP:	MOV	A, #00h
	MOVC	A, @A+DPTR
	CJNE	A, #'$', GO
	SJMP	PEND
GO:	INC	DPTR
	LCALL 	SEND	
	SJMP	LOOP

PEND:	RET			


WAIT:	SJMP DELAY
;
;DELAY:	MOV 	R2, #10D		; 2.53MS DELAY
;DELAY2:	MOV	R1, #10D			;
;DELAY1:	MOV 	R0, #10D			;((((R0*2)+3)*R1+3)*R2+3)*12/(f)
;	DJNZ	R0, $
;	DJNZ	R1, DELAY1
;	DJNZ 	R2, DELAY2
;			
;	RET
DELAY:	MOV	TH0, #6CH		; this is for the number of cycles for th1 interrupt
	MOV	TL0, #00H
	SETB	TR0
	JNB	TF0, $
	CLR	TF0
	CLR 	TR0
	RET

DELAY_30:	MOV	R5, #08H
LOOP_30:	LCALL 	WAIT
		DJNZ	R5, LOOP_30

DATA1:	DB 'Shirley','$'
DATA2:	DB 'Thiaguinho','$'

	END

