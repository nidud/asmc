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
    GetFrameStatistics	proc :ptr
    CreateTargetForHwnd proc :HWND, :BOOL, :ptr
    CreateVisual	proc :ptr
    CreateSurface	proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr
    CreateVirtualSurface proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr
    CreateSurfaceFromHandle proc :HANDLE, :ptr
    CreateSurfaceFromHwnd proc :HWND, :ptr
    CreateTranslateTransform proc :ptr
    CreateScaleTransform proc :ptr
    CreateRotateTransform proc :ptr
    CreateSkewTransform proc :ptr
    CreateMatrixTransform proc :ptr
    CreateTransformGroup proc :UINT, :ptr
    CreateTranslateTransform3D proc :ptr
    CreateScaleTransform3D proc :ptr
    CreateRotateTransform3D proc :ptr
    CreateMatrixTransform3D proc :ptr
    CreateTransform3DGroup proc :ptr, :UINT, :ptr
    CreateEffectGroup	proc :ptr
    CreateRectangleClip proc :ptr
    CreateAnimation	proc :ptr
    CheckDeviceState	proc :ptr
   .ENDS

DEFINE_IIDX(IDCompositionTarget, "eacdd04c-117e-4e17-88f4-d1b12b0e3d89")

.comdef IDCompositionTarget : public IUnknown

    SetRoot		proc :ptr
   .ENDS

DEFINE_IIDX(IDCompositionVisual, "4d93059d-097b-4651-9a60-f0f25116e2f3")

.comdef IDCompositionVisual : public IUnknown

    SetOffsetX?p	proc :ptr
    SetOffsetX?r	proc :real4
    SetOffsetY?p	proc :ptr
    SetOffsetY?r	proc :real4
    SetTransform	proc :ptr
    SetTransform2	proc :ptr
    SetTransformParent	proc :ptr
    SetEffect		proc :ptr
    SetBitmapInterpolationMode proc :DCOMPOSITION_BITMAP_INTERPOLATION_MODE
    SetBorderMode	proc :DCOMPOSITION_BORDER_MODE
    SetClip		proc :ptr
    SetClip2		proc :ptr
    SetContent		proc :ptr
    AddVisual		proc :ptr, :BOOL, :ptr
    RemoveVisual	proc :ptr
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

    SetOffsetX?p	proc :ptr
    SetOffsetX?r	proc :real4
    SetOffsetY?p	proc :ptr
    SetOffsetY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionScaleTransform, "71FDE914-40EF-45ef-BD51-68B037C339F9")

.comdef IDCompositionScaleTransform : public IDCompositionTransform

    SetScaleX?p		proc :ptr
    SetScaleX?r		proc :real4
    SetScaleY?p		proc :ptr
    SetScaleY?r		proc :real4
    SetCenterX?p	proc :ptr
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr
    SetCenterY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionRotateTransform, "641ED83C-AE96-46c5-90DC-32774CC5C6D5")

.comdef IDCompositionRotateTransform : public IDCompositionTransform

    SetAngle?p		proc :ptr
    SetAngle?r		proc :real4
    SetCenterX?p	proc :ptr
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr
    SetCenterY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionSkewTransform, "E57AA735-DCDB-4c72-9C61-0591F58889EE")

.comdef IDCompositionSkewTransform : public IDCompositionTransform

    SetAngleX?p		proc :ptr
    SetAngleX?r		proc :real4
    SetAngleY?p		proc :ptr
    SetAngleY?r		proc :real4
    SetCenterX?p	proc :ptr
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr
    SetCenterY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionMatrixTransform, "16CDFF07-C503-419c-83F2-0965C7AF1FA6")

.comdef IDCompositionMatrixTransform : public IDCompositionTransform

    SetMatrix		proc :ptr
    SetMatrixElement?p	proc :SINT, :SINT, :ptr
    SetMatrixElement?r	proc :SINT, :SINT, :real4
   .ENDS

DEFINE_IIDX(IDCompositionEffectGroup, "A7929A74-E6B2-4bd6-8B95-4040119CA34D")

.comdef IDCompositionEffectGroup : public IDCompositionEffect

    SetOpacity?p	proc :ptr
    SetOpacity?r	proc :real4
    SetTransform3D	proc :ptr
   .ENDS

DEFINE_IIDX(IDCompositionTranslateTransform3D, "91636D4B-9BA1-4532-AAF7-E3344994D788")

.comdef IDCompositionTranslateTransform3D : public IDCompositionTransform3D

    SetOffsetX?p	proc :ptr
    SetOffsetX?r	proc :real4
    SetOffsetY?p	proc :ptr
    SetOffsetY?r	proc :real4
    SetOffsetZ?p	proc :ptr
    SetOffsetZ?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionScaleTransform3D, "2A9E9EAD-364B-4b15-A7C4-A1997F78B389")

