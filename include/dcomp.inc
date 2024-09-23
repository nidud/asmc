.pragma list(push, 0)

include d2dbasetypes.inc
ifndef D3DMATRIX_DEFINED
include d3d9types.inc
endif
include d2d1_1.inc

.pragma comment(lib, dcomp)

include dcomptypes.inc
include dcompanimation.inc

if (NTDDI_VERSION GE NTDDI_WIN8)

DCompositionCreateDevice proto WINAPI :ptr IDXGIDevice, :REFIID, :ptr
if (_WIN32_WINNT GE _WIN32_WINNT_WINBLUE)
DCompositionCreateDevice2 proto WINAPI :ptr IUnknown, :REFIID, :ptr
endif
if (_WIN32_WINNT GE _WIN32_WINNT_WINTHRESHOLD)
DCompositionCreateDevice3 proto WINAPI :ptr IUnknown, :REFIID, :ptr
endif
DCompositionCreateSurfaceHandle proto WINAPI :DWORD, :ptr SECURITY_ATTRIBUTES, :ptr HANDLE
DCompositionAttachMouseWheelToHwnd proto WINAPI :ptr IDCompositionVisual, :HWND, :BOOL
DCompositionAttachMouseDragToHwnd proto WINAPI :ptr IDCompositionVisual, :HWND, :BOOL

DEFINE_IIDX(IDCompositionDevice, "C37EA93A-E7AA-450D-B16F-9746CB0407F3")

.comdef IDCompositionDevice : public IUnknown

    Commit		proc
    WaitForCommitCompletion proc
    GetFrameStatistics	proc :ptr DCOMPOSITION_FRAME_STATISTICS
    CreateTargetForHwnd proc :HWND, :BOOL, :ptr ptr IDCompositionTarget
    CreateVisual	proc :ptr ptr IDCompositionVisual
    CreateSurface	proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr ptr IDCompositionSurface
    CreateVirtualSurface proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr ptr IDCompositionVirtualSurface
    CreateSurfaceFromHandle proc :HANDLE, :ptr ptr IUnknown
    CreateSurfaceFromHwnd proc :HWND, :ptr ptr IUnknown
    CreateTranslateTransform proc :ptr ptr IDCompositionTranslateTransform
    CreateScaleTransform proc :ptr ptr IDCompositionScaleTransform
    CreateRotateTransform proc :ptr ptr IDCompositionRotateTransform
    CreateSkewTransform proc :ptr ptr IDCompositionSkewTransform
    CreateMatrixTransform proc :ptr ptr IDCompositionMatrixTransform
    CreateTransformGroup proc :UINT, :ptr ptr IDCompositionTransform
    CreateTranslateTransform3D proc :ptr ptr IDCompositionTranslateTransform3D
    CreateScaleTransform3D proc :ptr ptr IDCompositionScaleTransform3D
    CreateRotateTransform3D proc :ptr ptr IDCompositionRotateTransform3D
    CreateMatrixTransform3D proc :ptr ptr IDCompositionMatrixTransform3D
    CreateTransform3DGroup proc :ptr ptr IDCompositionTransform3D, :UINT, :ptr ptr IDCompositionTransform3D
    CreateEffectGroup	proc :ptr ptr IDCompositionEffectGroup
    CreateRectangleClip proc :ptr ptr IDCompositionRectangleClip
    CreateAnimation	proc :ptr ptr IDCompositionAnimation
    CheckDeviceState	proc :ptr BOOL
   .ENDS

DEFINE_IIDX(IDCompositionTarget, "eacdd04c-117e-4e17-88f4-d1b12b0e3d89")

.comdef IDCompositionTarget : public IUnknown

    SetRoot		proc :ptr IDCompositionVisual
   .ENDS

DEFINE_IIDX(IDCompositionVisual, "4d93059d-097b-4651-9a60-f0f25116e2f3")

