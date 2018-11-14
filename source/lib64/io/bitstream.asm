; BITSTREAM.ASM--
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
        dq bitstream_Release
        dq bitstream_Read
        dq bitstream_Flush
        dq bitstream_Getbits
        dq bitstream_Putbits
.code

    assume rdi:ptr bitstream

bitstream::bitstream proc syscall uses rbx r12 lpFilename:ptr sbyte, Mode:uint32_t, BSize:uint64_t

    .repeat

        mov ebx,Mode
        mov r12,BSize

        .break .if !malloc( sizeof(bitstream) )

        .if rdi

            mov [rdi],rax
        .endif

        mov r8,rdi
        mov rdx,rax
        mov rdi,rax
        mov ecx,sizeof(bitstream)/8
        xor eax,eax
        rep stosq
        mov rdi,rdx

        lea rax,virtual_table
        mov [rdi].lpVtbl,rax
        or  [rdi].flags,ebx

        .if ( ebx & IO_STRBUF )

            mov [rdi].base,lpFilename
            mov [rdi].bsize,r12
            mov [rdi].count,r12
        .else

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
        .endif
        mov rax,rdi

    .until 1
    ret

bitstream::bitstream endp

bitstream::Release proc syscall uses rbx

    .if ( [rdi].flags & IO_WRONLY )

        .while [rdi].bk

            mov rax,[rdi].bb
            .if [rdi].bk >= 8
                sub [rdi].bk,8
            .else
                mov [rdi].bk,0
            .endif
            mov bl,al
            shr rax,8
            mov [rdi].bb,rax

            mov rcx,[rdi].index
            .if rcx == [rdi].bsize

                .break .ifd ![rdi].Flush()
                mov rcx,[rdi].index
            .endif

            add rcx,[rdi].base
            mov [rcx],bl
            inc [rdi].index

        .endw

        [rdi].Flush()
    .endif

    .if ( !( [rdi].flags & IO_STRBUF ) )

        _close( [rdi].file )
        free( [rdi].base )
    .endif
    free(_this)
    ret

bitstream::Release endp

bitstream::Flush proc syscall

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

bitstream::Flush endp

bitstream::Read proc syscall

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

bitstream::Read endp

bitstream::Getbits proc syscall bitcount:int8_t

    .repeat

        .if bitcount <= [rdi].bk

            mov cl,bitcount
            mov eax,1   ; create mask (a mask table is faster..)
            shl rax,cl
            dec rax
            and rax,[rdi].bb  ; bits to EAX
            sub [rdi].bk,cl   ; dec bit count
            shr [rdi].bb,cl   ; dump used bits
            .break

        .endif

        mov rax,[rdi].index
        .if rax == [rdi].count

            .if ![rdi].Read()

                or [rdi].flags,IO_EOF
                .break
            .endif
            mov rax,[rdi].index
        .endif

        inc     [rdi].index
        add     rax,[rdi].base
        movzx   eax,BYTE PTR [rax]
        mov     cl,[rdi].bk
        shl     rax,cl
        or      [rdi].bb,rax
        add     [rdi].bk,8

        .continue(0)

    .until 1
    ret

bitstream::Getbits endp

bitstream::Putbits proc syscall bits:size_t, bitcount:int8_t

    .repeat

        mov cl,[rdi].bk
        mov al,bitcount
        add al,cl

        .if al <= 64

            add [rdi].bk,bitcount
            shl bits,cl
            or  [rdi].bb,bits
            mov eax,1
            .break
        .endif

        shld rdx,bits,cl
        shl bits,cl
        or  bits,[rdi].bb
        mov [rdi].bb,rdx
        sub al,64
        mov [rdi].bk,al

        mov rcx,[rdi].index
        add rcx,8
        .if rcx >= [rdi].bsize

            .break .ifd ![rdi].Flush()
        .endif

        mov rcx,[rdi].index
        add rcx,[rdi].base
        mov [rcx],bits
        add [rdi].index,8
        mov eax,1

    .until 1
    ret

bitstream::Putbits endp

    end
