; REWIND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc

    .code

rewind proc uses rbx fp:ptr FILE

    mov rbx,rdi
    fflush(rdi)

    mov eax,[rbx]._iobuf._flag
    and eax,not (_IOERR or _IOEOF)
    .if eax & _IORW
	and eax,not (_IOREAD or _IOWRT)
    .endif
    mov [rbx]._iobuf._flag,eax
    mov edi,[rbx]._iobuf._file

    lea rcx,_osfile
    and byte ptr [rcx+rdi],not FH_EOF
    _lseek(edi, 0, SEEK_SET)
    ret

rewind endp

    end
