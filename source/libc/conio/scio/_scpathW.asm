; _SCPATHW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_scpathW proc uses rsi rdi rbx x:BYTE, y:BYTE, maxlen:BYTE, string:LPWSTR

  local b[16]:wchar_t

    movzx esi,maxlen
    .ifd ( wcslen( string ) > esi )

        lea rbx,b
        mov rdi,string
        mov ecx,[rdi]
        lea rdi,[rdi+rax*2]
        sub rdi,rsi
        sub rdi,rsi
        mov edx,8
        mov eax,('.' shl 16) or '\'

        rol ecx,16
        .if ( cx == ':' )

            rol ecx,16
            mov [rbx],ecx
            mov [rbx+4],eax
            rol eax,16
            mov [rbx+8],eax
            add edx,4
        .else
            mov [rbx],eax
            rol eax,16
            mov [rbx+4],eax
        .endif

        mov b[rdx],0
        add rdi,rdx
        mov string,rdi
        shr edx,1
        add x,dl
        _scputsW( x, y, rbx )
    .endif

    mov esi,eax
    _scputsW( x, y, string )
    add eax,esi
    ret

_scpathW endp

    end
