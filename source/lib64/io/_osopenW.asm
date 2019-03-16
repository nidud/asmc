; _OSOPENW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include conio.inc

    .code

_osopenW PROC USES rsi rdi rbx lpFileName:LPWSTR, dwAccess:DWORD, dwShareMode:DWORD,
    lpSecurity:PVOID, dwCreation:DWORD, dwAttributes:DWORD

  local NameW[2048]:SBYTE

    .repeat
        xor eax,eax
        lea rsi,_osfile
        .while BYTE PTR [rsi+rax] & FH_OPEN
            inc eax
            .if eax == _nfile
                xor eax,eax
                mov _doserrno,eax ; no OS error
                mov errno,EBADF
                dec rax
                .break
            .endif
        .endw
        mov rbx,rax
        CreateFileW( lpFileName, dwAccess, dwShareMode, lpSecurity, dwCreation, dwAttributes, 0 )
        mov rdx,rax
        inc rax
        .ifz
            osmaperr()
        .else
            mov rax,rbx
            lea rsi,_osfile
            or  BYTE PTR [rsi+rax],FH_OPEN
            lea rsi,_osfhnd
            mov [rsi+rax*8],rdx
        .endif
    .until 1
    ret
_osopenW endp

    end
