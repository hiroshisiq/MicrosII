
	org 	0

	MOV	SCON, #50h 	; Serial Mode 1 + Receiver Enable 
	MOV	TMOD, #20h	; Timer Mode 2 (auto reload)
	MOV	TH1, #253d      ; Baud Rate 9600
	SETB	TR1		; Start timer

LOOP:	
	JNB	RI,$ 		; Wait until the byte has been received
	CLR	RI		; Reset flag
	MOV	SBUF, SBUF 	; Send to the serial port
	JNB	TI,$ 		; Wait until the byte has been sent
	CLR	TI		; Reset flag
	JMP	LOOP

	END			; Logic end