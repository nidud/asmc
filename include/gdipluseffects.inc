ifndef _GDIPLUSEFFECTS_HPP
define _GDIPLUSEFFECTS_HPP

if (GDIPVER GE 0x0110)

DEFINE_GUID(BlurEffectGuid, 0x633c80a4, 0x1843, 0x482b, 0x9e, 0xf2, 0xbe, 0x28, 0x34, 0xc5, 0xfd, 0xd4 )
DEFINE_GUID(SharpenEffectGuid, 0x63cbf3ee, 0xc526, 0x402c, 0x8f, 0x71, 0x62, 0xc5, 0x40, 0xbf, 0x51, 0x42 )
DEFINE_GUID(ColorMatrixEffectGuid, 0x718f2615, 0x7933, 0x40e3, 0xa5, 0x11, 0x5f, 0x68, 0xfe, 0x14, 0xdd, 0x74 )
DEFINE_GUID(ColorLUTEffectGuid, 0xa7ce72a9, 0xf7f,  0x40d7, 0xb3, 0xcc, 0xd0, 0xc0, 0x2d, 0x5c, 0x32, 0x12 )
DEFINE_GUID(BrightnessContrastEffectGuid, 0xd3a1dbe1, 0x8ec4, 0x4c17, 0x9f, 0x4c, 0xea, 0x97, 0xad, 0x1c, 0x34, 0x3d )
DEFINE_GUID(HueSaturationLightnessEffectGuid, 0x8b2dd6c3, 0xeb07, 0x4d87, 0xa5, 0xf0, 0x71, 0x8, 0xe2, 0x6a, 0x9c, 0x5f )
DEFINE_GUID(LevelsEffectGuid, 0x99c354ec, 0x2a31, 0x4f3a, 0x8c, 0x34, 0x17, 0xa8, 0x3, 0xb3, 0x3a, 0x25 )
DEFINE_GUID(TintEffectGuid, 0x1077af00, 0x2848, 0x4441, 0x94, 0x89, 0x44, 0xad, 0x4c, 0x2d, 0x7a, 0x2c )
DEFINE_GUID(ColorBalanceEffectGuid, 0x537e597d, 0x251e, 0x48da, 0x96, 0x64, 0x29, 0xca, 0x49, 0x6b, 0x70, 0xf8 )
DEFINE_GUID(RedEyeCorrectionEffectGuid, 0x74d29d05, 0x69a4, 0x4266, 0x95, 0x49, 0x3c, 0xc5, 0x28, 0x36, 0xb6, 0x32 )
DEFINE_GUID(ColorCurveEffectGuid, 0xdd6a0022, 0x58e4, 0x4a67, 0x9d, 0x9b, 0xd4, 0x8e, 0xb8, 0x81, 0xa5, 0x3d )


SharpenParams           STRUC
radius                  real4 ?
amount                  real4 ?
SharpenParams           ENDS

BlurParams              STRUC
radius                  real4 ?
expandEdge              BOOL ?
BlurParams              ENDS

BrightnessContrastParams STRUC
brightnessLevel         SINT ?
contrastLevel           SINT ?
BrightnessContrastParams ENDS

RedEyeCorrectionParams  STRUC
numberOfAreas           UINT ?
areas                   LPRECT ?
RedEyeCorrectionParams  ENDS

HueSaturationLightnessParams STRUC
hueLevel                SINT ?
saturationLevel         SINT ?
lightnessLevel          SINT ?
HueSaturationLightnessParams ENDS

TintParams              STRUC
hue                     SINT ?
amount                  SINT ?
TintParams              ENDS

LevelsParams            STRUC
highlight               SINT ?
midtone                 SINT ?
shadow                  SINT ?
LevelsParams            ENDS

ColorBalanceParams      STRUC
cyanRed                 SINT ?
magentaGreen            SINT ?
yellowBlue              SINT ?
ColorBalanceParams      ENDS

ColorLUTParams          STRUC
lutB                    ColorChannelLUT <>
lutG                    ColorChannelLUT <>
lutR                    ColorChannelLUT <>
lutA                    ColorChannelLUT <>
ColorLUTParams          ENDS

.enum CurveAdjustments {
    AdjustExposure,
    AdjustDensity,
    AdjustContrast,
    AdjustHighlight,
    AdjustShadow,
    AdjustMidtone,
    AdjustWhiteSaturation,
    AdjustBlackSaturation
    }

.enum CurveChannel {
    CurveChannelAll,
    CurveChannelRed,
    CurveChannelGreen,
    CurveChannelBlue
    }


ColorCurveParams        STRUC
adjustment              CurveAdjustments ?
channel                 CurveChannel ?
adjustValue             SINT ?
ColorCurveParams        ENDS

GdipCreateEffect proto WINAPI \
                  guid: ptr GUID,
                effect: ptr
GdipDeleteEffect proto WINAPI \
                effect: ptr
GdipGetEffectParameterSize proto WINAPI \
                effect: ptr,
                  size: ptr
GdipSetEffectParameters proto WINAPI \
                effect: ptr,
                params: ptr,
                  size: UINT
GdipGetEffectParameters proto WINAPI \
                effect: ptr,
                  size: ptr,
                params: ptr

ifndef _GDIPLUSEFFECTS_EXCLUDEOBJECTS

