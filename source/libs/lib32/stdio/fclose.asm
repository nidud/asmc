; FCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

fclose proc uses esi ebx fp:LPFILE

    mov ebx,fp
    mov eax,[ebx]._iobuf._flag
    and eax,_IOREAD or _IOWRT or _IORW
    .ifnz
        mov esi,fflush(ebx)
        _freebuf(ebx)
        xor eax,eax
        mov [ebx]._iobuf._flag,eax
        mov ecx,[ebx]._iobuf._file
        dec eax
        mov [ebx]._iobuf._file,eax
        .if _close(ecx)
            mov eax,-1
        .else
            mov eax,esi
        .endif
    .else
        dec eax
    .endif
    ret

fclose endp

    END
