; REWIND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include winbase.inc

    .code

    assume rbx:LPFILE

rewind proc uses rbx fp:LPFILE

    ldr rbx,fp
    fflush( rbx )

    mov eax,[rbx]._flag
    and eax,not (_IOERR or _IOEOF)
    .if ( eax & _IORW )
	and eax,not (_IOREAD or _IOWRT)
    .endif
    mov [rbx]._flag,eax
    and _osfile([rbx]._file),not FEOFLAG
    _lseek( [rbx]._file, 0, SEEK_SET )
    ret

rewind endp

    end
