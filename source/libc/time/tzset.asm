; _TZSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
ifdef __UNIX__
include io.inc
include fcntl.inc
include string.inc
.data?
 tz_buf     char_t 4096 dup(?)
 tz_trans   ptr time_t ?
 tz_types   pbyte_t ?
 tz_ttinfo  pbyte_t ?
 tz_timecnt int_t ?
 tz_typecnt int_t ?
.data
 tzh_done char_t 0
else
include winbase.inc
endif
.code

ifdef __UNIX__
;
; Look up exact UTC offset (in seconds east of UTC) and isdst for any 64-bit Unix timestamp
; Returns: eax = UTC offset in seconds (e.g., +3600 for CET, +7200 for CEST)
;          edx = isdst (0 or 1)
;
__tz_lookup proc uses rsi rdi rbx t:time_t
    .if ( !tzh_done )
        _tzset()
    .endif

    mov ecx,tz_timecnt
    mov rdx,tz_trans
    .if ( ecx == 0 || !rdx || !tz_ttinfo )
        mov eax,_timezone
        neg eax
        xor edx,edx
       .return
    .endif
    mov rdi,t
    xor esi,esi
    mov ebx,ecx

    .while ( esi < ebx )
        lea eax,[rsi+rbx]
        shr eax,1               ; mid = (low + high) / 2
      ifdef _WIN64
        mov rcx,[rdx+rax*8]
        bswap rcx               ; Big-endian int64 -> host int64
        .ifs ( rcx <= rdi )
            lea esi,[rax+1]
        .else
            mov ebx,eax
        .endif
      else
        mov ecx,[edx+eax*4]
        bswap ecx               ; Big-endian int32 -> host int32
        .ifs ( ecx <= edi )
            lea esi,[eax+1]
        .else
            mov ebx,eax
        .endif
      endif
    .endw

    ; Transition index is (low - 1); if low == 0, default to type 0
    xor eax,eax
    .ifs ( esi > 0 )
        dec esi
        mov rax,tz_types
        movzx eax,byte ptr [rax+rsi]
    .endif
    imul    eax,eax,6
    mov     rcx,tz_ttinfo
    add     rcx,rax
    mov     eax,[rcx]
    bswap   eax                   ; Signed UTC offset in seconds (east of UTC)
    movzx   edx,byte ptr [rcx+4]  ; tt_isdst (0 or 1)
    ret
    endp

endif

_tzset proc uses rbx rsi
ifdef __UNIX__
   .new size:int_t
   .new fd:int_t
   .new v1_timecnt:int_t

    .if ( tzh_done )
        .return
    .endif

    .ifsd ( open( "/etc/localtime", O_RDONLY ) < 0 )
        .return
    .endif
    mov fd,eax
    lea rbx,tz_buf
    mov size,read(fd, rbx, 4096)
    close(fd)

    mov eax,[rbx]
    .if ( eax != 'fiZT' || size < 44 )
        .return
    .endif

    mov     ecx,[rbx+32]
    bswap   ecx
    mov     v1_timecnt,ecx
  ifdef _WIN64
    mov     eax,[rbx+20]
    bswap   eax
    mov     ecx,[rbx+24]
    bswap   ecx
    add     eax,ecx
    mov     ecx,[rbx+28]
    bswap   ecx
    imul    ecx,ecx,8
    add     eax,ecx
    mov     ecx,v1_timecnt
    imul    ecx,ecx,5
    add     eax,ecx
    mov     ecx,[rbx+36]
    bswap   ecx
    imul    ecx,ecx,6
    add     eax,ecx
    mov     ecx,[rbx+40]
    bswap   ecx
    add     eax,ecx
    add     eax,44                 ; Offset to v2 header

    mov cl,[rbx+4]
    .if ( (cl != '2' && cl != '3') || eax >= size )
        .return
    .endif
    lea rsi,[rbx+rax]
    .if ( dword ptr [rsi] != 'fiZT' )
        .return
    .endif

    mov     eax,[rsi+32]
    bswap   eax
    mov     tz_timecnt,eax
    mov     ecx,[rsi+36]
    bswap   ecx
    mov     tz_typecnt,ecx
    add     rsi,44
    mov     tz_trans,rsi
    imul    eax,eax,8
  else
    mov     eax,v1_timecnt
    mov     tz_timecnt,eax
    mov     ecx,[rbx+36]
    bswap   ecx
    mov     tz_typecnt,ecx
    lea     rsi,[rbx+44]
    mov     tz_trans,rsi
    imul    eax,eax,4
  endif
    add     rsi,rax
    mov     tz_types,rsi
    mov     eax,tz_timecnt
    add     rsi,rax
    mov     tz_ttinfo,rsi

     mov tzh_done,1

    ; Populate _timezone, _daylight, and _dstbias for current time

    __tz_lookup(time(0))
    .if ( edx == 0 )
        neg eax
        mov _timezone,eax
        mov _daylight,0
        mov _dstbias,0
    .else
        mov rbx,rax
        time(0)
        sub rax,15768000
        __tz_lookup(rax)
        sub ebx,eax
        neg ebx
        mov _dstbias,ebx
        mov _daylight,1
        neg eax
        mov _timezone,eax
    .endif

