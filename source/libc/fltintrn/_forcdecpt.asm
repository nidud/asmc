include string.inc
include fltintrn.inc

    .code
;
; '#' and precision == 0 means force a decimal point
;
_forcdecpt proc buffer:LPSTR

    .if !strchr(buffer, '.')

        strcat(buffer, ".0")
    .endif
    ret

_forcdecpt endp

    END
