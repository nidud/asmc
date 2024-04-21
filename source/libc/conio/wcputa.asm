; WCPUTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

wcputxg proc private

    add rcx,2
    .repeat
        and [rcx],ah
        or  [rcx],al
        add rcx,4
        dec edx
    .until !edx
    ret

wcputxg endp

wcputa proc p:PCHAR_INFO, l:int_t, attrib:int_t

    ldr eax,attrib
    and eax,0xFF
    ldr rcx,p
    ldr edx,l
    wcputxg()
    ret

wcputa endp

wcputbg proc p:PCHAR_INFO, l:int_t, attrib:int_t

    ldr eax,attrib
    mov ah,0x0F
    and al,0xF0
    ldr rcx,p
    ldr edx,l
    wcputxg()
    ret

wcputbg endp

wcputfg proc p:PCHAR_INFO, l:int_t, attrib:int_t

    ldr eax,attrib
    mov ah,0x70
    and al,0x0F
    ldr rcx,p
    ldr edx,l
    wcputxg()
    ret

wcputfg endp


    END
