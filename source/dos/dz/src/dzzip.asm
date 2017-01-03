; DZZIP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT
;
; Inflate and Explode
;
;  inflate.c -- by Mark Adler
;  explode.c -- by Mark Adler
;
; Change history:
; ../../1997	Modified for Doszip
; 03/31/2010	Removed 386 instructions
; 06/30/2010	Added deflate
;
; This is from Info-ZIP's Zip 3.0:
;
;	trees.c	   - by Jean-loup Gailly
;	match.asm  - by Jean-loup Gailly
;	deflate.c  - by Jean-loup Gailly
;
;	Copyright (c) 1990-2008 Info-ZIP. All rights reserved.
;
; That is free (but copyrighted) software. The original sources and license
; are available from Info-ZIP's home site at: http://www.info-zip.org/
;
include dos.inc
include dir.inc
include io.inc
include iost.inc
include alloc.inc
include string.inc
include errno.inc
include syserrls.inc
include doserrls.inc
include stdio.inc
include math.inc
include wsub.inc
include fblk.inc
include filter.inc
include progress.inc
include confirm.inc
include conio.inc
include macro.inc
include dzzip.inc

SEGM64K		equ 0FFFFh

MIN_MATCH	equ 3		; The minimum and maximum match lengths
MAX_MATCH	equ 258

; Maximum window size = 32K. If you are really short of memory, compile
; with a smaller WSIZE but this reduces the compression ratio for files
; of size > WSIZE. WSIZE must be a power of two in the current implementation.
;
OSIZE		equ 8000h
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
ct_freq		DW ?	; frequency count
ct_dad		DW ?	; father node in Huffman tree
CT_DATA		ENDS

CT_UNION	STRUC
ct_code		DW ?	; bit string
ct_len		DW ?	; length of bit string
CT_UNION	ENDS

TREE_DESC	STRUC
td_dyn_tree	DW ?	; the dynamic tree
td_static_tree	DW ?	; corresponding static tree or NULL
td_extra_bits	DW ?	; extra bits for each code or NULL
td_extra_base	DW ?	; base index for extra_bits
td_elems	DW ?	; max number of elements in the tree
td_max_length	DW ?	; max bit length for the codes
td_max_code	DW ?	; largest code with non zero frequency
TREE_DESC	ENDS

dconfig		STRUC
good_length	DW ?	; reduce lazy search above this match length
max_lazy	DW ?	; do not perform lazy search above this match length
nice_length	DW ?	; quit search above this match length
max_chain	DW ?
dconfig		ENDS

S_LOCAL		STRUC	; 7794 byte
head		DW ?
prev		DW ?
window_size	DD ?
block_start	DD ?
sliding		DW ?
ins_h		DW ?
prev_length	DW ?
match_start	DW ?
str_start	DW ?
eofile		DW ?
lookahead	DW ?
max_chain_len	DW ?
max_lazy_match	DW ?
max_insert_len	equ max_lazy_match
good_match	DW ?
ifdef FULL_SEARCH
 nice_match	equ MAX_MATCH
else
 nice_match	DW ?
endif
heap_len	DW ?
heap_max	DW ?
l_buf		DD ?
d_buf		DD ?
flag_buf	equ _bufin+1024
last_lit	DW ?
last_dist	DW ?
last_flags	DW ?
flags		DB ?
flag_bit	DB ?
opt_len		DD ?
static_len	DD ?
cmpr_bytelen	DD ?
cmpr_lenbits	DD ?
bi_buf		DW ?
bi_valid	DW ?
compr_level	DW ?
compr_flags	DW ?
lm_chain_length DW ?			; longest_match()
bt_max_code	DW ?			; build_tree()
bt_next_node	DW ?
st_prevlen	DW ?			; scan_tree()/send_tree()
st_curlen	DW ?
st_nextlen	DW ?
st_count	DW ?
st_max_code	DW ?
st_max_count	DW ?
st_min_count	DW ?
gb_bits		DW ?			; gen_bitlen()
gb_overflow	DW ?
fb_opt_len	DD ?
fb_static_ln	DD ?
fb_buf		DD ?
fb_stored_ln	DD ?
fb_eof		DW ?
cb_dist		DW ?			; compress_block()
cb_lc		DW ?
cb_lx		DW ?
cb_dx		DW ?
cb_fx		DW ?
cb_flag		DB ?
cb_code		DW ?
cb_extra	DW ?
gc_next_code	DW MAX_BITS+1 dup(?)	; gen_codes()
d_mavailable	DW ?			; deflate()
d_prev_match	DW ?
d_match_length	DW ?
dyn_ltree	DW (2*HEAP_SIZE)	dup(?)
dyn_dtree	DW (2*(2*D_CODES+1))	dup(?)
static_ltree	DW (2*(L_CODES+2))	dup(?)
static_dtree	DW (2*(D_CODES))	dup(?)
bl_tree		DW (2*(2*BL_CODES+1))	dup(?)
heap		DW HEAP_SIZE		dup(?)
depth		DB HEAP_SIZE		dup(?)
base_length	DW LENGTH_CODES		dup(?)
length_code	DB MAX_MATCH-MIN_MATCH+1 dup(?)
dist_code	DB 512			dup(?)
base_dist	DW D_CODES		dup(?)
ifdef DEBUG
 bits_sent	DD ?
 input_len	DD ?
 input_size	DD ?
endif
S_LOCAL		ENDS

BMAX		equ 16	; Maximum bit length of any code (16 for explode)
N_MAX		equ 288 ; Maximum number of codes in any set

S_HUFT		STRUC
huft_e		DB ?
huft_b		DB ?
huft_n		DW ?
huft_seg	DW ?
S_HUFT		ENDS

;-------------------------------------------------------------------------------

	.data

;-------------------------------------------------------------------------------
; inflate
;-------------------------------------------------------------------------------

fixed_bd	dw 0
fixed_bl	dw 0
fixed_td	dd 0
fixed_tl	dd 0

border		dw 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15
cplens		dw 3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51
		dw 59,67,83,99,115,131,163,195,227,258,0,0
cplext		dw 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5
		dw 5,5,5,0,99,99
cpdist		dw 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257
		dw 385,513,769,1025,1537,2049,3073,4097,6145,8193
		dw 12289,16385,24577
cpdext		dw 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9
		dw 10,10,11,11,12,12,13,13
zlbits		dw 9
zdbits		dw 6
cplen2		dw 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17
		dw 18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34
		dw 35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51
		dw 52,53,54,55,56,57,58,59,60,61,62,63,64,65
cplen3		dw 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
		dw 19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
		dw 36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52
		dw 53,54,55,56,57,58,59,60,61,62,63,64,65,66
exextra		dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		dw 8
cpdist4		dw 1,65,129,193,257,321,385,449,513,577,641,705
		dw 769,833,897,961,1025,1089,1153,1217,1281,1345,1409,1473
		dw 1537,1601,1665,1729,1793,1857,1921,1985,2049,2113,2177
		dw 2241,2305,2369,2433,2497,2561,2625,2689,2753,2817,2881
		dw 2945,3009,3073,3137,3201,3265,3329,3393,3457,3521,3585
		dw 3649,3713,3777,3841,3905,3969,4033
cpdist8		dw 1,129,257,385,513,641,769,897,1025,1153,1281
		dw 1409,1537,1665,1793,1921,2049,2177,2305,2433,2561,2689
		dw 2817,2945,3073,3201,3329,3457,3585,3713,3841,3969,4097
		dw 4225,4353,4481,4609,4737,4865,4993,5121,5249,5377,5505
		dw 5633,5761,5889,6017,6145,6273,6401,6529,6657,6785,6913
		dw 7041,7169,7297,7425,7553,7681,7809,7937,8065

;-------------------------------------------------------------------------------
; Deflate
;-------------------------------------------------------------------------------

file_method	db ?
		;
		;      good lazy nice chain
config_table	DW	 0,   0,   0,	 0 ; 0 - store only
		DW	 4,   4,   8,	 4 ; 1 - maximum speed, no lazy matches
		DW	 4,   5,  16,	 8 ; 2
		DW	 4,   6,  32,	32 ; 3
		DW	 4,   4,  16,	16 ; 4 - lazy matches
		DW	 8,  16,  32,	32 ; 5
		DW	 8,  16, 128,  128 ; 6
		DW	 8,  32, 128,  256 ; 7
		DW	32, 128, 258, 1024 ; 8
		DW	32, 258, 258, 4096 ; 9 - maximum compression

bl_count	DW MAX_BITS+1 dup(?)
bl_order	DB 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15
extra_lbits	DW 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0
extra_dbits	DW 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13
extra_blbits	DW 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7

l_desc		DW ?	; dyn_ltree
		DW ?	; static_ltree
		DW offset extra_lbits
		DW LITERALS+1
		DW L_CODES
		DW MAX_BITS
		DW 0

d_desc		DW ?	; dyn_dtree
		DW ?	; static_dtree
		DW offset extra_dbits
		DW 0
		DW D_CODES
		DW MAX_BITS
		DW 0

bl_desc		DW ?	; bl_tree
		DW 0
		DW offset extra_blbits
		DW 0
		DW BL_CODES
		DW MAX_BL_BITS
		DW 0

;-------------------------------------------------------------------------------
; Doszip
;-------------------------------------------------------------------------------

ISIZE		equ 8000h
DC_MAXOBJ	equ 5000	; Max number of files in one subdir (recursive)
_C_BEST		equ 0300h
_C_FASTEST	equ 0200h
_C_SMALLEST	equ 0100h

externdef	compresslevel:byte
externdef	copy_fast:byte
externdef	cp_warning:byte
externdef	IDD_UnzipCRCError:dword
externdef	IDD_DZZipAttributes:dword
externdef	scan_fblock:S_WFBLK
externdef	format_s:byte

zip_attrib	DW ?
zip_central	S_CZIP <?>
zip_endcent	S_ZEND <0,0,0,0,0,0,0,0>
zip_local	S_LZIP <?>
key0		dd ?
key1		dd ?
key2		dd ?
arc_flength	dd ?
arc_pathz	dw ?
cp_ziptemp	DB '.$$$',0
password	DB 80 dup(0)
enterpassword	DB 'Enter password',0
format_sL_02X	db "%s",10,"'%02X'",0
cp_emarchive	db 'Error in archive',0
centhnd		dw -1
centtmp		db 'centtmp.$$$',0
foreslash	db '/',0
format_zx	db '%08lX',10
		db '%04X',10
		db '%04X',10
		db '%04X',10
		db '%04X',10
		db '%04X',10
		db '%08lX',10
		db '%08lX',10
		db '%08lX',10
		db '%04X',10
		db '%04X',10,10,10
		db '%04X', 10
		db '%08lX',10
		db '%08lX',10
		db '%08lX',10
		db 0
format_zu	db '%16lu',10
		db '%16lu',10
		db '%16u',10
		db '%16u',10
		db 0

.code

;-------------------------------------------------------------------------------
; inflate
;-------------------------------------------------------------------------------

bk	equ	<STDI.ios_l>
bb	equ	<STDI.ios_bb>
bb_ax	equ	<word ptr STDI.ios_bb>
bb_dx	equ	<word ptr STDI.ios_bb+2>

getbits proc private
	cmp byte ptr bk,al
	jb @F
	    mov cx,ax
	    mov ax,1
	    shl ax,cl
	    dec ax
	    mov dx,ax
	    and ax,bb_ax
	    test dl,dl
	    ret
	@@:
	    mov cx,bx
	    mov bx,STDI.ios_i
	    cmp bx,STDI.ios_c
	    je getbits_read
	    @@:
		push ax
		inc STDI.ios_i
		les ax,STDI.ios_bp
		add bx,ax
		mov al,es:[bx]
		mov bx,cx
		mov cx,bk
	    ifdef __3__
		movzx eax,al
		shl eax,cl
		or bb,eax
		add byte ptr bk,8
		pop ax
	    else
		mov ah,0
		mov dx,ax
		shl ax,cl
		or bb_ax,ax
		mov al,8
		add byte ptr STDI.ios_l,al
		cmp cl,al
		pop ax
		jbe getbits
		neg cl
		add cl,16
		shr dx,cl
		or bb_dx,dx
	    endif
		jmp getbits
	getbits_read:
	    push cx
	    push ax
	    call ofread
	    pop dx
	    pop cx
	    jz @F
		mov ax,dx
		mov bx,STDI.ios_i
		jmp @B
      @@:
	ret
getbits endp

dumpbits proc private
	sub byte ptr bk,cl
    ifdef __3__
	shr bb,cl
    else
	mov ax,bb_dx
	shr bb_dx,cl
	shr bb_ax,cl
	neg cl
	add cl,16
	shl ax,cl
	or bb_ax,ax
    endif
	ret
dumpbits endp

getdump proc private
	call getbits
	jz @F
	  ifdef __3__
	    sub byte ptr bk,cl
	    shr bb,cl
	    test dl,dl
	  else
	    push ax
	    call dumpbits
	    test dl,dl
	    pop ax
	  endif
      @@:
	ret
getdump endp

;
; Free the malloc'ed tables built by huft_build(), which makes a linked
; list of the tables it made, with the links in a dummy first entry of
; each table.
;
huft_free proc pascal private huft:dword
	les bx,huft
	.while bx
	    sub bx,6
	    pushm es:[bx+2]
	    invoke free, es::bx
	    pop bx
	    pop es
	.endw
	ret
huft_free endp

huft_build proc pascal private uses si di ds \
    b:dword,	; code lengths in bits (all assumed <= BMAX)
    n:word,	; number of codes (assumed <= N_MAX)
    s:word,	; number of simple-valued codes (0..s-1)
    d:dword,	; list of base values for non-simple codes
    e:dword,	; list of extra bits for non-simple codes
    t:dword,	; result: starting table
    m:dword	; maximum lookup bits, returns actual

local	z:word		; number of entries in current table
local	y:word		; number of dummy codes added
local	w:word		; bits before this table == (l * h)
local	p:word		; pointer into c[], b[], or v[]
local	l:word		; stack of bits per table
local	k:word		; number of bits in current code
local	i:word		; counter, current code
local	g:word		; maximum code length
local	el:dword	; length of EOB code (value 256)
local	a:word		; counter for codes of length k
local	q:dword		; points to current table
local	r:S_HUFT	; table entry for structure assignment
local	x[BMAX+1]:word	; bit offsets, then code stack
local	lx[BMAX+1]:word ; memory for l[-1..BMAX-1]
local	_c[BMAX+1]:word ; bit length count table
local	u[BMAX]:dword	; table stack
local	v[N_MAX]:word	; values in order of bit length

	invoke memzero, addr v, 774
	;--------------------------------------------------------------------
	; Generate counts for each bit length
	;--------------------------------------------------------------------
	lea ax,lx[2]
	mov l,ax
	mov cx,n
	lds di,b
	mov ax,BMAX
	.if cx > 256	; set length of EOB code, if any
	    mov ax,[di+512]
	.endif
	mov word ptr el,ax
	lea dx,_c
	.while cx
	    mov bx,[di]
	    add di,2
	    add bx,bx
	    add bx,dx
	    inc word ptr [bx]
	    dec cx
	.endw
	mov bx,dx
	mov ax,n
	.if [bx] == ax
	    xor ax,ax	; null input -- all zero length codes
	    les bx,t
	    mov es:[bx],ax
	    mov es:[bx+2],ax
	    les bx,m
	    mov es:[bx],ax
	    jmp huft_build_end
	.endif
	;--------------------------------------------------------------------
	; Find minimum and maximum length, bound *m by those
	;--------------------------------------------------------------------
	mov di,1
	xor ax,ax
	.while di <= BMAX
	    mov bx,di
	    add bx,bx
	    add bx,dx
	    .if [bx] == ax
		inc di
	    .else
		.break
	    .endif
	.endw
	mov k,di	; minimum code length
	les bx,m
	.if es:[bx] < di
	    mov es:[bx],di
	.endif
	mov cx,BMAX
	xor ax,ax
	.repeat
	    mov bx,cx
	    add bx,bx
	    add bx,dx
	    .break .if [bx] != ax
	.untilcxz
	mov g,cx	; maximum code length
	mov bx,word ptr m
	.if cx < es:[bx]
	    mov es:[bx],cx
	.endif
	;--------------------------------------------------------------------
	; Adjust last length count to fill out codes, if needed
	;--------------------------------------------------------------------
	mov si,cx
	mov cx,di
	mov ax,1
	shl ax,cl
	mov cx,ax
	.while di < si
	    mov bx,di
	    add bx,bx
	    add bx,dx
	    sub cx,[bx]
	    jl huft_build_erzip ; bad input: more codes than bits
	    add cx,cx
	    inc di
	.endw
	;--------------------------------------------------------------------
	; Generate starting offsets into the value table for each length
	;--------------------------------------------------------------------
	mov bx,si
	add bx,bx
	add bx,dx
	sub cx,[bx]
	jl huft_build_erzip
	add [bx],cx
	mov y,cx
	xor ax,ax
	lea bx,x[2]
	mov [bx],ax
	mov di,dx
	add di,2
	dec si
	.while si
	    add ax,[di]
	    add di,2
	    add bx,2
	    mov [bx],ax
	    dec si
	.endw
	;--------------------------------------------------------------------
	; Make a table of values in order of bit lengths
	;--------------------------------------------------------------------
	xor cx,cx
	mov si,word ptr b
	.repeat
	    mov ax,[si]
	    add si,2
	    .if ax
		add ax,ax
		lea bx,x
		add bx,ax
		mov ax,[bx]
		inc word ptr [bx]
		add ax,ax
		lea bx,v
		add bx,ax
		mov [bx],cx
	    .endif
	    inc cx
	.until cx >= n
	;--------------------------------------------------------------------
	; Generate the Huffman codes and for each, make the table entries
	;--------------------------------------------------------------------
	xor ax,ax
	mov i,ax
	mov x,ax
	mov lx,ax
	mov si,-1
	lea ax,v
	mov p,ax
	jmp HUFT_BUILD_35
    huft_build_erzip:
	mov ax,ER_ZIP
	jmp huft_build_end
	;--------------------------------------------------------------------
	; compute minimum size table less than or equal to *m bits
	;--------------------------------------------------------------------
    HUFT_BUILD_16:
	mov w,ax
	inc si
	mov ax,g	; upper limit
	sub ax,w
	mov z,ax
	les bx,m
	.if ax > es:[bx]
	    mov ax,es:[bx]
	    mov z,ax
	.endif
	mov ax,k
	sub ax,w
	mov di,ax
	mov cx,ax
	mov ax,1
	shl ax,cl
	mov cx,ax
	mov dx,a
	inc dx
	.if ax > dx
	    sub cx,dx
	    lea bx,_c
	    mov ax,k
	    add ax,ax
	    add bx,ax
	    .repeat
		mov ax,z
		inc di
		.break .if di >= ax
		mov ax,cx
		add ax,ax
		mov cx,ax
		add bx,2
		.break .if ax <= [bx]
		mov ax,[bx]
		sub cx,ax
	    .until 0
	.endif
	mov ax,w
	add ax,di
	.if ax > word ptr el
	    mov ax,word ptr el
	    .if w < ax
		sub ax,w
		mov di,ax
	    .endif
	.endif
	mov ax,1
	mov cx,di
	shl ax,cl
	mov z,ax
	mov bx,si
	add bx,bx
	add bx,l
	mov [bx],di
	inc ax
	add ax,ax
	mov dx,ax
	add ax,ax
	add ax,dx
	invoke malloc, ax
	.if ZERO?
	    .if si
		invoke huft_free, u
	    .endif
	    mov ax,ER_MEM
	    jmp huft_build_end
	.endif
	;--------------------------------------------------------------------
	; link to list for huft_free()
	;--------------------------------------------------------------------
	les bx,t
	add ax,6
	stom q
	stom es:[bx]
	sub ax,4
	stom t
	mov es,dx
	mov bx,ax
	xor ax,ax
	mov es:[bx],ax
	mov es:[bx+2],ax
	mov ax,si
	add ax,ax
	add ax,ax
	lea bx,u
	add bx,ax
	movmx [bx],q
	mov ax,si
	or  ax,ax
	jz  HUFT_BUILD_23
	add ax,ax	; connect to last table, if there is one
	lea bx,x	; save pattern for backing up
	add bx,ax
	mov dx,i
	mov [bx],dx
	mov bx,l	; bits to dump before this table
	add bx,ax
	sub bx,2
	mov cx,[bx]
	mov r.huft_b,cl
	mov bx,ax	; bits in this table
	mov ax,16
	add ax,di
	mov r.huft_e,al
	mov ax,word ptr q	; pointer to this table
	mov r.huft_n,ax
	mov ax,word ptr q+2
	mov r.huft_seg,ax
	mov ax,w
	sub ax,cx
	mov dx,ax
	mov ax,1
	mov cx,w
	shl ax,cl
	dec ax
	mov cx,i
	and cx,ax
	mov ax,cx
	mov cx,dx
	shr ax,cl
	add ax,ax
	mov dx,ax
	add ax,ax
	add dx,ax
	mov ax,si
	dec ax
	add ax,ax
	add ax,ax
	lea bx,u	; connect to last table
	add bx,ax
	mov ax,[bx]
	add ax,dx
	mov dx,[bx+2]
	mov es,dx
	mov bx,ax
	movmx es:[bx],r
	mov ax,r.huft_seg
	mov es:[bx+4],ax
    HUFT_BUILD_23:
	mov ax,si
	add ax,ax
	mov bx,l
	add bx,ax
	mov ax,w
	add ax,[bx]
	cmp ax,k
	jge @F
	jmp HUFT_BUILD_16
      @@:
	mov ax,k
	sub ax,w
	mov r.huft_b,al
	mov ax,n
	add ax,ax
	lea dx,v
	add ax,dx
	mov bx,p
	.if bx >= ax
	    mov r.huft_e,99	; out of values--invalid code
	.else
	    mov ax,[bx]
	    .if ax < s
		add p,2
		mov r.huft_n,ax ; simple code is just the value
		mov r.huft_e,16
		.if ax >= 256	; 256 is end-of-block code
		    mov r.huft_e,15
		.endif
	    .else
		add p,2		; non-simple -- look up in lists
		sub ax,s
		add ax,ax
		les bx,e
		add bx,ax
		mov dl,es:[bx]
		mov r.huft_e,dl
		les bx,d
		add bx,ax
		mov ax,es:[bx]
		mov r.huft_n,ax
	    .endif
	.endif
	mov cx,k
	sub cx,w
	mov ax,1
	shl ax,cl
	mov word ptr el+2,ax
	mov cx,w
	mov ax,i
	shr ax,cl
	mov cx,ax
	mov ax,word ptr q+2
	mov es,ax
	.while cx < z
	    mov ax,cx
	    add ax,ax
	    mov dx,ax
	    add ax,ax
	    add ax,dx
	    mov bx,word ptr q
	    add bx,ax
	    movmx es:[bx],r
	    mov ax,r.huft_seg
	    mov es:[bx+4],ax
	    add cx,word ptr el+2
	.endw
	mov cx,k
	dec cx
	mov ax,1
	shl ax,cl
	mov cx,ax
	mov di,i
	.while di & cx
	    xor di,cx
	    shr cx,1
	.endw
	xor di,cx
	mov i,di
	.repeat		; backup over finished tables
	    mov ax,1
	    mov cx,w
	    shl ax,cl
	    dec ax
	    mov dx,di
	    and dx,ax
	    mov bx,si
	    add bx,bx
	    lea ax,x
	    add bx,ax
	    .break .if dx == [bx]
	    dec si
	    mov ax,si
	    add ax,ax
	    mov bx,l
	    add bx,ax
	    mov ax,[bx]
	    sub w,ax
	.until 0
    HUFT_BUILD_33:
	mov ax,a
	dec a
	.if ax
	   jmp HUFT_BUILD_23
	.endif
	inc k
    HUFT_BUILD_35:
	mov ax,k
	cmp ax,g
	jg @F
	mov bx,ax
	add bx,bx
	lea ax,_c
	add bx,ax
	mov ax,[bx]
	mov a,ax
	jmp HUFT_BUILD_33
      @@:
	mov bx,l
	mov ax,[bx]
	les bx,m
	mov es:[bx],ax	; return actual size of base table
	mov ax,1	; Return true (1) --warning error--
	.if y == 0 || g == 1
	    dec ax	; if we were given an incomplete table
	.endif
    huft_build_end:
	ret
