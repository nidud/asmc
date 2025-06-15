; INDIRECT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

AssignPointer       proto __ccall :asym_t, :int_t, :token_t, :asym_t, :int_t, :asym_t
HandleIndirection   proto __ccall :asym_t, :token_t, :int_t
