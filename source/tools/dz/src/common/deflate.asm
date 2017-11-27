; DEFLATE.ASM--
;
;  This is from Info-ZIP's Zip 3.0:
;
;	trees.c	   - by Jean-loup Gailly
;	match.asm  - by Jean-loup Gailly
;	deflate.c  - by Jean-loup Gailly
;
;	Copyright (c) 1990-2008 Info-ZIP. All rights reserved.
;
;  That is free (but copyrighted) software. The original sources and license
;  are available from Info-ZIP's home site at: http://www.info-zip.org/
;
; Change history:
; 2012-09-09 - created
;
;
include iost.inc
include string.inc
include stdio.inc
include malloc.inc
include zip.inc
include errno.inc
include crtl.inc

PUBLIC	file_method

SEGM64K		equ 10000h

MIN_MATCH	equ 3 ; The minimum and maximum match lengths
MAX_MATCH	equ 258

; Maximum window size = 32K. If you are really short of memory, compile
; with a smaller WSIZE but this reduces the compression ratio for files
; of size > WSIZE. WSIZE must be a power of two in the current implementation.
;
WSIZE		equ 8000h
WMASK		equ WSIZE-1

; Minimum amount of lookahead, except at the end of the input file.
; See deflate.c for comments about the MIN_MATCH+1.
;
MIN_LOOKAHEAD	equ MAX_MATCH+MIN_MATCH+1

; In order to simplify the code, particularly on 16 bit machines, match
; distances are limited to MAX_DIST instead of WSIZE.
;
MAX_DIST	equ WSIZE-MIN_LOOKAHEAD

FILE_BINARY	equ 0	; internal file attribute
FILE_ASCII	equ 1
FILE_UNKNOWN	equ -1

METHOD_STORE	equ 0	; Store method
METHOD_DEFLATE	equ 8	; Deflation method
METHOD_BEST	equ -1	; Use best method (deflation or store)

MEDIUM_MEM	equ 1
HASH_BITS	equ 14	; Number of bits used to hash strings
LIT_BUFSIZE	equ 4000h

; HASH_SIZE and WSIZE must be powers of two
;
HASH_SIZE	equ (1 shl HASH_BITS)
HASH_MASK	equ HASH_SIZE-1
H_SHIFT		equ (HASH_BITS+MIN_MATCH-1)/MIN_MATCH

FAST		equ 4	; speed options for the general purpose bit flag
SLOW		equ 2

; Matches of length 3 are discarded if their distance exceeds TOO_FAR
;
TOO_FAR		equ 4096
MAXSEG_64K	equ 1

MAX_BITS	equ 15	; All codes must not exceed MAX_BITS bits
MAX_BL_BITS	equ 7	; Bit length codes must not exceed MAX_BL_BITS bits
LENGTH_CODES	equ 29	; number of length codes, not counting the special
			; END_BLOCK code
LITERALS	equ 256 ; number of literal bytes 0..255
END_BLOCK	equ 256 ; end of block literal code
D_CODES		equ 30	; number of distance codes
BL_CODES	equ 19	; number of codes used to transfer the bit lengths

; number of Literal or Length codes, including the END_BLOCK code
;
L_CODES		equ LITERALS+1+LENGTH_CODES

STORED_BLOCK	equ 0	; The three kinds of block type
STATIC_TREES	equ 1
DYN_TREES	equ 2

DIST_BUFSIZE	equ LIT_BUFSIZE

; repeat previous bit length 3-6 times (2 bits of repeat count)
;
REP_3_6		equ 16
REPZ_3_10	equ 17	; repeat a zero length 3-10 times (3 bits)
REPZ_11_138	equ 18	; repeat a zero length 11-138 times (7 bits)

HEAP_SIZE	equ 2*L_CODES+1 ; maximum heap size

SMALLEST	equ 1	; Index within the heap array of least
			; frequent node in the Huffman tree

; Data structure describing a single value and its code string.

CT_DATA		STRUC
UNION			; fc
  ct_freq	dw ?	; frequency count
  ct_code	dw ?	; bit string
ENDS
UNION			; dl
  ct_dad	dw ?	; father node in Huffman tree
  ct_len	dw ?	; length of bit string
ENDS
CT_DATA		ENDS

TREE_DESC	STRUC
td_dyn_tree	dd ?	; the dynamic tree
td_static_tree	dd ?	; corresponding static tree or NULL
td_extra_bits	dd ?	; extra bits for each code or NULL
td_extra_base	dd ?	; base index for extra_bits
td_elems	dd ?	; max number of elements in the tree
td_max_length	dd ?	; max bit length for the codes
td_max_code	dd ?	; largest code with non zero frequency
TREE_DESC	ENDS

dconfig		STRUC
good_length	dd ?	; reduce lazy search above this match length
max_lazy	dd ?	; do not perform lazy search above this match length
nice_length	dd ?	; quit search above this match length
max_chain	dd ?
dconfig		ENDS

S_DEFLATE	STRUC
head		dd ?
prev		dd ?
window_size	dd ?
block_start	dd ?
sliding		dd ?
ins_h		dd ?
prev_length	dd ?
match_start	dd ?
str_start	dd ?
eofile		dd ?
lookahead	dd ?
max_chain_len	dd ?
max_lazy_match	dd ?
max_insert_len	equ max_lazy_match
good_match	dd ?
ifdef FULL_SEARCH
nice_match	equ MAX_MATCH
else
nice_match	dd ?
endif
heap_len	dd ?
heap_max	dd ?
last_lit	dd ?
last_dist	dd ?
last_flags	dd ?
flags		db ?
flag_bit	db ?
opt_len		dd ?
static_len	dd ?
cmpr_bytelen	dd ?
cmpr_lenbits	dd ?
bi_buf		dd ?
bi_valid	dd ?
compr_level	dd ?
compr_flags	dd ?
lm_chain_length dd ?			; longest_match()
bt_max_code	dd ?			; build_tree()
bt_next_node	dd ?
st_prevlen	dd ?			; scan_tree()/send_tree()
st_curlen	dd ?
st_nextlen	dd ?
st_count	dd ?
st_max_code	dd ?
st_max_count	dd ?
st_min_count	dd ?
gb_bits		dd ?			; gen_bitlen()
gb_overflow	dd ?
fb_opt_len	dd ?
fb_static_ln	dd ?
fb_buf		dd ?
fb_stored_ln	dd ?
fb_eof		dd ?
cb_dist		dd ?			; compress_block()
cb_lc		dd ?
cb_lx		dd ?
cb_dx		dd ?
cb_fx		dd ?
cb_flag		db ?
cb_code		dd ?
cb_extra	dd ?
gc_next_code	dd MAX_BITS+1 dup(?)	; gen_codes()
d_mavailable	dd ?			; deflate()
d_prev_match	dd ?
d_match_length	dd ?
dyn_ltree	CT_DATA 2*L_CODES+1  dup(<?>)	; literal and length tree
dyn_dtree	CT_DATA 2*D_CODES+1  dup(<?>)	; distance tree
static_ltree	CT_DATA L_CODES+2    dup(<?>)	; the static literal tree
static_dtree	CT_DATA D_CODES	     dup(<?>)	; the static distance tree
bl_tree		CT_DATA 2*BL_CODES+1 dup(<?>)
heap		dd HEAP_SIZE dup(?)	; heap used to build the Huffman trees
depth		db HEAP_SIZE dup(?)	; Depth of each subtree
base_length	dd LENGTH_CODES dup(?)	; First normalized length for each code
length_code	db MAX_MATCH-MIN_MATCH+1 dup(?)
dist_code	db 512 dup(?)
base_dist	dd D_CODES dup(?)	; First normalized distance for each code
l_buf		db LIT_BUFSIZE dup(?)	; buffer for literals/lengths
d_buf		dd DIST_BUFSIZE dup(?)	; buffer for distances
flag_buf	db LIT_BUFSIZE/8 dup(?)
head_buf	dw HASH_SIZE dup(?)
prev_buf	dw 10000h dup(?)
S_DEFLATE	ENDS

	.data

