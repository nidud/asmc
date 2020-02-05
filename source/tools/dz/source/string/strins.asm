; STRINS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc
include string.inc

    .code

strins proc uses ebx s1:LPSTR, s2:LPSTR

    mov ebx,strlen(s2)
    inc strlen(s1)
    mov ecx,ebx
    add ecx,s1

    memmove(ecx, s1, eax)
    memcpy(s1, s2, ebx)
    ret

strins endp

    end
