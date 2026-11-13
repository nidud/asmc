; SYSTEMTIMETOFILETIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include timezoneapi.inc

define NSEC_PER_SEC  1000000000
define NSEC_PER_MSEC 1000000
define SECS_PER_DAY  86400

.code

 assume rbx:LPSYSTEMTIME

 SystemTimeToFileTime proc WINAPI uses rsi rdi rbx lpSystemTime:LPSYSTEMTIME, lpFileTime:LPFILETIME
   .new m:uint_t, d, yoe, doy, doe
    ldr rbx,lpSystemTime
    ldr rdi,lpFileTime
    .if ( !rbx || !rdi )
        .return( FALSE )
    .endif
    movzx eax,[rbx].wMonth
    .if ( eax < 1 || eax > 12 )
        .return( FALSE )
    .endif
    mov m,eax
    movzx eax,[rbx].wDay
    .if ( eax < 1 || eax > 31 )
        .return( FALSE )
    .endif
    mov d,eax
    .if ( [rbx].wHour > 23 || [rbx].wMinute > 59 || [rbx].wSecond > 59 || [rbx].wMilliseconds > 999 )
        .return( FALSE )
    .endif

    movsx rax,[rbx].wYear
    .if ( m <= 2 )
        dec rax
    .endif
    mov rsi,rax
    .ifs ( rax < 0 )
        sub rax,399
    .endif
    mov ecx,400
ifdef _WIN64
    cqo
else
    cdq
endif
    idiv    rcx
    mov     rdx,rsi
    mov     rsi,rax
    imul    rax,rax,400
    sub     rdx,rax
    mov     yoe,edx
    mov     eax,m

    .if ( eax > 2 )
        sub eax,3
    .else
        add eax,9
    .endif

    imul    eax,eax,153
    add     eax,2
    mov     ecx,5
    xor     edx,edx
    div     ecx
    add     eax,d
    dec     eax
    mov     doy,eax
    mov     ecx,yoe
    imul    eax,ecx,365
    mov     edx,ecx
    shr     edx,2
    add     eax,edx
    mov     doe,eax
    mov     eax,ecx
    mov     ecx,100
    xor     edx,edx
    div     ecx
    sub     doe,eax
    mov     eax,doy
    add     doe,eax
    imul    rax,rsi,146097
    mov     ecx,doe
    add     rax,rcx
    sub     rax,719468
    imul    rax,rax,SECS_PER_DAY
    movzx   ecx,[rbx].wHour
    imul    ecx,ecx,3600
    add     rax,rcx
    movzx   ecx,[rbx].wMinute
    imul    ecx,ecx,60
    add     rax,rcx
    movzx   ecx,[rbx].wSecond
    add     rax,rcx
    imul    rax,rax,NSEC_PER_SEC
    movzx   ecx,[rbx].wMilliseconds
    imul    rcx,rcx,NSEC_PER_MSEC
    add     rax,rcx
    mov     [rdi],rax
ifndef _WIN64
    cdq
    mov [edi+4],edx
endif
    .return( TRUE )
    endp

    end