.comdef IDCompositionVisual : public IUnknown

    SetOffsetX?p	proc :ptr IDCompositionAnimation
    SetOffsetX?r	proc :real4
    SetOffsetY?p	proc :ptr IDCompositionAnimation
    SetOffsetY?r	proc :real4
    SetTransform	proc :ptr D2D_MATRIX_3X2_F
    SetTransform2	proc :ptr IDCompositionTransform
    SetTransformParent	proc :ptr IDCompositionVisual
    SetEffect		proc :ptr IDCompositionEffect
    SetBitmapInterpolationMode proc :DCOMPOSITION_BITMAP_INTERPOLATION_MODE
    SetBorderMode	proc :DCOMPOSITION_BORDER_MODE
    SetClip		proc :ptr D2D_RECT_F
    SetClip2		proc :ptr IDCompositionClip
    SetContent		proc :ptr IUnknown
    AddVisual		proc :ptr IDCompositionVisual, :BOOL, :ptr IDCompositionVisual
    RemoveVisual	proc :ptr IDCompositionVisual
    RemoveAllVisuals	proc
    SetCompositeMode	proc :DCOMPOSITION_COMPOSITE_MODE
   .ENDS

DEFINE_IIDX(IDCompositionEffect, "EC81B08F-BFCB-4e8d-B193-A915587999E8")

.comdef IDCompositionEffect : public IUnknown
   .ENDS

DEFINE_IIDX(IDCompositionTransform3D, "71185722-246B-41f2-AAD1-0443F7F4BFC2")

.comdef IDCompositionTransform3D : public IDCompositionEffect
   .ENDS

DEFINE_IIDX(IDCompositionTransform, "FD55FAA7-37E0-4c20-95D2-9BE45BC33F55")

.comdef IDCompositionTransform : public IDCompositionTransform3D
   .ENDS

DEFINE_IIDX(IDCompositionTranslateTransform, "06791122-C6F0-417d-8323-269E987F5954")

.comdef IDCompositionTranslateTransform : public IDCompositionTransform

    SetOffsetX?p	proc :ptr IDCompositionAnimation
    SetOffsetX?r	proc :real4
    SetOffsetY?p	proc :ptr IDCompositionAnimation
    SetOffsetY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionScaleTransform, "71FDE914-40EF-45ef-BD51-68B037C339F9")

.comdef IDCompositionScaleTransform : public IDCompositionTransform

    SetScaleX?p		proc :ptr IDCompositionAnimation
    SetScaleX?r		proc :real4
    SetScaleY?p		proc :ptr IDCompositionAnimation
    SetScaleY?r		proc :real4
    SetCenterX?p	proc :ptr IDCompositionAnimation
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr IDCompositionAnimation
    SetCenterY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionRotateTransform, "641ED83C-AE96-46c5-90DC-32774CC5C6D5")

.comdef IDCompositionRotateTransform : public IDCompositionTransform

    SetAngle?p		proc :ptr IDCompositionAnimation
    SetAngle?r		proc :real4
    SetCenterX?p	proc :ptr IDCompositionAnimation
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr IDCompositionAnimation
    SetCenterY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionSkewTransform, "E57AA735-DCDB-4c72-9C61-0591F58889EE")

.comdef IDCompositionSkewTransform : public IDCompositionTransform

    SetAngleX?p		proc :ptr IDCompositionAnimation
    SetAngleX?r		proc :real4
    SetAngleY?p		proc :ptr IDCompositionAnimation
    SetAngleY?r		proc :real4
    SetCenterX?p	proc :ptr IDCompositionAnimation
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr IDCompositionAnimation
    SetCenterY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionMatrixTransform, "16CDFF07-C503-419c-83F2-0965C7AF1FA6")

.comdef IDCompositionMatrixTransform : public IDCompositionTransform

    SetMatrix		proc :ptr D2D_MATRIX_3X2_F
    SetMatrixElement?p	proc :SINT, :SINT, :ptr IDCompositionAnimation
    SetMatrixElement?r	proc :SINT, :SINT, :real4
   .ENDS

DEFINE_IIDX(IDCompositionEffectGroup, "A7929A74-E6B2-4bd6-8B95-4040119CA34D")

.comdef IDCompositionEffectGroup : public IDCompositionEffect

    SetOpacity?p	proc :ptr IDCompositionAnimation
    SetOpacity?r	proc :real4
    SetTransform3D	proc :ptr IDCompositionTransform3D
   .ENDS

