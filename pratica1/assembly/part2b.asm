	ORG 0
	SJMP MLOOP			; Jump to main loop

	
MLOOP:	MOV	SCON, #01010000B 	; Serial Mode 1 + Receiver Enable 
	MOV	TMOD, #00100000B 	; Timer Mode 2 (auto reload)
	MOV	TH1,  #253D      	; Baud Rate 9600
	SETB	TR1			; Start timer
	
PRINT: 	MOV	DPTR, #FRASE

LOOP:	MOV	A, #00H			
	MOVC	A, @A+DPTR
	CJNE	A, #'$', GO
	SJMP	PEND
GO:	INC	DPTR
	ACALL	SERIAL
	SJMP	LOOP			; Repeat this loop until $ char is read
	
	
PEND:	JMP	$			; Logic end

	
SERIAL: MOV	SBUF, A 		; Send to the serial port
	JNB	TI,$ 			; Wait until the byte has been sent
	CLR	TI			; Reset flag
	RET				; Return 

FRASE:	DB	'KKJ EAE MAN', '$'
	END			; Logic end