; __TIMET_TO_ST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

define SECS_PER_DAY 86400

.code

 assume rbx:ptr SYSTEMTIME

__timet_to_st proc uses rsi rdi rbx Time:time_t, lpSystemTime:ptr SYSTEMTIME
   .new doe:uint_t
   .new doy:uint_t
   .new mp:uint_t
    ldr rbx,lpSystemTime
    .if ( !rbx )
        .return( rbx )
    .endif
    mov [rbx].wMilliseconds,0
    ldr rax,Time
  ifdef _WIN64
    mov ecx,SECS_PER_DAY
    cqo
  else
    cdq
    mov ecx,SECS_PER_DAY
  endif
    idiv rcx
    .ifs ( rdx < 0 )
        dec rax
        add rdx,SECS_PER_DAY
    .endif
    mov rsi,rax
    mov eax,edx
    mov ecx,3600
    xor edx,edx
    div ecx
    mov [rbx].wHour,ax
    mov eax,edx
    mov ecx,60
    xor edx,edx
    div ecx
    mov [rbx].wMinute,ax
    mov [rbx].wSecond,dx
    mov rax,rsi
    add rax,4
  ifdef _WIN64
    mov ecx,7
    cqo
  else
    cdq
    mov ecx,7
  endif
    idiv rcx
    .ifs ( rdx < 0 )
        add rdx,7
    .endif
    mov [rbx].wDayOfWeek,dx
    mov rax,rsi
    add rax,719468
    mov rsi,rax
    .ifs ( rax < 0 )
        sub rax,146096
    .endif
  ifdef _WIN64
    mov ecx,146097
    cqo
  else
    cdq
    mov ecx,146097
  endif
    idiv rcx

    mov rcx,rax
    imul rax,rax,146097
    mov rdx,rsi
    sub rdx,rax
    mov doe,edx

    mov eax,edx
    mov esi,1460
    xor edx,edx
    div esi
    mov edx,doe
    sub edx,eax
    mov edi,edx

    mov eax,doe
    mov esi,36524
    xor edx,edx
    div esi
    add edi,eax

    mov eax,doe
    mov esi,146096
    xor edx,edx
    div esi
    sub edi,eax

    mov eax,edi
    mov esi,365
    xor edx,edx
    div esi
    mov edi,eax

    imul ecx,ecx,400
    add ecx,eax
    mov [rbx].wYear,cx

    mov ecx,edi
    imul eax,ecx,365
    shr ecx,2
    add eax,ecx
    mov doy,eax

    mov eax,edi
    mov ecx,100
    xor edx,edx
    div ecx
    mov edx,doy
    sub edx,eax
    mov eax,doe
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
    mov rax,rbx
    ret
    endp

    end
