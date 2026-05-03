
;--- format -pe, test address calculations: fixups without symbols
;--- this won't work with -coff, but it's allowed in -pe

	.386
	.model flat

?PRINT equ 1

	.data

var dd 12345678h

if ?PRINT
	.const
fstr1 db "lea reg,flat:[0]=%lX",10,0
fstr2 db "mov reg,offset flat:[0]=%lX",10,0
fstr3 db "lea reg,_TEXT:[0]=%lX",10,0
fstr4 db "mov reg,offset _TEXT:[0]=%lX",10,0
fstr5 db "lea reg,_DATA:[0]=%lX",10,0
fstr6 db "mov reg,offset _DATA:[0]=%lX",10,0
fstr7 db "lea reg,var=%lX",10,0
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

	public _start
_start:
	lea eax,flat:[0]
	@printf offset fstr1, eax
	mov eax,offset flat:[0]
	@printf offset fstr2, eax

	lea eax,_TEXT:[0]
	@printf offset fstr3, eax
	mov eax,offset _TEXT:[0]
	@printf offset fstr4, eax

	lea eax,_DATA:[0]
	@printf offset fstr5, eax
	mov eax,offset _DATA:[0]
	@printf offset fstr6, eax

	lea eax,var
	@printf offset fstr7, eax

	ret

	END _start
