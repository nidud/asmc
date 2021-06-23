; ATOFLOAT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __ATOFLOAT_INC
define __ATOFLOAT_INC

atofloat    proto :ptr, :string_t, :uint_t, :int_t, :uchar_t
quad_resize proto :ptr expr, :int_t

endif
