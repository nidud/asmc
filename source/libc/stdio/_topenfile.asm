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

externdef _fmode:dword
externdef _umaskval:dword

    .code

_topenfile proc uses rbx file:tstring_t, mode:tstring_t, shflag:int_t, stream:LPFILE

   .new oflag:int_t
   .new fileflag:int_t

    ldr rbx,mode
    .while ( tchar_t ptr [rbx] == ' ' )
        add rbx,tchar_t
    .endw
    movzx eax,tchar_t ptr [rbx]
    add rbx,tchar_t

    .switch pascal eax
    .case 'r': mov ecx,_IOREAD : mov edx,O_RDONLY
    .case 'w': mov ecx,_IOWRT  : mov edx,O_WRONLY or O_CREAT or O_TRUNC
    .case 'a': mov ecx,_IOWRT  : mov edx,O_WRONLY or O_CREAT or O_APPEND
    .default
        _set_errno(EINVAL)
        .return(NULL)
    .endsw

    movzx eax,tchar_t ptr [rbx]
    .while eax

        .switch pascal eax
        .case ' '
        .case '+'
            or  edx,O_RDWR
            and edx,not (O_RDONLY or O_WRONLY)
            or  ecx,_IORW
            and ecx,not (_IOREAD or _IOWRT)

        .case 't'
ifndef __UNIX__
            or  edx,O_TEXT
endif
        .case 'b': or  edx,O_BINARY
        .case 'c': or  ecx,_IOCOMMIT
        .case 'n': and ecx,not _IOCOMMIT
        .case 'S': or  edx,O_SEQUENTIAL
        .case 'R': or  edx,O_RANDOM
        .case 'T': or  edx,O_SHORT_LIVED
        .case 'D': or  edx,O_TEMPORARY
        .case 'z'
            or edx,O_BINARY
            or ecx,_IOZIP or _IOCRC32
        .default
            .break
        .endsw
        add rbx,tchar_t
        movzx eax,tchar_t ptr [rbx]
    .endw
    mov fileflag,ecx

    xor ecx,ecx
    .while eax
        .switch eax
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
        add rbx,tchar_t
        movzx eax,tchar_t ptr [rbx]
    .endw

    .if ( ecx == 5 && eax == 'U' )

        movzx eax,tchar_t ptr [rbx+tchar_t]
        movzx ecx,tchar_t ptr [rbx+tchar_t*4]
        .if ( eax == 'N' && ecx == 'O' )
            or edx,_O_WTEXT
        .elseif ( eax == 'T' && ecx == '1' )
            or edx,_O_U16TEXT
        .elseif ( eax == 'T' && ecx == '8' )
            or edx,_O_U8TEXT
        .else
            _set_errno(EINVAL)
            .return(NULL)
        .endif
    .endif
    mov oflag,edx

    mov rbx,stream
    .ifd ( _tsopen(file, oflag, shflag, CMASK) != -1 )

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

_topenfile endp

    end
