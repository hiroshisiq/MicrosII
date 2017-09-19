;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW64)
;--------------------------------------------------------
	.module freq
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _timer1
	.globl _timer0
	.globl _getFrequency
	.globl _configure_timers
	.globl _write
	.globl _to2line
	.globl _clearLCD
	.globl _configure8bits
	.globl _send
	.globl _delay
	.globl _strcat
	.globl _sprintf
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _FL
	.globl _P
	.globl _TF2
	.globl _EXF2
	.globl _RCLK
	.globl _TCLK
	.globl _EXEN2
	.globl _TR2
	.globl _C_T2
	.globl _CP_RL2
	.globl _T2CON_7
	.globl _T2CON_6
	.globl _T2CON_5
	.globl _T2CON_4
	.globl _T2CON_3
	.globl _T2CON_2
	.globl _T2CON_1
	.globl _T2CON_0
	.globl _PT2
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _EA
	.globl _ET2
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _T2EX
	.globl _T2
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _B
	.globl _A
	.globl _ACC
	.globl _PSW
	.globl _TH2
	.globl _TL2
	.globl _RCAP2H
	.globl _RCAP2L
	.globl _T2MOD
	.globl _T2CON
	.globl _IP
	.globl _P3
	.globl _IE
	.globl _P2
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _waveCounter
	.globl _timerCount
	.globl _t0
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
G$P0$0$0 == 0x0080
_P0	=	0x0080
G$SP$0$0 == 0x0081
_SP	=	0x0081
G$DPL$0$0 == 0x0082
_DPL	=	0x0082
G$DPH$0$0 == 0x0083
_DPH	=	0x0083
G$PCON$0$0 == 0x0087
_PCON	=	0x0087
G$TCON$0$0 == 0x0088
_TCON	=	0x0088
G$TMOD$0$0 == 0x0089
_TMOD	=	0x0089
G$TL0$0$0 == 0x008a
_TL0	=	0x008a
G$TL1$0$0 == 0x008b
_TL1	=	0x008b
G$TH0$0$0 == 0x008c
_TH0	=	0x008c
G$TH1$0$0 == 0x008d
_TH1	=	0x008d
G$P1$0$0 == 0x0090
_P1	=	0x0090
G$SCON$0$0 == 0x0098
_SCON	=	0x0098
G$SBUF$0$0 == 0x0099
_SBUF	=	0x0099
G$P2$0$0 == 0x00a0
_P2	=	0x00a0
G$IE$0$0 == 0x00a8
_IE	=	0x00a8
G$P3$0$0 == 0x00b0
_P3	=	0x00b0
G$IP$0$0 == 0x00b8
_IP	=	0x00b8
G$T2CON$0$0 == 0x00c8
_T2CON	=	0x00c8
G$T2MOD$0$0 == 0x00c9
_T2MOD	=	0x00c9
G$RCAP2L$0$0 == 0x00ca
_RCAP2L	=	0x00ca
G$RCAP2H$0$0 == 0x00cb
_RCAP2H	=	0x00cb
G$TL2$0$0 == 0x00cc
_TL2	=	0x00cc
G$TH2$0$0 == 0x00cd
_TH2	=	0x00cd
G$PSW$0$0 == 0x00d0
_PSW	=	0x00d0
G$ACC$0$0 == 0x00e0
_ACC	=	0x00e0
G$A$0$0 == 0x00e0
_A	=	0x00e0
G$B$0$0 == 0x00f0
_B	=	0x00f0
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
G$P0_0$0$0 == 0x0080
_P0_0	=	0x0080
G$P0_1$0$0 == 0x0081
_P0_1	=	0x0081
G$P0_2$0$0 == 0x0082
_P0_2	=	0x0082
G$P0_3$0$0 == 0x0083
_P0_3	=	0x0083
G$P0_4$0$0 == 0x0084
_P0_4	=	0x0084
G$P0_5$0$0 == 0x0085
_P0_5	=	0x0085
G$P0_6$0$0 == 0x0086
_P0_6	=	0x0086
G$P0_7$0$0 == 0x0087
_P0_7	=	0x0087
G$IT0$0$0 == 0x0088
_IT0	=	0x0088
G$IE0$0$0 == 0x0089
_IE0	=	0x0089
G$IT1$0$0 == 0x008a
_IT1	=	0x008a
G$IE1$0$0 == 0x008b
_IE1	=	0x008b
G$TR0$0$0 == 0x008c
_TR0	=	0x008c
G$TF0$0$0 == 0x008d
_TF0	=	0x008d
G$TR1$0$0 == 0x008e
_TR1	=	0x008e
G$TF1$0$0 == 0x008f
_TF1	=	0x008f
G$P1_0$0$0 == 0x0090
_P1_0	=	0x0090
G$P1_1$0$0 == 0x0091
_P1_1	=	0x0091
G$P1_2$0$0 == 0x0092
_P1_2	=	0x0092
G$P1_3$0$0 == 0x0093
_P1_3	=	0x0093
G$P1_4$0$0 == 0x0094
_P1_4	=	0x0094
G$P1_5$0$0 == 0x0095
_P1_5	=	0x0095
G$P1_6$0$0 == 0x0096
_P1_6	=	0x0096
G$P1_7$0$0 == 0x0097
_P1_7	=	0x0097
G$T2$0$0 == 0x0090
_T2	=	0x0090
G$T2EX$0$0 == 0x0091
_T2EX	=	0x0091
G$RI$0$0 == 0x0098
_RI	=	0x0098
G$TI$0$0 == 0x0099
_TI	=	0x0099
G$RB8$0$0 == 0x009a
_RB8	=	0x009a
G$TB8$0$0 == 0x009b
_TB8	=	0x009b
G$REN$0$0 == 0x009c
_REN	=	0x009c
G$SM2$0$0 == 0x009d
_SM2	=	0x009d
G$SM1$0$0 == 0x009e
_SM1	=	0x009e
G$SM0$0$0 == 0x009f
_SM0	=	0x009f
G$P2_0$0$0 == 0x00a0
_P2_0	=	0x00a0
G$P2_1$0$0 == 0x00a1
_P2_1	=	0x00a1
G$P2_2$0$0 == 0x00a2
_P2_2	=	0x00a2
G$P2_3$0$0 == 0x00a3
_P2_3	=	0x00a3
G$P2_4$0$0 == 0x00a4
_P2_4	=	0x00a4
G$P2_5$0$0 == 0x00a5
_P2_5	=	0x00a5
G$P2_6$0$0 == 0x00a6
_P2_6	=	0x00a6
G$P2_7$0$0 == 0x00a7
_P2_7	=	0x00a7
G$EX0$0$0 == 0x00a8
_EX0	=	0x00a8
G$ET0$0$0 == 0x00a9
_ET0	=	0x00a9
G$EX1$0$0 == 0x00aa
_EX1	=	0x00aa
G$ET1$0$0 == 0x00ab
_ET1	=	0x00ab
G$ES$0$0 == 0x00ac
_ES	=	0x00ac
G$ET2$0$0 == 0x00ad
_ET2	=	0x00ad
G$EA$0$0 == 0x00af
_EA	=	0x00af
G$P3_0$0$0 == 0x00b0
_P3_0	=	0x00b0
G$P3_1$0$0 == 0x00b1
_P3_1	=	0x00b1
G$P3_2$0$0 == 0x00b2
_P3_2	=	0x00b2
G$P3_3$0$0 == 0x00b3
_P3_3	=	0x00b3
G$P3_4$0$0 == 0x00b4
_P3_4	=	0x00b4
G$P3_5$0$0 == 0x00b5
_P3_5	=	0x00b5
G$P3_6$0$0 == 0x00b6
_P3_6	=	0x00b6
G$P3_7$0$0 == 0x00b7
_P3_7	=	0x00b7
G$RXD$0$0 == 0x00b0
_RXD	=	0x00b0
G$TXD$0$0 == 0x00b1
_TXD	=	0x00b1
G$INT0$0$0 == 0x00b2
_INT0	=	0x00b2
G$INT1$0$0 == 0x00b3
_INT1	=	0x00b3
G$T0$0$0 == 0x00b4
_T0	=	0x00b4
G$T1$0$0 == 0x00b5
_T1	=	0x00b5
G$WR$0$0 == 0x00b6
_WR	=	0x00b6
G$RD$0$0 == 0x00b7
_RD	=	0x00b7
G$PX0$0$0 == 0x00b8
_PX0	=	0x00b8
G$PT0$0$0 == 0x00b9
_PT0	=	0x00b9
G$PX1$0$0 == 0x00ba
_PX1	=	0x00ba
G$PT1$0$0 == 0x00bb
_PT1	=	0x00bb
G$PS$0$0 == 0x00bc
_PS	=	0x00bc
G$PT2$0$0 == 0x00bd
_PT2	=	0x00bd
G$T2CON_0$0$0 == 0x00c8
_T2CON_0	=	0x00c8
G$T2CON_1$0$0 == 0x00c9
_T2CON_1	=	0x00c9
G$T2CON_2$0$0 == 0x00ca
_T2CON_2	=	0x00ca
G$T2CON_3$0$0 == 0x00cb
_T2CON_3	=	0x00cb
G$T2CON_4$0$0 == 0x00cc
_T2CON_4	=	0x00cc
G$T2CON_5$0$0 == 0x00cd
_T2CON_5	=	0x00cd
G$T2CON_6$0$0 == 0x00ce
_T2CON_6	=	0x00ce
G$T2CON_7$0$0 == 0x00cf
_T2CON_7	=	0x00cf
G$CP_RL2$0$0 == 0x00c8
_CP_RL2	=	0x00c8
G$C_T2$0$0 == 0x00c9
_C_T2	=	0x00c9
G$TR2$0$0 == 0x00ca
_TR2	=	0x00ca
G$EXEN2$0$0 == 0x00cb
_EXEN2	=	0x00cb
G$TCLK$0$0 == 0x00cc
_TCLK	=	0x00cc
G$RCLK$0$0 == 0x00cd
_RCLK	=	0x00cd
G$EXF2$0$0 == 0x00ce
_EXF2	=	0x00ce
G$TF2$0$0 == 0x00cf
_TF2	=	0x00cf
G$P$0$0 == 0x00d0
_P	=	0x00d0
G$FL$0$0 == 0x00d1
_FL	=	0x00d1
G$OV$0$0 == 0x00d2
_OV	=	0x00d2
G$RS0$0$0 == 0x00d3
_RS0	=	0x00d3
G$RS1$0$0 == 0x00d4
_RS1	=	0x00d4
G$F0$0$0 == 0x00d5
_F0	=	0x00d5
G$AC$0$0 == 0x00d6
_AC	=	0x00d6
G$CY$0$0 == 0x00d7
_CY	=	0x00d7
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; overlayable bit register bank
;--------------------------------------------------------
	.area BIT_BANK	(REL,OVR,DATA)
