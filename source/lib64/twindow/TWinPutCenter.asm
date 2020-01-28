; TWINPUTCENTER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t
    assume rbx:window_t

TWindow::PutCenter proc uses rsi rdi rbx x:int_t, y:int_t, l:int_t, string:string_t

    mov     rbx,rcx
    mov     rsi,string
    mov     edi,r9d
    .return [rbx].PutPath(x, y, edi, rsi) .ifd strlen(rsi) > edi

    sub     edi,eax
    shr     edi,1
    add     x,edi
    [rbx].PutString(x, y, 0, eax, rsi)
    ret

TWindow::PutCenter endp

    end
