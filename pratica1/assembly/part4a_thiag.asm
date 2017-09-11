;;;;;;;;;;;;;;;	HEADER ;;;;;;;;;;;;;;;;;;
	BX	EQU P2
	LX	EQU P0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	ORG 0

MAIN:	MOV 	LX, BX
	SJMP 	MAIN
	
	END


