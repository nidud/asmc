; _TTSCPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

scputs proc uses rsi rdi rbx x:int_t, y:int_t, a:int_t, maxlen:int_t, string:LPTSTR

   .new q:byte

    ldr eax,x
    ldr rbx,string

    mov q,al
    .if ( maxlen == 0 )
        dec maxlen
    .endif

    .for ( rbx = string : maxlen && TCHAR ptr [rbx] : maxlen--, rbx+=TCHAR, q++ )

        movzx ecx,TCHAR ptr [rbx]
        .if ( ecx == 10 )

            inc y
            mov q,x
            dec q
           .continue

        .elseif ( ecx == 9 )

            mov al,q
            add al,4
            and al,-4
            dec al
            mov q,al
           .continue
        .endif
        _scputc(q, byte ptr y, 1, cx)
        .if ( byte ptr a )

            _scputa(q, byte ptr y, 1, byte ptr a)
        .endif
    .endf
    sub rsi,string
    mov eax,esi
ifdef _UNICODE
    shr eax,1
endif
    ret

scputs endp

    end
