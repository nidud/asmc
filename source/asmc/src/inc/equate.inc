; EQUATE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; EQU and '=' directives interface
;
ifndef __EQUATE_INC
define __EQUATE_INC

CreateConstant proto :ptr asm_tok
CreateVariable proto :string_t, :int_t

endif
