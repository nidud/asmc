; HUFT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include deflate.inc

define BMAX  16         ; Maximum bit length of any code (16 for explode)
define N_MAX 288        ; Maximum number of codes in any set

.code

huft_build proc __ccall uses rsi rdi rbx \
        b:ptr dword,        ; code lengths in bits (all assumed <= BMAX)
        n:dword,            ; number of codes (assumed <= N_MAX)
        s:dword,            ; number of simple-valued codes (0..s-1)
        d:ptr word,         ; list of base values for non-simple codes
        e:ptr word,         ; list of extra bits for non-simple codes
        t:ptr HUFT,         ; result: starting table
        m:ptr sdword        ; maximum lookup bits, returns actual

  local a:dword,            ; counter for codes of length k
        c[BMAX+1]:dword,    ; bit length count table
        el:dword,           ; length of EOB code (value 256)
        f:dword,            ; i repeats in table every f entries
        g:sdword,           ; maximum code length
        h:sdword,           ; table level
        i:dword,            ; counter, current code
        j:dword,            ; counter
        k:sdword,           ; number of bits in current code
        lx[BMAX+1]:sdword,  ; memory for l[-1..BMAX-1]
        l:ptr sdword,       ; stack of bits per table
        p:ptr dword,        ; pointer into c[], b[], or v[]
        q:ptr HUFT,         ; points to current table
        r:HUFT,             ; table entry for structure assignment
        u[BMAX]:PHUFT,      ; table stack
        v[N_MAX]:dword,     ; values in order of bit length
        w:sdword,           ; bits before this table == (l * h)
        x[BMAX+1]:dword,    ; bit offsets, then code stack
        xp:ptr dword,       ; pointer into x
        y:sdword,           ; number of dummy codes added
        z:dword             ; number of entries in current table


    ; Generate counts for each bit length

    lea rdi,z
    mov rcx,rbp
    sub rcx,rdi
    shr ecx,2
    xor eax,eax
    rep stosd

    mov rdx,b
    mov eax,BMAX    ; set length of EOB code, if any
    .if ( n > 256 )
        mov eax,[rdx+256*4]
    .endif
    mov el,eax

    .for ( : ecx < n : ecx++ )

        mov eax,[rdx+rcx*4]
        inc c[rax*4] ; assume all entries <= BMAX
    .endf

    mov rdx,m
    .if ( c[0] == ecx ) ; null input--all zero length codes

        xor eax,eax
        mov [rdx],eax
        mov rcx,t
        mov [rcx],rax
       .return
    .endif

    ; Find minimum and maximum length, bound *m by those

    .for ( ecx = 1 : ecx < BMAX : ecx++ )
        .break .if c[rcx*4]
    .endf
    mov k,ecx ; minimum code length
    .if ( [rdx] < ecx )
        mov [rdx],ecx
    .endif
    .for ( ecx = BMAX : ecx : ecx-- )
        .break .if c[rcx*4]
    .endf
    mov g,ecx ; maximum code length
    .if ( [rdx] > ecx )
        mov [rdx],ecx
    .endif

    ; Adjust last length count to fill out codes, if needed

    .for ( edx = ecx, ebx = 1, ecx = k, ebx <<= cl : ecx < edx : ecx++, ebx <<= 1 )

        sub ebx,c[rcx*4]
        .ifs ( ebx < 0 )
            .return( 2 ) ; bad input: more codes than bits
        .endif
    .endf
    sub ebx,c[rdx*4]
    .ifs ( ebx < 0 )
        .return( 2 )
    .endif
    mov y,ebx
    add c[rdx*4],ebx

    ; Generate starting offsets into the value table for each length

    .for ( --edx, eax = 0, ecx = 1 : edx : edx--, ecx++ )

        add eax,c[rcx*4]
        mov x[rcx*4+4],eax
    .endf

    ; Make a table of values in order of bit lengths

    .for ( rsi = b, edx = 0 : edx < n : edx++ )

        lodsd
        .if eax
            mov ecx,x[rax*4]
            inc x[rax*4]
            mov v[rcx*4],edx
        .endif
    .endf

    ; Generate the Huffman codes and for each, make the table entries

    mov rsi,-1      ; no tables yet--level -1
    lea rax,v
    mov p,rax
    lea rdi,lx[4]

    ; go through the bit lengths (k already is bits in shortest code)

    .for ( : k <= g : k++ )

        mov eax,k
        mov a,c[rax*4]

        .while ( a )

            dec a

            ; here i is the Huffman code of length k bits for value *p

            ; make tables up to required level

            .for ( eax = w, eax+=[rdi+rsi*4] : k > eax : )

                mov w,eax ; add bits already decoded
                inc esi

                ; compute minimum size table less than or equal to *m bits

                mov rcx,m
                mov eax,g
                sub eax,w
                .if ( eax > [rcx] )
                    mov eax,[rcx]
                .endif
                mov z,eax ; upper limit

                mov ecx,k ; try a k-w bit table
                sub ecx,w
                mov ebx,1
                shl ebx,cl
                mov eax,a
                inc eax

                .if ( ebx > eax )

                    sub ebx,eax ; deduct codes from patterns left

                    ; try smaller tables up to z bits

                    .for ( edx = k, ++ecx : ecx < z : ecx++ )

                        inc edx
                        add ebx,ebx
                        .if ( ebx <= c[rdx*4] )
                            .break          ; enough codes to use up j bits
                        .endif
                        sub ebx,c[rdx*4]    ; else deduct codes from patterns
                    .endf
                .endif

                mov ebx,w
                mov edx,el
                lea eax,[rbx+rcx]
                .if ( eax > edx && ebx < edx )
                    sub edx,ebx
                    mov ecx,edx     ; make EOB code end at table
                .endif

                mov eax,1
                shl eax,cl
                mov z,eax           ; table entries for j-bit table
                mov [rdi+rsi*4],ecx ; set table size in stack
                mov j,ecx

                ; allocate and link in new table

                inc  eax
                imul eax,eax,HUFT