else

  local tz:TIME_ZONE_INFORMATION

    .ifd ( GetTimeZoneInformation( &tz ) != -1 )

        mov eax,tz.Bias
        mov ebx,tz.StandardBias
        mov ecx,tz.DaylightBias
        imul eax,eax,60
        .if ( tz.StandardDate.wMonth )
            imul edx,ebx,60
            add eax,edx
        .endif
        mov _timezone,eax
        xor eax,eax
        xor edx,edx
        .if ( ax != tz.DaylightDate.wMonth && eax != tz.DaylightBias )
            inc eax
            sub ecx,ebx
            imul edx,ecx,60
        .endif
        mov _daylight,eax
        mov _dstbias,edx
        xor eax,eax
        lea rdx,_tzname
        mov rcx,[rdx]
        mov [rcx],al
        mov rcx,[rdx+size_t]
        mov [rcx],al
    .endif
endif
    ret
    endp

_isindst proc uses rsi rdi rbx tb:ptr tm
    ldr rbx,tb
    .if ( !rbx )
        .return( 0 )
    .endif
ifdef __UNIX__
    mov edi,[rbx].tm.tm_year
    add edi,1900
    mov esi,[rbx].tm.tm_mon
    inc esi
    _loctotime_t( edi, esi, [rbx].tm.tm_mday, [rbx].tm.tm_hour, [rbx].tm.tm_min, [rbx].tm.tm_sec, 0 )
    __tz_lookup(rax)
    mov eax,edx                 ; Return tt_isdst (0 or 1)
else
    xor eax,eax
    mov ecx,[rbx].tm.tm_mon
    mov edx,[rbx].tm.tm_year
    .if ( eax == _daylight || edx < 67 || ecx < 3 || ecx > 9 )
        .return
    .endif
    inc eax
    .if ( ecx > 3 && ecx < 9 )
        .return
    .endif
    lea rax,_days
    mov edi,edx
    mov esi,[rax+rcx*4+4]
    .if ( edx > 86 && ecx == 3 )
        mov esi,[rax+rcx*4]
        add esi,7
    .endif
    .if !(edx & 3)
        inc esi
    .endif
    lea  rax,[rsi+365]
    lea  rcx,[rdx-70]
    mul  ecx
    lea  rax,[rax+rdi-1]
    shr  eax,2
    sub  eax,_LEAP_YEAR_ADJUST + _BASE_DOW
    xor  edx,edx
    mov  ecx,7
    idiv ecx
    mov  eax,1
    .if ( [rbx].tm.tm_mon == 3 )
        .if ( edx != [rbx].tm.tm_yday )
            .if ( edx > [rbx].tm.tm_yday )
                dec eax
            .endif
        .elseif ( [rbx].tm.tm_hour < 2 )
            dec eax
        .endif
    .elseif ( edx <= [rbx].tm.tm_yday )
        .if ( edx < [rbx].tm.tm_yday || [rbx].tm.tm_hour >= 1 )
            dec eax
        .endif
    .endif
endif
    ret
    endp

    end
