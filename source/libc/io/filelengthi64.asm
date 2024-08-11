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
ifndef __UNIX__
include winbase.inc
endif

    .code

_filelengthi64 proc fd:int_t

   .new size:int64_t

ifdef __UNIX__

   .new offs:int64_t

    _lseeki64(fd, 0, SEEK_CUR)

ifdef _WIN64

    .ifd ( rax != -1 )

        mov offs,rax
        mov size,_lseeki64(fd, 0, SEEK_END)
        _lseeki64(fd, offs, SEEK_SET)
        mov rax,size
else

    .ifd ( eax != -1 && edx != -1 )

        mov dword ptr offs[0],eax
        mov dword ptr offs[4],edx
        _lseeki64(fd, 0, SEEK_END)
        mov dword ptr size[0],eax
        mov dword ptr size[4],edx
        _lseeki64(fd, offs, SEEK_SET)
        mov eax,dword ptr size[0]
        mov edx,dword ptr size[4]
endif
    .endif

else

    ldr ecx,fd
    mov rcx,_osfhnd(ecx)

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
endif
    ret

_filelengthi64 endp

    end