.comdef IDCompositionScaleTransform3D : public IDCompositionTransform3D

    SetScaleX?p		proc :ptr
    SetScaleX?r		proc :real4
    SetScaleY?p		proc :ptr
    SetScaleY?r		proc :real4
    SetScaleZ?p		proc :ptr
    SetScaleZ?r		proc :real4
    SetCenterX?p	proc :ptr
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr
    SetCenterY?r	proc :real4
    SetCenterZ?p	proc :ptr
    SetCenterZ?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionRotateTransform3D, "D8F5B23F-D429-4a91-B55A-D2F45FD75B18")

.comdef IDCompositionRotateTransform3D : public IDCompositionTransform3D

    SetAngle?p		proc :ptr
    SetAngle?r		proc :real4
    SetAxisX?p		proc :ptr
    SetAxisX?r		proc :real4
    SetAxisY?p		proc :ptr
    SetAxisY?r		proc :real4
    SetAxisZ?p		proc :ptr
    SetAxisZ?r		proc :real4
    SetCenterX?p	proc :ptr
    SetCenterX?r	proc :real4
    SetCenterY?p	proc :ptr
    SetCenterY?r	proc :real4
    SetCenterZ?p	proc :ptr
    SetCenterZ?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionMatrixTransform3D, "4B3363F0-643B-41b7-B6E0-CCF22D34467C")

.comdef IDCompositionMatrixTransform3D : public IDCompositionTransform3D

    SetMatrix		proc :ptr
    SetMatrixElement?p	proc :SINT, :SINT, :ptr
    SetMatrixElement?r	proc :SINT, :SINT, :real4
   .ENDS

DEFINE_IIDX(IDCompositionClip, "64AC3703-9D3F-45ec-A109-7CAC0E7A13A7")

.comdef IDCompositionClip : public IUnknown
   .ENDS

DEFINE_IIDX(IDCompositionRectangleClip, "9842AD7D-D9CF-4908-AED7-48B51DA5E7C2")

.comdef IDCompositionRectangleClip : public IDCompositionClip

    SetLeft?p		proc :ptr
    SetLeft?r		proc :real4
    SetTop?p		proc :ptr
    SetTop?r		proc :real4
    SetRight?p		proc :ptr
    SetRight?r		proc :real4
    SetBottom?p		proc :ptr
    SetBottom?r		proc :real4
    SetTopLeftRadiusX?p proc :ptr
    SetTopLeftRadiusX?r proc :real4
    SetTopLeftRadiusY?p proc :ptr
    SetTopLeftRadiusY?r proc :real4
    SetTopRightRadiusX?p proc :ptr
    SetTopRightRadiusX?r proc :real4
    SetTopRightRadiusY?p proc :ptr
    SetTopRightRadiusY?r proc :real4
    SetBottomLeftRadiusX?p proc :ptr
    SetBottomLeftRadiusX?r proc :real4
    SetBottomLeftRadiusY?p proc :ptr
    SetBottomLeftRadiusY?r proc :real4
    SetBottomRightRadiusX?p proc :ptr
    SetBottomRightRadiusX?r proc :real4
    SetBottomRightRadiusY?p proc :ptr
    SetBottomRightRadiusY?r proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionSurface, "BB8A4953-2C99-4F5A-96F5-4819027FA3AC")

.comdef IDCompositionSurface : public IUnknown

    BeginDraw		proc :ptr, :REFIID, :ptr, :ptr
    EndDraw		proc
    SuspendDraw		proc
    ResumeDraw		proc
    Scroll		proc :ptr, :ptr, :SINT, :SINT
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
    GetFrameStatistics	proc :ptr
    CreateVisual	proc :ptr
    CreateSurfaceFactory proc :ptr, :ptr
    CreateSurface	proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr
    CreateVirtualSurface proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr
    CreateTranslateTransform proc :ptr
    CreateScaleTransform proc :ptr
    CreateRotateTransform proc :ptr
    CreateSkewTransform proc :ptr
    CreateMatrixTransform proc :ptr
    CreateTransformGroup proc :UINT, :ptr
    CreateTranslateTransform3D proc :ptr
    CreateScaleTransform3D proc :ptr
    CreateRotateTransform3D proc :ptr
    CreateMatrixTransform3D proc :ptr
    CreateTransform3DGroup proc :ptr, :UINT, :ptr
    CreateEffectGroup	proc :ptr
    CreateRectangleClip proc :ptr
    CreateAnimation	proc :ptr
   .ENDS

DEFINE_IIDX(IDCompositionDesktopDevice, "5F4633FE-1E08-4CB8-8C75-CE24333F5602")

