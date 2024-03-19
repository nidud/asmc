; _TDOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include malloc.inc
include string.inc
include tchar.inc

    .code

    assume rbx:PDIRENT

_dopen proc uses rbx d:PDIRENT, path:LPTSTR, mask:LPTSTR, flags:UINT

    ldr rbx,d

    .if ( rbx == NULL )

        mov rbx,malloc(DIRENT+DMAXPATH*TCHAR)
        .if ( rax == NULL )
            .return
        .endif
        add rax,DIRENT
        mov [rbx].path,rax
        or flags,_D_MALLOC
    .else
        mov [rbx].path,malloc(DMAXPATH*TCHAR)
        .if ( rax == NULL )
            .return
        .endif
    .endif
    xor ecx,ecx
    mov [rax],ecx
    mov [rbx].flags,flags
    mov [rbx].mask,mask
    mov [rbx].count,ecx
    mov [rbx].fcb,rcx
    mov rdx,path
    .if ( rdx )
        _tcscpy([rbx].path, rdx)
    .else
        _tgetcwd([rbx].path, DMAXPATH)
    .endif
    mov rax,rbx
    ret

_dopen endp

    end
