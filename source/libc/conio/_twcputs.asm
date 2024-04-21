; _TWCPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

    .code

wcputs proc uses rsi rdi rbx p:PCHAR_INFO, l:int_t, m:int_t, string:LPTSTR

    ldr     rsi,string
    ldr     rdi,p
    ldr     edx,l
    ldr     ecx,m

    movzx   edx,dl
    shl     edx,2

    movzx   ecx,cx
    mov     ah,ch
    mov     ch,[rdi+2]
    and     ch,0xF0

    .if ch == at_background[BG_MENU]
        or  ch,at_foreground[FG_MENUKEY]
    .elseif ch == at_background[BG_DIALOG]
        or  ch,at_foreground[FG_DIALOGKEY]
    .else
        xor ch,ch
    .endif

    mov  rbx,rdi

    and  eax,0x0000FF00
    shl  eax,8

    .if !cl
        dec cl
    .endif

    .while cl

        _tlodsb
        .switch _tal
        .case 0
            .break
        .case 10
            add rbx,rdx
            mov rdi,rbx
            .continue
        .case 9
            add rdi,16
           .continue
        .case '&'
            .if ch
                mov [rdi+2],ch
                _tlodsb
                mov [rdi],ax
                add rdi,4
                .break .if !_tal
               .continue
            .endif
        .default
            .if eax & 0x00FF0000
                stosd
            .else
                mov [rdi],ax
                add rdi,4
            .endif
            .endc
        .endsw
        dec cl
    .endw
    mov rax,rsi
    sub rax,string
ifdef _UNICODE
    shr eax,1
endif
    ret

wcputs endp

    END
