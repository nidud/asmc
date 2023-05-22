; _LSEEKI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdlib.inc
include crtl.inc
include winbase.inc

    .code

_lseeki64 proc handle:SINT, offs:QWORD, pos:UINT

  local lpNewFilePointer:QWORD

    .ifd ( _get_osfhandle( handle ) != -1 )

        mov rcx,rax
        .ifd !SetFilePointerEx( rcx, offs, &lpNewFilePointer, pos )

            _dosmaperr( GetLastError() )
ifdef _WIN64
        .else
            mov rax,lpNewFilePointer
else
            cdq
        .else
            mov eax,DWORD PTR lpNewFilePointer
            mov edx,DWORD PTR lpNewFilePointer[4]
endif
        .endif
    .endif
    ret

_lseeki64 endp

    end
