; _TSTRTRUNC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Skip space from start and trunckate end
; Return RCX start and EAX char count
;
include string.inc
include ctype.inc
include tchar.inc

.code

_tstrtrunc proc uses rbx string:LPTSTR

    ldr rbx,string

    movzx ecx,TCHAR ptr [rbx]
    .whiled _istspace(ecx)

        add rbx,TCHAR
        movzx ecx,TCHAR ptr [rbx]
    .endw

    mov rdx,rbx
    xor eax,eax
    .while ( [rbx] != _tal )
        add rbx,TCHAR
    .endw

    .while ( rbx > rdx )

        movzx ecx,TCHAR ptr [rbx-TCHAR]
        .ifd !_istspace(ecx)

            .break
        .endif
        sub rbx,TCHAR
        mov TCHAR ptr [rbx],0
    .endw
    mov rax,rbx
    mov rcx,rdx
    sub rax,rdx
    ret

_tstrtrunc endp

    end
