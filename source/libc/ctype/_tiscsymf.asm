; _TISCSYMF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
include tchar.inc

    .code

_istcsymf proc c:int_t

    ldr ecx,c
    xor eax,eax
    .if ( ecx == '_' )
        inc eax
    .elseif ( ecx < 256 )
        add     ecx,ecx
        add     rcx,_pctype
        test    byte ptr [rcx],_UPPER or _LOWER
        setnz   al
    .endif
    ret

_istcsymf endp

    end

