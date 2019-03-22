include cruntime.inc
include internal.inc
include stdlib.inc

.data
__error_mode int_t _OUT_TO_DEFAULT

.code

_set_error_mode proc em:int_t

  local retval:int_t

    mov retval,0

    .repeat

        .switch (ecx)
        .case _OUT_TO_DEFAULT
        .case _OUT_TO_STDERR
        .case _OUT_TO_MSGBOX
            mov eax,__error_mode
            mov retval,eax
            mov __error_mode,ecx
            .endc
        .case _REPORT_ERRMODE
            mov eax,__error_mode
            mov retval,eax
            .endc
        .default
            _VALIDATE_RETURN(0, EINVAL, -1) ;; L"Invalid error_mode" && 0
        .endsw
        mov eax,retval
    .until 1
    ret

_set_error_mode endp

if (defined(_CRT_APP) eq 0) or defined(_KERNELX)

__set_app_type proc at:int_t
    mov __app_type,ecx
    ret
__set_app_type endp

endif

    end
