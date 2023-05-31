; _FILELENGTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifndef __UNIX__
include winbase.inc
endif

    .code

_filelength proc handle:SINT
ifdef __UNIX__
    _set_errno( ENOSYS )
    xor eax,eax
else

  local FileSize:QWORD

    ldr ecx,handle
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
endif
    ret

_filelength endp

    end