bk		dd 0
bb		dd 0
window		equ <STDI.ios_bp>
file_method	db 0,0,0,0
config_table	label DWORD
		;
		;      good lazy nice chain
		dd	 0,   0,   0,	 0 ; 0 - store only
		dd	 4,   4,   8,	 4 ; 1 - maximum speed, no lazy matches
		dd	 4,   5,  16,	 8 ; 2
		dd	 4,   6,  32,	32 ; 3
		dd	 4,   4,  16,	16 ; 4 - lazy matches
		dd	 8,  16,  32,	32 ; 5
		dd	 8,  16, 128,  128 ; 6
		dd	 8,  32, 128,  256 ; 7
		dd	32, 128, 258, 1024 ; 8
		dd	32, 258, 258, 4096 ; 9 - maximum compression

bl_order	db 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15
		ALIGN	4
bl_count	dd MAX_BITS+1 dup(0)
extra_lbits	dd 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0
extra_dbits	dd 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13
extra_blbits	dd 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7

l_desc		TREE_DESC <0,0,offset extra_lbits,LITERALS+1,L_CODES,MAX_BITS,0>
d_desc		TREE_DESC <0,0,offset extra_dbits,0,D_CODES,MAX_BITS,0>
bl_desc		TREE_DESC <0,0,offset extra_blbits,0,BL_CODES,MAX_BL_BITS,0>

	.code

	OPTION	PROC: PRIVATE
	ASSUME	ebp:  PTR S_DEFLATE

clear_hash PROC
	push	edi
	mov	edi,[ebp].head
	mov	ecx,HASH_SIZE
	xor	eax,eax
	rep	stosw
	pop	edi
	ret
clear_hash ENDP

clear_bl_count PROC
	push	edi
	lea	edi,bl_count
	mov	ecx,MAX_BITS+1
	xor	eax,eax
	rep	stosd
	pop	edi
	ret
clear_bl_count ENDP

flush_buf PROC
	mov	eax,[ebp].fb_buf
	mov	ecx,[ebp].fb_stored_ln
	test	ecx,ecx
	jz	flush_eof
	iowrite( addr STDO, eax, ecx )
	ret
flush_eof:
	inc	eax
	ret
flush_buf ENDP

putshort PROC
	push	eax
	mov	eax,esp
	iowrite( addr STDO, eax, 2 )
	pop	edx
	jz	@F
	mov	eax,1
@@:
	ret
putshort ENDP

gen_bitlen PROC USES esi edi ebx
	mov	esi,eax			; the tree descriptor
	call	clear_bl_count
	;
	; number of elements with bit length too large
	;
	mov	[ebp].gb_overflow,eax
	;
	; In a first pass, compute the optimal bit lengths (which may
	; overflow in the case of the bit length tree).
	;
	mov	ebx,[esi].TREE_DESC.td_dyn_tree
	mov	eax,[ebp].heap_max
	mov	eax,[ebp+eax*4].heap
	mov	[ebx+eax*4].CT_DATA.ct_len,0	; root of the heap
	mov	ecx,[ebp].heap_max
	inc	ecx
	jmp	next
lupe:
	mov	edx,[ebp+ecx*4].heap
	movzx	eax,[ebx+edx*4].CT_DATA.ct_dad
	movzx	eax,[ebx+eax*4].CT_DATA.ct_len
	inc	eax
	cmp	eax,[esi].TREE_DESC.td_max_length
	jbe	@F
	mov	eax,[esi].TREE_DESC.td_max_length
	inc	[ebp].gb_overflow
@@:
	mov	[ebp].gb_bits,eax
	mov	[ebx+edx*4].CT_DATA.ct_len,ax
	cmp	edx,[esi].TREE_DESC.td_max_code
	ja	continue			; not a leaf node
	inc	bl_count[eax*4]
	sub	edi,edi
	mov	eax,[esi].TREE_DESC.td_extra_base
	xchg	eax,edx
	cmp	eax,edx
	jb	@F
	mov	edi,eax
	sub	eax,edx
	shl	eax,2
	add	eax,[esi].TREE_DESC.td_extra_bits
	mov	eax,[eax]
	xchg	eax,edi
@@:
	push	eax
	movzx	eax,[ebx+eax*4].CT_DATA.ct_freq
	push	eax
	mov	edx,edi
	add	edx,[ebp].gb_bits
	mul	edx
	add	[ebp].opt_len,eax
	pop	eax
	pop	edx
	cmp	[esi].TREE_DESC.td_static_tree,0
	je	continue
	shl	edx,2
	add	edx,[esi].TREE_DESC.td_static_tree
	movzx	edx,[edx].CT_DATA.ct_len
	add	edx,edi
	mul	edx
	add	[ebp].static_len,eax
continue:
	inc	ecx
next:
	cmp	ecx,HEAP_SIZE
	jb	lupe
	mov	ecx,[ebp].gb_overflow
	xor	eax,eax
	test	ecx,ecx
	jne	overflow
toend:
	ret
overflow:
	;
	; Find the first bit length which could increase:
	;
	mov	edx,[esi].TREE_DESC.td_max_length
	dec	edx
@@:
	cmp	bl_count[edx*4],eax
	jne	@F
	dec	edx
	jmp	@B
@@:
	dec	bl_count[edx*4]		; move one leaf down the tree
	mov	eax,2
	add	bl_count[edx*4+4],eax	; move one overflow item as its brother
	mov	edx,[esi].TREE_DESC.td_max_length
	dec	bl_count[edx*4]
	;
	; The brother of the overflow item also moves one step up,
	; but this does not affect bl_count[max_length]
	;
	sub	ecx,eax
	sub	eax,eax
	cmp	ecx,eax
	jg	overflow
	;
	; Now recompute all bit lengths, scanning in increasing frequency.
	; h is still equal to HEAP_SIZE. (It is simpler to reconstruct all
	; lengths instead of fixing only the wrong ones. This idea is taken
	; from 'ar' written by Haruhiko Okumura.)
	;
	mov	edx,[esi].TREE_DESC.td_max_length
	mov	ecx,HEAP_SIZE
recompute:
	mov	ebx,bl_count[edx*4]
do:
	test	ebx,ebx
	jz	max_next
	dec	ecx
	mov	eax,[ebp+ecx*4].heap
	cmp	eax,[esi].TREE_DESC.td_max_code
	ja	do
	mov	edi,[esi].TREE_DESC.td_dyn_tree
	lea	edi,[edi+eax*4]
	movzx	eax,[edi].CT_DATA.ct_len
	cmp	eax,edx
	je	while_n
	mov	[edi].CT_DATA.ct_len,dx
	xchg	eax,edx
	sub	eax,edx
	movzx	edx,[edi].CT_DATA.ct_freq
	imul	edx
	add	[ebp].opt_len,eax
	movzx	edx,[edi].CT_DATA.ct_len
while_n:
	dec	ebx
	jnz	do
max_next:
	dec	edx
	jnz	recompute
	jmp	toend
gen_bitlen ENDP

gen_codes PROC USES esi edi
	push	edx		; largest code with non zero frequency
	mov	esi,eax		; the tree to decorate
	lea	edi,[ebp].gc_next_code
	xor	edx,edx		; running code value
	mov	ebx,edx		; bit index
	mov	ecx,MAX_BITS
	;
	; The distribution counts are first used to generate the code values
	; without bit reversal.
	;
