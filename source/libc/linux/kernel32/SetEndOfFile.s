; SETENDOFFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winbase.inc
include sys/syscall.inc

.code

 SetEndOfFile proc WINAPI uses rbx hFile:HANDLE
   .new pos:LARGE_INTEGER
    ldr rbx,hFile
    .ifd ( !SetFilePointerEx(rbx, 0, &pos, FILE_CURRENT) )
        .return( 0 )
    .endif
  ifdef _WIN64
    .ifsd ( sys_ftruncate(ebx, pos) < 0 )
        .return( _sys_maperr( eax ) )
    .endif
  else
    .ifs ( sys_ftruncate64(ebx, dword ptr pos, dword ptr pos[4]) < 0 )
        .return( _sys_maperr( eax ) )
    .endif
  endif
    .return( 1 )
    endp

    end
