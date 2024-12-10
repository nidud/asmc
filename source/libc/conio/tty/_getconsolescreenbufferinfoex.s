; _GETCONSOLESCREENBUFFERINFOEX.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include consoleapi.inc

    .code

    assume rbx:PCONSOLE_SCREEN_BUFFER_INFOEX

_getconsolescreenbufferinfoex proc WINAPI uses rsi rdi rbx fh:HANDLE, pc:PCONSOLE_SCREEN_BUFFER_INFOEX

    ldr rbx,pc
    ldr rcx,fh

    _getconsolescreenbufferinfo( rcx, &[rbx].dwSize )
    mov [rbx].wPopupAttributes,0
    mov [rbx].bFullscreenSupported,1
    lea rdi,[rbx].ColorTable
    lea rsi,_rgbcolortable
    mov ecx,16
    rep movsd
    mov eax,1
    ret

_getconsolescreenbufferinfoex endp

    end