@@:
	mov	eax,bl_count[ebx]
	add	ebx,4
	add	eax,edx
	add	eax,eax
	mov	edx,eax
	mov	[edi+ebx],eax
	dec	ecx
	jnz	@B
	pop	ecx
	inc	ecx
lupe:
	movzx	eax,[esi].CT_DATA.ct_len
	test	eax,eax
	jz	next
	movzx	ebx,WORD PTR [edi+eax*4]
	inc	WORD PTR [edi+eax*4]
	;
	; Now reverse the bits
	;
	mov	edx,eax
	xor	eax,eax
@@:
	shr	ebx,1
	adc	eax,0
	shl	eax,1
	dec	edx
	jnz	@B
	shr	eax,1
	mov	[esi].CT_DATA.ct_code,ax
next:
	add	esi,SIZE CT_DATA
	dec	ecx
	jnz	lupe
	ret
gen_codes ENDP

;
; Construct one Huffman tree and assigns the code bit strings and lengths.
; Update the total bit length for the current block.
;
build_tree PROC
	push	esi
	push	edi
	mov	esi,eax		; the tree descriptor
	mov	edx,-1		; largest code with non zero frequency
	xor	ecx,ecx
	mov	[ebp].heap_len,ecx
	mov	[ebp].heap_max,HEAP_SIZE
	mov	edi,ecx
	mov	ebx,[esi].TREE_DESC.td_dyn_tree
	jmp	start
@@:
	mov	[ebx].CT_DATA.ct_len,ax
	jmp	next
lupe:
	movzx	eax,[ebx].CT_DATA.ct_freq
	test	eax,eax
	jz	@B
	mov	[ebp+ecx].depth,0
	inc	edi
	mov	[ebp+edi*4].heap,ecx
	mov	edx,ecx
next:
	add	ebx,SIZE CT_DATA
	inc	ecx
start:
	cmp	ecx,[esi].TREE_DESC.td_elems
	jb	lupe
	mov	[ebp].bt_next_node,ecx
	;
	; The pkzip format requires that at least one distance code exists,
	; and that at least one bit should be sent even if there is only one
	; possible code. So to avoid special checks later on we force at least
	; two codes of non zero frequency.
	;
	mov	ecx,2
while_b:
	cmp	edi,ecx
	jnb	build_tree_b_end
	xor	eax,eax
	cmp	edx,ecx
	jnl	@F
	inc	edx
	mov	eax,edx
@@:
	inc	edi
	mov	[ebp+edi*4].heap,eax
	mov	ebx,[esi].TREE_DESC.td_dyn_tree
	mov	[ebx+eax*4].CT_DATA.ct_freq,1
	mov	[ebp+eax].depth,0
	dec	[ebp].opt_len
	mov	ebx,[esi].TREE_DESC.td_static_tree
	test	ebx,ebx
	je	while_b
	movzx	eax,[ebx+eax*4].CT_DATA.ct_len
	sub	[ebp].static_len,eax
	jmp	while_b
build_tree_b_end:
	mov	eax,edx
	mov	[esi].TREE_DESC.td_max_code,eax
	mov	[ebp].bt_max_code,eax
	mov	[ebp].heap_len,edi
	;
	; The elements heap[heap_len/2+1 .. heap_len] are leaves of the tree,
	; establish sub-heaps of increasing lengths:
	;
	shr	edi,1
	jz	do
@@:
	mov	eax,[esi].TREE_DESC.td_dyn_tree
	mov	edx,edi
	call	pqdownheap
	dec	edi
	jnz	@B
	;
	; Construct the Huffman tree by repeatedly combining the least two
	; frequent nodes.
	;
do:
	mov	eax,[ebp].heap_len
	dec	[ebp].heap_len
	mov	eax,[ebp+eax*4].heap
	mov	edi,[ebp].heap[4]
	mov	[ebp].heap[4],eax
	mov	eax,[esi].TREE_DESC.td_dyn_tree
	mov	edx,SMALLEST
	call	pqdownheap
	mov	eax,[ebp].heap_max
	dec	eax
	mov	ebx,eax
	dec	eax
	mov	[ebp].heap_max,eax
	mov	edx,[ebp].heap[4]
	mov	[ebp+ebx*4].heap,edi
	mov	[ebp+eax*4].heap,edx
	;
	; Create a new node father of n and m
	;
	push	edi
	mov	al,[ebp+eax].depth
	mov	ah,[ebp+edi].depth
	cmp	ah,al
	jb	@F
	mov	al,ah
@@:
	inc	al
	mov	ecx,[ebp].bt_next_node
	mov	[ebp+ecx].depth,al
	mov	ebx,[esi].TREE_DESC.td_dyn_tree
	mov	ax,[ebx+edx*4].CT_DATA.ct_freq
	add	ax,[ebx+edi*4].CT_DATA.ct_freq
	mov	[ebx+ecx*4].CT_DATA.ct_freq,ax
	mov	eax,ecx
	mov	[ebx+edx*4].CT_DATA.ct_dad,ax
	mov	[ebx+edi*4].CT_DATA.ct_dad,ax
	pop	edi
	mov	[ebp].heap[4],eax
	inc	eax
	mov	[ebp].bt_next_node,eax
	mov	eax,ebx
	mov	edx,SMALLEST
	call	pqdownheap
	cmp	[ebp].heap_len,2
	jae	do
	mov	eax,[ebp].heap[4*SMALLEST]
	dec	[ebp].heap_max
	mov	ebx,[ebp].heap_max
	mov	[ebp+ebx*4].heap,eax
	;
	; At this point, the fields freq and dad are set. We can now
	; generate the bit lengths.
	;
	mov	eax,esi
	call	gen_bitlen
	;
	; The field len is now set, we can generate the bit codes
	;
	mov	eax,[esi].TREE_DESC.td_dyn_tree
	mov	edx,[ebp].bt_max_code
	pop	edi
	pop	esi
	jmp	gen_codes
build_tree ENDP

smaller PROC		; (tree, n, m)
	push	edi	; esi == tree
	push	ecx	; eax == n
	mov	ecx,[ebp+edx*4].heap
	mov	di,[esi+eax*4].CT_DATA.ct_freq
	mov	ah,[ebp+eax].depth
	mov	al,[ebp+ecx].depth
	mov	cx,[esi+ecx*4].CT_DATA.ct_freq
	cmp	di,cx
	pop	ecx
	pop	edi
	jb	@1
	jne	@0
	cmp	ah,al
	ja	@0
@1:
	or	eax,1
	ret
@0:
	xor	eax,eax
	ret
smaller ENDP

pqdownheap PROC USES esi edi
	mov	esi,eax ; the tree to restore
	mov	edi,edx
	add	edx,edx
	mov	ecx,[ebp+edi*4].heap
	.while	edx <= [ebp].heap_len
		.if edx < [ebp].heap_len
			mov eax,[ebp+edx*4+4].heap
			.if smaller()
				inc edx
			.endif
		.endif
		mov	eax,ecx
		.break .if smaller()
		mov	eax,[ebp+edx*4].heap
		mov	[ebp+edi*4].heap,eax
		mov	edi,edx
		add	edx,edx
	.endw
	mov	[ebp+edi*4].heap,ecx
	ret
pqdownheap ENDP

send_bits PROC USES esi edi
	mov	esi,eax
	mov	edi,edx
	mov	ebx,[ebp].bi_buf
	mov	ecx,[ebp].bi_valid
	shl	eax,cl
	or	eax,ebx
	add	ecx,edx
	mov	[ebp].bi_buf,eax
	mov	[ebp].bi_valid,ecx
	cmp	ecx,16
	jbe	@F
	call	putshort
	mov	eax,[ebp].bi_valid
	sub	eax,16
	mov	[ebp].bi_valid,eax
	mov	ecx,edi
	sub	ecx,eax
	shr	esi,cl
	mov	[ebp].bi_buf,esi
