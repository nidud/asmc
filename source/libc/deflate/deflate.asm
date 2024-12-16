; DEFLATE.ASM--
;
;  This is from Info-ZIP's Zip 3.0:
;
;       trees.c    - by Jean-loup Gailly
;       match.asm  - by Jean-loup Gailly
;       deflate.c  - by Jean-loup Gailly
;
;       Copyright (c) 1990-2008 Info-ZIP. All rights reserved.
;
;  That is free (but copyrighted) software. The original sources and license
;  are available from Info-ZIP's home site at: http://www.info-zip.org/
;
; Change history:
; 2012-09-09 - created
;
;
include string.inc
include malloc.inc
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

define SEGM64K 0x10000

define MIN_MATCH 3   ; The minimum and maximum match lengths
define MAX_MATCH 258

; Maximum window size = 32K. If you are really short of memory, compile
; with a smaller WSIZE but this reduces the compression ratio for files
; of size > WSIZE. WSIZE must be a power of two in the current implementation.

define WSIZE 0x8000
define WMASK (WSIZE-1)

; Minimum amount of lookahead, except at the end of the input file.
; See deflate.c for comments about the MIN_MATCH+1.

define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)

; In order to simplify the code, particularly on 16 bit machines, match
; distances are limited to MAX_DIST instead of WSIZE.

define MAX_DIST (WSIZE-MIN_LOOKAHEAD)

define FILE_BINARY      0       ; internal file attribute
define FILE_ASCII       1
;define FILE_UNKNOWN     (-1)

define METHOD_STORE     0       ; Store method
define METHOD_DEFLATE   8       ; Deflation method
define METHOD_BEST      (-1)    ; Use best method (deflation or store)

define MEDIUM_MEM       1
define HASH_BITS        14      ; Number of bits used to hash strings
define LIT_BUFSIZE      0x4000

; HASH_SIZE and WSIZE must be powers of two

define HASH_SIZE (1 shl HASH_BITS)
define HASH_MASK HASH_SIZE-1
define H_SHIFT   (HASH_BITS+MIN_MATCH-1)/MIN_MATCH

define FAST 4 ; speed options for the general purpose bit flag
define SLOW 2

; Matches of length 3 are discarded if their distance exceeds TOO_FAR

define TOO_FAR         4096
define MAXSEG_64K      1

define MAX_BITS        15   ; All codes must not exceed MAX_BITS bits
define MAX_BL_BITS     7    ; Bit length codes must not exceed MAX_BL_BITS bits
define LENGTH_CODES    29   ; number of length codes, not counting the special
                            ; END_BLOCK code
define LITERALS        256  ; number of literal bytes 0..255
define END_BLOCK       256  ; end of block literal code
define D_CODES         30   ; number of distance codes
define BL_CODES        19   ; number of codes used to transfer the bit lengths

; number of Literal or Length codes, including the END_BLOCK code

define L_CODES         LITERALS+1+LENGTH_CODES

define STORED_BLOCK    0    ; The three kinds of block type
define STATIC_TREES    1
define DYN_TREES       2

define DIST_BUFSIZE    LIT_BUFSIZE

; repeat previous bit length 3-6 times (2 bits of repeat count)

define REP_3_6         16
define REPZ_3_10       17   ; repeat a zero length 3-10 times (3 bits)
define REPZ_11_138     18   ; repeat a zero length 11-138 times (7 bits)

define HEAP_SIZE       (2*L_CODES+1) ; maximum heap size

define SMALLEST        1    ; Index within the heap array of least
                            ; frequent node in the Huffman tree

; Data structure describing a single value and its code string.

ct_data         struct
union
 Freq           dw ?        ; frequency count
 Code           dw ?        ; bit string
ends
union
 Dad            dw ?        ; father node in Huffman tree
 Len            dw ?        ; length of bit string
ends
ct_data         ends
PCTDATA         typedef ptr ct_data
LPINT           typedef ptr SDWORD

tree_desc       struct
dyn_tree        PCTDATA ?   ; the dynamic tree
static_tree     PCTDATA ?   ; corresponding static tree or NULL
extra_bits      LPINT ?     ; extra bits for each code or NULL
extra_base      SINT ?      ; base index for extra_bits
elems           SINT ?      ; max number of elements in the tree
max_length      SINT ?      ; max bit length for the codes
max_code        SINT ?      ; largest code with non zero frequency
tree_desc       ends
PTREE           typedef ptr tree_desc

dconfig         STRUC
good_length     dd ?    ; reduce lazy search above this match length
max_lazy        dd ?    ; do not perform lazy search above this match length
nice_length     dd ?    ; quit search above this match length
max_chain       dd ?
dconfig         ENDS

DEFLATE         STRUC
fpi             LPFILE ?
fpo             LPFILE ?
head            LPSTR ?
prev            LPSTR ?
crc             UINT ?
csize           UINT ?
fsize           UINT ?
chain_length    UINT ?
str_start       UINT ?
prev_length     UINT ?
max_chain_len   UINT ?
good_match      UINT ?
match_start     UINT ?
nice_match      UINT ?
flags           BYTE ?
flag_bit        BYTE ?
block_start     UINT ?
ins_h           UINT ?
eofile          UINT ?
lookahead       UINT ?
max_lazy_match  UINT ?
heap_len        UINT ?
heap_max        UINT ?
last_lit        UINT ?
last_dist       UINT ?
last_flags      UINT ?
opt_len         UINT ?
static_len      UINT ?
cmpr_bytelen    UINT ?
cmpr_lenbits    UINT ?
bi_buf          UINT ?
bi_valid        UINT ?
compr_level     UINT ?
compr_flags     UINT ?
bl_count        UINT MAX_BITS+1 dup(?)
dyn_ltree       ct_data 2*L_CODES+1  dup(<>)   ; literal and length tree
dyn_dtree       ct_data 2*D_CODES+1  dup(<>)   ; distance tree
static_ltree    ct_data L_CODES+2    dup(<>)   ; the static literal tree
static_dtree    ct_data D_CODES      dup(<>)   ; the static distance tree
bl_tree         ct_data 2*BL_CODES+1 dup(<>)
heap            UINT HEAP_SIZE dup(?)     ; heap used to build the Huffman trees
depth           BYTE HEAP_SIZE dup(?)     ; Depth of each subtree
base_length     UINT LENGTH_CODES dup(?)  ; First normalized length for each code
length_code     BYTE MAX_MATCH-MIN_MATCH+1 dup(?)
d_code          BYTE 512 dup(?)
base_dist       UINT D_CODES dup(?)       ; First normalized distance for each code
l_buf           BYTE LIT_BUFSIZE dup(?)   ; buffer for literals/lengths
d_buf           UINT DIST_BUFSIZE dup(?)  ; buffer for distances
flag_buf        BYTE LIT_BUFSIZE/8 dup(?)
head_buf        WORD HASH_SIZE dup(?)
DEFLATE         ENDS
PDEFLATE        typedef ptr DEFLATE

.data

; good lazy nice chain

