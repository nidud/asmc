; _SCPATHA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_scpathA proc uses rbx x:BYTE, y:BYTE, maxlen:BYTE, string:LPSTR

  local b[16]:char_t

    ldr rbx,string
    strlen(rbx)
    movzx edx,maxlen
    .ifd ( eax > edx )

        mov ecx,[rbx]
        add rbx,rax
        sub rbx,rdx
        lea rdx,b
        mov eax,'\..\'

        .if ( ch == ':' )

            mov [rdx],cx
            mov [rdx+2],eax
            mov edx,6
        .else
            mov [rdx],eax
            mov edx,4
        .endif

        mov b[rdx],0
        add rbx,rdx
        mov cl,x
        add x,dl

        _scputsA( cl, y, &b )
    .endif
    _scputsA( x, y, rbx )
    ret

_scpathA endp

    end
