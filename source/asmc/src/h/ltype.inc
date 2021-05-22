.pragma list(push, 0)

ifndef __LIBC_INC
 include libc.inc
endif

_UPPER      equ 01h ; upper case letter
_LOWER      equ 02h ; lower case letter
_DIGIT      equ 04h ; digit[0-9]
_SPACE      equ 08h ; tab, carriage return, newline, vertical tab or form feed
_PUNCT      equ 10h ; punctuation character
_CONTROL    equ 20h ; control character
_LABEL      equ 40h ; _UPPER + _LOWER + '@' + '_' + '$' + '?'
_HEX        equ 80h ; hexadecimal digit

externdef   _ltype: BYTE ; Label type array

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

.pragma list(pop)
