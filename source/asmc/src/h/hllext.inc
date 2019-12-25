ifndef __HLLEXT_INC
__HLLEXT_INC equ <>

include memalloc.inc
include parser.inc
include expreval.inc
include segment.inc
include listing.inc
include lqueue.inc
include tokenize.inc
include input.inc
include reswords.inc

.pragma list(push, 0)

MIN_JTABLE	equ 8
MAX_JTABLE	equ 32
LABELSIZE	equ 8
LABELSGLOBAL	equ 0		;; make the generated labels global
JMPPREFIX	equ <>		;; define spaces before "jmp" or "loop"
LABELFMT	equ <"@C%04X">

;; v2.10: static variables moved to ModuleInfo

;HllStack	equ <ModuleInfo.HllStack>
;HllFree	equ <ModuleInfo.HllFree>

if LABELSGLOBAL
 LABELQUAL	equ <"::">
else
 LABELQUAL	equ <":">
endif

EOLCHAR		equ 10		;; line termination char in generated source

;; values for struct hll_item.cmd
.enum hll_cmd {
    HLL_IF,
    HLL_WHILE,
    HLL_REPEAT,
    HLL_BREAK,	; .IF behind .BREAK or .CONTINUE
    HLL_SWITCH,
    HLL_RETURN,
    HLL_FOR
}

;; index values for struct hll_item.labels[]
.enum hll_label_index {
    LTEST,	;; test (loop) condition
    LEXIT,	;; block exit
    LSTART,	;; loop start
    LSTARTSW,	;; switch start
}

;; values for struct hll_item.flags

.enum hll_flags {
    HLLF_ELSEOCCURED	= 0x01,
    HLLF_ELSEIF		= 0x02,
    HLLF_WHILE		= 0x04,
    HLLF_EXPRESSION	= 0x08,
    HLLF_DEFAULT	= 0x10,
    HLLF_DELAYED	= 0x20,		;; set by DelayExpand()
    HLLF_NOTEST		= 0x40,		;; direct jump..
    HLLF_ARGREG		= 0x80,		;; register 16/32/64-bit size_t
    HLLF_ARGMEM		= 0x0100,	;; memory if set, else register
    HLLF_ARG16		= 0x0200,	;; size: 8/16/32/64
    HLLF_ARG32		= 0x0400,
    HLLF_ARG64		= 0x0800,
    HLLF_ARG3264	= 0x1000,	;; .switch eax in 64-bit assumend rax
    HLLF_NUM		= 0x2000,	;; .case arg is const
    HLLF_TABLE		= 0x4000,	;; .case is in jump table
    HLLF_ENDCOCCUR	= 0x8000,	;; jmp exit in .case omitted
    HLLF_IFB		= 0x00010000,	;; .ifb proc() --> al
    HLLF_IFW		= 0x00020000,	;; .ifw proc() --> ax
    HLLF_IFD		= 0x00040000,	;; .ifd proc() --> eax
    HLLF_IFS		= 0x00080000,	;; Signed compare --> CMP REG,val
    HLLF_PASCAL		= 0x00100000,	;; .continue(0) [.if]
    HLLF_JTABLE		= 0x00200000,	;; if HLLF_NOTEST direct .case jump
    HLLF_JTDATA		= 0x00400000	;; Jump table in data segment -- HLLF_NOTEST
}

hll_t		typedef ptr hll_item

hll_item	struct
next		hll_t ?
caselist	hll_t ?
labels		uint_t 4 dup(?) ; labels for LTEST, LEXIT, LSTART
condlines	string_t ?	; .WHILE/ELSEIF/CASE-blocks only: lines to add after 'test' label
cmd		int_t ?		; start cmd (IF, WHILE, REPEAT)
flags		int_t ?		; v2.08: added
hll_item	ends

hll_opnd	struct		; v2.08: struct added
lastjmp		string_t ?
lasttruelabel	uint_t ?	; v2.08: new member
hll_opnd	ends

; in Masm, there's a nesting level limit of 20. In JWasm, there's
; currently no limit.

GetHllLabel macro
    inc ModuleInfo.hll_label
    mov eax,ModuleInfo.hll_label
    exitm<eax>
    endm

GetLabelStr		proto :int_t, :string_t
ExpandLine		proto :string_t, :tok_t
ExpandCStrings		proto :tok_t
EvaluateHllExpression	proto :hll_t, :ptr int_t, :tok_t, :int_t, :int_t, :string_t
ExpandHllProc		proto :string_t, :int_t, :tok_t
ExpandHllExpression	proto :hll_t, :ptr int_t, :tok_t, :int_t, :int_t, :string_t
QueueTestLines		proto :string_t
HllContinueIf		proto :hll_t, :ptr int_t, :tok_t, :int_t, :hll_t, :int_t
GenerateCString		proto :int_t, :tok_t

.pragma list(pop)
endif
