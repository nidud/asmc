; LISTING.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; listing interface.
;
ifndef __LISTING_INC
define __LISTING_INC

.enum lsttype {
    LSTTYPE_DATA,
    LSTTYPE_CODE,
    LSTTYPE_EQUATE,
    LSTTYPE_TMACRO,
    LSTTYPE_DIRECTIVE,
    LSTTYPE_MACRO,
    LSTTYPE_STRUCT,
    LSTTYPE_LABEL,
    LSTTYPE_MACROLINE
    }

LstInit		proto __ccall
LstWriteSrcLine proto __ccall
LstWriteCRef	proto __ccall
LstPrintf	proto __ccall :string_t, :vararg
LstSetPosition	proto __ccall
LstNL		proto __ccall
LstWrite	proto __ccall :int_t, :uint_t, :ptr

endif
