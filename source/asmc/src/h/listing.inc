.pragma list(push, 0)
ifndef __LISTING_INC
define __LISTING_INC

;; listing interface.

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

LstInit		proto
LstWriteSrcLine proto
LstWriteCRef	proto
LstPrintf	proto _CDecl :string_t, :vararg
LstSetPosition	proto
LstNL		proto
LstWrite	proto :int_t, :uint_t, :ptr

endif
.pragma list(pop)