huft_build endp

;************** Explode an imploded compressed stream

; Get the bit lengths for a code representation from the compressed
; stream. If gettree() returns 4, then there is an error in the data.
; Otherwise zero is returned.

ex_b	equ [bp-02]
ex_io	equ [bp-04]
ex_s	equ [bp-08]
ex_bd	equ [bp-10]
ex_bl	equ [bp-12]
ex_bb	equ [bp-14]
ex_td	equ [bp-18]
ex_tl	equ [bp-22]
ex_tb	equ [bp-26]
ex_l	equ [bp-538]

get_tree proc private
	mov di,ax
	call ogetc
	inc ax
	push ax
	xor si,si
	.repeat
	    call ogetc
	    mov dx,ax
	    and ax,000Fh
	    mov cx,ax
	    inc cx
	    and dx,00F0h
	    shr dx,4
	    inc dx
	    mov ax,dx
	    add ax,si
	    .if ax <= di
		.repeat
		    lea bx,ex_l
		    mov ax,si
		    add ax,ax
		    add bx,ax
		    mov [bx],cx
		    inc si
		    dec dx
		.until !dx
		pop ax
		dec ax
		.if !ZERO?
		    push ax
		.else
		    .if si == di
			ret
		    .endif
		    .break
		.endif
	    .else
		pop ax
		.break
	    .endif
	.until 0
	mov ax,4
	or ax,ax
	ret
get_tree endp

explode_init proc private
	xor ax,ax
	mov STDI.ios_l,ax
	mov word ptr STDI.ios_bb,ax
	mov word ptr STDI.ios_bb+2,ax
	mov ex_io,ax
	movmx ex_s,zip_local.lz_fsize
	ret
explode_init endp

decode_huft proc private
	call getbits
	.repeat
	    not ax
	    and ax,dx
	    add ax,ax
	    add bx,ax
	    add ax,ax
	    add bx,ax
	    mov es,si
	    mov cl,es:[bx].S_HUFT.huft_b
	  ifdef __3__
	    sub byte ptr bk,cl
	    shr bb,cl
	  else
	    call dumpbits
	  endif
	    xor ax,ax
	    mov al,es:[bx].S_HUFT.huft_e
	    mov si,ax
	    mov al,0
	    .if si > 16
		inc ax
		.if si != 99
		    sub si,16
		    mov ax,si
		    push es
		    call getbits
		    pop es
		    mov si,es:[bx+4]
		    mov bx,es:[bx+2]
		.else
		    .break
		.endif
	    .else
		.break
	    .endif
	.until 0
	or ax,ax
	ret
decode_huft endp

explode_docopy proc private
	mov ax,ex_b
	call getdump
	mov di,ax
	mov bx,ex_td
	mov si,ex_td+2
	mov ax,ex_bd
	call decode_huft
	.if ZERO?
	    mov dx,es:[bx+2]
	    mov ax,STDO.ios_i
	    sub ax,di
	    sub ax,dx
	    mov di,ax
	    mov ax,ex_bl
	    mov bx,ex_tl
	    mov si,ex_tl+2
	    call decode_huft
	    .if ZERO?
		mov ax,si
		mov si,es:[bx+2]
		.if ax
		    mov ax,8
		    call getdump
		    add si,ax
		.endif
		xor ax,ax
		mov dx,word ptr ex_s
		mov bx,word ptr ex_s+2
		mov word ptr ex_s,ax
		mov word ptr ex_s+2,ax
		mov ax,si
		.if bx || (!bx && dx > ax)
		    sub dx,ax
		    sbb bx,0
		    mov word ptr ex_s,dx
		    mov word ptr ex_s+2,bx
		.endif
	      @@:
		and di,OSIZE-1
		mov ax,di
		.if ax <= STDO.ios_i
		    mov ax,STDO.ios_i
		.endif
		mov cx,OSIZE
		sub cx,ax
		.if cx > si
		    mov cx,si
		.endif
		sub si,cx
		mov ax,STDO.ios_i
		add STDO.ios_i,cx
		push ds
		push si
		mov si,di
		add di,cx
		push di
		cld?
		mov bx,word ptr STDO.ios_bp
		mov dx,word ptr STDO.ios_bp+2
		mov es,dx
		mov ds,dx
		mov di,bx
		add di,ax
		add bx,si
		cmp ax,si
		mov si,bx
		jbe @_docopy_io
	      @_docopy_mov:
		rep movsb
	      @_docopy_pop:
		pop di
		pop si
		pop ds
		cmp STDO.ios_i,OSIZE
		jae @_docopy_flush
	      @_docopy_lup:
		or si,si
		jnz @B
		sub ax,ax
	    .endif
	.endif
	ret
    @_docopy_io:
	mov al,ex_io
	test al,al
	jnz @_docopy_mov
	rep stosb
	jmp @_docopy_pop
    @_docopy_flush:
	call oflush
	mov ex_io,al
	jnz @_docopy_lup
	mov ax,ER_DISK
	ret
explode_docopy endp

; Decompress the imploded data using coded literals and a sliding
; window (of size 2^(6+bdl) bytes).

explode_lit proc private
	call explode_init
	@@:
	    mov ax,ex_s
	    or ax,ex_s+2
	    jz explode_flush
	    mov ax,1
	    call getdump
	    test al,al
	    jz @lit_docopy
		decm ex_s
		mov bx,ex_tb
		mov si,ex_tb+2
		mov ax,ex_bb
		call decode_huft
		jnz @F
		mov al,es:[bx+2]
		call oputc
		jz explode_eof
		cmp ax,STDO.ios_i
		jbe @B
		mov ex_io,al
		jmp @B
	    @lit_docopy:
		 call explode_docopy
		 test ax,ax
		 jz @B
	@@:
	ret
explode_lit endp

explode_flush:
	call oflush

explode_eof:	; Out of space..
	dec ax
	ret

; Decompress the imploded data using uncoded literals and a sliding
; window (of size 2^(6+bdl) bytes).

explode_nolit proc private
	call explode_init
	@@:
	    mov ax,ex_s
	    or ax,ex_s+2
	    jz explode_flush
	    mov ax,1
	    call getdump
	    test al,al
	    jz @nolit_docopy
		decm ex_s
		mov ax,8
		call getdump
		call oputc
		jz explode_eof
		cmp ax,STDO.ios_i
		jbe @B
		mov ex_io,al
		jmp @B
	    @nolit_docopy:
		call explode_docopy
		test ax,ax
		jz @B
	ret
explode_nolit endp

zip_explode proc _CType uses si di
local \
    exb:	word,	; -02
    exio:	word,	; -04
    exs:	dword,	; -08
    exbd:	word,	; -10
    exbl:	word,	; -12
    exbb:	word,	; -14
    extd:	dword,	; -18
    extl:	dword,	; -22
    extb:	dword,	; -26
    exl[256]:	word	; -538
	mov ax,7
	mov exbl,ax
	.if word ptr zip_local.lz_csize+2 >= 3 && \
	    word ptr zip_local.lz_csize > 0D40h
	    inc ax
	.endif
	mov exbd,ax
	xor ax,ax
	mov word ptr extb,ax
	mov word ptr extb+2,ax
	.if zip_local.lz_flag & 4
	    mov exbb,9
	    mov ax,256
	    call get_tree
	    .if ax
		jmp explode_end
	    .endif
	    .if huft_build(addr ex_l, 256,256,0,0, addr extb, addr exbb)
		.if ax == 1
		    jmp explode_freetb
		.endif
		jmp explode_end
	    .endif
	    mov ax,64
	    call get_tree
	    .if ax
		jmp explode_freetb
	    .endif
	    mov dx,offset cplen3
	.else
	    mov ax,64
	    call get_tree
	    .if ax
		jmp explode_end
	    .endif
	    mov dx,offset cplen2
	.endif
	.if huft_build(addr ex_l,64,0,ds::dx,addr exextra,addr extl,addr exbl)
	    .if ax == 1
		jmp explode_freetl
	    .endif
	    jmp explode_freetb
	.endif
	mov ax,64
	call get_tree
	.if ax
	    jmp explode_freetl
	.endif
	mov exb,6
	mov dx,offset cpdist4
	.if zip_local.lz_flag & 2
	    mov dx,offset cpdist8
	    inc exb
	.endif
	.if huft_build(addr ex_l,64,0,ds::dx,addr exextra,addr extd,addr exbd)
	    .if ax == 1
		jmp explode_freetd
	    .endif
	    jmp explode_freetb
	.endif
	.if word ptr extb == ax
	    call explode_nolit
	.else
	    call explode_lit
	.endif
    explode_freetd:
	push ax
	invoke huft_free, addr extd
	pop ax
    explode_freetl:
	push ax
	invoke huft_free, addr extl
	pop ax
    explode_freetb:
	push ax
	invoke huft_free, addr extb
	pop ax
    explode_end:
	ret
zip_explode endp

;************** Decompress the codes in a compressed block

inflatecode proc private
	call getbits
	add ax,ax
	add bx,ax
	add ax,ax
	add bx,ax
	mov es,si
	sub ax,ax
	mov al,es:[bx].S_HUFT.huft_e
	mov si,ax
	cmp al,16
	ja @F
	mov cl,es:[bx].S_HUFT.huft_b
      ifdef __3__
	sub byte ptr bk,cl
	shr bb,cl
      else
	call dumpbits
      endif
	sub ax,ax
	ret
      @@:
	.while al != 99
	    mov cl,es:[bx].S_HUFT.huft_b
	  ifdef __3__
	    sub byte ptr bk,cl
	    shr bb,cl
	  else
	    call dumpbits
	  endif
	    sub si,16
	    mov ax,si
	    mov si,es
	    call getbits
	    mov es,si
	    les bx,es:[bx+2]
	    add ax,ax
	    add bx,ax
	    add ax,ax
	    add bx,ax
	    sub ax,ax
	    mov al,es:[bx].S_HUFT.huft_e
	    mov si,ax
	    .if al <= 16
		mov cl,es:[bx].S_HUFT.huft_b
	      ifdef __3__
		sub byte ptr bk,cl
		shr bb,cl
	      else
		call dumpbits
	      endif
		sub ax,ax
		ret
	    .endif
	.endw
	mov ax,1
	test al,al
	ret
inflatecode endp

inflate_codes proc pascal private uses si di tl:dword, td:dword, wl:word, wd:word
	;
	; do until end of block
	;
	.while 1
	    mov si,word ptr tl+2
	    mov bx,word ptr tl
	    mov ax,wl
	    call inflatecode
	    .if ZERO?
		.if si == 16
		    mov al,es:[bx+2]
		    call oputc
		    jz inflate_codes_erdisk
		    .continue
		.elseif si == 15
		    xor ax,ax
		    ret
		.else
		    mov ax,si
		    mov si,es
		    call getdump
		    mov es,si
		    add ax,es:[bx+2]
		    mov di,ax
		    mov si,word ptr td+2
		    mov bx,word ptr td
		    mov ax,wd
		    call inflatecode
		    jnz inflate_codes_end
		    push es:[bx].S_HUFT.huft_n
		    mov ax,si
		    call getdump
		    mov dx,ax
		    mov ax,STDO.ios_i
		    pop bx
		    sub ax,bx
		    sub ax,dx
		    mov bx,ax
		    .while 1
			and bx,OSIZE-1
			mov cx,OSIZE
			mov ax,bx
			.if ax <= STDO.ios_i
			    mov ax,STDO.ios_i
			.endif
			sub cx,ax
			.if cx > di
			    mov cx,di
			.endif
			sub di,cx
			mov ax,STDO.ios_i
			add STDO.ios_i,cx
			mov dx,di
			les di,STDO.ios_bp
			lds si,STDO.ios_bp
			add di,ax
			add si,bx
			add bx,cx
			add ax,cx
			cld?
			rep movsb
			mov di,dx
			cmp ax,OSIZE;STDO.ios_size
			mov ax,ss
			mov ds,ax
			jae inflate_codes_flush
		      inflate_codes_ifdi:
			.break .if !di
		    .endw
		.endif
	    .else
		.break
	    .endif
	.endw
    inflate_codes_end:
	ret
    inflate_codes_flush:
	push bx
	call oflush
	pop bx
	jnz inflate_codes_ifdi
    inflate_codes_erdisk:
	mov ax,ER_DISK
	jmp inflate_codes_end
inflate_codes endp

;************** Decompress an inflated type 1 (fixed Huffman codes) block

inflate_fixed proc pascal private uses di
local	l[288]:word	; length list for huft_build
	lea di,l
	xor ax,ax
	.if word ptr fixed_tl == ax
	    mov bx,di
	    push ss
	    pop es
	    cld?
	    mov cx,144	; literal table
	    mov ax,8
	    rep stosw
	    mov cx,112
	    mov ax,9
	    rep stosw
	    mov cx,24
	    mov ax,7
	    rep stosw	; make a complete, but wrong code set
	    mov cx,8
	    mov ax,8
	    rep stosw
	    mov di,bx
	    mov fixed_bl,7
	    .if huft_build(ss::di,288,257,addr cplens,addr cplext,addr fixed_tl, addr fixed_bl)
		mov word ptr fixed_tl,0
		jmp @F
	    .endif
	    mov dx,di	; make an incomplete code set
	    mov cx,30
	    mov ax,5
	    push ss
	    pop es
	    cld?
	    rep stosw
	    mov fixed_bd,5
	    mov di,dx
	    .if huft_build(ss::di,30,0,addr cpdist,addr cpdext,addr fixed_td, addr fixed_bd)
		.if ax != 1
		    push ax
		    invoke huft_free, fixed_tl
		    mov word ptr fixed_tl,0
		    pop ax
		    jmp @F
		.endif
	    .endif
	.endif
	;
	; decompress until an end-of-block code
	;
	invoke inflate_codes, fixed_tl, fixed_td, fixed_bl, fixed_bd
	or ax,ax
	jz @F
	mov ax,1
      @@:
	ret
inflate_fixed endp

;************** Decompress an inflated type 2 (dynamic Huffman codes) block

inflate_dynamic proc pascal private uses si di
local	nd:word,	; number of distance codes
	nl:word,	; number of literal/length codes
	nb:word,	; number of bit length codes
	tl:dword,	; literal/length code table
	td:dword,	; distance code table
	wl:word,	; lookup bits for tl (bl)
	wd:word,	; lookup bits for td (bd)
	n:word,		; number of lengths to get
	ll[320]:word	; literal/length and distance code lengths
	mov ax,5
	call getdump
	add ax,257
	mov nl,ax	; number of literal/length codes
	mov ax,5
	call getdump
	inc ax
	mov nd,ax	; number of distance codes
	mov ax,4
	call getdump
	add ax,4
	mov nb,ax	; number of bit length codes
	;
	; PKZIP_BUG_WORKAROUND
	;
	.if nl > 288 || nd > 32
	    mov ax,1
	    jmp inflate_dynamic_end
	.endif
	xor si,si
	lea di,ll
	.while si < nb
	    mov ax,3
	    call getdump
	    mov dx,ax
	    mov bx,si
	    add bx,bx
	    mov ax,[bx+border]
	    add ax,ax
	    mov bx,di
	    add bx,ax
	    mov [bx],dx
	    inc si
	.endw
	.while si < 19
	    mov bx,si
	    add bx,bx
	    mov ax,[bx+border]
	    add ax,ax
	    mov bx,di
	    add bx,ax
	    xor ax,ax
	    mov [bx],ax
	    inc si
	.endw
	mov wl,7
	invoke huft_build, ss::di, 19, 19, 0, 0, addr tl, addr wl
	.if !wl
	    mov ax,1	; no bit lengths
	.endif
	.if ax		; incomplete code set
	    jmp inflate_dynamic_free1
	.endif
	mov ax,nl
	add ax,nd
	mov n,ax
	xor si,si
	mov di,si
	.while si < n
	    movmx td,tl
	    mov ax,wl
	    call getbits
	    add ax,ax
	    mov bx,ax
	    add ax,ax
	    add ax,bx
	    add word ptr td,ax
	    les bx,td
	    mov cl,es:[bx+1]
	  ifdef __3__
	    sub byte ptr bk,cl
	    shr bb,cl
	  else
	    call dumpbits
	  endif
	    mov ax,es:[bx+2]
	    .if ax == 16
		mov ax,2
		call getdump
		add ax,3
		mov dx,ax
		add ax,si
		.if ax > n
		    mov ax,1
		    jmp inflate_dynamic_end
		.endif
		lea ax,ll
		.while dx
		    dec dx
		    mov bx,si
		    inc si
		    add bx,bx
		    add bx,ax
		    mov [bx],di
		.endw
	    .elseif ax > 16
		.if ax != 17
		    mov ax,7
		    call getdump
		    add ax,11
		.else
		    mov ax,3
		    call getdump
		    add ax,3
		.endif
		mov dx,ax
		add ax,si
		.if ax > n
		    mov ax,1
		    jmp inflate_dynamic_end
		.endif
		xor di,di
		lea ax,ll
		.while dx
		   mov bx,si
		   inc si
		   add bx,bx
		   add bx,ax
		   mov [bx],di
		   dec dx
		.endw
	    .else
		mov di,ax
		lea ax,ll
		mov bx,si
		inc si
		add bx,bx
		add bx,ax
		mov [bx],di
	    .endif
	.endw
	invoke huft_free, tl
	mov ax,zlbits
	mov wl,ax
	invoke huft_build, addr ll, nl, 257, addr cplens,
	    addr cplext, addr tl, addr wl
	.if !wl
	    mov ax,1
	.endif
	.if ax
	    jmp inflate_dynamic_free1
	.endif
	mov ax,zdbits
	mov wd,ax
	lea ax,ll
	add ax,nl
	add ax,nl
	invoke huft_build, ss::ax, nd, 0, addr cpdist,
	    addr cpdext, addr td, addr wd
	.if !wd && nl > 257 ; ? wl
	    mov ax,1
	    jmp inflate_dynamic_free
	.endif
	.if ax == 1
	    xor ax,ax
	.endif
	.if ax
	    jmp inflate_dynamic_free
	.endif
	invoke inflate_codes, tl, td, wl, wd
	push ax
	invoke huft_free, td
	pop ax
	.if ax
	    mov ax,1
	.endif
    inflate_dynamic_free:
	push ax
	invoke huft_free, tl
	pop ax
    inflate_dynamic_end:
	ret
    inflate_dynamic_free1:
	cmp ax,1
	je  inflate_dynamic_free
	jmp inflate_dynamic_end
inflate_dynamic endp

;****** Decompress an inflated type 0 (stored) block.

inflate_stored proc private
	push si
	mov STDI.ios_l,0
	mov ax,16
	call getdump
	mov si,ax	; number of bytes in block
	mov ax,16
	call getdump
	not ax
	cmp ax,si
	jne inflate_stored_er1
	.while si	; read and output the compressed data
	    dec si
	    mov ax,8
	    call getdump
	    jz inflate_stored_er1
	    call oputc
	    jz inflate_stored_er2
	.endw
	xor ax,ax
      @@:
	pop si
	ret
inflate_stored_er1:
	mov ax,1	; error in compressed data
	jmp @B
inflate_stored_er2:
	mov ax,ER_DISK
	jmp @B
inflate_stored endp

zip_inflate proc _CType
	push si
	push di
	xor ax,ax
	mov word ptr STDI.ios_bb+2,ax
	mov word ptr STDI.ios_bb,ax
      @@:
	mov ax,1
	call getdump
	mov di,ax
	mov ax,2
	call getdump
	mov dx,ax
	.if ax == 2
	    call inflate_dynamic
	.elseif ax == 1
	    call inflate_fixed
	.elseif !ax
	    call inflate_stored
	.else
	    mov ax,ER_ZIP
	.endif
	mov si,ax
	or ax,ax
	jne @F
	or di,di
	jz @B
	call oflush
	jnz @F
	mov si,ER_USERABORT
	.if STDO.ios_flag & IO_ERROR
	    mov si,ER_DISK
	.endif
      @@:
	.if word ptr fixed_tl != 0
	    invoke huft_free, fixed_td
	    invoke huft_free, fixed_tl
	    mov word ptr fixed_td,0
	    mov word ptr fixed_tl,0
	.endif
	mov ax,si
	pop di
	pop si
	ret
zip_inflate endp

;-------------------------------------------------------------------------------
; Deflate
;-------------------------------------------------------------------------------

clear_hash PROC private
	mov	ax,[bp].S_LOCAL.head
	mov	cx,HASH_SIZE
	xor	dx,dx
	jmp	clear_axdxcx
clear_hash ENDP

clear_bl_count PROC private
	mov	ax,ds
	mov	cx,MAX_BITS+1
	mov	dx,offset bl_count
clear_bl_count ENDP

clear_axdxcx PROC private
	assert	ax,0,jne,"null pointer"
	xchg	di,dx
	mov	es,ax
	xor	ax,ax
	cld?
	rep	stosw
	mov	di,dx
	ret
clear_axdxcx ENDP

read_buf PROC private
	add	ax,dx
	mov	word ptr STDI.ios_bp,ax
	mov	STDI.ios_size,cx
	xor	ax,ax
	assert	ax,cx,jne,"read_buf"
	mov	STDI.ios_c,ax
	mov	STDI.ios_i,ax
	call	ofread
	mov	word ptr STDI.ios_bp,0
  ifdef DEBUG
	add	word ptr [bp].S_LOCAL.input_size,ax
	adc	word ptr [bp].S_LOCAL.input_size[2],0
	test	ax,ax
  endif
	ret
read_buf ENDP

flush_buf PROC private
	mov	ax,word ptr [bp].S_LOCAL.fb_buf
	mov	dx,word ptr [bp].S_LOCAL.fb_buf[2]
	mov	cx,word ptr [bp].S_LOCAL.fb_stored_ln
	assert	cx,0,jne,"flush_buf"
	assert	dx,0,jne,"flush_buf"
	mov	es,dx
	mov	bx,ax
	mov	ax,cx
	test	ax,ax
	jz	flush_eof
	call	owrite
	ret
    flush_eof:
	inc	ax
	ret
flush_buf ENDP

putshort PROC private
	mov	dx,ax
	call	oputc
	jz	putshort_eof
	mov	al,dh
	call	oputc
    putshort_eof:
	ret
putshort ENDP

