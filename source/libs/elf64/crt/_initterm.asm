; _INITTERM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

externdef __ImageBase:size_t

MAXENTRIES equ 128

    .code

_initterm proc uses rbx r12 pfbegin:ptr, pfend:ptr

  local entries[MAXENTRIES*2]:uint64_t

    mov rax,pfend
    sub rax,pfbegin

    ;; walk the table of function pointers from the bottom up, until
    ;; the end is encountered.  Do not skip the first entry.  The initial
    ;; value of pfbegin points to the first valid entry.  Do not try to
    ;; execute what pfend points to.  Only entries before pfend are valid.

    .ifnz

        .for ( rsi = pfbegin,
               rdi = &entries,
               edx = 0,
               rcx = rsi,
               rcx += rax : rsi < rcx && edx < MAXENTRIES : )

            lodsq
            .if eax
                stosq
                mov rax,[rsi]
                stosq
                inc edx
            .endif
            add rsi,8
        .endf

        .for ( r12 = &entries, ebx = edx :: )

            .for ( eax = 0,
                   ecx = MAXENTRIES,
                   rsi = r12,
                   edx = 0,
                   edi = ebx : edi : edi--, rsi+=16 )

                .if ( rax != [rsi] && ecx >= [rsi+8] )

                    mov ecx,[rsi+8]
                    mov rdx,rsi
                .endif
            .endf
            .break .if !rdx

            mov  rcx,[rdx]
            mov  [rdx],rax
            add  rcx,__ImageBase
            call rcx
        .endf
    .endif
    ret

_initterm endp

    end
