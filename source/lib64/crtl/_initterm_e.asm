; _INITTERM_E.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include internal.inc

    .code

    option win64:rsp nosave

_initterm_e proc frame uses rsi rdi rbx pfbegin:ptr _PIFV, pfend:ptr _PIFV

    mov rsi,rcx
    mov rdi,rdx
    xor ebx,ebx

    ;;
    ;; walk the table of function pointers from the bottom up, until
    ;; the end is encountered.  Do not skip the first entry.  The initial
    ;; value of pfbegin points to the first valid entry.  Do not try to
    ;; execute what pfend points to.  Only entries before pfend are valid.
    ;;

    .while ( rsi < rdi && ebx == 0 )

        ;;
        ;; if current table entry is non-NULL, call thru it.
        ;;
        mov rax,[rsi]
        .if rax
            mov rbx,rax()
        .endif
        add rsi,8
    .endw

    mov eax,ebx
    ret

_initterm_e endp

    end
