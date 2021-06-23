; HLL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __HLL_INC
define __HLL_INC

define NULLC	0

HllInit		proto :int_t ;; reset counter for hll labels
HllCheckOpen	proto
ClassInit	proto
ClassCheckOpen	proto
PragmaInit	proto
PragmaCheckOpen proto

InvertJump	proto fastcall :string_t
GetExpression	proto :ptr hll_item, :ptr int_t, :ptr asm_tok, :int_t, :uint_t, :string_t, :ptr hll_opnd
ForDirective	proto :int_t, :ptr asm_tok

endif