config_table dconfig \
    {    0,   0,   0,    0 }, ; 0 - store only
    {    4,   4,   8,    4 }, ; 1 - maximum speed, no lazy matches
    {    4,   5,  16,    8 }, ; 2
    {    4,   6,  32,   32 }, ; 3
    {    4,   4,  16,   16 }, ; 4 - lazy matches
    {    8,  16,  32,   32 }, ; 5
    {    8,  16, 128,  128 }, ; 6
    {    8,  32, 128,  256 }, ; 7
    {   32, 128, 258, 1024 }, ; 8
    {   32, 258, 258, 4096 }  ; 9 - maximum compression

compresslevel   int_t 9
bl_order        BYTE 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15
file_method     BYTE ?

align size_t
extra_lbits     UINT 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0
extra_dbits     UINT 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13
extra_blbits    UINT 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7
align size_t
l_desc          tree_desc <0,0,extra_lbits,LITERALS+1,L_CODES,MAX_BITS,0>
d_desc          tree_desc <0,0,extra_dbits,0,D_CODES,MAX_BITS,0>
bl_desc         tree_desc <0,0,extra_blbits,0,BL_CODES,MAX_BL_BITS,0>

    .code

    option proc:private, dotname

    assume rbx:PDEFLATE

ioread proc uses rsi rdi

    .ifd ( fgetc([rbx].fpi) == -1 )

        .return( 0 )
    .endif

    mov rcx,[rbx].fpi
    inc [rcx].FILE._cnt
    dec [rcx].FILE._ptr
    mov eax,[rcx].FILE._cnt
    lea rsi,crctable
    mov rdi,[rcx].FILE._base
    add [rbx].fsize,eax

    .for ( ecx = [rbx].crc, edx = 0 : eax : eax-- )

        mov dl,cl
        xor dl,[rdi]
        shr ecx,8
        xor ecx,[rsi+rdx*4]
        inc rdi
    .endf
    mov [rbx].crc,ecx
    mov rcx,[rbx].fpi
    mov eax,[rcx].FILE._cnt
    ret

ioread endp


ifdef _LIN64
oputc proc __ccall uses rsi rdi c:int_t
else
oputc proc __ccall c:int_t
endif
    ldr ecx,c

    inc [rbx].csize
    .ifd ( fputc( ecx, [rbx].fpo ) != -1 )
        .return( 1 )
    .endif
    xor eax,eax
    ret

oputc endp


putshort proc __ccall c:int_t

    .ifd ( oputc( c ) == 1 )

        mov ecx,c
        shr ecx,8
        oputc( ecx )
    .endif
    ret

putshort endp


    assume rsi:ptr tree_desc
    assume rdi:ptr ct_data

gen_bitlen proc __ccall uses rsi rdi desc:PTREE

   .new bits:int_t
   .new xbits:int_t
   .new h:int_t
   .new n:int_t
   .new f:int_t
   .new overflow:int_t = 0 ; number of elements with bit length too large

    ldr rsi,desc ; the tree descriptor

    lea rdi,[rbx].bl_count
    mov ecx,MAX_BITS+1
    xor eax,eax
    rep stosd

    ; In a first pass, compute the optimal bit lengths (which may
    ; overflow in the case of the bit length tree).

    mov eax,[rbx].heap_max
    mov eax,[rbx+rax*4].heap
    mov rdi,[rsi].dyn_tree
    mov [rdi+rax*4].Len,0 ; root of the heap

    mov ecx,[rbx].heap_max
    inc ecx
    mov h,ecx

    .for ( : h < HEAP_SIZE : h++ )

        mov ecx,h
        mov edx,[rbx+rcx*4].heap
        movzx eax,[rdi+rdx*4].Dad
        movzx eax,[rdi+rax*4].Len
        inc eax
        .if ( eax > [rsi].max_length )
            mov eax,[rsi].max_length
            inc overflow
        .endif
        mov bits,eax
        mov n,edx

        ; We overwrite tree[n].Dad which is no longer needed

        mov [rdi+rdx*4].Len,ax
        .if ( edx <= [rsi].max_code ) ; leaf node

            inc dword ptr [rbx+rax*4].bl_count
            xor ecx,ecx
            .if ( edx >= [rsi].extra_base )

                sub edx,[rsi].extra_base
                mov rcx,[rsi].extra_bits
                mov ecx,[rcx+rdx*4]
            .endif
            mov xbits,ecx
            mov edx,n
            movzx eax,[rdi+rdx*4].Freq
            mov f,eax
            add ecx,bits
            mul ecx
            add [rbx].opt_len,eax
            mov rcx,[rsi].static_tree

            .if ( rcx )

                mov   edx,n
                movzx eax,[rcx+rdx*4].ct_data.Len
                add   eax,xbits
                mul   f
                add   [rbx].static_len,eax
            .endif
        .endif
    .endf

    .if ( overflow == 0 )

        .return
    .endif

    assume rdi:nothing

    ; Find the first bit length which could increase:

    .repeat

        mov edx,[rsi].max_length
        dec edx
        lea rdi,[rbx].bl_count
        xor eax,eax
        .while ( eax == [rdi+rdx*4] )
            dec edx
        .endw

        dec dword ptr [rdi+rdx*4]   ; move one leaf down the tree
        mov eax,2
        add [rdi+rdx*4+4],eax       ; move one overflow item as its brother

        mov edx,[rsi].max_length
        dec dword ptr [rdi+rdx*4]

        ; The brother of the overflow item also moves one step up,
        ; but this does not affect bl_count[max_length]

        sub overflow,eax
    .until ( overflow < 1 )

    ; Now recompute all bit lengths, scanning in increasing frequency.
    ; h is still equal to HEAP_SIZE. (It is simpler to reconstruct all
    ; lengths instead of fixing only the wrong ones. This idea is taken
    ; from 'ar' written by Haruhiko Okumura.)


    .for ( bits = [rsi].max_length: bits: bits-- )

        mov eax,bits
        mov n,[rbx+rax*4].bl_count

        .while ( n )

            dec h
            mov eax,h
            mov edi,[rbx+rax*4].heap
            .if (edi > [rsi].max_code)
                .continue
            .endif

            mov rdx,[rsi].dyn_tree
            movzx eax,[rdx+rdi*4].ct_data.Len
            .if ( eax != bits )

                mov ecx,bits
                mov [rdx+rdi*4].ct_data.Len,cx
                sub ecx,eax
                movzx eax,[rdx+rdi*4].ct_data.Freq
                mul ecx
                add [rbx].opt_len,eax
            .endif
            dec n
        .endw
    .endf
    ret

gen_bitlen endp


    assume rsi:nothing

gen_codes proc __ccall uses rsi rdi tree:PCTDATA, max_code:int_t

   .new next_code[MAX_BITS+1]:UINT

    ldr rsi,tree ; the tree to decorate

    .for ( eax = 0, ecx = 0 : ecx < MAX_BITS: ecx++ )

        ; The distribution counts are first used to generate the code values
        ; without bit reversal.

        add eax,[rbx+rcx*4].bl_count
        add eax,eax
        mov next_code[rcx*4+4],eax
    .endf

    .for ( edi = 0 : edi <= max_code : edi++ )

        movzx ecx,[rsi+rdi*4].ct_data.Len
        .if ( ecx )

            ; Now reverse the bits

            mov edx,next_code[rcx*4]
            inc next_code[rcx*4]
            xor eax,eax
            .repeat
                shr edx,1
                adc eax,eax
            .untilcxz
            mov [rsi+rdi*4].ct_data.Code,ax
        .endif
    .endf
    ret