DEFINE_IIDX(IDCompositionTranslateTransform3D, "91636D4B-9BA1-4532-AAF7-E3344994D788")

.comdef IDCompositionTranslateTransform3D : public IDCompositionTransform3D

    SetOffsetX?p	proc :ptr IDCompositionAnimation
    SetOffsetX?r	proc :real4
    SetOffsetY?p	proc :ptr IDCompositionAnimation
    SetOffsetY?r	proc :real4
    SetOffsetZ?p	proc :ptr IDCompositionAnimation
    SetOffsetZ?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionScaleTransform3D, "2A9E9EAD-364B-4b15-A7C4-A1997F78B389")

.comdef IDCompositionScaleTransform3D : public IDCompositionTransform3D

    SetScaleX?p		proc :ptr IDCompositionAnimation
    SetScaleX?r		proc :real4
    SetScaleY?p		proc :ptr IDCompositionAnimation
    SetScaleY?r		proc :real4
    SetScaleZ?p		proc :ptr IDCompositionAnimation
    SetScaleZ?r		proc :real4
    SetCenterX?p	proc :ptr IDCompositionAnimation
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr IDCompositionAnimation
    SetCenterY?r	proc :real4
    SetCenterZ?p	proc :ptr IDCompositionAnimation
    SetCenterZ?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionRotateTransform3D, "D8F5B23F-D429-4a91-B55A-D2F45FD75B18")

.comdef IDCompositionRotateTransform3D : public IDCompositionTransform3D

    SetAngle?p		proc :ptr IDCompositionAnimation
    SetAngle?r		proc :real4
    SetAxisX?p		proc :ptr IDCompositionAnimation
    SetAxisX?r		proc :real4
    SetAxisY?p		proc :ptr IDCompositionAnimation
    SetAxisY?r		proc :real4
    SetAxisZ?p		proc :ptr IDCompositionAnimation
    SetAxisZ?r		proc :real4
    SetCenterX?p	proc :ptr IDCompositionAnimation
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr IDCompositionAnimation
    SetCenterY?r	proc :real4
    SetCenterZ?p	proc :ptr IDCompositionAnimation
    SetCenterZ?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionMatrixTransform3D, "4B3363F0-643B-41b7-B6E0-CCF22D34467C")

.comdef IDCompositionMatrixTransform3D : public IDCompositionTransform3D

    SetMatrix		proc :ptr D3DMATRIX
    SetMatrixElement?p	proc :SINT, :SINT, :ptr IDCompositionAnimation
    SetMatrixElement?r	proc :SINT, :SINT, :real4
   .ENDS

DEFINE_IIDX(IDCompositionClip, "64AC3703-9D3F-45ec-A109-7CAC0E7A13A7")

.comdef IDCompositionClip : public IUnknown
   .ENDS

DEFINE_IIDX(IDCompositionRectangleClip, "9842AD7D-D9CF-4908-AED7-48B51DA5E7C2")

.comdef IDCompositionRectangleClip : public IDCompositionClip

    SetLeft?p		proc :ptr IDCompositionAnimation
    SetLeft?r		proc :real4
    SetTop?p		proc :ptr IDCompositionAnimation
    SetTop?r		proc :real4
    SetRight?p		proc :ptr IDCompositionAnimation
    SetRight?r		proc :real4
    SetBottom?p		proc :ptr IDCompositionAnimation
    SetBottom?r		proc :real4
    SetTopLeftRadiusX?p proc :ptr IDCompositionAnimation
    SetTopLeftRadiusX?r proc :real4
    SetTopLeftRadiusY?p proc :ptr IDCompositionAnimation
    SetTopLeftRadiusY?r proc :real4
    SetTopRightRadiusX?p proc :ptr IDCompositionAnimation
    SetTopRightRadiusX?r proc :real4
    SetTopRightRadiusY?p proc :ptr IDCompositionAnimation
    SetTopRightRadiusY?r proc :real4
    SetBottomLeftRadiusX?p proc :ptr IDCompositionAnimation
    SetBottomLeftRadiusX?r proc :real4
    SetBottomLeftRadiusY?p proc :ptr IDCompositionAnimation
    SetBottomLeftRadiusY?r proc :real4
    SetBottomRightRadiusX?p proc :ptr IDCompositionAnimation
    SetBottomRightRadiusX?r proc :real4
    SetBottomRightRadiusY?p proc :ptr IDCompositionAnimation
    SetBottomRightRadiusY?r proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionSurface, "BB8A4953-2C99-4F5A-96F5-4819027FA3AC")

