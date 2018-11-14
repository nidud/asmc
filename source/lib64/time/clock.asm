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

    mov rdx,rdi
    xor eax,eax
    mov ecx,sizeof(SYSTEMTIME)
    lea rdi,t
    rep stosb
    mov rdi,rdx
    GetLocalTime( &t )
    __STToTime( &t )
    ret

clock endp

    end