gen_codes endp


smaller proc __ccall uses rsi tree:PCTDATA, n:int_t, m:int_t

    ldr rcx,tree
    ldr edx,n
    ldr esi,m

    .if ( ( [rcx+rdx*4].ct_data.Freq < [rcx+rsi*4].ct_data.Freq ) ||
          ( ZERO? && [rbx+rdx].depth <= [rbx+rsi].depth ) )
        .return( 1 )
    .endif
    .return( 0 )

smaller endp


pqdownheap proc __ccall uses rsi rdi tree:PCTDATA, k:int_t

   .new v:int_t

    ldr esi,k
    lea edi,[rsi*2] ; left son of k
    mov v,[rbx+rsi*4].heap

    .while ( edi <= [rbx].heap_len )

        ; Set EDI to the smallest of the two sons:

        .if ( edi < [rbx].heap_len )

            .ifd smaller(tree, [rbx+rdi*4+4].heap, [rbx+rdi*4].heap)

                inc edi
            .endif
        .endif

        ; Exit if v is smaller than both sons

        .break .ifd smaller(tree, v, [rbx+rdi*4].heap)

        ; Exchange v with the smallest son

        mov [rbx+rsi*4].heap,[rbx+rdi*4].heap
        mov esi,edi

        ; And continue down the tree, setting j(EDI) to the left son of k(ESI)

        add edi,edi
    .endw
    mov [rbx+rsi*4].heap,v
    ret

pqdownheap endp


;
; Construct one Huffman tree and assigns the code bit strings and lengths.
; Update the total bit length for the current block.
;

build_tree proc __ccall uses rsi rdi desc:PTREE

   .new tree:PCTDATA
   .new stree:PCTDATA
   .new max_code:int_t ; largest code with non zero frequency
   .new elems:int_t
   .new node:int_t

    ldr rsi,desc ; the tree descriptor
    mov tree,[rsi].tree_desc.dyn_tree
    mov stree,[rsi].tree_desc.static_tree
    mov elems,[rsi].tree_desc.elems
    mov node,eax
    mov [rbx].heap_max,HEAP_SIZE

    .for ( rdx = tree, eax = 0, edi = 0, ecx = -1 : eax < elems : eax++ )

        .if ( [rdx+rax*4].ct_data.Freq != 0 )

            mov ecx,eax
            inc edi
            mov [rbx+rdi*4].heap,eax
            mov [rbx+rax].depth,0
        .else
            mov [rdx+rax*4].ct_data.Len,0
        .endif
    .endf

    ;
    ; The pkzip format requires that at least one distance code exists,
    ; and that at least one bit should be sent even if there is only one
    ; possible code. So to avoid special checks later on we force at least
    ; two codes of non zero frequency.
    ;
    .while ( edi < 2 )

        inc edi
        xor eax,eax
        .ifs ( ecx < 2 )
            inc ecx
            mov eax,ecx
        .endif
        mov [rbx+rdi*4].heap,eax
        mov [rdx+rax*4].ct_data.Freq,1
        mov [rbx+rax].depth,0
        dec [rbx].opt_len
        mov rdx,stree
        .if rdx
            movzx eax,[rdx+rax*4].ct_data.Len
            sub [rbx].static_len,eax
        .endif
    .endw
    mov [rbx].heap_len,edi
    mov max_code,ecx
    mov [rsi].tree_desc.max_code,ecx

    ;
    ; The elements heap[heap_len/2+1 .. heap_len] are leaves of the tree,
    ; establish sub-heaps of increasing lengths:
    ;
    .for ( edi >>= 1 : edi >= 1 : edi-- )

        pqdownheap(tree, edi)
    .endf
    ;
    ; Construct the Huffman tree by repeatedly combining the least two
    ; frequent nodes.
    ;
    .repeat

        mov edi,[rbx+SMALLEST*4].heap
        mov eax,[rbx].heap_len
        dec [rbx].heap_len
        mov eax,[rbx+rax*4].heap
        mov [rbx+SMALLEST*4].heap,eax
        pqdownheap(tree, SMALLEST)

        mov ecx,[rbx+SMALLEST*4].heap
        sub [rbx].heap_max,2
        mov eax,[rbx].heap_max
        mov [rbx+rax*4+4].heap,edi
        mov [rbx+rax*4].heap,ecx

        ; Create a new node father of n and m

        mov rdx,tree
        mov ax,[rdx+rcx*4].ct_data.Freq
        add ax,[rdx+rdi*4].ct_data.Freq
        mov esi,node
        mov [rdx+rsi*4].ct_data.Freq,ax

        mov al,[rbx+rcx].depth
        mov ah,[rbx+rdi].depth
        .if ( ah >= al )
            mov al,ah
        .endif
        inc al
        mov [rbx+rsi].depth,al
        mov [rdx+rcx*4].ct_data.Dad,si
        mov [rdx+rdi*4].ct_data.Dad,si

        ; and insert the new node in the heap

        mov [rbx+SMALLEST*4].heap,esi
        inc node
        pqdownheap(tree, SMALLEST)

    .until ( [rbx].heap_len < 2 )

    mov eax,[rbx+SMALLEST*4].heap
    dec [rbx].heap_max
    mov ecx,[rbx].heap_max
    mov [rbx+rcx*4].heap,eax

    ; At this point, the fields freq and dad are set. We can now
    ; generate the bit lengths.

    gen_bitlen(desc)

    ; The field len is now set, we can generate the bit codes

    gen_codes(tree, max_code)
    ret

build_tree endp


send_bits proc __ccall uses rsi rdi value:int_t, length:int_t

    ldr esi,value
    ldr edi,length

    mov edx,[rbx].bi_buf
    mov ecx,[rbx].bi_valid
    mov eax,esi
    shl eax,cl
    or  eax,edx
    add ecx,edi
    mov [rbx].bi_buf,eax
    mov [rbx].bi_valid,ecx

    .if ( ecx > 16 )

        putshort(eax)

        sub [rbx].bi_valid,16
        mov ecx,edi
        sub ecx,[rbx].bi_valid
        shr esi,cl
        mov [rbx].bi_buf,esi
    .endif
    ret

send_bits endp


