; FPTOSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include string.inc

    .code

_fptostr proc __ccall buf:string_t, digits:int_t, pflt:ptr STRFLT

    ldr rcx,buf
    ldr rdx,pflt

    mov byte ptr [rcx],'0'
    inc rcx
    .for ( : digits > 0 : digits--, rcx++ )
        mov al,[rdx]
        .if al
            inc rdx
        .else
            mov al,'0'
        .endif
        mov [rcx],al
    .endf
    mov byte ptr [rcx],0
    mov al,[rdx]
    .if ( digits >= 0 && al >= '5' )
        dec rcx
        .while ( byte ptr [rcx] == '9' )
            mov byte ptr [rcx],'0'
            dec rcx
        .endw
        inc byte ptr [rcx]
    .endif
    mov rcx,buf
    .if ( byte ptr [rcx] == '1' )
        mov rdx,pflt
        inc [rdx].STRFLT.exponent
    .else
        strcpy( rcx, &[rcx+1] )
    .endif
    ret
    endp

    end
