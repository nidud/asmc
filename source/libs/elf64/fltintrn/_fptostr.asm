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

    mov byte ptr [rdi],'0'
    inc rdi

    ; Copy the digits of the value into the buffer (with 0 padding)
    ; and insert the terminating null character.

    .fors ( rcx = &[rdx].STRFLT.mantissa, r8d = esi : r8d > 0 : r8d--, rdi++ )

        mov al,[rcx]
        .if al
            inc rcx
        .else
            mov al,'0'
        .endif
        mov [rdi],al
    .endf
    mov byte ptr [rdi],0
    mov al,[rcx]

    ; do any rounding which may be needed.  Note - if digits < 0 don't
    ; do any rounding since in this case, the rounding occurs in  a digit
    ; which will not be output beause of the precision requested

    .ifs ( esi >= 0 && al >= '5' )

        mov rcx,rdi
        dec rcx
        .while ( byte ptr [rcx] == '9' )

            mov byte ptr [rcx],'0'
            dec rcx
        .endw
        inc byte ptr [rcx]
    .endif

    .if ( byte ptr [rdi] == '1' )

        ; the rounding caused overflow into the leading digit (e.g.
        ; 9.999.. went to 10.000...), so increment the decpt position
        ; by 1

        inc [rdx].STRFLT.exponent

    .else
        ; move the entire string to the left one digit to remove the
        ; unused overflow digit.

        strcpy(rdi, &[rdi+1])
    .endif
    ret

_fptostr endp

    end