scan_tree proc __ccall uses rsi rdi tree:PCTDATA, max_code:int_t

   .new prevlen:int_t = -1     ; last emitted length
   .new max_count:int_t = 7    ; max repeat count
   .new min_count:int_t = 4    ; min repeat count

    ldr rdi,tree
    ldr edx,max_code
    mov [rdi+rdx*4+4].ct_data.Len,-1
    movzx eax,[rdi].ct_data.Len
    .if ( eax == 0 )

        mov max_count,138
        mov min_count,3
    .endif

    .for ( edx = 0, esi = 0 : esi <= max_code : esi++ )

        mov     ecx,eax
        lea     eax,[rsi+1]
        movzx   eax,[rdi+rax*4].ct_data.Len
        inc     edx

        .if ( edx < max_count && ecx == eax )
            .continue
        .elseif ( edx < min_count )
            add [rbx+rcx*4].bl_tree.Freq,dx
        .elseif ( ecx != 0 )
            .if ( ecx != prevlen )
                inc [rbx+rcx*4].bl_tree.Freq
            .endif
            inc [rbx+4*REP_3_6].bl_tree.Freq
        .elseif ( edx <= 10 )
            inc [rbx+4*REPZ_3_10].bl_tree.Freq
        .else
            inc [rbx+4*REPZ_11_138].bl_tree.Freq
        .endif

        xor edx,edx
        mov prevlen,ecx
        .if ( eax == 0 )
            mov max_count,138
            mov min_count,3
        .elseif ( ecx == eax )
            mov max_count,6
            mov min_count,3
        .else
            mov max_count,7
            mov min_count,4
        .endif
    .endf
    ret

scan_tree endp


send_tree proc __ccall uses rsi rdi tree:PCTDATA, max_code:int_t

   .new prevlen:int_t = -1     ; last emitted length
   .new curlen:int_t           ; length of current code
   .new nextlen:int_t          ; length of next code
   .new count:int_t = 0        ; repeat count of the current code
   .new max_count:int_t = 7    ; max repeat count
   .new min_count:int_t = 4    ; min repeat count

    mov rdi,tree
    movzx eax,[rdi].ct_data.Len
    mov nextlen,eax

    .if ( eax == 0 )

        mov max_count,138
        mov min_count,3
    .endif

    .for ( esi = 0 : esi <= max_code : esi++ )

        mov curlen,nextlen

        lea eax,[rsi+1]
        movzx eax,[rdi+rax*4].ct_data.Len
        mov nextlen,eax
        inc count

        mov ecx,curlen
        mov edx,count

        .if ( edx < max_count && ecx == nextlen )
            .continue
        .elseif ( edx < min_count )
            .repeat
                movzx edx,[rbx+rcx*4].bl_tree.ct_data.Len
                movzx ecx,[rbx+rcx*4].bl_tree.ct_data.Code
                send_bits(ecx, edx)
                mov ecx,curlen
                dec count
            .untilz
        .elseif ( ecx != 0 )
            .if ( ecx != prevlen )
                movzx edx,[rbx+rcx*4].bl_tree.ct_data.Len
                movzx ecx,[rbx+rcx*4].bl_tree.ct_data.Code
                send_bits(ecx, edx)
                dec count
            .endif
            movzx ecx,[rbx+4*REP_3_6].bl_tree.Code
            movzx edx,[rbx+4*REP_3_6].bl_tree.Len
            send_bits(ecx, edx)
            mov ecx,count
            sub ecx,3
            send_bits(ecx, 2)

        .elseif ( edx <= 10 )
            movzx ecx,[rbx+4*REPZ_3_10].bl_tree.Code
            movzx edx,[rbx+4*REPZ_3_10].bl_tree.Len
            send_bits(ecx, edx)
            mov ecx,count
            sub ecx,3
            send_bits(ecx, 3)
        .else
            movzx ecx,[rbx+4*REPZ_11_138].bl_tree.Code
            movzx edx,[rbx+4*REPZ_11_138].bl_tree.Len
            send_bits(ecx, edx)
            mov ecx,count
            sub ecx,11
            send_bits(ecx, 7)
        .endif
        mov count,0
        mov prevlen,curlen
        .if ( nextlen == 0 )
            mov max_count,138
            mov min_count,3
        .elseif ( curlen == nextlen )
            mov max_count,6
            mov min_count,3
        .else
            mov max_count,7
            mov min_count,4
        .endif
    .endf
    ret

send_tree endp


build_bl_tree proc

    scan_tree(&[rbx].dyn_ltree, l_desc.max_code)
    scan_tree(&[rbx].dyn_dtree, d_desc.max_code)
    build_tree(&bl_desc)

    .for ( rdx = &bl_order, ecx = BL_CODES-1 : ecx >= 3 : ecx-- )

        movzx eax,byte ptr [rdx+rcx]
        movzx eax,[rbx+rax*4].bl_tree.ct_data.Len
       .break .if eax
    .endf

    inc ecx
    imul eax,ecx,3
    dec ecx
    add eax,5+5+4
    add [rbx].opt_len,eax
    mov eax,ecx
    ret

build_bl_tree endp


send_all_trees proc __ccall uses rsi rdi lcodes:int_t, dcodes:int_t, blcodes:int_t

    mov esi,lcodes
    mov edi,dcodes

    mov ecx,esi
    sub ecx,257
    send_bits(ecx, 5)

    mov ecx,edi
    dec ecx
    send_bits(ecx, 5)

    mov ecx,blcodes
    sub ecx,4
    send_bits(ecx, 4)

    .for ( esi = 0 : esi < blcodes : esi++ )

        lea rdx,bl_order
        movzx eax,byte ptr [rdx+rsi]
        movzx ecx,[rbx+rax*4].bl_tree.ct_data.Len
        send_bits(ecx, 3)
    .endf

    mov edx,lcodes
    dec edx
    send_tree(&[rbx].dyn_ltree, edx)
    dec edi
    send_tree(&[rbx].dyn_dtree, edi)
    ret

send_all_trees endp


init_block proc

    ; Initialize the trees.

    .for ( ecx = 0 : ecx < L_CODES :  ecx++ )
        mov [rbx+rcx*4].dyn_ltree.Freq,0
    .endf
    .for ( ecx = 0 : ecx < D_CODES :  ecx++ )
        mov [rbx+rcx*4].dyn_dtree.Freq,0
    .endf
    .for ( ecx = 0 : ecx < BL_CODES :  ecx++ )
        mov [rbx+rcx*4].bl_tree.Freq,0
    .endf
    mov [rbx].dyn_ltree[END_BLOCK*4].Freq,1
    mov [rbx].opt_len,0
    mov [rbx].static_len,0
    mov [rbx].last_lit,0
    mov [rbx].last_dist,0
    mov [rbx].last_flags,0
    mov [rbx].flags,0
    mov [rbx].flag_bit,1
    ret

init_block endp


