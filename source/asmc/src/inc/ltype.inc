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

externdef _ltype: byte ; Label type array

islalnum proto watcall c:byte {
    retm<(_ltype[eax+1] & (_DIGIT or _UPPER or _LOWER))>
    }
islalpha proto watcall c:byte {
    retm<(_ltype[eax+1] & (_UPPER or _LOWER))>
    }
islascii proto watcall c:byte {
    retm<(al !< 128)>
    }
islcntrl proto watcall c:byte {
    retm<(_ltype[eax+1] & _CONTROL)>
    }
isldigit proto watcall c:byte {
    retm<(_ltype[eax+1] & _DIGIT)>
    }
islgraph proto watcall c:byte {
    retm<(al !>= 0x21 && al !<= 0x7e)>
    }
isllower proto watcall c:byte {
    retm<(_ltype[eax+1] & _LOWER)>
    }
islprint proto watcall c:byte {
    retm<(al !>= 0x20 && al !<= 0x7e)>
    }
islpunct proto watcall c:byte {
    retm<(_ltype[eax+1] & _PUNCT)>
    }
islspace proto watcall c:byte {
    retm<(_ltype[eax+1] & _SPACE)>
    }
islupper proto watcall c:byte {
    retm<(_ltype[eax+1] & _UPPER)>
    }
islxdigit proto watcall c:byte {
    retm<(_ltype[eax+1] & _HEX)>
    }
islabel proto watcall c:byte {
    retm<(_ltype[eax+1] & _LABEL)>
    }

is_valid_id_char proto watcall c:byte {
    retm<(_ltype[eax+1] & (_LABEL or _DIGIT))>
    }
is_valid_id_first_char proto watcall :byte {
    retm<((al == '.' && ModuleInfo.dotname) || (_ltype[eax+1] & _LABEL))>
    }
is_valid_id_start proto watcall c:byte {
    retm<(_ltype[eax+1] & _LABEL)>
    }
is_valid_first_char proto watcall c:byte {
    retm<(al == '.' || (_ltype[eax+1] & _LABEL))>
    }

ltokstart proto fastcall string:string_t {
    .while ( islspace( [ecx] ) )
        inc ecx
    .endw
    xchg ecx,eax
    }

endif
