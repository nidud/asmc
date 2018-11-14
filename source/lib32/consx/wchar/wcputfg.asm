; WCPUTFG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

wcputxg proto

    .code

wcputfg proc uses ecx ebx wp:PVOID, l, attrib
    mov eax,attrib
    mov ah,70h
    and al,0Fh
    mov ecx,l
    mov ebx,wp
    wcputxg()
    ret
wcputfg endp

    END
