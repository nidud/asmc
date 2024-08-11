; _PCUMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

public _pcumap
public _pclmap

.data
 _pcumap_table label byte
 i = 0
 while i lt 256
    if i lt 'a' or i gt 'z'
        db i
    else
        db i - 'a' + 'A'
    endif
    i = i + 1
 endm
 _pclmap_table label byte
 i = 0
 while i lt 256
    if i lt 'A' or i gt 'Z'
        db i
    else
        db i or 0x20
    endif
    i = i + 1
 endm
 _pclmap string_t _pclmap_table
 _pcumap string_t _pcumap_table

    end