ct_init proc uses rsi rdi

    mov file_method,METHOD_DEFLATE

    ; Initialize the mapping length (0..255) -> length code (0..28)

    xor esi,esi
    .for ( edx = 0 : edx < LENGTH_CODES-1 : edx++ )

        mov [rbx+rdx*4].base_length,esi

        lea rcx,extra_lbits
        mov ecx,[rcx+rdx*4]
        mov eax,1
        shl eax,cl

        .for ( edi = 0 : edi < eax : edi++ )

            mov [rbx+rsi].length_code,dl
            inc esi
        .endf
    .endf

    ; Note that the length 255 (match length 258) can be represented
    ; in two different ways: code 284 + 5 bits or code 285, so we
    ; overwrite length_code[255] to use the best encoding:

    mov [rbx+rsi-1].length_code,dl

    ; Initialize the mapping dist (0..32K) -> dist code (0..29)

    xor esi,esi
    .for ( edx = 0 : edx < 16 : edx++ )

        mov [rbx+rdx*4].base_dist,esi
        lea rcx,extra_dbits
        mov ecx,[rcx+rdx*4]
        mov eax,1
        shl eax,cl

        .for ( edi = 0 : edi < eax : edi++ )

            mov [rbx+rsi].d_code,dl
            inc esi
        .endf
    .endf

    ; from now on, all distances are divided by 128

    .for ( esi >>= 7 : edx < D_CODES : edx++ )

        mov eax,esi
        shl eax,7
        mov [rbx+rdx*4].base_dist,eax

        lea rcx,extra_dbits
        mov ecx,[rcx+rdx*4]
        sub ecx,7
        mov eax,1
        shl eax,cl

        .for ( edi = 0 : edi < eax : edi++ )

            mov [rbx+rsi].d_code[256],dl
            inc esi
        .endf
    .endf

    lea rdi,[rbx].bl_count
    mov ecx,MAX_BITS+1
    xor eax,eax
    rep stosd
    mov ecx,8

    .while ( eax <= 143 )
        inc [rbx].bl_count[8*4]
        mov [rbx+rax*4].static_ltree.Len,cx
        inc eax
    .endw
    inc ecx
    .while ( eax <= 255 )
        inc [rbx].bl_count[9*4]
        mov [rbx+rax*4].static_ltree.Len,cx
        inc eax
    .endw
    mov ecx,7
    .while ( eax <= 279 )
        inc [rbx].bl_count[7*4]
        mov [rbx+rax*4].static_ltree.Len,cx
        inc eax
    .endw
    inc ecx
    .while ( eax <= 287 )
        inc [rbx].bl_count[8*4]
        mov [rbx+rax*4].static_ltree.Len,cx
        inc eax
    .endw

    ; Codes 286 and 287 do not exist, but we must include them in the tree
    ; construction to get a canonical Huffman tree (longest code all ones)

    gen_codes(&[rbx].static_ltree, L_CODES+1)

    ; The static distance tree is trivial

    .for ( esi = 0 : esi < D_CODES : esi++ )

        mov edx,5
        mov [rbx+rsi*4].static_dtree.Len,dx

        .for ( eax = 0, ecx = esi : edx : edx-- )

            shr ecx,1
            adc eax,eax
        .endf
        mov [rbx+rsi*4].static_dtree.Code,ax
    .endf

    ; Initialize the first block of the first file:

    init_block()
    ret

ct_init endp

;
; Write out any remaining bits in an incomplete byte.
;
bi_windup proc uses rsi rdi

    xor eax,eax
    mov ecx,[rbx].bi_valid
    mov edx,[rbx].bi_buf
    mov [rbx].bi_buf,eax
    mov [rbx].bi_valid,eax
    mov esi,ecx
    mov edi,edx
    inc eax
    .if ecx

        .ifd oputc(edx)

            .if ( esi > 8 )

                mov ecx,edi
                movzx ecx,ch
                oputc(ecx)
            .endif
        .endif
    .endif
    ret

bi_windup endp


ifdef _LIN64
copy_block proc __ccall uses rsi rdi buf:LPSTR, len:UINT, header:int_t
else
copy_block proc __ccall buf:LPSTR, len:UINT, header:int_t
endif

    .ifd bi_windup()

        .if header

            .ifd !putshort(len)
                .return
            .endif
            mov ecx,len
            not ecx
            .ifd !putshort(ecx)
                .return
            .endif
        .endif

        mov eax,1
        .if ( len )

            .ifd ( fwrite(buf, 1, len, [rbx].fpo) == len )
                .return( 1 )
            .endif
            xor eax,eax
        .endif
    .endif
    ret

copy_block endp


compress_block proc __ccall uses rsi rdi ltree:PCTDATA, dtree:PCTDATA

   .new dist:UINT       ; distance of matched string
   .new lc:SINT         ; match length or unmatched char (if dist == 0)
   .new lx:UINT = 0     ; running index in l_buf
   .new _dx:UINT = 0    ; running index in d_buf
   .new fx:UINT = 0     ; running index in flag_buf
   .new flag:BYTE = 0   ; current flags
   .new code:UINT       ; the code to send
   .new extra:SINT      ; number of extra bits to send

    ldr rsi,ltree
    ldr rdi,dtree

     .if ( [rbx].last_lit )

        .repeat

            mov edx,lx
            .if !( edx & 7 )

                mov eax,fx
                inc fx
                mov al,[rbx].flag_buf[rax]
                mov flag,al
            .endif

            inc lx
            movzx eax,[rbx+rdx].l_buf
            mov lc,eax

            .if !( flag & 1 )

                movzx edx,[rsi+rax*4].ct_data.Len
                movzx ecx,[rsi+rax*4].ct_data.Code
                send_bits(ecx, edx)

            .else

                ; Here, lc is the match length - MIN_MATCH

                mov     eax,lc
                movzx   eax,[rbx+rax].length_code
                mov     code,eax
                add     eax,LITERALS+1
                movzx   edx,[rsi+rax*4].ct_data.Len
                movzx   ecx,[rsi+rax*4].ct_data.Code
                send_bits(ecx, edx) ; send the length code

                mov eax,code
                lea rdx,extra_lbits
                mov eax,[rdx+rax*4]
                mov extra,eax
                .if eax
                    mov edx,eax
                    mov ecx,code
                    mov eax,lc
                    sub eax,[rbx+rcx*4].base_length
                    mov lc,eax
                    send_bits(eax, edx) ; send the extra length bits
                .endif

                mov eax,_dx
                inc _dx
                mov eax,[rbx].d_buf[rax*4]
                mov dist,eax

                ; Here, dist is the match distance - 1

                .if ( eax >= 256 )

                    shr eax,7
                    add eax,256
                .endif

                movzx   eax,[rbx+rax].d_code
                mov     code,eax
                movzx   edx,[rdi+rax*4].ct_data.Len
                movzx   ecx,[rdi+rax*4].ct_data.Code
                send_bits(ecx, edx) ; send the distance code

                mov ecx,code
                lea rdx,extra_dbits
                mov eax,[rdx+rcx*4]
                mov extra,eax
                .if eax
                    mov edx,eax
                    mov eax,dist
                    sub eax,[rbx+rcx*4].base_dist
                    mov dist,eax
                    send_bits(eax, edx) ; send the extra distance bits
                .endif
            .endif

            shr flag,1
            mov eax,lx
        .until ( eax >= [rbx].last_lit )
    .endif

    movzx ecx,[rsi+4*END_BLOCK].ct_data.Code
    movzx edx,[rsi+4*END_BLOCK].ct_data.Len
    send_bits(ecx, edx)
    ret

compress_block endp


