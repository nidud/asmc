
;--- format -pe, test address calculations: fixups without symbols
;--- this won't work with -coff, but it's allowed in -pe

	.386
	.model flat

	.data

var dd 12345678h

	.code

	public _start
_start:
	lea eax,flat:[0]
	mov eax,offset flat:[0]
	lea eax,_TEXT:[0]
	mov eax,offset _TEXT:[0]
	lea eax,_DATA:[0]
	mov eax,offset _DATA:[0]
	lea eax,var
	ret

	END _start