ct_init PROC private
	assert	[bp].S_LOCAL.static_dtree.CT_UNION.ct_len,0,je,"ct_init already called"
	push	si
	push	di
	mov	file_method,METHOD_DEFLATE
	xor	si,si
	mov	dx,si
    ct_init_length:
	cmp	dx,LENGTH_CODES-1
	jnb	ct_init_length_end
	mov	di,dx
	add	di,di
	mov	[bp+di].S_LOCAL.base_length,si
	xor	bx,bx
    ct_init_length_code:
	mov	cx,extra_lbits[di]
	mov	ax,1
	shl	ax,cl
	cmp	bx,ax
	jnb	ct_init_length_loop
	mov	[bp+si].S_LOCAL.length_code,dl
	inc	si
	inc	bx
	jmp	ct_init_length_code
    ct_init_length_loop:
	inc	dx
	jmp	ct_init_length
    ct_init_length_end:
	assert	si,256,je,"ct_init: length != 256"
	dec	si
	mov	[bp+si].S_LOCAL.length_code,dl
	xor	si,si
	mov	dx,si
    ct_init_dist:
	cmp	dx,16
	jnb	ct_init_dist_end
	mov	di,dx
	add	di,di
	mov	[bp+di].S_LOCAL.base_dist,si
	xor	bx,bx
    ct_init_dist_code:
	mov	cx,[di+extra_dbits]
	mov	ax,1
	shl	ax,cl
	cmp	bx,ax
	jnb	ct_init_dist_loop
	mov	[bp+si].S_LOCAL.dist_code,dl
	inc	si
	inc	bx
	jmp	ct_init_dist_code
    ct_init_dist_loop:
	inc	dx
	jmp	ct_init_dist
    ct_init_dist_end:
	assert	si,256,je,"ct_init: dist != 256"
	shr	si,7
    ct_init_dist_02:
	cmp	dx,D_CODES
	jnb	ct_init_dist_end_02
	mov	di,dx
	add	di,di
	mov	ax,si
	shl	ax,7
	mov	[bp+di].S_LOCAL.base_dist,ax
	xor	bx,bx
    ct_init_dist_code_02:
	mov	cx,extra_dbits[di]
	sub	cx,7
	mov	ax,1
	shl	ax,cl
	cmp	bx,ax
	jnb	ct_init_dist_loop_02
	mov	[bp+si].S_LOCAL.dist_code[256],dl
	inc	si
	inc	bx
	jmp	ct_init_dist_code_02
    ct_init_dist_loop_02:
	inc	dx
	jmp	ct_init_dist_02
    ct_init_dist_end_02:
	assert	si,256,je,"ct_init: 256+dist != 512"
	call	clear_bl_count
	lea	di,[bp].S_LOCAL.static_ltree
	mov	cx,144
	mov	al,8
	mov	bx,16
	call	ct_init_code
	mov	cx,112
	inc	al
	mov	bl,18
	call	ct_init_code
	mov	cx,24
	mov	al,7
	mov	bl,14
	call	ct_init_code
	mov	cx,8
	inc	al
	mov	bl,16
	call	ct_init_code
	jmp	ct_init_gen_codes
    ct_init_code:
	inc	bl_count[bx]
	mov	[di].CT_UNION.ct_len,ax
	add	di,SIZE CT_DATA
	dec	cx
	jnz	ct_init_code
	ret
    ct_init_gen_codes:
	lea	ax,[bp].S_LOCAL.static_ltree
	mov	dx,L_CODES+1
	call	gen_codes
	xor	si,si
	lea	di,[bp].S_LOCAL.static_dtree
    ct_init_dtree:
	mov	dx,5
	mov	[di].CT_UNION.ct_len,dx
	mov	ax,si
	call	bi_reverse
	mov	[di].CT_UNION.ct_code,ax
	add	di,SIZE CT_DATA
	inc	si
	cmp	si,D_CODES
	jb	ct_init_dtree
	pop	di
	pop	si
ct_init ENDP

init_block PROC private
	xor	ax,ax
	lea	bx,[bp].S_LOCAL.dyn_ltree
	mov	cx,L_CODES
    init_block_ltree:
	mov	[bx].CT_DATA.ct_freq,ax
	add	bx,SIZE CT_DATA
	dec	cx
	jnz	init_block_ltree
	lea	bx,[bp].S_LOCAL.dyn_dtree
	mov	cx,D_CODES
    init_block_dtree:
	mov	[bx].CT_DATA.ct_freq,ax
	add	bx,SIZE CT_DATA
	dec	cx
	jnz	init_block_dtree
	lea	bx,[bp].S_LOCAL.bl_tree
	mov	cx,BL_CODES
    init_block_bltree:
	mov	[bx].CT_DATA.ct_freq,ax
	add	bx,SIZE CT_DATA
	dec	cx
	jnz	init_block_bltree
	mov	bx,bp
	mov	[bx].S_LOCAL.dyn_ltree[END_BLOCK*4].CT_DATA.ct_freq,1
	mov	word ptr [bx].S_LOCAL.opt_len,ax
	mov	word ptr [bx].S_LOCAL.opt_len[2],ax
	mov	word ptr [bx].S_LOCAL.static_len,ax
	mov	word ptr [bx].S_LOCAL.static_len[2],ax
	mov	[bx].S_LOCAL.last_lit,ax
	mov	[bx].S_LOCAL.last_dist,ax
	mov	[bx].S_LOCAL.last_flags,ax
	mov	[bx].S_LOCAL.flags,al
	inc	ax
	mov	[bx].S_LOCAL.flag_bit,al
	ret
init_block ENDP

gen_bitlen PROC private
	push	si
	push	di
	mov	si,ax
	call	clear_bl_count
	mov	bx,bp
	mov	bp,[si].TREE_DESC.td_dyn_tree
	mov	[bx].S_LOCAL.gb_overflow,ax
	mov	di,[bx].S_LOCAL.heap_max
	add	di,di
	mov	di,[di+bx].S_LOCAL.heap
	shl	di,2
	add	di,bp
	mov	[di].CT_UNION.ct_len,ax
	mov	cx,[bx].S_LOCAL.heap_max
	inc	cx
	jmp	gen_bitlen_next
    gen_bitlen_loop:
	mov	di,cx
	add	di,di
	mov	di,[di+bx].S_LOCAL.heap
	mov	dx,di
	shl	di,2
	mov	ax,[di+bp].CT_DATA.ct_dad
	shl	ax,2
	xchg	ax,di
	mov	di,[di+bp].CT_UNION.ct_len
	xchg	ax,di
	inc	ax
	cmp	ax,[si].TREE_DESC.td_max_length
	jbe	gen_bitlen_bits
	mov	ax,[si].TREE_DESC.td_max_length
	inc	[bx].S_LOCAL.gb_overflow
    gen_bitlen_bits:
	mov	[bx].S_LOCAL.gb_bits,ax
	mov	[di+bp].CT_UNION.ct_len,ax
	cmp	dx,[si].TREE_DESC.td_max_code
	ja	gen_bitlen_continue
	add	ax,ax
	mov	di,ax
	mov	ax,dx
	inc	bl_count[di]
	xor	dx,dx
	cmp	ax,[si].TREE_DESC.td_extra_base
	jb	gen_bitlen_nxb
	mov	di,ax
	sub	di,[si].TREE_DESC.td_extra_base
	add	di,di
	add	di,[si].TREE_DESC.td_extra_bits
	mov	dx,[di]
    gen_bitlen_nxb:
	shl	ax,2
	mov	di,ax
	mov	ax,[di+bp].CT_DATA.ct_freq
	push	dx
	push	ax
	add	dx,[bx].S_LOCAL.gb_bits
	mul	dx
	add	word ptr [bx].S_LOCAL.opt_len,ax
	adc	word ptr [bx].S_LOCAL.opt_len[2],dx
	pop	ax
	pop	dx
	cmp	[si].TREE_DESC.td_static_tree,0
	je	gen_bitlen_continue
	add	di,[si].TREE_DESC.td_static_tree
	add	dx,[di].CT_UNION.ct_len
	mul	dx
	add	word ptr [bx].S_LOCAL.static_len,ax
	adc	word ptr [bx].S_LOCAL.static_len[2],dx
    gen_bitlen_continue:
	inc	cx
    gen_bitlen_next:
	cmp	cx,HEAP_SIZE
	jb	gen_bitlen_loop
	assert	cx,HEAP_SIZE,je,"gen_bitlen"
	mov	cx,[bx].S_LOCAL.gb_overflow
	xor	ax,ax
	test	cx,cx
	jne	gen_bitlen_overflow
    gen_bitlen_end:
	mov	bp,bx
	pop	di
	pop	si
	ret
    gen_bitlen_overflow:
	mov	dx,[si].TREE_DESC.td_max_length
	dec	dx
    gen_bitlen_of_00:
	mov	di,dx
	add	di,di
	cmp	bl_count[di],ax
	jne	gen_bitlen_of_01
	dec	dx
	jmp	gen_bitlen_of_00
    gen_bitlen_of_01:
	mov	al,2
	dec	bl_count[di]
	add	di,ax
	add	bl_count[di],ax
	mov	di,[si].TREE_DESC.td_max_length
	add	di,di
	dec	bl_count[di]
	sub	cx,ax
	xor	ax,ax
	cmp	cx,ax
	jg	gen_bitlen_overflow
	mov	dx,[si].TREE_DESC.td_max_length
	mov	cx,HEAP_SIZE
    gen_bitlen_recompute:
	mov	di,dx
	add	di,di
	mov	bp,bl_count[di]
    gen_bitlen_while_n:
	test	bp,bp
	jz	gen_bitlen_max_next
	dec	cx
	mov	di,cx
	add	di,di
	mov	ax,[di+bx].S_LOCAL.heap
	cmp	ax,[si].TREE_DESC.td_max_code
	ja	gen_bitlen_while_n
	shl	ax,2
	mov	di,ax
	add	di,[si].TREE_DESC.td_dyn_tree
	mov	ax,[di].CT_UNION.ct_len
	cmp	ax,dx
	je	gen_bitlen_do
	mov	[di].CT_UNION.ct_len,dx
	xchg	ax,dx
	sub	ax,dx
	imul	[di].CT_DATA.ct_freq
	add	word ptr [bx].S_LOCAL.opt_len,ax
	adc	word ptr [bx].S_LOCAL.opt_len[2],dx
	mov	ax,word ptr [bx].S_LOCAL.opt_len
	mov	dx,word ptr [bx].S_LOCAL.opt_len[2]
	mov	dx,[di].CT_UNION.ct_len
    gen_bitlen_do:
	dec	bp
	jnz	gen_bitlen_while_n
    gen_bitlen_max_next:
	dec	dx
	jnz	gen_bitlen_recompute
	jmp	gen_bitlen_end
gen_bitlen ENDP

gen_codes PROC private
	push	si
	push	di
	push	dx
	mov	si,ax
	lea	di,[bp].S_LOCAL.gc_next_code
	xor	dx,dx
	mov	bx,dx
	mov	cx,MAX_BITS
	mov	ax,offset bl_count
    gen_codes_bits:
	mov	ax,bl_count[bx]
	add	bx,2
	add	ax,dx
	add	ax,ax
	mov	dx,ax
	mov	[di+bx],ax
	dec	cx
	jnz	gen_codes_bits
  ifdef DEBUG
	mov	ax,bl_count[2*MAX_BITS]
	add	ax,dx
	sub	ax,1
	assert	ax,<(1 shl MAX_BITS)-1>,je,"gen_codes"
  endif
	pop	cx
	inc	cx
	assert	cx,0,jne,"gen_codes"
    gen_codes_loop:
	mov	ax,[si].CT_UNION.ct_len
	test	ax,ax
	jz	gen_codes_next
	mov	bx,di
	add	bx,ax
	add	bx,ax
	mov	dx,ax
	mov	ax,[bx]
	inc	word ptr [bx]
	call	bi_reverse
	mov	[si].CT_UNION.ct_code,ax
    gen_codes_next:
	add	si,SIZE CT_DATA
	dec	cx
	jnz	gen_codes_loop
    gen_codes_end:
	pop	di
	pop	si
	ret
gen_codes ENDP

build_tree PROC private
	push	si
	push	di
	mov	si,ax
	mov	dx,-1
	xor	cx,cx
	mov	[bp].S_LOCAL.heap_len,cx
	mov	ax,HEAP_SIZE
	mov	[bp].S_LOCAL.heap_max,HEAP_SIZE
	mov	di,cx
	mov	bx,[si].TREE_DESC.td_dyn_tree
	jmp	build_tree_elems
    build_tree_zero:
	mov	[bx].CT_UNION.ct_len,ax
	jmp	build_tree_next
    build_tree_loop:
	mov	ax,[bx].CT_DATA.ct_freq
	test	ax,ax
	jz	build_tree_zero
	xchg	cx,si
	mov	[bp+si].S_LOCAL.depth,0
	xchg	cx,si
	inc	di
	add	di,di
	mov	[bp+di].S_LOCAL.heap,cx
	shr	di,1
	mov	dx,cx
    build_tree_next:
	add	bx,SIZE CT_DATA
	inc	cx
    build_tree_elems:
	cmp	cx,[si].TREE_DESC.td_elems
	jb	build_tree_loop
    build_tree_break:
	mov	[bp].S_LOCAL.bt_next_node,cx
	mov	cx,2
    build_tree_while_b:
	cmp	di,cx
	jnb	build_tree_b_end
	xor	ax,ax
	cmp	dx,cx
	jnl	build_tree_b_00
	inc	dx
	mov	ax,dx
    build_tree_b_00:
	inc	di
	mov	bx,di
	add	di,di
	mov	[bp+di].S_LOCAL.heap,ax
	mov	di,ax
	mov	[bp+di].S_LOCAL.depth,ch
	mov	di,bx
	mov	bx,[si].TREE_DESC.td_dyn_tree
	shl	ax,cl
	add	bx,ax
	mov	[bx].CT_DATA.ct_freq,1
	sub	word ptr [bp].S_LOCAL.opt_len,1
	sbb	word ptr [bp].S_LOCAL.opt_len[2],0
	cmp	[si].TREE_DESC.td_static_tree,0
	je	build_tree_while_b
	add	ax,[si].TREE_DESC.td_static_tree
	mov	bx,ax
	mov	ax,[bx].CT_UNION.ct_len
	sub	word ptr [bp].S_LOCAL.static_len,ax
	sbb	word ptr [bp].S_LOCAL.static_len[2],0
	jmp	build_tree_while_b
    build_tree_b_end:
	mov	ax,dx
	mov	[si].TREE_DESC.td_max_code,ax
	mov	[bp].S_LOCAL.bt_max_code,ax
	mov	[bp].S_LOCAL.heap_len,di
	shr	di,1
	jz	build_tree_do
    build_tree_pqdown:
	mov	ax,[si].TREE_DESC.td_dyn_tree
	mov	dx,di
	call	pqdownheap
	dec	di
	jnz	build_tree_pqdown
    build_tree_do:
	mov	bx,bp
	mov	di,[bx].S_LOCAL.heap_len
	dec	[bx].S_LOCAL.heap_len
	add	di,di
	mov	ax,[bx+di].S_LOCAL.heap
	mov	di,[bx].S_LOCAL.heap[2]
	mov	[bx].S_LOCAL.heap[2],ax
	mov	dx,SMALLEST
	mov	ax,[si].TREE_DESC.td_dyn_tree
	call	pqdownheap
	mov	ax,[bx].S_LOCAL.heap_max
	dec	ax
	add	bx,ax
	add	bx,ax
	dec	ax
	mov	[bp].S_LOCAL.heap_max,ax
	mov	ax,[bp].S_LOCAL.heap[2]
	mov	[bx].S_LOCAL.heap,di
	mov	[bx].S_LOCAL.heap[-2],ax
	push	di
	mov	bx,bp
	mov	dx,ax
	add	bx,ax
	mov	al,[bx].S_LOCAL.depth
	mov	bx,bp
	mov	ah,[bx+di].S_LOCAL.depth
	cmp	ah,al
	jb	build_tree_do_00
	mov	al,ah
    build_tree_do_00:
	inc	al
	mov	cx,[bx].S_LOCAL.bt_next_node
	add	bx,cx
	mov	[bx].S_LOCAL.depth,al
	mov	bx,dx
	mov	dx,cx
	mov	cx,2
	mov	ax,[si].TREE_DESC.td_dyn_tree
	shl	bx,cl
	add	bx,ax
	shl	dx,cl
	add	dx,ax
	shl	di,cl
	add	di,ax
	mov	ax,[bx].CT_DATA.ct_freq
	add	ax,[di].CT_DATA.ct_freq
	xchg	bx,dx
	mov	[bx].CT_DATA.ct_freq,ax
	mov	ax,[bp].S_LOCAL.bt_next_node
	mov	[di].CT_DATA.ct_dad,ax
	mov	bx,dx
	mov	[bx].CT_DATA.ct_dad,ax
	pop	di
	mov	bx,bp
	mov	[bx].S_LOCAL.heap[2],ax
	inc	ax
	mov	[bx].S_LOCAL.bt_next_node,ax
	mov	ax,[si].TREE_DESC.td_dyn_tree
	mov	dx,SMALLEST
	call	pqdownheap
	cmp	[bx].S_LOCAL.heap_len,2
	jae	build_tree_do
	mov	ax,[bp].S_LOCAL.heap[2*SMALLEST]
	dec	[bp].S_LOCAL.heap_max
	mov	bx,[bp].S_LOCAL.heap_max
	add	bx,bx
	add	bx,bp
	mov	[bx].S_LOCAL.heap,ax
	mov	ax,si
	call	gen_bitlen
	mov	ax,[si].TREE_DESC.td_dyn_tree
	mov	dx,[bp].S_LOCAL.bt_max_code
	pop	di
	pop	si
	jmp	gen_codes
build_tree ENDP

pqdownheap PROC private
	push	bp
	push	si
	push	di
	mov	si,bp
	mov	bx,ax
	mov	bp,dx
	add	bp,bp
	mov	di,bp
	add	di,di
	mov	cx,[si+bp].S_LOCAL.heap
	xchg	si,bx
    pqdownheap_loop:
	cmp	bp,[bx].S_LOCAL.heap_len
	ja	pqdownheap_break
	je	pqdownheap_00
	mov	ax,[bx+di].S_LOCAL.heap[2]
	call	smaller
	jz	pqdownheap_00
	inc	bp
    pqdownheap_00:
	mov	di,bp
	add	di,di
	mov	ax,cx
	call	smaller
	jnz	pqdownheap_break
	mov	ax,[bx+di].S_LOCAL.heap
	add	dx,dx
	mov	di,dx
	mov	[bx+di].S_LOCAL.heap,ax
	mov	dx,bp
	add	bp,bp
	mov	di,bp
	add	di,di
	jmp	pqdownheap_loop
    pqdownheap_break:
	add	dx,dx
	mov	di,dx
	mov	[bx+di].S_LOCAL.heap,cx
	pop	di
	pop	si
	pop	bp
	ret
pqdownheap ENDP

smaller PROC private
	push	di
	push	cx
	mov	cx,[bx+di].S_LOCAL.heap
	mov	di,ax
	mov	ah,[bx+di].S_LOCAL.depth
	xchg	di,cx
	mov	al,[bx+di].S_LOCAL.depth
	shl	cx,2
	shl	di,2
	xchg	si,bx
	mov	di,[bx+di].CT_DATA.ct_freq
	xchg	cx,di
	mov	di,[bx+di].CT_DATA.ct_freq
	cmp	di,cx
	xchg	si,bx
	pop	cx
	pop	di
	jb	smaller_01
	jne	smaller_00
	cmp	ah,al
	ja	smaller_00
    smaller_01:
	or	ax,1
	ret
    smaller_00:
	xor	ax,ax
	ret
smaller ENDP

send_bits PROC private
	push	si
	push	di
	mov	si,ax
	mov	di,dx
  ifdef DEBUG
	assert	dx,0,ja,  "invalid length"
	assert	dx,15,jbe,"invalid length"
	add	word ptr [bp].S_LOCAL.bits_sent,dx
	adc	word ptr [bp].S_LOCAL.bits_sent[2],0
  endif
	mov	bx,[bp].S_LOCAL.bi_buf
	mov	cx,[bp].S_LOCAL.bi_valid
	shl	ax,cl
	or	ax,bx
	add	cx,dx
	mov	[bp].S_LOCAL.bi_buf,ax
	mov	[bp].S_LOCAL.bi_valid,cx
	cmp	cx,16
	jbe	send_bits_00
	call	putshort
	mov	ax,[bp].S_LOCAL.bi_valid
	sub	ax,16
	mov	[bp].S_LOCAL.bi_valid,ax
	mov	cx,di
	sub	cx,ax
	shr	si,cl
	mov	[bp].S_LOCAL.bi_buf,si
    send_bits_00:
	pop	di
	pop	si
	ret
send_bits ENDP

s_tree_init PROC private
	mov	[bp].S_LOCAL.st_max_code,dx
	mov	di,ax
	xor	ax,ax
	mov	si,ax
	dec	ax
	mov	[bp].S_LOCAL.st_prevlen,ax
	mov	ax,[di].CT_UNION.ct_len
	mov	[bp].S_LOCAL.st_nextlen,ax
	mov	[bp].S_LOCAL.st_count,si
	mov	[bp].S_LOCAL.st_max_count,7
	mov	[bp].S_LOCAL.st_min_count,4
	test	ax,ax
	jnz	s_tree_init_end
	mov	[bp].S_LOCAL.st_max_count,138
	dec	[bp].S_LOCAL.st_min_count
    s_tree_init_end:
	ret
s_tree_init ENDP

s_tree_loop PROC private
	cmp	si,[bp].S_LOCAL.st_max_code
	ja	s_tree_exit
	mov	ax,[bp].S_LOCAL.st_nextlen
	mov	[bp].S_LOCAL.st_curlen,ax
	mov	bx,si
	inc	bx
	shl	bx,2
	mov	ax,[di+bx].CT_UNION.ct_len
	mov	[bp].S_LOCAL.st_nextlen,ax
	inc	[bp].S_LOCAL.st_count
	mov	bx,[bp].S_LOCAL.st_count
	cmp	bx,[bp].S_LOCAL.st_max_count
	jae	s_tree_elif
	cmp	ax,[bp].S_LOCAL.st_curlen
	jne	s_tree_elif
	inc	si
	jmp	s_tree_loop
    s_tree_elif:
	or	al,1
	ret
    s_tree_exit:
	xor	ax,ax
	ret
s_tree_loop ENDP

s_tree_set PROC private
	inc	si
	mov	ax,[bp].S_LOCAL.st_curlen
	mov	[bp].S_LOCAL.st_prevlen,ax
	mov	[bp].S_LOCAL.st_count,0
	mov	[bp].S_LOCAL.st_max_count,7
	mov	[bp].S_LOCAL.st_min_count,4
	mov	ax,[bp].S_LOCAL.st_nextlen
	test	ax,ax
	jz	s_tree_set_00
	cmp	ax,[bp].S_LOCAL.st_curlen
	jne	s_tree_set_01
	dec	[bp].S_LOCAL.st_max_count
	dec	[bp].S_LOCAL.st_min_count
	ret
    s_tree_set_00:
	mov	[bp].S_LOCAL.st_max_count,138
	dec	[bp].S_LOCAL.st_min_count
    s_tree_set_01:
	ret
s_tree_set ENDP

