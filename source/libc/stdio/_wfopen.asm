; _WFOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; FILE *_wfopen(file, mode) - open a file
;
; mode:
;  r  : read
;  w  : write
;  a  : append
;  r+ : read/write
;  w+ : open empty for read/write
;  a+ : read/append
;
; Append "t" or "b" for text and binary mode
;
; Change history:
; 2017-02-16 - _UNICODE
;
include stdio.inc
include share.inc
include io.inc
include fcntl.inc
include errno.inc

externdef _fmode:dword
externdef _umaskval:dword

    .code

    option switch:pascal

_wfopen proc uses rsi rdi rbx file:LPWSTR, mode:LPWSTR

    mov rbx,mode
    movzx eax,word ptr [rbx]
    add rbx,2

    .switch eax
    .case 'r': mov esi,_IOREAD : mov edi,O_RDONLY
    .case 'w': mov esi,_IOWRT  : mov edi,O_WRONLY or O_CREAT or O_TRUNC
    .case 'a': mov esi,_IOWRT  : mov edi,O_WRONLY or O_CREAT or O_APPEND
    .default
        _set_errno(EINVAL)
        .return 0
    .endsw

    mov ax,[rbx]
    .while eax

        .switch eax
        .case '+'
            or  edi,O_RDWR
            and edi,not (O_RDONLY or O_WRONLY)
            or  esi,_IORW
            and esi,not (_IOREAD or _IOWRT)

        .case 't': or  edi,O_TEXT
        .case 'b': or  edi,O_BINARY
        .case 'c': or  esi,_IOCOMMIT
        .case 'n': and esi,not _IOCOMMIT
        .case 'S': or  edi,O_SEQUENTIAL
        .case 'R': or  edi,O_RANDOM
        .case 'T': or  edi,O_SHORT_LIVED
        .case 'D': or  edi,O_TEMPORARY
        .default
            .break
        .endsw

        add rbx,2
        mov ax,[rbx]
    .endw

    .if ( _getst() == NULL )
        .return
    .endif

    mov rbx,rax

    .if ( _wsopen( file, edi, SH_DENYNO, 0284h ) != -1 )

        mov [rbx]._iobuf._file,eax
        xor eax,eax
        mov [rbx]._iobuf._cnt,eax
        mov [rbx]._iobuf._ptr,rax
        mov [rbx]._iobuf._base,rax
        mov [rbx]._iobuf._flag,esi
        or  rax,rbx

    .else
        xor eax,eax
    .endif
    ret

_wfopen endp

    end
