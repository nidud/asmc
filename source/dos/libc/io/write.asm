; WRITE.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include errno.inc

	.code

write PROC _CType PUBLIC USES di si bx h:size_t, b:DWORD, l:size_t
local lb[1026]:BYTE
local count:size_t
local result:size_t
	mov ax,l
	mov bx,h
	.if ax
	    .if bx < _NFILE_
		.if [bx+_osfile] & FH_APPEND
		    invoke lseek,h,0,SEEK_END
		.endif
		sub ax,ax
		mov result,ax
		mov count,ax
		.if [bx+_osfile] & FH_TEXT
		    les si,b
		  write_04:
		    mov ax,si
		    sub ax,WORD PTR b
		    .if ax < l
			lea di,lb
		      @@:
			lea dx,lb
			mov ax,di
			sub ax,dx
			.if ax < 1024
			    mov ax,si
			    sub ax,WORD PTR b
			    .if ax < l
				mov al,es:[si]
				.if al == 10
				    mov BYTE PTR [di],13
				    inc di
				.endif
				mov [di],al
				inc si
				inc di
				inc count
				jmp @B
			    .endif
			.endif
			lea ax,lb
			mov dx,di
			sub dx,ax
			invoke oswrite,h,addr lb,dx
			.if ax
			    lea cx,lb
			    mov dx,di
			    sub dx,cx
			    cmp ax,dx
			    jb	write_11
			    jmp write_04
			.endif
			jmp write_09
		    .endif
		    jmp write_11
		.endif
		invoke oswrite,h,b,l
		test ax,ax
		jz write_09
		mov result,0
		mov count,ax
	    .else
		sub ax,ax
		mov doserrno,ax
		mov errno,EBADF
		dec ax
	    .endif
	.endif
    write_15:
	ret
    write_09:
	inc	result
    write_11:
	mov	ax,count
	test	ax,ax
	jnz	write_15
	cmp	ax,result
	jne	write_13
	cmp	doserrno,5	; access denied
	jne	write_12
	mov	errno,EBADF
    write_12:
	mov	ax,-1
	jmp	write_15
    write_13:
	test	[bx+_osfile],FH_DEVICE
	jz	write_14
	les	bx,b
	cmp	BYTE PTR es:[bx],26
	jne	write_14
	sub	ax,ax
	jmp	write_15
    write_14:
	mov	errno,ENOSPC
	mov	doserrno,0
	mov	ax,-1
	jmp	write_15
write	ENDP

	END
