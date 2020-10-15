; GETFILESIZEEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc
include winbase.inc

if (WINVER LT 0x0502)

    .data
    externdef kernel32_dll:BYTE
    GetFileSizeEx GetFileSizeEx_T dummy

    .code

dummy proc WINAPI private hFile:HANDLE, lpFileSize:PLARGE_INTEGER

    .if GetFileSize( hFile, lpFileSize )

        mov edx,lpFileSize
        mov [edx],eax
        xor eax,eax
        mov [edx+4],eax
        inc eax
    .endif
    ret

dummy endp


Install:
    .if GetModuleHandle( addr kernel32_dll )

        .if GetProcAddress( eax, "GetFileSizeEx" )

            mov GetFileSizeEx,eax
        .endif
    .endif
    ret

.pragma init(Install, 7)

endif
    END