@@:
	ret
send_bits ENDP

s_tree_init PROC
	mov	[ebp].st_max_code,edx
	mov	edi,eax
	xor	eax,eax
	mov	esi,eax
	dec	eax
	mov	[ebp].st_prevlen,eax
	movzx	eax,[edi].CT_DATA.ct_len
	mov	[ebp].st_nextlen,eax
	mov	[ebp].st_count,esi
	mov	[ebp].st_max_count,7
	mov	[ebp].st_min_count,4
	test	eax,eax
	jnz	@F
	mov	[ebp].st_max_count,138
	dec	[ebp].st_min_count
@@:
	ret
s_tree_init ENDP

s_tree_loop PROC
	cmp	esi,[ebp].st_max_code
	ja	@0
	mov	eax,[ebp].st_nextlen
	mov	[ebp].st_curlen,eax
	mov	eax,esi
	inc	eax
	movzx	eax,[edi+eax*4].CT_DATA.ct_len
	mov	[ebp].st_nextlen,eax
	inc	[ebp].st_count
	mov	ebx,[ebp].st_count
	cmp	ebx,[ebp].st_max_count
	jae	@1
	cmp	eax,[ebp].st_curlen
	jne	@1
	inc	esi
	jmp	s_tree_loop
@1:
	or	al,1
	ret
@0:
	xor	eax,eax
	ret
s_tree_loop ENDP

s_tree_set PROC
	inc	esi
	mov	eax,[ebp].st_curlen
	mov	[ebp].st_prevlen,eax
	mov	[ebp].st_count,0
	mov	[ebp].st_max_count,7
	mov	[ebp].st_min_count,4
	mov	eax,[ebp].st_nextlen
	test	eax,eax
	jz	@3
	cmp	eax,[ebp].st_curlen
	jne	@2
	dec	[ebp].st_max_count
@1:
	dec	[ebp].st_min_count
@2:
	ret
@3:
	mov	[ebp].st_max_count,138
	jmp	@1
s_tree_set ENDP

scan_tree PROC USES esi edi
	call	s_tree_init
	inc	edx
	mov	[edi+edx*4].CT_DATA.ct_len,-1
lupe:
	call	s_tree_loop
	jz	toend
	cmp	ebx,[ebp].st_min_count
	jae	@F
	lea	ebx,[ebp].bl_tree
	mov	ecx,[ebp].st_curlen
	mov	eax,[ebp].st_count
	add	[ebx+ecx*4].CT_DATA.ct_freq,ax
next:
	call	s_tree_set
	jmp	lupe
@@:
	mov	eax,[ebp].st_curlen
	test	eax,eax
	jz	l1
	cmp	eax,[ebp].st_prevlen
	je	@F
	inc	[ebp+eax*4].bl_tree.CT_DATA.ct_freq
@@:
	mov	eax,REP_3_6*4
	jmp	l2
l1:
	mov	eax,REPZ_11_138*4
	cmp	[ebp].st_count,10
	ja	l2
	mov	eax,REPZ_3_10*4
l2:
	inc	[ebp+eax].bl_tree.CT_DATA.ct_freq
	jmp	next
toend:
	ret
scan_tree ENDP

send_tree PROC USES esi edi
	call	s_tree_init
	jmp	around
toend:
	ret
do:
	mov	eax,[ebp].st_curlen
	movzx	edx,[ebp+eax*4].bl_tree.CT_DATA.ct_len
	movzx	eax,[ebp+eax*4].bl_tree.CT_DATA.ct_code
	call	send_bits
	dec	[ebp].st_count
	jnz	do
continue:
	call	s_tree_set
around:
	call	s_tree_loop
	jz	toend
	cmp	ebx,[ebp].st_min_count
	jb	do
	mov	eax,[ebp].st_curlen
	test	eax,eax
	jz	send_REP_3_10
	cmp	eax,[ebp].st_prevlen
	je	send_REP_3_6
	movzx	edx,[ebp+eax*4].bl_tree.CT_DATA.ct_len
	movzx	eax,[ebp+eax*4].bl_tree.CT_DATA.ct_code
	call	send_bits
	dec	[ebp].st_count
send_REP_3_6:
	mov	eax,[ebp].st_count
	movzx	eax,[ebp].bl_tree.CT_DATA.ct_code[4*REP_3_6]
	movzx	edx,[ebp].bl_tree.CT_DATA.ct_len[4*REP_3_6]
	call	send_bits
	mov	eax,[ebp].st_count
	sub	eax,3
	mov	edx,2
	call	send_bits
	jmp	continue
send_REP_3_10:
	cmp	[ebp].st_count,10
	ja	send_REPZ_11_138
	movzx	eax,[ebp].bl_tree.CT_DATA.ct_code[4*REPZ_3_10]
	movzx	edx,[ebp].bl_tree.CT_DATA.ct_len[4*REPZ_3_10]
	call	send_bits
	mov	eax,[ebp].st_count
	sub	eax,3
	mov	edx,3
	call	send_bits
	jmp	continue
send_REPZ_11_138:
	movzx	eax,[ebp].bl_tree.CT_DATA.ct_code[4*REPZ_11_138]
	movzx	edx,[ebp].bl_tree.CT_DATA.ct_len[4*REPZ_11_138]
	call	send_bits
	mov	eax,[ebp].st_count
	sub	eax,11
	mov	edx,7
	call	send_bits
	jmp	continue
send_tree ENDP

build_bl_tree PROC
	lea	eax,[ebp].dyn_ltree
	mov	edx,l_desc.TREE_DESC.td_max_code
	call	scan_tree
	lea	eax,[ebp].dyn_dtree
	mov	edx,d_desc.TREE_DESC.td_max_code
	call	scan_tree
	mov	eax,offset bl_desc
	call	build_tree
	mov	ecx,BL_CODES-1
@@:
	cmp	ecx,4
	jb	@F
	movzx	eax,bl_order[ecx]
	movzx	eax,[ebp+eax*4].bl_tree.CT_DATA.ct_len
	test	eax,eax
	jnz	@F
	dec	ecx
	jmp	@B
@@:
	mov	eax,3
	inc	ecx
	imul	ecx
	dec	ecx
	add	eax,5+5+4
	add	[ebp].opt_len,eax
	mov	eax,ecx
	ret
build_bl_tree ENDP

send_all_trees PROC
	push	esi	; ax: lcodes
	push	edi	; dx: dcodes
	push	ebx	; bx: blcodes
	mov	esi,eax
	mov	edi,edx
	sub	eax,257
	mov	edx,5
	call	send_bits
	mov	eax,edi
	dec	eax
	mov	edx,5
	call	send_bits
	pop	eax
	push	edi
	push	esi
	push	eax
	mov	edx,4
	sub	eax,edx
	call	send_bits
	pop	edi
	xor	esi,esi
@@:
	cmp	esi,edi
	jnb	@F
	movzx	eax,bl_order[esi]
	movzx	eax,[ebp+eax*4].bl_tree.CT_DATA.ct_len
	mov	edx,3
	call	send_bits
	inc	esi
	jmp	@B
@@:
	pop	edx
	dec	edx
	lea	eax,[ebp].dyn_ltree
	call	send_tree
	lea	eax,[ebp].dyn_dtree
	pop	edx
	dec	edx
	call	send_tree
	pop	edi
	pop	esi
	ret
send_all_trees ENDP

ct_init PROC
	push	esi
	push	edi
	mov	file_method,METHOD_DEFLATE
	xor	esi,esi
	mov	edx,esi
	;
	; Initialize the mapping length (0..255) -> length code (0..28)
	;
init_length:
	cmp	edx,LENGTH_CODES-1
	jnb	length_end
	mov	[ebp+edx*4].base_length,esi
	xor	ebx,ebx
