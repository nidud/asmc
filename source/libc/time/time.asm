; TIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; time_t time( time_t *timeptr );
; __time32_t _time32( __time32_t *timeptr );
; __time64_t _time64( __time64_t *timeptr );
;
include time.inc
include stdlib.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
ifdef _WIN64
undef _time64
ALIAS <_time64>=<time>
else
undef _time32
ALIAS <_time32>=<time>
endif
endif

; Number of 100 nanosecond units from 1/1/1601 to 1/1/1970

define EPOCH_BIAS  116444736000000000

.code

ifdef __UNIX__
time proc timeptr:ptr time_t
    sys_time(ldr(timeptr))
else
time proc uses rbx timeptr:ptr time_t
  local ft:int64_t
    ldr rbx,timeptr
    GetSystemTimeAsFileTime( &ft )
ifdef _WIN64
    mov     rcx,ft
    mov     rax,-EPOCH_BIAS
    add     rcx,rax
    mov     rax,-2972493582642298179
    imul    rcx
    lea     rax,[rdx+rcx]
    sar     rcx,63
    sar     rax,23
    sub     rax,rcx
    mov     rcx,_MAX__TIME64_T
    mov     rdx,-1
    cmp     rax,rcx
    cmova   rax,rdx
else
    mov     eax,dword ptr ft
    mov     edx,dword ptr ft[4]
    sub     eax,LOW32(EPOCH_BIAS)
    sbb     edx,HIGH32(EPOCH_BIAS)
    push    ebx
    alldiv(edx::eax, 10000000)
    pop     ebx
    .ifs ( eax > _MAX__TIME32_T )
        mov eax,-1
    .endif
endif
    .if rbx
        mov [rbx],rax
    .endif
endif
    ret
    endp

    end
