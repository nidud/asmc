; DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:PDOBJ

dlopen proc uses rbx dobj:PDOBJ, at:uint_t, ttl:string_t

    ldr rbx,dobj
    ldr edx,at

    and edx,0xFF
    mov [rbx].window,rcopen([rbx].rc, [rbx].flags, 0, edx, ttl, [rbx].window)

    .if rax

        or  [rbx].flags,W_ISOPEN
        mov eax,1
    .endif
    ret

dlopen endp

    end
