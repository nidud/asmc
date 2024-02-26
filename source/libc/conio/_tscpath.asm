; _TSCPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include string.inc
include tchar.inc

    .code

_scpath proc uses rbx x:BYTE, y:BYTE, maxlen:BYTE, string:LPTSTR

  local b[16]:TCHAR

    ldr rbx,string
    _tcslen(rbx)
    movzx edx,maxlen
    .ifd ( eax > edx )

        mov ecx,[rbx]
        lea rbx,[rbx+rax*TCHAR]
        sub rbx,rdx
ifdef _UNICODE
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
else
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
endif

        mov b[rdx*TCHAR],0
        lea rbx,[rbx+rdx*TCHAR]
        mov cl,x
        add x,dl
        _scputs(cl, y, &b)
    .endif
    _scputs(x, y, rbx)
    ret

_scpath endp

    end