bits:
	.ds 1
	b0 = bits[0]
	b1 = bits[1]
	b2 = bits[2]
	b3 = bits[3]
	b4 = bits[4]
	b5 = bits[5]
	b6 = bits[6]
	b7 = bits[7]
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
G$t0$0$0==.
_t0::
	.ds 2
G$timerCount$0$0==.
_timerCount::
	.ds 2
G$waveCounter$0$0==.
_waveCounter::
	.ds 2
Lfreq.getFrequency$buf$1$46==.
_getFrequency_buf_1_46:
	.ds 12
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
	reti
	.ds	7
	ljmp	_timer0
	.ds	5
	reti
	.ds	7
	ljmp	_timer1
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genXINIT
	.globl __mcs51_genXRAMCLEAR
	.globl __mcs51_genRAMCLEAR
	C$freq.c$12$1$50 ==.
;	freq.c:12: int t0 =   0;
	clr	a
	mov	_t0,a
	mov	(_t0 + 1),a
	C$freq.c$13$1$50 ==.
;	freq.c:13: int timerCount =    20;
	mov	_timerCount,#0x14
;	1-genFromRTrack replaced	mov	(_timerCount + 1),#0x00
	mov	(_timerCount + 1),a
	C$freq.c$14$1$50 ==.
;	freq.c:14: int waveCounter = 0;
	mov	_waveCounter,a
	mov	(_waveCounter + 1),a
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
__sdcc_program_startup:
	ljmp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'delay'
