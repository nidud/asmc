; _TWCENTER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

    .code

wcenter proc uses rbx p:PCHAR_INFO, maxlen:int_t, string:tstring_t

    ldr rbx,string

    mov ecx,_tcslen(rbx)
    mov rdx,p

    .if ( ecx > maxlen )

        lea rbx,[rbx+rcx*tchar_t]
        mov ecx,maxlen
        sub rbx,rcx
ifdef _UNICODE
        sub rbx,rcx
endif
        mov eax,BSLASH
        mov [rdx],ax
        mov [rdx+12],ax
        mov al,'.'
        mov [rdx+4],ax
        mov [rdx+8],ax
        add rdx,16
        sub ecx,4
        xor eax,eax
    .endif
    .ifs ( ecx > 0 )

        .if ecx == eax

            mov eax,maxlen
            sub eax,ecx
            shr eax,1
            lea rdx,[rdx+rax*4]
        .endif
        .repeat
            movzx eax,tchar_t ptr [rbx]
            mov [rdx],ax
            add rdx,4
            add rbx,tchar_t
        .untilcxz
    .endif
    ret

wcenter endp

    end
