; HLLEXT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __HLLEXT_INC
define __HLLEXT_INC

include memalloc.inc
include parser.inc
include expreval.inc
include segment.inc
include listing.inc
include lqueue.inc
include tokenize.inc
include input.inc
include reswords.inc

define MIN_JTABLE   8
define MAX_JTABLE   32
define LABELSIZE    8
define LABELSGLOBAL 0	; make the generated labels global
define LABELFMT	    <"@C%04X">

if LABELSGLOBAL
define LABELQUAL <"::">
else
define LABELQUAL <":">
endif

define EOLCHAR 10 ; line termination char in generated source

; values for struct hll_item.cmd

.enum hll_cmd {
    HLL_IF,
    HLL_WHILE,
    HLL_REPEAT,
    HLL_BREAK,	; .IF behind .BREAK or .CONTINUE
    HLL_SWITCH,
    HLL_RETURN,
    HLL_FOR
    }

; index values for struct hll_item.labels[]

.enum hll_label_index {
    LTEST,	; test (loop) condition
    LEXIT,	; block exit
    LSTART,	; loop start
    LSTARTSW,	; switch start
    }

; values for struct hll_item.flags

.enum hll_flags {
    HLLF_ELSEOCCURED	= 0x01,
    HLLF_ELSEIF		= 0x02,
    HLLF_WHILE		= 0x04,
    HLLF_EXPRESSION	= 0x08,
    HLLF_DEFAULT	= 0x10,
    HLLF_DELAYED	= 0x20, ; set by DelayExpand()
    HLLF_NOTEST		= 0x40, ; direct jump..
    HLLF_ARGREG		= 0x80, ; register 16/32/64-bit size_t
    HLLF_ARGMEM	       = 0x100, ; memory if set, else register
    HLLF_ARG16	       = 0x200, ; size: 8/16/32/64
    HLLF_ARG32	       = 0x400,
    HLLF_ARG64	       = 0x800,
    HLLF_ARG3264      = 0x1000, ; .switch eax in 64-bit assumend rax
    HLLF_NUM	      = 0x2000, ; .case arg is const
    HLLF_TABLE	      = 0x4000, ; .case is in jump table
    HLLF_ENDCOCCUR    = 0x8000, ; jmp exit in .case omitted
    HLLF_IFB	     = 0x10000, ; .ifb proc() --> al
    HLLF_IFW	     = 0x20000, ; .ifw proc() --> ax
    HLLF_IFD	     = 0x40000, ; .ifd proc() --> eax
    HLLF_IFS	     = 0x80000, ; Signed compare --> CMP REG,val
    HLLF_PASCAL	    = 0x100000, ; .continue(0) [.if]
    HLLF_JTABLE	    = 0x200000, ; if HLLF_NOTEST direct .case jump
    HLLF_JTDATA	    = 0x400000	; Jump table in data segment -- HLLF_NOTEST
    }

hll_item	struct
next		ptr hll_item ?
caselist	ptr hll_item ?
union
ifdef _WIN64
 value		int64_t ?
else
 struct
  value		int_t ?
  hvalue	int_t ?
 ends
endif
 labels		uint_t 4 dup(?) ; labels for LTEST, LEXIT, LSTART
ends
condlines	string_t ?	; .WHILE/ELSEIF/CASE-blocks only: lines to add after 'test' label
cmd		int_t ?		; start cmd (IF, WHILE, REPEAT)
flags		int_t ?		; v2.08: added
tokval		int_t ?		; v2.33.67: added
hll_item	ends

hll_opnd	struct		; v2.08: struct added
lastjmp		string_t ?
lasttruelabel	uint_t ?	; v2.08: new member
hll_opnd	ends

; in Masm, there's a nesting level limit of 20. In JWasm, there's
; currently no limit.

GetHllLabel macro
    inc MODULE.hll_label
    mov eax,MODULE.hll_label
    exitm<eax>
    endm

GetLabelStr		proto __ccall :int_t, :string_t
ExpandLine		proto __ccall :string_t, :ptr asm_tok
ExpandCStrings		proto __ccall :ptr asm_tok
EvaluateHllExpression	proto __ccall :ptr hll_item, :ptr int_t, :ptr asm_tok, :int_t, :int_t, :string_t
ExpandHllProc		proto __ccall :string_t, :int_t, :ptr asm_tok
ExpandHllExpression	proto __ccall :ptr hll_item, :ptr int_t, :ptr asm_tok, :int_t, :int_t, :string_t
HllContinueIf		proto __ccall :ptr hll_item, :ptr int_t, :ptr asm_tok, :int_t, :ptr hll_item, :int_t
GenerateCString		proto __ccall :int_t, :ptr asm_tok

endif
