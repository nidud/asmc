; HLL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __HLL_INC
define __HLL_INC

define NULLC		0
define EOLCHAR		10	; line termination char in generated source
define MIN_JTABLE	8
define MAX_JTABLE	32
define LABELSIZE	8
define LABELSGLOBAL	0	; make the generated labels global
define LABELFMT		<"@C%04X">
if LABELSGLOBAL
define LABELQUAL	<"::">
else
define LABELQUAL	<":">
endif

.enum hll_cmd { ; values for hll_item.cmd
    HLL_IF,
    HLL_WHILE,
    HLL_REPEAT,
    HLL_BREAK,	; .IF behind .BREAK or .CONTINUE
    HLL_SWITCH,
    HLL_RETURN,
    HLL_FOR
    }

.enum hll_label_index { ; index values for hll_item.labels[]
    LTEST,	; test (loop) condition
    LEXIT,	; block exit
    LSTART,	; loop start
    LSTARTSW,	; switch start
    }

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


HllInit			proto __ccall :int_t ;; reset counter for hll labels
HllCheckOpen		proto __ccall
ClassInit		proto __ccall
ClassCheckOpen		proto __ccall
PragmaInit		proto __ccall
PragmaCheckOpen		proto __ccall
ForDirective		proto __ccall :int_t, :token_t
GetLabelStr		proto __ccall :int_t, :string_t
ExpandLine		proto __ccall :string_t, :token_t
ExpandCStrings		proto __ccall :token_t
EvaluateHllExpression	proto __ccall :hllitem_t, :ptr int_t, :token_t, :int_t, :int_t, :string_t
ExpandHllProc		proto __ccall :string_t, :int_t, :token_t
ExpandHllExpression	proto __ccall :hllitem_t, :ptr int_t, :token_t, :int_t, :int_t, :string_t
HllContinueIf		proto __ccall :hllitem_t, :ptr int_t, :token_t, :int_t, :hllitem_t, :int_t
GenerateCString		proto __ccall :int_t, :token_t
DefaultConstructor	proto __ccall :asym_t, :token_t

endif
