; CLOCK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

clock proc
  local t:SYSTEMTIME
    mov edx,edi
    xor eax,eax
    mov ecx,SIZE SYSTEMTIME
    lea edi,t
    rep stosb
    mov edi,edx
    GetLocalTime(&t)
    __STToTime(&t)
    ret
clock endp

    END
