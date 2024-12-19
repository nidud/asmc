; INFLATE.ASM--
;
;  inflate.c -- by Mark Adler
;  explode.c -- by Mark Adler
;
; Change history:
; 2012-09-08 - Modified for DZ32
; 03/31/2010 - Removed 386 instructions
; ../../1997 - Modified for Doszip

include malloc.inc
include string.inc
include errno.inc
include deflate.inc

ifdef _WIN64
define __ccall <fastcall>   ; Use fastcall for -elf64
ifdef __UNIX__
define _LIN64
endif
elseifdef __UNIX__
define __ccall <syscall>
else
define __ccall <c>
endif

define BMAX  16         ; Maximum bit length of any code (16 for explode)
define N_MAX 288        ; Maximum number of codes in any set
define OSIZE 0x8000

.pragma pack(push, size_t)
;
; Huffman code lookup table entry--this entry is four bytes for machines
;   that have 16-bit pointers (e.g. PC's in the small or medium model).
;   Valid extra bits are 0..13.  e == 15 is EOB (end of block), e == 16
;   means that v is a literal, 16 < e < 32 means that v is a pointer to
;   the next table, which codes e - 16 bits, and lastly e == 99 indicates
;   an unused code.  If a code with e == 99 is looked up, this implies an
;   error in the data.
;
HUFT        struct
e           db ?        ; number of extra bits or operation
b           db ?        ; number of bits in this code or subcode
union
 n          dw ?        ; literal, length base, or distance base
 t          PVOID ?     ; pointer to next level of table
ends
HUFT        ends
PHUFT       typedef ptr HUFT

.pragma pack(pop)

    .data

; Tables for deflate from PKZIP's appnote.txt

border dd \
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15

cplens dw \
     3, 4, 5, 6, 7, 8, 9,10, 11, 13, 15, 17, 19, 23, 27, 31,
     35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0

cplext dw \ ; Extra bits for literal codes 257..285
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 99, 99 ; 99==invalid

cpdist dw \ ; Copy offsets for distance codes 0..29
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
    257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
    8193, 12289, 16385, 24577

cpdext dw \ ; Extra bits for distance codes
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
    7, 7, 8, 8, 9, 9, 10, 10, 11, 11,
    12, 12, 13, 13

align 4
ifdef __DEBUG__
hufts dd 0 ; track memory usage
endif

fixed_bd dd 0
fixed_bl dd 0
fixed_td PHUFT 0
fixed_tl PHUFT 0

define lbits 9
define dbits 6

align size_t

STDO    LPFILE 0
STDI    LPFILE 0
fsize   uint_t 0

    .code

    option proc:private, dotname

ifdef _LIN64
needbits proc __ccall uses rsi rdi count:int_t
else
needbits proc __ccall count:int_t
endif
    ldr edx,count

    .if ( _fneedb(STDI, edx) == -1 )
        xor eax,eax
    .endif
    ret

needbits endp

dumpbits proto fastcall :dword {
    mov rdx,STDI
    sub [rdx].FILE._bitcnt,ecx   ; dec bit count
    shr [rdx].FILE._charbuf,cl   ; dump used bits
    }

ifdef _LIN64
getbits proc __ccall uses rsi rdi count:int_t
else
getbits proc __ccall count:int_t
endif
    ldr edx,count

    .ifd ( _fgetb(STDI, ecx) == -1 )
        xor eax,eax
    .endif
    ret

getbits endp

ifdef _LIN64
oputc proc __ccall uses rsi rdi c:int_t
else
oputc proc __ccall c:int_t
endif
    ldr ecx,c

    inc fsize
    .ifd ( fputc(ecx, STDO) == -1 )

        .return( ER_DISK )
    .endif
    xor eax,eax
    ret

oputc endp

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

ifdef __DEBUG__
                mov ecx,z
                inc ecx
                add hufts,ecx ; track memory usage
endif
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


;************** Decompress the codes in a compressed block

inflate_codes proc __ccall uses rsi rdi rbx tl:PHUFT, td:PHUFT, l:SINT, d:SINT

    .while 1 ; do until end of block

        mov rbx,tl
        needbits(l)

        imul  eax,eax,HUFT
        add   rbx,rax
        movzx esi,[rbx].HUFT.e

        .if ( esi > 16 )

            .repeat

                .if ( esi == 99 )

                   .return( 1 )
                .endif

                dumpbits([rbx].HUFT.b)
                sub esi,16
                needbits(esi)

                mov   rbx,[rbx].HUFT.t
                imul  eax,eax,HUFT
                add   rbx,rax
                movzx esi,[rbx].HUFT.e
            .until esi <= 16
        .endif

        dumpbits([rbx].HUFT.b)

        .if ( esi == 16 ) ; then it's a literal

            movzx ecx,[rbx].HUFT.n
            .ifd oputc(ecx)
                .return
            .endif

        .else ; it's an EOB or a length

            .if ( esi == 15 ) ; exit if end of block

                .return( 0 )
            .endif

            ; get length of block to copy

            movzx edi,[rbx].HUFT.n
            add edi,getbits(esi)

            ; decode distance of block to copy

            needbits(d)

            mov   rbx,td
            imul  eax,eax,HUFT
            add   rbx,rax
            movzx esi,[rbx].HUFT.e

            .if ( esi > 16 )

                .repeat

                    .if ( esi == 99 )

                       .return( 1 )
                    .endif

                    dumpbits([rbx].HUFT.b)
                    sub esi,16
                    needbits(esi)

                    mov   rbx,[rbx].HUFT.t
                    imul  eax,eax,HUFT
                    add   rbx,rax
                    movzx esi,[rbx].HUFT.e
                .until esi <= 16
            .endif
            dumpbits([rbx].HUFT.b)

            movzx ebx,[rbx].HUFT.n
            mov edx,getbits(esi)

            mov rcx,STDO
            mov rax,[rcx].FILE._ptr
            sub rax,[rcx].FILE._base
            sub eax,ebx
            sub eax,edx
            mov ebx,eax

            .repeat

                mov rsi,STDO
                mov rdx,[rsi].FILE._ptr
                sub rdx,[rsi].FILE._base
                and ebx,OSIZE-1
                mov ecx,OSIZE
                mov eax,ebx
                .if ( eax <= edx )
                    mov eax,edx
                .endif
                sub ecx,eax
                .if ( ecx > edi )
                    mov ecx,edi
                .endif

                sub edi,ecx
                mov eax,edx
                add [rsi].FILE._ptr,rcx
                mov edx,[rsi].FILE._bufsiz
                sub edx,eax
                sub edx,ecx
                mov [rsi].FILE._cnt,edx
                mov edx,edi
                mov rsi,[rsi].FILE._base
                lea rdi,[rsi+rax]
                add rsi,rbx
                add ebx,ecx
                add eax,ecx
                add fsize,ecx
                rep movsb
                mov edi,edx

                .if ( eax >= OSIZE )
ifdef _LIN64
                    .new count:uint_t = edi
endif
                    fflush( STDO )
ifdef _LIN64
                    mov edi,count
endif
                    .if ( eax )
                        .return( ER_DISK )
                    .endif
                .endif
            .until !edi
        .endif
    .endw
    ret

inflate_codes endp

;************** Decompress an inflated type 1 (fixed Huffman codes) block

inflate_fixed proc uses rdi rbx

  local ll[288]:DWORD   ; length list for huft_build

    lea rdi,ll
    xor eax,eax
    .if ( rax == fixed_tl )

        mov rbx,rdi
        mov ecx,144         ; literal table
        mov eax,8
        rep stosd
        mov ecx,112
        mov eax,9
        rep stosd
        mov ecx,24
        mov eax,7
        rep stosd           ; make a complete, but wrong code set
        mov ecx,8
        mov eax,8
        rep stosd

        mov rdi,rbx
        mov fixed_bl,7
        .ifd huft_build( rdi, 288, 257, &cplens, &cplext, &fixed_tl, &fixed_bl )

            mov fixed_tl,NULL
           .return
        .endif

        mov rdx,rdi         ; make an incomplete code set
        mov ecx,30
        mov eax,5
        rep stosd
        mov fixed_bd,5
        mov rdi,rdx
        .ifd huft_build( rdi, 30, 0, &cpdist, &cpdext, &fixed_td, &fixed_bd )

            .if ( eax != 1 )

                mov ebx,eax
                huft_free( fixed_tl )
                mov fixed_tl,NULL
                mov eax,ebx
               .return
            .endif
        .endif
    .endif
    ;
    ; decompress until an end-of-block code
    ;
    .ifd inflate_codes( fixed_tl, fixed_td, fixed_bl, fixed_bd )

        mov eax,1
    .endif
    ret

inflate_fixed endp

;************** Decompress an inflated type 2 (dynamic Huffman codes) block

inflate_dynamic proc uses rsi rdi rbx

  local nd:dword,       ; number of distance codes
        nl:dword,       ; number of literal/length codes
        nb:dword,       ; number of bit length codes
        tl:PHUFT,       ; literal/length code table
        td:PHUFT,       ; distance code table
        l:dword,        ; lookup bits for tl (bl)
        d:dword,        ; lookup bits for td (bd)
        n:dword,        ; number of lengths to get
        ll[320]:DWORD   ; literal/length and distance code lengths

    getbits(5)
    add eax,257
    mov nl,eax          ; number of literal/length codes
    getbits(5)
    inc eax
    mov nd,eax          ; number of distance codes
    getbits(4)
    add eax,4
    mov nb,eax          ; number of bit length codes

    .if ( nl > 288 || nd > 32 )    ; PKZIP_BUG_WORKAROUND
        .return( 1 )
    .endif

    lea rbx,border
    .for ( esi = 0 : esi < nb : esi++ )

        getbits(3)
        mov edx,[rbx+rsi*4]
        mov ll[rdx*4],eax
    .endf

    .for ( : esi < 19 : esi++ )

        mov eax,[rbx+rsi*4]
        mov ll[rax*4],0
    .endf

    ; build decoding table for trees--single level, 7 bit lookup

    mov l,7
    .ifd huft_build( &ll, 19, 19, NULL, NULL, &tl, &l )

        mov esi,eax
        .if ( eax == 1 )
            huft_free(tl)
        .endif
        .return( esi ) ; incomplete code set
    .endif

    mov eax,nl
    add eax,nd
    mov n,eax

    .for ( edi = 0, esi = 0 : esi < n : )

        needbits(l)

        mov     rbx,tl
        imul    eax,eax,HUFT
        add     rbx,rax
        mov     td,rbx

        dumpbits([rbx].HUFT.b)
        movzx eax,[rbx].HUFT.n
        .if ( eax < 16 )

            mov edi,eax
            mov ll[rsi*4],eax
            inc esi
            xor edx,edx

        .elseif ( eax == 16 )

            getbits(2)
            add eax,3
            mov edx,eax
            add eax,esi
            .if ( eax > n )
                .return( 1 )
            .endif

        .else

            .if ( eax == 17 )

                getbits(3)
                add eax,3
            .else
                getbits(7)
                add eax,11
            .endif
            mov edx,eax
            add eax,esi
            .if ( eax > n )
                .return( 1 )
            .endif
            xor edi,edi
        .endif

        .if edx
            .repeat
                mov ll[rsi*4],edi
                inc esi
                dec edx
            .untilz
        .endif
    .endf

    ; free decoding table for trees

    huft_free( tl )


    mov l,lbits
    huft_build( &ll, nl, 257, &cplens, &cplext, &tl, &l )

    .if ( l == 0 || eax == 1 )

        huft_free( tl )
       .return( 1 )
    .endif
    .if ( eax )
        .return
    .endif

    mov d,dbits
    mov eax,nl
    lea rcx,ll[rax*4]
    huft_build( rcx, nd, 0, &cpdist, &cpdext, &td, &d )

    .if ( l == 0 && nl <= 257 )

        huft_free( tl )
       .return( 1 )
    .endif
    .if ( eax == 1 )
        xor eax,eax
    .endif
    .if ( eax )

        mov ebx,eax
        huft_free( tl )
       .return( ebx )
    .endif

    mov ebx,inflate_codes( tl, td, l, d )
    huft_free( td )
    huft_free( tl )

    mov eax,ebx
    .if ( eax )
        mov eax,1
    .endif
    ret

inflate_dynamic endp


;****** Decompress an inflated type 0 (stored) block.

inflate_stored proc uses rbx

    mov rcx,STDI        ; go to byte boundary
    and [rcx].FILE._bitcnt,7
    getbits([rcx].FILE._bitcnt)

    mov ebx,getbits(16) ; number of bytes in block
    getbits(16)
    not ax
    .if ( eax != ebx )

        .return( 1 )
    .endif
    .if ( eax == 0 )

        .return
    .endif
    .for ( : ebx : ebx-- ) ; read and output the compressed data

        .ifd oputc(getbits(8))
            .return
        .endif
    .endf
    .return( 0 )

inflate_stored endp


inflate proc public uses rbx file:string_t, fp:ptr FILE, zp:ptr ZipLocal

    mov STDI,ldr(fp)
    .if ( fopen(file, "wz") == NULL )

        dec rax
       .return
    .endif
    mov STDO,rax
    mov fsize,0

    .repeat

        mov ebx,getbits(1)
        .switch getbits(2)
        .case 0
            inflate_stored()
           .endc
        .case 1
            inflate_fixed()
           .endc
        .case 2
            inflate_dynamic()
           .endc
        .default
            mov eax,ER_ZIP
        .endsw

        xchg ebx,eax
        .if ( ebx == 0 )

            .continue( 0 ) .if !eax
            .ifd fflush(STDO)
                mov ebx,ER_DISK
            .endif
        .endif
        xor eax,eax
        .if ( rax != fixed_tl )

            huft_free( fixed_td )
            huft_free( fixed_tl )
            xor eax,eax
            mov fixed_td,rax
            mov fixed_tl,rax
        .endif
    .until 1

    mov rcx,zp
    .if ( rcx )

        mov rax,STDO
        mov eax,[rax].FILE._crc32
        not eax
        .if ( eax != [rcx].ZipLocal.crc )
            mov ebx,ER_CRCERR
        .elseif ( fsize != [rcx].ZipLocal.fsize )
            mov ebx,ER_ZIP
        .endif
    .endif
    fclose(STDO)
    mov eax,ebx
    ret

inflate endp

    end
