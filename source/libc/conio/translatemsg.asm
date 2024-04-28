; _TRANSLATEMESSAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rcx:PMESSAGE
    assume rax:PMESSAGE

_translatemsg proc msg:PMESSAGE

    ldr rcx,msg

    mov eax,[rcx].message
    .if ( eax  )

        mov rax,[rcx].hwnd
        .if ( rax == NULL )

            mov rdx,_console
            .while ( rdx && rax != [rdx].TDIALOG.next )
                mov rdx,[rdx].TDIALOG.next
            .endw
            mov [rcx].hwnd,rdx
        .endif
        mov rax,rcx
        _sendmessage([rax].hwnd, [rax].message, [rax].wParam, [rax].lParam)
    .endif
    ret

_translatemsg endp

    end
