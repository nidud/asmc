; FWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include errno.inc
include string.inc

    .code

    assume rbx:ptr FILE

fwrite proc uses rbx r12 r13 r14 r15 buf:LPSTR, rsize:SINT, _num:SINT, fp:ptr FILE

   .new size:uint_t = esi
   .new num:uint_t = edx
   .new count:uint_t

    .if ( esi == 0 || edx == 0 )
        .return 0
    .endif
    .if ( rcx == NULL )

        _set_errno(EINVAL)
        .return 0
    .endif

    mov r15,rdi ; buf
    mov rbx,rcx ; fp

    mov rax,rsi ; rsize
    mul rdx     ; num
    mov count,eax
    mov r12,rax

    mov r13d,_MAXIOBUF
    .if ( [rbx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF )
        mov r13d,[rbx]._bufsiz
    .endif

    .while ( count )

        mov ecx,[rbx]._cnt

        .if ( ecx && [rbx]._flag & _IOMYBUF or _IOYOURBUF )

            .if ( count < ecx )
                mov ecx,count
            .endif
            sub count,ecx
            sub [rbx]._cnt,ecx

            mov rdi,[rbx]._ptr
            mov rsi,r15
            rep movsb
            mov r15,rsi
            mov [rbx]._ptr,rdi

        .elseif ( count >= r13d )

            .if ( [rbx]._flag & _IOMYBUF or _IOYOURBUF )

                fflush(rbx)
                test rax,rax
                jnz break
            .endif

            mov eax,count
            .if ( r13d )

                xor edx,edx
                div r13d
                mov eax,count
                sub eax,edx
            .endif
            mov r14d,eax

            _write([rbx]._file, r15, eax)
            cmp eax,-1
            je  error

            sub count,eax
            add r15,rax
            cmp eax,r14d
            jb  error

        .else

            movzx eax,byte ptr [r15]
            _flsbuf(eax, rbx)
            cmp eax,-1
            je  break

            inc r15
            dec count

            mov eax,[rbx]._bufsiz
            .if ( !eax )
                mov eax,1
            .endif
            mov r13d,eax
        .endif
    .endw
    mov rax,num
toend:
    ret
error:
    or  [rbx]._flag,_IOERR
break:
    mov edx,count
    mov rax,r12
    sub rax,rdx
    xor rdx,rdx
    div size
    jmp toend
fwrite  endp

    END
