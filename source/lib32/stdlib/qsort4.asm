include stdlib.inc

.code

qsort4 proc uses esi edi ebx p:PVOID, n:SIZE_T, compare:LPQSORTCMD

local stack_level

    mov eax,n
    .if eax > 1

        dec eax
        mov esi,p
        lea edi,[esi+eax*4]
        mov stack_level,0

        .while 1

            mov ecx,4
            lea eax,[edi+4]   ; middle from (hi - lo) / 2
            sub eax,esi
            shr eax,3
            lea ebx,[esi+eax*4]

            .ifs compare( esi, ebx ) > 0

                mov eax,[esi]
                mov edx,[ebx]
                mov [esi],edx
                mov [ebx],eax
            .endif
            .ifs compare( esi, edi ) > 0

                mov eax,[esi]
                mov edx,[edi]
                mov [esi],edx
                mov [edi],eax
            .endif
            .ifs compare( ebx, edi ) > 0

                mov eax,[edi]
                mov edx,[ebx]
                mov [edi],edx
                mov [ebx],eax
            .endif

            mov p,esi
            mov n,edi

            .while  1

                add p,4
                .if p < edi

                    .continue .ifs compare( p, ebx ) <= 0
                .endif

                .while  1

                    sub n,4

                    .break .if n <= ebx
                    .break .ifs compare( n, ebx ) <= 0
                .endw

                mov edx,n
                mov eax,p
                .break .if edx < eax

                mov ecx,[eax]
                push eax
                mov eax,[edx]
                mov [edx],ecx
                pop ecx
                mov [ecx],eax

                .if ebx == n

                    mov ebx,p
                .endif
            .endw

            add n,4

            .while  1

                sub n,4

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

qsort4 endp

    end
