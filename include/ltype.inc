; LTYPE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
.pragma list(push, 0)

ifndef __LTYPE_INC
define __LTYPE_INC
ifndef _LIBC_
include libc.inc
endif

define _UPPER   0x01 ; upper case letter
define _LOWER   0x02 ; lower case letter
define _DIGIT   0x04 ; digit[0-9]
define _SPACE   0x08 ; tab, carriage return, newline, vertical tab or form feed
define _PUNCT   0x10 ; punctuation character
define _CONTROL 0x20 ; control character
define _LABEL   0x40 ; _UPPER + _LOWER + '@' + '_' + '$' + '?'
define _HEX     0x80 ; hexadecimal digit

; Label type array

DEFINE_LTYPE macro name
    name byte \
     9 dup(_CONTROL),           ; 00-08
     5 dup(_SPACE+_CONTROL),    ; 09-0D
    18 dup(_CONTROL),           ; 0E-1F
       _SPACE,                  ; 20 SPACE
     3 dup(_PUNCT),             ; 21-23 (!-#)
       _PUNCT+_LABEL,           ; 24 $
    11 dup(_PUNCT),             ; 25-2F (%-/)
    10 dup(_DIGIT+_HEX),        ; 30-39 (0-9)
     5 dup(_PUNCT),             ; 3A-3E :;<=>
     2 dup(_PUNCT+_LABEL),      ; 3F-40 ?@
     6 dup(_UPPER+_LABEL+_HEX), ; 41-46 (A-F)
    20 dup(_UPPER+_LABEL),      ; 47-5A (G-Z)
     4 dup(_PUNCT),             ; 5B-5E [\]^
       _PUNCT+_LABEL,           ; 5F _
       _PUNCT,                  ; 60 `
     6 dup(_LOWER+_LABEL+_HEX), ; 61-66 (a-f)
    20 dup(_LOWER+_LABEL),      ; 67-7A (g-z)
     4 dup(_PUNCT),             ; 7B-7E
       _CONTROL,                ; 7F
    128 dup(0)                  ; and the rest are 0...
    endm

if defined(LTYPE_INLINE) or defined(__PE__)
.data
DEFINE_LTYPE _ltype
_DATA ends
else
externdef _ltype: byte
endif

.pragma warning(disable: 8019) ; assume byte..

islascii    proto watcall :tchar_t { retm<(eax !< 128)> }
islprint    proto watcall :tchar_t { retm<(eax !>= 0x20 && eax !<= 0x7e)> }
islgraph    proto watcall :tchar_t { retm<(eax !>= 0x21 && eax !<= 0x7e)> }

ifdef _WIN64
;
; Use (global) r15 in 64-bit
;
_ltypeinit proto
_ltypeexit proto

ifndef _UNICODE

getltype proto watcall :byte {
    movzx ecx,byte ptr [r15+rax]
    }

islalnum    proto watcall :byte { retm<(byte ptr [r15+rax] & (_DIGIT or _UPPER or _LOWER))> }
islalpha    proto watcall :byte { retm<(byte ptr [r15+rax] & (_UPPER or _LOWER))> }
islcntrl    proto watcall :byte { retm<(byte ptr [r15+rax] & _CONTROL)> }
isldigit    proto watcall :byte { retm<(byte ptr [r15+rax] & _DIGIT)> }
isllower    proto watcall :byte { retm<(byte ptr [r15+rax] & _LOWER)> }
islpunct    proto watcall :byte { retm<(byte ptr [r15+rax] & _PUNCT)> }
islspace    proto watcall :byte { retm<(byte ptr [r15+rax] & _SPACE)> }
islupper    proto watcall :byte { retm<(byte ptr [r15+rax] & _UPPER)> }
islxdigit   proto watcall :byte { retm<(byte ptr [r15+rax] & _HEX)> }
;
; Valid first char and next (= first + digit)
;
islabel0    proto watcall :byte { retm<(byte ptr [r15+rax] & _LABEL)> }
islabel     proto watcall :byte { retm<(byte ptr [r15+rax] & (_LABEL or _DIGIT))> }
isdotlabel  proto watcall :byte, :byte { retm<((al == '.' && dl) || (byte ptr [r15+rax] & _LABEL))> }
;
; C label
;
isclabel0   proto watcall :byte { retm<(al == '_' || byte ptr [r15+rax] & (_UPPER or _LOWER))> }
isclabel    proto watcall :byte { retm<(al == '_' || byte ptr [r15+rax] & (_UPPER or _LOWER or _DIGIT))> }
else
islalnum    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & (_DIGIT or _UPPER or _LOWER))> }
islalpha    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & (_UPPER or _LOWER))> }
islcntrl    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & _CONTROL)> }
isldigit    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & _DIGIT)> }
isllower    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & _LOWER)> }
islpunct    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & _PUNCT)> }
islspace    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & _SPACE)> }
islupper    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & _UPPER)> }
islxdigit   proto watcall :word { retm<(!ah && byte ptr [r15+rax] & _HEX)> }
islabel0    proto watcall :word { retm<(!ah && byte ptr [r15+rax] & _LABEL)> }
islabel     proto watcall :word { retm<(!ah && byte ptr [r15+rax] & (_LABEL or _DIGIT))> }
isdotlabel  proto watcall :word, :word { retm<((eax == '.' && edx) || (!ah && byte ptr [r15+rax] & _LABEL))> }
isclabel0   proto watcall :word { retm<(eax == '_' || (!ah && byte ptr [r15+rax] & (_UPPER or _LOWER)))> }
isclabel    proto watcall :word { retm<(eax == '_' || (!ah && byte ptr [r15+rax] & (_UPPER or _LOWER or _DIGIT)))> }
endif

else

getltype proto watcall :byte {
    movzx ecx,_ltype[eax]
    }

islalnum    proto watcall :byte { retm<(_ltype[eax] & (_DIGIT or _UPPER or _LOWER))> }
islalpha    proto watcall :byte { retm<(_ltype[eax] & (_UPPER or _LOWER))> }
islcntrl    proto watcall :byte { retm<(_ltype[eax] & _CONTROL)> }
isldigit    proto watcall :byte { retm<(_ltype[eax] & _DIGIT)> }
isllower    proto watcall :byte { retm<(_ltype[eax] & _LOWER)> }
islpunct    proto watcall :byte { retm<(_ltype[eax] & _PUNCT)> }
islspace    proto watcall :byte { retm<(_ltype[eax] & _SPACE)> }
islupper    proto watcall :byte { retm<(_ltype[eax] & _UPPER)> }
islxdigit   proto watcall :byte { retm<(_ltype[eax] & _HEX)> }
islabel0    proto watcall :byte { retm<(_ltype[eax] & _LABEL)> }
islabel     proto watcall :byte { retm<(_ltype[eax] & (_LABEL or _DIGIT))> }
isdotlabel  proto watcall :byte, :byte { retm<((al == '.' && edx) || (_ltype[eax] & _LABEL))> }
isclabel0   proto watcall :byte { retm<(al == '_' || _ltype[eax] & (_UPPER or _LOWER))> }
isclabel    proto watcall :byte { retm<(al == '_' || _ltype[eax] & (_UPPER or _LOWER or _DIGIT))> }

endif

ltokstartc proto fastcall string:LPTSTR {
    .while ( islspace( [rcx] ) )
        add rcx,tchar_t
    .endw
    }

ltokstart proto fastcall string:LPTSTR {
    ltokstartc(rcx)
    xchg rax,rcx
    }

lprevtokc proto fastcall string_pos:LPTSTR, start_pos:LPTSTR {
    .while ( rcx > rdx && !islabel( [rcx] ) )
        sub rcx,tchar_t
    .endw
    .while ( rcx > rdx && islabel( [rcx] ) )
        sub rcx,tchar_t
    .endw
    .if ( !islabel( eax ) )
        .if ( islabel( [rcx+tchar_t] ) )
            add rcx,tchar_t
        .endif
        movzx eax,tchar_t ptr[rcx]
    .endif
    }

lnexttokc proto fastcall string_pos:LPTSTR {
    .while ( islabel( [rcx] ) )
        add rcx,tchar_t
    .endw
    .while ( eax && !islabel( [rcx] ) )
        add rcx,tchar_t
    .endw
    }

endif
.pragma list(pop)
