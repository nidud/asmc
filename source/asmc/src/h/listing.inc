.pragma list(push, 0)
ifndef __LISTING_INC
__LISTING_INC equ <>

;; listing interface.

LSTTYPE_DATA		equ 0
LSTTYPE_CODE		equ 1
LSTTYPE_EQUATE		equ 2
LSTTYPE_TMACRO		equ 3
LSTTYPE_DIRECTIVE	equ 4
LSTTYPE_MACRO		equ 5
LSTTYPE_STRUCT		equ 6
LSTTYPE_LABEL		equ 7
LSTTYPE_MACROLINE	equ 8

LstInit			proto
LstWriteSrcLine		proto
LstWriteCRef		proto
LstPrintf		proto _CDecl :string_t, :vararg
LstSetPosition		proto
LstNL			proto
LstWrite		proto :int_t, :uint_t, :ptr

endif
.pragma list(pop)
