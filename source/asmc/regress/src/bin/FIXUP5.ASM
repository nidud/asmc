
;--- bug in jwasm < 2.13
;--- the segment override did ignore that CS was in a group

	.model small
	.dosseg
	.stack 1024

DGROUP group _TEXT

	.data?

dwVar dd ?

	.code

start16:
	mov ax,4c00h
	int 21h
	jmp cs:[dwVar]
	jmp [dwVar]
	mov ax,offset dwVar
	mov ax,offset _BSS:dwVar
	mov ax,offset cs:dwVar		;jwasm creates wrong fixup: should be same as DGROUP:dwVar
	mov ax,offset DGROUP:dwVar

	end start16