flush_block proc __ccall uses rsi rdi eof:int_t

   .new opt_lenb:UINT       ; opt_len in bytes
   .new static_lenb:UINT    ; static_len in bytes
   .new stored_len:UINT     ; length of input block
   .new max_blindex:UINT    ; index of last bit length code of non zero freq
   .new buf:LPSTR           ; input block, or NULL if too old

    xor eax,eax
    .ifs ( [rbx].block_start >= eax )
        mov eax,[rbx].block_start
        mov rdx,[rbx].fpi
        add rax,[rdx].FILE._base
    .endif
    mov buf,rax

    mov eax,[rbx].str_start
    sub eax,[rbx].block_start
    mov stored_len,eax

    mov al,[rbx].flags  ; Save the flags for the last 8 items
    mov ecx,[rbx].last_flags
    mov [rbx+rcx].flag_buf,al

    build_tree(&l_desc) ; Construct the literal and distance trees
    build_tree(&d_desc)

    ; At this point, opt_len and static_len are the total bit lengths of
    ; the compressed block data, excluding the tree representations.

    ; Build the bit length tree for the above two trees, and get the index
    ; in bl_order of the last bit length code to send.

    mov max_blindex,build_bl_tree()

    ; Determine the best encoding. Compute first the block length in bytes

    mov eax,[rbx].opt_len
    add eax,3+7
    shr eax,3
    mov opt_lenb,eax

    mov eax,[rbx].static_len
    add eax,3+7
    shr eax,3
    mov static_lenb,eax
    .if ( eax <= opt_lenb )
        mov opt_lenb,eax
    .endif

    mov eax,stored_len
    lea ecx,[rax+4]     ; 4: two words for the lengths
    mov edx,[rbx].cmpr_bytelen
    or  edx,[rbx].cmpr_lenbits

    ; If compression failed and this is the first and last block,
    ; and if the zip file can be seeked (to rewrite the local header),
    ; the whole file is transformed into a stored file:

ifdef FORCE_METHOD
    .if ( [rbx].cmpr_level == 1 && eof && edx == 0 ) ; force stored file
else
    .if ( eax <= opt_lenb && eof && edx == 0 )
endif
        ; Since LIT_BUFSIZE <= 2*WSIZE, the input data must be there:

        .if ( buf == NULL )

            .return( 0 )
        .endif
        .if !copy_block(buf, stored_len, 0) ; without header

            .return
        .endif
        mov [rbx].cmpr_bytelen,stored_len
        mov file_method,METHOD_STORE

ifdef FORCE_METHOD
    .elseif ( [rbx].cmpr_level == 2 && buf ) ; force stored file
else
    .elseif ( ecx <= opt_lenb && buf )
endif
        ; The test buf != NULL is only necessary if LIT_BUFSIZE > WSIZE.
        ; Otherwise we can't have processed more than WSIZE input bytes since
        ; the last block flush, because compression would have been
        ; successful. If LIT_BUFSIZE <= WSIZE, it is never too late to
        ; transform a block into a stored block.

        send_bits(eof, 3) ; send block type

        mov eax,[rbx].cmpr_lenbits
        add eax,3+7
        shr eax,3
        add eax,stored_len
        add eax,4
        add [rbx].cmpr_bytelen,eax
        mov [rbx].cmpr_lenbits,0
        .if !copy_block(buf, stored_len, 1) ; with header

            .return
        .endif
ifdef FORCE_METHOD
    .elseif ( [rbx].cmpr_level == 3 ) ; force static trees
else
    .elseif ( static_lenb == opt_lenb )
endif


        mov ecx,eof
        add ecx,STATIC_TREES*2
        send_bits(ecx, 3)
        compress_block(&[rbx].static_ltree, &[rbx].static_dtree)
        mov eax,[rbx].static_len
        add eax,3
        add eax,[rbx].cmpr_lenbits
        mov ecx,eax
        and eax,7
        mov [rbx].cmpr_lenbits,eax
        shr ecx,3
        add [rbx].cmpr_bytelen,ecx

    .else

        mov ecx,eof
        add ecx,DYN_TREES*2
        send_bits(ecx, 3)
        mov ecx,l_desc.max_code
        inc ecx
        mov edx,d_desc.max_code
        inc edx
        mov eax,max_blindex
        inc eax
        send_all_trees(ecx, edx, eax)
        compress_block(&[rbx].dyn_ltree, &[rbx].dyn_dtree)
        mov eax,[rbx].opt_len
        add eax,3
        add eax,[rbx].cmpr_lenbits
        mov ecx,eax
        and eax,7
        mov [rbx].cmpr_lenbits,eax
        shr ecx,3
        add [rbx].cmpr_bytelen,ecx
    .endif

    init_block()
    .if ( eof )
        bi_windup()
        add [rbx].cmpr_lenbits,7 ; align on byte boundary
    .endif
    mov eax,[rbx].cmpr_bytelen
    ret

flush_block endp

;
; Save the match info and tally the frequency counts. Return true if
; the current block must be flushed.
;
; DX match length-MIN_MATCH or unmatched char (if dist==0)
; AX distance of matched string
;

ct_tally proc __ccall uses rsi rdi dist:int_t, lc:int_t

    ldr eax,dist
    ldr edx,lc

    mov ecx,[rbx].last_lit
    mov [rbx+rcx].l_buf,dl
    inc [rbx].last_lit

    .if ( eax == 0 )

        ; lc is the unmatched char

        inc [rbx+rdx*4].dyn_ltree.Freq
    .else

        ; Here, lc is the match length - MIN_MATCH

        dec eax
        mov edi,eax
        movzx eax,[rbx+rdx].length_code
        add eax,LITERALS+1
        inc [rbx+rax*4].dyn_ltree.Freq

        mov edx,edi
        .if ( edi >= 256 )

            shr edi,7
            add edi,256
        .endif

        movzx eax,[rbx+rdi].d_code
        inc [rbx+rax*4].dyn_dtree.Freq

        mov eax,[rbx].last_dist
        inc [rbx].last_dist
        mov [rbx+rax*4].d_buf,edx
        mov al,[rbx].flag_bit
        or  [rbx].flags,al
    .endif

    shl [rbx].flag_bit,1

    ; Output the flags if they fill a byte:

    .if !( [rbx].last_lit & 7 )

        mov al,[rbx].flags
        mov edi,[rbx].last_flags
        inc [rbx].last_flags
        mov [rbx].flag_buf[rdi],al
        mov [rbx].flags,0
        mov [rbx].flag_bit,1
    .endif

    ; Try to guess if it is profitable to stop the current block here

    mov edi,[rbx].last_lit
    .if ( [rbx].compr_level > 2 && !( edi & 0x0FFF ) )

        ; Compute an upper bound for the compressed length

        .for ( edi <<= 3, ecx = 0 : ecx < D_CODES : ecx++ )

            movzx eax,[rbx+rcx*4].dyn_dtree.Freq
            lea rdx,extra_dbits
            mov edx,[rdx+rcx*4]
            add edx,5
            mul edx
            add edi,eax
        .endf
        shr edi,3

        mov eax,[rbx].last_lit
        shr eax,1
        .if ( [rbx].last_dist < eax )

            mov eax,[rbx].str_start
            sub eax,[rbx].block_start
            and eax,0xFFFF
            shr eax,1
            .if ( edi < eax )

                .return( 1 )
            .endif
        .endif
    .endif
    mov eax,1
    .if ( [rbx].last_lit != LIT_BUFSIZE-1 && [rbx].last_dist != DIST_BUFSIZE )
        dec eax
    .endif
    ret

ct_tally endp


update_hash proc watcall id:int_t

    mov     rcx,[rbx].fpi
    mov     rcx,[rcx].FILE._base
    movzx   ecx,BYTE PTR [rcx+rax]
    mov     eax,[rbx].ins_h
    shl     eax,H_SHIFT
    xor     eax,ecx
    and     eax,HASH_MASK
    mov     [rbx].ins_h,eax
    ret