scan_tree PROC private
	push	si
	push	di
	call	s_tree_init
	inc	dx
	shl	dx,2
	mov	bx,dx
	mov	[di+bx].CT_UNION.ct_len,-1
    scan_tree_loop:
	call	s_tree_loop
	jz	scan_tree_exit
	cmp	bx,[bp].S_LOCAL.st_min_count
	jae	scan_tree_elif_00
	lea	bx,[bp].S_LOCAL.bl_tree
	mov	ax,[bp].S_LOCAL.st_curlen
	shl	ax,2
	add	bx,ax
	mov	ax,[bp].S_LOCAL.st_count
	add	[bx].CT_DATA.ct_freq,ax
	jmp	scan_tree_next
    scan_tree_elif_00:
	mov	ax,[bp].S_LOCAL.st_curlen
	test	ax,ax
	jz	scan_tree_elif_10
	cmp	ax,[bp].S_LOCAL.st_prevlen
	je	scan_tree_REP_3_6
	shl	ax,2
	add	ax,bp
	mov	bx,ax
	inc	[bx].S_LOCAL.bl_tree.CT_DATA.ct_freq
      scan_tree_REP_3_6:
	mov	ax,REP_3_6*4
	jmp	scan_tree_inc
    scan_tree_elif_10:
	cmp	[bp].S_LOCAL.st_count,10
	ja	scan_tree_else
	mov	ax,REPZ_3_10*4
	jmp	scan_tree_inc
    scan_tree_else:
	mov	ax,REPZ_11_138*4
    scan_tree_inc:
	add	ax,bp
	mov	bx,ax
	inc	[bx].S_LOCAL.bl_tree.CT_DATA.ct_freq
    scan_tree_next:
	call	s_tree_set
	jmp	scan_tree_loop
    scan_tree_exit:
	pop	di
	pop	si
	ret
scan_tree ENDP

send_tree PROC private
	push	si
	push	di
	call	s_tree_init
    send_tree_loop:
	call	s_tree_loop
	jz	send_tree_exit
	cmp	bx,[bp].S_LOCAL.st_min_count
	jae	send_tree_elif_00
    send_tree_do:
	mov	bx,[bp].S_LOCAL.st_curlen
	shl	bx,2
	add	bx,bp
	mov	ax,[bx].S_LOCAL.bl_tree.CT_UNION.ct_code
	mov	dx,[bx].S_LOCAL.bl_tree.CT_UNION.ct_len
	call	send_bits
	dec	[bp].S_LOCAL.st_count
	jnz	send_tree_do
	jmp	send_tree_next
    send_tree_elif_00:
	mov	bx,[bp].S_LOCAL.st_curlen
	test	bx,bx
	jz	send_tree_elif_10
	cmp	bx,[bp].S_LOCAL.st_prevlen
	je	send_tree_elif_000
	shl	bx,2
	add	bx,bp
	mov	ax,[bx].S_LOCAL.bl_tree.CT_UNION.ct_code
	mov	dx,[bx].S_LOCAL.bl_tree.CT_UNION.ct_len
	call	send_bits
	dec	[bp].S_LOCAL.st_count
      send_tree_elif_000:
	mov	ax,[bp].S_LOCAL.st_count
	assert	ax,3,jae,"send_tree: 3_6?"
	assert	ax,6,jbe,"send_tree: 3_6?"
	mov	ax,[bp].S_LOCAL.bl_tree.CT_UNION.ct_code[4*REP_3_6]
	mov	dx,[bp].S_LOCAL.bl_tree.CT_UNION.ct_len[4*REP_3_6]
	call	send_bits
	mov	ax,[bp].S_LOCAL.st_count
	sub	ax,3
	mov	dx,2
	call	send_bits
	jmp	send_tree_next
    send_tree_elif_10:
	cmp	[bp].S_LOCAL.st_count,10
	ja	send_tree_else
	mov	ax,[bp].S_LOCAL.bl_tree.CT_UNION.ct_code[4*REPZ_3_10]
	mov	dx,[bp].S_LOCAL.bl_tree.CT_UNION.ct_len[4*REPZ_3_10]
	call	send_bits
	mov	ax,[bp].S_LOCAL.st_count
	sub	ax,3
	mov	dx,3
	call	send_bits
	jmp	send_tree_next
    send_tree_else:
	mov	ax,[bp].S_LOCAL.bl_tree.CT_UNION.ct_code[4*REPZ_11_138]
	mov	dx,[bp].S_LOCAL.bl_tree.CT_UNION.ct_len[4*REPZ_11_138]
	call	send_bits
	mov	ax,[bp].S_LOCAL.st_count
	sub	ax,11
	mov	dx,7
	call	send_bits
    send_tree_next:
	call	s_tree_set
	jmp	send_tree_loop
    send_tree_exit:
	pop	di
	pop	si
	ret
send_tree ENDP

build_bl_tree PROC private
	lea	ax,[bp].S_LOCAL.dyn_ltree
	mov	dx,l_desc.TREE_DESC.td_max_code
	call	scan_tree
	lea	ax,[bp].S_LOCAL.dyn_dtree
	mov	dx,d_desc.TREE_DESC.td_max_code
	call	scan_tree
	mov	ax,offset bl_desc
	call	build_tree
	mov	cx,BL_CODES-1
    build_bl_tree_loop:
	cmp	cx,4
	jb	build_bl_tree_end
	mov	bx,cx
	mov	al,bl_order[bx]
	mov	ah,0
	shl	ax,2
	add	ax,bp
	mov	bx,ax
	mov	ax,[bx].S_LOCAL.bl_tree.CT_UNION.ct_len
	test	ax,ax
	jnz	build_bl_tree_end
	dec	cx
	jmp	build_bl_tree_loop
    build_bl_tree_end:
	mov	ax,3
	inc	cx
	imul	cx
	assert	dx,0,je,"overflow"
	dec	cx
	add	ax,5+5+4
	adc	dx,0
	add	word ptr [bp].S_LOCAL.opt_len,ax
	adc	word ptr [bp].S_LOCAL.opt_len[2],dx
	mov	ax,cx
	ret
build_bl_tree ENDP

send_all_trees PROC private
	push	si	; ax: lcodes
	push	di	; dx: dcodes
	push	bx	; bx: blcodes
	assert	ax,L_CODES,jbe,"too many codes"
	assert	dx,D_CODES,jbe,"too many codes"
	assert	bx,BL_CODES,jbe,"too many codes"
	assert	ax,257,jae,"not enough codes"
	assert	dx,1,jae,"not enough codes"
	assert	bx,4,jae,"not enough codes"
	mov	si,ax
	mov	di,dx
	sub	ax,257
	mov	dx,5
	call	send_bits
	mov	ax,di
	dec	ax
	mov	dx,5
	call	send_bits
	pop	ax
	push	di
	push	si
	push	ax
	mov	dx,4
	sub	ax,dx
	call	send_bits
	pop	di
	xor	si,si
    send_all_trees_loop:
	cmp	si,di
	jnb	send_all_trees_end
	mov	al,bl_order[si]
	mov	ah,0
	shl	ax,2
	add	ax,bp
	mov	bx,ax
	mov	ax,[bx].S_LOCAL.bl_tree.CT_UNION.ct_len
	mov	dx,3
	call	send_bits
	inc	si
	jmp	send_all_trees_loop
    send_all_trees_end:
	pop	dx
	dec	dx
	lea	ax,[bp].S_LOCAL.dyn_ltree
	call	send_tree
	lea	ax,[bp].S_LOCAL.dyn_dtree
	pop	dx
	dec	dx
	call	send_tree
	pop	di
	pop	si
	ret
send_all_trees ENDP

flush_block PROC private
	mov	[bp].S_LOCAL.fb_eof,ax
  ifdef __3__
	xor	eax,eax
	cmp	word ptr [bp].S_LOCAL.block_start[2],ax
	jl	flush_block_00
	mov	eax,STDI.ios_bp
	mov	ax,word ptr [bp].S_LOCAL.block_start
    flush_block_00:
	mov	[bp].S_LOCAL.fb_buf,eax
	movzx	eax,[bp].S_LOCAL.str_start
	sub	eax,[bp].S_LOCAL.block_start
	mov	[bp].S_LOCAL.fb_stored_ln,eax
  ifdef DEBUG
	add	[bp].S_LOCAL.input_len,eax
  endif
	push	si
	push	di
	mov	al,[bp].S_LOCAL.flags
	mov	bx,[bp].S_LOCAL.last_flags
	mov	flag_buf[bx],al
	mov	ax,offset l_desc
	call	build_tree
	mov	ax,offset d_desc
	call	build_tree
	call	build_bl_tree
	mov	bx,bp
	mov	si,ax
	mov	eax,[bx].S_LOCAL.opt_len
	add	eax,3+7
	shr	eax,3
	mov	[bx].S_LOCAL.fb_opt_len,eax
	mov	eax,[bx].S_LOCAL.static_len
	add	eax,3+7
	shr	eax,3
	mov	[bx].S_LOCAL.fb_static_ln,eax
	cmp	eax,[bx].S_LOCAL.fb_opt_len
	ja	flush_block_01
	mov	[bx].S_LOCAL.fb_opt_len,eax
    flush_block_01:
	mov	eax,[bx].S_LOCAL.fb_opt_len
	cmp	[bx].S_LOCAL.fb_stored_ln,eax
	ja	flush_block_else_01
	xor	eax,eax
	cmp	[bx].S_LOCAL.fb_eof,ax
	je	flush_block_else_01
	cmp	file_method,al
	je	flush_block_else_01
	cmp	[bx].S_LOCAL.cmpr_bytelen,eax
	jne	flush_block_else_01
	cmp	[bx].S_LOCAL.cmpr_lenbits,eax
	jne	flush_block_else_01
	call	copy_block
	jz	flush_block_eof
	mov	bx,bp
	movmx	[bx].S_LOCAL.cmpr_bytelen,[bx].S_LOCAL.fb_stored_ln
	mov	file_method,METHOD_STORE
	jmp	flush_block_endif
    flush_block_else_01:
	mov	eax,[bx].S_LOCAL.fb_buf
	test	eax,eax
	jz	flush_block_else_02
	mov	eax,[bx].S_LOCAL.fb_stored_ln
	add	eax,4
	cmp	eax,[bx].S_LOCAL.fb_opt_len
	ja	flush_block_else_02
	mov	ax,[bx].S_LOCAL.fb_eof
	add	ax,STORED_BLOCK*2
	mov	dx,3
	call	send_bits
	mov	bx,bp
	mov	eax,[bx].S_LOCAL.cmpr_lenbits
	add	eax,3+7
	shr	eax,3
	add	eax,[bx].S_LOCAL.fb_stored_ln
	add	eax,4
	add	[bx].S_LOCAL.cmpr_bytelen,eax
	xor	eax,eax
	mov	[bx].S_LOCAL.cmpr_lenbits,eax
	inc	ax
	call	copy_block
	jz	flush_block_eof
	mov	bx,bp
	jmp	flush_block_endif
    flush_block_else_02:
	cmpmm	[bx].S_LOCAL.fb_static_ln,[bx].S_LOCAL.fb_opt_len
	jne	flush_block_else_03
	mov	ax,[bx].S_LOCAL.fb_eof
	add	ax,STATIC_TREES*2
	mov	dx,3
	call	send_bits
	lea	ax,[bp].S_LOCAL.static_ltree
	lea	dx,[bp].S_LOCAL.static_dtree
	call	compress_block
	mov	eax,[bp].S_LOCAL.static_len
	jmp	flush_block_else_04
    flush_block_else_03:
	mov	ax,[bp].S_LOCAL.fb_eof
	add	ax,DYN_TREES*2
	mov	dx,3
	call	send_bits
	mov	ax,l_desc.TREE_DESC.td_max_code
	inc	ax
	mov	dx,d_desc.TREE_DESC.td_max_code
	inc	dx
	mov	bx,si
	inc	bx
	call	send_all_trees
	lea	ax,[bp].S_LOCAL.dyn_ltree
	lea	dx,[bp].S_LOCAL.dyn_dtree
	call	compress_block
	mov	bx,bp
	mov	eax,[bx].S_LOCAL.opt_len
    flush_block_else_04:
	mov	bx,bp
	xor	cx,cx
	add	eax,3
	add	eax,[bx].S_LOCAL.cmpr_lenbits
	mov	word ptr [bx].S_LOCAL.cmpr_lenbits[2],cx
	mov	cx,ax
	and	cx,7
	mov	word ptr [bx].S_LOCAL.cmpr_lenbits,cx
	shr	eax,3
	add	[bx].S_LOCAL.cmpr_bytelen,eax
    flush_block_endif:
	call	init_block
	mov	ax,[bp].S_LOCAL.fb_eof
	test	ax,ax
	jz	flush_block_end
	call	bi_windup
	jz	flush_block_eof
	add	[bp].S_LOCAL.cmpr_lenbits,7
  else
	xor	ax,ax
	mov	dx,ax
	cmp	word ptr [bp].S_LOCAL.block_start[2],ax
	jl	flush_block_00
	mov	dx,word ptr STDI.ios_bp+2
	mov	ax,word ptr [bp].S_LOCAL.block_start
    flush_block_00:
	mov	word ptr [bp].S_LOCAL.fb_buf,ax
	mov	word ptr [bp].S_LOCAL.fb_buf[2],dx
	xor	dx,dx
	mov	ax,[bp].S_LOCAL.str_start
	sub	ax,word ptr [bp].S_LOCAL.block_start
	sbb	dx,word ptr [bp].S_LOCAL.block_start[2]
	mov	word ptr [bp].S_LOCAL.fb_stored_ln[2],dx
	mov	word ptr [bp].S_LOCAL.fb_stored_ln,ax
  ifdef DEBUG
	add	word ptr [bp].S_LOCAL.input_len,ax
	adc	word ptr [bp].S_LOCAL.input_len[2],dx
  endif
	push	si
	push	di
	mov	al,[bp].S_LOCAL.flags
	mov	bx,[bp].S_LOCAL.last_flags
	mov	flag_buf[bx],al
	mov	ax,offset l_desc
	call	build_tree
	mov	ax,offset d_desc
	call	build_tree
	call	build_bl_tree
	mov	bx,bp
	mov	si,ax
	mov	ax,word ptr [bx].S_LOCAL.opt_len
	mov	dx,word ptr [bx].S_LOCAL.opt_len[2]
	add	ax,3+7
	adc	dx,0
	mov	cx,3
	call	_shr32
	mov	word ptr [bx].S_LOCAL.fb_opt_len,ax
	mov	word ptr [bx].S_LOCAL.fb_opt_len[2],dx
	mov	ax,word ptr [bx].S_LOCAL.static_len
	mov	dx,word ptr [bx].S_LOCAL.static_len[2]
	add	ax,3+7
	adc	dx,0
	mov	cx,3
	call	_shr32
	mov	word ptr [bx].S_LOCAL.fb_static_ln,ax
	mov	word ptr [bx].S_LOCAL.fb_static_ln[2],dx
	cmprm	[bx].S_LOCAL.fb_opt_len
	ja	flush_block_01
	mov	word ptr [bx].S_LOCAL.fb_opt_len,ax
	mov	word ptr [bx].S_LOCAL.fb_opt_len[2],dx
    flush_block_01:
	cmpmm	[bx].S_LOCAL.fb_stored_ln,[bx].S_LOCAL.fb_opt_len
	ja	flush_block_else_01
	xor	ax,ax
	cmp	[bx].S_LOCAL.fb_eof,ax
	je	flush_block_else_01
	cmp	file_method,al
	je	flush_block_else_01
	cmp	word ptr [bx].S_LOCAL.cmpr_bytelen,ax
	jne	flush_block_else_01
	cmp	word ptr [bx].S_LOCAL.cmpr_bytelen[2],ax
	jne	flush_block_else_01
	cmp	word ptr [bx].S_LOCAL.cmpr_lenbits,ax
	jne	flush_block_else_01
	cmp	word ptr [bx].S_LOCAL.cmpr_lenbits[2],ax
	jne	flush_block_else_01
	assert	word ptr [bx].S_LOCAL.fb_buf[2],ax,jne,"block vanished"
	call	copy_block
	jz	flush_block_eof
	mov	bx,bp
	movmx	[bx].S_LOCAL.cmpr_bytelen,[bx].S_LOCAL.fb_stored_ln
	mov	file_method,METHOD_STORE
	jmp	flush_block_endif
    flush_block_else_01:
	mov	ax,word ptr [bx].S_LOCAL.fb_buf[2]
	or	ax,word ptr [bx].S_LOCAL.fb_buf
	jz	flush_block_else_02
	mov	ax,word ptr [bx].S_LOCAL.fb_stored_ln
	mov	dx,word ptr [bx].S_LOCAL.fb_stored_ln[2]
	add	ax,4
	adc	dx,0
	cmprm	[bx].S_LOCAL.fb_opt_len
	ja	flush_block_else_02
	mov	ax,[bx].S_LOCAL.fb_eof
	add	ax,STORED_BLOCK*2
	mov	dx,3
	call	send_bits
	mov	bx,bp
	mov	ax,word ptr [bx].S_LOCAL.cmpr_lenbits
	mov	dx,word ptr [bx].S_LOCAL.cmpr_lenbits[2]
	add	ax,3+7
	adc	dx,0
	mov	cx,3
	call	_shr32
	add	ax,word ptr [bx].S_LOCAL.fb_stored_ln
	adc	dx,word ptr [bx].S_LOCAL.fb_stored_ln[2]
	add	ax,4
	adc	dx,0
	add	word ptr [bx].S_LOCAL.cmpr_bytelen,ax
	adc	word ptr [bx].S_LOCAL.cmpr_bytelen[2],dx
	xor	ax,ax
	mov	word ptr [bx].S_LOCAL.cmpr_lenbits,ax
	mov	word ptr [bx].S_LOCAL.cmpr_lenbits[2],ax
	inc	ax
	call	copy_block
	jz	flush_block_eof
	mov	bx,bp
	jmp	flush_block_endif
    flush_block_else_02:
	cmpmm	[bx].S_LOCAL.fb_static_ln,[bx].S_LOCAL.fb_opt_len
	jne	flush_block_else_03
	mov	ax,[bx].S_LOCAL.fb_eof
	add	ax,STATIC_TREES*2
	mov	dx,3
	call	send_bits
	lea	ax,[bp].S_LOCAL.static_ltree
	lea	dx,[bp].S_LOCAL.static_dtree
	call	compress_block
	mov	ax,word ptr [bp].S_LOCAL.static_len
	mov	dx,word ptr [bp].S_LOCAL.static_len[2]
	jmp	flush_block_else_04
    flush_block_else_03:
	mov	ax,[bp].S_LOCAL.fb_eof
	add	ax,DYN_TREES*2
	mov	dx,3
	call	send_bits
	mov	ax,l_desc.TREE_DESC.td_max_code
	inc	ax
	mov	dx,d_desc.TREE_DESC.td_max_code
	inc	dx
	mov	bx,si
	inc	bx
	call	send_all_trees
	lea	ax,[bp].S_LOCAL.dyn_ltree
	lea	dx,[bp].S_LOCAL.dyn_dtree
	call	compress_block
	mov	bx,bp
	mov	ax,word ptr [bx].S_LOCAL.opt_len
	mov	dx,word ptr [bx].S_LOCAL.opt_len[2]
    flush_block_else_04:
	mov	bx,bp
	xor	cx,cx
	add	ax,3
	adc	dx,cx
	add	ax,word ptr [bx].S_LOCAL.cmpr_lenbits
	adc	dx,word ptr [bx].S_LOCAL.cmpr_lenbits[2]
	mov	word ptr [bx].S_LOCAL.cmpr_lenbits[2],cx
	mov	cx,ax
	and	cx,7
	mov	word ptr [bx].S_LOCAL.cmpr_lenbits,cx
	mov	cx,3
	call	_shr32
	add	word ptr [bx].S_LOCAL.cmpr_bytelen,ax
	adc	word ptr [bx].S_LOCAL.cmpr_bytelen[2],dx
    flush_block_endif:
  ifdef DEBUG
	mov	ax,word ptr [bx].S_LOCAL.cmpr_bytelen
	mov	dx,word ptr [bx].S_LOCAL.cmpr_bytelen[2]
	mov	cx,3
	call	_shl32
	add	ax,word ptr [bx].S_LOCAL.cmpr_lenbits
	adc	dx,word ptr [bx].S_LOCAL.cmpr_lenbits[2]
	xchg	ax,dx
	mov	cx,word ptr [bx].S_LOCAL.bits_sent
	mov	bx,word ptr [bx].S_LOCAL.bits_sent[2]
	assert	ax,bx,je,"bad compressed size"
	assert	dx,cx,je,"bad compressed size"
  endif
	call	init_block
	mov	ax,[bp].S_LOCAL.fb_eof
	test	ax,ax
	jz	flush_block_end
  ifdef DEBUG
	mov	ax,word ptr [bp].S_LOCAL.input_len
	mov	dx,word ptr [bp].S_LOCAL.input_len[2]
	assert	ax,word ptr [bp].S_LOCAL.input_size,je,"bad input size"
	assert	dx,word ptr [bp].S_LOCAL.input_size+2,je,"bad input size"
  endif
	call	bi_windup
	jz	flush_block_eof
	add	word ptr [bp].S_LOCAL.cmpr_lenbits,7
	adc	word ptr [bp].S_LOCAL.cmpr_lenbits[2],0
  endif
    flush_block_end:
	xor	ax,ax
	inc	ax
    flush_block_eof:
	pop	di
	pop	si
	ret
flush_block ENDP

