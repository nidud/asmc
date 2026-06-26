
;--- SIZE, LENGTH operators with externdefs
;--- also external prototypes and function pointers
ifdef __ASMC__
option masm:on
endif

	.286
	.model small, stdcall
	.dosseg
	.386
	option casemap:none

	.stack 100h

	includelib <extern7.lib>

VOID struct
VOID ends
S1 struct
F1 db 5 dup (?)
S1 ends
S2 struct
F2 db 5 dup (?)
S2 ends

TP1 typedef proto :word
TP2 typedef proto far :word
TP3 typedef proto far16 :word
TP4 typedef proto far32 :dword
PTP1 typedef ptr TP1
PTP2 typedef ptr TP2
PTP3 typedef ptr TP3
PTP4 typedef ptr TP4

externdef e1:byte
externdef e3:ptr byte
externdef e3:near ptr byte
externdef e4:far ptr byte
externdef e5:S1
externdef e6:VOID
externdef e10:TP1
externdef e11:TP2
externdef e12:TP3
externdef e13:TP4
externdef e14:PTP1
externdef e15:PTP2
externdef e16:PTP3
externdef e17:PTP4
externdef e20:proto :WORD
externdef e21:proto far :WORD
externdef e22:proto far16 :WORD
externdef e23:proto far32 :DWORD

externdef e1:byte
externdef e2:ptr byte
externdef e3:near ptr byte
externdef e4:far ptr byte
externdef e5:S1
externdef e6:VOID
externdef e10:TP1
externdef e11:TP2
externdef e12:TP3
externdef e13:TP4
externdef e14:PTP1
externdef e15:PTP2
externdef e16:PTP3
externdef e17:PTP4
externdef e20:proto :WORD
externdef e21:proto far :WORD
externdef e22:proto far16 :WORD
externdef e23:proto far32 :DWORD

	.code

	dw LENGTH e1,	 SIZE e1
	dw LENGTH e2,	 SIZE e2
	dw LENGTH e3,	 SIZE e3
	dw LENGTH e4,	 SIZE e4
	dw LENGTH e5,	 SIZE e5
	dw LENGTH e6,	 SIZE e6
	dw LENGTH e10,	 SIZE e10
	dw LENGTH e11,	 SIZE e11
	dw LENGTH e12,	 SIZE e12
	dw LENGTH e13,	 SIZE e13
	dw LENGTH e14,	 SIZE e14
	dw LENGTH e15,	 SIZE e15
	dw LENGTH e16,	 SIZE e16
	dw LENGTH e17,	 SIZE e17
	dw LENGTH e20,	 SIZE e20
	dw LENGTH e21,	 SIZE e21
	dw LENGTH e22,	 SIZE e22
	dw LENGTH e23,	 SIZE e23

	invoke e10, ax
	invoke e11, ax
	invoke e12, ax
	invoke e13, eax
	invoke e14, ax
	invoke e15, ax
	invoke e16, ax
	invoke e17, eax
	invoke e20, ax
	invoke e21, ax
	invoke e22, ax
	invoke e23, eax

start:
	mov ah,4ch
	int 21h

	end start