@@:
	mov	ecx,extra_lbits[edx*4]
	mov	eax,1
	shl	eax,cl
	cmp	ebx,eax
	jnb	@F
	mov	[ebp+esi].length_code,dl
	inc	esi
	inc	ebx
	jmp	@B
@@:
	inc	edx
	jmp	init_length
length_end:
	;
	; Note that the length 255 (match length 258) can be represented
	; in two different ways: code 284 + 5 bits or code 285, so we
	; overwrite length_code[255] to use the best encoding:
	;
	dec	esi
	mov	[ebp+esi].length_code,dl
	;
	; Initialize the mapping dist (0..32K) -> dist code (0..29)
	;
	xor	esi,esi
	mov	edx,esi
init_dist:
	cmp	edx,16
	jnb	dist_end
	mov	[ebp+edx*4].base_dist,esi
	xor	ebx,ebx
@@:
	mov	ecx,extra_dbits[edx*4]
	mov	eax,1
	shl	eax,cl
	cmp	ebx,eax
	jnb	@F
	mov	[ebp+esi].dist_code,dl
	inc	esi
	inc	ebx
	jmp	@B
@@:
	inc	edx
	jmp	init_dist
dist_end:
	shr	esi,7
init_dist_02:
	cmp	edx,D_CODES
	jnb	dist_end_02
	mov	eax,esi
	shl	eax,7
	mov	[ebp+edx*4].base_dist,eax
	xor	ebx,ebx
@@:
	mov	ecx,extra_dbits[edx*4]
	sub	ecx,7
	mov	eax,1
	shl	eax,cl
	cmp	ebx,eax
	jnb	@F
	mov	[ebp+esi].dist_code[256],dl
	inc	esi
	inc	ebx
	jmp	@B
@@:
	inc	edx
	jmp	init_dist_02
dist_end_02:
	call	clear_bl_count
	lea	edi,[ebp].static_ltree
	mov	ecx,144
	mov	eax,8
	mov	ebx,8
	call	@F
	mov	ecx,112
	inc	eax
	inc	ebx
	call	@F
	mov	ecx,24
	mov	al,7
	mov	bl,7
	call	@F
	mov	ecx,8
	inc	eax
	mov	bl,8
	call	@F
	jmp	codes
@@:
	inc	bl_count[ebx*4]
	mov	[edi].CT_DATA.ct_len,ax
	add	edi,SIZE CT_DATA
	dec	ecx
	jnz	@B
	ret
codes:
	lea	eax,[ebp].static_ltree
	mov	edx,L_CODES+1
	call	gen_codes
	xor	esi,esi
	lea	edi,[ebp].static_dtree
cloop:
	mov	edx,5
	mov	[edi].CT_DATA.ct_len,dx
	mov	ebx,esi
	xor	eax,eax
@@:
	shr	ebx,1
	adc	eax,0
	shl	eax,1
	dec	edx
	jnz	@B
	shr	eax,1
	mov	[edi].CT_DATA.ct_code,ax
	add	edi,SIZE CT_DATA
	inc	esi
	cmp	esi,D_CODES
	jb	cloop
	pop	edi
	pop	esi
ct_init ENDP

init_block PROC
	xor	eax,eax
	lea	ebx,[ebp].dyn_ltree
	mov	ecx,L_CODES
@@:
	mov	[ebx].CT_DATA.ct_freq,ax
	add	ebx,SIZE CT_DATA
	dec	ecx
	jnz	@B
	lea	ebx,[ebp].dyn_dtree
	mov	ecx,D_CODES
@@:
	mov	[ebx].CT_DATA.ct_freq,ax
	add	ebx,SIZE CT_DATA
	dec	ecx
	jnz	@B
	lea	ebx,[ebp].bl_tree
	mov	ecx,BL_CODES
@@:
	mov	[ebx].CT_DATA.ct_freq,ax
	add	ebx,SIZE CT_DATA
	dec	ecx
	jnz	@B
	mov	[ebp].dyn_ltree[END_BLOCK*4].CT_DATA.ct_freq,1
	mov	[ebp].opt_len,eax
	mov	[ebp].static_len,eax
	mov	[ebp].last_lit,eax
	mov	[ebp].last_dist,eax
	mov	[ebp].last_flags,eax
	mov	[ebp].flags,al
	inc	eax
	mov	[ebp].flag_bit,al
	ret
init_block ENDP

flush_block PROC
	mov	[ebp].fb_eof,eax
	xor	eax,eax
	cmp	[ebp].block_start,eax
	jl	@F
	mov	eax,window
	add	eax,[ebp].block_start
@@:
	mov	[ebp].fb_buf,eax
	mov	eax,[ebp].str_start
	sub	eax,[ebp].block_start
	mov	[ebp].fb_stored_ln,eax
	push	esi
	push	edi
	mov	al,[ebp].flags
	mov	ebx,[ebp].last_flags
	mov	[ebp].flag_buf[ebx],al
	mov	eax,offset l_desc
	call	build_tree
	mov	eax,offset d_desc
	call	build_tree
	call	build_bl_tree
	mov	esi,eax
	mov	eax,[ebp].opt_len
	add	eax,3+7
	shr	eax,3
	mov	[ebp].fb_opt_len,eax
	mov	eax,[ebp].static_len
	add	eax,3+7
	shr	eax,3
	mov	[ebp].fb_static_ln,eax
	cmp	eax,[ebp].fb_opt_len
	ja	@F
	mov	[ebp].fb_opt_len,eax
@@:
	mov	eax,[ebp].fb_opt_len
	cmp	[ebp].fb_stored_ln,eax
	ja	@F
	xor	eax,eax
	cmp	[ebp].fb_eof,eax
	je	@F
	cmp	file_method,al
	je	@F
	cmp	[ebp].cmpr_bytelen,eax
	jne	@F
	cmp	[ebp].cmpr_lenbits,eax
	jne	@F
	call	copy_block
	jz	toend
	mov	eax,[ebp].fb_stored_ln
	mov	[ebp].cmpr_bytelen,eax
	mov	file_method,METHOD_STORE
	jmp	done
@@:
	mov	eax,[ebp].fb_buf
	test	eax,eax
	jz	@F
	mov	eax,[ebp].fb_stored_ln
	add	eax,4
	cmp	eax,[ebp].fb_opt_len
	ja	@F
	mov	eax,[ebp].fb_eof
	mov	edx,3
	call	send_bits
	mov	eax,[ebp].cmpr_lenbits
	add	eax,3+7
	shr	eax,3
	add	eax,[ebp].fb_stored_ln
	add	eax,4
	add	[ebp].cmpr_bytelen,eax
	xor	eax,eax
	mov	[ebp].cmpr_lenbits,eax
	inc	eax
	call	copy_block
	jz	toend
	jmp	done
@@:
	mov	eax,[ebp].fb_static_ln
	cmp	eax,[ebp].fb_opt_len
	jne	@F
	mov	eax,[ebp].fb_eof
	add	eax,STATIC_TREES*2
	mov	edx,3
	call	send_bits
	lea	eax,[ebp].static_ltree
	lea	edx,[ebp].static_dtree
	call	compress_block
	mov	eax,[ebp].static_len
	jmp	@04
@@:
	mov	eax,[ebp].fb_eof
	add	eax,DYN_TREES*2
	mov	edx,3
	call	send_bits
	mov	eax,l_desc.TREE_DESC.td_max_code
	inc	eax
	mov	edx,d_desc.TREE_DESC.td_max_code
	inc	edx
	mov	ebx,esi
	inc	ebx
	call	send_all_trees
	lea	eax,[ebp].dyn_ltree
	lea	edx,[ebp].dyn_dtree
	call	compress_block
	mov	eax,[ebp].opt_len