.comdef IDCompositionSurface : public IUnknown

    BeginDraw		proc :ptr RECT, :REFIID, :ptr ptr, :ptr POINT
    EndDraw		proc
    SuspendDraw		proc
    ResumeDraw		proc
    Scroll		proc :ptr RECT, :ptr RECT, :SINT, :SINT
   .ENDS

DEFINE_IIDX(IDCompositionVirtualSurface, "AE471C51-5F53-4A24-8D3E-D0C39C30B3F0")

.comdef IDCompositionVirtualSurface : public IDCompositionSurface

    Resize		proc :UINT, :UINT
    Trim		proc :UINT
   .ENDS

if (_WIN32_WINNT GE _WIN32_WINNT_WINBLUE)

DEFINE_IIDX(IDCompositionDevice2, "75F6468D-1B8E-447C-9BC6-75FEA80B5B25")

.comdef IDCompositionDevice2 : public IUnknown

    Commit		proc
    WaitForCommitCompletion proc
    GetFrameStatistics	proc :ptr DCOMPOSITION_FRAME_STATISTICS
    CreateVisual	proc :ptr ptr IDCompositionVisual2
    CreateSurfaceFactory proc :ptr IUnknown, :ptr ptr IDCompositionSurfaceFactory
    CreateSurface	proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr ptr IDCompositionSurface
    CreateVirtualSurface proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr ptr IDCompositionVirtualSurface
    CreateTranslateTransform proc :ptr ptr IDCompositionTranslateTransform
    CreateScaleTransform proc :ptr ptr IDCompositionScaleTransform
    CreateRotateTransform proc :ptr ptr IDCompositionRotateTransform
    CreateSkewTransform proc :ptr ptr IDCompositionSkewTransform
    CreateMatrixTransform proc :ptr ptr IDCompositionMatrixTransform
    CreateTransformGroup proc :UINT, :ptr ptr IDCompositionTransform
    CreateTranslateTransform3D proc :ptr ptr IDCompositionTranslateTransform3D
    CreateScaleTransform3D proc :ptr ptr IDCompositionScaleTransform3D
    CreateRotateTransform3D proc :ptr ptr IDCompositionRotateTransform3D
    CreateMatrixTransform3D proc :ptr ptr IDCompositionMatrixTransform3D
    CreateTransform3DGroup proc :ptr ptr IDCompositionTransform3D, :UINT, :ptr ptr IDCompositionTransform3D
    CreateEffectGroup	proc :ptr ptr IDCompositionEffectGroup
    CreateRectangleClip proc :ptr ptr IDCompositionRectangleClip
    CreateAnimation	proc :ptr ptr IDCompositionAnimation
   .ENDS

DEFINE_IIDX(IDCompositionDesktopDevice, "5F4633FE-1E08-4CB8-8C75-CE24333F5602")

.comdef IDCompositionDesktopDevice : public IDCompositionDevice2

    CreateTargetForHwnd proc :HWND, :BOOL, :ptr ptr IDCompositionTarget
    CreateSurfaceFromHandle proc :HANDLE, :ptr ptr IUnknown
    CreateSurfaceFromHwnd proc :HWND, :ptr ptr IUnknown
   .ENDS

DEFINE_IIDX(IDCompositionDeviceDebug, "A1A3C64A-224F-4A81-9773-4F03A89D3C6C")

.comdef IDCompositionDeviceDebug : public IUnknown

    EnableDebugCounters proc
    DisableDebugCounters proc
   .ENDS

