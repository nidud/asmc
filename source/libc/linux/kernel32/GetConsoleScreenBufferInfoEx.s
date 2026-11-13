; GETCONSOLESCREENBUFFERINFOEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

.code
 assume rbx:PCONSOLE_SCREEN_BUFFER_INFOEX
ifndef _WIN64
 assume uses esi edi
endif

 GetConsoleScreenBufferInfoEx proc WINAPI uses rbx fp:HANDLE, pc:PCONSOLE_SCREEN_BUFFER_INFOEX
    ldr rbx,pc
    GetConsoleScreenBufferInfo(fp, &[rbx].dwSize)
    mov [rbx].wPopupAttributes,0
    mov [rbx].bFullscreenSupported,1
    lea rdi,[rbx].ColorTable
    lea rsi,_rgbcolortable
    mov ecx,16
    rep movsd
    mov eax,1
    ret
    endp

    end
