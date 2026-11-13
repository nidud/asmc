; _CONFH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include stdio.inc
include conio.inc

.data
 _confh HANDLE -1
 _confd int_t -1

.code

__initconout proc private

    mov _confd,_open(CONOUT, O_BINARY or O_RDWR or O_NOCTTY)
    .ifs ( eax > 0 )
ifdef __UNIX__
        .if _getst()
            mov ecx,_confd
            mov [rax].FILE._file,ecx
            mov [rax].FILE._flag,_IOWRT
        .endif
else
        _get_osfhandle(eax)
endif
        mov _confh,rax
    .endif
    ret
    endp

.pragma init(__initconout, 21)

    end
