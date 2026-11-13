; FILETIMETOSYSTEMTIME.ASM--
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

 FileTimeToSystemTime proc WINAPI uses rsi rdi rbx lpFileTime:LPFILETIME, lpSystemTime:LPSYSTEMTIME
   .new era:ssize_t
   .new rem_ns:ssize_t
   .new doy:uint_t
   .new mp:uint_t
    ldr rbx,lpSystemTime
    ldr rcx,lpFileTime
    .if ( !rcx || !rbx )
        .return( FALSE )
    .endif
    mov rax,[rcx]
ifdef _WIN64
    cqo
else
    mov edx,[ecx+4]
endif
    mov ecx,NSEC_PER_SEC
    idiv rcx
    .ifs ( rdx < 0 )
        dec rax
        add rdx,NSEC_PER_SEC
    .endif
    mov rem_ns,rdx
    mov ecx,SECS_PER_DAY
ifdef _WIN64
    cqo
else
    xor edx,edx
endif
    idiv rcx
    .ifs ( rdx < 0 )
        dec rax
        add rdx,SECS_PER_DAY
    .endif
    mov rdi,rax
    mov rsi,rdx
    mov ecx,3600
    mov rax,rdx
    xor rdx,rdx
    div rcx
    mov [rbx].wHour,ax
    mov ecx,60
    mov rax,rdx
    xor rdx,rdx
    div rcx
    mov [rbx].wMinute,ax
    mov ecx,60
    mov rax,rsi
    xor rdx,rdx
    div rcx
    mov [rbx].wSecond,dx
    mov ecx,NSEC_PER_MSEC
    mov rax,rem_ns
ifdef _WIN64
    cqo
else
    xor edx,edx
endif
    idiv rcx
    mov [rbx].wMilliseconds,ax
    mov ecx,7
    mov rax,rdi
    add rax,4
ifdef _WIN64
    cqo
else
    xor edx,edx
endif
    idiv rcx
    .ifs ( rdx < 0 )
        add rdx,rcx
    .endif
    mov [rbx].wDayOfWeek,dx
    mov rax,rdi
    add rax,719468
    mov rdi,rax
    .ifs ( rax < 0 )
        sub rax,146096
    .endif
    mov ecx,146097
ifdef _WIN64
    cqo
else
    xor edx,edx
endif
    idiv rcx
    mov era,rax
    mul rcx
    mov rdx,rdi
    sub rdx,rax
    mov edi,edx
    mov eax,edx
    mov ecx,1460
    xor edx,edx
    div ecx
    mov edx,edi
    sub edx,eax
    mov esi,edx
    mov eax,edi
    mov ecx,36524
    xor edx,edx
    div ecx
    add esi,eax
    mov eax,edi
    mov ecx,146096
    xor edx,edx
    div ecx
    sub esi,eax
    mov ecx,365
    mov eax,esi
    xor edx,edx
    div ecx
    mov esi,eax
    mov rcx,400
    mov rax,era
    mul rcx
    add eax,esi
    mov [rbx].wYear,ax
    mov ecx,esi
    imul eax,ecx,365
    shr ecx,2
    add eax,ecx
    mov doy,eax
    mov ecx,100
    mov eax,esi
    xor edx,edx
    div ecx
    mov edx,doy
    sub edx,eax
    mov eax,edi
    sub eax,edx
    mov doy,eax
    imul eax,eax,5
    add eax,2
    mov ecx,153
    xor edx,edx
    div ecx
    mov mp,eax
    imul eax,eax,153
    add eax,2
    mov ecx,5
    xor edx,edx
    div ecx
    mov edx,doy
    sub edx,eax
    inc edx
    mov [rbx].wDay,dx
    mov eax,mp
    mov ecx,-9
    .if ( eax < 10 )
        mov ecx,3
    .endif
    add eax,ecx
    mov [rbx].wMonth,ax
    .if ( eax <= 2 )
        inc [rbx].wYear
    .endif
    mov eax,1
    ret
    endp

    end

