; _WFINDFIRST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include time.inc
ifndef __UNIX__
include winbase.inc
endif
include tchar.inc

    .code

_tfindnext proc uses rsi rdi handle:intptr_t, ff:ptr _tfinddata_t
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov rax,-1
else
  local wf:WIN32_FIND_DATA

    ldr rcx,handle
    ldr rdi,ff
    lea rsi,wf

    .if FindNextFile( rcx, rsi )
        copyblock()
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_tfindnext endp


_tfindfirst proc uses rsi rdi rbx lpFileName:LPTSTR, ff:ptr _tfinddata_t
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov rax,-1
else
  local FindFileData:WIN32_FIND_DATA

    ldr rcx,lpFileName
    ldr rdi,ff
    lea rsi,FindFileData

    .ifd ( FindFirstFile( rcx, rsi ) != -1 )

        mov rbx,rax
        copyblock()
        mov rax,rbx
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_tfindfirst endp

ifndef __UNIX__

    ASSUME  rsi:ptr WIN32_FIND_DATA
    ASSUME  rdi:ptr _tfinddata_t

copyblock proc private

    mov eax,[rsi].dwFileAttributes
    mov [rdi].attrib,eax
    mov eax,[rsi].nFileSizeLow
    mov dword ptr [rdi].size,eax
    mov eax,[rsi].nFileSizeHigh
    mov dword ptr [rdi].size[4],eax

    FileTimeToTime( addr [rsi].ftCreationTime )
    mov [rdi].time_create,rax
    FileTimeToTime( addr [rsi].ftLastAccessTime )
    mov [rdi].time_access,rax
    FileTimeToTime( addr [rsi].ftLastWriteTime )
    mov [rdi].time_write,rax

    lea rsi,[rsi].cFileName
    lea rdi,[rdi].name
    mov rcx,(260/4)*TCHAR
    rep movsd
    xor eax,eax
    ret

copyblock endp
endif
    end
