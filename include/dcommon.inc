ifndef DCOMMON_H_INCLUDED
DCOMMON_H_INCLUDED equ <>

ifndef DEFINE_ENUM_FLAG_OPERATORS
DEFINE_ENUM_FLAG_OPERATORS macro ENUMTYPE
	exitm<.err>
	endm
endif

ifndef __field_ecount_opt
__field_ecount_opt macro x
	exitm<.err>
	endm
endif

ifndef __range
__range macro x,y
	exitm<.err>
	endm
endif

ifndef __field_ecount
__field_ecount macro x
	exitm<.err>
	endm
endif

.enum DWRITE_MEASURING_MODE {
    DWRITE_MEASURING_MODE_NATURAL,
    DWRITE_MEASURING_MODE_GDI_CLASSIC,
    DWRITE_MEASURING_MODE_GDI_NATURAL
    }

endif

