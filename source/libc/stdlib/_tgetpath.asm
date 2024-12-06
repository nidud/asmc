; _TGETPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char * _getpath(const char *, char *, size_t);
; wchar_t * _wgetpath(const wchar_t *, wchar_t *, size_t);
;
include stdlib.inc
include errno.inc
include tchar.inc

ifdef __UNIX__
define DELIM ':'
else
define DELIM ';'
endif

define _HPFS_

    .code

    assume rbx:tstring_t

_tgetpath proc uses rbx src:tstring_t, dst:tstring_t, maxlen:size_t

    ldr rbx,src
    ldr rcx,maxlen
    ldr rdx,dst

    .while ( [rbx] == DELIM )
        add rbx,TCHAR
    .endw
    mov src,rbx
    dec rcx
    jz  error

    .while ( [rbx] && [rbx] != DELIM )

ifdef _HPFS_

        .if ( [rbx] != '"' )

            mov _tal,[rbx]
            mov [rdx],_tal
            add rdx,TCHAR
            add rbx,TCHAR
            dec rcx
            jz  error

        .else

            add rbx,TCHAR
            .while ( [rbx] && [rbx] != '"' )

                mov _tal,[rbx]
                mov [rdx],_tal
                add rdx,TCHAR
                add rbx,TCHAR
                dec rcx
                jz  error
            .endw
            .if ( [rbx] )
                add rbx,TCHAR
            .endif
        .endif

else
        mov _tal,[rbx]
        mov [rdx],_tal
        add rdx,TCHAR
        add rbx,TCHAR
        dec rcx
        jz  error
endif
    .endw

    .while ( [rbx] == DELIM )
        add rbx,TCHAR
    .endw

appendnull:
    xor eax,eax
    mov [rdx],_tal
    .if ( rbx != src )
        mov rax,rbx
    .endif
    ret

error:
    mov src,rbx
    mov dst,rdx
    _set_errno(ERANGE)
    mov rdx,dst
    jmp appendnull

_tgetpath endp

    end
