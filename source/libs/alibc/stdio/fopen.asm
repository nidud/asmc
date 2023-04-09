; FOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include errno.inc
include fcntl.inc
include sys/stat.inc

    option switch:pascal

    .code

    assume rbx:ptr _iobuf

fopen proc uses rbx fname:string_t, mode:string_t

    .return .if ( _getst() == NULL )

    mov rbx,rax
    xor edx,edx
    lodsb
    .switch al
    .case 'r'
        mov r9d,_IOREAD
        mov r8d,O_RDONLY
    .case 'w'
        mov r9d,_IOWRT
        mov edx,S_IRUSR or S_IWUSR or S_IRGRP
        mov r8d,O_CREAT or O_TRUNC or O_WRONLY
    .case 'a'
        mov r9d,_IOWRT
        mov edx,S_IRUSR or S_IWUSR or S_IRGRP
        mov r8d,O_CREAT or O_APPEND or O_WRONLY
    .default
        _set_errno(EINVAL)
        .return NULL
    .endsw

    lodsb
    xor ecx,ecx
    .while al
        .switch al
        .case '+'
            .break .if r8d & O_RDWR
            or  r8d,O_RDWR
            and r8d,not ( O_RDONLY or O_WRONLY )
            or  r9d,_IORW
            and r9d,not ( _IOREAD or _IOWRT )
        .case 't'
            .break .if r8d & ( O_TEXT or O_BINARY )
            or  r8d,O_TEXT
        .case 'b'
            .break .if r8d & ( O_TEXT or O_BINARY )
            or  r8d,O_BINARY
        .case 'c'
            .break .if ecx
            or  r9d,_IOCOMMIT
            inc ecx
        .case 'n'
            .break .if ecx
            and r9d,not _IOCOMMIT
            inc ecx
        .case 'S': or r8d,O_SEQUENTIAL
        .case 'R': or r8d,O_RANDOM
        .case 'T': or r8d,O_SHORT_LIVED
        .case 'D': or r8d,O_TEMPORARY
        .default
            .break
        .endsw
        lodsb
    .endw
    mov esi,r8d
    mov [rbx]._iobuf._flag,r9d

    .ifd ( open(rdi, esi, edx) == -1 )

        xor eax,eax
        mov [rbx]._iobuf._flag,eax
       .return
    .endif
    mov [rbx]._iobuf._file,eax
    mov rax,rbx
    ret

fopen endp

    end
