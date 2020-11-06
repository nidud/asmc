include d2dbasetypes.inc
ifndef D3DMATRIX_DEFINED
include d3d9types.inc
endif
include d2d1_1.inc

include dcomptypes.inc
include dcompanimation.inc

if (NTDDI_VERSION GE NTDDI_WIN8)

DCompositionCreateDevice proto WINAPI \
	    dxgiDevice: ptr IDXGIDevice,
		   iid: REFIID,
    dcompositionDevice: ptr


if (_WIN32_WINNT GE _WIN32_WINNT_WINBLUE)

DCompositionCreateDevice2 proto WINAPI \
       renderingDevice: ptr IUnknown,
		   iid: REFIID,
    dcompositionDevice: ptr

endif

if (_WIN32_WINNT GE _WIN32_WINNT_WINTHRESHOLD)

DCompositionCreateDevice3 proto WINAPI \
       renderingDevice: ptr IUnknown,
		   iid: REFIID,
    dcompositionDevice: ptr


endif

DCompositionCreateSurfaceHandle proto WINAPI \
	 desiredAccess: DWORD,
    securityAttributes: ptr SECURITY_ATTRIBUTES,
	 surfaceHandle: ptr HANDLE

DCompositionAttachMouseWheelToHwnd proto WINAPI \
		visual: IDCompositionVisual*,
		  hwnd: HWND,
		enable: BOOL

DCompositionAttachMouseDragToHwnd proto WINAPI \
		visual: IDCompositionVisual*,
		  hwnd: HWND,
		enable: BOOL


DEFINE_IIDX(IDCompositionDevice, "C37EA93A-E7AA-450D-B16F-9746CB0407F3")

.comdef IDCompositionDevice : public IUnknown

    Commit		proc
    WaitForCommitCompletion proc
    GetFrameStatistics	proc :ptr DCOMPOSITION_FRAME_STATISTICS
    CreateTargetForHwnd proc :HWND hwnd, :BOOL, :ptr ptr IDCompositionTarget
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
    CreateTransform3DGroup proc :UINT, :ptr ptr IDCompositionTransform3D
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

    SetOffsetX		proc :float
    SetOffsetX		proc :ptr IDCompositionAnimation
    SetOffsetY		proc :float
    SetOffsetY		proc :ptr IDCompositionAnimation
    SetTransform	proc :ptr D2D_MATRIX_3X2_F
    SetTransform	proc :ptr IDCompositionTransform
    SetTransformParent	proc :ptr IDCompositionVisual
    SetEffect		proc :ptr IDCompositionEffect
    SetBitmapInterpolationMode proc :DCOMPOSITION_BITMAP_INTERPOLATION_MODE
    SetBorderMode	proc :DCOMPOSITION_BORDER_MODE
    SetClip		proc :ptr D2D_RECT_F
    SetClip		proc :ptr IDCompositionClip
    SetContent		proc :ptr IUnknown *content
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

    SetOffsetX		proc :float
    SetOffsetX2		proc :ptr IDCompositionAnimation
    SetOffsetY		proc :float
    SetOffsetY2		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionScaleTransform, "71FDE914-40EF-45ef-BD51-68B037C339F9")

.comdef IDCompositionScaleTransform : public IDCompositionTransform

    SetScaleX		proc :float
    SetScaleX		proc :ptr IDCompositionAnimation
    SetScaleY		proc :float
    SetScaleY		proc :ptr IDCompositionAnimation
    SetCenterX		proc :float
    SetCenterX		proc :ptr IDCompositionAnimation
    SetCenterY		proc :float
    SetCenterY		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionRotateTransform, "641ED83C-AE96-46c5-90DC-32774CC5C6D5")

.comdef IDCompositionRotateTransform : public IDCompositionTransform

    SetAngle		proc :float
    SetAngle2		proc :ptr IDCompositionAnimation
    SetCenterX		proc :float
    SetCenterX2		proc :ptr IDCompositionAnimation
    SetCenterY		proc :float
    SetCenterY2		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionSkewTransform, "E57AA735-DCDB-4c72-9C61-0591F58889EE")

