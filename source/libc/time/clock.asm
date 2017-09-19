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
