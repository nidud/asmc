include errno.inc
include stdlib.inc

    .data
     __error_mode int_t _OUT_TO_DEFAULT

    .code

_set_error_mode proc em:int_t

    ldr ecx,em
    xor eax,eax

    .switch ecx
    .case _OUT_TO_DEFAULT
    .case _OUT_TO_STDERR
    .case _OUT_TO_MSGBOX
        mov eax,__error_mode
        mov __error_mode,ecx
       .endc
    .case _REPORT_ERRMODE
        mov eax,__error_mode
       .endc
    .default
        _set_errno(EINVAL)
        mov eax,-1
    .endsw
    ret

_set_error_mode endp

    end
