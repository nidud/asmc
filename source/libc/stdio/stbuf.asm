; STBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include io.inc
include malloc.inc

    .data
    _stdbuf string_t 2 dup(0) ; buffer for stdout and stderr

    .code

    assume rbx:ptr _iobuf

_stbuf proc uses rbx fp:LPFILE

   .new p:string_t

    ldr rbx,fp

    .if _isatty([rbx]._file)

        xor eax,eax
        lea rdx,_stdbuf
        .if ( rbx != stdout )
            .if ( rbx != stderr )
                .return
            .endif
            add rdx,string_t
        .endif

        mov ecx,[rbx]._flag
        and ecx,_IOMYBUF or _IONBF or _IOYOURBUF
        .ifnz
            .return
        .endif
        or  ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
        mov [rbx]._flag,ecx

        mov rax,[rdx]
        .if ( rax == NULL )

            mov p,rdx
            malloc( _INTIOBUF )
            mov rcx,p
            mov [rcx],rax
        .endif

        mov ecx,_INTIOBUF
if defined(_WIN64) or not defined(__UNIX__)
        .if ( rax == NULL )

            lea rax,[rbx]._charbuf
            mov ecx,4
        .endif
endif
        mov [rbx]._ptr,rax
        mov [rbx]._base,rax
        mov [rbx]._bufsiz,ecx
        mov eax,1
    .endif
    ret

_stbuf endp

    end
