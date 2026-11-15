; SETPRIORITYCLASS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include processthreadsapi.inc

.code

 SetPriorityClass proc WINAPI hProcess:HANDLE, dwPriorityClass:DWORD
    mov eax,TRUE ; No-op success (or call setpriority(PRIO_PROCESS, 0, -20) if root)
    ret
    endp

    end
