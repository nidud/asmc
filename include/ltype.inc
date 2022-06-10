.pragma list(push, 0)

; LTYPE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef __LTYPE_INC
define __LTYPE_INC
ifndef __LIBC_INC
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
name byte 0,            ; -1 EOF
    _CONTROL,           ; 00 (NUL)
    _CONTROL,           ; 01 (SOH)
    _CONTROL,           ; 02 (STX)
    _CONTROL,           ; 03 (ETX)
    _CONTROL,           ; 04 (EOT)
    _CONTROL,           ; 05 (ENQ)
    _CONTROL,           ; 06 (ACK)
    _CONTROL,           ; 07 (BEL)
    _CONTROL,           ; 08 (BS)
    _SPACE+_CONTROL,    ; 09 (HT)
    _SPACE+_CONTROL,    ; 0A (LF)
    _SPACE+_CONTROL,    ; 0B (VT)
    _SPACE+_CONTROL,    ; 0C (FF)
    _SPACE+_CONTROL,    ; 0D (CR)
    _CONTROL,           ; 0E (SI)
    _CONTROL,           ; 0F (SO)
    _CONTROL,           ; 10 (DLE)
    _CONTROL,           ; 11 (DC1)
    _CONTROL,           ; 12 (DC2)
    _CONTROL,           ; 13 (DC3)
    _CONTROL,           ; 14 (DC4)
    _CONTROL,           ; 15 (NAK)
    _CONTROL,           ; 16 (SYN)
    _CONTROL,           ; 17 (ETB)
    _CONTROL,           ; 18 (CAN)
    _CONTROL,           ; 19 (EM)
    _CONTROL,           ; 1A (SUB)
    _CONTROL,           ; 1B (ESC)
    _CONTROL,           ; 1C (FS)
    _CONTROL,           ; 1D (GS)
    _CONTROL,           ; 1E (RS)
    _CONTROL,           ; 1F (US)
    _SPACE,             ; 20 SPACE
    _PUNCT,             ; 21 !
    _PUNCT,             ; 22 ""
    _PUNCT,             ; 23 #
    _PUNCT+_LABEL,      ; 24 $
    _PUNCT,             ; 25 %
    _PUNCT,             ; 26 &
    _PUNCT,             ; 27 '
    _PUNCT,             ; 28 (
    _PUNCT,             ; 29 )
    _PUNCT,             ; 2A *
    _PUNCT,             ; 2B +
    _PUNCT,             ; 2C
    _PUNCT,             ; 2D -
    _PUNCT,             ; 2E .
    _PUNCT,             ; 2F /
    _DIGIT+_HEX,        ; 30 0
    _DIGIT+_HEX,        ; 31 1
    _DIGIT+_HEX,        ; 32 2
    _DIGIT+_HEX,        ; 33 3
    _DIGIT+_HEX,        ; 34 4
    _DIGIT+_HEX,        ; 35 5
    _DIGIT+_HEX,        ; 36 6
    _DIGIT+_HEX,        ; 37 7
    _DIGIT+_HEX,        ; 38 8
    _DIGIT+_HEX,        ; 39 9
    _PUNCT,             ; 3A :
    _PUNCT,             ; 3B ;
    _PUNCT,             ; 3C <
    _PUNCT,             ; 3D =
    _PUNCT,             ; 3E >
    _PUNCT+_LABEL,      ; 3F ?
    _PUNCT+_LABEL,      ; 40 @
    _UPPER+_LABEL+_HEX, ; 41 A
    _UPPER+_LABEL+_HEX, ; 42 B
    _UPPER+_LABEL+_HEX, ; 43 C
    _UPPER+_LABEL+_HEX, ; 44 D
    _UPPER+_LABEL+_HEX, ; 45 E
    _UPPER+_LABEL+_HEX, ; 46 F
    _UPPER+_LABEL,      ; 47 G
    _UPPER+_LABEL,      ; 48 H
    _UPPER+_LABEL,      ; 49 I
    _UPPER+_LABEL,      ; 4A J
    _UPPER+_LABEL,      ; 4B K
    _UPPER+_LABEL,      ; 4C L
    _UPPER+_LABEL,      ; 4D M
    _UPPER+_LABEL,      ; 4E N
    _UPPER+_LABEL,      ; 4F O
    _UPPER+_LABEL,      ; 50 P
    _UPPER+_LABEL,      ; 51 Q
    _UPPER+_LABEL,      ; 52 R
    _UPPER+_LABEL,      ; 53 S
    _UPPER+_LABEL,      ; 54 T
    _UPPER+_LABEL,      ; 55 U
    _UPPER+_LABEL,      ; 56 V
    _UPPER+_LABEL,      ; 57 W
    _UPPER+_LABEL,      ; 58 X
    _UPPER+_LABEL,      ; 59 Y
    _UPPER+_LABEL,      ; 5A Z
    _PUNCT,             ; 5B [
    _PUNCT,             ; 5C \
    _PUNCT,             ; 5D ]
    _PUNCT,             ; 5E ^
    _PUNCT+_LABEL,      ; 5F _
    _PUNCT,             ; 60 `
    _LOWER+_LABEL+_HEX, ; 61 a
    _LOWER+_LABEL+_HEX, ; 62 b
    _LOWER+_LABEL+_HEX, ; 63 c
    _LOWER+_LABEL+_HEX, ; 64 d
    _LOWER+_LABEL+_HEX, ; 65 e
    _LOWER+_LABEL+_HEX, ; 66 f
    _LOWER+_LABEL,      ; 67 g
    _LOWER+_LABEL,      ; 68 h
    _LOWER+_LABEL,      ; 69 i
    _LOWER+_LABEL,      ; 6A j
    _LOWER+_LABEL,      ; 6B k
    _LOWER+_LABEL,      ; 6C l
    _LOWER+_LABEL,      ; 6D m
    _LOWER+_LABEL,      ; 6E n
    _LOWER+_LABEL,      ; 6F o
    _LOWER+_LABEL,      ; 70 p
    _LOWER+_LABEL,      ; 71 q
    _LOWER+_LABEL,      ; 72 r
    _LOWER+_LABEL,      ; 73 s
    _LOWER+_LABEL,      ; 74 t
    _LOWER+_LABEL,      ; 75 u
    _LOWER+_LABEL,      ; 76 v
    _LOWER+_LABEL,      ; 77 w
    _LOWER+_LABEL,      ; 78 x
    _LOWER+_LABEL,      ; 79 y
    _LOWER+_LABEL,      ; 7A z
    _PUNCT,             ; 7B {
    _PUNCT,             ; 7C |
    _PUNCT,             ; 7D }
    _PUNCT,             ; 7E ~
    _CONTROL,           ; 7F (DEL)
    128 dup(0)          ; and the rest are 0...
    endm

ifdef __PE__
.data
DEFINE_LTYPE _ltype
_DATA ends
else
externdef _ltype: byte
endif

.pragma warning(disable: 8019) ; assume byte..

islascii    proto watcall :TCHAR { retm<(eax !< 128)> }
islprint    proto watcall :TCHAR { retm<(eax !>= 0x20 && eax !<= 0x7e)> }
islgraph    proto watcall :TCHAR { retm<(eax !>= 0x21 && eax !<= 0x7e)> }

ifdef _WIN64
;
; Use (global) r15 in 64-bit
;
ifndef _UNICODE
islalnum    proto watcall :byte { retm<(byte ptr [r15+rax+1] & (_DIGIT or _UPPER or _LOWER))> }
islalpha    proto watcall :byte { retm<(byte ptr [r15+rax+1] & (_UPPER or _LOWER))> }
islcntrl    proto watcall :byte { retm<(byte ptr [r15+rax+1] & _CONTROL)> }
isldigit    proto watcall :byte { retm<(byte ptr [r15+rax+1] & _DIGIT)> }
isllower    proto watcall :byte { retm<(byte ptr [r15+rax+1] & _LOWER)> }
islpunct    proto watcall :byte { retm<(byte ptr [r15+rax+1] & _PUNCT)> }
islspace    proto watcall :byte { retm<(byte ptr [r15+rax+1] & _SPACE)> }
islupper    proto watcall :byte { retm<(byte ptr [r15+rax+1] & _UPPER)> }
islxdigit   proto watcall :byte { retm<(byte ptr [r15+rax+1] & _HEX)> }
;
; Valid first char and next (= first + digit)
;
islabel0    proto watcall :byte { retm<(byte ptr [r15+rax+1] & _LABEL)> }
islabel     proto watcall :byte { retm<(byte ptr [r15+rax+1] & (_LABEL or _DIGIT))> }
isdotlabel  proto watcall :byte, :byte { retm<((al == '.' && dl) || (byte ptr [r15+rax+1] & _LABEL))> }
;
; C label
;
isclabel0   proto watcall :byte { retm<(al == '_' || byte ptr [r15+rax+1] & (_UPPER or _LOWER))> }
isclabel    proto watcall :byte { retm<(al == '_' || byte ptr [r15+rax+1] & (_UPPER or _LOWER or _DIGIT))> }
else
islalnum    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & (_DIGIT or _UPPER or _LOWER))> }
islalpha    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & (_UPPER or _LOWER))> }
islcntrl    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & _CONTROL)> }
isldigit    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & _DIGIT)> }
isllower    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & _LOWER)> }
islpunct    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & _PUNCT)> }
islspace    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & _SPACE)> }
islupper    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & _UPPER)> }
islxdigit   proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & _HEX)> }
islabel0    proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & _LABEL)> }
islabel     proto watcall :word { retm<(!ah && byte ptr [r15+rax+1] & (_LABEL or _DIGIT))> }
isdotlabel  proto watcall :word, :word { retm<((eax == '.' && edx) || (!ah && byte ptr [r15+rax+1] & _LABEL))> }
isclabel0   proto watcall :word { retm<(eax == '_' || (!ah && byte ptr [r15+rax+1] & (_UPPER or _LOWER)))> }
isclabel    proto watcall :word { retm<(eax == '_' || (!ah && byte ptr [r15+rax+1] & (_UPPER or _LOWER or _DIGIT)))> }
endif

else

islalnum    proto watcall :byte { retm<(_ltype[eax+1] & (_DIGIT or _UPPER or _LOWER))> }
islalpha    proto watcall :byte { retm<(_ltype[eax+1] & (_UPPER or _LOWER))> }
islcntrl    proto watcall :byte { retm<(_ltype[eax+1] & _CONTROL)> }
isldigit    proto watcall :byte { retm<(_ltype[eax+1] & _DIGIT)> }
isllower    proto watcall :byte { retm<(_ltype[eax+1] & _LOWER)> }
islpunct    proto watcall :byte { retm<(_ltype[eax+1] & _PUNCT)> }
islspace    proto watcall :byte { retm<(_ltype[eax+1] & _SPACE)> }
islupper    proto watcall :byte { retm<(_ltype[eax+1] & _UPPER)> }
islxdigit   proto watcall :byte { retm<(_ltype[eax+1] & _HEX)> }
islabel0    proto watcall :byte { retm<(_ltype[eax+1] & _LABEL)> }
islabel     proto watcall :byte { retm<(_ltype[eax+1] & (_LABEL or _DIGIT))> }
isdotlabel  proto watcall :byte, :byte { retm<((al == '.' && edx) || (_ltype[eax+1] & _LABEL))> }
isclabel0   proto watcall :byte { retm<(al == '_' || _ltype[eax+1] & (_UPPER or _LOWER))> }
isclabel    proto watcall :byte { retm<(al == '_' || _ltype[eax+1] & (_UPPER or _LOWER or _DIGIT))> }

endif

ltokstartc proto fastcall string:LPTSTR {
    .while ( islspace( [rcx] ) )
        add rcx,TCHAR
    .endw
    }

ltokstart proto fastcall string:LPTSTR {
    ltokstartc(rcx)
    xchg rax,rcx
    }

lprevtokc proto fastcall string_pos:LPTSTR, start_pos:LPTSTR {
    .while ( rcx > rdx && !islabel( [rcx] ) )
        sub rcx,TCHAR
    .endw
    .while ( rcx > rdx && islabel( [rcx] ) )
        sub rcx,TCHAR
    .endw
    .if ( !islabel( eax ) )
        .if ( islabel( [rcx+TCHAR] ) )
            add rcx,TCHAR
        .endif
        movzx eax,TCHAR ptr[rcx]
    .endif
    }

lnexttokc proto fastcall string_pos:LPTSTR {
    .while ( islabel( [rcx] ) )
        add rcx,TCHAR
    .endw
    .while ( eax && !islabel( [rcx] ) )
        add rcx,TCHAR
    .endw
    }

endif
.pragma list(pop)