ct_tally PROC private
	push	si
	push	di
	mov	bx,bp
	les	di,[bx].S_LOCAL.l_buf
	add	di,[bx].S_LOCAL.last_lit
	mov	es:[di],dl
	inc	[bx].S_LOCAL.last_lit
	test	ax,ax
	jnz	ct_tally_else
	assert	dh,0,je,"ct_tally"
	shl	dx,2
	mov	di,dx
	inc	[di+bx].S_LOCAL.dyn_ltree.CT_DATA.ct_freq
	jmp	ct_tally_02
    ct_tally_else:
	dec	ax
  ifdef DEBUG
	assert	ax,MAX_DIST,jb,"ct_tally"
	push	dx
	shr	dx,2
	assert	dx,MAX_MATCH-MIN_MATCH,jbe,"ct_tally"
	mov	bx,ax
	cmp	ax,256
	jb	@@tally_1
	shr	bx,7
	add	bx,256
    @@tally_1:
	add	bx,bp
	mov	bl,[bx].S_LOCAL.dist_code
	assert	bl,D_CODES,jb,"ct_tally"
	mov	bx,bp
	pop	dx
  endif
	mov	di,dx
	mov	dx,ax
	mov	ah,0
	mov	al,[di+bx].S_LOCAL.length_code
	add	ax,LITERALS+1
	shl	ax,2
	mov	di,ax
	inc	[di+bx].S_LOCAL.dyn_ltree.CT_DATA.ct_freq
	mov	ax,256
	mov	di,dx
	cmp	dx,ax
	jb	ct_tally_01
	shr	di,7
	add	di,ax
    ct_tally_01:
	dec	ax
	mov	al,[di+bx].S_LOCAL.dist_code
	shl	ax,2
	mov	di,ax
	inc	[di+bx].S_LOCAL.dyn_dtree.CT_DATA.ct_freq
	mov	ax,[bx].S_LOCAL.last_dist
	add	ax,ax
	les	di,[bx].S_LOCAL.d_buf
	add	di,ax
	inc	[bx].S_LOCAL.last_dist
	mov	es:[di],dx
	mov	al,[bx].S_LOCAL.flag_bit
	or	[bx].S_LOCAL.flags,al
    ct_tally_02:
	shl	[bx].S_LOCAL.flag_bit,1
	mov	ax,[bx].S_LOCAL.last_lit
	and	ax,7
	jnz	ct_tally_03
	mov	al,[bx].S_LOCAL.flags
	mov	di,[bx].S_LOCAL.last_flags
	inc	[bx].S_LOCAL.last_flags
	mov	flag_buf[di],al
	mov	[bx].S_LOCAL.flags,0
	mov	[bx].S_LOCAL.flag_bit,1
    ct_tally_03:
	cmp	[bx].S_LOCAL.compr_level,2
	jbe	ct_tally_04
	mov	ax,[bx].S_LOCAL.last_lit
	mov	dl,ah
	and	ax,0FFFh
	jnz	ct_tally_04
	or	ah,dl
	mov	dh,al
	shl	ah,3
	shr	dl,5
	mov	si,dx
	mov	bp,ax
	xor	cx,cx
    ct_tally_loop:
	mov	di,cx
	shl	di,2
	mov	ax,[di+bx].S_LOCAL.dyn_dtree.CT_DATA.ct_freq
	shr	di,1
	mov	di,extra_dbits[di]
	add	di,5
	mul	di
	add	bp,ax
	adc	si,dx
	inc	cx
	cmp	cx,D_CODES
	jb	ct_tally_loop
	mov	cx,3
	mov	dx,si
	mov	ax,bp
	call	_shr32
	mov	bp,bx
	mov	di,ax
	mov	si,dx
	mov	ax,[bx].S_LOCAL.last_lit
	mov	cx,1
	shr	ax,cl
	cmp	[bx].S_LOCAL.last_dist,ax
	jnb	ct_tally_04
	xor	dx,dx
	mov	ax,[bx].S_LOCAL.str_start
	sub	ax,word ptr [bx].S_LOCAL.block_start
	sbb	dx,word ptr [bx].S_LOCAL.block_start[2]
	shr	ax,cl
	shr	dx,cl
	jnc	ct_tally_cmp
	or	ah,80h
    ct_tally_cmp:
	xchg	cx,ax
	cmp	si,dx
	jne	ct_tally_cmp_00
	cmp	di,cx
    ct_tally_cmp_00:
	jb	ct_tally_end
    ct_tally_04:
	mov	ax,1
	cmp	[bx].S_LOCAL.last_lit,LIT_BUFSIZE-1
	je	ct_tally_end
	cmp	[bx].S_LOCAL.last_dist,DIST_BUFSIZE
	je	ct_tally_end
	dec	ax
    ct_tally_end:
	test	ax,ax
	pop	di
	pop	si
	ret
ct_tally ENDP

compress_block PROC private
	push	si
	push	di
	mov	si,ax
	mov	di,dx
	xor	ax,ax
	mov	bx,bp
	mov	[bx].S_LOCAL.cb_lx,ax
	mov	[bx].S_LOCAL.cb_dx,ax
	mov	[bx].S_LOCAL.cb_fx,ax
	mov	[bx].S_LOCAL.cb_flag,al
	cmp	[bx].S_LOCAL.last_lit,ax
	je	compress_block_end
    compress_block_do:
	mov	ax,[bp].S_LOCAL.cb_lx
	test	al,7
	jnz	compress_block_01
	mov	bx,[bp].S_LOCAL.cb_fx
	inc	[bp].S_LOCAL.cb_fx
	mov	bl,flag_buf[bx]
	mov	[bp].S_LOCAL.cb_flag,bl
    compress_block_01:
	inc	[bp].S_LOCAL.cb_lx
	les	bx,[bp].S_LOCAL.l_buf
	add	bx,ax
	mov	al,es:[bx]
	mov	ah,0
	mov	[bp].S_LOCAL.cb_lc,ax
	test	[bp].S_LOCAL.cb_flag,1
	jnz	compress_block_else
	shl	ax,2
	mov	bx,ax
	mov	ax,[si+bx].CT_UNION.ct_code
	mov	dx,[si+bx].CT_UNION.ct_len
	call	send_bits
	jmp	compress_block_endif
    compress_block_else:
	mov	bx,[bp].S_LOCAL.cb_lc
	add	bx,bp
	mov	al,[bx].S_LOCAL.length_code
	mov	ah,0
	mov	[bp].S_LOCAL.cb_code,ax
	add	ax,LITERALS+1
	shl	ax,2
	mov	bx,ax
	mov	ax,[si+bx].CT_UNION.ct_code
	mov	dx,[si+bx].CT_UNION.ct_len
	call	send_bits
	mov	bx,[bp].S_LOCAL.cb_code
	add	bx,bx
	mov	ax,extra_lbits[bx]
	mov	[bp].S_LOCAL.cb_extra,ax
	test	ax,ax
	jz	compress_block_03
	mov	dx,ax
	mov	bx,[bp].S_LOCAL.cb_code
	add	bx,bx
	add	bx,bp
	mov	ax,[bp].S_LOCAL.cb_lc
	sub	ax,[bx].S_LOCAL.base_length
	mov	[bp].S_LOCAL.cb_lc,ax
	call	send_bits
    compress_block_03:
	mov	ax,[bp].S_LOCAL.cb_dx
	inc	[bp].S_LOCAL.cb_dx
	add	ax,ax
	les	bx,[bp].S_LOCAL.d_buf
	add	bx,ax
	mov	ax,es:[bx]
	mov	[bp].S_LOCAL.cb_dist,ax
	mov	bx,256
	cmp	ax,bx
	jb	compress_block_04
	shr	ax,7
	add	ax,bx
    compress_block_04:
	mov	bx,ax
	add	bx,bp
	mov	al,[bx].S_LOCAL.dist_code
	mov	ah,0
	mov	[bp].S_LOCAL.cb_code,ax
	assert	ax,D_CODES,jb,"bad d_code"
	shl	ax,2
	mov	bx,ax
	mov	ax,[di+bx].CT_UNION.ct_code
	mov	dx,[di+bx].CT_UNION.ct_len
	call	send_bits
	mov	bx,[bp].S_LOCAL.cb_code
	add	bx,bx
	mov	ax,extra_dbits[bx]
	mov	[bp].S_LOCAL.cb_extra,ax
	test	ax,ax
	jz	compress_block_endif
	mov	dx,ax
	mov	ax,[bp].S_LOCAL.cb_dist
	add	bx,bp
	sub	ax,[bx].S_LOCAL.base_dist
	mov	[bp].S_LOCAL.cb_dist,ax
	call	send_bits
    compress_block_endif:
	shr	[bp].S_LOCAL.cb_flag,1
	mov	ax,[bp].S_LOCAL.cb_lx
	cmp	ax,[bp].S_LOCAL.last_lit
	jnb	compress_block_end
	jmp	compress_block_do
    compress_block_end:
	mov	ax,[si+4*END_BLOCK].CT_UNION.ct_code
	mov	dx,[si+4*END_BLOCK].CT_UNION.ct_len
	call	send_bits
	pop	di
	pop	si
	ret
compress_block ENDP

bi_reverse PROC private
	assert	dx,0,jne,	"bi_reverse"
	assert	dx,MAX_BITS,jbe,"bi_reverse"
	xor	bx,bx
    bi_reverse_loop:
	shr	ax,1
	adc	bx,0
	shl	bx,1
	dec	dx
	jnz	bi_reverse_loop
	mov	ax,bx
	shr	ax,1
	ret
bi_reverse ENDP

bi_windup PROC private
	xor	ax,ax
	mov	cx,[bp].S_LOCAL.bi_valid
	mov	dx,[bp].S_LOCAL.bi_buf
	mov	[bp].S_LOCAL.bi_buf,ax
	mov	[bp].S_LOCAL.bi_valid,ax
	test	cx,cx
	jz	bi_windup_ok
	mov	al,dl
	call	oputc
	jz	bi_windup_eof
	cmp	cx,8
	jbe	bi_windup_ok
	mov	al,dh
	call	oputc
  ifdef DEBUG
	jnz	bi_windup_ok
  endif
	ret
    bi_windup_ok:
	inc	ax
  ifdef DEBUG
	mov	ax,word ptr [bp].S_LOCAL.bits_sent
	mov	dx,word ptr [bp].S_LOCAL.bits_sent[2]
	add	ax,7
	adc	dx,0
	and	ax,not 7
	mov	word ptr [bp].S_LOCAL.bits_sent,ax
	mov	word ptr [bp].S_LOCAL.bits_sent[2],dx
	xor	ax,ax
	inc	ax
  endif
    bi_windup_eof:
	ret
bi_windup ENDP

copy_block PROC private
	push	si
	mov	si,ax
	call	bi_windup
	jz	copy_block_eof
	test	si,si
	jz	copy_block_flush
	mov	ax,word ptr [bp].S_LOCAL.fb_stored_ln
	call	putshort
	jz	copy_block_eof
	mov	ax,word ptr [bp].S_LOCAL.fb_stored_ln
	not	ax
	call	putshort
	jz	copy_block_eof
  ifdef DEBUG
	add	word ptr [bp].S_LOCAL.bits_sent,2*16
	adc	word ptr [bp].S_LOCAL.bits_sent[2],0
  endif
    copy_block_flush:
	call	flush_buf
  ifdef DEBUG
	pushf
	xor	dx,dx
	mov	ax,word ptr [bp].S_LOCAL.fb_stored_ln
	mov	cx,3
	call	_shl32
	add	word ptr [bp].S_LOCAL.bits_sent,ax
	adc	word ptr [bp].S_LOCAL.bits_sent[2],dx
	popf
  endif
    copy_block_eof:
	pop	si
	ret
copy_block ENDP

update_hash PROC private
	les	ax,STDI
	assert	ax,0,je,"update_hash"
	mov	al,es:[bx]
	mov	dx,ax
	mov	ax,[bp].S_LOCAL.ins_h
	shl	ax,H_SHIFT
	xor	ax,dx
	and	ax,HASH_MASK
	mov	[bp].S_LOCAL.ins_h,ax
	ret
update_hash ENDP

insert_string PROC private
	mov	bx,[bp].S_LOCAL.str_start
	add	bx,MIN_MATCH-1
	call	update_hash
	sub	bx,MIN_MATCH-1
	xchg	ax,bx
	add	bx,bx
	mov	dx,[bp].S_LOCAL.head
	mov	es,dx
	mov	si,es:[bx]
	mov	es:[bx],ax
	mov	dx,[bp].S_LOCAL.prev
	mov	es,dx
	and	ax,WMASK
	add	ax,ax
	mov	bx,ax
	mov	es:[bx],si
	ret
insert_string ENDP

lm_init PROC private
	xor	ax,ax
	cmp	word ptr [bp].S_LOCAL.window_size[2],ax
	jne	lm_init_config
	cmp	word ptr [bp].S_LOCAL.window_size,ax
	jne	lm_init_config
	mov	word ptr [bp].S_LOCAL.window_size,ax
	inc	ax
	mov	word ptr [bp].S_LOCAL.window_size[2],ax
	mov	[bp].S_LOCAL.sliding,ax
    lm_init_config:
	mov	ax,[bp].S_LOCAL.compr_level
	shl	ax,3
	mov	bx,ax
	mov	ax,config_table[bx].dconfig.max_lazy
	mov	[bp].S_LOCAL.max_lazy_match,ax
	mov	ax,config_table[bx].dconfig.good_length
	mov	[bp].S_LOCAL.good_match,ax
  ifndef FULL_SEARCH
	mov	ax,config_table[bx].dconfig.nice_length
	mov	[bp].S_LOCAL.nice_match,ax
  endif
	mov	ax,config_table[bx].dconfig.max_chain
	mov	[bp].S_LOCAL.max_chain_len,ax
	mov	ax,[bp].S_LOCAL.compr_level
	cmp	al,1
	jne	lm_init_slow
	mov	[bp].S_LOCAL.compr_flags,FAST
    lm_init_slow:
	cmp	al,9
	jne	lm_init_read
	mov	[bp].S_LOCAL.compr_flags,SLOW
    lm_init_read:
	call	ofread
  ifdef DEBUG
	add	word ptr [bp].S_LOCAL.input_size,ax
	adc	word ptr [bp].S_LOCAL.input_size[2],0
	test	ax,ax
  endif
	mov	[bp].S_LOCAL.lookahead,ax
	jz	lm_init_eof
	cmp	ax,MIN_LOOKAHEAD
	jae	lm_init_hash
	call	fill_window
    lm_init_hash:
	xor	bx,bx
	mov	[bp].S_LOCAL.ins_h,bx
	call	update_hash
	inc	bx
	call	update_hash
	test	bx,bx
    lm_init_end:
	ret
    lm_init_eof:
	mov	[bp].S_LOCAL.eofile,1
	jmp	lm_init_end
lm_init ENDP

longest_match PROC private
	push	ds
	push	si
	push	di
	cld?
	mov	si,ax
	mov	ax,word ptr STDI.ios_bp+2
	mov	es,ax
	mov	ax,[bp].S_LOCAL.str_start
	assert	ax,0-MIN_LOOKAHEAD,jbe,"insufficient lookahead"
	mov	dx,ax
	mov	di,ax
	sub	dx,MAX_DIST
	jae	longest_match_limit_ok
	xor	dx,dx
    longest_match_limit_ok:
	add	di,2
	mov	bx,[bp].S_LOCAL.prev_length
	mov	ax,[bp].S_LOCAL.max_chain_len
	cmp	bx,[bp].S_LOCAL.good_match
	jb	longest_match_chain
	shr	ax,2
    longest_match_chain:
	mov	[bp].S_LOCAL.lm_chain_length,ax
	mov	ax,[bp].S_LOCAL.prev
	mov	ds,ax
	mov	ax,es:[bx+di-3]
	mov	cx,es:[di-2]
	jmp	longest_match_scan
    longest_match_long:
	mov	cx,[di-2]
	mov	ax,[bp].S_LOCAL.prev		; hot spot
	mov	ds,ax			;
	mov	ax,es:[bx+di-3]		; *
    longest_match_short:
	add	si,si			; ********
	dec	[bp].S_LOCAL.lm_chain_length	; *
	mov	si,[si]			; ******
	jz	longest_match_end	; ******************
	cmp	si,dx			;
	jbe	longest_match_end	; *******
    longest_match_scan:
	cmp	ax,es:[bx+si-1]		; ********
	jne	longest_match_short	; ****************************
	cmp	cx,es:[si]		;
	jne	longest_match_short	; **
	mov	cx,es			;
	add	si,2			; *
	mov	ds,cx			;
	mov	cx,(MAX_MATCH-2)/2	; *
	mov	ax,di			;
	repe	cmpsw			; **
	je	longest_match_max	; ***
    longest_match_mis:
	mov	cl,[di-2]
	xchg	ax,di
	sub	cl,[si-2]
	sub	ax,di
	sub	si,2
	sub	si,ax
	sub	cl,1
	adc	ax,0
	cmp	ax,bx
	jle	longest_match_long
	mov	[bp].S_LOCAL.match_start,si
	mov	bx,ax
	cmp	ax,[bp].S_LOCAL.nice_match
	jl	longest_match_long
    longest_match_end:
	pop	di
	pop	si
	pop	ds
	mov	ax,bx
	ret
    longest_match_max:
	cmpsb
	jmp	longest_match_mis
longest_match ENDP

ifdef	DEBUG

mcheck	macro start, match, length
	mov	ax,start
	mov	dx,match
	mov	cx,length
	call	check_match
	assert	al,0,je,"invalid match"
	endm
  check_match:
	cld?
	push	si
	push	di
	push	ds
	mov	si,ax
	mov	di,dx
	mov	ax,word ptr STDI.ios_bp+2
	mov	ds,ax
	mov	es,ax
    check_match_loop:
	lodsb
	sub	al,es:[di]
	jnz	check_match_failed
	inc	di
	loop	check_match_loop
    check_match_failed:
	pop	ds
	pop	di
	pop	si
	ret
else
mcheck	macro start, match, length
	endm
endif ; DEBUG

fill_window PROC private
	push	si
	push	di
    fill_window_do:
	mov	ax,[bp].S_LOCAL.str_start
	mov	dx,ax
	add	ax,[bp].S_LOCAL.lookahead
	xor	di,di
	sub	di,ax
	cmp	di,-1
	jne	fill_window_else
	dec	di
	jmp	fill_window_endif
    fill_window_else:
	cmp	dx,WSIZE+MAX_DIST
	jb	fill_window_endif
	xor	ax,ax
	cmp	ax,[bp].S_LOCAL.sliding
	je	fill_window_endif
	mov	dx,word ptr STDI.ios_bp+2
	push	dx
	push	ax
	push	dx
	push	WSIZE
	push	WSIZE
	call	memcpy
	mov	ax,WSIZE
	sub	[bp].S_LOCAL.match_start,ax
	sub	[bp].S_LOCAL.str_start,ax
	sub	word ptr [bp].S_LOCAL.block_start,ax
	sbb	word ptr [bp].S_LOCAL.block_start[2],0
	mov	ax,[bp].S_LOCAL.head
	mov	cx,HASH_SIZE
	call	fill_loop
	mov	ax,[bp].S_LOCAL.prev
	mov	cx,WSIZE
	call	fill_loop
	add	di,WSIZE
    fill_window_endif:
	xor	ax,ax
	cmp	[bp].S_LOCAL.eofile,ax
	jne	fill_window_end
	assert	di,2,jnb,"more < 2"
	mov	ax,[bp].S_LOCAL.str_start
	mov	dx,[bp].S_LOCAL.lookahead
	mov	cx,di
	call	read_buf
	jz	fill_window_eof
	add	[bp].S_LOCAL.lookahead,ax
	cmp	[bp].S_LOCAL.lookahead,MIN_LOOKAHEAD
	jb	fill_window_do
    fill_window_end:
	pop	di
	pop	si
	ret
    fill_window_eof:
	mov	[bp].S_LOCAL.eofile,1
	jmp	fill_window_end
      fill_loop:
	mov	es,ax
	xor	bx,bx
      fill_loop_next:
	xor	ax,ax
	mov	dx,es:[bx]
	cmp	dx,WSIZE
	jb	fill_loop_below
	mov	ax,dx
	sub	ax,WSIZE
      fill_loop_below:
	mov	es:[bx],ax
	add	bx,2
	dec	cx
	jnz	fill_loop_next
      fill_loop_break:
	ret
fill_window ENDP

deflate_fast PROC private
	push	si
	push	di
	xor	ax,ax
	mov	si,ax
	mov	[bp].S_LOCAL.d_match_length,ax
	mov	[bp].S_LOCAL.prev_length,MIN_MATCH-1
    deflate_fast_do:
	xor	ax,ax
	mov	cx,[bp].S_LOCAL.lookahead
	cmp	cx,ax
	jne	deflate_fast_while_lookahead
	inc	ax
	call	flush_block
    deflate_fast_end:
	pop	di
	pop	si
	ret
    deflate_fast_while_lookahead:
  ifndef DEFL_UNDETERM
	cmp	cx,MIN_MATCH
	jb	deflate_fast_no_string
  endif
	call	insert_string
    deflate_fast_no_string:
	test	si,si
	jz	deflate_fast_check_match
	mov	ax,[bp].S_LOCAL.str_start
	sub	ax,si
	cmp	ax,MAX_DIST
	ja	deflate_fast_check_match
  ifndef HUFFMAN_ONLY
    ifndef DEFL_UNDETERM
	mov	ax,[bp].S_LOCAL.lookahead
	cmp	[bp].S_LOCAL.nice_match,ax
	jna	deflate_fast_get_length
	mov	[bp].S_LOCAL.nice_match,ax
      deflate_fast_get_length:
    endif
	mov	ax,si
	call	longest_match
	mov	dx,[bp].S_LOCAL.lookahead
	cmp	ax,dx
	jna	deflate_fast_set_length
	mov	ax,dx
    deflate_fast_set_length:
	mov	[bp].S_LOCAL.d_match_length,ax
  endif
    deflate_fast_check_match:
	mov	ax,[bp].S_LOCAL.d_match_length
	cmp	ax,MIN_MATCH
	jb	deflate_fast_no_match
	mcheck	[bp].S_LOCAL.str_start,[bp].S_LOCAL.match_start,[bp].S_LOCAL.d_match_length
	mov	ax,[bp].S_LOCAL.str_start
	sub	ax,[bp].S_LOCAL.match_start
	mov	dx,[bp].S_LOCAL.d_match_length
	sub	dx,MIN_MATCH
	call	ct_tally
	mov	di,ax
	mov	ax,[bp].S_LOCAL.d_match_length
	sub	[bp].S_LOCAL.lookahead,ax
	cmp	ax,[bp].S_LOCAL.max_insert_len
	ja	deflate_fast_to_large
  ifndef DEFL_UNDETERM
	cmp	[bp].S_LOCAL.lookahead,MIN_MATCH
	jb	deflate_fast_to_large
  endif
	dec	[bp].S_LOCAL.d_match_length
     deflate_fast_insert_loop:
	inc	[bp].S_LOCAL.str_start
	call	insert_string
  ifdef DEFL_UNDETERM
  endif
	dec	[bp].S_LOCAL.d_match_length
	jnz	deflate_fast_insert_loop
	inc	[bp].S_LOCAL.str_start
	jmp	deflate_fast_flush
    deflate_fast_to_large:
	add	[bp].S_LOCAL.str_start,ax
	xor	ax,ax
	mov	[bp].S_LOCAL.d_match_length,ax
	les	bx,STDI
	mov	bx,[bp].S_LOCAL.str_start
	mov	al,es:[bx]
	mov	[bp].S_LOCAL.ins_h,ax
	inc	bx
	call	update_hash
  if not (MIN_MATCH eq 3)
	Call UPDATE_HASH() MIN_MATCH-3 more times
  endif
	jmp	deflate_fast_flush
    deflate_fast_no_match:
	les	bx,STDI
	mov	bx,[bp].S_LOCAL.str_start
	xor	ax,ax
	mov	dx,ax
	mov	dl,es:[bx]
	call	ct_tally
	mov	di,ax
	dec	[bp].S_LOCAL.lookahead
	inc	[bp].S_LOCAL.str_start
    deflate_fast_flush:
	test	di,di
	jz	deflate_fast_noflush
	xor	ax,ax
	call	flush_block
	jz	deflate_fast_end
	mov	ax,[bp].S_LOCAL.str_start
	mov	word ptr [bp].S_LOCAL.block_start,ax
	mov	word ptr [bp].S_LOCAL.block_start[2],0
    deflate_fast_noflush:
	cmp	[bp].S_LOCAL.lookahead,MIN_LOOKAHEAD
	jae	deflate_fast_continue
	call	fill_window
	test	STDI.ios_flag,IO_ERROR
	jz	deflate_fast_continue
	xor	ax,ax
	jmp	deflate_fast_end
    deflate_fast_continue:
	jmp	deflate_fast_do
deflate_fast ENDP

