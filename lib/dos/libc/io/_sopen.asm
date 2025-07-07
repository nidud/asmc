; _SOPEN.ASM--
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

define EXIST_FAIL       0x00 ; DL - action
define EXIST_OPEN       0x01
define EXIST_TRUNC      0x02
define NOFILE_FAIL      0x00
define NOFILE_CREATE    0x10

define M_OPEN_EXISTING  (EXIST_OPEN or NOFILE_FAIL)
define M_OPEN_ALWAYS    (EXIST_OPEN or NOFILE_CREATE)
define M_CREATE_NEW     (EXIST_FAIL or NOFILE_CREATE)
define M_CREATE_ALWAYS  (EXIST_TRUNC or NOFILE_CREATE)
define M_TRUNCATE       (EXIST_TRUNC or NOFILE_FAIL)

define ACCESS_RDONLY    0x00 ; AL (BL) - open mode
define ACCESS_WRONLY    0x01
define ACCESS_RDWR      0x02

externdef _umaskval:uint_t

.code

_sopen proc uses si di bx fname:string_t, oflag:int_t, shflag:int_t, args:vararg

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

    xor cx,cx
    .if ( di & O_CREAT )

        mov ax,_umaskval
        not ax
        and ax,args
        .if !( ax & _S_IWRITE )
            mov cx,FILE_ATTRIBUTE_READONLY
        .endif
    .endif
    mov attrib,cx

    mov bx,shflag
    mov ax,di
    and ax,O_RDONLY or O_WRONLY or O_RDWR
    .switch pascal ax
    .case O_RDONLY: or bx,ACCESS_RDONLY ; read access
    .case O_WRONLY: or bx,ACCESS_WRONLY ; write access
    .case O_RDWR:   or bx,ACCESS_RDWR   ; read and write access
    .default
        mov errno,EINVAL
       .return( -1 )
    .endsw

    mov ax,di
    and ax,O_CREAT or O_EXCL or O_TRUNC
    .switch ax
    .case 0
    .case O_EXCL
        mov dx,M_OPEN_EXISTING
       .endc
    .case O_CREAT
        mov dx,M_OPEN_ALWAYS
       .endc
    .case O_CREAT or O_EXCL
    .case O_CREAT or O_EXCL or O_TRUNC
        mov dx,M_CREATE_NEW
       .endc
    .case O_CREAT or O_TRUNC
        mov dx,M_CREATE_ALWAYS
       .endc
    .case O_TRUNC
    .case O_TRUNC or O_EXCL
        mov dx,M_TRUNCATE
       .endc
    .default
        mov errno,EINVAL
       .return( -1 )
    .endsw
    mov action,dx

ifdef __LFN__
    stc
    cmp     _ifsmgr,0
    mov     ax,0x716C
endif
    pushl   ds
    ldr     si,fname
ifdef __LFN__
    jnz     .21
endif
    mov     ax,0x6C00   ; DOS 4.0+ - EXTENDED OPEN/CREATE
    cmp     _dosmajor,4
    jae     .21
    mov     ah,0x3D     ; DOS 2+ - OPEN EXISTING FILE
    mov     al,bl
    test    di,O_TRUNC or O_CREAT
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
    mov ax,0x4400
    int 0x21
    mov cl,fileflags
    .if ( !CARRY? && dl & 0x80 )
        or cl,FDEV
    .endif
    .if ( !( cl & FDEV or FPIPE ) && di & O_APPEND )
        or cl,FAPPEND
    .endif
    mov _osfile[bx],cl
    mov ax,bx
    ret

_sopen endp

    end
