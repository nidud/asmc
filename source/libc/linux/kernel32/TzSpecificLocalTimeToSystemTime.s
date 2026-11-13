; TZSPECIFICLOCALTIMETOSYSTEMTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include timezoneapi.inc

define NSEC_PER_SEC 1000000000

.code

 TzSpecificLocalTimeToSystemTime proc WINAPI uses rsi rdi rbx lpTimeZoneInformation:LPTIME_ZONE_INFORMATION,
        lpLocalTime:LPSYSTEMTIME, lpUniversalTime:LPSYSTEMTIME
   .new ft_local:FILETIME
   .new ft_utc:FILETIME
    ldr rsi,lpTimeZoneInformation
    ldr rdi,lpLocalTime
    ldr rbx,lpUniversalTime
    .if ( !rdi || !rbx )
        .return( FALSE )
    .endif
    .ifd !SystemTimeToFileTime(rdi, &ft_local)
        .return( FALSE )
    .endif
    .if ( !rsi )
        .ifd !LocalFileTimeToFileTime(&ft_local, &ft_utc)
            .return( FALSE )
        .endif
        .return FileTimeToSystemTime(&ft_utc, rbx)
    .endif
    .if ( [rsi].TIME_ZONE_INFORMATION.DaylightDate.wMonth != 0 &&
          [rsi].TIME_ZONE_INFORMATION.StandardDate.wMonth != 0 )
        movzx edx,[rdi].SYSTEMTIME.wMonth
        mov ax,[rsi].TIME_ZONE_INFORMATION.DaylightDate.wMonth
        .if ( ax < [rsi].TIME_ZONE_INFORMATION.StandardDate.wMonth )
            .if ( dx >= ax && dx < [rsi].TIME_ZONE_INFORMATION.StandardDate.wMonth )
                mov eax,[rsi].TIME_ZONE_INFORMATION.Bias
                add eax,[rsi].TIME_ZONE_INFORMATION.DaylightBias
            .else
                mov eax,[rsi].TIME_ZONE_INFORMATION.Bias
                add eax,[rsi].TIME_ZONE_INFORMATION.StandardBias
            .endif
        .else
            .if ( dx >= ax || dx < [rsi].TIME_ZONE_INFORMATION.StandardDate.wMonth )
                mov eax,[rsi].TIME_ZONE_INFORMATION.Bias
                add eax,[rsi].TIME_ZONE_INFORMATION.DaylightBias
            .else
                mov eax,[rsi].TIME_ZONE_INFORMATION.Bias
                add eax,[rsi].TIME_ZONE_INFORMATION.StandardBias
            .endif
        .endif
    .else
        mov eax,[rsi].TIME_ZONE_INFORMATION.Bias
        add eax,[rsi].TIME_ZONE_INFORMATION.StandardBias
    .endif
    imul eax,eax,60
  ifdef _WIN64
    movsxd rax,eax
    imul rax,rax,NSEC_PER_SEC
    add rax,ft_local
    mov ft_utc,rax
  else
    mov ecx,NSEC_PER_SEC
    imul ecx
    add eax,ft_local.dwLowDateTime
    adc edx,ft_local.dwHighDateTime
    mov ft_utc.dwLowDateTime,eax
    mov ft_utc.dwHighDateTime,edx
  endif
    .return FileTimeToSystemTime(&ft_utc, rbx)
    endp

    end
