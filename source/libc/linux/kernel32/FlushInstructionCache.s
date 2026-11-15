; FLUSHINSTRUCTIONCACHE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include processthreadsapi.inc

.code

 FlushInstructionCache proc WINAPI hProcess:HANDLE, lpBaseAddress:LPCVOID, dwSize:SIZE_T
    mov eax,TRUE ; x86/x86_64 has coherent instruction caches
    ret
    endp

    end
