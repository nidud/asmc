; _TSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include dos.inc
include stdlib.inc
include fcntl.inc
include sys/stat.inc
include errno.inc
include winbase.inc

define F_OPEN      0x0001
define F_TRUNC     0x0002
define F_CREATE    0x0010

externdef _umaskval:uint_t

.code

_sopen proc uses si di bx fname:LPSTR, oflag:int_t, shflag:int_t, args:vararg

   .new mode:uint_t
   .new action:uint_t
   .new attrib:uint_t
   .new fh:int_t
   .new fileflags:char_t ; _osfile flags

    mov di,oflag
    mov _doserrno,0

    ; figure out binary/text mode

    mov al,FOPEN
    .if !( di & O_BINARY )
        .if ( di & O_TEXT )
            or al,FTEXT
        .elseif ( _fmode != O_BINARY ) ; check default mode
            or al,FTEXT
        .endif
    .endif
    mov fileflags,al

    mov dx,FILE_ATTRIBUTE_NORMAL
    .if ( di & O_CREAT )

        mov ax,_umaskval
        not ax
        and ax,args
        mov dx,FILE_ATTRIBUTE_NORMAL
        .if !( ax & _S_IWRITE )
            mov dx,FILE_ATTRIBUTE_READONLY
        .endif
    .endif
    mov attrib,dx

    mov ax,di
    and ax,O_RDONLY or O_WRONLY or O_RDWR
    .switch pascal ax
    .case O_RDONLY  ; read access
        mov ax,0x0000
    .case O_WRONLY  ; write access
        mov ax,0x0001
    .case O_RDWR    ; read and write access
        mov ax,0x0002
        .endc
    .default
        mov errno,EINVAL
       .return( -1 )
    .endsw
    mov mode,ax

    mov ax,di
    and ax,O_CREAT or O_EXCL or O_TRUNC
    .switch pascal ax
    .case 0
    .case O_EXCL
        mov cx,F_OPEN
    .case O_CREAT
        mov cx,F_CREATE
    .case O_CREAT or O_EXCL
        mov cx,F_OPEN or F_CREATE
    .case O_CREAT or O_EXCL or O_TRUNC
        mov cx,F_CREATE or F_OPEN or F_TRUNC
    .case O_CREAT or O_TRUNC
        mov cx,F_CREATE or F_TRUNC
    .case O_TRUNC
        mov cx,F_TRUNC
    .case O_TRUNC or O_EXCL
        mov cx,F_OPEN or F_TRUNC
    .default
        mov errno,EINVAL
       .return( -1 )
    .endsw
    mov action,cx

ifdef __LFN__
    stc
    cmp     _ifsmgr,0
    mov     ax,0x716C
endif
    pushl   ds
    ldsl    si,fname
    mov     bx,mode
    mov     cx,attrib
    mov     dx,action
ifdef __LFN__
    jnz     .21
endif
    mov     ax,0x6C00   ; DOS 4.0+ - EXTENDED OPEN/CREATE
    cmp     _dosmajor,4
    jae     .21
    mov     ah,0x3D     ; DOS 2+ - OPEN EXISTING FILE
    mov     al,bl
    test    dl,A_TRUNC or A_CREATE
    xchg    dx,si
    jz      .21
    dec     ah          ; DOS 2+ - CREATE OR TRUNCATE FILE
    test    si,A_TRUNC
    jnz     .21
    mov     ah,0x43     ; Create a new file - test if exist
    int     0x21
    .ifc
        popl ds
        .return( _dosmaperr( ERROR_FILE_EXISTS ) )
    .endif
    mov     ah,0x3C
    mov     cx,attrib
    cmp     al,2        ; file not found
    je      .21
    mov     si,dx       ; Windows for Workgroups bug
    mov     dx,action
    mov     ax,0x6C00
.21:
    int     0x21
    popl    ds
    .ifc
        .return( _dosmaperr( ax ) )
    .elseif ( ax >= _nfile )
        mov errno,EBADF
        .return( -1 )
    .endif
    mov bx,ax
    mov cl,fileflags
    mov _osfile[bx],cl
    ret

_sopen endp

    end
