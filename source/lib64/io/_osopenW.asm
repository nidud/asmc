; _OSOPENW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include conio.inc

    .code

_osopenW proc frame lpFileName:LPWSTR, dwAccess:DWORD, dwShareMode:DWORD,
        lpSecurity:ptr, dwCreation:DWORD, dwAttributes:DWORD

  local NameW[1024]:wchar_t
  local handle:int_t

    xor eax,eax
    lea r10,_osfile

    .while byte ptr [r10+rax] & FH_OPEN

        inc eax
        .if eax == _nfile

            mov _doserrno,0 ; no OS error
            mov errno,EBADF
            .return -1
        .endif
    .endw

    mov handle,eax
    .if CreateFileW(rcx, edx, r8d, r9, dwCreation, dwAttributes, 0) == INVALID_HANDLE_VALUE

        .return _dosmaperr(GetLastError())
    .endif

    mov rdx,rax
    mov eax,handle
    lea rcx,_osfile
    or  byte ptr [rcx+rax],FH_OPEN
    lea rcx,_osfhnd
    mov [rcx+rax*8],rdx
    ret

_osopenW endp

    end
