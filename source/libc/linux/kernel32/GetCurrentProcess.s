; GETCURRENTPROCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include processthreadsapi.inc

.code

 GetCurrentProcess proc WINAPI
    xor rax,rax
    dec rax ; Win32 pseudo-handle ((HANDLE)-1)
    ret
    endp

    end
