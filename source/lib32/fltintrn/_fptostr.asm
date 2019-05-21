; _FPTOSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include string.inc

    .code

_fptostr proc buf:string_t, digits:int_t, pflt:ptr STRFLT

    mov ecx,buf
    mov edx,pflt

    ; initialize the first digit in the buffer to '0' (NOTE - NOT '\0')
    ; and set the pointer to the second digit of the buffer.  The first
    ; digit is used to handle overflow on rounding (e.g. 9.9999...
    ; becomes 10.000...) which requires a carry into the first digit.

    mov byte ptr [ecx],'0'
    inc ecx

    ; Copy the digits of the value into the buffer (with 0 padding)
    ; and insert the terminating null character.

    .for ( edx = [edx].STRFLT.mantissa : digits > 0 : digits--, ecx++ )

        mov al,[edx]
        .if al
            inc edx
        .else
            mov al,'0'
        .endif
        mov [ecx],al
    .endf
    mov byte ptr [ecx],0
    mov al,[edx]

    ; do any rounding which may be needed.  Note - if digits < 0 don't
    ; do any rounding since in this case, the rounding occurs in  a digit
    ; which will not be output beause of the precision requested

    .if ( digits >= 0 && al >= '5' )

        dec ecx
        .while ( byte ptr [ecx] == '9' )

            mov byte ptr [ecx],'0'
            dec ecx
        .endw
        inc byte ptr [ecx]
    .endif

    mov ecx,buf

    .if ( byte ptr [ecx] == '1' )

        ; the rounding caused overflow into the leading digit (e.g.
        ; 9.999.. went to 10.000...), so increment the decpt position
        ; by 1

        mov edx,pflt
        inc [edx].STRFLT.exponent

    .else
        ; move the entire string to the left one digit to remove the
        ; unused overflow digit.

        strcpy(ecx, &[ecx+1])
    .endif
    ret

_fptostr endp

    end