.comdef IDCompositionSkewTransform : public IDCompositionTransform

    SetAngleX		proc :float
    SetAngleX2		proc :ptr IDCompositionAnimation
    SetAngleY		proc :float
    SetAngleY2		proc :ptr IDCompositionAnimation
    SetCenterX		proc :float
    SetCenterX2		proc :ptr IDCompositionAnimation
    SetCenterY		proc :float
    SetCenterY2		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionMatrixTransform, "16CDFF07-C503-419c-83F2-0965C7AF1FA6")

.comdef IDCompositionMatrixTransform : public IDCompositionTransform

    SetMatrix		proc :ptr D2D_MATRIX_3X2_F
    SetMatrixElement	proc :SINT, :SINT, :float
    SetMatrixElement2	proc :SINT, :SINT, :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionEffectGroup, "A7929A74-E6B2-4bd6-8B95-4040119CA34D")

.comdef IDCompositionEffectGroup : public IDCompositionEffect

    SetOpacity		proc :float
    SetOpacity2		proc :ptr IDCompositionAnimation
    SetTransform3D	proc :ptr IDCompositionTransform3D
    .ENDS

DEFINE_IIDX(IDCompositionTranslateTransform3D, "91636D4B-9BA1-4532-AAF7-E3344994D788")

.comdef IDCompositionTranslateTransform3D : public IDCompositionTransform3D

    SetOffsetX		proc :float
    SetOffsetX2		proc :ptr IDCompositionAnimation
    SetOffsetY		proc :float
    SetOffsetY2		proc :ptr IDCompositionAnimation
    SetOffsetZ		proc :float
    SetOffsetZ2		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionScaleTransform3D, "2A9E9EAD-364B-4b15-A7C4-A1997F78B389")

.comdef IDCompositionScaleTransform3D : public IDCompositionTransform3D

    SetScaleX		proc :float
    SetScaleX2		proc :ptr IDCompositionAnimation
    SetScaleY		proc :float
    SetScaleY2		proc :ptr IDCompositionAnimation
    SetScaleZ		proc :float
    SetScaleZ2		proc :ptr IDCompositionAnimation
    SetCenterX		proc :float
    SetCenterX2		proc :ptr IDCompositionAnimation
    SetCenterY		proc :float
    SetCenterY2		proc :ptr IDCompositionAnimation
    SetCenterZ		proc :float
    SetCenterZ2		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionRotateTransform3D, "D8F5B23F-D429-4a91-B55A-D2F45FD75B18")

.comdef IDCompositionRotateTransform3D : public IDCompositionTransform3D

    SetAngle		proc :float
    SetAngle2		proc :ptr IDCompositionAnimation
    SetAxisX		proc :float
    SetAxisX2		proc :ptr IDCompositionAnimation
    SetAxisY		proc :float
    SetAxisY2		proc :ptr IDCompositionAnimation
    SetAxisZ		proc :float
    SetAxisZ2		proc :ptr IDCompositionAnimation
    SetCenterX		proc :float
    SetCenterX2		proc :ptr IDCompositionAnimation
    SetCenterY		proc :float
    SetCenterY2		proc :ptr IDCompositionAnimation
    SetCenterZ		proc :float
    SetCenterZ2		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionMatrixTransform3D, "4B3363F0-643B-41b7-B6E0-CCF22D34467C")

.comdef IDCompositionMatrixTransform3D : public IDCompositionTransform3D

    SetMatrix		proc :ptr D3DMATRIX
    SetMatrixElement	proc :SINT, :SINT, :float
    SetMatrixElement2	proc :SINT, :SINT, :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionClip, "64AC3703-9D3F-45ec-A109-7CAC0E7A13A7")

.comdef IDCompositionClip : public IUnknown

    .ENDS

DEFINE_IIDX(IDCompositionRectangleClip, "9842AD7D-D9CF-4908-AED7-48B51DA5E7C2")

