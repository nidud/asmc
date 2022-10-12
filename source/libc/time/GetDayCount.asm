; GETDAYCOUNT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

GetDayCount proc uses rsi rdi rbx y:uint_t, m:uint_t, d:uint_t

  local t:SYSTEMTIME,
        cur_y:uint_t,
        cur_m:uint_t,
        cur_d:uint_t,
        result:uint_t

    GetLocalTime(&t)

    movzx eax,t.wYear
    mov cur_y,eax
    mov ax,t.wMonth
    mov cur_m,eax
    mov ax,t.wDay
    mov cur_d,eax

    mov esi,y
    mov ebx,m
    mov edi,d

    .if ( esi > cur_y )

        xchg esi,cur_y
        xchg edi,cur_d
        xchg ebx,cur_m

    .elseif ( esi == cur_y && ebx > cur_m )

        xchg edi,cur_d
        xchg ebx,cur_m

    .elseif ( esi == cur_y && ebx == cur_m && edi > cur_d )

        xchg edi,cur_d
    .endif

    mov result,0

    .while ( esi < cur_y || ebx < cur_m || edi < cur_d )

        inc edi
        inc result

        .if ( DaysInMonth(esi, ebx) < rdi )

            mov edi,1
            inc ebx

            .if ( ebx > 12 )

                mov ebx,1
                inc esi
            .endif
        .endif
    .endw
    .return( result )

GetDayCount endp

    end