DEFINE_IIDX(IDCompositionSurfaceFactory, "E334BC12-3937-4E02-85EB-FCF4EB30D2C8")

.comdef IDCompositionSurfaceFactory : public IUnknown

    CreateSurface	proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr ptr IDCompositionSurface
    CreateVirtualSurface proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr ptr IDCompositionVirtualSurface
   .ENDS

DEFINE_IIDX(IDCompositionVisual2, "E8DE1639-4331-4B26-BC5F-6A321D347A85")

.comdef IDCompositionVisual2 : public IDCompositionVisual

    SetOpacityMode	proc :DCOMPOSITION_OPACITY_MODE
    SetBackFaceVisibility proc :DCOMPOSITION_BACKFACE_VISIBILITY
   .ENDS

DEFINE_IIDX(IDCompositionVisualDebug, "FED2B808-5EB4-43A0-AEA3-35F65280F91B")

.comdef IDCompositionVisualDebug : public IDCompositionVisual2

    EnableHeatMap	proc :ptr D2D1_COLOR_F
    DisableHeatMap	proc
    EnableRedrawRegions proc
    DisableRedrawRegions proc
   .ENDS
endif

if (_WIN32_WINNT GE _WIN32_WINNT_WINTHRESHOLD)

DEFINE_IIDX(IDCompositionVisual3, "2775F462-B6C1-4015-B0BE-B3E7D6A4976D")

.comdef IDCompositionVisual3 : public IDCompositionVisualDebug

    SetDepthMode	proc :DCOMPOSITION_DEPTH_MODE
    SetOffsetZ?p	proc :ptr IDCompositionAnimation
    SetOffsetZ?r	proc :real4
    SetOpacity?p	proc :ptr IDCompositionAnimation
    SetOpacity?r	proc :real4
    SetTransform?m	proc :ptr D2D_MATRIX_4X4_F
    SetTransform?p	proc :ptr IDCompositionTransform3D
    SetVisible		proc :BOOL
   .ENDS

DEFINE_IIDX(IDCompositionDevice3, "0987CB06-F916-48BF-8D35-CE7641781BD9")

.comdef IDCompositionDevice3 : public IDCompositionDevice2

    CreateGaussianBlurEffect proc :ptr ptr IDCompositionGaussianBlurEffect
    CreateBrightnessEffect proc :ptr ptr IDCompositionBrightnessEffect
    CreateColorMatrixEffect proc :ptr ptr IDCompositionColorMatrixEffect
    CreateShadowEffect	proc :ptr ptr IDCompositionShadowEffect
    CreateHueRotationEffect proc :ptr ptr IDCompositionHueRotationEffect
    CreateSaturationEffect proc :ptr ptr IDCompositionSaturationEffect
    CreateTurbulenceEffect proc :ptr ptr IDCompositionTurbulenceEffect
    CreateLinearTransferEffect proc :ptr ptr IDCompositionLinearTransferEffect
    CreateTableTransferEffect proc :ptr ptr IDCompositionTableTransferEffect
    CreateCompositeEffect proc :ptr ptr IDCompositionCompositeEffect
    CreateBlendEffect	proc :ptr ptr IDCompositionBlendEffect
    CreateArithmeticCompositeEffect proc :ptr ptr IDCompositionArithmeticCompositeEffect
    CreateAffineTransform2DEffect proc :ptr ptr IDCompositionAffineTransform2DEffect
   .ENDS

DEFINE_IIDX(IDCompositionFilterEffect, "30C421D5-8CB2-4E9F-B133-37BE270D4AC2")

.comdef IDCompositionFilterEffect : public IDCompositionEffect

    SetInput		proc :UINT, :ptr IUnknown, :UINT
   .ENDS

DEFINE_IIDX(IDCompositionGaussianBlurEffect, "45D4D0B7-1BD4-454E-8894-2BFA68443033")

.comdef IDCompositionGaussianBlurEffect : public IDCompositionFilterEffect

    SetStandardDeviation?p proc :ptr IDCompositionAnimation
    SetStandardDeviation?r proc :real4
    SetBorderMode	proc :D2D1_BORDER_MODE
   .ENDS

