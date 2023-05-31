; _STBUF.ASM--
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

   .new p:string_t = &_stdbuf

    ldr rbx,fp

    .if _isatty([rbx]._file)

        xor eax,eax
        .if ( rbx != stdout )

            .if ( rbx != stderr )
                .return
            .endif
            add p,string_t
        .endif

        mov ecx,[rbx]._flag
        and ecx,_IOMYBUF or _IONBF or _IOYOURBUF
        .ifnz
            .return
        .endif
        or  ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
        mov [rbx]._flag,ecx

        mov rcx,p
        mov rax,[rcx]
        .if ( rax == NULL )

            malloc( _INTIOBUF )
            mov rcx,p
            mov [rcx],rax
        .endif

        mov ecx,_INTIOBUF
        .if ( rax == NULL )

            lea rax,[rbx]._charbuf
            mov ecx,4
        .endif
        mov [rbx]._ptr,rax
        mov [rbx]._base,rax
        mov [rbx]._bufsiz,ecx
        mov rax,1
    .endif
    ret

_stbuf endp

    end
