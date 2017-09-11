	ORG 0
	JMP MLOOP		; Jump to main loop

	ORG 0023H		; Serial Interruption
	JMP SERIAL 

MLOOP:	MOV SCON, #01010000B 	; Serial Mode 1 + Receiver Enable 
	MOV TMOD, #00100000B 	; Timer Mode 2 (auto reload)
	MOV TH1,  #253D      	; Baud Rate 9600
	MOV IE,   #10010000B 	; Enable interrupt
	SETB TR1		; Start timer

	JMP $			; Wait	

SERIAL: CLR ES			; Disable interrupt
	CLR RI			; Reset flag
	MOV SBUF, SBUF 		; Send to the serial port
	JNB TI,$ 		; Wait until the byte has been sent
	CLR TI			; Reset flag
	SETB ES			; Enable interrupt
	RETI			; Return 
	
	END			; Logic end