.template Effect fastcall

    nativeEffect    ptr_t ?
    auxData         ptr_t ?
    auxDataSize     int_t ?
    useAuxData      BOOL ?

    .inline Effect :vararg {
        xor eax,eax
        mov this.nativeEffect,rax
        mov this.auxData,rax
        mov this.auxDataSize,eax
        mov this.useAuxData,eax
        }

    .static Release {

        ;; pvData is allocated by ApplyEffect. Return the pointer so that
        ;; it can be freed by the appropriate memory manager.

        GdipFree(this.auxData)
        ;; Release the native Effect.
        GdipDeleteEffect(this.nativeEffect)
        }

    .static GetAuxDataSize {
        mov eax,this.auxDataSize
        }
    .static GetAuxData {
        mov rax,this.auxData
        }
    .static UseAuxData useAuxDataFlag:abs {
        mov this.useAuxData,useAuxDataFlag
        }
    .static GetParameterSize size:abs {
        GdipGetEffectParameterSize(this.nativeEffect, size)
        }
    .static GetParameters size:abs, params:abs {
        GdipGetEffectParameters(this.nativeEffect, size, params)
        }
    .ends


.template Blur fastcall : public Effect

    .static Blur {
        Effect_Effect(this)
        ifdef __PE__
            .data
                BlurEffectGuid GUID _BlurEffectGuid
            .code
        endif
        GdipCreateEffect(addr BlurEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters parameters:abs {
        GdipSetEffectParameters(this.nativeEffect, parameters, sizeof(BlurParams))
        }
    .ends


.template Sharpen fastcall : public Effect

    .static Sharpen {
        Effect_Effect(this)
        ifdef __PE__
            .data
                SharpenEffectGuid GUID _SharpenEffectGuid
            .code
        endif
        GdipCreateEffect(addr SharpenEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(SharpenParams))
        }
    .ends


.template RedEyeCorrection fastcall : public Effect

    .static RedEyeCorrection {
        Effect_Effect(this)
        ifdef __PE__
            .data
                RedEyeCorrectionEffectGuid GUID _RedEyeCorrectionEffectGuid
            .code
        endif
        GdipCreateEffect(addr RedEyeCorrectionEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :ptr RedEyeCorrectionParams {
        mov eax,InvalidParameter
        .if _1
            imul eax,[_1].RedEyeCorrectionParams.numberOfAreas,sizeof(RECT)
            add  eax,sizeof(RedEyeCorrectionParams)
            GdipSetEffectParameters(this.nativeEffect, _1, eax)
        .endif
        }
    .ends


.template BrightnessContrast fastcall : public Effect

    .static BrightnessContrast {
        Effect_Effect(this)
        ifdef __PE__
            .data
                BrightnessContrastEffectGuid GUID _BrightnessContrastEffectGuid
            .code
        endif
        GdipCreateEffect(addr BrightnessContrastEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(BrightnessContrastParams))
        }
    .ends


.template HueSaturationLightness fastcall : public Effect

    .static HueSaturationLightness {
        Effect_Effect(this)
        ifdef __PE__
            .data
                HueSaturationLightnessEffectGuid GUID _HueSaturationLightnessEffectGuid
            .code
        endif
        GdipCreateEffect(addr HueSaturationLightnessEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(HueSaturationLightnessParams))
        }
    .ends

ifndef __Levels_INTERFACE_DEFINED__
.template Levels fastcall : public Effect

    .static Levels {
        Effect_Effect(this)
        ifdef __PE__
            .data
                LevelsEffectGuid GUID _LevelsEffectGuid
            .code
        endif
        GdipCreateEffect(addr LevelsEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(LevelsParams))
        }
    .ends
endif

.template Tint fastcall : public Effect

    .static Tint {
        Effect_Effect(this)
        ifdef __PE__
            .data
                TintEffectGuid GUID _TintEffectGuid
            .code
        endif
        GdipCreateEffect(addr TintEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(TintParams))
        }
    .ends


.template ColorBalance fastcall : public Effect

    .static ColorBalance {
        Effect_Effect(this)
        ifdef __PE__
            .data
                ColorBalanceEffectGuid GUID _ColorBalanceEffectGuid
            .code
        endif
        GdipCreateEffect(addr ColorBalanceEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(ColorBalanceParams))
        }
    .ends


.template ColorMatrixEffect fastcall : public Effect

    .static ColorMatrixEffect {
        Effect_Effect(this)
        ifdef __PE__
            .data
                ColorMatrixEffectGuid GUID _ColorMatrixEffectGuid
            .code
        endif
        GdipCreateEffect(addr ColorMatrixEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(ColorMatrix))
        }
    .ends


.template ColorLUT fastcall : public Effect

    .static ColorLUT {
        Effect_Effect(this)
        ifdef __PE__
            .data
                ColorLUTEffectGuid GUID _ColorLUTEffectGuid
            .code
        endif
        GdipCreateEffect(addr ColorLUTEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(ColorLUTParams))
        }
    .ends


.template ColorCurve fastcall : public Effect

    .static ColorCurve {
        Effect_Effect(this)
        ifdef __PE__
            .data
                ColorCurveEffectGuid GUID _ColorCurveEffectGuid
            .code
        endif
        GdipCreateEffect(addr ColorCurveEffectGuid, addr this.nativeEffect)
        }

    .static SetParameters :abs {
        GdipSetEffectParameters(this.nativeEffect, _1, sizeof(ColorCurveParams))
        }
    .ends

endif ;; _GDIPLUSEFFECTS_EXCLUDEEOBJECTS
endif ;;(GDIPVER GE 0x0110)
endif


