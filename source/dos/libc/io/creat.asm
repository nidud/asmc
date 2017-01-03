; CREAT.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include dos.inc
include fcntl.inc
include stat.inc
include errno.inc

	.code

creat	PROC _CType PUBLIC path:DWORD, flag:size_t
	mov dx,_A_NORMAL
	mov ax,flag
	and ax,S_IREAD or S_IWRITE
	.if ax == S_IREAD
	    mov ax,O_RDONLY
	    mov dx,_A_RDONLY
	.elseif ax == S_IWRITE
	    mov ax,O_WRONLY
	.elseif ax == S_IREAD or S_IWRITE
	    mov ax,O_RDWR
	.else
	    mov errno,EINVAL
	    xor ax,ax
	    mov doserrno,ax
	    dec ax
	    jmp @F
	.endif
	invoke osopen,path,dx,ax,A_CREATE or A_TRUNC
      @@:
	ret
creat	ENDP

	END
