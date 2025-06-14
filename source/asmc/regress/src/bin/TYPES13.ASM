
;--- some more type compares
;--- support added in v2.10

ifdef __ASMC__
option masm:on
endif

.386
.model flat, stdcall
option casemap :none

S1 struct
x DWORD ?
S1 ends
PS1 typedef ptr S1
PPS1 typedef ptr PS1

	.data?
g_pS1	PS1 ?
g_ppS1	PPS1 ?
	.code
main proc
	LOCAL l_pS1:PS1
	LOCAL l_pS1i:ptr S1
	LOCAL l_ppS1:PPS1
	LOCAL l_ppS1i:ptr PS1

	dw (TYPE g_pS1) EQ (TYPE PS1)
	dw (TYPE l_pS1) EQ (TYPE PS1)
	dw (TYPE l_pS1i) EQ (TYPE PS1)
	dw (TYPE PS1 ptr esi) EQ (TYPE PS1)
	dw (TYPE g_ppS1) EQ (TYPE PPS1)
	dw (TYPE l_ppS1) EQ (TYPE PPS1)
	dw (TYPE l_ppS1i) EQ (TYPE PPS1)
	dw (TYPE PPS1 ptr esi) EQ (TYPE PPS1)
	dw (TYPE [PS1 ptr esi]) EQ (TYPE S1)

main endp
end

