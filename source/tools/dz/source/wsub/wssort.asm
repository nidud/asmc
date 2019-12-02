include string.inc
include io.inc
include stdlib.inc
include wsub.inc
include crtl.inc

    .data
    flag dd ?

    .code

compare PROC PRIVATE a, b

    mov eax,b
    mov eax,[eax]
    mov b,eax
    mov edx,[eax].S_FBLK.fb_flag
    mov eax,a
    mov eax,[eax]
    mov a,eax
    mov ecx,[eax].S_FBLK.fb_flag

    mov eax,dword ptr [eax].S_FBLK.fb_name
    and eax,0x00FFFFFF

    cmp eax,'..'
    je  below
    mov eax,ecx
    and edx,_A_SUBDIR
    and eax,_A_SUBDIR
    mov ecx,flag
    jz  l1
    test edx,edx
    jz  l1
    test ecx,_W_SORTSUB
    jnz l2
    mov ecx,_W_SORTNAME
    jmp l3
l1:
    or  eax,edx
    jz  l2
    mov ecx,_W_SORTSUB
    jmp l3
l2:
    and ecx,_W_SORTSIZE
l3:
    mov eax,a
    mov edx,b
    cmp ecx,_W_SORTTYPE
    je  ftype
    cmp ecx,_W_SORTDATE
    je  fdate
    cmp ecx,_W_SORTSIZE
    je  fsize
    cmp ecx,_W_SORTSUB
    je  subdir
    jmp fname

ftype:

    add edx,S_FBLK.fb_name
    add eax,S_FBLK.fb_name

    xchg eax,edx
    push edx
    strext(eax)
    pop  edx
    xchg eax,edx
    push edx
    strext(eax)
    pop  edx
    test eax,eax
    jz  @F
    test edx,edx
    jz  above
    _stricmp( eax, edx )
    jz  ftequ
    jmp toend
@@:
    test    edx,edx
    jnz below
ftequ:
    mov eax,a
    mov edx,b
    jmp fname
fdate:
    mov ecx,[eax].S_FBLK.fb_time
    cmp ecx,[edx].S_FBLK.fb_time
    jb  above
    ja  below
    jmp fname
fsize:
    mov ecx,dword ptr [eax].S_FBLK.fb_size[4]
    cmp ecx,dword ptr [edx].S_FBLK.fb_size[4]
    jb  above
    ja  below
    mov ecx,dword ptr [eax].S_FBLK.fb_size
    cmp ecx,dword ptr [edx].S_FBLK.fb_size
    jb  above
    ja  below
    jmp fname
subdir:
    test [edx].S_FBLK.fb_flag,_A_SUBDIR
    jnz above
below:
    mov eax,-1
    jmp toend
above:
    mov eax,1
    jmp toend
fname:
    add edx,S_FBLK.fb_name
    add eax,S_FBLK.fb_name
    _stricmp( eax, edx )
toend:
    ret

compare ENDP

wssort PROC USES esi edi ebx wsub:PTR S_WSUB

    local n, p, q

    mov edx,wsub
    mov eax,[edx].S_WSUB.ws_flag
    mov flag,eax
    mov eax,[edx].S_WSUB.ws_count
    mov esi,[edx].S_WSUB.ws_fcb
    mov p,esi
    mov n,eax

    .if eax > 1

        dec eax
        lea edi,[esi+eax*4]
        mov q,0

        .while 1

            lea eax,[edi+4] ; middle from (hi - lo) / 2
            sub eax,esi
            shr eax,3
            lea ebx,[esi+eax*4]

            .ifs compare( esi, ebx ) > 0

                mov eax,[ebx]
                mov ecx,[esi]
                mov [ebx],ecx
                mov [esi],eax
            .endif

            .ifs compare( esi, edi ) > 0

                mov eax,[edi]
                mov ecx,[esi]
                mov [edi],ecx
                mov [esi],eax
            .endif

            .ifs compare( ebx, edi ) > 0

                mov eax,[edi]
                mov ecx,[ebx]
                mov [edi],ecx
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
                mov eax,[edx]
                mov [edx],ecx
                mov ecx,p
                mov [ecx],eax
                .if ebx == edx

                    mov ebx,ecx
                .endif
            .endw

            add n,4
            .while  1

                sub n,4
                .break .if n <= esi
                .break .if compare( ebx, n )
            .endw

            mov edx,p
            mov eax,n
            sub eax,esi
            mov ecx,edi
            sub ecx,edx

            .ifs eax < ecx

                mov ecx,n

                .if edx < edi

                    push    edx
                    push    edi
                    inc q
                .endif

                .if esi < ecx

                    mov edi,ecx
                    .continue
                .endif
            .else
                mov ecx,n

                .if esi < ecx

                    push    esi
                    push    ecx
                    inc q
                .endif

                .if edx < edi

                    mov esi,edx
                    .continue
                .endif
            .endif

            .break .if !q
            dec q
            pop edi
            pop esi
        .endw
    .endif
    ret

wssort ENDP

    END
