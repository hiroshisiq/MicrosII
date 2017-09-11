	ORG 0
	JMP MLOOP		; Jump to main loop

	ORG 0023H		; Serial Interruption
	JMP SERIAL 

MLOOP:	MOV SCON, #01010000B 	; Serial Mode 1 + Receiver Enable 
	MOV TCON, #00100000B 	; Timer Mode 2 (auto reload)
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

PRINT0: MOV R0, #MAN
	MOV R1, 12D
LOOP0:	DJNZ R1, ENDPRINT
	MOV A, @R0
	INC R0
	ACALL SEND
	SJMP LOOP0
	
PRINT1: MOV R0, #TREE
	MOV R1, 15D
LOOP1:	DJNZ R1, ENDPRINT
	MOV A, @R0
	INC R0
	ACALL SEND
	SJMP LOOP1
	
PRINT2:	MOV R0, #RICK
	MOV R1, 10D
LOOP2:	DJNZ R1, ENDPRINT
	MOV A, @R0
	INC R0
	ACALL SEND
	SJMP LOOP2
	
PRINT3:	MOV R0, #DF
	MOV R1, 8D
LOOP3:	DJNZ R1, ENDPRINT
	MOV A, @R0
	INC R0
	ACALL SEND
	SJMP LOOP3
	
PRINT4:	MOV R0, #PROF
	MOV R1, 31D
LOOP4:	DJNZ R1, ENDPRINT
	MOV A, @R0
	ACALL SEND
	SJMP LOOP4

ENDPRINT:	RET

SEND:	MOV SBUF, A 		; Send to the serial port
	JNB TI,$ 		; Wait until the byte has been sent
	CLR TI			; Reset flag
	RET			; Return


	ORG 0A0H
MAN:	DB 'KKJ EAE MAN' 	; 11 letters
	ORG 0B0H
TREE:	DB 'Happy lil tree'	; 14 letters
	ORG 0C0H
RICK:	DB 'eez Rick'		; 9 letters
	ORG 0D0H
DF:	DB 'Default'		; 7 letters
	ORG 0E0H
PROF:	DB 'Evandro Luis Linhari Rodrigues'	; 30 letters
	
	END			; Logic end