ifndef _D2D1_EFFECT_AUTHOR_1_H_
define _D2D1_EFFECT_AUTHOR_1_H_

ifndef _D2D1_3_H_
include d2d1_3.inc
endif
ifndef _D2D1_EFFECT_AUTHOR_H_
include d2d1effectauthor.inc
endif

ifndef D2D_USE_C_DEFINITIONS

DEFINE_IIDX(ID2D1EffectContext1, "84ab595a-fc81-4546-bacd-e8ef4d8abe7a")

.comdef ID2D1EffectContext1 : public ID2D1EffectContext

    CreateLookupTable3D proc :D2D1_BUFFER_PRECISION, :LPBYTE, :UINT32, :ptr UINT32, :ptr ptr ID2D1LookupTable3D
    .ends


if NTDDI_VERSION GE NTDDI_WIN10_RS2

DEFINE_IIDX(ID2D1EffectContext2, "577ad2a0-9fc7-4dda-8b18-dab810140052")

.comdef ID2D1EffectContext2  : public ID2D1EffectContext1

    CreateColorContextFromDxgiColorSpace proc :DXGI_COLOR_SPACE_TYPE, :ptr ptr ID2D1ColorContext1
    CreateColorContextFromSimpleColorProfile proc :ptr D2D1_SIMPLE_COLOR_PROFILE, :ptr ptr ID2D1ColorContext1
    .ends


endif

endif


ifdef D2D_USE_C_DEFINITIONS


if NTDDI_VERSION GE NTDDI_WIN10_RS2

endif

endif

endif
