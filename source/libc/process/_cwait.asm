; _CWAIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _cwait(int *stat_loc, intptr_t process_id, int action_code);
;

include errno.inc
ifndef __UNIX__
include winbase.inc
include process.inc
endif

.code

_cwait proc uses rbx stat_loc:ptr int_t, process_id:intptr_t, action_code:int_t

ifndef __UNIX__

   .new retval:intptr_t
   .new retstatus:int_t

    DBG_UNREFERENCED_PARAMETER(action_code)

    ; Explicitly check for process_id being -1 or -2. In Windows NT,
    ; -1 is a handle on the current process, -2 is a handle on the
    ; current thread, and it is perfectly legal to to wait (forever)
    ; on either

    ldr rbx,process_id
    .if ( rbx == -1 || rbx == -2 )

        .return( _set_errno(ECHILD) )
    .endif

    ; wait for child process, then fetch its exit code

    .ifd ( WaitForSingleObject(rbx, -1) == 0 )

        GetExitCodeProcess(rbx, &retstatus)
    .else
        xor eax,eax
    .endif

    .if ( eax )

        mov retval,rbx

    .else

        ; one of the API calls failed. map the error and set up to
        ; return failure. note the invalid handle error is mapped in-
        ; line to ECHILD

        mov ecx,GetLastError()
        .if ( ecx == ERROR_INVALID_HANDLE )

            mov _doserrno,ecx
            _set_errno(ECHILD)
        .else
            _dosmaperr(eax)
        .endif
        mov retval,-1
        mov retstatus,-1
    .endif

    CloseHandle(rbx)
    mov rcx,stat_loc
    .if ( rcx != NULL )

        mov eax,retstatus
        mov [rcx],eax
    .endif
    mov rax,retval
else
    _set_errno( ENOSYS )
endif
    ret

_cwait endp

    end
