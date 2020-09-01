; QSORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include crtl.inc

    .code

qsort proc uses esi edi ebx p:PVOID, n:SIZE_T, w:SIZE_T, compare:LPQSORTCMD

  local stack_level

    mov eax,n
    .if eax > 1

        dec eax
        mul w
        mov esi,p
        lea edi,[esi+eax]
        mov stack_level,0

        .while 1

            mov ecx,w
            lea eax,[edi+ecx]   ; middle from (hi - lo) / 2
            sub eax,esi

            .if !ZERO?

                sub edx,edx
                div ecx
                shr eax,1
                mul ecx
            .endif

            lea ebx,[esi+eax]
            .ifs compare( esi, ebx ) > 0

                memxchg( esi, ebx, w )
            .endif
            .ifs compare( esi, edi ) > 0

                memxchg( esi, edi, w )
            .endif
            .ifs compare( ebx, edi ) > 0

                memxchg( ebx, edi, w )
            .endif

            mov p,esi
            mov n,edi

            .while 1

                mov eax,w
                add p,eax
                .if p < edi

                    .continue .ifs compare( p, ebx ) <= 0
                .endif

                .while 1

                    mov eax,w
                    sub n,eax

                    .break .if n <= ebx
                    .break .ifs compare( n, ebx ) <= 0
                .endw

                mov edx,n
                mov eax,p
                .break .if edx < eax

                memxchg( edx, eax, w )

                .if ebx == n

                    mov ebx,p
                .endif
            .endw

            mov eax,w
            add n,eax

            .while 1

                mov eax,w
                sub n,eax

                .break .if n <= esi
                .break .if compare( n, ebx )
            .endw

            mov edx,p
            mov eax,n
            sub eax,esi
            mov ecx,edi
            sub ecx,edx

            .ifs eax < ecx

                mov ecx,n
                .if edx < edi

                    push edx
                    push edi
                    inc  stack_level
                .endif

                .if esi < ecx

                    mov edi,ecx
                    .continue
                .endif
            .else
                mov ecx,n
                .if esi < ecx

                    push esi
                    push ecx
                    inc  stack_level
                .endif

                .if edx < edi

                    mov esi,edx
                    .continue
                .endif
            .endif

            .break .if !stack_level

            dec stack_level
            pop edi
            pop esi
        .endw
    .endif
    ret

qsort endp

    end