.comdef IDCompositionRectangleClip : public IDCompositionClip

    SetLeft		proc :float
    SetLeft2		proc :ptr IDCompositionAnimation
    SetTop		proc :float
    SetTop2		proc :ptr IDCompositionAnimation
    SetRight		proc :float
    SetRight2		proc :ptr IDCompositionAnimation
    SetBottom		proc :float
    SetBottom2		proc :ptr IDCompositionAnimation
    SetTopLeftRadiusX	proc :float
    SetTopLeftRadiusX2	proc :ptr IDCompositionAnimation
    SetTopLeftRadiusY	proc :float
    SetTopLeftRadiusY2	proc :ptr IDCompositionAnimation
    SetTopRightRadiusX	proc :float
    SetTopRightRadiusX2 proc :ptr IDCompositionAnimation
    SetTopRightRadiusY	proc :float
    SetTopRightRadiusY2 proc :ptr IDCompositionAnimation
    SetBottomLeftRadiusX proc :float
    SetBottomLeftRadiusX2 proc :ptr IDCompositionAnimation
    SetBottomLeftRadiusY proc :float
    SetBottomLeftRadiusY2 proc :ptr IDCompositionAnimation
    SetBottomRightRadiusX proc :float
    SetBottomRightRadiusX2 proc :ptr IDCompositionAnimation
    SetBottomRightRadiusY proc :float
    SetBottomRightRadiusY2 proc :ptr IDCompositionAnimation
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
    CreateTransform3DGroup proc :UINT, :ptr ptr IDCompositionTransform3D
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
    SetOffsetZ		proc :float
    SetOffsetZ		proc :ptr IDCompositionAnimation
    SetOpacity		proc :float
    SetOpacity		proc :ptr IDCompositionAnimation
    SetTransform	proc :ptr D2D_MATRIX_4X4_F
    SetTransform	proc :ptr IDCompositionTransform3D
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

    SetStandardDeviation proc :float
    SetStandardDeviation proc :ptr IDCompositionAnimation
    SetBorderMode	proc :D2D1_BORDER_MODE
    .ENDS

DEFINE_IIDX(IDCompositionBrightnessEffect, "6027496E-CB3A-49AB-934F-D798DA4F7DA6")

.comdef IDCompositionBrightnessEffect : public IDCompositionFilterEffect

    SetWhitePoint	proc :ptr D2D1_VECTOR_2F
    SetBlackPoint	proc :ptr D2D1_VECTOR_2F
    SetWhitePointX	proc :float
    SetWhitePointX	proc :ptr IDCompositionAnimation
    SetWhitePointY	proc :float
    SetWhitePointY	proc :ptr IDCompositionAnimation
    SetBlackPointX	proc :float
    SetBlackPointX	proc :ptr IDCompositionAnimation
    SetBlackPointY	proc :float
    SetBlackPointY	proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionColorMatrixEffect, "C1170A22-3CE2-4966-90D4-55408BFC84C4")

.comdef IDCompositionColorMatrixEffect : public IDCompositionFilterEffect

    SetMatrix		proc :ptr D2D1_MATRIX_5X4_F
    SetMatrixElement	proc :SINT, :SINT, :float
    SetMatrixElement	proc :SINT, SINT, :ptr IDCompositionAnimation
    SetAlphaMode	proc :D2D1_COLORMATRIX_ALPHA_MODE
    SetClampOutput	proc :BOOL
    .ENDS

DEFINE_IIDX(IDCompositionShadowEffect, "4AD18AC0-CFD2-4C2F-BB62-96E54FDB6879")

.comdef IDCompositionShadowEffect : public IDCompositionFilterEffect

    SetStandardDeviation proc :float
    SetStandardDeviation proc :ptr IDCompositionAnimation
    SetColor		proc :ptr D2D1_VECTOR_4F
    SetRed		proc :float
    SetRed		proc :ptr IDCompositionAnimation
    SetGreen		proc :float
    SetGreen		proc :ptr IDCompositionAnimation
    SetBlue		proc :float
    SetBlue		proc :ptr IDCompositionAnimation
    SetAlpha		proc :float
    SetAlpha		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionHueRotationEffect, "6DB9F920-0770-4781-B0C6-381912F9D167")