.comdef IDCompositionDesktopDevice : public IDCompositionDevice2

    CreateTargetForHwnd proc :HWND, :BOOL, :ptr
    CreateSurfaceFromHandle proc :HANDLE, :ptr
    CreateSurfaceFromHwnd proc :HWND, :ptr
   .ENDS

DEFINE_IIDX(IDCompositionDeviceDebug, "A1A3C64A-224F-4A81-9773-4F03A89D3C6C")

.comdef IDCompositionDeviceDebug : public IUnknown

    EnableDebugCounters proc
    DisableDebugCounters proc
   .ENDS

DEFINE_IIDX(IDCompositionSurfaceFactory, "E334BC12-3937-4E02-85EB-FCF4EB30D2C8")

.comdef IDCompositionSurfaceFactory : public IUnknown

    CreateSurface	proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr
    CreateVirtualSurface proc :UINT, :UINT, :DXGI_FORMAT, :DXGI_ALPHA_MODE, :ptr
   .ENDS

DEFINE_IIDX(IDCompositionVisual2, "E8DE1639-4331-4B26-BC5F-6A321D347A85")

.comdef IDCompositionVisual2 : public IDCompositionVisual

    SetOpacityMode	proc :DCOMPOSITION_OPACITY_MODE
    SetBackFaceVisibility proc :DCOMPOSITION_BACKFACE_VISIBILITY
   .ENDS

DEFINE_IIDX(IDCompositionVisualDebug, "FED2B808-5EB4-43A0-AEA3-35F65280F91B")

.comdef IDCompositionVisualDebug : public IDCompositionVisual2

    EnableHeatMap	proc :ptr
    DisableHeatMap	proc
    EnableRedrawRegions proc
    DisableRedrawRegions proc
   .ENDS
endif

if (_WIN32_WINNT GE _WIN32_WINNT_WINTHRESHOLD)

DEFINE_IIDX(IDCompositionVisual3, "2775F462-B6C1-4015-B0BE-B3E7D6A4976D")

.comdef IDCompositionVisual3 : public IDCompositionVisualDebug

    SetDepthMode	proc :DCOMPOSITION_DEPTH_MODE
    SetOffsetZ?p	proc :ptr
    SetOffsetZ?r	proc :real4
    SetOpacity?p	proc :ptr
    SetOpacity?r	proc :real4
    SetTransform?m	proc :ptr
    SetTransform?p	proc :ptr
    SetVisible		proc :BOOL
   .ENDS

DEFINE_IIDX(IDCompositionDevice3, "0987CB06-F916-48BF-8D35-CE7641781BD9")

.comdef IDCompositionDevice3 : public IDCompositionDevice2

    CreateGaussianBlurEffect proc :ptr
    CreateBrightnessEffect proc :ptr
    CreateColorMatrixEffect proc :ptr
    CreateShadowEffect	proc :ptr
    CreateHueRotationEffect proc :ptr
    CreateSaturationEffect proc :ptr
    CreateTurbulenceEffect proc :ptr
    CreateLinearTransferEffect proc :ptr
    CreateTableTransferEffect proc :ptr
    CreateCompositeEffect proc :ptr
    CreateBlendEffect	proc :ptr
    CreateArithmeticCompositeEffect proc :ptr
    CreateAffineTransform2DEffect proc :ptr
   .ENDS

DEFINE_IIDX(IDCompositionFilterEffect, "30C421D5-8CB2-4E9F-B133-37BE270D4AC2")

.comdef IDCompositionFilterEffect : public IDCompositionEffect

    SetInput		proc :UINT, :ptr, :UINT
   .ENDS

DEFINE_IIDX(IDCompositionGaussianBlurEffect, "45D4D0B7-1BD4-454E-8894-2BFA68443033")

.comdef IDCompositionGaussianBlurEffect : public IDCompositionFilterEffect

    SetStandardDeviation?p proc :ptr
    SetStandardDeviation?r proc :real4
    SetBorderMode	proc :D2D1_BORDER_MODE
   .ENDS

DEFINE_IIDX(IDCompositionBrightnessEffect, "6027496E-CB3A-49AB-934F-D798DA4F7DA6")

.comdef IDCompositionBrightnessEffect : public IDCompositionFilterEffect

    SetWhitePoint	proc :ptr
    SetBlackPoint	proc :ptr
    SetWhitePointX?p	proc :ptr
    SetWhitePointX?r	proc :real4
    SetWhitePointY?p	proc :ptr
    SetWhitePointY?r	proc :real4
    SetBlackPointX?p	proc :ptr
    SetBlackPointX?r	proc :real4
    SetBlackPointY?p	proc :ptr
    SetBlackPointY?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionColorMatrixEffect, "C1170A22-3CE2-4966-90D4-55408BFC84C4")

