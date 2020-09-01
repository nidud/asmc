; _INITTERM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

MAXENTRIES equ 256

    .code

    option win64:nosave

_initterm proc frame uses rsi rdi rbx pfbegin:ptr, pfend:ptr

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

        mov rbx,GetImageBase()

        .for ( rsi = &entries, edi = edx :: )

            .for ( eax = 0,
                   ecx = MAXENTRIES,
                   r10 = rsi,
                   edx = 0,
                   r8d = edi : r8d : r8d--, r10+=8 )

                .if ( eax != [r10] && ecx >= [r10+4] )

                    mov ecx,[r10+4]
                    mov rdx,r10
                .endif
            .endf
            .break .if !rdx

            mov  ecx,[rdx]
            mov  [rdx],eax
            add  rcx,rbx
            call rcx
        .endf
    .endif
    ret

_initterm endp

    end
