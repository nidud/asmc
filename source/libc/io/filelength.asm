; FILELENGTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; 2024-07-31 - return -1L
;
; long _filelength(int fd);
;
include io.inc
include errno.inc
include winbase.inc

    .code

_filelength proc fd:int_t
  local FileSize:QWORD
    mov rcx,_get_osfhandle(ldr(fd))
    .ifd GetFileSizeEx( rcx, &FileSize )
ifdef _WIN64
        mov rax,FileSize
else
        mov edx,dword ptr FileSize[4]
        mov eax,dword ptr FileSize
endif
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret
    endp

    end
