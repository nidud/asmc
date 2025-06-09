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
tokval		int_t ?		; v2.33.67: added

union				; values for struct hll_item.flags
 flags		dd ?		; v2.08: added
 record				; v2.36.40: added
  ElseOccured	dd : 1 ?
  WhileMode	dd : 1 ?	; Expression delayed
  Expression	dd : 1 ?	; Has expression
  DefaultCase	dd : 1 ?	; Case is .default
  ExpDelayed	dd : 1 ?	; Expansion delayed - see DelayExpand()
  SwitchJump	dd : 1 ?	; Direct jump (no test)
  SwitchReg	dd : 1 ?	; Switch arg is register
  SwitchMem	dd : 1 ?	; Switch arg is memory
  Switch16	dd : 1 ?	; Switch Arg size
  Switch32	dd : 1 ?
  Switch64	dd : 1 ?
  Switch3264	dd : 1 ?
  CaseIsConst	dd : 1 ?	; Case arg is const
  CaseInTable	dd : 1 ?	; Case is in jump table
  EndOccured	dd : 1 ?	; Jump exit in .case omitted
  SizeDB	dd : 1 ?	; Flag Extension B - BYTE
  SizeDW	dd : 1 ?	; Flag Extension W - WORD
  SizeDD	dd : 1 ?	; Flag Extension D - DWORD
  Signed	dd : 1 ?	; Flag Extension S - Signed
  Structured	dd : 1 ?	; Structured (Pascal) switch where each .CASE is a closed branch
  SwitchTable	dd : 1 ?	; If SwitchJump direct .case jump
  SwitchTData	dd : 1 ?	; Jump table in data segment -- SwitchJump
 ends
ends
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
DefaultConstructor	proto __ccall :ptr asym, :string_t

endif