update_hash endp

;
; Insert string s in the dictionary and set match_head to the previous head
; of the hash chain (the most recent string with same hash key). Return
; the previous length of the hash chain.
;
insert_string proc

    mov     rcx,[rbx].fpi
    mov     rcx,[rcx].FILE._base
    mov     edx,[rbx].str_start
    add     edx,MIN_MATCH-1
    movzx   ecx,BYTE PTR [rcx+rdx]
    mov     eax,[rbx].ins_h
    shl     eax,H_SHIFT
    xor     eax,ecx
    and     eax,HASH_MASK
    mov     [rbx].ins_h,eax
    sub     edx,MIN_MATCH-1
    movzx   esi,[rbx].head_buf[rax*2]
    mov     [rbx].head_buf[rax*2],dx
    mov     rcx,[rbx].prev
    and     edx,WMASK
    mov     [rcx+rdx*2],si
    ret

insert_string endp


if HASH_BITS lt 8 or MAX_MATCH ne 258
   .err <Code too clever>
endif

longest_match proc uses rsi rdi rbp ; cur_match:int_t

    mov     rdx,[rbx].fpi
    mov     rdi,[rdx].FILE._base
    mov     rsi,rdi
    mov     si,ax                   ; match: window + cur_match

    mov     edx,[rbx].str_start
    mov     di,dx                   ; scan: window + start
    sub     edx,MAX_DIST            ; limit: start - MAX_DIST : 0
    jae     .0
    xor     edx,edx
.0:
    mov     ebp,[rbx].prev_length   ; best_len: prev_length

    ; Do not waste too much time if we already have a good match:

    mov     eax,[rbx].max_chain_len
    cmp     ebp,[rbx].good_match
    jb      .1
    shr     eax,2
.1:
    mov     rcx,[rbx].prev
    mov     [rbx].chain_length,eax
    mov     cx,[rdi]
    mov     ax,[rdi+rbp-1]
    add     rdi,2
.2:
    cmp     ax,[rsi+rbp-1]
    jne     .4
    cmp     cx,[rsi]
    jne     .4
    add     rsi,2
    mov     rax,rdi
    mov     ecx,(MAX_MATCH-2)
    repe    cmpsb
    mov     rcx,[rbx].prev
    xchg    rax,rdi
    sub     rax,rdi
    sub     rsi,rax
    sub     rsi,2
    inc     eax
    cmp     eax,ebp
    jle     .3
    mov     word ptr [rbx].match_start,si
    mov     ebp,eax
    cmp     eax,[rbx].nice_match
    jge     .5
.3:
    mov     ax,[rdi+rbp-3]
.4:
    add     si,si
    mov     cx,si
    mov     si,[rcx]
    mov     cx,[rdi-2]
    dec     [rbx].chain_length
    jz      .5
    cmp     si,dx
    ja      .2
.5:
    mov     eax,ebp
    ret

longest_match endp


fill_window proc uses rsi rdi

    .while 1

        xor esi,esi ; Amount of free space at the end of the window.
        mov eax,[rbx].str_start
        add eax,[rbx].lookahead
        sub si,ax

        .if ( si == -1 )

            dec si

        .elseif ( [rbx].str_start >= WSIZE+MAX_DIST )

            mov rcx,[rbx].fpi
            mov rdi,[rcx].FILE._base
            mov rdx,rsi
            lea rsi,[rdi+WSIZE]
            mov ecx,WSIZE
            rep movsb
            mov rsi,rdx

            sub [rbx].match_start,WSIZE
            sub [rbx].str_start,WSIZE
            sub [rbx].block_start,WSIZE

            .for ( rdi = [rbx].head, ecx = HASH_SIZE : ecx : ecx-- )

                xor eax,eax
                movzx edx,word ptr [rdi]
                .if ( edx >= WSIZE )
                    mov eax,edx
                    sub eax,WSIZE
                .endif
                stosw
            .endf

            .for ( rdi = [rbx].prev, ecx = WSIZE : ecx : ecx-- )

                xor eax,eax
                movzx edx,word ptr [rdi]
                .if ( edx >= WSIZE )
                    mov eax,edx
                    sub eax,WSIZE
                .endif
                stosw
            .endf
            add esi,WSIZE
        .endif
        .if ( [rbx].eofile )
            .return( 0 )
        .endif

        mov eax,[rbx].str_start
        add eax,[rbx].lookahead
        mov rdi,[rbx].fpi
        mov rdx,[rdi].FILE._base
        mov dx,ax
        mov [rdi].FILE._ptr,rdx
        mov [rdi].FILE._base,rdx
        mov [rdi].FILE._bufsiz,esi
        mov [rdi].FILE._cnt,0
        ioread()
        mov rdx,[rdi].FILE._base
        xor dx,dx
        mov [rdi].FILE._ptr,rdx
        mov [rdi].FILE._base,rdx

        .if ( eax == 0 )

            mov [rbx].eofile,1
           .return
        .endif
        mov eax,[rcx].FILE._cnt
        add [rbx].lookahead,eax
       .break .if ( [rbx].lookahead >= MIN_LOOKAHEAD )
    .endw
    ret

fill_window endp


deflate_fast proc uses rsi rdi

   .new match_length:int_t

    xor esi,esi
    mov match_length,esi
    mov [rbx].prev_length,MIN_MATCH-1

    .while 1 ; deflate while lookahead

        xor eax,eax
        mov ecx,[rbx].lookahead
        .if ( ecx == eax )

            .break
        .endif
        .if ( ecx >= MIN_MATCH )

            insert_string()
        .endif

        mov ecx,[rbx].str_start
        sub ecx,esi
        .if ( esi && ecx <= MAX_DIST )

            mov eax,[rbx].lookahead
            .if ( [rbx].nice_match > eax )
                mov [rbx].nice_match,eax
            .endif
            mov eax,esi
            longest_match()
            mov edx,[rbx].lookahead
            .if ( eax > edx )
                mov eax,edx
            .endif
            mov match_length,eax
        .endif

        mov eax,match_length
        .if ( eax >= MIN_MATCH )

            mov eax,[rbx].str_start
            sub eax,[rbx].match_start
            mov edx,match_length
            sub edx,MIN_MATCH
            ct_tally(eax, edx)

            mov edi,eax
            mov eax,match_length
            sub [rbx].lookahead,eax

            .if ( eax <= [rbx].max_lazy_match && [rbx].lookahead >= MIN_MATCH )

                .repeat
                    inc [rbx].str_start
                    insert_string()
                    dec match_length
                .untilz
                inc [rbx].str_start

            .else

                add [rbx].str_start,eax
                xor eax,eax
                mov match_length,eax
                mov ecx,[rbx].str_start
                mov rdx,[rbx].fpi
                add rcx,[rdx].FILE._base
                mov al,[rcx]
                mov [rbx].ins_h,eax
                mov eax,[rbx].str_start
                inc eax
                update_hash(eax)
  if not (MIN_MATCH eq 3)
                call UPDATE_HASH() MIN_MATCH-3 more times
  endif
            .endif
        .else

            mov ecx,[rbx].str_start
            mov rdx,[rbx].fpi
            add rcx,[rdx].FILE._base
            movzx edx,BYTE PTR [rcx]
            mov edi,ct_tally(0, edx)
            dec [rbx].lookahead
            inc [rbx].str_start
        .endif

        .if ( edi )

            .ifd !flush_block(0)

                .return
            .endif
            mov [rbx].block_start,[rbx].str_start
        .endif
        .continue .if ( [rbx].lookahead >= MIN_LOOKAHEAD )

        fill_window()
        mov rcx,[rbx].fpi
        .if ( [rcx].FILE._flag & _IOERR )

            .return( 0 )
        .endif
    .endw
    flush_block(1)
    ret

