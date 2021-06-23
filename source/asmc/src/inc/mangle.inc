; MANGLE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Declaration for mangler routines (name decoration)
;
ifndef __MANGLE_INC
define __MANGLE_INC

Mangle      proto :ptr asym, :string_t
SetMangler  proto :ptr asym, :int_t, :string_t

endif
