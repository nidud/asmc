; TDIALOG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include tdialog.inc

    .data

    Vtbl dq TObject_Release

    .code

TObject::TObject proc uses rsi rbx p:LPROBJECT

    mov rbx,rcx
    mov rsi,rdx

    .if malloc( sizeof(TObject) )

        lea rdx,Vtbl
        mov [rax],rdx
        mov rdx,[rsi]
        mov [rax+8],rdx

    .endif

    .if rbx

        mov [rbx],rax
    .endif
    ret

TObject::TObject endp


TObject::Release proc uses rbx

    mov rbx,rcx

    free( [rcx].TObject.pData )
    free( rbx )
    ret

TObject::Release endp

    end
