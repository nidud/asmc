; _LSEEKI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdlib.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc
endif

    .code

_lseeki64 proc handle:SINT, offs:QWORD, pos:UINT

ifdef __UNIX__

    ldr ecx,handle
    ldr rax,offs
    ldr edx,pos

    .ifs ( sys_lseek(ecx, rax, edx) < 0 )

        neg eax
        _set_errno(eax)
        mov rax,-1
    .endif
else

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
endif
    ret

_lseeki64 endp

    end