@04:
	add	eax,3
	add	eax,[ebp].cmpr_lenbits
	mov	ecx,eax
	and	eax,7
	mov	[ebp].cmpr_lenbits,eax
	mov	eax,ecx
	shr	eax,3
	add	[ebp].cmpr_bytelen,eax
done:
	call	init_block
	mov	eax,[ebp].fb_eof
	test	eax,eax
	jz	@F
	call	bi_windup
	jz	toend
	add	[ebp].cmpr_lenbits,7
@@:
	xor	eax,eax
	inc	eax
toend:
	pop	edi
	pop	esi
	ret
flush_block ENDP

;
; Save the match info and tally the frequency counts. Return true if
; the current block must be flushed.
;
; DX match length-MIN_MATCH or unmatched char (if dist==0)
; AX distance of matched string
;
ct_tally PROC USES esi edi
	mov	ecx,[ebp].last_lit
	mov	[ebp+ecx].l_buf,dl
	inc	[ebp].last_lit
	test	eax,eax
	jnz	@F
	inc	[ebp+edx*4].dyn_ltree.CT_DATA.ct_freq
	jmp	around
@@:
	;
	; Here, DX is the match length - MIN_MATCH
	;
	dec	eax
	mov	edi,edx
	mov	edx,eax
	movzx	eax,[ebp+edi].length_code
	add	eax,LITERALS+1
	inc	[ebp+eax*4].dyn_ltree.CT_DATA.ct_freq
	mov	eax,256
	mov	edi,edx
	cmp	edx,eax
	jb	@F
	shr	edi,7
	add	edi,eax
@@:
	movzx	eax,[edi+ebp].dist_code
	inc	[ebp+eax*4].dyn_dtree.CT_DATA.ct_freq
	mov	eax,[ebp].last_dist
	inc	[ebp].last_dist
	mov	[ebp+eax*4].d_buf,edx
	mov	al,[ebp].flag_bit
	or	[ebp].flags,al
around:
	shl	[ebp].flag_bit,1
	;
	; Output the flags if they fill a byte:
	;
	mov	eax,[ebp].last_lit
	and	eax,7
	jnz	@F
	mov	al,[ebp].flags
	mov	edi,[ebp].last_flags
	inc	[ebp].last_flags
	mov	[ebp].flag_buf[edi],al
	mov	[ebp].flags,0
	mov	[ebp].flag_bit,1
@@:
	;
	; Try to guess if it is profitable to stop the current block here
	;
	cmp	[ebp].compr_level,2
	jbe	done
	mov	eax,[ebp].last_lit
	mov	edx,eax
	and	edx,0FFFh
	jnz	done
	;
	; Compute an upper bound for the compressed length
	;
	shl	eax,3
	mov	ebx,eax
	xor	ecx,ecx
@@:
	movzx	eax,[ebp+ecx].dyn_dtree.CT_DATA.ct_freq
	mov	edi,extra_dbits[ecx]
	add	edi,5
	mul	edi
	add	ebx,eax
	add	ecx,4
	cmp	ecx,D_CODES*4
	jb	@B
	mov	eax,ebx
	shr	eax,3
	mov	edi,eax
	mov	eax,[ebp].last_lit
	shr	eax,1
	;
	; if (last_dist < last_lit/2 && out_length < in_length/2) return 1;
	;
	cmp	[ebp].last_dist,eax
	jnb	done
	mov	eax,[ebp].str_start
	sub	eax,[ebp].block_start
	and	eax,0000FFFFh
	shr	eax,1
	cmp	edi,eax
	jnb	done
	mov	eax,1
	jmp	toend
done:
	mov	eax,1
	cmp	[ebp].last_lit,LIT_BUFSIZE-1
	je	toend
	cmp	[ebp].last_dist,DIST_BUFSIZE
	je	toend
	dec	eax
toend:
	test	eax,eax
	ret
ct_tally ENDP

compress_block PROC USES esi edi
	mov	esi,eax
	mov	edi,edx
	xor	eax,eax
	mov	[ebp].cb_lx,eax
	mov	[ebp].cb_dx,eax
	mov	[ebp].cb_fx,eax
	mov	[ebp].cb_flag,al
	cmp	[ebp].last_lit,eax
	je	toend
do:
	mov	edx,[ebp].cb_lx
	test	edx,7
	jnz	@F
	mov	eax,[ebp].cb_fx
	inc	[ebp].cb_fx
	mov	al,[ebp].flag_buf[eax]
	mov	[ebp].cb_flag,al
@@:
	inc	[ebp].cb_lx
	movzx	eax,[ebp+edx].l_buf
	mov	[ebp].cb_lc,eax
	test	[ebp].cb_flag,1
	jnz	@F
	movzx	edx,[esi+eax*4].CT_DATA.ct_len
	movzx	eax,[esi+eax*4].CT_DATA.ct_code
	call	send_bits
	jmp	done
@@:
	mov	eax,[ebp].cb_lc
	movzx	eax,[ebp+eax].length_code
	mov	[ebp].cb_code,eax
	add	eax,LITERALS+1
	movzx	edx,[esi+eax*4].CT_DATA.ct_len
	movzx	eax,[esi+eax*4].CT_DATA.ct_code
	call	send_bits
	mov	eax,[ebp].cb_code
	mov	eax,extra_lbits[eax*4]
	mov	[ebp].cb_extra,eax
	test	eax,eax
	jz	@F
	mov	edx,eax
	mov	ebx,[ebp].cb_code
	mov	eax,[ebp].cb_lc
	sub	eax,[ebp+ebx*4].base_length
	mov	[ebp].cb_lc,eax
	call	send_bits
@@:
	mov	eax,[ebp].cb_dx
	inc	[ebp].cb_dx
	lea	ebx,[ebp].d_buf
	mov	eax,[ebx+eax*4]
	mov	[ebp].cb_dist,eax
	mov	ebx,256
	cmp	eax,ebx
	jb	@F
	shr	eax,7
	add	eax,ebx
@@:
	movzx	eax,[ebp+eax].dist_code
	mov	[ebp].cb_code,eax
	movzx	edx,[edi+eax*4].CT_DATA.ct_len
	movzx	eax,[edi+eax*4].CT_DATA.ct_code
	call	send_bits
	mov	ebx,[ebp].cb_code
	mov	eax,extra_dbits[ebx*4]
	mov	[ebp].cb_extra,eax
	test	eax,eax
	jz	done
	mov	edx,eax
	mov	eax,[ebp].cb_dist
	sub	eax,[ebp+ebx*4].base_dist
	mov	[ebp].cb_dist,eax
	call	send_bits
done:
	shr	[ebp].cb_flag,1
	mov	eax,[ebp].cb_lx
	cmp	eax,[ebp].last_lit
	jb	do
toend:
	movzx	eax,[esi+4*END_BLOCK].CT_DATA.ct_code
	movzx	edx,[esi+4*END_BLOCK].CT_DATA.ct_len
	call	send_bits
	ret
compress_block ENDP

;
; Write out any remaining bits in an incomplete byte.
;
bi_windup PROC
	xor	eax,eax
	mov	ecx,[ebp].bi_valid
	mov	edx,[ebp].bi_buf
	mov	[ebp].bi_buf,eax
	mov	[ebp].bi_valid,eax
	test	ecx,ecx
	jz	@F
	mov	al,dl
	call	oputc
	jz	error
	cmp	ecx,8
	jbe	@F
	mov	al,dh
	call	oputc
error:
	ret
@@:
	inc	eax
	ret
bi_windup ENDP

copy_block PROC USES esi
	mov	esi,eax
	call	bi_windup
	jz	toend
	test	esi,esi
	jz	@F
	mov	eax,[ebp].fb_stored_ln
	call	putshort
	jz	toend
	mov	eax,[ebp].fb_stored_ln
	not	eax
	call	putshort
	jz	toend
