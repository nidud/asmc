include alloc.inc

public	_chkstk
public	_alloca_probe

	.code

_chkstk:
_alloca_probe:

	mov [esp-4],ecx
	lea ecx,[esp+4]
@@:
	cmp eax,1000h	; probe pages
	jb  @F
	sub ecx,1000h
	test [ecx],eax
	sub eax,1000h
	jmp @B
@@:
	sub ecx,eax
	and ecx,-16	; align 16
	test [ecx],eax	; probe page
	mov eax,esp
	mov esp,ecx
	mov ecx,[eax-4]
	mov eax,[eax]
	jmp eax

	end