DEFINE_IIDX(IDCompositionBrightnessEffect, "6027496E-CB3A-49AB-934F-D798DA4F7DA6")

.comdef IDCompositionBrightnessEffect : public IDCompositionFilterEffect

    SetWhitePoint	proc :ptr D2D1_VECTOR_2F
    SetBlackPoint	proc :ptr D2D1_VECTOR_2F
    SetWhitePointX?p	proc :ptr IDCompositionAnimation
    SetWhitePointX?r	proc :real4
    SetWhitePointY?p	proc :ptr IDCompositionAnimation
    SetWhitePointY?r	proc :real4
    SetBlackPointX?p	proc :ptr IDCompositionAnimation
    SetBlackPointX?r	proc :real4
    SetBlackPointY?p	proc :ptr IDCompositionAnimation
    SetBlackPointY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionColorMatrixEffect, "C1170A22-3CE2-4966-90D4-55408BFC84C4")

.comdef IDCompositionColorMatrixEffect : public IDCompositionFilterEffect

    SetMatrix		proc :ptr D2D1_MATRIX_5X4_F
    SetMatrixElement?p	proc :SINT, :SINT, :ptr IDCompositionAnimation
    SetMatrixElement?r	proc :SINT, :SINT, :real4
    SetAlphaMode	proc :D2D1_COLORMATRIX_ALPHA_MODE
    SetClampOutput	proc :BOOL
   .ENDS

DEFINE_IIDX(IDCompositionShadowEffect, "4AD18AC0-CFD2-4C2F-BB62-96E54FDB6879")

.comdef IDCompositionShadowEffect : public IDCompositionFilterEffect

    SetStandardDeviation?p proc :ptr IDCompositionAnimation
    SetStandardDeviation?r proc :real4
    SetColor		proc :ptr D2D1_VECTOR_4F
    SetRed?p		proc :ptr IDCompositionAnimation
    SetRed?r		proc :real4
    SetGreen?p		proc :ptr IDCompositionAnimation
    SetGreen?r		proc :real4
    SetBlue?p		proc :ptr IDCompositionAnimation
    SetBlue?r		proc :real4
    SetAlpha?p		proc :ptr IDCompositionAnimation
    SetAlpha?r		proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionHueRotationEffect, "6DB9F920-0770-4781-B0C6-381912F9D167")

.comdef IDCompositionHueRotationEffect : public IDCompositionFilterEffect

    SetAngle?p		proc :ptr IDCompositionAnimation
    SetAngle?r		proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionSaturationEffect, "A08DEBDA-3258-4FA4-9F16-9174D3FE93B1")

.comdef IDCompositionSaturationEffect : public IDCompositionFilterEffect

    SetSaturation?p	proc :ptr IDCompositionAnimation
    SetSaturation?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionTurbulenceEffect, "A6A55BDA-C09C-49F3-9193-A41922C89715")

.comdef IDCompositionTurbulenceEffect : public IDCompositionFilterEffect

    SetOffset		proc :ptr D2D1_VECTOR_2F
    SetBaseFrequency	proc :ptr D2D1_VECTOR_2F
    SetSize		proc :ptr D2D1_VECTOR_2F
    SetNumOctaves	proc :UINT
    SetSeed		proc :UINT
    SetNoise		proc :D2D1_TURBULENCE_NOISE
    SetStitchable	proc :BOOL
   .ENDS

DEFINE_IIDX(IDCompositionLinearTransferEffect, "4305EE5B-C4A0-4C88-9385-67124E017683")

