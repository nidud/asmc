; EQUATE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; EQU and '=' directives interface
;
ifndef __EQUATE_INC
define __EQUATE_INC

CreateConstant proto __ccall :token_t
CreateVariable proto __ccall :string_t, :int_t

endif