deflate_fast endp


_deflate proc uses rsi rdi

   .new len:int_t
   .new mavailable:int_t = 0
   .new match_length:int_t = MIN_MATCH-1
   .new prev_match:uint_t

    .if ( [rbx].compr_level <= 3 )

        .return deflate_fast()
    .endif

    xor esi,esi

    .while 1

        xor eax,eax
        mov ecx,[rbx].lookahead
        .if ( !ecx )

            .break
        .endif
        .if ( ecx >= MIN_MATCH )

            insert_string()
        .endif

        mov prev_match,[rbx].match_start
        mov [rbx].prev_length,match_length
        mov match_length,MIN_MATCH-1
        mov ecx,[rbx].str_start
        sub ecx,esi

        .if ( esi && eax < [rbx].max_lazy_match && ecx <= MAX_DIST )

            mov eax,[rbx].lookahead
            .if ( [rbx].nice_match >= eax )
                mov [rbx].nice_match,eax
            .endif

            mov eax,esi
            longest_match()
            .if ( eax >= [rbx].lookahead )
                mov eax,[rbx].lookahead
            .endif
            mov match_length,eax
            .if ( eax == MIN_MATCH )

                mov eax,[rbx].str_start
                sub ax,word ptr [rbx].match_start
                .if ( eax > TOO_FAR )
                    mov match_length,MIN_MATCH-1
                .endif
            .endif
        .endif

        mov eax,[rbx].prev_length
        .if ( eax >= MIN_MATCH && match_length <= eax )

            mov eax,[rbx].str_start
            add eax,[rbx].lookahead
            sub eax,MIN_MATCH
            mov len,eax

            mov eax,[rbx].str_start
            dec eax
            sub ax,word ptr prev_match
            mov edx,[rbx].prev_length
            sub edx,MIN_MATCH
            mov edi,ct_tally(eax, edx)

            mov eax,[rbx].prev_length
            dec eax
            sub [rbx].lookahead,eax
            dec eax
            mov [rbx].prev_length,eax

            .repeat
                inc [rbx].str_start
                .if ( [rbx].str_start <= len )
                    insert_string()
                .endif
                dec [rbx].prev_length
            .untilz
            inc [rbx].str_start
            xor eax,eax
            mov mavailable,eax
            mov match_length,MIN_MATCH-1

            .if ( edi )

                .ifd !flush_block(0)

                    .return
                .endif
                mov [rbx].block_start,[rbx].str_start
            .endif

        .else

            xor eax,eax
            .if ( mavailable != eax )

                mov rdx,[rbx].fpi
                mov rcx,[rdx].FILE._base
                mov cx,word ptr [rbx].str_start
                movzx edx,byte ptr [rcx-1]
                .ifd ct_tally(eax, edx)

                    .ifd !flush_block(0)

                       .return
                    .endif
                    mov [rbx].block_start,[rbx].str_start
                .endif
            .else
                mov mavailable,1
            .endif
            inc [rbx].str_start
            dec [rbx].lookahead
        .endif

        .continue .if ( [rbx].lookahead >= MIN_LOOKAHEAD )
        fill_window()
        mov rcx,[rbx].fpi
        .if ( [rcx].FILE._flag & _IOERR )

            .return( 0 )
        .endif
    .endw

    .if ( mavailable )

        mov ecx,[rbx].str_start
        mov rdx,[rbx].fpi
        add rcx,[rdx].FILE._base
        movzx edx,BYTE PTR [rcx-1]
        ct_tally(0, edx)
    .endif
    flush_block(1)
    ret

_deflate endp


deflate proc public uses rsi rdi rbx src:string_t, dst:LPFILE, zp:ptr ZipLocal

    .new fp:LPFILE = fopen(ldr(src), "rb")
    .new retval:int_t = 0

    .if ( rax == NULL )

       .return
    .endif

    .if !malloc(DEFLATE+3*0x10000)

        fclose(fp)
       .return( 0 )
    .endif
    mov rbx,rax
    mov rdi,rax
    mov ecx,DEFLATE+3*0x10000
    xor eax,eax
    rep stosb

    dec [rbx].crc
    mov [rbx].fpi,fp
    mov [rbx].fpo,dst
    mov [rbx].compr_level,compresslevel
    mov [rbx].head,&[rbx].head_buf

    lea rax,[rbx+DEFLATE]
    and rax,-65536 ; align block on 64K
    add rax,65536
    mov [rbx].prev,rax
    add rax,0x10000
    setvbuf(fp, rax, _IOFBF, 0x8000)

    mov l_desc.dyn_tree,&[rbx].dyn_ltree
    mov l_desc.static_tree,&[rbx].static_ltree
    mov d_desc.dyn_tree,&[rbx].dyn_dtree
    mov d_desc.static_tree,&[rbx].static_dtree
    mov bl_desc.dyn_tree,&[rbx].bl_tree

    mov rdi,[rbx].head
    mov ecx,HASH_SIZE/2
    xor eax,eax
    rep stosd
    mov file_method,al

    .ifd ct_init()

        mov eax,[rbx].compr_level
        imul eax,eax,dconfig
        lea rcx,config_table
        add rcx,rax

        mov [rbx].max_lazy_match,[rcx].dconfig.max_lazy
        mov [rbx].good_match,[rcx].dconfig.good_length
        mov [rbx].nice_match,[rcx].dconfig.nice_length
        mov [rbx].max_chain_len,[rcx].dconfig.max_chain

        mov eax,[rbx].compr_level
        .if ( al == 1 )
            mov [rbx].compr_flags,FAST
        .endif
        .if ( al == 9 )
            mov [rbx].compr_flags,SLOW
        .endif

        mov [rbx].lookahead,ioread()
        .if ( eax == 0 )

           .return( 1 )
        .endif
        .if ( eax < MIN_LOOKAHEAD )

            fill_window()
        .endif
        update_hash(0)
        update_hash(1)
        mov retval,_deflate()
    .endif

    mov rcx,zp
    .if ( rcx )

        mov [rcx].ZipLocal.Signature,ZIPLOCALID
        mov eax,[rbx].crc
        not eax
        mov [rcx].ZipLocal.crc,eax
        movzx eax,file_method
        mov [rcx].ZipLocal.method,ax
        mov [rcx].ZipLocal.csize,[rbx].csize
        mov [rcx].ZipLocal.fsize,[rbx].fsize
    .endif

    fclose(fp)
    free(rbx)
    mov eax,retval
    ret

deflate endp

    end
