.pragma list(push, 0)
ifndef __HLL_INC
__HLL_INC equ <>

NULLC		equ 0

HllInit		proto :int_t ;; reset counter for hll labels
HllCheckOpen	proto
ClassInit	proto
ClassCheckOpen	proto
PragmaInit	proto
PragmaCheckOpen proto

hll_t		typedef ptr hll_item

InvertJump	proto fastcall :string_t
GetExpression	proto :hll_t, :ptr int_t, :token_t, :int_t, :uint_t, :string_t, :ptr hll_opnd
ForDirective	proto :int_t, :token_t

endif
.pragma list(pop)
