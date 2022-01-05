; GETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include winbase.inc
include malloc.inc

    .code

getfattr proc uses rsi rdi lpFilename:LPSTR

    mov rdi,rcx
    .ifd GetFileAttributesA(rcx) == -1

        mov rdi,__allocwpath(rdi)
        xor esi,esi
        dec rsi
        .if rdi
            mov rsi,GetFileAttributesW(rdi)
            free(rdi)
        .endif
        .if ( esi == -1 )
            osmaperr()
        .endif
        mov rax,rsi
    .endif
    ret

getfattr endp

    END

