; FGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rbx:ptr _iobuf

fgets proc uses rbx buf:LPSTR, count:SINT, fp:LPFILE

   .new pointer:string_t

    ldr rbx,fp
    ldr rcx,buf
    .if ( count <= 0 )
        .return( NULL )
    .endif

    dec count
    .ifnz
        .repeat
            dec [rbx]._cnt
            .ifl
                mov pointer,rcx
                _filbuf(rbx)
                mov rcx,pointer
                .if ( eax  == -1 )

                    .break .if ( rcx != buf )
                    .return( NULL )
                .endif
            .else
                mov rdx,[rbx]._ptr
                inc [rbx]._ptr
                mov al,[rdx]
            .endif
            mov [rcx],al
            inc rcx
            .break .if ( al == 10 )
            dec count
        .untilz
    .endif
    mov byte ptr [rcx],0
   .return( buf )

fgets endp

    end