.comdef IDCompositionColorMatrixEffect : public IDCompositionFilterEffect

    SetMatrix		proc :ptr
    SetMatrixElement?p	proc :SINT, :SINT, :ptr
    SetMatrixElement?r	proc :SINT, :SINT, :real4
    SetAlphaMode	proc :D2D1_COLORMATRIX_ALPHA_MODE
    SetClampOutput	proc :BOOL
   .ENDS

DEFINE_IIDX(IDCompositionShadowEffect, "4AD18AC0-CFD2-4C2F-BB62-96E54FDB6879")

.comdef IDCompositionShadowEffect : public IDCompositionFilterEffect

    SetStandardDeviation?p proc :ptr
    SetStandardDeviation?r proc :real4
    SetColor		proc :ptr
    SetRed?p		proc :ptr
    SetRed?r		proc :real4
    SetGreen?p		proc :ptr
    SetGreen?r		proc :real4
    SetBlue?p		proc :ptr
    SetBlue?r		proc :real4
    SetAlpha?p		proc :ptr
    SetAlpha?r		proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionHueRotationEffect, "6DB9F920-0770-4781-B0C6-381912F9D167")

.comdef IDCompositionHueRotationEffect : public IDCompositionFilterEffect

    SetAngle?p		proc :ptr
    SetAngle?r		proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionSaturationEffect, "A08DEBDA-3258-4FA4-9F16-9174D3FE93B1")

.comdef IDCompositionSaturationEffect : public IDCompositionFilterEffect

    SetSaturation?p	proc :ptr
    SetSaturation?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionTurbulenceEffect, "A6A55BDA-C09C-49F3-9193-A41922C89715")

.comdef IDCompositionTurbulenceEffect : public IDCompositionFilterEffect

    SetOffset		proc :ptr
    SetBaseFrequency	proc :ptr
    SetSize		proc :ptr
    SetNumOctaves	proc :UINT
    SetSeed		proc :UINT
    SetNoise		proc :D2D1_TURBULENCE_NOISE
    SetStitchable	proc :BOOL
   .ENDS

DEFINE_IIDX(IDCompositionLinearTransferEffect, "4305EE5B-C4A0-4C88-9385-67124E017683")

.comdef IDCompositionLinearTransferEffect : public IDCompositionFilterEffect

    SetRedYIntercept?p	proc :ptr
    SetRedYIntercept?r	proc :real4
    SetRedSlope?p	proc :ptr
    SetRedSlope?r	proc :real4
    SetRedDisable	proc :BOOL
    SetGreenYIntercept?p proc :ptr
    SetGreenYIntercept?r proc :real4
    SetGreenSlope?p	proc :ptr
    SetGreenSlope?r	proc :real4
    SetGreenDisable	proc :BOOL
    SetBlueYIntercept?p proc :ptr
    SetBlueYIntercept?r proc :real4
    SetBlueSlope?p	proc :ptr
    SetBlueSlope?r	proc :real4
    SetBlueDisable	proc :BOOL
    SetAlphaYIntercept?p proc :ptr
    SetAlphaYIntercept?r proc :real4
    SetAlphaSlope?p	proc :ptr
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
    SetRedTableValue?p	proc :UINT, :ptr
    SetRedTableValue?r	proc :UINT, :real4
    SetGreenTableValue?p proc :UINT, :ptr
    SetGreenTableValue?r proc :UINT, :real4
    SetBlueTableValue?p proc :UINT, :ptr
    SetBlueTableValue?r proc :UINT, :real4
    SetAlphaTableValue?p proc :UINT, :ptr
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

    SetCoefficients	proc :ptr
    SetClampOutput	proc :BOOL
    SetCoefficient1?p	proc :ptr
    SetCoefficient1?r	proc :real4
    SetCoefficient2?p	proc :ptr
    SetCoefficient2?r	proc :real4
    SetCoefficient3?p	proc :ptr
    SetCoefficient3?r	proc :real4
    SetCoefficient4?p	proc :ptr
    SetCoefficient4?r	proc :real4
   .ENDS

DEFINE_IIDX(IDCompositionAffineTransform2DEffect, "0B74B9E8-CDD6-492F-BBBC-5ED32157026D")

.comdef IDCompositionAffineTransform2DEffect : public IDCompositionFilterEffect

    SetInterpolationMode proc :D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE
    SetBorderMode	proc :D2D1_BORDER_MODE
    SetTransformMatrix	proc :ptr
    SetTransformMatrixElement?p proc :SINT, :SINT, :ptr
    SetTransformMatrixElement?r proc :SINT, :SINT, :real4
    SetSharpness?p	proc :ptr
    SetSharpness?r	proc :real4
   .ENDS

endif

endif
.pragma list(pop)

