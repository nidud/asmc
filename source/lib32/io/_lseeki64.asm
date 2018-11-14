; _LSEEKI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc

.code

_lseeki64 proc handle:SINT, offs:QWORD, pos:DWORD

  local lpNewFilePointer:QWORD

    .if getosfhnd(handle) != -1

        mov ecx,eax
        lea eax,lpNewFilePointer

        .if !SetFilePointerEx(ecx, offs, eax, pos)

            osmaperr()
            mov edx,eax
        .else
            mov eax,DWORD PTR lpNewFilePointer
            mov edx,DWORD PTR lpNewFilePointer[4]
        .endif
    .else
        mov edx,eax
    .endif
    ret
_lseeki64 ENDP

    END
