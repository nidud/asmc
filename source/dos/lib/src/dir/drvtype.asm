; DRVTYPE.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc

	.code

_disk_type PROC _CType PUBLIC USES dx bx disk:size_t
	mov	dx,disk
	cmp	dl,1
	ja	_disk_type_hdd
	mov	ah,15h		; GET DISK TYPE
	int	13h
	jc	_disk_type_NODISK
	test	ah,ah
	jz	_disk_type_NODISK
	mov	bx,disk		; remapped B drive ?
	cmp	bl,1
	jne	_disk_type_FLOPPY
	inc	bx
	mov	ax,440Eh
	int	21h		; IOCTL - GET LOGICAL DRIVE MAP
	test	al,al
	jz	_disk_type_FLOPPY
	jmp	_disk_type_NODISK
    _disk_type_hdd:
	mov	bx,dx
	inc	bx
	mov	ax,4409h	; IOCTL - CHECK IF BLOCK DEVICE REMOTE
	int	21h
	jc	_disk_type_NODISK
	test	dh,80h		; bit 15: drive is SUBSTituted
	jnz	_disk_type_SUBST
	test	dh,10h		; bit 12: drive is remote
	jnz	_disk_type_NETWORK
	jmp	_disk_type_LOCAL
    _disk_type_SUBST:
	mov	ax,_DISK_SUBST
	jmp	_disk_type_end
    _disk_type_NETWORK:
	mov	ax,_DISK_NETWORK
	jmp	_disk_type_end
    _disk_type_LOCAL:
	mov	ax,_DISK_LOCAL
	jmp	_disk_type_end
    _disk_type_FLOPPY:
	mov	ax,_DISK_FLOPPY
	jmp	_disk_type_end
    _disk_type_NODISK:
	sub	ax,ax
    _disk_type_end:
	test	ax,ax
	ret
_disk_type ENDP

	END
