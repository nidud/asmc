	.386
	.model flat, stdcall


PAGESIZE equ 1000h	; size of memory page

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

alloca  proc bsize
	lea	eax,[esp+4]
	mov	ecx,[eax]	; size to probe
@@:
	cmp	ecx,PAGESIZE	; probe pages
	jb	@F
	sub	eax,PAGESIZE
	test	[eax],eax
	sub	ecx,PAGESIZE
	jmp	@B
@@:
	sub	eax,ecx
	and	al,0F0h		; align 16
	test	[eax],eax	; probe page
	mov	ecx,esp
	mov	esp,eax
	push	[ecx+8+8]	; preserve ESI EDI EBX
	push	[ecx+8+4]
	push	[ecx+8+0]
	push	[ecx]		; return address
	ret
alloca  endp

	end
