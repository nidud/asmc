; MEM2MEM.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef _MEM2MEM_
define _MEM2MEM_

mem2mem proto __ccall :uint_t, :uint_t, :token_t, :ptr expr
imm2xmm proto __ccall :token_t, :expr_t, :uint_t
SizeFromExpression proto __ccall :ptr expr
CRecordField proto __ccall :int_t, :ptr expr, :ptr expr

endif

