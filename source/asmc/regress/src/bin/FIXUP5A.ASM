
;--- this didn't work up to jwasm v2.13
;--- if option -mz was used, jwasm made 5 seg fixups
;--- if option -omf was used, the 4. fixup was a seg fixup

	.model small
	.dosseg
	.stack 1024

DGROUP group _TEXT

XXX segment public 'BSS'	;segment NOT in DGROUP
dwVar dd ?
XXX ends

	.code

start16:
	mov ax,4c00h
	int 21h
	jmp cs:[dwVar]				;grp fixup   
	mov ax,offset dwVar			;seg fixup -> ofs 0
	mov ax,offset XXX:dwVar		;seg fixup -> ofs 0
	mov ax,offset cs:dwVar		;grp fixup (error if jwasm < v2.13: seg fixup)
	mov ax,offset DGROUP:dwVar	;grp fixup
;	jmp [dwVar]					;masm+jwasm: 'cannot access label thru seg register'

	end start16
