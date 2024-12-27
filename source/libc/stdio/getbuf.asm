; GETBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

    assume rbx:LPFILE

_getbuf proc uses rbx fp:LPFILE

    ldr rbx,fp

ifdef STDZIP
    .if ( [rbx]._flag & _IOZIP )

        .if _aligned_malloc( _ZIPIOBUF*2, _ZIPIOBUF*2 )

            mov ecx,_ZIPIOBUF
            .if ( [rbx]._flag & _IOZIP64 )
                add ecx,ecx
            .endif
            or  [rbx]._flag,_IOMYBUF
            mov [rbx]._bufsiz,ecx
        .endif

    .elseif malloc( _INTIOBUF )
else
    .if malloc( _INTIOBUF )
endif
        or  [rbx]._flag,_IOMYBUF
        mov [rbx]._bufsiz,_INTIOBUF
    .else
        or  [rbx]._flag,_IONBF
        mov [rbx]._bufsiz,4
        lea rax,[rbx]._charbuf
    .endif
    mov [rbx]._ptr,rax
    mov [rbx]._base,rax
    mov [rbx]._cnt,0
    ret

_getbuf endp

    end
