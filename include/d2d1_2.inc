ifndef _D2D1_2_H_
define _D2D1_2_H_

ifndef _D2D1_1_H_
include d2d1_1.inc
endif
ifndef _D2D1_EFFECTS_1_
include d2d1effects_1.inc
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

include d2d1_2helper.inc
endif
