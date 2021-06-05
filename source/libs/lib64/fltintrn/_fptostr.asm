; _FPTOSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include string.inc

    .code

_fptostr proc buf:string_t, digits:int_t, pflt:ptr STRFLT

    ; initialize the first digit in the buffer to '0' (NOTE - NOT '\0')
    ; and set the pointer to the second digit of the buffer.  The first
    ; digit is used to handle overflow on rounding (e.g. 9.9999...
    ; becomes 10.000...) which requires a carry into the first digit.

    mov byte ptr [rcx],'0'
    inc rcx

    ; Copy the digits of the value into the buffer (with 0 padding)
    ; and insert the terminating null character.

    .fors ( r9 = &[r8].STRFLT.mantissa, r10d = edx : r10d > 0 : r10d--, rcx++ )

        mov al,[r9]
        .if al
            inc r9
        .else
            mov al,'0'
        .endif
        mov [rcx],al
    .endf
    mov byte ptr [rcx],0
    mov al,[r9]

    ; do any rounding which may be needed.  Note - if digits < 0 don't
    ; do any rounding since in this case, the rounding occurs in  a digit
    ; which will not be output beause of the precision requested

    .ifs ( edx >= 0 && al >= '5' )

        mov r9,rcx
        dec r9
        .while ( byte ptr [r9] == '9' )

            mov byte ptr [r9],'0'
            dec r9
        .endw
        inc byte ptr [r9]
    .endif

    .if ( byte ptr [rcx] == '1' )

        ; the rounding caused overflow into the leading digit (e.g.
        ; 9.999.. went to 10.000...), so increment the decpt position
        ; by 1

        inc [r8].STRFLT.exponent

    .else
        ; move the entire string to the left one digit to remove the
        ; unused overflow digit.

        strcpy(rcx, &[rcx+1])
    .endif
    ret

_fptostr endp

    end
