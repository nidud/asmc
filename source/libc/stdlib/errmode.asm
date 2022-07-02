include cruntime.inc
include internal.inc
include stdlib.inc

.data
__error_mode int_t _OUT_TO_DEFAULT

.code

_set_error_mode proc em:int_t

    .new retval:int_t = 0

ifndef _WIN64
    mov ecx,em
endif
    .switch ecx
    .case _OUT_TO_DEFAULT
    .case _OUT_TO_STDERR
    .case _OUT_TO_MSGBOX
        mov retval,__error_mode
        mov __error_mode,ecx
       .endc
    .case _REPORT_ERRMODE
        mov retval,__error_mode
       .endc
    .default
        .repeat
         _VALIDATE_RETURN(0, EINVAL, -1) ; L"Invalid error_mode" && 0
        .until 1
        mov retval,eax
    .endsw
    .return( retval )

_set_error_mode endp

if (defined(_CRT_APP) eq 0) or defined(_KERNELX)

__set_app_type proc at:int_t

ifndef _WIN64
    mov ecx,at
endif
    mov __app_type,ecx
    ret

__set_app_type endp

endif

    end
