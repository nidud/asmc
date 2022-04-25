; FTELL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include errno.inc

    .code

    assume rbx:ptr _iobuf

ftell proc uses rbx r12 r13 r14 r15 fp:ptr FILE

    mov rbx,fp
    mov edx,[rbx]._file
    lea rcx,_osfile
    mov r15b,[rcx+rdx]

    .if ( [rbx]._cnt < 0 )
        mov [rbx]._cnt,0
    .endif
    .ifs lseek([rbx]._file, 0, SEEK_CUR) < 0
        .return -1
    .endif
    mov ecx,[rbx]._flag
    .if !( ecx & _IOMYBUF or _IOYOURBUF )
        mov edx,[rbx]._cnt
        sub rax,rdx
       .return
    .endif

    mov r13,rax
    mov r12,[rbx]._ptr
    sub r12,[rbx]._base
    .if ( !( ecx & _IOWRT or _IOREAD or _IORW ) )
        _set_errno(EINVAL)
        .return -1
    .endif

    mov rax,r12
    .return .if !rax

    .if ( ecx & _IOREAD )

        mov eax,[rbx]._cnt
        .if ( eax == 0 )
            mov r12,rax
        .else
            add rax,[rbx]._ptr
            sub rax,[rbx]._base
            mov r14,rax

            .if ( r15b & FH_TEXT )

                .if ( lseek([rbx]._file, 0, SEEK_END) == r13 )

                    mov rax,r14
                    mov rcx,[rbx]._base
                    add rax,rcx

                    .while ( rcx < rax )
                        .if ( byte ptr [rcx] == 10 )
                            inc r14
                        .endif
                        inc rcx
                    .endw
                    .if ( [rbx]._flag & _IOCTRLZ )
                        inc r14
                    .endif

                .else

                    lseek([rbx]._file, r13, SEEK_SET)
                    mov eax,[rbx]._flag

                    .if ( r14 <= 512 && ( eax & _IOMYBUF ) && !( eax & _IOSETVBUF ) )
                        mov r14,512
                    .else
                        mov eax,[rbx]._bufsiz
                        mov r14,rax
                    .endif
                    .if ( r15b & FH_CRLF )
                        inc r14
                    .endif
                .endif
            .endif
            sub r13,r14
        .endif
    .endif
    lea rax,[r12+r13]
    ret

ftell endp

    end