.comdef IDCompositionLinearTransferEffect : public IDCompositionFilterEffect

    SetRedYIntercept?p	proc :ptr IDCompositionAnimation
    SetRedYIntercept?r	proc :real4
    SetRedSlope?p	proc :ptr IDCompositionAnimation
    SetRedSlope?r	proc :real4
    SetRedDisable	proc :BOOL
    SetGreenYIntercept?p proc :ptr IDCompositionAnimation
    SetGreenYIntercept?r proc :real4
    SetGreenSlope?p	proc :ptr IDCompositionAnimation
    SetGreenSlope?r	proc :real4
    SetGreenDisable	proc :BOOL
    SetBlueYIntercept?p proc :ptr IDCompositionAnimation
    SetBlueYIntercept?r proc :real4
    SetBlueSlope?p	proc :ptr IDCompositionAnimation
    SetBlueSlope?r	proc :real4
    SetBlueDisable	proc :BOOL
    SetAlphaYIntercept?p proc :ptr IDCompositionAnimation
    SetAlphaYIntercept?r proc :real4
    SetAlphaSlope?p	proc :ptr IDCompositionAnimation
    SetAlphaSlope?r	proc :real4
    SetAlphaDisable	proc :BOOL
    SetClampOutput	proc :BOOL
   .ENDS

DEFINE_IIDX(IDCompositionTableTransferEffect, "9B7E82E2-69C5-4EB4-A5F5-A7033F5132CD")

.comdef IDCompositionTableTransferEffect : public IDCompositionFilterEffect

    SetRedTable		proc :UINT
    SetGreenTable	proc :UINT
    SetBlueTable	proc :UINT
    SetAlphaTable	proc :UINT
    SetRedDisable	proc :BOOL
    SetGreenDisable	proc :BOOL
    SetBlueDisable	proc :BOOL
    SetAlphaDisable	proc :BOOL
    SetClampOutput	proc :BOOL
    SetRedTableValue?p	proc :UINT, :ptr IDCompositionAnimation
    SetRedTableValue?r	proc :UINT, :real4
    SetGreenTableValue?p proc :UINT, :ptr IDCompositionAnimation
    SetGreenTableValue?r proc :UINT, :real4
    SetBlueTableValue?p proc :UINT, :ptr IDCompositionAnimation
    SetBlueTableValue?r proc :UINT, :real4
    SetAlphaTableValue?p proc :UINT, :ptr IDCompositionAnimation
    SetAlphaTableValue?r proc :UINT, :real4
   .ENDS

DEFINE_IIDX(IDCompositionCompositeEffect, "576616C0-A231-494D-A38D-00FD5EC4DB46")

.comdef IDCompositionCompositeEffect : public IDCompositionFilterEffect

    SetMode		proc :D2D1_COMPOSITE_MODE
   .ENDS

DEFINE_IIDX(IDCompositionBlendEffect, "33ECDC0A-578A-4A11-9C14-0CB90517F9C5")

.comdef IDCompositionBlendEffect : public IDCompositionFilterEffect

    SetMode		proc :D2D1_BLEND_MODE
   .ENDS

DEFINE_IIDX(IDCompositionArithmeticCompositeEffect, "3B67DFA8-E3DD-4E61-B640-46C2F3D739DC")

.comdef IDCompositionArithmeticCompositeEffect : public IDCompositionFilterEffect

    SetCoefficients	proc :ptr D2D1_VECTOR_4F
    SetClampOutput	proc :BOOL
    SetCoefficient1?p	proc :ptr IDCompositionAnimation
    SetCoefficient1?r	proc :real4
    SetCoefficient2?p	proc :ptr IDCompositionAnimation
    SetCoefficient2?r	proc :real4
    SetCoefficient3?p	proc :ptr IDCompositionAnimation
    SetCoefficient3?r	proc :real4
    SetCoefficient4?p	proc :ptr IDCompositionAnimation
    SetCoefficient4?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionAffineTransform2DEffect, "0B74B9E8-CDD6-492F-BBBC-5ED32157026D")

.comdef IDCompositionAffineTransform2DEffect : public IDCompositionFilterEffect

    SetInterpolationMode proc :D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE
    SetBorderMode	proc :D2D1_BORDER_MODE
    SetTransformMatrix	proc :ptr D2D1_MATRIX_3X2_F
    SetTransformMatrixElement?p proc :SINT, :SINT, :ptr IDCompositionAnimation
    SetTransformMatrixElement?r proc :SINT, :SINT, :real4
    SetSharpness?p	proc :ptr IDCompositionAnimation
    SetSharpness?r	proc :real4
   .ENDS

endif

endif
.pragma list(pop)

