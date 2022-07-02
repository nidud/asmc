; _FILELENGTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

    .code

_filelength proc handle:SINT

  local FileSize:QWORD

    mov ecx,handle
    lea rax,_osfhnd
    mov rcx,[rax+rcx*size_t]

    .if GetFileSizeEx( rcx, &FileSize )
ifdef _WIN64
        mov rax,FileSize
else
        mov edx,dword ptr FileSize[4]
        mov eax,dword ptr FileSize
endif
    .else
        _dosmaperr( GetLastError() )
        xor eax,eax
    .endif
    ret

_filelength endp

    end
