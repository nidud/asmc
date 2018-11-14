; IOSTREAM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc
include iostream.inc
include malloc.inc
include fcntl.inc
include stat.inc

.data
    virtual_table label qword
        dq iostream_Release
        dq iostream_Read
        dq iostream_Write
        dq iostream_Flush
        dq iostream_Getc
        dq iostream_Putc
.code

    assume rdi:ptr iostream

iostream::iostream proc syscall uses rbx lpFilename:ptr sbyte, mode:uint32_t

    .repeat

        mov ebx,mode

        .break .if !malloc( sizeof(iostream) )

        .if rdi

            mov [rdi],rax
        .endif

        mov r8,rdi
        mov rdx,rax
        mov rdi,rax
        mov ecx,sizeof(iostream)/8
        xor eax,eax
        rep stosq
        mov rdi,rdx

        lea rax,virtual_table
        mov [rdi].lpVtbl,rax
        or  [rdi].flags,ebx

        .if ebx & IO_WRONLY

            _open(lpFilename, O_WRONLY or O_CREAT or O_TRUNC, S_IWRITE)
        .else
            _open(lpFilename, O_RDONLY)
        .endif
        .if eax == -1

            free(rdi)
            xor eax,eax
            .break
        .endif

        mov [rdi].file,eax
        mov [rdi].base,_aligned_malloc(_SEGSIZE_, _SEGSIZE_)
        mov [rdi].bsize,_SEGSIZE_
        mov rax,rdi

    .until 1
    ret

iostream::iostream endp

iostream::Release proc syscall

    .if [rdi].flags & IO_WRONLY

        [rdi].Flush()
    .endif
    _close([rdi].file)
    free([rdi].base)
    free(_this)
    ret

iostream::Release endp

iostream::Getc proc syscall

    mov r10,[rdi].index

    .repeat

        .if r10 == [rdi].count

            .while 1

                [rdi].Read()

                mov r10,[rdi].index
                .break .if rax

                mov eax,-1
                .break(1)

            .endw
        .endif

        inc   [rdi].index
        add   r10,[rdi].base
        movzx eax,byte ptr [r10]

    .until 1
    ret

iostream::Getc endp

iostream::Putc proc syscall char:int8_t

    mov rax,[rdi].index

    .repeat

        .if rax == [rdi].bsize

            [rdi].Flush()
            mov rax,[rdi].index
        .endif

        add rax,[rdi].base
        inc [rdi].index
        mov [rax],char
        mov eax,1
    .until 1
    ret

iostream::Putc endp

iostream::Flush proc syscall

    mov rax,[rdi].index

    .if rax

        .if oswrite( [rdi].file, [rdi].base, [rdi].index ) == [rdi].index

            xor eax,eax
            mov [rdi].count,rax
            mov [rdi].index,rax

        .else
            or [rdi].flags,IO_ERROR
            or eax,-1
        .endif
    .endif

    inc eax
    ret

iostream::Flush endp

iostream::Read proc syscall

    xor eax,eax

    .repeat

        .break .if [rdi].flags & IO_STRBUF

        mov rcx,[rdi].count
        sub rcx,[rdi].index
        .ifnz

            .break .if rcx == [rdi].count

            mov r10,rsi
            mov r11,rdi
            mov rsi,[rdi].base
            add rsi,[rdi].index
            mov rdi,[rdi].base
            mov r9,rcx
            rep movsb
            mov rcx,r9
            mov rsi,r10
            mov rdi,r11
        .endif

        mov [rdi].index,rax
        mov [rdi].count,rcx

        mov r8,[rdi].bsize
        sub r8,rcx
        mov rdx,[rdi].base
        add rdx,rcx

        osread([rdi].file, rdx, r8)
        add [rdi].count,rax
        mov rax,[rdi].count

    .until 1
    ret

iostream::Read endp

iostream::Write proc syscall uses rbx r12 buffer:ptr_t, len:size_t

    mov rbx,len
    mov r12,rsi

    .repeat

        mov rcx,rbx
        mov rdx,[rdi].index
        mov rax,[rdi].bsize
        sub rax,rdx
        add rdx,[rdi].base

        .if rax < rcx

            add  [rdi].index,rax
            sub  rbx,rax
            mov  rcx,rax
            xchg rdi,rdx
            rep  movsb
            mov  rdi,rdx

            [rdi].Flush()
            .continue(0) .if eax

            .break
        .endif

        add  [rdi].index,rcx
        xchg rdi,rdx
        rep  movsb
        mov  rdi,rdx

    .until 1

    mov rax,rsi
    sub rax,r12
    ret

iostream::Write endp

    end
