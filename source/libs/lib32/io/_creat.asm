; _CREAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include sys/stat.inc
include errno.inc
include winbase.inc

    .code

_creat proc path:LPSTR, flag

    mov edx,_A_NORMAL
    mov ecx,O_WRONLY
    mov eax,flag
    and eax,_S_IREAD or _S_IWRITE
    .repeat
        .if eax != _S_IWRITE
        mov ecx,O_RDWR
        .if eax != _S_IREAD or _S_IWRITE
            .if eax == _S_IREAD
            mov ecx,O_RDONLY
            mov edx,_A_RDONLY
            .else
            mov errno,EINVAL
            xor eax,eax
            mov _doserrno,eax
            dec eax
            .break
            .endif
        .endif
        .endif
        xor eax,eax
        .if ecx == O_RDONLY
        mov eax,FILE_SHARE_READ
        .endif
        _osopenA( path, ecx, eax, 0, A_CREATETRUNC, edx )
    .until 1
    ret

_creat endp

    END
