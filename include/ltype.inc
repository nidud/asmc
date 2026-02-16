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

if defined(LTYPE_INLINE) or defined(_MSVCRT)
.data
DEFINE_LTYPE _ltype
_DATA ends
else
externdef _ltype: byte
endif

.pragma warning(disable: 8019) ; assume byte..

islascii proto watcall :tchar_t { retm<(eax !< 128)> }
islprint proto watcall :tchar_t { retm<(eax !>= 0x20 && eax !<= 0x7e)> }
islgraph proto watcall :tchar_t { retm<(eax !>= 0x21 && eax !<= 0x7e)> }

ifdef _WIN64
define LTYPE <byte ptr [r15+rax]>
else
define LTYPE <_ltype[eax]>
endif

getltype proto watcall :byte {
    movzx ecx,LTYPE
    }

ifdef _WIN64 ; Use (global) r15 in 64-bit
_ltypeinit proto
_ltypeexit proto
endif

%_isltypeA      proto watcall :byte, :abs { retm<(LTYPE & _2)> }
%_islalnumA     proto watcall :byte { retm<(LTYPE & (_DIGIT or _UPPER or _LOWER))> }
%_islalphaA     proto watcall :byte { retm<(LTYPE & (_UPPER or _LOWER))> }
%_islcntrlA     proto watcall :byte { retm<(LTYPE & _CONTROL)> }
%_isldigitA     proto watcall :byte { retm<(LTYPE & _DIGIT)> }
%_isllowerA     proto watcall :byte { retm<(LTYPE & _LOWER)> }
%_islpunctA     proto watcall :byte { retm<(LTYPE & _PUNCT)> }
%_islspaceA     proto watcall :byte { retm<(LTYPE & _SPACE)> }
%_islupperA     proto watcall :byte { retm<(LTYPE & _UPPER)> }
%_islxdigitA    proto watcall :byte { retm<(LTYPE & _HEX)> }

; Valid first char and next (= first + digit)

%_islabel0A     proto watcall :byte { retm<(LTYPE & _LABEL)> }
%_islabelA      proto watcall :byte { retm<(LTYPE & (_LABEL or _DIGIT))> }
%_isdotlabelA   proto watcall :byte, :byte { retm<((al == '.' && dl) || (LTYPE & _LABEL))> }

; C label

%_isclabel0A    proto watcall :byte { retm<(al == '_' || LTYPE & (_UPPER or _LOWER))> }
%_isclabelA     proto watcall :byte { retm<(al == '_' || LTYPE & (_UPPER or _LOWER or _DIGIT))> }

%_isltypeW      proto watcall :byte, :abs { retm<(!ah && LTYPE & _2)> }
%_islalnumW     proto watcall :word { retm<(!ah && LTYPE & (_DIGIT or _UPPER or _LOWER))> }
%_islalphaW     proto watcall :word { retm<(!ah && LTYPE & (_UPPER or _LOWER))> }
%_islcntrlW     proto watcall :word { retm<(!ah && LTYPE & _CONTROL)> }
%_isldigitW     proto watcall :word { retm<(!ah && LTYPE & _DIGIT)> }
%_isllowerW     proto watcall :word { retm<(!ah && LTYPE & _LOWER)> }
%_islpunctW     proto watcall :word { retm<(!ah && LTYPE & _PUNCT)> }
%_islspaceW     proto watcall :word { retm<(!ah && LTYPE & _SPACE)> }
%_islupperW     proto watcall :word { retm<(!ah && LTYPE & _UPPER)> }
%_islxdigitW    proto watcall :word { retm<(!ah && LTYPE & _HEX)> }
%_islabel0W     proto watcall :word { retm<(!ah && LTYPE & _LABEL)> }
%_islabelW      proto watcall :word { retm<(!ah && LTYPE & (_LABEL or _DIGIT))> }
%_isdotlabelW   proto watcall :word, :word { retm<((eax == '.' && edx) || (!ah && LTYPE & _LABEL))> }
%_isclabel0W    proto watcall :word { retm<(eax == '_' || (!ah && LTYPE & (_UPPER or _LOWER)))> }
%_isclabelW     proto watcall :word { retm<(eax == '_' || (!ah && LTYPE & (_UPPER or _LOWER or _DIGIT)))> }

_ltolowerA proto watcall :byte {
    .if _islupperA(eax)
        add eax,'a'-'A'
    .endif
    }
_ltoupperA proto watcall :byte {
    .if _isllowerA(eax)
        sub eax,'a'-'A'
    .endif
    }
_ltolowerW proto watcall :word {
    .if _islupperW(eax)
        add eax,'a'-'A'
    .endif
    }
_ltoupperW proto watcall :word {
    .if _isllowerW(eax)
        sub eax,'a'-'A'
    .endif
    }

ifdef _UNICODE
define isltype          <_isltypeW>
define islalnum         <_islalnumW>
define islalpha         <_islalphaW>
define islcntrl         <_islcntrlW>
define isldigit         <_isldigitW>
define isllower         <_isllowerW>
define islpunct         <_islpunctW>
define islspace         <_islspaceW>
define islupper         <_islupperW>
define islxdigit        <_islxdigitW>
define islabel0         <_islabel0W>
define islabel          <_islabelW>
define isdotlabel       <_isdotlabelW>
define isclabel0        <_isclabel0W>
define isclabel         <_isclabelW>
define ltolower         <_ltolowerW>
define ltoupper         <_ltoupperW>
else
define isltype          <_isltypeA>
define islalnum         <_islalnumA>
define islalpha         <_islalphaA>
define islcntrl         <_islcntrlA>
define isldigit         <_isldigitA>
define isllower         <_isllowerA>
define islpunct         <_islpunctA>
define islspace         <_islspaceA>
define islupper         <_islupperA>
define islxdigit        <_islxdigitA>
define islabel0         <_islabel0A>
define islabel          <_islabelA>
define isdotlabel       <_isdotlabelA>
define isclabel0        <_isclabel0A>
define isclabel         <_isclabelA>
define ltolower         <_ltolowerA>
define ltoupper         <_ltoupperA>
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

endif
.pragma list(pop)
