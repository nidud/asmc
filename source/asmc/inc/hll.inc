; HLL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __HLL_INC
define __HLL_INC

define NULLC	0

HllInit		proto __ccall :int_t ;; reset counter for hll labels
HllCheckOpen	proto __ccall
ClassInit	proto __ccall
ClassCheckOpen	proto __ccall
PragmaInit	proto __ccall
PragmaCheckOpen proto __ccall

InvertJump	proto fastcall :string_t
GetExpression	proto __ccall :ptr hll_item, :ptr int_t, :ptr asm_tok, :int_t, :uint_t, :string_t, :ptr hll_opnd
ForDirective	proto __ccall :int_t, :ptr asm_tok

endif
