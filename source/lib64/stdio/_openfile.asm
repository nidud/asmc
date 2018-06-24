include stdio.inc
include io.inc
include fcntl.inc

CMASK   equ 644 ; rw-r--r--

    .code

    option  switch:pascal, win64:rsp nosave

_openfile proc uses rsi filename:LPSTR, mode:LPSTR, shflag:SINT, stream:LPFILE

    mov rsi,r9
    .repeat

        mov al,[rdx]
        .switch al
          .case 'r': mov r9d,_IOREAD : mov r10d,O_RDONLY
          .case 'w': mov r9d,_IOWRT  : mov r10d,O_WRONLY or O_CREAT or O_TRUNC
          .case 'a': mov r9d,_IOWRT  : mov r10d,O_WRONLY or O_CREAT or O_APPEND
          .default
            xor eax,eax
            .break
        .endsw

        inc rdx
        mov al,[rdx]
        xor r11d,r11d
        .while  al
            .switch al
              .case '+'
                .break .if r10d & O_RDWR
                or  r10d,O_RDWR
                and r10d,not (O_RDONLY or O_WRONLY)
                or  r9d,_IORW
                and r9d,not (_IOREAD or _IOWRT)
              .case 't'
                .break .if r10d & (O_TEXT or O_BINARY)
                or  r10d,O_TEXT
              .case 'b'
                .break .if r10d & (O_TEXT or O_BINARY)
                or  r10d,O_BINARY
              .case 'c'
                .break .if r11d
                or  r9d,_IOCOMMIT
                inc r11d
              .case 'n'
                .break .if r11d
                and r9d,not _IOCOMMIT
                inc r11d
              .case 'S': or r10d,O_SEQUENTIAL
              .case 'R': or r10d,O_RANDOM
              .case 'T': or r10d,O_SHORT_LIVED
              .case 'D': or r10d,O_TEMPORARY
              .default
                .break
            .endsw
            inc rdx
            mov al,[rdx]
        .endw

        mov [rsi]._iobuf._flag,r9d
        .ifd _sopen(rcx, r10d, r8d, CMASK) != -1
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
    .until 1
    ret

_openfile endp

    END
