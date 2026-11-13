; __TIMET_TO_ST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

define SECS_PER_DAY 86400

.code

 assume rbx:ptr SYSTEMTIME

__timet_to_st proc uses rbx Time:time_t, lpSystemTime:ptr SYSTEMTIME
   .new days:ssize_t
   .new day_secs:uint_t
   .new doe:uint_t
   .new yoe:uint_t
   .new doy:uint_t
   .new mp:uint_t

    ldr rbx,lpSystemTime
    .if ( !rbx )
        .return( NULL )
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
    mov days,rax
    mov day_secs,edx

    ; wHour = day_secs / 3600, remainder in edx
    mov eax,edx
    mov ecx,3600
    xor edx,edx
    div ecx
    mov [rbx].wHour,ax

    ; wMinute = rem / 60, wSecond = rem % 60
    mov eax,edx
    mov ecx,60
    xor edx,edx
    div ecx
    mov [rbx].wMinute,ax
    mov [rbx].wSecond,dx

    ; wDayOfWeek = (days + 4) % 7  (0 = Sunday .. 6 = Saturday)
    mov rax,days
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

    ; Civil date from Unix days (shift epoch from 1970-01-01 to 0000-03-01)
    mov rax,days
    add rax,719468
    mov days,rax
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
    ; rax = era (kept in rcx for later multiplication), remainder in rdx = doe
    ; Note: For negative dates, compute doe = days - era * 146097 explicitly
    mov rcx,rax
    imul rax,rax,146097
    mov rdx,days
    sub rdx,rax
    mov doe,edx

    ; yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365
    mov eax,edx
    mov esi,1460
    xor edx,edx
    div esi
    mov edx,doe
    sub edx,eax
    mov yoe,edx

    mov eax,doe
    mov esi,36524
    xor edx,edx
    div esi
    add yoe,eax

    mov eax,doe
    mov esi,146096
    xor edx,edx
    div esi
    sub yoe,eax

    mov eax,yoe
    mov esi,365
    xor edx,edx
    div esi
    mov yoe,eax

    ; wYear = era * 400 + yoe
    imul ecx,ecx,400
    add ecx,eax
    mov [rbx].wYear,cx

    ; doy = doe - (365 * yoe + yoe / 4 - yoe / 100)
    mov ecx,yoe
    imul eax,ecx,365
    shr ecx,2
    add eax,ecx
    mov doy,eax

    mov eax,yoe
    mov ecx,100
    xor edx,edx
    div ecx
    mov edx,doy
    sub edx,eax
    mov eax,doe
    sub eax,edx
    mov doy,eax

    ; mp = (5 * doy + 2) / 153
    imul eax,eax,5
    add eax,2
    mov ecx,153
    xor edx,edx
    div ecx
    mov mp,eax

    ; wDay = doy - (153 * mp + 2) / 5 + 1
    imul eax,eax,153
    add eax,2
    mov ecx,5
    xor edx,edx
    div ecx
    mov edx,doy
    sub edx,eax
    inc edx
    mov [rbx].wDay,dx

    ; wMonth = mp + (mp < 10 ? 3 : -9)
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
