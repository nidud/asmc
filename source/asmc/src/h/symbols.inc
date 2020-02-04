.pragma list(push, 0)
ifndef __SYMBOLS_INC
__SYMBOLS_INC equ <>

;; defines symbol structures asym and dsym,
;; and prototypes of functions in symbols.c.
;; This file is included by parser.inc

;; SYM_LIB  - library paths are no longer added to the symbol table
;; SYM_LNAME has been removed. It was used for the null-entry in the LNAME table only
;; v2.01: SYM_PROC has been removed.
;; v2.01: SYM_LIB has been removed.

.enum sym_state {
    SYM_UNDEFINED,
    SYM_INTERNAL,	;;  1 internal label
    SYM_EXTERNAL,	;;  2 external
    SYM_SEG,		;;  3 segment
    SYM_GRP,		;;  4 group
    SYM_STACK,		;;  5 stack variable - in local symbol tables only
    SYM_STRUCT_FIELD,	;;  6 struct member - not in symbol table - except record fields
    SYM_TYPE,		;;  7 structure, union, typedef, record
    SYM_ALIAS,		;;  8 alias name
    SYM_MACRO,		;;  9 macro
    SYM_TMACRO,		;; 10 text macro
    SYM_CLASS_LNAME	;; 11 lname item for segm class - not in symbol table
}

;; v2.04: MT_SHORT removed
;; v2.07: MT_ABS (0xC2) removed

MT_SIZE_MASK		equ 0x1F ;; if MT_SPECIAL==0 then bits 0-4 = size - 1
MT_FLOAT		equ 0x20 ;; bit 5=1
MT_SIGNED		equ 0x40 ;; bit 6=1
MT_BYTE			equ 1 - 1
MT_SBYTE		equ MT_BYTE or MT_SIGNED
MT_WORD			equ 2 - 1
MT_SWORD		equ MT_WORD or MT_SIGNED
MT_REAL2		equ MT_WORD or MT_FLOAT
MT_DWORD		equ 4 - 1
MT_SDWORD		equ MT_DWORD or MT_SIGNED
MT_REAL4		equ MT_DWORD or MT_FLOAT
MT_FWORD		equ 6 - 1
MT_QWORD		equ 8 - 1
MT_SQWORD		equ MT_QWORD or MT_SIGNED
MT_REAL8		equ MT_QWORD or MT_FLOAT
MT_TBYTE		equ 10 - 1
MT_REAL10		equ MT_TBYTE or MT_FLOAT
MT_OWORD		equ 16 - 1
MT_REAL16		equ MT_OWORD or MT_FLOAT
MT_YMMWORD		equ 32 - 1
MT_ZMMWORD		equ 64 - 1
MT_YWORD		equ MT_YMMWORD
MT_ZWORD		equ MT_ZMMWORD
MT_PROC			equ 0x80 ;; symbol is a TYPEDEF PROTO, state=SYM_TYPE,
				 ;; typekind=TYPE_TYPEDEF, prototype is stored in target_type
MT_NEAR			equ 0x81
MT_FAR			equ 0x82
MT_EMPTY		equ 0xC0
MT_BITS			equ 0xC1 ;; record field
MT_PTR			equ 0xC3 ;; v2.05: changed, old value 0x83
MT_TYPE			equ 0xC4 ;; symbol has user-defined type (struct, union, record)
MT_SPECIAL		equ 0x80 ;; bit 7
MT_SPECIAL_MASK		equ 0xC0 ;; bit 6+7
MT_ADDRESS		equ 0x80 ;; bit 7=1, bit 6 = 0

IS_SIGNED macro x
    mov al,x
    and al,MT_SPECIAL_MASK
    .if al == MT_SIGNED
	mov eax,1
    .else
	xor eax,eax
    .endif
    exitm<eax>
    endm

;; symbols can be
;; - "labels" (data or code, internal, external, stack)
;;   mem_type is MT_BYTE..MT_OWORD, MT_NEAR, MT_FAR, MT_PTR
;; - constants (EQU) or assembly time variables ("="),
;;   mem_type "usually" is MT_EMPTY.
;; - types (STRUCT, UNION, TYPEDEF, RECORD), mem_type = MT_TYPE
;; - preprocessor items (macros and text macros), which have no
;;   mem_type (MT_EMPTY).

