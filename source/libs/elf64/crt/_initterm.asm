; _INITTERM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

MAXENTRIES equ 256

    .code

_initterm proc uses rbx r12 pfbegin:ptr, pfend:ptr

  local entries[MAXENTRIES]:uint64_t

    mov rax,rdx
    sub rax,rcx

    ;; walk the table of function pointers from the bottom up, until
    ;; the end is encountered.  Do not skip the first entry.  The initial
    ;; value of pfbegin points to the first valid entry.  Do not try to
    ;; execute what pfend points to.  Only entries before pfend are valid.

    .ifnz

        .for ( rsi = rcx,
               rdi = &entries,
               edx = 0,
               rcx += rax : rsi < rcx && edx < MAXENTRIES : )
            lodsq
            .if eax
                stosq
                inc edx
            .endif
        .endf

        .for ( r12 = &entries, ebx = edx :: )

            .for ( eax = 0,
                   ecx = MAXENTRIES,
                   rsi = r12,
                   edx = 0,
                   edi = ebx : edi : edi--, rsi+=8 )

                .if ( eax != [rsi] && ecx >= [rsi+4] )

                    mov ecx,[rsi+4]
                    mov rdx,rsi
                .endif
            .endf
            .break .if !rdx

            mov  ecx,[rdx]
            mov  [rdx],eax
            call rcx
        .endf
    .endif
    ret

_initterm endp

    end
