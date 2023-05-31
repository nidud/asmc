; _OPENFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include fcntl.inc

define CMASK 0x1A4 ; rw-r--r--

    .code

    assume rbx:LPFILE
    option switch:pascal

_openfile proc uses rsi rdi rbx filename:LPSTR, mode:LPSTR, shflag:SINT, stream:LPFILE

    ldr rbx,stream
    ldr rdx,mode
    .while ( byte ptr [rdx] == ' ' )
        inc rdx
    .endw

    mov al,[rdx]
    .switch al
    .case 'r' : mov edi,_IOREAD : mov esi,O_RDONLY
    .case 'w' : mov edi,_IOWRT  : mov esi,O_WRONLY or O_CREAT or O_TRUNC
    .case 'a' : mov edi,_IOWRT  : mov esi,O_WRONLY or O_CREAT or O_APPEND
    .default
        .return 0
    .endsw

    inc rdx
    mov al,[rdx]
    xor ecx,ecx

    .while al
        .switch al
        .case '+'
            .break .if esi & O_RDWR
            or  esi,O_RDWR
            and esi,not (O_RDONLY or O_WRONLY)
            or  edi,_IORW
            and edi,not (_IOREAD or _IOWRT)
        .case 't'
            .break .if esi & (O_TEXT or O_BINARY)
            or  esi,O_TEXT
        .case 'b'
            .break .if esi & (O_TEXT or O_BINARY)
            or  esi,O_BINARY
        .case 'c'
            .break .if ecx
            or  edi,_IOCOMMIT
            inc ecx
        .case 'n'
            .break .if ecx
            and edi,not _IOCOMMIT
            inc ecx
        .case 'S': or esi,O_SEQUENTIAL
        .case 'R': or esi,O_RANDOM
        .case 'T': or esi,O_SHORT_LIVED
        .case 'D': or esi,O_TEMPORARY
        .default
            .break
        .endsw
        inc rdx
        mov al,[rdx]
    .endw

    mov [rbx]._flag,edi
    .ifd ( _sopen( filename, esi, shflag, CMASK ) != -1 )

        mov [rbx]._file,eax
        xor eax,eax
        mov [rbx]._cnt,eax
        mov [rbx]._ptr,rax
        mov [rbx]._base,rax
        mov [rbx]._tmpfname,rax
        mov rax,rbx
    .else
        xor eax,eax
        mov [rbx]._flag,eax
    .endif
    ret

_openfile endp

    end
