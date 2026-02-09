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
.data
 tzh_done char_t 0
else
include winbase.inc
endif
.code

_tzset proc uses rbx

ifdef __UNIX__

   .new zone[128]:char_t
   .new rbuf[2048]:char_t
   .new size:int_t
   .new fd:int_t
   .new timecnt:int_t
   .new typecnt:int_t
   .new timidx:int_t
   .new stdzon:int_t
   .new dstzon:int_t

    .if ( tzh_done )
        .return
    .endif
    .ifsd ( open( "/etc/timezone", O_RDONLY ) < 0 )
        .return
    .endif
    mov fd,eax
    mov ebx,read(fd, &zone, 127)
    close(fd)
    mov zone[rbx],0
    .ifd ( strtrim(&zone) == 0 )
        .return
    .endif

    lea rbx,rbuf
    strcpy(rbx, "/usr/share/zoneinfo/")
    .ifsd ( open( strcat(rbx, &zone), O_RDONLY ) < 0 )
        .return
    .endif
    mov size,read(fd, rbx, 2048)
    close(fd)

    mov eax,[rbx]
    .if ( eax != 'fiZT' || size < 1024 )
        .return
    .endif

    mov     eax,[rbx+32]
    mov     ecx,[rbx+36]
    bswap   eax
    bswap   ecx
    mov     timecnt,eax
    mov     typecnt,ecx
    add     rbx,44
    mov     timidx,0
    mov     edx,time(0)

    .for ( ecx = 0 : ecx < timecnt : ecx++, rbx += 4 )

        mov     eax,[rbx]
        bswap   eax
        .if ( edx >= eax )
            mov timidx,ecx
        .endif
    .endf

    mov     eax,timidx
    movzx   ecx,byte ptr [rbx+rax]
    imul    ecx,ecx,6
    add     ecx,timecnt
    mov     stdzon,ecx
    movzx   edx,byte ptr [rbx+rcx+4]

    .ifs ( eax > 0 )

        movzx eax,byte ptr [rbx+rax-1]
        imul  eax,eax,6
        add   eax,timecnt
        .if ( edx )
            mov stdzon,eax
        .else
            mov ecx,eax
        .endif
    .endif

    xor eax,eax
    xor edx,edx
    mov dstzon,ecx
    .if ( ecx != stdzon )

        mov     eax,[rbx+rcx]
        bswap   eax
        mov     ecx,stdzon
        mov     ecx,[rbx+rcx]
        bswap   ecx
        sub     eax,ecx
        mov     edx,1
    .endif
    neg     eax
    mov     _dstbias,eax
    mov     _daylight,edx
    mov     ecx,stdzon
    mov     eax,[rbx+rcx]
    bswap   eax
    neg     eax
    mov     _timezone,eax
    movzx   ecx,byte ptr [rbx+rcx+5]
    add     ecx,timecnt
    imul    edx,typecnt,6
    add     ecx,edx
    mov     eax,dstzon
    movzx   eax,byte ptr [rbx+rax+5]
    add     eax,timecnt
    add     eax,edx
    lea     rdx,[rbx+rax]
    lea     rbx,[rbx+rcx]
    lea     rcx,_tzname
    strcpy( [rcx], rdx )
    lea     rcx,_tzname
    strcpy( [rcx+size_t], rbx )
    mov     tzh_done,1

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

_tzset endp


_isindst proc uses rsi rdi rbx tb:ptr tm

    ldr rsi,tb

    xor eax,eax
    mov ecx,[rsi].tm.tm_mon
    mov edx,[rsi].tm.tm_year
    .if ( eax == _daylight || edx < 67 || ecx < 3 || ecx > 9 )
        .return
    .endif
    inc eax
    .if ( ecx > 3 && ecx < 9 )
        .return
    .endif
    lea rax,_days
    mov edi,edx
    mov ebx,[rax+rcx*4+4]
    .if ( edx > 86 && ecx == 3 )
        mov ebx,[rax+rcx*4]
        add ebx,7
    .endif
    .if !(edx & 3)
        inc ebx
    .endif
    lea  rax,[rbx+365]
    lea  rcx,[rdx-70]
    mul  ecx
    lea  rax,[rax+rdi-1]
    shr  eax,2
    sub  eax,_LEAP_YEAR_ADJUST + _BASE_DOW
    xor  edx,edx
    mov  ecx,7
    idiv ecx
    mov  eax,1
    .if ( [rsi].tm.tm_mon == 3 )
        .if ( edx != [rsi].tm.tm_yday )
            .if ( edx > [rsi].tm.tm_yday )
                dec eax
            .endif
        .elseif ( [rsi].tm.tm_hour < 2 )
            dec eax
        .endif
    .elseif ( edx <= [rsi].tm.tm_yday )
        .if ( edx < [rsi].tm.tm_yday || [rsi].tm.tm_hour >= 1 )
            dec eax
        .endif
    .endif
    ret
    endp

    end