;------------------------------------------------------------
;mstime                    Allocated to registers r6 r7 
;i                         Allocated to registers r4 r5 
;j                         Allocated to registers r2 r3 
;------------------------------------------------------------
	G$delay$0$0 ==.
	C$lcd.h$10$0$0 ==.
;	lcd.h:10: void delay(int mstime) {
;	-----------------------------------------
;	 function delay
;	-----------------------------------------
_delay:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
	mov	r6,dpl
	mov	r7,dph
	C$lcd.h$12$1$36 ==.
;	lcd.h:12: for(i=0; i<mstime; i++)
	mov	r4,#0x00
	mov	r5,#0x00
00107$:
	mov	ar2,r6
	mov	ar3,r7
	clr	c
	mov	a,r4
	subb	a,r2
	mov	a,r5
	subb	a,r3
	jnc	00109$
	C$lcd.h$13$1$36 ==.
;	lcd.h:13: for(j=0; j<1275; j++);
	mov	r2,#0xfb
	mov	r3,#0x04
00105$:
	mov	a,r2
	add	a,#0xff
	mov	r0,a
	mov	a,r3
	addc	a,#0xff
	mov	r1,a
	mov	ar2,r0
	mov	ar3,r1
	mov	a,r0
	orl	a,r1
	jnz	00105$
	C$lcd.h$12$1$36 ==.
;	lcd.h:12: for(i=0; i<mstime; i++)
	inc	r4
	cjne	r4,#0x00,00107$
	inc	r5
	sjmp	00107$
00109$:
	C$lcd.h$14$1$36 ==.
	XG$delay$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'send'
;------------------------------------------------------------
;data                      Allocated to registers r7 
;------------------------------------------------------------
	G$send$0$0 ==.
	C$lcd.h$16$1$36 ==.
;	lcd.h:16: void send(char data) {
;	-----------------------------------------
;	 function send
;	-----------------------------------------
_send:
	mov	r7,dpl
	C$lcd.h$18$1$38 ==.
;	lcd.h:18: P0 = (P0 & 0x0F) | (data & 0xF0);
	mov	a,#0x0f
	anl	a,_P0
	mov	r6,a
	mov	a,#0xf0
	anl	a,r7
	orl	a,r6
	mov	_P0,a
	C$lcd.h$20$1$38 ==.
;	lcd.h:20: P2 = data;
	mov	_P2,r7
	C$lcd.h$22$1$38 ==.
;	lcd.h:22: P0_2 = 1;
	setb	_P0_2
	C$lcd.h$23$1$38 ==.
;	lcd.h:23: P0_2 = 0;
	clr	_P0_2
	C$lcd.h$25$1$38 ==.
;	lcd.h:25: delay(2);
	mov	dptr,#0x0002
	lcall	_delay
	C$lcd.h$26$1$38 ==.
	XG$send$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'configure8bits'
;------------------------------------------------------------
	G$configure8bits$0$0 ==.
	C$lcd.h$28$1$38 ==.
;	lcd.h:28: void configure8bits() {
;	-----------------------------------------
;	 function configure8bits
;	-----------------------------------------
_configure8bits:
	C$lcd.h$29$1$39 ==.
;	lcd.h:29: P0 = 0x00;
	mov	_P0,#0x00
	C$lcd.h$30$1$39 ==.
;	lcd.h:30: delay(20);
	mov	dptr,#0x0014
	lcall	_delay
	C$lcd.h$31$1$39 ==.
;	lcd.h:31: send(0x0E); // display on
	mov	dpl,#0x0e
	lcall	_send
	C$lcd.h$32$1$39 ==.
;	lcd.h:32: send(0x06); // write to >>
	mov	dpl,#0x06
	lcall	_send
	C$lcd.h$33$1$39 ==.
	XG$configure8bits$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'clearLCD'
;------------------------------------------------------------
	G$clearLCD$0$0 ==.
	C$lcd.h$35$1$39 ==.
;	lcd.h:35: void clearLCD() {
;	-----------------------------------------
;	 function clearLCD
;	-----------------------------------------
_clearLCD:
	C$lcd.h$36$1$40 ==.
;	lcd.h:36: P0_0 = 0x00;
	clr	_P0_0
	C$lcd.h$37$1$40 ==.
;	lcd.h:37: send(0x01);
	mov	dpl,#0x01
	lcall	_send
	C$lcd.h$38$1$40 ==.
;	lcd.h:38: P0_0 = 0x01;
	setb	_P0_0
	C$lcd.h$39$1$40 ==.
	XG$clearLCD$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'to2line'
;------------------------------------------------------------
	G$to2line$0$0 ==.
	C$lcd.h$41$1$40 ==.
;	lcd.h:41: void to2line() {
;	-----------------------------------------
;	 function to2line
;	-----------------------------------------
_to2line:
	C$lcd.h$42$1$41 ==.
;	lcd.h:42: P0 = 0x00;
	mov	_P0,#0x00
	C$lcd.h$43$1$41 ==.
;	lcd.h:43: send(0xC0);
	mov	dpl,#0xc0
	lcall	_send
	C$lcd.h$44$1$41 ==.
	XG$to2line$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'write'
;------------------------------------------------------------
;txt                       Allocated to registers r5 r6 r7 
;------------------------------------------------------------
	G$write$0$0 ==.
	C$lcd.h$46$1$41 ==.
;	lcd.h:46: void write(char *txt) {
;	-----------------------------------------
;	 function write
;	-----------------------------------------
_write:
	mov	r5,dpl
	mov	r6,dph
	mov	r7,b
	C$lcd.h$47$1$43 ==.
;	lcd.h:47: P0_0 = 0x01; // RS = 1;
	setb	_P0_0
	C$lcd.h$48$1$43 ==.
;	lcd.h:48: while(*txt != '\0') {
00101$:
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r4,a
	jz	00104$
	C$lcd.h$49$2$44 ==.
;	lcd.h:49: send(*txt);
	mov	dpl,r4
	push	ar7
	push	ar6
	push	ar5
	lcall	_send
	pop	ar5
	pop	ar6
	pop	ar7
	C$lcd.h$50$2$44 ==.
;	lcd.h:50: txt++;
	inc	r5
	cjne	r5,#0x00,00101$
	inc	r6
	sjmp	00101$
00104$:
	C$lcd.h$52$1$43 ==.
	XG$write$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'configure_timers'
;------------------------------------------------------------
	G$configure_timers$0$0 ==.
	C$freq.c$16$1$43 ==.
;	freq.c:16: void configure_timers(){
;	-----------------------------------------
;	 function configure_timers
;	-----------------------------------------
_configure_timers:
	C$freq.c$20$1$45 ==.
;	freq.c:20: TMOD = 0x51;
	mov	_TMOD,#0x51
	C$freq.c$21$1$45 ==.
;	freq.c:21: TH0 = high50ms;
	mov	_TH0,#0x4b
	C$freq.c$22$1$45 ==.
;	freq.c:22: TL0 = low50ms;
	mov	_TL0,#0xff
	C$freq.c$23$1$45 ==.
;	freq.c:23: EA = 1;
	setb	_EA
	C$freq.c$24$1$45 ==.
;	freq.c:24: ET1 = 1;
	setb	_ET1
	C$freq.c$25$1$45 ==.
;	freq.c:25: ET0 = 1;
	setb	_ET0
	C$freq.c$26$1$45 ==.
	XG$configure_timers$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'getFrequency'
;------------------------------------------------------------
;frequency                 Allocated to registers r4 r5 
;buf                       Allocated with name '_getFrequency_buf_1_46'
;------------------------------------------------------------
	G$getFrequency$0$0 ==.
	C$freq.c$28$1$45 ==.
;	freq.c:28: void getFrequency(){
;	-----------------------------------------
;	 function getFrequency
;	-----------------------------------------
_getFrequency:
	C$freq.c$33$1$46 ==.
;	freq.c:33: frequency =  65536*waveCounter + 256*TH1 + TL1;
	mov	r4,_waveCounter
	mov	a,(_waveCounter + 1)
	mov	r5,a
	rlc	a
	subb	a,acc
	mov	ar7,r5
	mov	ar6,r4
	mov	r5,#0x00
	mov	r4,#0x00
	mov	r3,_TH1
	mov	r2,#0x00
	mov	ar0,r2
	mov	a,r3
	mov	r1,a
	rlc	a
	subb	a,acc
	mov	r2,a
	mov	r3,a
	mov	a,r0
	add	a,r4
	mov	r4,a
	mov	a,r1
	addc	a,r5
	mov	r5,a
	mov	a,r2
	addc	a,r6
	mov	r6,a
	mov	a,r3
	addc	a,r7
	mov	r7,a
	mov	r2,_TL1
	mov	r3,#0x00
	mov	ar0,r2
	mov	a,r3
	mov	r1,a
	rlc	a
	subb	a,acc
	mov	r2,a
	mov	r3,a
	mov	a,r0
	add	a,r4
	mov	r4,a
	mov	a,r1
	addc	a,r5
	mov	r5,a
	mov	a,r2
	addc	a,r6
	mov	a,r3
	addc	a,r7
	C$freq.c$35$1$46 ==.
;	freq.c:35: sprintf(buf,"%d", frequency);
	push	ar4
	push	ar5
	mov	a,#___str_0
	push	acc
	mov	a,#(___str_0 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	mov	a,#_getFrequency_buf_1_46
	push	acc
	mov	a,#(_getFrequency_buf_1_46 >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	lcall	_sprintf
	mov	a,sp
	add	a,#0xf8
	mov	sp,a
	C$freq.c$36$1$46 ==.
;	freq.c:36: strcat(buf, " Hz");
	mov	_strcat_PARM_2,#___str_1
	mov	(_strcat_PARM_2 + 1),#(___str_1 >> 8)
	mov	(_strcat_PARM_2 + 2),#0x80
	mov	dptr,#_getFrequency_buf_1_46
	mov	b,#0x40
	lcall	_strcat
	C$freq.c$38$1$46 ==.
;	freq.c:38: delay(20);
	mov	dptr,#0x0014
	lcall	_delay
	C$freq.c$39$1$46 ==.
;	freq.c:39: clearLCD();
	lcall	_clearLCD
	C$freq.c$40$1$46 ==.
;	freq.c:40: delay(200);
	mov	dptr,#0x00c8
	lcall	_delay
	C$freq.c$41$1$46 ==.
;	freq.c:41: write(buf);
	mov	dptr,#_getFrequency_buf_1_46
	mov	b,#0x40
	lcall	_write
	C$freq.c$42$1$46 ==.
	XG$getFrequency$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'timer0'
;------------------------------------------------------------
	G$timer0$0$0 ==.
	C$freq.c$44$1$46 ==.
;	freq.c:44: void timer0() __interrupt(1){
;	-----------------------------------------
;	 function timer0
;	-----------------------------------------
_timer0:
	push	bits
	push	acc
	push	b
	push	dpl
	push	dph
	push	(0+7)
	push	(0+6)
	push	(0+5)
	push	(0+4)
	push	(0+3)
	push	(0+2)
	push	(0+1)
	push	(0+0)
	push	psw
	mov	psw,#0x00
	C$freq.c$46$1$47 ==.
;	freq.c:46: timerCount--;
	dec	_timerCount
	mov	a,#0xff
	cjne	a,_timerCount,00108$
	dec	(_timerCount + 1)
00108$:
	C$freq.c$48$1$47 ==.
;	freq.c:48: TH0 = high50ms;
	mov	_TH0,#0x4b
	C$freq.c$49$1$47 ==.
;	freq.c:49: TL0 = low50ms;
	mov	_TL0,#0xff
	C$freq.c$51$1$47 ==.
;	freq.c:51: if(timerCount == 0){
	mov	a,_timerCount
	orl	a,(_timerCount + 1)
	jnz	00103$
	C$freq.c$52$2$48 ==.
;	freq.c:52: TR0 = 0;
	clr	_TR0
	C$freq.c$53$2$48 ==.
;	freq.c:53: TR1 = 0;
	clr	_TR1
	C$freq.c$55$2$48 ==.
;	freq.c:55: getFrequency();
	lcall	_getFrequency
	C$freq.c$56$2$48 ==.
;	freq.c:56: configure_timers();
	lcall	_configure_timers
	C$freq.c$58$2$48 ==.
;	freq.c:58: timerCount = 20;
	mov	_timerCount,#0x14
	mov	(_timerCount + 1),#0x00
	C$freq.c$59$2$48 ==.
;	freq.c:59: TR0 = 1;
	setb	_TR0
	C$freq.c$60$2$48 ==.
;	freq.c:60: TR1 = 1;
	setb	_TR1
00103$:
	pop	psw
	pop	(0+0)
	pop	(0+1)
	pop	(0+2)
	pop	(0+3)
	pop	(0+4)
	pop	(0+5)
	pop	(0+6)
	pop	(0+7)
	pop	dph
	pop	dpl
	pop	b
	pop	acc
	pop	bits
	C$freq.c$63$1$47 ==.
	XG$timer0$0$0 ==.
	reti
;------------------------------------------------------------
;Allocation info for local variables in function 'timer1'
;------------------------------------------------------------
	G$timer1$0$0 ==.
	C$freq.c$65$1$47 ==.
;	freq.c:65: void timer1() __interrupt(3){
;	-----------------------------------------
;	 function timer1
;	-----------------------------------------
_timer1:
	push	acc
	push	psw
	C$freq.c$67$1$49 ==.
;	freq.c:67: waveCounter++;
	inc	_waveCounter
	clr	a
	cjne	a,_waveCounter,00103$
	inc	(_waveCounter + 1)
00103$:
	pop	psw
	pop	acc
	C$freq.c$68$1$49 ==.
	XG$timer1$0$0 ==.
	reti
;	eliminated unneeded mov psw,# (no regs used in bank)
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
	G$main$0$0 ==.
	C$freq.c$70$1$49 ==.
;	freq.c:70: int main () {
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	C$freq.c$71$1$50 ==.
;	freq.c:71: configure8bits();
	lcall	_configure8bits
	C$freq.c$72$1$50 ==.
;	freq.c:72: clearLCD();
	lcall	_clearLCD
	C$freq.c$73$1$50 ==.
;	freq.c:73: configure_timers();
	lcall	_configure_timers
	C$freq.c$75$1$50 ==.
;	freq.c:75: TR0 = 1;
	setb	_TR0
	C$freq.c$76$1$50 ==.
;	freq.c:76: TR1 = 1;
	setb	_TR1
	C$freq.c$78$1$50 ==.
;	freq.c:78: while(1);	// end
00102$:
	sjmp	00102$
	C$freq.c$79$1$50 ==.
	XG$main$0$0 ==.
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
Ffreq$__str_0$0$0 == .
___str_0:
	.ascii "%d"
	.db 0x00
Ffreq$__str_1$0$0 == .
___str_1:
	.ascii " Hz"
	.db 0x00
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