deflate PROC private
	cmp	[bp].S_LOCAL.compr_level,3
	ja	deflate_slow
	jmp	deflate_fast
    deflate_slow:
	push	si
	push	di
	xor	ax,ax
	mov	si,ax
	mov	[bp].S_LOCAL.d_mavailable,ax
	mov	[bp].S_LOCAL.d_match_length,MIN_MATCH-1
    deflate_do:
	xor	ax,ax
	mov	cx,[bp].S_LOCAL.lookahead
	cmp	cx,ax
	jne	@F
	jmp	deflate_break
      @@:
  ifndef DEFL_UNDETERM
	cmp	cx,MIN_MATCH
	jb	deflate_no_string
  endif
	call	insert_string
    deflate_no_string:
	mov	ax,[bp].S_LOCAL.match_start
	mov	[bp].S_LOCAL.d_prev_match,ax
	mov	ax,[bp].S_LOCAL.d_match_length
	mov	[bp].S_LOCAL.prev_length,ax
	mov	[bp].S_LOCAL.d_match_length,MIN_MATCH-1
	test	si,si
	jz	deflate_if
	cmp	ax,[bp].S_LOCAL.max_lazy_match
	jae	deflate_if
	mov	ax,[bp].S_LOCAL.str_start
	sub	ax,si
	cmp	ax,MAX_DIST
	ja	deflate_if
	mov	ax,[bp].S_LOCAL.lookahead
	cmp	[bp].S_LOCAL.nice_match,ax
	jb	deflate_00
	mov	[bp].S_LOCAL.nice_match,ax
    deflate_00:
	mov	ax,si
	call	longest_match
	mov	dx,[bp].S_LOCAL.lookahead
	cmp	ax,dx
	jb	deflate_01
	mov	ax,dx
    deflate_01:
	mov	[bp].S_LOCAL.d_match_length,ax
	mov	ax,[bp].S_LOCAL.d_match_length
	cmp	ax,MIN_MATCH
	jne	deflate_if
	mov	ax,[bp].S_LOCAL.str_start
	sub	ax,[bp].S_LOCAL.match_start
	cmp	ax,TOO_FAR
	jbe	deflate_if
	mov	[bp].S_LOCAL.d_match_length,MIN_MATCH-1
    deflate_if:
	mov	ax,[bp].S_LOCAL.prev_length
	cmp	ax,MIN_MATCH
	jae	@F
	jmp	deflate_else_if
      @@:
	cmp	[bp].S_LOCAL.d_match_length,ax
	ja	deflate_else_if
	mov	ax,[bp].S_LOCAL.str_start
	add	ax,[bp].S_LOCAL.lookahead
	sub	ax,MIN_MATCH
	push	ax
  ifdef DEBUG
	mov	bx,[bp].S_LOCAL.str_start
	dec	bx
	mcheck	bx,[bp].S_LOCAL.d_prev_match,[bp].S_LOCAL.prev_length
  endif
	mov	ax,[bp].S_LOCAL.str_start
	dec	ax
	sub	ax,[bp].S_LOCAL.d_prev_match
	mov	dx,[bp].S_LOCAL.prev_length
	sub	dx,MIN_MATCH
	call	ct_tally
	mov	di,ax
	mov	ax,[bp].S_LOCAL.prev_length
	dec	ax
	sub	[bp].S_LOCAL.lookahead,ax
	dec	ax
	mov	[bp].S_LOCAL.prev_length,ax
	pop	cx
    deflate_do_insert:
	inc	[bp].S_LOCAL.str_start
	cmp	[bp].S_LOCAL.str_start,cx
	ja	deflate_while_insert
	call	insert_string
    deflate_while_insert:
	dec	[bp].S_LOCAL.prev_length
	jnz	deflate_do_insert
	inc	[bp].S_LOCAL.str_start
	xor	ax,ax
	mov	[bp].S_LOCAL.d_mavailable,ax
	mov	[bp].S_LOCAL.d_match_length,MIN_MATCH-1
	test	di,di
	jz	deflate_endif
	call	flush_block
	jz	deflate_end
	mov	ax,[bp].S_LOCAL.str_start
	mov	word ptr [bp].S_LOCAL.block_start,ax
	mov	word ptr [bp].S_LOCAL.block_start[2],0
	jmp	deflate_endif
    deflate_else_if:
	xor	ax,ax
	cmp	[bp].S_LOCAL.d_mavailable,ax
	jz	deflate_else
	les	bx,STDI
	mov	bx,[bp].S_LOCAL.str_start
	dec	bx
	mov	dx,ax
	mov	dl,es:[bx]
	call	ct_tally
	jz	deflate_noflush
	xor	ax,ax
    deflate_doflush:
	call	flush_block
	jz	deflate_end
	mov	ax,[bp].S_LOCAL.str_start
	mov	word ptr [bp].S_LOCAL.block_start,ax
	mov	word ptr [bp].S_LOCAL.block_start[2],0
	jmp	deflate_noflush
    deflate_else:
	mov	[bp].S_LOCAL.d_mavailable,1
    deflate_noflush:
	inc	[bp].S_LOCAL.str_start
	dec	[bp].S_LOCAL.lookahead
    deflate_endif:
	cmp	[bp].S_LOCAL.lookahead,MIN_LOOKAHEAD
	jae	deflate_continue
	call	fill_window
	test	STDI.ios_flag,IO_ERROR
	jz	deflate_continue
	xor	ax,ax
	jmp	deflate_end
    deflate_continue:
	jmp	deflate_do
    deflate_break:
	cmp	[bp].S_LOCAL.d_mavailable,ax
	je	deflate_flush
	les	bx,STDI
	mov	bx,[bp].S_LOCAL.str_start
	xor	ax,ax
	mov	dx,ax
	mov	dl,es:[bx-1]
	call	ct_tally
	xor	ax,ax
    deflate_flush:
	inc	ax
	call	flush_block
    deflate_end:
	pop	di
	pop	si
	ret
deflate ENDP

deflate_alloc PROC private
	push	SEGM64K
	call	malloc
	jz	deflate_alloc_exit
	inc	dx
	mov	[bp].S_LOCAL.prev,dx
	push	HASH_SIZE*2+16
	call	malloc
	jz	deflate_free
	inc	dx
	mov	[bp].S_LOCAL.head,dx
	push	LIT_BUFSIZE+16
	call	malloc
	jz	deflate_free
	inc	dx
	mov	word ptr [bp].S_LOCAL.l_buf[2],dx
	push	DIST_BUFSIZE*2+16
	call	malloc
	jz	deflate_free
	inc	dx
	mov	word ptr [bp].S_LOCAL.d_buf[2],dx
	call	clear_hash
	inc	ax
    deflate_alloc_exit:
	ret
deflate_alloc ENDP

deflate_free PROC private
	mov	ax,[bp].S_LOCAL.head
	call	deflate_free_block
	mov	ax,[bp].S_LOCAL.prev
	call	deflate_free_block
	mov	ax,word ptr [bp].S_LOCAL.l_buf[2]
	call	deflate_free_block
	mov	ax,word ptr [bp].S_LOCAL.d_buf[2]
	call	deflate_free_block
    deflate_free_end:
	xor	ax,ax
	ret
    deflate_free_block:
	test	ax,ax
	jz	deflate_free_end
	dec	ax
	push	ax
	push	ax
	call	free
	ret
deflate_free ENDP

zip_deflate proc _CType public level:WORD
local	zip_stack:S_LOCAL
	push	bp
	push	si
	push	level
	lea	bp,zip_stack
	push	ss
	push	bp
	push	SIZE S_LOCAL
	call	memzero
	pop	ax
	mov	[bp].S_LOCAL.compr_level,ax
	lea	ax,[bp].S_LOCAL.dyn_ltree
	mov	l_desc.TREE_DESC.td_dyn_tree,ax
	lea	ax,[bp].S_LOCAL.static_ltree
	mov	l_desc.TREE_DESC.td_static_tree,ax
	lea	ax,[bp].S_LOCAL.dyn_dtree
	mov	d_desc.TREE_DESC.td_dyn_tree,ax
	lea	ax,[bp].S_LOCAL.static_dtree
	mov	d_desc.TREE_DESC.td_static_tree,ax
	lea	ax,[bp].S_LOCAL.bl_tree
	mov	bl_desc.TREE_DESC.td_dyn_tree,ax
	xor	si,si
	call	deflate_alloc
	jz	zip_deflate_exit
	call	ct_init
	jz	zip_deflate_exit
	call	lm_init
	jz	zip_deflate_exit
	call	deflate
	mov	si,ax
	call	deflate_free
    zip_deflate_exit:
	mov	ax,si
	test	ax,ax
	pop	si
	pop	bp
	ret
zip_deflate endp

;-------------------------------------------------------------------------------
; Unzip
;-------------------------------------------------------------------------------

_CRC32:
ifdef __3__
	xor ax,dx
	xor ah,ah
	shl ax,2
	mov bx,ax
	mov eax,[bx+crctab]
	shr edx,8
	xor eax,edx
else
	mov dx,bx	; cx:bx, ax
	xor ax,dx
	xor ah,ah
	shl ax,2
	mov bx,ax
	mov dl,dh
	mov dh,cl
	mov cl,ch
	mov ch,0
	mov ax,word ptr [bx+crctab]
	xor ax,dx
	mov dx,word ptr [bx+crctab+2]
	xor dx,cx
endif
	ret

update_keys:
ifdef __3__
	push	ax
	mov	edx,key0
	call	_CRC32
	mov	key0,eax
	and	eax,000000FFh
	add	eax,key1
	mov	edx,134775813
	mul	edx
	inc	eax
	mov	key1,eax
	mov	edx,key2
	shr	eax,24
	call	_CRC32
	mov	key2,eax
	pop	ax
else
	push	cx
	mov	bx,word ptr key0
	mov	cx,word ptr key0+2
	push	ax
	call	_CRC32
	mov	word ptr key0,ax
	mov	word ptr key0+2,dx
	mov	dx,word ptr key1+2
	mov	ah,0
	add	ax,word ptr key1
	adc	dx,0
	mov	cx,0808h
	mov	bx,8405h
	call	_mul32
	add	ax,1
	adc	dx,0
	mov	word ptr key1,ax
	mov	word ptr key1+2,dx
	mov	bx,word ptr key2
	mov	cx,word ptr key2+2
	mov	al,dh
	xor	dx,dx
	mov	ah,00h
	call	_CRC32
	mov	word ptr key2,ax
	mov	word ptr key2+2,dx
	pop	ax
	pop	cx
endif
	ret

decryptbyte:
	mov	bx,word ptr key2
	or	bx,2
	mov	dx,bx
	xor	dx,1
	mov	ax,bx
	mul	dx
	mov	al,ah
	ret

init_keys:
ifdef __3__
	mov key0,12345678h
	mov key1,23456789h
	mov key2,34567890h
else
	mov word ptr key0,5678h
	mov word ptr key0+2,1234h
	mov word ptr key1,6789h
	mov word ptr key1+2,2345h
	mov word ptr key2,7890h
	mov word ptr key2+2,3456h
endif
	push si
	mov si,offset password
	.repeat
	    xor ax,ax
	    mov al,[si]
	    inc si
	    .break .if !al
	    call update_keys
	.until 0
	pop si
	ret

odecrypt proc public
	push	si
	xor	si,si
      @@:
	call	decryptbyte
	les	bx,dword ptr STDI
	add	bx,si
	xor	es:[bx],al
	mov	al,es:[bx]
	call	update_keys
	inc	si
	cmp	si,STDI.S_IOST.ios_c
	jl	@B
	pop	si
	ret
odecrypt endp

test_password proc pascal private uses si di string:dword
local b[12]:byte
	call	init_keys
	lea	di,b
	invoke	memcpy,ss::di,string,12
	xor	si,si
	.repeat
	    call decryptbyte
	    xor [di],al
	    mov al,[di]
	    call update_keys
	    inc di
	    inc si
	.until si == 12
	lea di,b
	mov ax,zip_local.lz_time
	.if !(zip_attrib & _A_ZEXTLOCHD)
	    mov ax,word ptr zip_local.lz_crc+2
	.endif
	.if ah != [di+11]
	    xor ax,ax
	.else
	    mov cx,STDI.S_IOST.ios_c
	    sub cx,12
	    les si,dword ptr STDI
	    add si,12
	    .repeat
		call decryptbyte
		xor es:[si],al
		mov al,es:[si]
		call update_keys
		inc si
	    .untilcxz
	    mov ax,cx
	    inc ax
	.endif
	ret
test_password endp

zip_decrypt proc pascal private uses si di
local	b[12]:byte
	mov	si,12
	lea	di,b
      @@:
	call	ogetc
	mov	[di],al
	inc	di
	dec	si
	jnz	@B
	.if !test_password(addr b)
	    mov password,0
	    .if tgetline(addr enterpassword,addr password,32,80)
		xor ax,ax
		.if password != al
		    invoke test_password,addr b
		.endif
	    .endif
	.endif
	test	ax,ax
	ret
zip_decrypt endp

unzip	proc _CType public
	push	si
	mov	si,ER_MEM
	mov	STDI.S_IOST.ios_file,ax ; zip file handle
	mov	STDO.S_IOST.ios_file,dx ; out file handle
	invoke	oinitst,addr STDO,WSIZE
	jz	@F
	invoke	oinitst,addr STDI,64000
	.if ZERO?
	    invoke oinitst,addr STDI,8000h
	.endif
	jz	@F
	mov	si,-1
	mov	STDI.S_IOST.ios_flag,IO_USEBITS
	mov	STDO.S_IOST.ios_flag,IO_UPDTOTAL or IO_USEUPD or IO_USECRC
	.if zip_attrib & _A_ZENCRYPTED
	    call ogetc
	    jz @F
	    dec STDI.S_IOST.ios_i
	    call zip_decrypt
	    or ax,ax
	    jz @F
	    or STDI.S_IOST.ios_flag,IO_CRYPT
	.endif
	mov	ax,zip_local.lz_method
	.if !ax
	    mov STDI.S_IOST.ios_flag,IO_USECRC
	    xor si,si
	    .if !ocopy(zip_local.lz_fsize)
		mov si,ax
	    .endif
	.elseif ax == 8
	    call zip_inflate
	    mov si,ax
	.elseif ax == 6
	    call zip_explode
	    mov si,ax
	.else
	    invoke ermsg,addr cp_warning,addr format_sL_02X,
		zip_local.lz_method,sys_errlist[ENOSYS*4]
	    mov si,3
	.endif
      @@:
	invoke	ofreest,addr STDI
	invoke	ofreest,addr STDO
	.if STDO.S_IOST.ios_flag & IO_ERROR
	    mov si,ER_DISK
	.elseif !si
ifdef __3__
	    mov eax,STDO.S_IOST.ios_bb
	    not eax
	    cmp eax,zip_local.lz_crc
else
	    lodm STDO.ios_bb
	    not ax
	    not dx
	    .if dx == word ptr zip_local.lz_crc+2
		.if ax == word ptr zip_local.lz_crc
		.endif
	    .endif
endif
	    .if !ZERO?
		.if !rsmodal(IDD_UnzipCRCError)
		    mov si,ER_CRCERR
		.endif
	    .endif
	.endif
	mov	ax,si
	pop	si
	ret
unzip	endp

;-------------------------------------------------------------------------------
; Zip-IO
;-------------------------------------------------------------------------------

zip_copylocal proc _CType uses si di exact_match:byte
local	extsize_local:word
local	offset_local:dword
	invoke	strlen,addr __outpath
	mov	di,ax
	sub	ax,ax
	mov	si,ax
	mov	[bp-6],ax
	dec	ax
	mov	[bp-2],ax
	mov	[bp-4],ax
    copylocal_loop:
	mov	ax,SIZE S_ZEND
	call	oread
	jnz	copylocal_test_local
    copylocal_error:
	mov	ax,-1
    copylocal_toend:
	jmp	copylocal_end
    copylocal_test_local:
	cmp	word ptr es:[bx],ZIPHEADERID
	jne	copylocal_error
	mov	ax,si
	cmp	word ptr es:[bx+2],ZIPLOCALID
	jne	copylocal_toend
	mov	ax,SIZE S_LZIP
	add	ax,di
    copylocal_oread:
	call	oread
	jz	copylocal_error
	mov	dx,word ptr es:[bx].S_LZIP.lz_csize[2]
	mov	ax,SIZE S_LZIP
	add	ax,es:[bx].S_LZIP.lz_fnsize
	cmp	cx,ax
	jb	copylocal_oread
	add	ax,es:[bx].S_LZIP.lz_extsize
	add	ax,word ptr es:[bx].S_LZIP.lz_csize
	adc	dx,0
	push	dx
	push	ax
	test	si,si
	jnz	copylocal_copy
	mov	ax,es:[bx].S_LZIP.lz_fnsize
	cmp	exact_match,0
	je	copylocal_subdir
	cmp	di,ax
	je	copylocal_compare
    copylocal_copy:
	call	ocopy
	jz	copylocal_error
    copylocal_next:
	jmp	copylocal_loop
    copylocal_subdir:
	cmp	ax,di
	jbe	copylocal_copy
    copylocal_compare:
	push	bx
	add	bx,SIZE S_LZIP
	invoke	strnicmp,addr __outpath,es::bx,di
	pop	bx
	jnz	copylocal_copy
    copylocal_found:
	inc	si
	mov	ax,es:[bx].S_LZIP.lz_extsize
	mov	[bp-6],ax
	mov	ax,es:[bx].S_LZIP.lz_fnsize
	push	ax
	add	bx,SIZE S_LZIP
	and	ax,01FFh
	invoke	memcpy,addr entryname,es::bx,ax
	pop	bx
	add	bx,ax
	mov	byte ptr es:[bx],0
	lodm	STDO.ios_total
	add	ax,STDO.ios_i
	adc	dx,0
	mov	[bp-2],dx
	mov	[bp-4],ax
	pop	cx
	pop	bx
	add	ax,cx
	adc	dx,bx
	invoke	oseek,dx::ax,SEEK_SET
	jnz	copylocal_next
	mov	ax,-1
    copylocal_end:
	mov	dx,[bp-2]
	mov	cx,[bp-4]
	mov	bx,[bp-6]
	ret
zip_copylocal endp

zip_copycentral proc _CType uses si di loffset:dword,
	lsize:dword, exact_match:byte
	invoke	strlen,addr __outpath
	mov	di,ax
	xor	si,si
    copycentral_loop:
	mov	ax,SIZE S_ZEND
	call	oread
	jnz	copycentral_03
    copycentral_ioerror:
	mov	si,-1
    copycentral_end:
	mov	ax,si
	ret
    copycentral_03:
	cmp	es:[bx].S_CZIP.cz_pkzip,ZIPHEADERID	; 'PK'	4B50h
	jne	copycentral_ioerror
	cmp	es:[bx].S_CZIP.cz_zipid,ZIPCENTRALID	; 1,2	0201h
	jne	copycentral_end
	mov	ax,SIZE S_CZIP
	call	oread
	jz	copycentral_ioerror
	mov	ax,SIZE S_CZIP
	add	ax,es:[bx].S_CZIP.cz_fnsize
	call	oread
	jz	copycentral_ioerror
	mov	ax,SIZE S_CZIP		; Central directory
	add	ax,es:[bx].S_CZIP.cz_fnsize	; file name length (*this)
	add	ax,es:[bx].S_CZIP.cz_extsize
	add	ax,es:[bx].S_CZIP.cz_cmtsize
	push	0
	push	ax			; = size of this record
  ifdef __3__
	mov	eax,loffset		; Update local offset if above
	cmp	es:[bx].S_CZIP.cz_off_local,eax
	jb	copycentral_06
	mov	eax,lsize
	sub	es:[bx].S_CZIP.cz_off_local,eax
  else
	mov	ax,word ptr loffset+2	; Update local offset if above
	cmp	word ptr es:[bx].S_CZIP.cz_off_local[2],ax
	jb	copycentral_06
	ja	copycentral_05
	mov	ax,word ptr loffset
	cmp	word ptr es:[bx].S_CZIP.cz_off_local,ax
	jb	copycentral_06
    copycentral_05:
	lodm	lsize
	sub	word ptr es:[bx].S_CZIP.cz_off_local,ax
	sbb	word ptr es:[bx].S_CZIP.cz_off_local[2],dx
  endif
    copycentral_06:
	test	si,si
	jnz	copycentral_copy	; already found -- deleted
	mov	ax,es:[bx].S_CZIP.cz_fnsize
	cmp	exact_match,0
	je	copycentral_subdir
	cmp	di,ax
	jne	copycentral_copy
    copycentral_subdir:
	cmp	di,ax
	ja	copycentral_copy
	add	bx,SIZE S_CZIP
	invoke	strnicmp,addr __outpath,es::bx,di
	test	ax,ax
	jz	copycentral_delete
    copycentral_copy:
	call	ocopy
	jz	copycentral_error
    copycentral_next:
	jmp	copycentral_loop
    copycentral_delete:
	inc	si
	push	SEEK_CUR
	call	oseek
	jnz	copycentral_next
    copycentral_error:
	jmp	copycentral_ioerror
zip_copycentral endp

;-------------------------------------------------------------------------------
; Read
;-------------------------------------------------------------------------------

getendcentral proc pascal private wsub:dword, zend:dword
	invoke wsopenarch, wsub
	mov STDI.S_IOST.ios_file,ax
	inc ax
	.if ax
	    invoke oseekl,0,SEEK_END
	    .if !ZERO?
		mov ax,word ptr STDI.ios_offset
		stom arc_flength
		.if dx || ax >= SIZE S_ZEND
		    call oungetc
		    .if !ZERO? && STDI.ios_i >= SIZE S_ZEND-1
			sub STDI.ios_i,SIZE S_ZEND-2
			.while 1
			    call oungetc
			    .if !ZERO?
				.if al != 'P'
				    .continue
				.endif
				mov ax,SIZE S_ZEND
				call oread
				.if !ZERO?
				    lodm es:[bx]
				    .if ax != ZIPHEADERID || dx != ZIPENDSENTRID
					.continue
				    .endif
				    invoke memcpy,zend,es::bx,SIZE S_ZEND
				    mov ax,1
				    jmp @F
				.endif
				.break
			    .endif
			    .break
			.endw
		    .endif
		.endif
	    .endif
	    invoke close,STDI.ios_file
	    xor ax,ax
	.endif
      @@:
	or ax,ax
	ret
getendcentral endp

zip_allocfblk proc private
	push si
	push di
	mov si,offset entryname
	mov di,ax
	invoke strlen,ds::si
	add ax,SIZE S_FBLK
	push ax
	add ax,12
	invoke malloc,ax
	pop cx
	.if !ZERO?
	    mov bx,ax
	    mov ax,zip_central.cz_ext_attrib
	    and ax,_A_FATTRIB
	    or	ax,zip_attrib
	    mov es,dx
	    mov es:[bx],ax
	    .if di == 2
		mov di,cx
		.if zip_central.cz_version_made == 0
		    .if byte ptr zip_central.cz_ext_attrib & _A_SUBDIR
			jmp @F
		    .endif
		.endif
		mov ax,zip_attrib
		or  ax,_A_SUBDIR
		mov es:[bx],ax
	    .else
		mov di,cx
		movmx es:[bx].S_FBLK.fb_size,zip_central.cz_fsize
	    .endif
	  @@:
	    push dx
	    push bx
	    mov ax,zip_central.cz_date
	    mov word ptr es:[bx].S_FBLK.fb_time[2],ax
	    mov ax,zip_central.cz_time
	    mov word ptr es:[bx].S_FBLK.fb_time,ax
	    add bx,S_FBLK.fb_name
	    invoke strcpy,dx::bx,ds::si
	    sub ax,S_FBLK.fb_name
	    add di,ax
