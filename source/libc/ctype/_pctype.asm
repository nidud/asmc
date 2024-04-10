; _PCTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

public _pctype ; pointer to table for char's

.data
  db size_t-2 dup(0)
 _ctype word 0,                 ; -1
     9 dup(_CONTROL),           ; 00-08
     5 dup(_SPACE+_CONTROL),    ; 09-0D
    18 dup(_CONTROL),           ; 0E-1F
       _SPACE+_BLANK,           ; 20 SPACE
    15 dup(_PUNCT),             ; 21-2F (!-/)
    10 dup(_DIGIT+_HEX),        ; 30-39 (0-9)
     7 dup(_PUNCT),             ; 3A-40 (:-@)
     6 dup(_UPPER+_HEX),        ; 41-46 (A-F)
    20 dup(_UPPER),             ; 47-5A (G-Z)
     6 dup(_PUNCT),             ; 5B-60 ([-`)
     6 dup(_LOWER+_HEX),        ; 61-66 (a-f)
    20 dup(_LOWER),             ; 67-7A (g-z)
     4 dup(_PUNCT),             ; 7B-7E ({-~)
       _CONTROL,                ; 7F
    128 dup(0)                  ; and the rest are 0...
  _pctype ptr word _ctype[2]

.code

__pctype_func proc

    mov rax,_pctype
    ret

__pctype_func endp

    end
