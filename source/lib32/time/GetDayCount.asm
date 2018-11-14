; GETDAYCOUNT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

GetDayCount proc uses esi edi ebx y, m, d

local t:SYSTEMTIME, cur_y, cur_m, cur_d, result

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
    .if esi > cur_y
        xchg esi,cur_y
        xchg edi,cur_d
        xchg ebx,cur_m
    .elseif esi == cur_y && ebx > cur_m
        xchg edi,cur_d
        xchg ebx,cur_m
    .elseif esi == cur_y && ebx == cur_m && edi > cur_d
        xchg edi,cur_d
    .endif
    mov result,0
    .while  esi < cur_y || ebx < cur_m || edi < cur_d
        inc edi
        inc result
        .if DaysInMonth(esi, ebx) < edi
            mov edi,1
            inc ebx
            .if ebx > 12
                mov ebx,1
                inc esi
            .endif
        .endif
    .endw
    mov eax,result
    ret

GetDayCount endp

    END
