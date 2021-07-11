; OSREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

    .code

osread proc h:SINT, b:PVOID, z:SIZE_T

  local count:UINT

    lea rax,_osfhnd
    mov rcx,[rax+rcx*8]

    .ifd !ReadFile(rcx, rdx, r8d, &count, 0)

        _dosmaperr(GetLastError())
        xor eax,eax
    .else

        mov ecx,eax
        mov eax,count
    .endif
    ret

osread endp

    end
