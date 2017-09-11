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
	MOV A, SBUF 		; Copy to acc
	ACALL TEST0		; Test value rotine
	SETB ES			; Enable interrupt
	RETI			; Return 

TEST0:	CJNE A, #'A', TEST1	; If 'A' print0
	ACALL PRINT0
	RET

TEST1:	CJNE A, #'B', TEST2	; If 'B' print1
	ACALL PRINT1
	RET

TEST2:	CJNE A, #'C', TEST3	; If 'C' print2
	ACALL PRINT2
	RET
TEST3:	CJNE A, #'D', TEST4	; If 'D' print3
	ACALL PRINT3
	RET


TEST4:	ACALL PRINT4		; Else print4
	RET

PRINT0: MOV DPTR, #MAN
	SJMP LOOP

PRINT1: MOV DPTR, #TREE
	SJMP LOOP
	
PRINT2: MOV DPTR, #RICK
	SJMP LOOP
	
PRINT3: MOV DPTR, #DF
	SJMP LOOP
	
PRINT4: MOV DPTR, #PROF
	SJMP LOOP

LOOP:	MOV 	A, #00h
	MOVC A, @A+DPTR
	CJNE A, #'$', GO
	SJMP ENDPRINT
GO:	INC DPTR
	ACALL SEND
	SJMP LOOP


ENDPRINT:	RET

SEND:	MOV SBUF, A 		; Send to the serial port
	JNB TI,$ 		; Wait until the byte has been sent
	CLR TI			; Reset flag
	RET			; Return

MAN:	DB 'KKJ EAE MAN \n\r','$' 	; 11 letters
TREE:	DB 'Happy lil tree \n\r','$'	; 14 letters
RICK:	DB 'Geez Rick \n\r','$'		; 9 letters
PROF:	DB 'Default \n\r','$'		; 7 letters
DF:	DB 'Evandro Luis Linhari Rodrigues \n\r','$'	; 30 letters
	
	END			; Logic end