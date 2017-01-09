include io.inc
include direct.inc
include wsub.inc

	.code

	ASSUME	esi: ptr S_WSUB

wssetflag PROC USES esi edi wsub:PTR S_WSUB
	mov	esi,wsub
	mov	edi,[esi].ws_flag
	and	edi,not _W_NETWORK
	mov	[esi].ws_flag,edi
	mov	eax,[esi].ws_path
	mov	eax,[eax]
	cmp	ah,'\'
	je	network
	cmp	ah,':'
	jne	error
	or	al,20h
	sub	al,'a' - 1
	movzx	eax,al
	_disk_type( eax )
	cmp	eax,DRIVE_CDROM
	je	cdroom
	cmp	eax,DRIVE_REMOVABLE
	je	removable
	cmp	eax,DRIVE_REMOTE
	je	remote
	cmp	eax,_DISK_SUBST
	je	subst
	and	eax,1
	jmp	toend
removable:
	or	edi,_W_REMOVABLE
	jmp	toend
remote:
	or	edi,_W_NETWORK or _W_CDROOM
	mov	eax,3
	jmp	toend
subst:
	mov	eax,2
cdroom:
	or	edi,_W_CDROOM
	jmp	toend
network:
	mov	eax,3
	or	edi,_W_NETWORK
toend:
	mov	[esi].ws_flag,edi
	ret
error:
	xor	eax,eax
	jmp	toend
wssetflag ENDP

	END
