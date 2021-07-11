; _OSOPENA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include conio.inc

        .code

_osopenA proc lpFileName:LPSTR, dwAccess:DWORD, dwShareMode:DWORD,
        lpSecurity:ptr, dwCreation:DWORD, dwAttributes:DWORD

  local handle:int_t
  local dosretval:ulong_t
  local NameW[2048]:char_t

    xor eax,eax
    lea r10,_osfile

    .while byte ptr [r10+rax] & FH_OPEN

        inc eax
        .if eax == _nfile

            _set_doserrno(0) ; no OS error
            _set_errno(EBADF)
            .return -1
        .endif
    .endw

    mov handle,eax
    .if CreateFileA(rcx, edx, r8d, r9, dwCreation, dwAttributes, 0) == INVALID_HANDLE_VALUE

        mov dosretval,GetLastError()
        _dosmaperr(eax)
        .return .if dosretval != ERROR_FILENAME_EXCED_RANGE

        lea rcx,NameW
        mov rdx,rcx
        mov r8,lpFileName
        mov dword ptr [rdx],'\'+('\' shl 16)
        mov dword ptr [rdx+4],'?'+('\' shl 16)
        add rdx,8
        .repeat
            mov al,[r8]
            mov [rdx],al
            add rdx,1
            add r8,1
        .until !al

        .if CreateFileW(rcx, dwAccess, dwShareMode, lpSecurity, dwCreation,
                dwAttributes, 0) == INVALID_HANDLE_VALUE


            .return _dosmaperr(GetLastError())
        .endif
    .endif

    mov rdx,rax
    mov eax,handle
    lea rcx,_osfile
    or  byte ptr [rcx+rax],FH_OPEN
    lea rcx,_osfhnd
    mov [rcx+rax*8],rdx
    ret

_osopenA endp

    end
