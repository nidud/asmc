; _INITTERM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

MAXENTRIES equ 256

    .code

_initterm proc uses esi edi ebx pfbegin:ptr, pfend:ptr

  local entries[MAXENTRIES]:uint64_t

    mov ecx,pfbegin
    mov eax,pfend
    sub eax,ecx

    ;; walk the table of function pointers from the bottom up, until
    ;; the end is encountered.  Do not skip the first entry.  The initial
    ;; value of pfbegin points to the first valid entry.  Do not try to
    ;; execute what pfend points to.  Only entries before pfend are valid.

    .ifnz

        .for ( esi = ecx,
               edi = &entries,
               edx = 0,
               ecx += eax : esi < ecx && edx < MAXENTRIES : esi+=8)

            mov eax,[esi]
            .if eax
                stosd
                mov eax,[esi+4]
                stosd
                inc edx
            .endif
        .endf

        .for ( esi = &entries, edi = edx :: )

            .for ( ecx = MAXENTRIES,
                   ebx = esi,
                   edx = 0,
                   eax = edi : eax : eax--, ebx+=8 )

                .if ( dword ptr [ebx] != 0 && ecx >= [ebx+4] )

                    mov ecx,[ebx+4]
                    mov edx,ebx
                .endif
            .endf

            .break .if !edx
            mov  ecx,[edx]
            mov  dword ptr [edx],0
            call ecx
        .endf
    .endif
    ret

_initterm endp

    end
