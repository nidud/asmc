; _TOPENFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include share.inc
include io.inc
include fcntl.inc
include errno.inc
include tchar.inc

define CMASK 0644O

    .code

_topenfile proc uses bx file:LPTSTR, mode:LPTSTR, shflag:SINT, stream:LPFILE

   .new oflag:int_t
   .new fileflag:int_t

    lesl bx,mode
    .while ( TCHAR ptr esl[bx] == ' ' )
        add bx,TCHAR
    .endw
    mov al,esl[bx]
    add bx,1

    .switch pascal ax
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

        .case 't'
ifndef __UNIX__
            or  dx,O_TEXT
endif
        .case 'b': or  dx,O_BINARY
        .case 'c': or  cx,_IOCOMMIT
        .case 'n': and cx,not _IOCOMMIT
        .case 'S': or  dx,O_SEQUENTIAL
        .case 'R': or  dx,O_RANDOM
        .case 'T': or  dx,O_SHORT_LIVED
        .case 'D': or  dx,O_TEMPORARY
        .case 'z'
            or dx,O_BINARY
        .default
            .break
        .endsw
        add bx,TCHAR
        mov al,esl[bx]
    .endw
    mov fileflag,cx

    xor cx,cx
    .while al
        .switch al
        .case ','   ; ", ccs=UNICODE"   _O_WTEXT
        .case 'c'   ; ", ccs=UTF-16LE"  _O_U16TEXT
        .case 's'   ; ", ccs=UTF-8"     _O_U8TEXT
        .case '='
            inc cx
        .case ' '
            .endc
        .default
            .break
        .endsw
        add bx,TCHAR
        mov al,TCHAR ptr esl[bx]
    .endw

    mov oflag,dx
    lesl bx,stream
    .if ( _tsopen(file, oflag, shflag, CMASK) != -1 )

        mov esl[bx]._iobuf._file,ax
        xor ax,ax
        mov esl[bx]._iobuf._cnt,ax
        mov word ptr esl[bx]._iobuf._ptr,ax
        mov word ptr esl[bx]._iobuf._base,ax
        mov esl[bx]._iobuf._flag,fileflag
        mov ax,bx
    .else
        xor ax,ax
    .endif
    ret

_topenfile endp

    end
