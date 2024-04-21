; _TWCPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

    .code

wcpath proc uses rbx b:PCHAR_INFO, maxlen:int_t, string:LPTSTR

    ldr rbx,string

    mov ecx,_tcslen(rbx)
    mov rdx,b

    .if ( ecx > maxlen )

        lea rbx,[rbx+rcx*TCHAR]
        mov ecx,maxlen
        sub rbx,rcx
ifdef _UNICODE
        sub rbx,rcx
endif
        mov eax,'\'
        mov [rdx],ax
        mov [rdx+12],ax
        mov al,'.'
        mov [rdx+4],ax
        mov [rdx+8],ax
        add rdx,16
        sub ecx,4
    .endif
    .ifs ( ecx > 0 )
        .repeat
            movzx eax,TCHAR ptr [rbx]
            mov [rdx],ax
            add rdx,4
            add rbx,TCHAR
        .untilcxz
    .endif
    ret

wcpath endp

    END
