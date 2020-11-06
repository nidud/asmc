ifndef _D2D1_2_H_
_D2D1_2_H_ equ <>

ifndef _D2D1_1_H_
include d2d1_1.inc
endif
ifndef _D2D1_EFFECTS_1_
include d2d1effects_1.inc
endif

ifndef D2D_USE_C_DEFINITIONS

endif

.enum D2D1_RENDERING_PRIORITY {
    D2D1_RENDERING_PRIORITY_NORMAL = 0,
    D2D1_RENDERING_PRIORITY_LOW = 1,
    D2D1_RENDERING_PRIORITY_FORCE_DWORD = 0xffffffff
    }


externdef IID_ID2D1GeometryRealization:IID
externdef IID_ID2D1DeviceContext1:IID
externdef IID_ID2D1Device1:IID
externdef IID_ID2D1Factory2:IID
externdef IID_ID2D1CommandSink1:IID


ifndef D2D_USE_C_DEFINITIONS

endif


ifdef D2D_USE_C_DEFINITIONS
endif

if NTDDI_VERSION GE NTDDI_WINBLUE
endif

include d2d1_2helper.inc
endif