@@:
	call	flush_buf
toend:
	ret
copy_block ENDP

update_hash PROC
	mov	edx,window
	movzx	edx,BYTE PTR [edx+eax]
	mov	eax,[ebp].ins_h
	shl	ax,H_SHIFT
	xor	ax,dx
	and	eax,HASH_MASK
	mov	[ebp].ins_h,eax
	ret
update_hash ENDP
;
; Insert string s in the dictionary and set match_head to the previous head
; of the hash chain (the most recent string with same hash key). Return
; the previous length of the hash chain.
;
insert_string PROC
	mov	ebx,[ebp].str_start
	add	ebx,MIN_MATCH-1
	mov	eax,ebx
	call	update_hash
	sub	ebx,MIN_MATCH-1
	xchg	eax,ebx
	movzx	esi,[ebp].head_buf[ebx*2]
	mov	[ebp].head_buf[ebx*2],ax
	mov	ebx,[ebp].prev
	and	eax,WMASK
	mov	[ebx+eax*2],si
	ret
insert_string ENDP
;
; Note: window and prev is segment aligned to SSSS0000
;
longest_match PROC USES esi edi
	mov	edi,window
	mov	esi,edi
	mov	si,ax		; current match
	mov	edx,[ebp].str_start
	mov	di,dx
	sub	edx,MAX_DIST
	jae	@F
	sub	edx,edx
@@:
	add	edi,2
	mov	ebx,[ebp].prev_length
	mov	eax,[ebp].max_chain_len
	cmp	ebx,[ebp].good_match
	jb	@F
	shr	eax,2
@@:
	mov	ecx,[ebp].prev		; ECX to address of .prev
	mov	[ebp].lm_chain_length,eax
	mov	cx,[edi-2]		; window[di]
	mov	ax,[ebx+edi-3]		; window[di+bx]
	jmp	scan
loop_l:
	mov	ax,[ebx+edi-3]		; window[di+bx]
loop_s:
	add	si,si			; ********
	mov	cx,si			; prev[si]
	mov	si,[ecx]		; ******
	mov	cx,[edi-2]		; window[di]
	dec	[ebp].lm_chain_length	; *
	jz	toend			; ******************
	cmp	si,dx			;
	jbe	toend			; *******
scan:
	cmp	ax,[ebx+esi-1]		; window[si+bx]
	jne	loop_s			; ****************************
	cmp	cx,[esi]		; window[si]
	jne	loop_s			; **
	add	esi,2			; *
	mov	ecx,(MAX_MATCH-2)/2	; *
	mov	eax,edi			;
	repe	cmpsw			; window[si],window[di]
	je	maxm			; ***
mismatch:
	mov	ecx,[ebp].prev		; restore "segment" of prev
	mov	cl,[edi-2]
	xchg	eax,edi
	sub	cl,[esi-2]
	sub	eax,edi
	sub	esi,2
	sub	esi,eax
	sub	cl,1
	adc	eax,0
	cmp	eax,ebx
	jle	loop_l
	mov	WORD PTR [ebp].match_start,si
	mov	ebx,eax
	cmp	eax,[ebp].nice_match
	jl	loop_l
toend:
	mov	eax,ebx
	ret
maxm:
	cmpsb
	jmp	mismatch
longest_match ENDP

fill_window PROC USES esi edi
do:
	xor	edi,edi
	mov	eax,[ebp].str_start
	mov	edx,eax
	add	eax,[ebp].lookahead
	sub	di,ax
	cmp	di,-1
	je	decdi
	cmp	edx,WSIZE+MAX_DIST
	jb	@F
	xor	eax,eax
	cmp	eax,[ebp].sliding
	je	@F
	mov	eax,window
	lea	edx,[eax+WSIZE]
	memcpy( eax, edx, WSIZE )
	mov	eax,WSIZE
	sub	[ebp].match_start,eax
	sub	[ebp].str_start,eax
	sub	[ebp].block_start,eax
	mov	eax,[ebp].head
	mov	ecx,HASH_SIZE
	call	fill_loop
	mov	eax,[ebp].prev
	mov	ecx,WSIZE
	call	fill_loop
	add	edi,WSIZE
@@:
	xor	eax,eax
	cmp	[ebp].eofile,eax
	jne	toend
	mov	eax,[ebp].str_start
	add	eax,[ebp].lookahead
	mov	WORD PTR STDI.ios_bp,ax
	mov	STDI.ios_size,edi
	xor	eax,eax
	mov	STDI.ios_c,eax
	mov	STDI.ios_i,eax
	ioread( addr STDI )
	mov	WORD PTR STDI.ios_bp,0
	jz	@eof
	add	[ebp].lookahead,eax
	cmp	[ebp].lookahead,MIN_LOOKAHEAD
	jb	do
toend:
	ret
@eof:
	mov	[ebp].eofile,1
	jmp	toend
decdi:
	dec	di
	jmp	@B
fill_loop:
	mov	ebx,eax
next:
	sub	eax,eax
	mov	dx,[ebx]
	cmp	dx,WSIZE
	jb	@F
	mov	ax,dx
	sub	ax,WSIZE
@@:
	mov	[ebx],ax
	add	ebx,2
	dec	ecx
	jnz	next
	retn
fill_window ENDP

deflate_fast PROC USES esi edi
	xor	eax,eax
	mov	esi,eax
	mov	[ebp].d_match_length,eax
	mov	[ebp].prev_length,MIN_MATCH-1
	jmp	do
break:
	inc	eax
	call	flush_block
toend:
	ret
do: ; deflate while lookahead
	xor	eax,eax
	mov	ecx,[ebp].lookahead
	cmp	ecx,eax
	je	break
	cmp	ecx,MIN_MATCH
	jb	no_string
	call	insert_string
no_string:
	test	esi,esi
	jz	check_length
	mov	eax,[ebp].str_start
	sub	eax,esi
	cmp	eax,MAX_DIST
	ja	check_length
	mov	eax,[ebp].lookahead
	cmp	[ebp].nice_match,eax
	jna	get_length
	mov	[ebp].nice_match,eax
get_length:
	mov	eax,esi
	call	longest_match
	mov	edx,[ebp].lookahead
	cmp	eax,edx
	jna	set_length
	mov	eax,edx
set_length:
	mov	[ebp].d_match_length,eax
check_length:
	mov	eax,[ebp].d_match_length
	cmp	eax,MIN_MATCH
	jb	no_match
	mov	eax,[ebp].str_start
	sub	eax,[ebp].match_start
	mov	edx,[ebp].d_match_length
	sub	edx,MIN_MATCH
	call	ct_tally
	mov	edi,eax
	mov	eax,[ebp].d_match_length
	sub	[ebp].lookahead,eax
	cmp	eax,[ebp].max_insert_len
	ja	to_large
	cmp	[ebp].lookahead,MIN_MATCH
	jb	to_large
	dec	[ebp].d_match_length
insert_loop:
	inc	[ebp].str_start
	call	insert_string
	dec	[ebp].d_match_length
	jnz	insert_loop
	inc	[ebp].str_start
	jmp	flushblock
to_large:
	add	[ebp].str_start,eax
	xor	eax,eax
	mov	[ebp].d_match_length,eax
	mov	ebx,window
	add	ebx,[ebp].str_start
	mov	al,[ebx]
	mov	[ebp].ins_h,eax
	mov	eax,[ebp].str_start
	inc	eax
	call	update_hash
  if not (MIN_MATCH eq 3)
	call UPDATE_HASH() MIN_MATCH-3 more times
  endif
	jmp	flushblock
no_match:
	mov	ebx,window
	add	ebx,[ebp].str_start
	xor	eax,eax
	movzx	edx,BYTE PTR [ebx]
	call	ct_tally
	mov	edi,eax
	dec	[ebp].lookahead
	inc	[ebp].str_start
