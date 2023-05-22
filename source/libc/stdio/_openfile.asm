; _OPENFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include fcntl.inc

define CMASK 644 ; rw-r--r--

    .code

    option switch:pascal

_openfile proc uses rsi rdi rbx filename:LPSTR, mode:LPSTR, shflag:SINT, stream:LPFILE

    ldr rsi,stream
    ldr rdx,mode

    mov al,[rdx]
    .switch al
    .case 'r' : mov edi,_IOREAD : mov ebx,O_RDONLY
    .case 'w' : mov edi,_IOWRT  : mov ebx,O_WRONLY or O_CREAT or O_TRUNC
    .case 'a' : mov edi,_IOWRT  : mov ebx,O_WRONLY or O_CREAT or O_APPEND
    .default
        .return 0
    .endsw

    inc rdx
    mov al,[rdx]
    xor ecx,ecx

    .while al
        .switch al
          .case '+'
            .break .if ebx & O_RDWR
            or  ebx,O_RDWR
            and ebx,not (O_RDONLY or O_WRONLY)
            or  edi,_IORW
            and edi,not (_IOREAD or _IOWRT)
          .case 't'
            .break .if ebx & (O_TEXT or O_BINARY)
            or  ebx,O_TEXT
          .case 'b'
            .break .if ebx & (O_TEXT or O_BINARY)
            or  ebx,O_BINARY
          .case 'c'
            .break .if ecx
            or  edi,_IOCOMMIT
            inc ecx
          .case 'n'
            .break .if ecx
            and edi,not _IOCOMMIT
            inc ecx
          .case 'S': or ebx,O_SEQUENTIAL
          .case 'R': or ebx,O_RANDOM
          .case 'T': or ebx,O_SHORT_LIVED
          .case 'D': or ebx,O_TEMPORARY
          .default
            .break
        .endsw
        inc rdx
        mov al,[rdx]
    .endw

    mov [rsi]._iobuf._flag,edi

    .ifd ( _sopen( filename, ebx, shflag, CMASK ) != -1 )

        mov [rsi]._iobuf._file,eax
        xor eax,eax
        mov [rsi]._iobuf._cnt,eax
        mov [rsi]._iobuf._ptr,rax
        mov [rsi]._iobuf._base,rax
        mov [rsi]._iobuf._tmpfname,rax
        mov rax,rsi
    .else
        xor eax,eax
        mov [rsi]._iobuf._flag,eax
    .endif
    ret

_openfile endp

    end