ifdef __3__
	    mov eax,zip_central.cz_off_local
	    stosd
	    mov eax,zip_central.cz_csize
	    stosd
	    mov eax,zip_central.cz_crc
	    stosd
else
	    mov ax,word ptr zip_central.cz_off_local
	    stosw
	    mov ax,word ptr zip_central.cz_off_local+2
	    stosw
	    mov ax,word ptr zip_central.cz_csize
	    stosw
	    mov ax,word ptr zip_central.cz_csize+2
	    stosw
	    mov ax,word ptr zip_central.cz_crc
	    stosw
	    mov ax,word ptr zip_central.cz_crc+2
	    stosw
endif
	    pop ax
	    pop dx
	.endif
	pop di
	pop si
	ret
zip_allocfblk endp

zip_readcentral proc private
	push	si
	push	di
	mov	ax,SIZE S_CZIP
	call	oread
	jz	toend
	sub	ax,ax
	cmp	es:[bx].S_CZIP.cz_pkzip,ZIPHEADERID
	jne	toend
	cmp	es:[bx].S_CZIP.cz_zipid,ZIPCENTRALID
	jne	toend
	add	STDI.ios_i,SIZE S_CZIP
	dec	ax
	mov	dx,arc_pathz
	cmp	es:[bx].S_CZIP.cz_fnsize,dx
	jbe	toend
	mov	ax,es
	mov	ds,ax
	mov	ax,ss
	mov	es,ax
	mov	di,offset zip_central
	mov	si,bx
	mov	ax,cx
	mov	cx,SIZE S_CZIP / 2
	cld?
	rep	movsw
	mov	cx,[bx].S_CZIP.cz_fnsize
	add	bx,SIZE S_CZIP
	sub	ax,SIZE S_CZIP
	cmp	ax,cx
	jae	@F
	mov	ax,ss
	mov	ds,ax
	mov	ax,cx
	call	oread
	jz	toend
	mov	cx,zip_central.cz_fnsize
	mov	ax,es
	mov	ds,ax
	mov	ax,ss
	mov	es,ax
@@:
	mov	si,bx
	mov	di,offset entryname
	mov	ah,'\'
@@:
	test	cx,cx
	jz	@F
	dec	cx
	mov	al,[si]
	mov	es:[di],al
	inc	di
	inc	si
	cmp	al,'/'
	jne	@B
	mov	es:[di-1],ah
	jmp	@B
@@:
	mov	ax,ss
	mov	ds,ax
	mov	byte ptr [di],0
	mov	ax,zip_central.cz_fnsize
	add	STDI.ios_i,ax
	mov	cx,ax
	mov	ax,_A_ARCHZIP or _A_ARCH
	test	byte ptr zip_central.cz_bitflag,1
	jz	@F
	or	ax,_A_ZENCRYPTED
@@:
	test	byte ptr zip_central.cz_bitflag,8
	jz	@F
	or	ax,_A_ZEXTLOCHD
@@:
	mov	zip_attrib,ax
	mov	ax,'\'
	dec	di
	cmp	[di],al
	jne	@F
	mov	[di],ah
	or	zip_attrib,_A_SUBDIR
	dec	zip_central.cz_fnsize
@@:
	mov	di,zip_central.cz_extsize
	add	di,zip_central.cz_cmtsize
	jz	@F
	mov	ax,di
	call	oread
	jz	toend
	add	STDI.ios_i,di
@@:
	mov	ax,1
toend:
	test	ax,ax
	pop	di
	pop	si
	ret
zip_readcentral endp

zip_testcentral proc pascal private uses si di wsub:dword
	mov si,offset entryname
	les di,[di].S_WSUB.ws_arch
	mov al,[di]
	.if al
	    mov al,0
	    mov cx,arc_pathz
	    inc cx
	    @@:
		dec cx
		jz @F
		mov al,[si]
		mov ah,[di]
		inc si
		inc di
		cmp ah,al
		je @B
		or ax,2020h
		cmp ah,al
		je @B
	    @@:
	    sub al,ah
	    mov ax,0
	    jnz @F
	.endif
	mov si,word ptr wsub
	sub di,word ptr [si].S_WSUB.ws_arch
	mov si,offset entryname
	.if di
	    .if [di+entryname] == '\'
		mov ax,si
		inc ax
		add ax,di
		invoke strcpy, ds::si, ds::ax
	    .else
		jmp @F
	    .endif
	.endif
	.if entryname == ','
	    mov ax,si
	    inc ax
	    invoke strcpy,ds::si,ds::ax
	.endif
	invoke strchr,ds::si,'\'
	.if !ZERO?
	    mov bx,ax
	    mov byte ptr [bx],0
	    invoke wsearch,wsub,ds::si
	    .if ax == -1
		mov ax,2
	    .else
		xor ax,ax
	    .endif
	.else
	    invoke wsearch,wsub,ds::si
	    .if ax == -1
		mov ax,1
	    .else
		les bx,wsub
		les bx,es:[bx].S_WSUB.ws_fcb
		shl ax,2
		add bx,ax
		les bx,es:[bx]
		mov ax,zip_central.cz_date
		mov dx,zip_central.cz_time
		mov word ptr es:[bx].S_FBLK.fb_time,dx
		mov word ptr es:[bx].S_FBLK.fb_time[2],ax
		.if zip_central.cz_version_made == 0
		    mov ax,zip_central.cz_ext_attrib
		    or	ax,zip_attrib
		    and ax,_A_FATTRIB
		    mov es:[bx],ax
		.endif
		xor ax,ax
	    .endif
	.endif
      @@:
	ret
zip_testcentral endp

zip_findnext proc private
	call zip_readcentral
	.while ax
	    inc ax
	    .if ax
		invoke zip_testcentral, si::di
	    .else
		mov ax,es:[bx].S_CZIP.cz_extsize
		add ax,es:[bx].S_CZIP.cz_cmtsize
		add ax,es:[bx].S_CZIP.cz_fnsize
		push ax
		call oread
		pop dx
		.break .if ZERO?
		add STDI.ios_i,dx
		xor ax,ax
	    .endif
	    .if ax
		call zip_allocfblk
		.break
	    .endif
	    call zip_readcentral
	.endw
	ret
zip_findnext endp

wzipread proc _CType public uses si di wsub:dword
local	alloc:byte
local	fblk:dword
local	rbuf[8192]:byte
	sub ax,ax
	mov STDI.ios_i,ax
	mov STDI.ios_c,ax
	mov STDI.ios_flag,ax
	mov alloc,al
	invoke malloc,64000
	.if ax
	    mov cx,64000
	    mov alloc,1
	.else
	    lea ax,rbuf
	    mov dx,ss
	    mov cx,8192
	.endif
	mov STDI.ios_size,cx
	stom STDI.ios_bp
	les bx,wsub
	invoke strlen,es:[bx].S_WSUB.ws_arch
	mov arc_pathz,ax
	mov si,word ptr wsub+2
	mov di,word ptr wsub
	invoke wsfree,si::di
	invoke getendcentral,si::di,addr zip_endcent
	.if ZERO?
	    mov ax,-2
	.else
	    invoke fbupdir,_A_ARCHZIP
	    mov es,si
	    mov es:[di].S_WSUB.ws_count,1
	    les bx,es:[di].S_WSUB.ws_fcb
	    stom es:[bx]
	    invoke oseek,zip_endcent.ze_off_cent,SEEK_SET
	    call zip_findnext
	    stom fblk
	    .while ax
		mov bx,ax
		mov al,es:[0004h]
		.if al & _A_SUBDIR
		  @@:
		    mov es,si
		    mov ax,es:[di].S_WSUB.ws_count
		    les bx,es:[di].S_WSUB.ws_fcb
		    shl ax,2
		    add bx,ax
		    movmx es:[bx],fblk
		    mov es,si
		    inc es:[di].S_WSUB.ws_count
		    mov ax,es:[di].S_WSUB.ws_count
		    .break .if ax >= es:[di].S_WSUB.ws_maxfb
		.else
		    add bx,S_FBLK.fb_name
		    mov es,si
		    invoke cmpwarg,dx::bx,es:[di].S_WSUB.ws_mask
		    jnz @B
		    invoke free,fblk
		.endif
		call zip_findnext
		stom fblk
	    .endw
	    invoke close,STDI.ios_file
	    mov es,si
	    mov ax,es:[di]
	.endif
	.if alloc
	    mov si,ax
	    invoke free,STDI.ios_bp
	    mov ax,si
	.endif
	ret
wzipread endp

;-------------------------------------------------------------------------------
; Copy
;-------------------------------------------------------------------------------

wzipfindentry proc _CType private uses si di fblk:dword, ziph:size_t
	mov si,ziph
	les di,fblk
	invoke strlen, addr es:[di].S_FBLK.fb_name
	add ax,SIZE S_FBLK
	add di,ax
	invoke lseek,si,es:[di],SEEK_SET
	invoke osread,si,addr zip_local,SIZE S_LZIP
	.if ax == SIZE S_LZIP && zip_local.lz_pkzip == ZIPHEADERID && \
	    zip_local.lz_zipid == ZIPLOCALID
	    mov ax,zip_local.lz_fnsize
	    add ax,zip_local.lz_extsize
	    invoke lseek, si, ax, SEEK_CUR
	    .if zip_local.lz_flag & 8
		les ax,fblk
		movmx zip_local.lz_crc,es:[di+4]
		movmx zip_local.lz_csize,es:[di+8]
	    .endif
	    mov ax,1
	.else
	    sub ax,ax
	.endif
	test ax,ax
	ret
wzipfindentry endp

wzipcopyfile proc _CType private uses si di wsub:dword, fblk:dword, out_path:dword
local fhandle:word
local fname[WMAXPATH*2]:byte
    .if filter_fblk(fblk)
	.if wsopenarch(wsub) != -1
	    mov si,ax
	    .if wzipfindentry(fblk,si)
		lea di,fname
		les bx,fblk
		invoke strfcat,ss::di,out_path,addr es:[bx].S_FBLK.fb_name
		les bx,fblk
		.if !progress_set(addr es:[bx].S_FBLK.fb_name,out_path,es:[bx].S_FBLK.fb_size)
		    .if SWORD ptr ogetouth(ss::di) > 0
			mov fhandle,ax
			mov dx,ax
			les bx,fblk
			mov ax,es:[bx]
			mov zip_attrib,ax
			mov ax,si
			call unzip
			push ax
			invoke close,si
			les bx,fblk
			pop ax
			.if !ax
			  ifdef __LFN__
			    .if _ifsmgr
				invoke close,fhandle
				les bx,fblk
				lodm es:[bx].S_FBLK.fb_time
				invoke wsetwrdate,ss::di,dx,ax
			    .else
			  endif
			    invoke _dos_setftime,fhandle,
				word ptr es:[bx].S_FBLK.fb_time+2,
				word ptr es:[bx].S_FBLK.fb_time
			    invoke close,fhandle
			  ifdef __LFN__
			    .endif
			  endif
			    les bx,fblk
			    mov ax,es:[bx]
			    and ax,_A_FATTRIB
			    invoke _dos_setfileattr,ss::di,ax
			    sub ax,ax
			.else
			    mov si,fhandle
			    push ax
			    invoke remove,ss::di
			    pop ax
			    .if ax == ER_USERABORT
				jmp @F
			    .endif
			    mov di,ax
			    mov dx,offset CP_ENOMEM
			    .if ax == ER_MEM
				mov ax,dx
			    .elseif ax == ER_DISK
				mov ax,offset CP_DOSER20
			    .else
				mov dx,offset CP_DOSER04
				mov ax,offset cp_emarchive
			    .endif
			    invoke ermsg,ds::ax,ds::dx
			    mov ax,di
			    jmp @F
			.endif
		    .else
			jmp @F
		    .endif
		.else
		    jmp @F
		.endif
	    .else
		lodm fblk
		add ax,S_FBLK.fb_name
		invoke ermsg,addr CP_ENOENT,addr format_s,dx::ax
		mov ax,ER_FIND
	      @@:
		push ax
		invoke close,si
		pop ax
	    .endif
	.else
	    mov ax,ER_NOZIP
	.endif
    .endif
    ret
wzipcopyfile endp

S_ZSUB		STRUC
zs_wsub		S_WSUB <>
zs_off_path	dw ?
zs_off_file	dw ?
zs_index	dw ?
zs_result	dw ?
S_ZSUB		ENDS

wzipcopypath proc _CType private uses si di wsub:dword, fblk:dword, out_path:dword
local	zs:S_ZSUB
	lea	di,zs
	les	bx,wsub
	movmx	zs.zs_wsub.ws_path,es:[bx].S_WSUB.ws_path
	movmx	zs.zs_wsub.ws_file,es:[bx].S_WSUB.ws_file
	movmx	zs.zs_wsub.ws_mask,es:[bx].S_WSUB.ws_mask
	mov	si,offset scan_fblock
	mov	[si].S_PATH.wp_flag,_W_SORTSIZE
	mov	ax,si
	mov	dx,ds
	stom	zs.zs_wsub.ws_flag
	add	ax,S_PATH.wp_arch
	stom	zs.zs_wsub.ws_arch
	mov	zs.zs_wsub.ws_count,0
	mov	zs.zs_wsub.ws_maxfb,DC_MAXOBJ
	push	dx
	push	ax
	lodm	fblk
	add	ax,S_FBLK.fb_name
	les	bx,es:[bx].S_WSUB.ws_arch
	.if byte ptr es:[bx]
	    push es
	    push bx
	    push dx
	    push ax
	    call strfcat
	.else
	    push dx
	    push ax
	    call strcpy
	.endif
	add si,S_PATH.wp_file
	les bx,fblk
	invoke strfcat,ds::si,out_path,addr es:[bx].S_FBLK.fb_name
	.if mkdir(ds::si) != -1
	    .if !_dos_setfileattr(ds::si,0)
		les bx,fblk
		mov ax,es:[bx]
		and ax,_A_FATTRIB
		and ax,not _A_SUBDIR
		invoke _dos_setfileattr,ds::si,ax
	    .endif
	.endif
	push	ds
	push	si
	add	si,SIZE S_PATH.wp_file
	invoke	strlen,ds::si
	add	ax,si
	mov	zs.zs_off_file,ax
	call	strlen
	sub	si,SIZE S_PATH.wp_file
	add	ax,si
	mov	zs.zs_off_path,ax
	les	bx,fblk
	invoke	progress_set,addr es:[bx].S_FBLK.fb_name,out_path,0
	jnz	wzipcopypath_end
	invoke	wsopen,ss::di
	test	ax,ax
	jnz	wzipcopypath_read
	dec	ax
	jmp	wzipcopypath_end
    wzipcopypath_read:
	invoke	wzipread,ss::di
	cmp	ax,1
	ja	wzipcopypath_sort
	invoke	wsclose,ss::di
	xor	ax,ax
    wzipcopypath_end:
	ret
    wzipcopypath_warning:
	invoke	stdmsg,addr cp_warning,addr cp_emaxfb,ax,ax
	jmp	wzipcopypath_max
    wzipcopypath_sort:
	invoke	wssort,ss::di
	mov	ax,[di].S_WSUB.ws_maxfb
	cmp	ax,[di].S_WSUB.ws_count
	je	wzipcopypath_warning
    wzipcopypath_max:
	mov	ax,[di].S_WSUB.ws_count
	dec	ax
	mov	zs.zs_index,ax
	xor	ax,ax
	mov	zs.zs_result,ax
    wzipcopypath_next:
	cmp	byte ptr zs.zs_result,0
	jne	wzipcopypath_close
	mov	ax,zs.zs_index
	cmp	ax,1
	jl	wzipcopypath_close
	les	bx,[di].S_WSUB.ws_fcb
	shl	ax,2
	add	bx,ax
	mov	dx,es:[bx+2]
	mov	bx,es:[bx]
	mov	es,dx
	mov	ax,es:[bx]
	and	ax,_A_SUBDIR
	jz	wzipcopypath_file
	invoke	wzipcopypath,ss::di,dx::bx,ds::si
	mov	zs.zs_result,ax
	xor	al,al
	mov	bx,zs.zs_off_file
	mov	[bx],al		; *a = 0;
	mov	bx,zs.zs_off_path
	mov	[bx],al		; *p = 0;
	jmp	wzipcopypath_free
    wzipcopypath_close:
	invoke	wsclose,ss::di
	mov	ax,zs.zs_result
	jmp	wzipcopypath_end
    wzipcopypath_file:
	push	dx
	push	bx
	invoke	progress_set,addr es:[bx].S_FBLK.fb_name,out_path,es:[bx].S_FBLK.fb_size
	mov	zs.zs_result,ax
	pop	bx
	pop	dx
	jnz	wzipcopypath_close
	invoke	wzipcopyfile,ss::di,dx::bx,ds::si
	mov	zs.zs_result,ax
    wzipcopypath_free:
	les	bx,[di].S_WSUB.ws_fcb
	mov	ax,zs.zs_index
	shl	ax,2
	add	bx,ax
	xor	ax,ax
	pushm	es:[bx]
	mov	es:[bx],ax
	mov	es:[bx+2],ax
	call	free
	dec	zs.zs_index
	jmp	wzipcopypath_next
wzipcopypath endp

wzipcopy proc _CType public wsub:dword, fblk:dword, out_path:dword
	pushm wsub
	pushm fblk
	pushm out_path
	les bx,fblk
	.if byte ptr es:[bx] & _A_SUBDIR
	    call wzipcopypath
	.else
	    call wzipcopyfile
	.endif
	ret
wzipcopy endp

wsdecomp proc _CType public uses bx wsub:dword, fblk:dword, out_path:dword
	les bx,fblk
	.if es:[bx].S_FBLK.fb_flag & _A_ARCHIVE
	    invoke wzipcopy,wsub,fblk,out_path
	.else
	    call notsup
	    mov ax,-1
	.endif
	ret
wsdecomp endp

;-------------------------------------------------------------------------------
; Add
;-------------------------------------------------------------------------------

display_error:
	mov	ax,offset CP_DOSER20
	mov	dx,offset CP_ENOMEM
	test	STDO.ios_flag,IO_ERROR
	jnz	@F
	mov	ax,offset CP_ENOMEM
	cmp	errno,ENOMEM
	je	@F
	mov	ax,offset cp_emarchive
	mov	dx,offset CP_DOSER04
      @@:
	invoke	ermsg,ds::dx,ds::ax
	ret

zip_renametemp proc private
	invoke	oclose,addr STDI
	invoke	oclose,addr STDO
	invoke	filexist,ds::di		; 1 file, 2 subdir
	cmp	ax,1
	jne	@F
	invoke	remove,ds::si
	invoke	rename,ds::di,ds::si	; 0 or -1
	ret
      @@:
	mov	ax,-1
	ret
zip_renametemp endp

zip_copyendcentral proc _CType public
	push	si
	push	di
	mov	si,ax
	mov	di,dx
	call	otell
	sub	ax,word ptr zip_endcent.ze_off_cent
	sbb	dx,word ptr zip_endcent.ze_off_cent+2
	stom	zip_endcent.ze_size_cent
	mov	ax,SIZE S_ZEND
	call	oread
	jz	copyendcentral_fail
	invoke	memcpy,es::bx,addr zip_endcent,SIZE S_ZEND
	mov	ax,zip_endcent.ze_comment_size
	add	ax,SIZE S_ZEND
	invoke	ocopy,cx::ax
	jz	copyendcentral_fail
	call	oflush
	jz	copyendcentral_fail
	movmx	arc_flength,STDO.ios_total
	call	zip_renametemp		; 0 or -1
      @@:
	pop	di
	pop	si
	ret
    copyendcentral_fail:
	dec	ax			; -1
	jmp	@B
zip_copyendcentral endp

update_local proc private
	cmpmm	zip_central.cz_off_local, STDO.ios_total
	jb	@F
	sub	ax,word ptr STDO.ios_total
	mov	dx,word ptr STDO.ios_bp+2
	add	ax,word ptr STDO.ios_bp
	invoke	memcpy,dx::ax,addr zip_local,SIZE S_LZIP
	ret
      @@:
	call	oflush
	jz	@F
	invoke	lseek,STDO.ios_file,zip_central.cz_off_local,SEEK_SET
	invoke	oswrite,STDO.ios_file,addr zip_local,SIZE S_LZIP
	invoke	lseek,STDO.ios_file,0,SEEK_END
      @@:
	ret
update_local endp

mkarchivetmp proc private
	invoke	strcpy,ss::ax,addr __outfile
	invoke	setfext,dx::ax,addr cp_ziptemp
	ret
mkarchivetmp endp

set_progress proc private
	invoke	progress_set,addr __outfile,ss::bx,dx::ax
	mov	STDO.ios_flag,IO_USEUPD or IO_UPDTOTAL
	ret
set_progress endp

initentry proc private			; AX	offset file name buffer
	push	ax			; BX	time
	mov	ax,bx			; DI	date
	mov	zip_local.lz_time,ax	; CX:DX size
	mov	zip_central.cz_time,ax	; SI	attrib
	mov	ax,di
	mov	zip_local.lz_date,ax
	mov	zip_central.cz_date,ax
  ifdef __3__
	mov	eax,edx
	mov	zip_local.lz_fsize,eax
	mov	zip_local.lz_csize,eax
	mov	zip_central.cz_fsize,eax
	mov	zip_central.cz_csize,eax
  else
	mov	ax,cx
	mov	word ptr zip_local.lz_fsize+2,ax
	mov	word ptr zip_local.lz_csize+2,ax
	mov	word ptr zip_central.cz_fsize+2,ax
	mov	word ptr zip_central.cz_csize+2,ax
	mov	ax,dx
	mov	word ptr zip_local.lz_fsize,ax
	mov	word ptr zip_local.lz_csize,ax
	mov	word ptr zip_central.cz_fsize,ax
	mov	word ptr zip_central.cz_csize,ax
  endif
	mov	ax,si
	and	ax,_A_FATTRIB
	mov	zip_central.cz_ext_attrib,ax
	pop	ax
	invoke	strcpy,ss::ax,addr __outpath
	test	si,_A_SUBDIR
	jnz	@F
	invoke	unixtodos,dx::ax
	push	ax
	invoke	strfn,addr __srcfile
	pop	cx
	invoke	strfcat,ss::cx,0,dx::ax
	invoke	dostounix,dx::ax
      @@:
	invoke	strlen,dx::ax
	mov	zip_local.lz_fnsize,ax
	mov	zip_central.cz_fnsize,ax
	ret
initentry endp

clearentry proc private
	invoke	memzero,addr zip_local,SIZE S_LZIP
	invoke	memzero,addr zip_central,SIZE S_CZIP
	mov	zip_local.lz_pkzip,ZIPHEADERID
	mov	zip_local.lz_zipid,ZIPLOCALID
	mov	byte ptr zip_local.lz_version,20
	mov	zip_central.cz_pkzip,ZIPHEADERID
	mov	zip_central.cz_zipid,ZIPCENTRALID
	mov	byte ptr zip_central.cz_version_made,20
	mov	byte ptr zip_central.cz_version_need,10
	ret
clearentry endp

compress proc private
  ifdef __3__
	cmp	zip_local.lz_fsize,2
	jb	@F
  else
	cmp	word ptr zip_local.lz_fsize+2,0
	jne	compress_00
	cmp	word ptr zip_local.lz_fsize,2
	jb	@F
    compress_00:
  endif
	cmp	compresslevel,0
	je	@F
	mov	STDI.ios_size,8000h
	invoke	zip_deflate,compresslevel
	ret
      @@:
	invoke	ocopy,zip_local.lz_fsize
	ret
