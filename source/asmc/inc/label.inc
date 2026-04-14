; LABEL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; label routines prototypes
;
ifndef __LABEL_INC
define __LABEL_INC

LabelInit           proto __ccall
CreateLabel         proto __ccall :token_t, :string_t, :uchar_t, :ptr qualified_type, :int_t

endif
