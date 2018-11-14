; SETMBVAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc
include winnls.inc

public __invalid_mb_chars

.data
__invalid_mb_chars dd 0

.code
__set_invalid_mb_chars proc

local astring:word

    mov astring,"a" ; test string

    ;
    ; Determine whether API supports this flag by making a dummy call.
    ;

    .if MultiByteToWideChar(0, MB_ERR_INVALID_CHARS, addr astring, -1, NULL, 0)
        mov __invalid_mb_chars,MB_ERR_INVALID_CHARS
    .else
        mov __invalid_mb_chars,0
    .endif

    ret

__set_invalid_mb_chars endp

.pragma(init(__set_invalid_mb_chars, 40))

    end

