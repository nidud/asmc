; _OPENFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include share.inc
include io.inc
include fcntl.inc
include errno.inc

define CMASK 0644O

    .code

_openfile proc uses bx file:string_t, mode:string_t, shflag:int_t, stream:LPFILE

   .new fileflag:int_t

    lesl bx,mode
    .while ( byte ptr esl[bx] == ' ' )
        inc bx
    .endw
    mov al,esl[bx]
    add bx,1

    .switch pascal al
    .case 'r': mov cx,_IOREAD : mov dx,O_RDONLY
    .case 'w': mov cx,_IOWRT  : mov dx,O_WRONLY or O_CREAT or O_TRUNC
    .case 'a': mov cx,_IOWRT  : mov dx,O_WRONLY or O_CREAT or O_APPEND
    .default
        mov errno,EINVAL
        .return(NULL)
    .endsw

    mov al,esl[bx]
    .while al
        .switch pascal al
        .case ' '
        .case '+'
            or  dx,O_RDWR
            and dx,not (O_RDONLY or O_WRONLY)
            or  cx,_IORW
            and cx,not (_IOREAD or _IOWRT)
        .case 't': or  dx,O_TEXT
        .case 'b': or  dx,O_BINARY
        .case 'c': or  cx,_IOCOMMIT
        .case 'n': and cx,not _IOCOMMIT
        .case 'S': or  dx,O_SEQUENTIAL
        .case 'R': or  dx,O_RANDOM
        .case 'T': or  dx,O_SHORT_LIVED
        .case 'D': or  dx,O_TEMPORARY
        .case 'z': or  dx,O_BINARY
        .default
            .break
        .endsw
        inc bx
        mov al,esl[bx]
    .endw
    mov fileflag,cx

    .if ( _sopen(file, dx, shflag, CMASK) != -1 )

        lesl bx,stream
        mov esl[bx]._iobuf._file,ax
        xor ax,ax
        mov esl[bx]._iobuf._cnt,ax
        mov word ptr esl[bx]._iobuf._ptr,ax
        mov word ptr esl[bx]._iobuf._base,ax
        mov esl[bx]._iobuf._flag,fileflag
        mov ax,bx
        movl dx,es
    .else
        xor ax,ax
        cwd
    .endif
    ret

_openfile endp

    end
