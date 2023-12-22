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

_openfile proc uses rbx file:LPSTR, mode:LPSTR, shflag:SINT, stream:LPFILE

   .new oflag:int_t
   .new fileflag:int_t

    ldr rbx,mode
    .while ( byte ptr [rbx] == ' ' )
        inc rbx
    .endw
    mov al,[rbx]
    inc rbx

    .switch pascal al
    .case 'r': mov ecx,_IOREAD : mov edx,O_RDONLY
    .case 'w': mov ecx,_IOWRT  : mov edx,O_WRONLY or O_CREAT or O_TRUNC
    .case 'a': mov ecx,_IOWRT  : mov edx,O_WRONLY or O_CREAT or O_APPEND
    .default
        _set_errno(EINVAL)
        .return(NULL)
    .endsw

    mov al,[rbx]
    .while al

        .switch pascal al
        .case ' '
        .case '+'
            or  edx,O_RDWR
            and edx,not (O_RDONLY or O_WRONLY)
            or  ecx,_IORW
            and ecx,not (_IOREAD or _IOWRT)

        .case 't': or  edx,O_TEXT
        .case 'b': or  edx,O_BINARY
        .case 'c': or  ecx,_IOCOMMIT
        .case 'n': and ecx,not _IOCOMMIT
        .case 'S': or  edx,O_SEQUENTIAL
        .case 'R': or  edx,O_RANDOM
        .case 'T': or  edx,O_SHORT_LIVED
        .case 'D': or  edx,O_TEMPORARY
        .default
            .break
        .endsw
        inc rbx
        mov al,[rbx]
    .endw
    mov fileflag,ecx

    xor ecx,ecx
    .while al
        .switch al
        .case ','   ; ", ccs=UNICODE"   _O_WTEXT
        .case 'c'   ; ", ccs=UTF-16LE"  _O_U16TEXT
        .case 's'   ; ", ccs=UTF-8"     _O_U8TEXT
        .case '='
            inc ecx
        .case ' '
            .endc
        .default
            .break
        .endsw
        inc rbx
        mov al,[rbx]
    .endw
    .if ( ecx == 5 && al == 'U' )
        mov eax,[rbx+1]
        .if ( eax == 'OCIN' )
            or edx,_O_WTEXT
        .elseif ( eax == '1-FT' )
            or edx,_O_U16TEXT
        .elseif ( eax == '8-FT' )
            or edx,_O_U8TEXT
        .else
            _set_errno(EINVAL)
            .return(NULL)
        .endif
    .endif
    mov oflag,edx

    mov rbx,stream
    .if ( _sopen(file, oflag, shflag, CMASK) != -1 )

        mov [rbx]._iobuf._file,eax
        xor eax,eax
        mov [rbx]._iobuf._cnt,eax
        mov [rbx]._iobuf._ptr,rax
        mov [rbx]._iobuf._base,rax
        mov [rbx]._iobuf._flag,fileflag
        mov rax,rbx
    .else
        xor eax,eax
    .endif
    ret

_openfile endp

    end