fixup_t		typedef ptr fixup
dlldesc_t	typedef ptr dll_desc
segitem_t	typedef ptr seg_item
debug_t		typedef ptr debug_info
asym_t		typedef ptr asym
dsym_t		typedef ptr esym
group_t		typedef ptr grp_info
segment_t	typedef ptr seg_info
proc_t		typedef ptr proc_info
srcline_t	typedef ptr srcline
mparm_t		typedef ptr mparm_list
macro_t		typedef ptr macro_info
sfield_t	typedef ptr sfield
struct_t	typedef ptr struct_info
tok_t		typedef ptr asm_tok

CALLBACKC(internal_func, :asym_t, :ptr)
CALLBACKC(macro_func, :ptr macro_instance, :string_t, :tok_t)


debug_info	struct
start_line	dd ?	;; procs's start line
end_line	dd ?	;; procs's last line
ln_fileofs	dd ?	;; file offset to line numbers
line_numbers	dw ?	;; line numbers in function
file		dw ?	;; proc's start file
next_proc	dd ?	;; index next proc
next_file	dd ?	;; index next file
debug_info	ends

S_USED		equ 0x0001
S_ISDEFINED	equ 0x0002
S_SCOPED	equ 0x0004
S_IAT_USED	equ 0x0008
S_ISEQUATE	equ 0x0010
S_PREDEFINED	equ 0x0020
S_VARIABLE	equ 0x0040
S_ISPUBLIC	equ 0x0080
S_LIST		equ 0x0100
S_ISARRAY	equ 0x0200
S_ISDATA	equ 0x0400
S_ISPROC	equ 0x0800
S_ISSAVED	equ 0x1000
S_FWDREF	equ 0x2000
S_INCLUDED	equ 0x4000
S_METHOD	equ 0x8000

SINT_SEGOFSSIZE equ 0x03
SINT_ISCOM	equ 0x04
SINT_WEAK	equ 0x08
SINT_ISFAR	equ 0x10
SINT_ISVARARG	equ 0x20

M_ISVARARG	equ 0x01
M_ISFUNC	equ 0x02
M_LABEL		equ 0x04
M_MULTILINE	equ 0x08
M_PURGED	equ 0x10

asym		struct
nextitem	asym_t ?	; next symbol in hash line
name		string_t ?	; symbol name
union
 _offset	int_t ?		; used by SYM_INTERNAL (labels), SYM_TYPE, SYM_STACK, SYM_SEG
 value		int_t ?		; used by SYM_INTERNAL (equates)
 uvalue		uint_t ?	; v2.01: equates (they are 33-bit!)
 string_ptr	string_t ?	; used by SYM_TMACRO
 substitute	asym_t ?	; v2.04b: used by SYM_ALIAS
 func_ptr	macro_func ?	; used by SYM_MACRO if predefined==1
 classlnameidx	int_t ? ; used by SYM_CLASS_LNAME
ends
_segment	asym_t ?	; used by SYM_INTERNAL, SYM_EXTERNAL
state		uchar_t ?
mem_type	uchar_t ?
flag		dw ?		; bitfield
union				; for SYM_INTERNAL (data labels, memtype != NEAR|FAR), SYM_STRUCT_FIELD
 first_size	uint_t ?	; size of 1st initializer's dimension in bytes
 struct
  Ofssize	uchar_t ?	; offset size (USE16, USE32)
  is_ptr	uchar_t ?	; PTR indirection
  union
   ptr_memtype	uchar_t ?	; pointer target type
   asmpass	uchar_t ?	; SYM_INTERNAL (mem_type NEAR|FAR)
  ends
  sint_flag	uchar_t ?
 ends
 mac_flag	uint_t ?	; for SYM_MACRO -- byte
