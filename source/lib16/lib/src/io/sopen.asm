; SOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include dos.inc
include share.inc
include stdio.inc
include fcntl.inc
include stat.inc
include errno.inc

externdef _fmode:size_t
externdef _umaskval:size_t

	.code

sopen	PROC _CDecl PUBLIC USES si di path:DWORD, oflag:size_t, shflag:size_t, args:VARARG
	mov	si,FH_TEXT
	cmp	_fmode,O_BINARY
	je	sopen_start
	mov	ax,oflag
	test	ax,O_BINARY
	jz	sopen_start
	sub	si,si
    sopen_start:
	and	ax,O_RDONLY or O_WRONLY or O_RDWR
	cmp	ax,O_RDONLY
	je	sopen_valid
	cmp	ax,O_WRONLY
	je	sopen_valid
	cmp	ax,O_RDWR
	je	sopen_valid
    sopen_einval:
	mov	errno,EINVAL
	sub	ax,ax
	mov	doserrno,ax
	dec	ax
	jmp	sopen_end
    sopen_valid:
	mov	di,ax
	mov	ax,oflag
	and	ax,O_CREAT or O_EXCL or O_TRUNC
	jz	sopen_a_open
	cmp	ax,O_EXCL
	je	sopen_a_open
	cmp	ax,O_CREAT
	je	sopen_a_open_create
	cmp	ax,O_CREAT or O_TRUNC
	je	sopen_a_create_trunc
	cmp	ax,O_CREAT or O_EXCL
	je	sopen_a_create_trunc
	cmp	ax,O_CREAT or O_TRUNC or O_EXCL
	je	sopen_a_create_trunc
	cmp	ax,O_TRUNC
	je	sopen_a_trunc
	cmp	ax,O_TRUNC or O_EXCL
	je	sopen_a_trunc
	jmp	sopen_einval
    sopen_a_open:
	mov	ax,A_OPEN
	jmp	sopen_flag
    sopen_a_open_create:
	mov	ax,A_OPEN or A_CREATE
	jmp	sopen_flag
    sopen_a_create_trunc:
	mov	ax,A_CREATE or A_TRUNC
	jmp	sopen_flag
    sopen_a_trunc:
	mov	ax,A_TRUNC
    sopen_flag:
	mov	cx,_A_NORMAL
	mov	dx,oflag
	test	dx,O_CREAT
	jz	sopen_del
	lea	bx,args
	push	ax
	mov	ax,[bx]
	mov	bx,_umaskval
	not	bx
	and	ax,bx
	and	ax,S_IWRITE
	pop	ax
	jnz	sopen_del
	mov	cx,_A_RDONLY
    sopen_del:
	test	dx,O_TEMPORARY
	jz	sopen_tmp
	or	cx,_A_DELETE
	or	di,O_SHORT_LIVED
    sopen_tmp:
	test	dx,O_SHORT_LIVED
	jz	sopen_seq
	or	cx,_A_TEMPORARY
    sopen_seq:
	test	dx,O_SEQUENTIAL
	jz	sopen_ran
	or	cx,_A_SEQSCAN
	jmp	sopen_os
    sopen_ran:
	test	dx,O_RANDOM
	jz	sopen_os
	or	cx,_A_RANDOM
    sopen_os:
	invoke	osopen,path,cx,di,ax
	cmp	ax,-1
	je	sopen_end
	mov	di,ax
	invoke	osfiletype,ax
	cmp	ax,DEV_UNKNOWN
	je	sopen_doserr
	cmp	ax,DEV_CHAR
	jne	sopen_osf
	or	si,FH_DEVICE
    sopen_osf:
	or	si,FH_OPEN
	mov	ax,si
	mov	_osfile[di],al
	test	al,FH_DEVICE or FH_PIPE
	jnz	sopen_append
	test	al,FH_TEXT
	jz	sopen_append
	test	oflag,O_RDWR
	jz	sopen_append
	invoke	lseek,di,-1,SEEK_END
	cmp	dx,-1
	jne	sopen_read
	cmp	ax,-1
	jne	sopen_read
	cmp	errno,EINVAL
	jne	sopen_error
	jmp	sopen_append
    sopen_read:
	push	dx
	push	ax
	sub	ax,ax
	mov	WORD PTR path,ax
	invoke	osread,di,addr path,1
	test	ax,ax
	pop	ax
	pop	dx
	jnz	sopen_chsize
	cmp	BYTE PTR path,26
	jne	sopen_seek
    sopen_chsize:
	invoke	chsize,di,dx::ax
	cmp	ax,-1
	je	sopen_error
    sopen_seek:
	invoke	lseek,di,0,SEEK_SET
	cmp	dx,-1
	jne	sopen_append
	cmp	ax,-1
	je	sopen_error
    sopen_append:
	mov	ax,si
	and	ax,FH_DEVICE or FH_PIPE
	jnz	sopen_done
	test	oflag,O_APPEND
	jz	sopen_done
	or	_osfile[di],FH_APPEND
    sopen_done:
	mov	ax,di
    sopen_end:
	ret
    sopen_doserr:
	mov	ax,doserrno
	call	osmaperr
    sopen_error:
	invoke	close,di
	mov	ax,-1
	jmp	sopen_end
sopen	ENDP

	END
