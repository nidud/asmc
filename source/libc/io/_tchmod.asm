; _TCHMOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
ifdef _UNICODE
include sys/stat.inc
else
include winnls.inc
include malloc.inc
include string.inc
endif
endif
include tchar.inc

.code

ifdef __UNIX__

_tchmod proc path:tstring_t, mode:int_t

    .ifsd ( sys_chmod( ldr(path), ldr(mode) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif

else

_tchmod proc uses rsi rdi rbx path:tstring_t, mode:int_t

    ldr rbx,path

ifndef _UNICODE

    xor esi,esi

    .if ( rbx )

        .ifd !WideCharToMultiByte(CP_ACP, 0, rbx, -1, NULL, 0, NULL, NULL)

            dec rax
           .return
        .endif
        mov edi,eax
        mov rsi,malloc(&[rax*2+2])
        .ifd ( rax == NULL )

            dec rax
           .return
        .endif
        WideCharToMultiByte(CP_ACP, 0, rbx, edi, rsi, edi, NULL, NULL)
    .endif
    mov ebx,_wchmod(rsi, mode)
    free(rsi)
    mov eax,ebx

else

    .new attr_data:WIN32_FILE_ATTRIBUTE_DATA

    .if ( rbx == NULL)

        .return( _set_errno(EINVAL) )
    .endif
    .ifd !GetFileAttributesExW(rbx, GetFileExInfoStandard, &attr_data)

        .return( _dosmaperr(GetLastError()) )
    .endif
    and attr_data.dwFileAttributes,not FILE_ATTRIBUTE_READONLY
    .if !( mode & _S_IWRITE )
        or attr_data.dwFileAttributes,FILE_ATTRIBUTE_READONLY
    .endif
    .ifd !SetFileAttributesW(rbx, attr_data.dwFileAttributes)

        .return( _dosmaperr(GetLastError()) )
    .endif
    xor eax,eax
endif
endif
    ret

_tchmod endp

    end
