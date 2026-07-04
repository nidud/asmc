; INDIRECT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef _INDIRECT_
define _INDIRECT_

FindDotSymbol       proto fastcall :token_t
AssignPointer       proto __ccall :asym_t, :int_t, :token_t, :asym_t, :int_t, :asym_t
HandleIndirection   proto __ccall :asym_t, :token_t, :int_t

endif

