; FILELENGTHI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; 2024-07-31 - return -1L
;
; __int64 _filelengthi64(int fd);
;
include io.inc
include errno.inc
include winbase.inc

.code

_filelengthi64 proc fd:int_t
   .new size:int64_t
    mov rcx,_get_osfhandle(ldr(fd))
    .ifd GetFileSizeEx( rcx, &size )
ifdef _WIN64
        mov rax,size
else
        mov edx,dword ptr size[4]
        mov eax,dword ptr size
endif
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret
    endp

    end