ifdef _LIN64
                push rsi
                push rdi
endif
                malloc(eax)
ifdef _LIN64
                pop rdi
                pop rsi
endif
                .if ( rax == NULL )

                    .if ( esi )
                        huft_free(u)
                    .endif
                    .return( ER_MEM ) ; not enough memory
                .endif

                mov rcx,t
                add rax,HUFT
                mov [rcx],rax ; link to list for huft_free()
                mov q,rax
                lea rdx,[rax-HUFT].HUFT.t
                xor ecx,ecx
                mov [rdx],rcx
                mov t,rdx
                mov u[rsi*PHUFT],rax ; table starts after link

                ; connect to last table, if there is one

                .if ( esi )

                    mov     edx,i               ; save pattern for backing up
                    mov     x[rsi*4],edx
                    mov     ecx,w               ; connect to last table
                    mov     ebx,1
                    shl     ebx,cl
                    dec     ebx
                    and     ebx,edx
                    mov     edx,[rdi+rsi*4-4]
                    sub     ecx,edx
                    shr     ebx,cl
                    imul    ebx,ebx,HUFT
                    add     rbx,u[rsi*PHUFT-PHUFT]
                    mov     [rbx].HUFT.t,rax    ; pointer to this table
                    mov     eax,j
                    add     eax,16
                    mov     [rbx].HUFT.e,al     ; bits in this table
                    mov     [rbx].HUFT.b,dl     ; bits to dump before this table
                .endif
                mov eax,w
                add eax,[rdi+rsi*4]
            .endf

            ; set up table entry in r

            mov eax,k
            sub eax,w
            mov r.b,al

            mov ecx,n
            lea rax,v[rcx*4]
            mov rbx,p
            mov edx,s

            .if ( rbx >= rax )

                mov r.e,99          ; out of values--invalid code

            .elseif ( [rbx] < edx )

                mov eax,[rbx]
                .if ( eax < 256 )   ; 256 is end-of-block code
                    mov r.e,16
                .else
                    mov r.e,15
                .endif
                mov r.n,ax          ; simple code is just the value
                add rbx,4           ;

            .else

                mov ecx,[rbx]       ; non-simple--look up in lists
                sub ecx,s
                mov rdx,e
                mov al,[rdx+rcx*2]
                mov r.e,al
                mov rdx,d
                mov ax,[rdx+rcx*2]
                mov r.n,ax
                add rbx,4
            .endif
            mov p,rbx

            ; fill code-like entries with r

            mov ecx,k
            sub ecx,w
            mov edx,1
            shl edx,cl
            mov ecx,w
            mov eax,i
            shr eax,cl

            .for ( ecx = eax : ecx < z : ecx += edx )

                imul ebx,ecx,HUFT
                add rbx,q
                mov al,r.e
                mov ah,r.b
                mov [rbx].HUFT.e,al
                mov [rbx].HUFT.b,ah
                mov rax,r.t
                mov [rbx].HUFT.t,rax
            .endf

            ; backwards increment the k-bit code i

            mov ecx,k
            dec ecx
            mov eax,1
            shl eax,cl
            mov edx,i

            .for ( ecx = eax : ecx & edx : ecx >>= 1 )

                xor edx,ecx
            .endf
            xor edx,ecx
            mov i,edx

            ; backup over finished tables

            mov ecx,w
            .while 1

                mov eax,1
                shl eax,cl
                dec eax
                and eax,edx

                .if ( eax == x[rsi*4] )
                    .break
                .endif
                dec esi
                sub ecx,[rdi+rsi*4]
            .endw
            mov w,ecx
        .endw
    .endf

    ; return actual size of base table

    mov rdx,m
    mov ecx,[rdi]
    mov [rdx],ecx

    ; Return true (1) if we were given an incomplete table

    xor eax,eax
    .if ( eax != y && g != 1 )
        inc eax
    .endif
    ret

huft_build endp

;
; Free the malloc'ed tables built by huft_build(), which makes a linked
; list of the tables it made, with the links in a dummy first entry of
; each table.
;

ifdef _LIN64
huft_free proc __ccall uses rsi rdi rbx huft:PHUFT
else
huft_free proc __ccall uses rbx huft:PHUFT
endif

    .for ( rbx = huft : rbx : )

        lea rcx,[rbx-HUFT]
        mov rbx,[rcx].HUFT.t
        free(rcx)
    .endf
    ret

huft_free endp

    end
