; CONTEXT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; PUSHCONTEXT/POPCONTEXT interface
;
ifndef __CONTEXT_INC
define __CONTEXT_INC

ContextInit proto __ccall :int_t
ContextFini proto __ccall

endif
