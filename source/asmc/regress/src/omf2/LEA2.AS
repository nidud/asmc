
;--- test address calculations: fixups without symbols
;--- modified in v2.15.
;--- -omf: see omffixup.c, omf_set_logref()
;--- -bin, -mz: special LEA handling in parser.c, seg_override()

	.386
	.model small
DGROUP group _TEXT
	.const
	.stack 4096
	.dosseg

?PRINT equ 0

	.data
var dw 1234
	.const
if ?PRINT
fstr1 db "lea reg,DGROUP:[0]=%X",10,0
fstr2 db "mov reg,offset DGROUP:[0]=%X",10,0
fstr3 db "lea reg,_TEXT:[0]=%X",10,0
fstr4 db "mov reg,offset _TEXT:[0]=%X",10,0
fstr5 db "lea reg,_DATA:[0]=%X",10,0
fstr6 db "mov reg,offset _DATA:[0]=%X",10,0
fstr7 db "lea reg,var=%X",10,0
endif

	.code

if ?PRINT
	include printf.inc
@printf macro args:vararg
	invoke printf, args
endm
else
@printf textequ <;>
endif

	public start32
start32:
	lea eax,DGROUP:[0]
	@printf offset fstr1, eax
	mov eax,offset DGROUP:[0]
	@printf offset fstr2, eax

	lea eax,_TEXT:[0]
	@printf offset fstr3, eax
	mov eax,offset _TEXT:[0]
	@printf offset fstr4, eax

	lea eax,_DATA:[0]
	@printf offset fstr5, eax
	mov eax,offset _DATA:[0]
	@printf offset fstr6, eax

	lea eax, var
	@printf offset fstr7, eax

	mov ax,4c00h
	int 21h

if ?PRINT
	include initpm.inc
?start textequ <start>
else
?start textequ <>
endif

	END ?start
