; INDIRECT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

AssignPointer       proto __ccall :ptr asym, :int_t, :ptr asm_tok, :ptr asym, :int_t, :ptr asym
HandleIndirection   proto __ccall :ptr asym, :ptr asm_tok, :int_t
