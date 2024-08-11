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
ifndef __UNIX__
include winbase.inc
endif

    .code

_filelength proc fd:int_t

ifdef __UNIX__

   .new offs:size_t
   .new size:size_t

    .ifd ( _lseek(fd, 0, SEEK_CUR) != -1 )

        mov offs,rax
        mov size,_lseek(fd, 0, SEEK_END)
        _lseek(fd, offs, SEEK_SET)
        mov rax,size
    .endif

else

  local FileSize:QWORD

    ldr ecx,fd
    mov rcx,_osfhnd(ecx)

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
endif
    ret

_filelength endp

    end
