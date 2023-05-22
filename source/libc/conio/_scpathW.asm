; _SCPATHW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_scpathW proc uses rbx x:BYTE, y:BYTE, maxlen:BYTE, string:LPWSTR

  local b[16]:wchar_t

    ldr rbx,string
    wcslen(rbx)
    movzx edx,maxlen
    .ifd ( eax > edx )

        mov ecx,[rbx]
        lea rbx,[rbx+rax*2]
        sub rbx,rdx
        sub rbx,rdx
        lea rdx,b

        mov eax,('.' shl 16) or '\'
        rol ecx,16
        .if ( cx == ':' )

            rol ecx,16
            mov [rdx],ecx
            mov [rdx+4],eax
            rol eax,16
            mov [rdx+8],eax
            mov edx,6
        .else
            mov [rdx],eax
            rol eax,16
            mov [rdx+4],eax
            mov edx,4
        .endif

        mov b[rdx*2],0
        lea rbx,[rbx+rdx*2]
        mov cl,x
        add x,dl
        _scputsW(cl, y, &b)
    .endif
    _scputsW(x, y, rbx)
    ret

_scpathW endp

    end
