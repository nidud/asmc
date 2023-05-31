; _FINDFIRST.ASM--
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

    .code

_findnext proc uses rsi rdi handle:intptr_t, ff:ptr _finddata_t
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov rax,-1
else
  local wf:WIN32_FIND_DATAA

    ldr rcx,handle
    ldr rdi,ff
    lea rsi,wf

    .if FindNextFileA( rcx, rsi )
        copyblock()
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_findnext endp


_findfirst proc uses rsi rdi rbx lpFileName:LPSTR, ff:PTR _finddata_t
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov rax,-1
else
  local FindFileData:WIN32_FIND_DATAA

    ldr rcx,lpFileName
    ldr rdi,ff
    lea rsi,FindFileData

    .ifd ( FindFirstFileA( rcx, rsi ) != -1 )

        mov rbx,rax
        copyblock()
        mov rax,rbx
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_findfirst endp

ifndef __UNIX__

    ASSUME  rsi:ptr WIN32_FIND_DATAA
    ASSUME  rdi:ptr _finddata_t

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
    mov rcx,260/4
    rep movsd
    xor eax,eax
    ret

copyblock endp
endif

    end