flushblock:
	test	edi,edi
	jz	@F
	xor	eax,eax
	call	flush_block
	jz	toend
	mov	eax,[ebp].str_start
	mov	[ebp].block_start,eax
@@:
	cmp	[ebp].lookahead,MIN_LOOKAHEAD
	jae	do
	call	fill_window
	test	STDI.ios_flag,IO_ERROR
	jz	do
	xor	eax,eax
	jmp	toend
deflate_fast ENDP

deflate PROC
	cmp	[ebp].compr_level,3
	jna	deflate_fast
	push	esi
	push	edi
	xor	eax,eax
	mov	esi,eax
	mov	[ebp].d_mavailable,eax
	mov	[ebp].d_match_length,MIN_MATCH-1
do:
	xor	eax,eax
	mov	ecx,[ebp].lookahead
	cmp	ecx,eax
	je	break
	cmp	ecx,MIN_MATCH
	jb	@F
	call	insert_string
@@:
	mov	eax,[ebp].match_start
	mov	[ebp].d_prev_match,eax
	mov	eax,[ebp].d_match_length
	mov	[ebp].prev_length,eax
	mov	[ebp].d_match_length,MIN_MATCH-1
	test	esi,esi
	jz	l1
	cmp	eax,[ebp].max_lazy_match
	jae	l1
	mov	eax,[ebp].str_start
	sub	eax,esi
	cmp	eax,MAX_DIST
	ja	l1
	mov	eax,[ebp].lookahead
	cmp	[ebp].nice_match,eax
	jb	@F
	mov	[ebp].nice_match,eax
@@:
	mov	eax,esi
	call	longest_match
	mov	edx,[ebp].lookahead
	cmp	eax,edx
	jb	@F
	mov	eax,edx
@@:
	mov	[ebp].d_match_length,eax
	cmp	eax,MIN_MATCH
	jne	l1
	mov	eax,[ebp].str_start
	sub	ax,WORD PTR [ebp].match_start
	cmp	eax,TOO_FAR
	jbe	l1
	mov	[ebp].d_match_length,MIN_MATCH-1

l1:
	mov	eax,[ebp].prev_length
	cmp	eax,MIN_MATCH
	jb	l2
	cmp	[ebp].d_match_length,eax
	ja	l2
	mov	eax,[ebp].str_start
	add	eax,[ebp].lookahead
	sub	eax,MIN_MATCH
	push	eax
	mov	eax,[ebp].str_start
	dec	eax
	sub	ax,WORD PTR [ebp].d_prev_match
	mov	edx,[ebp].prev_length
	sub	edx,MIN_MATCH
	call	ct_tally
	mov	edi,eax
	mov	eax,[ebp].prev_length
	dec	eax
	sub	[ebp].lookahead,eax
	dec	eax
	mov	[ebp].prev_length,eax
	pop	ecx
do_insert:
	inc	[ebp].str_start
	cmp	[ebp].str_start,ecx
	ja	@F
	call	insert_string
@@:
	dec	[ebp].prev_length
	jnz	do_insert
	inc	[ebp].str_start
	xor	eax,eax
	mov	[ebp].d_mavailable,eax
	mov	[ebp].d_match_length,MIN_MATCH-1
	test	edi,edi
	jz	done
	call	flush_block
	jz	toend
	mov	eax,[ebp].str_start
	mov	[ebp].block_start,eax
	jmp	done
l2:
	xor	eax,eax
	cmp	[ebp].d_mavailable,eax
	jz	@F
	mov	ebx,window
	mov	bx,WORD PTR [ebp].str_start
	dec	ebx
	movzx	edx,BYTE PTR [ebx]
	call	ct_tally
	jz	noflush
	xor	eax,eax
	call	flush_block
	jz	toend
	mov	eax,[ebp].str_start
	mov	[ebp].block_start,eax
	jmp	noflush
@@:
	mov	[ebp].d_mavailable,1
noflush:
	inc	[ebp].str_start
	dec	[ebp].lookahead
done:
	cmp	[ebp].lookahead,MIN_LOOKAHEAD
	jae	do
	lea	eax,[ebp].ins_h ;@@
	call	fill_window
	test	STDI.ios_flag,IO_ERROR
	jz	do
	xor	eax,eax
	jmp	toend
break:
	cmp	[ebp].d_mavailable,eax
	je	@F
	mov	ebx,window
	add	ebx,[ebp].str_start
	xor	eax,eax
	movzx	edx,BYTE PTR [ebx-1]
	call	ct_tally
	xor	eax,eax
@@:
	inc	eax
	call	flush_block
toend:
	pop	edi
	pop	esi
	ret
deflate ENDP

lm_init proc
	xor	eax,eax
	cmp	[ebp].window_size,eax
	jne	@F
	mov	[ebp].window_size,10000h
	inc	eax
	mov	[ebp].sliding,eax
@@:
	mov	eax,[ebp].compr_level
	shl	eax,4
	mov	ebx,eax
	mov	eax,config_table[ebx].dconfig.max_lazy
	mov	[ebp].max_lazy_match,eax
	mov	eax,config_table[ebx].dconfig.good_length
	mov	[ebp].good_match,eax
  ifndef FULL_SEARCH
	mov	eax,config_table[ebx].dconfig.nice_length
	mov	[ebp].nice_match,eax
  endif
	mov	eax,config_table[ebx].dconfig.max_chain
	mov	[ebp].max_chain_len,eax
	mov	eax,[ebp].compr_level
	cmp	al,1
	jne	@F
	mov	[ebp].compr_flags,FAST
@@:
	cmp	al,9
	jne	@F
	mov	[ebp].compr_flags,SLOW
@@:
ifndef MAXSEG_64K
    ; Can read 64K in one step
endif
	ioread( addr STDI )
	mov	[ebp].lookahead,eax
	jz	eof
	cmp	eax,MIN_LOOKAHEAD
	jae	@F
	call	fill_window
@@:
	xor	eax,eax
	mov	[ebp].ins_h,eax
	call	update_hash
	mov	eax,1
	call	update_hash
	mov	eax,1
	test	eax,eax
toend:
	ret
eof:
	mov	[ebp].eofile,1
	jmp	toend
lm_init endp

	OPTION	PROC: PUBLIC

zip_deflate PROC USES esi edi ebx level
	push	ebp
	xor	esi,esi
	malloc( SIZE S_DEFLATE )
	jz	toend
	mov	ebx,level
	mov	ebp,eax
	mov	edi,eax
	mov	ecx,SIZE S_DEFLATE
	xor	eax,eax
	rep	stosb
	mov	edi,ebx
	mov	[ebp].compr_level,edi
	lea	eax,[ebp].head_buf
	mov	[ebp].head,eax
	lea	eax,[ebp].prev_buf
	and	eax,0FFFF0000h
	add	eax,000010000h	; align block on 64K
	mov	[ebp].prev,eax
	lea	eax,[ebp].dyn_ltree
	mov	l_desc.TREE_DESC.td_dyn_tree,eax
	lea	eax,[ebp].static_ltree
	mov	l_desc.TREE_DESC.td_static_tree,eax
	lea	eax,[ebp].dyn_dtree
	mov	d_desc.TREE_DESC.td_dyn_tree,eax
	lea	eax,[ebp].static_dtree
	mov	d_desc.TREE_DESC.td_static_tree,eax
	lea	eax,[ebp].bl_tree
	mov	bl_desc.TREE_DESC.td_dyn_tree,eax
	call	clear_hash
	call	ct_init
	jz	@F
	call	lm_init
	jz	@F
	call	deflate
	mov	esi,eax
@@:
	free  ( ebp )
	mov	eax,esi
	test	eax,eax
toend:
	pop	ebp
	ret
zip_deflate ENDP

	END
