	ORG 0

	MOV SCON, #01010000B 	; Serial Mode 1 + Receiver Enable 
	MOV TMOD, #00100000B 	; Timer Mode 2 (auto reload)
	MOV TH1,  #253D      	; Baud Rate 9600
	SETB TR1		; Start timer

LOOP:	MOV SBUF,#'A' 		; Send to the serial port
	JNB TI,$ 		; Wait until the byte has been sent
	CLR TI			; Reset flag
	JMP LOOP		

	END			; Logic end