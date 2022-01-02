; NAMESPACE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef __NAMESPACE_INC
define __NAMESPACE_INC

.template nsp_item
    next ptr nsp_item ?
    name ptr sbyte ?
   .ends

NameSpaceDirective  proto __ccall :int_t, :token_t
NameSpace           proto watcall :string_t, :string_t

endif
