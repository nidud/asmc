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

_wfopen proc uses rbx file:LPWSTR, mode:LPWSTR

   .new oflag:int_t
   .new fileflag:int_t

    ldr rbx,mode
    movzx eax,word ptr [rbx]
    add rbx,2

    .switch eax
    .case 'r': mov ecx,_IOREAD : mov edx,O_RDONLY
    .case 'w': mov ecx,_IOWRT  : mov edx,O_WRONLY or O_CREAT or O_TRUNC
    .case 'a': mov ecx,_IOWRT  : mov edx,O_WRONLY or O_CREAT or O_APPEND
    .default
        _set_errno(EINVAL)
        .return 0
    .endsw

    mov ax,[rbx]
    .while eax

        .switch eax
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
        add rbx,2
        mov ax,[rbx]
    .endw

    mov oflag,edx
    mov fileflag,ecx

    .if ( _getst() == NULL )
        .return
    .endif
    mov rbx,rax

    .if ( _wsopen( file, oflag, SH_DENYNO, 0284h ) != -1 )

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

_wfopen endp

    end
