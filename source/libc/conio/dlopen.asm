; DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:PDOBJ

dlopen proc uses rbx dobj:PDOBJ, at:uint_t, ttl:LPSTR

    ldr rbx,dobj
    ldr edx,at

    and edx,0xFF
    mov [rbx].wp,rcopen([rbx].rc, [rbx].flag, 0, edx, ttl, [rbx].wp)

    .if rax

        or  [rbx].flag,W_ISOPEN
        mov eax,1
    .endif
    ret

dlopen endp

    end