.comdef IDCompositionHueRotationEffect : public IDCompositionFilterEffect

    SetAngle		proc :float
    SetAngle		proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionSaturationEffect, "A08DEBDA-3258-4FA4-9F16-9174D3FE93B1")

.comdef IDCompositionSaturationEffect : public IDCompositionFilterEffect

    SetSaturation	proc :float
    SetSaturation	proc :ptr IDCompositionAnimation
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

    SetRedYIntercept	proc :float
    SetRedYIntercept	proc :ptr IDCompositionAnimation
    SetRedSlope		proc :float
    SetRedSlope		proc :ptr IDCompositionAnimation
    SetRedDisable	proc :BOOL
    SetGreenYIntercept	proc :float
    SetGreenYIntercept	proc :ptr IDCompositionAnimation
    SetGreenSlope	proc :float
    SetGreenSlope	proc :ptr IDCompositionAnimation
    SetGreenDisable	proc :BOOL
    SetBlueYIntercept	proc :float
    SetBlueYIntercept	proc :ptr IDCompositionAnimation
    SetBlueSlope	proc :float
    SetBlueSlope	proc :ptr IDCompositionAnimation
    SetBlueDisable	proc :BOOL
    SetAlphaYIntercept	proc :float
    SetAlphaYIntercept	proc :ptr IDCompositionAnimation
    SetAlphaSlope	proc :float
    SetAlphaSlope	proc :ptr IDCompositionAnimation
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
    SetRedTableValue	proc :UINT, :float
    SetRedTableValue	proc :UINT, :ptr IDCompositionAnimation
    SetGreenTableValue	proc :UINT, :float
    SetGreenTableValue	proc :UINT, :ptr IDCompositionAnimation
    SetBlueTableValue	proc :UINT, :float
    SetBlueTableValue	proc :UINT, :ptr IDCompositionAnimation
    SetAlphaTableValue	proc :UINT, :float
    SetAlphaTableValue	proc :UINT, :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionCompositeEffect, "576616C0-A231-494D-A38D-00FD5EC4DB46")

.comdef IDCompositionCompositeEffect : public IDCompositionFilterEffect

    SetMode		proc :D2D1_COMPOSITE_MODE
    .ENDS

DEFINE_IIDX(IDCompositionBlendEffect, "33ECDC0A-578A-4A11-9C14-0CB90517F9C5")

.comdef IDCompositionBlendEffect : public IDCompositionFilterEffect

    SetMode		proc :_In_ D2D1_BLEND_MODE mode,
    .ENDS

DEFINE_IIDX(IDCompositionArithmeticCompositeEffect, "3B67DFA8-E3DD-4E61-B640-46C2F3D739DC")

.comdef IDCompositionArithmeticCompositeEffect : public IDCompositionFilterEffect

    SetCoefficients	proc :ptr D2D1_VECTOR_4F
    SetClampOutput	proc :BOOL
    SetCoefficient1	proc :float
    SetCoefficient1	proc :ptr IDCompositionAnimation
    SetCoefficient2	proc :float
    SetCoefficient2	proc :ptr IDCompositionAnimation
    SetCoefficient3	proc :float
    SetCoefficient3	proc :ptr IDCompositionAnimation
    SetCoefficient4	proc :float
    SetCoefficient4	proc :ptr IDCompositionAnimation
    .ENDS

DEFINE_IIDX(IDCompositionAffineTransform2DEffect, "0B74B9E8-CDD6-492F-BBBC-5ED32157026D")

.comdef IDCompositionAffineTransform2DEffect : public IDCompositionFilterEffect

    SetInterpolationMode proc :D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE
    SetBorderMode	proc :D2D1_BORDER_MODE
    SetTransformMatrix	proc :ptr D2D1_MATRIX_3X2_F
    SetTransformMatrixElement proc :SINT, :SINT, :float
    SetTransformMatrixElement proc :SINT, :SINT, :ptr IDCompositionAnimation
    SetSharpness	proc :float
    SetSharpness	proc :ptr IDCompositionAnimation
    .ENDS

endif

endif
