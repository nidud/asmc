; SETFILEPOINTEREX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winbase.inc
include sys/syscall.inc

.code

 SetFilePointerEx proc WINAPI uses rsi rbx hFile:HANDLE, liDistanceToMove:LARGE_INTEGER,
        lpNewFilePointer:PLARGE_INTEGER, dwMoveMethod:DWORD
ifndef _WINN64
   .new pos:LARGE_INTEGER
endif
    ldr rcx,hFile
    ldr eax,dwMoveMethod
    ldr rbx,lpNewFilePointer
    .ifs ( ecx < 0 )
        .return( SetLastError( ERROR_INVALID_HANDLE ) )
    .endif
    .if ( eax > FILE_END )
        .return( SetLastError( ERROR_INVALID_PARAMETER ) )
    .endif
  ifdef _WIN64
    ldr rsi,liDistanceToMove
    .ifd ( sys_lseek(ecx, rsi, eax) > -4096 )
        .return( _sys_maperr( eax ) )
    .endif
    .if ( rbx )
        mov [rbx],rax
    .endif
  else
    lea esi,pos
    .ifs ( sys_llseek(ecx, dword ptr liDistanceToMove[4], dword ptr liDistanceToMove[0], esi, eax) < 0 )
        .return( _sys_maperr( eax ) )
    .endif
    .if ( ebx )
        mov eax,dword ptr pos[0]
        mov edx,dword ptr pos[4]
        mov [ebx],eax
        mov [ebx+4],edx
    .endif
  endif
    .return( 1 )
    endp

    end
