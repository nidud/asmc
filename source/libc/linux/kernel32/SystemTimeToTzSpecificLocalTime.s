; SYSTEMTIMETOTZSPECIFICLOCALTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include timezoneapi.inc

define NSEC_PER_SEC 1000000000

.code

 SystemTimeToTzSpecificLocalTime proc WINAPI uses rsi rdi rbx lpTimeZoneInformation:LPTIME_ZONE_INFORMATION,
        lpUniversalTime:LPSYSTEMTIME, lpLocalTime:LPSYSTEMTIME
   .new ft_utc:FILETIME
   .new ft_local:FILETIME
    ldr rsi,lpTimeZoneInformation
    ldr rdi,lpUniversalTime
    ldr rbx,lpLocalTime
    .if ( !rdi || !rbx )
        .return( FALSE )
    .endif
    .ifd !SystemTimeToFileTime(rdi, &ft_utc)
        .return( FALSE )
    .endif
    .if ( !rsi )
        .ifd !FileTimeToLocalFileTime(&ft_utc, &ft_local)
            .return( FALSE )
        .endif
        .return FileTimeToSystemTime(&ft_local, rbx)
    .endif
    mov eax,[rsi].TIME_ZONE_INFORMATION.Bias
    .if ( [rsi].TIME_ZONE_INFORMATION.DaylightDate.wMonth != 0 &&
          [rsi].TIME_ZONE_INFORMATION.StandardDate.wMonth != 0 )
        movzx edx,[rdi].SYSTEMTIME.wMonth
        movzx edi,[rsi].TIME_ZONE_INFORMATION.DaylightDate.wMonth
        movzx ecx,[rsi].TIME_ZONE_INFORMATION.StandardDate.wMonth
        .if ( edi < ecx )
            .if ( edx >= edi && edx < ecx )
                add eax,[rsi].TIME_ZONE_INFORMATION.DaylightBias
            .else
                add eax,[rsi].TIME_ZONE_INFORMATION.StandardBias
            .endif
        .else
            .if ( edx >= edi || edx < ecx )
                add eax,[rsi].TIME_ZONE_INFORMATION.DaylightBias
            .else
                add eax,[rsi].TIME_ZONE_INFORMATION.StandardBias
            .endif
        .endif
    .else
        add eax,[rsi].TIME_ZONE_INFORMATION.StandardBias
    .endif
    imul eax,eax,-60
  ifdef _WIN64
    movsxd rax,eax
    imul rax,rax,NSEC_PER_SEC
    add rax,ft_utc
    mov ft_local,rax
  else
    mov ecx,NSEC_PER_SEC
    imul ecx
    add eax,ft_utc.dwLowDateTime
    adc edx,ft_utc.dwHighDateTime
    mov ft_local.dwLowDateTime,eax
    mov ft_local.dwHighDateTime,edx
  endif
    .return FileTimeToSystemTime(&ft_local, rbx)
    endp

    end
