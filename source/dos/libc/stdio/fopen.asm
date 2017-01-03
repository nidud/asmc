; FOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include dos.inc
include fcntl.inc
include stat.inc
include errno.inc

extrn	_fmode:size_t
extrn	_umaskval:size_t

	.code

fopen PROC _CType PUBLIC USES si di bx filename:DWORD, mode:DWORD
local fp:DWORD
local flag:size_t
local fmode:size_t
local create:size_t
local isdev:size_t
local attrib:size_t
local filepos:DWORD
local oflag:size_t
local sflag:size_t
local wflag:size_t
	xor	ax,ax
	mov	oflag,ax
	mov	sflag,ax
	mov	wflag,ax
	mov	si,ax
	call	_getst
	test	ax,ax
	jz	fopen_02
	stom	fp
	les	bx,mode
	mov	al,es:[bx]
	xor	dx,dx
	mov	bx,dx
	cmp	al,'r'
	jne	fopen_00
	mov	dx,O_RDONLY	; oflag
	mov	bx,_IOREAD	; sflag
	jmp	fopen_03
    fopen_00:
	cmp	al,'w'
	jne	fopen_01
	mov	dx,O_WRONLY or O_CREAT or O_TRUNC
	mov	bx,_IOWRT
	jmp	fopen_03
    fopen_01:
	cmp	al,'a'
	jne	fopen_02
	mov	dx,O_WRONLY or O_CREAT or O_APPEND
	mov	bx,_IOWRT
	jmp	fopen_03
    fopen_02:
	jmp	fopen_NULL
    fopen_03:
	mov	oflag,dx
	mov	sflag,bx
	mov	wflag,1
	les	bx,mode
    fopen_04:
	inc	bx
	mov	al,es:[bx]
	test	al,al
	jz	fopen_11
	cmp	wflag,0
	je	fopen_11
	cmp	al,'+'
	je	fopen_05
	cmp	al,'b'
	je	fopen_07
	cmp	al,'t'
	je	fopen_09
	mov	wflag,0
	jmp	fopen_11
    fopen_05:
	test	oflag,O_RDWR
	jz	fopen_06
	mov	wflag,0
	jmp	fopen_11
    fopen_06:
	or	oflag,O_RDWR
	and	oflag,not (O_RDONLY or O_WRONLY)
	or	sflag,_IORW
	and	sflag,not (_IOREAD or _IOWRT)
	jmp	fopen_11
    fopen_07:
	test	oflag,O_TEXT or O_BINARY
	jz	fopen_08
	mov	wflag,0
	jmp	fopen_11
    fopen_08:
	or	oflag,O_BINARY
	jmp	fopen_11
    fopen_09:
	test	oflag,O_TEXT or O_BINARY
	jz	fopen_10
	mov	wflag,0
	jmp	fopen_11
    fopen_10:
	or	oflag,O_TEXT
    fopen_11:
	test	oflag,O_BINARY
	jz	fopen_12
	mov	flag,0
	jmp	fopen_15
    fopen_12:
	test	oflag,O_TEXT
	jz	fopen_13
	mov	flag,FH_TEXT
	jmp	fopen_15
    fopen_13:
	cmp	_fmode,O_BINARY
	jne	fopen_14
	mov	flag,0
	jmp	fopen_15
    fopen_14:
	mov	flag,FH_TEXT
    fopen_15:
	mov	ax,oflag
	and	ax,O_RDONLY or O_WRONLY or O_RDWR
	cmp	ax,O_RDONLY
	je	fopen_RDONLY
	cmp	ax,O_WRONLY
	je	fopen_WRONLY
	cmp	ax,O_RDWR
	je	fopen_RDWR
    fopen_16:
	mov	errno,EINVAL
	mov	doserrno,0
	jmp	fopen_NULL
    fopen_WRONLY:
	mov	ax,M_WRONLY
	jmp	fopen_17
    fopen_RDWR:
	mov	ax,M_RDWR
	jmp	fopen_17
    fopen_RDONLY:
	mov	ax,M_RDONLY
    fopen_17:
	mov	fmode,ax
	mov	ax,oflag
	and	ax,O_CREAT or O_EXCL or O_TRUNC
	jz	fopen_18
	cmp	ax,O_EXCL
	je	fopen_18
	cmp	ax,O_CREAT
	je	fopen_19
	cmp	ax,O_CREAT or O_EXCL
	je	fopen_20
	cmp	ax,O_CREAT or O_TRUNC or O_EXCL
	je	fopen_20
	cmp	ax,O_TRUNC
	je	fopen_21
	cmp	ax,O_TRUNC or O_EXCL
	je	fopen_21
	cmp	ax,O_CREAT or O_TRUNC
	je	fopen_22
	jmp	fopen_16
    fopen_18:
	mov	create,A_OPEN
	jmp	fopen_23
    fopen_19:
	mov	create,A_OPENCREATE
	jmp	fopen_23
    fopen_20:
	mov	create,A_CREATETRUNC
	jmp	fopen_23
    fopen_21:
	mov	create,A_TRUNC
	jmp	fopen_23
    fopen_22:
	mov	create,A_CREATETRUNC
    fopen_23:
	mov	attrib,_A_NORMAL
	test	oflag,O_CREAT
	jz	fopen_24
	mov	ax,_umaskval
	not	ax
	and	ax,0284h
	and	ax,S_IWRITE
	jnz	fopen_24
	mov	attrib,_A_RDONLY
    fopen_24:
	invoke	osopen,filename,attrib,fmode,create
	mov	si,ax
	cmp	ax,-1
	je	fopen_NULL
	invoke	osfiletype,ax
	mov	isdev,ax
	cmp	ax,DEV_UNKNOWN
	jne	fopen_25
	invoke	close,si
	mov	ax,doserrno
	mov	errno,ax
	jmp	fopen_NULL
    fopen_25:
	cmp	ax,DEV_CHAR
	jne	fopen_26
	or	flag,FH_DEVICE
    fopen_26:
	or	flag,FH_OPEN
	mov	ax,flag
	mov	_osfile[si],al
	test	al,FH_DEVICE or FH_PIPE
	jnz	fopen_30
	test	al,FH_TEXT
	jz	fopen_30
	test	oflag,O_RDWR
	jz	fopen_30
	invoke	lseek,si,-1,SEEK_END
	stom	filepos
	cmp	ax,-1
	jne	fopen_27
	cmp	errno,EINVAL
	je	fopen_30
	invoke	close,si
    fopen_NULL:
	xor	ax,ax
	jmp	fopen_32
    fopen_30:
	mov	ax,flag
	and	ax,FH_DEVICE or FH_PIPE
	jnz	fopen_33
	test	oflag,O_APPEND
	jz	fopen_33
    fopen_31:
	or	_osfile[si],FH_APPEND
    fopen_33:
	mov	bx,WORD PTR fp
	mov	ax,sflag
	mov	[bx].S_FILE.iob_flag,ax
	xor	ax,ax
	mov	[bx].S_FILE.iob_cnt,ax
	mov	WORD PTR [bx].S_FILE.iob_bp+2,ax
	mov	WORD PTR [bx].S_FILE.iob_base+2,ax
	mov	WORD PTR [bx].S_FILE.iob_bp,ax
	mov	WORD PTR [bx].S_FILE.iob_base,ax
	mov	[bx].S_FILE.iob_file,si
	mov	ax,bx
	mov	dx,ds
	jmp	fopen_32
    fopen_29:
	invoke	lseek,si,0,SEEK_SET
	cmp	ax,-1
	jne	fopen_30
	cmp	dx,-1
	jne	fopen_30
	jmp	fopen_28
    fopen_27:
	xor	ax,ax
	mov	WORD PTR mode,ax
	mov	WORD PTR mode+2,ax
	lea	dx,mode
	inc	ax
	invoke	osread,si,ss::dx,ax
	test	ax,ax
	jnz	fopen_29
	mov	al,BYTE PTR mode
	cmp	al,26
	jne	fopen_29
	invoke	chsize,si,filepos
	cmp	ax,-1
	jne	fopen_29
    fopen_28:
	invoke	close,si
	jmp	fopen_NULL
    fopen_32:
	ret
fopen	ENDP

	END
