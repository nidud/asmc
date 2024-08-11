; FPTOSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include string.inc

    .code

_fptostr proc __ccall buf:string_t, digits:int_t, pflt:ptr STRFLT

    ; initialize the first digit in the buffer to '0' (NOTE - NOT '\0')
    ; and set the pointer to the second digit of the buffer.  The first
    ; digit is used to handle overflow on rounding (e.g. 9.9999...
    ; becomes 10.000...) which requires a carry into the first digit.

    ldr rcx,buf
    ldr rdx,pflt

    mov byte ptr [rcx],'0'
    inc rcx

    ; Copy the digits of the value into the buffer (with 0 padding)
    ; and insert the terminating null character.

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

    ; do any rounding which may be needed.  Note - if digits < 0 don't
    ; do any rounding since in this case, the rounding occurs in  a digit
    ; which will not be output beause of the precision requested

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

        ; the rounding caused overflow into the leading digit (e.g.
        ; 9.999.. went to 10.000...), so increment the decpt position
        ; by 1

        mov rdx,pflt
        inc [rdx].STRFLT.exponent

    .else
        ; move the entire string to the left one digit to remove the
        ; unused overflow digit.

        strcpy( rcx, &[rcx+1] )
    .endif
    ret

_fptostr endp

    end
