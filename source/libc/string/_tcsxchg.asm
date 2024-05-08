; _TCSXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

.code

_tcsxchg proc uses rbx dst:LPTSTR, old:LPTSTR, new:LPTSTR

   .new lnew:int_t
   .new lold:int_t
    ldr rbx,dst

    _tcslen(new)
ifdef _UNICODE
    add eax,eax
endif
    mov lnew,eax
    _tcslen(old)
ifdef _UNICODE
    add eax,eax
endif
    mov lold,eax

    .while _tcsistr(rbx, old)   ; find token

        mov rbx,rax             ; RBX to start of token
        mov ecx,lnew
        add rcx,rax
        mov edx,lold
        add rdx,rax
        _tcsmove(rcx, rdx)      ; move($ + len(new), $ + len(old))
        memmove(rbx, new, lnew) ; copy($, new, len(new))
        add rbx,TCHAR
    .endw                       ; $++
    mov rax,dst
    ret

_tcsxchg endp

    end

