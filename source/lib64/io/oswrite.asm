; OSWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

    .code

    option win64:nosave

oswrite proc frame uses rbx h:SINT, b:PVOID, z:SIZE_T

  local NumberOfBytesWritten:dword

    mov ebx,r8d
    lea rax,_osfhnd
    mov rcx,[rax+rcx*8]
    .if WriteFile(rcx, rdx, r8d, &NumberOfBytesWritten, 0)

        mov eax,NumberOfBytesWritten
        .if eax != ebx
            mov errno,ERROR_DISK_FULL
            xor eax,eax
        .endif
    .else
        _dosmaperr(GetLastError())
        xor eax,eax
    .endif
    ret

oswrite endp

    end