ends
union				; for SYM_INTERNAL (data labels only), SYM_STRUCT_FIELD
 first_length	uint_t ?	; size of 1st initializer's dimension in item units
				; SYM_TYPE (TYPEKIND_STRUCT or TYPEKIND_UNION)
 max_mbr_size	uint_t ?	; max size members
				; SYM_STACK, SYM_TYPE (TYPEKIND_TYPEDEF), SYM_EXTERNAL,
				; SYM_INTERNAL (code labels)
 target_type	asym_t ?	; set if ptr_memtype is MT_TYPE
ends
regist		ushort_t 2 dup(?) ; SYM_TMACRO (if it's a register variable for FASTCALL)
union				; for SYM_INTERNAL, SYM_STRUCT_FIELD,
				; SYM_TYPE, SYM_STACK,
				; SYM_EXTERNAL (comm=1)
				; SYM_TMACRO: size of buffer allocated for the text in string_ptr
 total_size	uint_t ?	; total number of bytes (sizeof)
				; for SYM_INTERNAL, isequate=1 (numeric equates)
 value3264	int_t ?		; high bits for equates
 dll		dlldesc_t ?	; SYM_EXTERNAL (isproc=1)
 max_offset	int_t ?		; for SYM_SEG; v2.11: moved here to make segment's
ends				; offset field contain "local start offset" (=0)
union				; SYM_INTERNAL, SYM_STRUCT_FIELD,
				; SYM_STACK, SYM_EXTERNAL (comm==1):
 total_length	uint_t ?	; total number of elements (LENGTHOF)
 altname	asym_t ?	; SYM_EXTERNAL (comm==0): alternative name
 debuginfo	debug_t ?	; SYM_INTERNAL (isproc==1): debug info (COFF)
 sfunc_ptr	internal_func ? ; SYM_INTERNAL+predefined
 struct				; SYM_TYPE
  cvtyperef	ushort_t ?	; codeview type index (used after assembly steps)
  typekind	ushort_t ?	; v2.04: moved from first_length, were it didn't work anymore
 ends				; since the addition of field max_mbr_size.
ends
name_size	ushort_t ?
langtype	ushort_t ?
type		asym_t ?	; set if memtype is MT_TYPE
union				; SYM_INTERNAL, SYM_UNDEFINED, SYM_EXTERNAL: backpatching fixup
 bp_fixup	fixup_t ?
 ext_idx	uint_t ?	; for SYM_EXTERNAL: table index ( for coff and elf )
 struct				; omf indices are 16-bit only!
  ext_idx1	ushort_t ?	; omf: (external definition) index
  ext_idx2	ushort_t ?	; omf: (external definition) index for weak external
 ends
ends
asym		ends

;;---------------------------------------------------------------------------
;; Structures for grpdef, segdef, externdef, pubdef, included library,
;; procedure and symbolic integer constants.
;;---------------------------------------------------------------------------

seg_item	struct
next		segitem_t ?
iseg		dsym_t ?
seg_item	ends

grp_info	struct		;;
seglist		segitem_t ?	;; list of segments in the group
grp_idx		int_t ?		;; its group index (OMF)
lname_idx	int_t ?		;; LNAME index (OMF only)
numseg		uint_t ?	;; OMF: number of segments in the group
grp_info	ends		;;


CALLBACK(FlushSegFunc, :dsym_t, :uchar_t, :uint_t, :ptr )

seg_info	struct		;;
sgroup		asym_t ?	;; segment's group or NULL
start_loc	uint_t ?	;; starting offset of current ledata or lidata
union				;;
 current_loc	uint_t ?	;; current offset in current ledata or lidata
 reloc_offset	uint_t ?	;; ELF: reloc file offset
 start_offset	uint_t ?	;; BIN: start offset in group
ends				;;
CodeBuffer	string_t ?	;;
bytes_written	uint_t ?	;; initialized bytes in segment
union				;;
 label_list	asym_t ?	;; linked list of labels in this seg
 flushfunc	FlushSegFunc ?	;; to flush the segment buffer
ends				;;
head		fixup_t ?	;; fixup queue head
tail		fixup_t ?	;; fixup queue tail
union				;;
 LinnumQueue	ptr_t ?		;; for COFF line numbers
 fileoffset	uint_t ?	;; used by BIN + ELF
 num_linnums	uint_t ?	;; used by COFF (after LinnumQueue has been read)
ends				;;
num_relocs	uint_t ?	;; used by COFF/ELF
seg_idx		uint_t ?	;; segment #; v2.12: changed from short to unsigned
segtype		uint_t ?	;; segment's type (code, data, ...)
lname_idx	int_t ?		;; segment's name LNAME index (OMF only)
clsym		asym_t ?	;; segment's class name (stored in an asym item)
union				;;
 abs_frame	uint_t ?	;; ABS seg, frame number (OMF,BIN)
 comdat_number	uint_t ?	;; associated COMDAT segno (COFF)
 comdat_idx	uint_t ?	;; lname index of COMDAT symbol (OMF)
ends
union
 abs_offset	uint_t ?	;; ABS seg, offset (OMF only)
 aliasname	string_t ?	;; ALIAS name (COFF/ELF only)
ends
Ofssize		uchar_t ?	;; segment's offset size
characteristics uchar_t ?	;; used by COFF/ELF/PE
alignment	uchar_t ?	;; is value 2^x
readonly	uchar_t ?	;; if segment is readonly
info		uchar_t ?	;; if segment is info only (COFF/ELF)
force32		uchar_t ?	;; force 32bit segdef (OMF only)
data_in_code	uchar_t ?	;; data items in code segm (OMF only)
internal	uchar_t ?	;; internal segment with private buffer
written		uchar_t ?	;; code/data just written
linnum_init	uchar_t ?	;; v2.10: linnum data emitted for segment?
combine		uchar_t ?	;; combine type, see omfspec.inc
comdatselection uchar_t ?	;; if > 0, it's a COMDAT (COFF/OMF)
seg_info	ends		;;


MAX_SEGALIGNMENT equ 0xFF

;; PROC item

PROC_HAS_VARARG equ 0x01	;; last param is VARARG
PROC_PE_TYPE	equ 0x02	;; PROC: prolog-epilog type, 1=use LEAVE
PROC_ISEXPORT	equ 0x04	;; PROC: EXPORT attribute set
PROC_FORCEFRAME equ 0x08	;; PROC: FORCEFRAME prologuearg?
PROC_LOADDS	equ 0x10	;; PROC: LOADDS prologuearg?
PROC_STACKPARAM equ 0x20	;; PROC: 1=stack params exists ( not just register params )
PROC_ISFRAME	equ 0x40	;; PROC: FRAME attribute set?
PROC_FPO	equ 0x80	;;

proc_info	struct
regslist	ptr_t ?		;; PROC: list of registers to be saved
paralist	dsym_t ?	;; list of parameters
locallist	dsym_t ?	;; PROC: list of local variables
labellist	dsym_t ?	;; PROC: list of local labels
parasize	uint_t ?	;; total no. of bytes used by parameters
localsize	uint_t ?	;; PROC: total no. of bytes used by local variables
prologuearg	string_t ?	;; PROC: prologuearg attribute
exc_handler	asym_t ?	;; PROC: exc handler set by FRAME
ReservedStack	int_t ?		;; PROC: win64: additional reserved stack
prolog_list_pos uint_t ?	;; PROC: prologue list pos
flags		uchar_t ?
size_prolog	uchar_t ?	;; PROC: v2.10: prologue size
basereg		ushort_t ?	;; PROC: v2.11: stack base register
proc_info	ends


;; macro parameter

mparm_list	struct
deflt		string_t ?	;; optional default parm
required	uchar_t ?	;; is parm required (REQ)
mparm_list	ends

;; macro line

srcline		struct
next		srcline_t ?
ph_count	uchar_t ?	;; placeholders contained in this line
line		char_t 1 dup(?)
srcline		ends

;; macro item

macro_info	struct
parmcnt		ushort_t ?	;; no of params
union
 localcnt	ushort_t ?	;; no of locals
 autoexp	ushort_t ?	;; auto-expansion flags if predefined macro
ends
parmlist	mparm_t ?	;; array of parameter items
_data		srcline_t ?	;; prepared macro source lines
srcfile		uint_t ?	;; sourcefile index
macro_info	ends

;; STRUCT field

sfield		struct
sym		asym <>		;; field symbol ( state=SYM_STRUCT_FIELD )
next		sfield_t ?	;; next field in STRUCT,UNION,RECORD
ivalue		char_t ?	;; v2.09: type changed from char * to char[]
sfield		ends

TYPE_NONE	equ 0
TYPE_STRUCT	equ 1
TYPE_UNION	equ 2
TYPE_TYPEDEF	equ 3
TYPE_RECORD	equ 4

STINF_ISINLINE	equ 1		;; STRUCT/UNION: inline (unused)
STINF_ISOPEN	equ 2		;; STRUCT/UNION: set until the matching ENDS is found
STINF_ORGINSIDE equ 4		;; STRUCT: struct contains an ORG

struct_info	struct
head		sfield_t ?	;; STRUCT/UNION/RECORD: start of field list
tail		sfield_t ?	;; STRUCT/UNION/RECORD: current/next field
alignment	uchar_t ?	;; STRUCT: 1,2,4,8,16 or 32
flags		uchar_t ?
struct_info	ends

;; dsym originally was a "directive_node"
;; However, currently all symbols except SYM_STRUCT_FIELDs are allocated as a dsym.
;; the additional 3 fields are used differently depending on symbol's type.

esym		struct
sym		asym <>
union
 seginfo	segment_t ?	;; SYM_SEG (segments)
 grpinfo	group_t ?	;; SYM_GRP (groups)
 procinfo	proc_t ?	;; SYM_INTERNAL|SYM_EXTERNAL (procs, isproc=1)
 structinfo	struct_t ?	;; SYM_TYPE (structs, unions, records [, typedefs])
 macroinfo	macro_t ?	;; SYM_MACRO (macros)
 nextll		dsym_t ?	;; SYM_STACK, SYM_INTERNAL (code labels, isproc=0)
				;; used to save the local hash table (contains
				;; PROC locals: params, locals, labels). Details
				;; see SymGetLocal(), SymSetLocal() in symbols.asm
ends
next		dsym_t ?	;; next item in linked lists of certain symbol types.
				;; - SYM_UNDEFINED -> TAB_UNDEF
				;; - SYM_EXTERNAL  -> TAB_EXT
				;; - SYM_SEG	   -> TAB_SEG
				;; - SYM_GRP	   -> TAB_GRP
				;; - SYM_ALIAS:	   -> TAB_ALIAS
				;; for SYM_INTERNAL:
				;; linked list of labels for current segment
				;; (used for BackPatch)

;; for SYM_UNDEFINED, SYM_EXTERNAL, SYM_ALIAS and SYM_GRP:
;; predecessor of current symbol with the same state, to allow fast removes.
;; Actually, the only symbols which may change the state and thus
;; have a chance to be removed are SYM_UNDEFINED and SYM_EXTERNAL ( weak=TRUE )
;; during pass one.
union
 prev		dsym_t ? ;; used by PROC symbols (SYM_INTERNAL) for linked list, TAB_PROC
 nextproc	dsym_t ? ;; used by PROC locals (SYM_STACK) for linked list
 nextlocal	dsym_t ? ;; used by PROC params (SYM_STACK) for linked list
 nextparam	dsym_t ? ;; used by SYM_EXTERNAL (weak=FALSE) if altname is set
ends
esym		ends

SymAlloc	proto :string_t
SymFree		proto :asym_t
SymCreate	proto :string_t
SymLCreate	proto :string_t
SymAddGlobal	proto :asym_t
SymAddLocal	proto :asym_t, :string_t
SymLookup	proto :string_t
SymLookupLocal	proto :string_t
SymFind		proto fastcall :string_t

SymSearch macro x
    exitm<SymFind(x)>
    endm

SymInit		proto
SymPassInit	proto :int_t
SymMakeAllSymbolsPublic proto
SymGetAll	proto :ptr asym_t
SymEnum		proto :asym_t, :ptr int_t
SymGetCount	proto

CALLBACKC(StrCmpFunc, :ptr, :ptr, :size_t )
externdef	SymCmpFunc:StrCmpFunc

SymSetCmpFunc	proto
SymClearLocal	proto
SymSetLocal	proto :asym_t
SymGetLocal	proto :asym_t

endif
.pragma list(pop)