compress endp

initcrc proc private
	sub	ax,ax
	mov	al,file_method
	mov	zip_local.lz_method,ax
	mov	zip_central.cz_method,ax
  ifdef __3__
	mov	eax,STDI.ios_bb
	not	eax
	mov	zip_local.lz_crc,eax
	mov	zip_central.cz_crc,eax
  else
	mov	ax,word ptr STDI.ios_bb
	not	ax
	mov	word ptr zip_local.lz_crc,ax
	mov	word ptr zip_central.cz_crc,ax
	mov	ax,word ptr STDI.ios_bb+2
	not	ax
	mov	word ptr zip_local.lz_crc+2,ax
	mov	word ptr zip_central.cz_crc+2,ax
  endif
	invoke	oclose,addr STDI
	ret
initcrc endp

popstdi proc private
	mov	ax,OSTDI
	invoke	memcpy,ds::ax,ss::si,SIZE S_IOST
	sub	ax,ax
	ret
popstdi endp

wzipopen proc _CType public uses si di
local	arch[384]:byte
	call	clearentry
	mov	si,offset entryname
	invoke	strcpy,ds::si,addr __outfile
	lea	ax,arch
	mov	di,ax
	call	mkarchivetmp
	invoke	strfn,ds::si
	invoke	strcpy,dx::ax,addr centtmp
	mov	ax,offset __outfile
	mov	dx,di
	call	wscopy_open
	inc	ax		; (-1) -> (0)
	jz	wzipopen_end	; error
	dec	ax		; (1) --> (0)
	jnz	wzipopen_openc	; cancel
    wzipopen_end:
	test	ax,ax
	ret
    wzipopen_ioerror:
	invoke	close,centhnd
	invoke	remove,ds::si
    wzipopen_eropen:
	mov	ax,di
	call	wscopy_remove
	sub	ax,ax
	jmp	wzipopen_end
    wzipopen_openc:
	invoke	ogetouth,ds::si
	mov	centhnd,ax
	dec	ax
	jz	wzipopen_eropen
	lea	bx,arch
	lodm	arc_flength
	call	set_progress
	invoke	ocopy,zip_endcent.ze_off_cent
	jz	wzipopen_ioerror
	call	oflush
	jz	wzipopen_ioerror
    wzipopen_lzero:
	push	STDO.ios_file
	mov	ax,centhnd
	mov	STDO.ios_file,ax
	invoke	ocopy,zip_endcent.ze_size_cent
	jz	wzipopen_errcpy
	call	oflush
	jz	wzipopen_errcpy
	pop	ax
	mov	STDO.ios_file,ax
  ifdef __3__
	mov	eax,zip_endcent.ze_size_cent
	sub	STDO.ios_total,eax
  else
	lodm	zip_endcent.ze_size_cent
	sub	word ptr STDO.ios_total,ax
	sbb	word ptr STDO.ios_total+2,dx
  endif
    wzipopen_zero:
	mov	STDO.ios_flag,0
	invoke	oclose,addr STDI
	mov	ax,1
	jmp	wzipopen_end
    wzipopen_errcpy:
	pop	ax
	mov	STDO.ios_file,ax
	jmp	wzipopen_ioerror
wzipopen endp

wzipclose proc _CType public uses si di
local	arch[384]:byte
	mov	si,ax		; result
	lea	ax,arch
	mov	di,ax
	call	mkarchivetmp
	test	si,si
	jnz	wzipclose_remove
	mov	bx,centhnd
	mov	ax,4200h + SEEK_CUR
	xor	cx,cx
	mov	dx,cx
	int	21h
	jc	wzipclose_remove
	stom	zip_endcent.ze_size_cent
	lea	bx,arch
	call	set_progress
	invoke	close,centhnd
	mov	STDI.ios_size,8000h
	invoke	oopen,addr entryname, M_RDONLY
	inc	ax
	jz	wzipclose_remove
	invoke	ocopy,zip_endcent.ze_size_cent
	test	ax,ax
	jz	wzipclose_close
	push	ds
	pop	es
	mov	cx,SIZE S_ZEND
	mov	bx,offset zip_endcent
	call	owrite
	jz	wzipclose_close
	mov	si,zip_endcent.ze_comment_size
	test	si,si
	jnz	wzipclose_comment
    wzipclose_rename:
	call	oflush
	jz	wzipclose_close
	mov	si,offset __outfile
	call	zip_renametemp
	inc	ax
	jz	wzipclose_remove
    wzipclose_remcent:
	invoke	remove,addr entryname
    wzipclose_end:
	ret
    wzipclose_remove:
	invoke	close,centhnd
    wzipclose_remout:
	mov	ax,di
	call	wscopy_remove
	call	display_error
	jmp	wzipclose_remcent
    wzipclose_close:
	invoke	oclose,addr STDI
	jmp	wzipclose_remout
    wzipclose_comment:
	invoke	close,STDI.ios_file
	invoke	openfile,addr __outfile,M_RDONLY,A_OPEN
	mov	STDI.ios_file,ax
	mov	bx,ax
	inc	ax
	jz	wzipclose_close
	mov	ax,4200h + SEEK_END
	xor	cx,cx
	mov	dx,cx
	sub	dx,si
	sbb	cx,0
	int	21h
	jc	wzipclose_close
	sub	ax,ax
	mov	STDI.ios_c,ax
	mov	STDI.ios_i,ax
	invoke	ocopy,ax::si
	jz	wzipclose_close
	jmp	wzipclose_rename
wzipclose endp

wzipadd proc _CType public uses si di fsize:dword, ftime:dword, fattrib:size_t
local	ios:S_IOST
local	ztemp[384]:byte
local	zpath[384]:byte
local	copyl_ax:word
local	copyl_cx:word
local	copyl_dx:word
local	local_size:dword
local	deflate_begin:dword
	mov	di,word ptr ftime+2
	mov	si,fattrib
	xor	ax,ax
	mov	errno,ax
	mov	file_method,al
	cmp	copy_fast,0
	jne	@F
	jmp	wzipadd_slow
      @@:
	lea	ax,zpath
	mov	bx,word ptr ftime
  ifdef __3__
	mov	edx,fsize
  else
	mov	dx,word ptr fsize
	mov	cx,word ptr fsize+2
  endif
	call	initentry
  ifdef __3__
	xor	eax,eax
	mov	zip_local.lz_crc,eax
	mov	zip_central.cz_crc,eax
	mov	zip_central.cz_off_local,eax
  else
	sub	ax,ax
	mov	word ptr zip_local.lz_crc,ax
	mov	word ptr zip_local.lz_crc+2,ax
	mov	word ptr zip_central.cz_crc,ax
	mov	word ptr zip_central.cz_crc+2,ax
	mov	word ptr zip_central.cz_off_local,ax
	mov	word ptr zip_central.cz_off_local+2,ax
  endif
	test	si,_A_SUBDIR
	jnz	wzipfast_subdir
	dec	ax
	mov	STDI.ios_size,ax
	call	otell
	stom	zip_central.cz_off_local
	invoke	oopen,addr __srcfile,M_RDONLY
	mov	STDI.ios_size,ISIZE
	inc	ax
	jnz	@F
	;
	; v2.33 continue if error open source
	;
	jmp	wzipfast_end
    wzipfast_error:
	invoke	oclose,addr STDO
	invoke	close,centhnd
	invoke	remove,addr entryname
	mov	ax,-1
	jmp	wzipfast_end
    wzipfast_ercopy:
	invoke	oclose,addr STDI
	jmp	wzipfast_error
      @@:
	push	ds
	pop	es
	mov	bx,offset zip_local
	mov	cx,SIZE S_LZIP
	call	owrite
	jz	wzipfast_ercopy
	lea	bx,zpath
	mov	cx,zip_local.lz_fnsize
	call	owrite
	jz	wzipfast_ercopy
	mov	STDI.ios_flag,IO_USECRC or IO_USEUPD or IO_UPDTOTAL
	call	otell
	stom	deflate_begin
	call	compress
	test	ax,ax
	jz	wzipfast_ercopy
	call	initcrc
    wzipfast_subdir:
	call	otell
	stom	zip_endcent.ze_off_cent
	test	byte ptr fattrib,_A_SUBDIR
	jnz	@F
	sub	ax,word ptr deflate_begin
	sbb	dx,word ptr deflate_begin+2
	stom	zip_local.lz_csize
	stom	zip_central.cz_csize
	call	update_local
      @@:
	invoke	oswrite,centhnd,addr zip_central,SIZE S_CZIP
	cmp	ax,SIZE S_CZIP
	je	@F
	jmp	wzipfast_error
      @@:
	invoke	oswrite,centhnd,addr zpath,zip_central.cz_fnsize
	cmp	ax,zip_central.cz_fnsize
	je	@F
	jmp	wzipfast_error
      @@:
	inc	zip_endcent.ze_entry_cur
	inc	zip_endcent.ze_entry_dir
	sub	ax,ax
	jmp	wzipfast_end
    ;--------------------------------------------------------------
    wzipadd_slow:	; do slow copy
    ;--------------------------------------------------------------
	movmx	progress_size,arc_flength
	call	clearentry
	invoke	strcpy, addr zpath, addr __outpath
	mov	ax,offset __outpath
	mov	bx,word ptr ftime
  ifdef __3__
	mov	edx,fsize
  else
	mov	dx,word ptr fsize
	mov	cx,word ptr fsize+2
  endif
	call	initentry
	lea	ax,ztemp
	call	mkarchivetmp
	mov	dx,ax
	mov	ax,offset __outfile
	call	wscopy_open
	cmp	ax,-1
	jne	@F
	jmp	wzipfast_end
      @@:
	mov	STDO.ios_flag,IO_USEUPD or IO_UPDTOTAL
	test	ax,ax
	jnz	@F
	inc	ax
	jmp	wzipfast_end
      @@:
	xor	ax,ax
	mov	word ptr local_size,ax
	mov	word ptr local_size+2,ax
	invoke	zip_copylocal,1
	mov	copyl_ax,ax	; result: 1 found, 0 not found, -1 error
	mov	copyl_cx,cx	; [cx:dx] offset local directory if found
	mov	copyl_dx,dx
	mov	cx,ax
	inc	ax
	jz	wzipadd_error
;	test	si,_A_SUBDIR
;	jnz	@F
	call	otell
	stom	zip_central.cz_off_local
      @@:
	dec	cx
	jnz	@F
	mov	cx,word ptr zip_endcent.ze_off_cent+2
	mov	bx,word ptr zip_endcent.ze_off_cent
	sub	bx,ax
	sbb	cx,dx
	mov	word ptr local_size+2,cx
	mov	word ptr local_size,bx
      @@:
	invoke	memcpy,addr ios,addr STDI,SIZE S_IOST
	test	si,_A_SUBDIR
	lea	si,ios
	jnz	@F;wzipslow_subdir
	mov	file_method,0
	mov	STDI.ios_size,-1
	invoke	oopen,addr __srcfile,M_RDONLY
	mov	STDI.ios_size,ISIZE
	cmp	ax,-1
	jne	@F
	call	popstdi
	;
	; v2.33 continue if error open source
	;
	jmp	wzipadd_skip
      @@:
	push	ds
	pop	es
	mov	bx,offset zip_local
	mov	cx,SIZE S_LZIP
	call	owrite
	jz	wzipadd_ersource
	mov	bx,offset __outpath
	mov	cx,zip_local.lz_fnsize
	call	owrite
	jz	wzipadd_ersource
	mov	STDI.ios_flag,IO_USECRC or IO_USEUPD or IO_UPDTOTAL
	and	STDO.ios_flag,not IO_USEUPD
	call	otell
	stom	deflate_begin
	invoke	progress_set,addr __srcfile,addr __outfile,fsize
	jnz	wzipadd_ersource
	test	byte ptr fattrib,_A_SUBDIR
	jnz	wzipslow_subdir
	call	compress
	test	ax,ax
	jnz	wzipadd_zerofile
   wzipadd_ersource:
	invoke	oclose,addr STDI
	call	popstdi
	jmp	wzipadd_error
   wzipadd_zerofile:
	call	initcrc
	call	popstdi
	lea	bx,ztemp
	lodm	arc_flength
	call	set_progress
    wzipslow_subdir:
	call	otell
	stom	zip_endcent.ze_off_cent
;	test	byte ptr fattrib,_A_SUBDIR
;	jnz	@F
	sub	ax,word ptr deflate_begin
	sbb	dx,word ptr deflate_begin+2
	stom	zip_local.lz_csize
	stom	zip_central.cz_csize
	add	word ptr progress_size,ax
	adc	word ptr progress_size+2,dx
	call	update_local
      @@:
	mov	dx,copyl_dx
	mov	ax,copyl_cx
	invoke	zip_copycentral,dx::ax,local_size,1
	inc	ax
	jz	wzipadd_ioerror
	dec	ax			; if file or directory deleted
	jz	@F			; -- ask user to overwrite
	dec	zip_endcent.ze_entry_dir
	dec	zip_endcent.ze_entry_cur
	invoke	confirm_delete_file,addr __outpath,zip_central.cz_ext_attrib
	inc	ax
	jz	wzipadd_ioerror		; Cancel (-1)
	dec	ax
	jz	wzipadd_skip		; Jump (0)
	jmp	wzipslow_czip
      @@:
	cmp	copyl_ax,ax
	je	wzipslow_czip
	jmp	wzipadd_ioerror ; found local, not central == error
    wzipslow_czip:
	push	ds
	pop	es
	mov	bx,offset zip_central
	mov	cx,SIZE S_CZIP
	call	owrite
	jz	wzipadd_ioerror
	mov	bx,offset __outpath
	mov	cx,zip_central.cz_fnsize
	call	owrite
	jz	wzipadd_ioerror
	inc	zip_endcent.ze_entry_cur
	inc	zip_endcent.ze_entry_dir
	mov	ax,offset __outfile
	lea	dx,ztemp
	call	zip_copyendcentral
	inc	ax
	jz	wzipadd_ioerror
	jmp	wzipadd_ok
    wzipfast_end:
	test	ax,ax
	ret
    wzipadd_skip:
	invoke	oclose,addr STDI
	lea	ax,ztemp
	call	wscopy_remove
    wzipadd_ok:
	invoke	strcpy,addr __outpath,addr zpath
	sub	ax,ax
	jmp	wzipfast_end
    wzipadd_ioerror:
	sub	ax,ax
    wzipadd_error:
	mov	di,ax
	invoke	oclose,addr STDI
	lea	ax,ztemp
	call	wscopy_remove
	mov	ax,di
	inc	di
	jz	wzipfast_end
	call	display_error
	dec	ax
	jmp	wzipfast_end
wzipadd endp

;-------------------------------------------------------------------------------
; Make Directory
;-------------------------------------------------------------------------------

wzipmkdir proc _CType public uses bx wsub:dword, directory:ptr byte
	les	bx,wsub
	mov	dx,word ptr directory
	mov	__srcfile,0
	push	dx
	invoke	strfcat,addr __outfile,[bx].S_WSUB.ws_path,[bx].S_WSUB.ws_file
	pop	dx
	invoke	strfcat,addr __outpath,[bx].S_WSUB.ws_arch,ds::dx
	invoke	strcat,addr __outpath,addr foreslash
	invoke	dostounix,dx::ax
	call	dostime
	invoke	wzipadd,0,dx::ax,_A_SUBDIR
	ret
wzipmkdir endp

;-------------------------------------------------------------------------------
; Attrib
;-------------------------------------------------------------------------------

cmzipattrib proc _CType public wsub:word
	push si
	push di
	push bp
	mov si,dx	; SI:DI FBLK
	mov di,bx	; CX attrib
	mov bx,wsub
	.if !(cl & _A_SUBDIR)
	    mov bp,cx
	    .if wsopenarch(ds::bx) != -1
		push bp
		mov bp,ax
		;------------------------------------------------------------
		; CRC, compressed size and local offset stored at end of FBLK
		;------------------------------------------------------------
		mov ax,di
		add ax,S_FBLK.fb_name
		invoke strlen,si::ax
		add ax,SIZE S_FBLK
		add di,ax
		movmx zip_central.cz_crc,es:[di][4]
		movmx zip_central.cz_csize,es:[di][8]
		movmm zip_central.cz_off_local,es:[di]
		invoke lseek,bp,dx::ax,SEEK_SET ; seek to and read local offset
		invoke osread,bp,addr zip_local,SIZE S_LZIP
		pop di ; FBLK.flag
		.if ax == SIZE S_LZIP && word ptr zip_local.lz_zipid == ZIPLOCALID \
			&& word ptr zip_local.lz_pkzip == ZIPHEADERID
		    invoke osread,bp,addr entryname,zip_local.lz_fnsize
		    mov si,ax
		    invoke close,bp
		    .if si == zip_local.lz_fnsize
			mov bx,offset entryname
			add bx,si
			mov byte ptr [bx],0
			.if rsopen(IDD_DZZipAttributes)
			    push dx
			    push ax
			    push dx
			    push ax
			    mov si,es:[bx][4]
			    invoke dlshow,dx::ax
			    mov bx,si
			    add bx,0104h
			    mov dl,bh
			    invoke scpath,bx,dx,54,addr entryname
			    ; push info to stack
			    pushm zip_central.cz_crc
			    pushm zip_central.cz_csize
			    pushm zip_central.cz_off_local
			    and	 di,_A_FATTRIB
			    push di
			    mov	 cx,15
			    std
			    mov si,offset zip_local + SIZE S_LZIP - 2
			    .repeat
				lodsw
				push ax
			    .untilcxz
			    cld
			    ; print info to screen
			    add dl,03h
			    add bl,17h
			    mov cx,88
			    invoke scputf,bx,dx,0,cx,addr format_zx
			    add sp,18
			    add dl,07h
			    add bl,08h
			    invoke scputf,bx,dx,0,cx,addr format_zu
			    add sp,26
			    add dl,06h
			    add bl,12h
			    .if di & _A_RDONLY
				invoke scputc,bx,dx,1,'x'
			    .endif
			    inc dl
			    .if di & _A_HIDDEN
				invoke scputc,bx,dx,1,'x'
			    .endif
			    inc dl
			    .if di & _A_SYSTEM
				invoke scputc,bx,dx,1,'x'
			    .endif
			    inc dl
			    .if di & _A_ARCH
				invoke scputc,bx,dx,1,'x'
			    .endif
			    call dlevent
			    call dlclose
			.endif
		    .else
			xor ax,ax
		    .endif
		.else
		    invoke close,bp
		.endif
	    .endif
	.endif
	pop bp
	pop di
	pop si
	ret
cmzipattrib endp

;-------------------------------------------------------------------------------
; Delete
;-------------------------------------------------------------------------------

wsdeletearc proc _CType public
	push	bp
	push	si
	push	di
	mov	bp,ax	; SS:AX --> SS:BP = wsub
	mov	si,dx	; DX:AX --> SI:DI = fblk
	mov	di,bx
	xor	ax,ax
    delete_zip_file:
	mov	bx,ax
	test	ax,ax	; AX set if repeated call with same directory
	jz	@F
	mov	ax,offset entryname
	jmp	wzipdel_progress
      @@:
	push	bx
	mov	es,si
	mov	cx,es:[di]
	mov	dx,si
	mov	ax,di
	add	ax,S_FBLK.fb_name
	test	cl,_A_SUBDIR
	jz	@F
	invoke	confirm_delete_sub,dx::ax
	jmp	wzipdel_confirm
      @@:
	invoke	confirm_delete_file,dx::ax,cx
    wzipdel_confirm:
	pop	bx
	test	ax,ax
	jnz	@F
	jmp	wzipdel_end		; 0: Skip file
      @@:
	inc	ax
	jnz	@F
	jmp	wzipdel_cancel		; -1: Cancel
      @@:
	invoke	strfcat,addr __srcfile,[bp].S_WSUB.ws_path,[bp].S_WSUB.ws_file
	invoke	strcpy,addr __outfile,dx::ax
	invoke	setfext,dx::ax,addr cp_ziptemp
	mov	ax,di
	add	ax,S_FBLK.fb_name
	invoke	strfcat,addr __outpath,[bp].S_WSUB.ws_arch,si::ax
	invoke	dostounix,dx::ax
	mov	es,si
	test	byte ptr es:[di],_A_SUBDIR
	jz	@F
	invoke	strcat,dx::ax,addr foreslash
      @@:
	invoke	strcmp,addr __srcfile,addr __outfile
	test	ax,ax
	jnz	@F
	jmp	wzipdel_err
      @@:
	mov	ax,offset __outpath
    wzipdel_progress:
	push	bx
	invoke	progress_set,ds::ax,addr __srcfile,arc_flength
	mov	ax,offset __srcfile
	mov	dx,offset __outfile
	call	wscopy_open
	pop	bx
	cmp	ax,-1
	jne	@F
	jmp	zip_delete_end
      @@:
	mov	STDO.ios_flag,IO_UPDTOTAL or IO_USEUPD
	test	ax,ax
	jz	zip_delete_error
	xor	bx,1		; 0: match directory\*.*
	push	bx		; 1: exact match -- file or directory/
	push	bx
	call	zip_copylocal	; copy compressed data to temp file
	pop	es		; local offset in DX:CX if found
	inc	ax
	jz	zip_delete_error
	push	es
	push	dx		; Central directory
	push	cx		; offset local if found
	lodm	STDO.ios_total
	add	ax,STDO.ios_i
	adc	dx,0
	mov	cx,word ptr zip_endcent.ze_off_cent+2
	mov	bx,word ptr zip_endcent.ze_off_cent
	stom	zip_endcent.ze_off_cent
	sub	bx,ax
	sbb	cx,dx
	push	cx
	push	bx
	push	es
	call	zip_copycentral
	pop	bx
	dec	ax
	jnz	zip_delete_error	; must be found..
	xor	ax,ax		;-------- End Central Directory
	dec	zip_endcent.ze_entry_dir
	dec	zip_endcent.ze_entry_cur
	push	ax
	mov	ax,offset __srcfile
	mov	dx,offset __outfile
	call	zip_copyendcentral
	inc	ax
	pop	ax
	jnz	zip_delete_end
    zip_delete_error:
	push	bx
	invoke	oclose,addr STDI
	mov	ax,offset __outfile
	call	wscopy_remove
	pop	ax
	test	ax,ax
	jz	@F
	dec	ax
	jmp	wzipdel_end
      @@:
	inc	ax
    zip_delete_end:
	mov	es,si
	mov	dl,es:[di]
	and	dl,_A_SUBDIR
	jnz	wzipdel_end
	cmp	ax,1
	jne	wzipdel_end
    wzipdel_err:		; 2: ZIP file deleted (Ok)
	cmp	errno,0
	jne	@F
	mov	errno,ENOENT
      @@:
	invoke	erdelete,addr __outpath
	inc	ax
    wzipdel_cancel:
	inc	ax
    wzipdel_end:		; 0: Jump/Ok/Continue
	test	ax,ax
	jnz	wsdeletearc_end
	mov	es,si
	mov	cx,es:[di]
	test	cl,_A_SUBDIR
	jz	wsdeletearc_end
	inc	ax
	jmp	delete_zip_file
    wsdeletearc_end:
	test	ax,ax
	pop	di
	pop	si
	pop	bp
	ret
wsdeletearc endp

	END
