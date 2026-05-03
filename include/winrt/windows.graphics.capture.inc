ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Egraphics2Ecapture_h__
define __windows2Egraphics2Ecapture_h__
ifndef __windows2Egraphics2Ecapture_p_h__
define __windows2Egraphics2Ecapture_p_h__

ifndef SPECIFIC_API_CONTRACT_DEFINITIONS
ifndef WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION
define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
endif
ifndef WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION
define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x130000
endif
ifndef WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION
define WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION 0x70000
endif
endif
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include windowscontracts.inc
include Windows.Graphics.inc
include Windows.Graphics.DirectX.inc
include Windows.Graphics.DirectX.Direct3D11.inc
include Windows.Security.Authorization.AppCapabilityAccess.inc
include Windows.System.inc
include Windows.UI.inc
include Windows.UI.Composition.inc

.namespace Windows
.namespace Graphics
.namespace Capture

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
.enum GraphicsCaptureAccessKind {
    GraphicsCaptureAccessKind_Borderless = 0,
    GraphicsCaptureAccessKind_Programmatic = 1,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x130000
.enum GraphicsCaptureDirtyRegionMode {
    GraphicsCaptureDirtyRegionMode_ReportOnly = 0,
    GraphicsCaptureDirtyRegionMode_ReportAndRender = 1,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IDirect3D11CaptureFrame <"Windows.Graphics.Capture.IDirect3D11CaptureFrame">
DEFINE_IIDX(IDirect3D11CaptureFrame, "fa50c623-38da-4b32-acf3-fa9734ad800e")

.comdef IDirect3D11CaptureFrame : public IInspectable
    get_Surface         proc :ptr ptr
    get_SystemRelativeTime proc :ptr
    get_ContentSize     proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x130000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFrame2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFrame2_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IDirect3D11CaptureFrame2 <"Windows.Graphics.Capture.IDirect3D11CaptureFrame2">
DEFINE_IIDX(IDirect3D11CaptureFrame2, "37869cfa-2b48-5ebf-9afb-dffd805defdb")

.comdef IDirect3D11CaptureFrame2 : public IInspectable
    get_DirtyRegions    proc :ptr ptr
    get_DirtyRegionMode proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFramePool_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFramePool_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IDirect3D11CaptureFramePool <"Windows.Graphics.Capture.IDirect3D11CaptureFramePool">
DEFINE_IIDX(IDirect3D11CaptureFramePool, "24eb6d22-1975-422e-82e7-780dbd8ddf24")

.comdef IDirect3D11CaptureFramePool : public IInspectable
    Recreate            proc :ptr, :Windows::Graphics::DirectX::DirectXPixelFormat, :INT32, :Windows::Graphics::SizeInt32
    TryGetNextFrame     proc :ptr ptr
    add_FrameArrived    proc :ptr, :ptr
    remove_FrameArrived proc :EventRegistrationToken
    CreateCaptureSession proc :ptr, :ptr ptr
    get_DispatcherQueue proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFramePoolStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFramePoolStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IDirect3D11CaptureFramePoolStatics <"Windows.Graphics.Capture.IDirect3D11CaptureFramePoolStatics">
DEFINE_IIDX(IDirect3D11CaptureFramePoolStatics, "7784056a-67aa-4d53-ae54-1088d5a8ca21")

.comdef IDirect3D11CaptureFramePoolStatics : public IInspectable
    Create              proc :ptr, :Windows::Graphics::DirectX::DirectXPixelFormat, :INT32, :Windows::Graphics::SizeInt32, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFramePoolStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIDirect3D11CaptureFramePoolStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IDirect3D11CaptureFramePoolStatics2 <"Windows.Graphics.Capture.IDirect3D11CaptureFramePoolStatics2">
DEFINE_IIDX(IDirect3D11CaptureFramePoolStatics2, "589b103f-6bbc-5df5-a991-02e28b3b66d5")

.comdef IDirect3D11CaptureFramePoolStatics2 : public IInspectable
    CreateFreeThreaded  proc :ptr, :Windows::Graphics::DirectX::DirectXPixelFormat, :INT32, :Windows::Graphics::SizeInt32, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureAccessStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureAccessStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureAccessStatics <"Windows.Graphics.Capture.IGraphicsCaptureAccessStatics">
DEFINE_IIDX(IGraphicsCaptureAccessStatics, "743ed370-06ec-5040-a58a-901f0f757095")

.comdef IGraphicsCaptureAccessStatics : public IInspectable
    RequestAccessAsync  proc :Windows::Graphics::Capture::GraphicsCaptureAccessKind, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureItem_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureItem <"Windows.Graphics.Capture.IGraphicsCaptureItem">
DEFINE_IIDX(IGraphicsCaptureItem, "79c3f95b-31f7-4ec2-a464-632ef5d30760")

.comdef IGraphicsCaptureItem : public IInspectable
    get_DisplayName     proc :ptr
    get_Size            proc :ptr
    add_Closed          proc :ptr, :ptr
    remove_Closed       proc :EventRegistrationToken
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureItemStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureItemStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureItemStatics <"Windows.Graphics.Capture.IGraphicsCaptureItemStatics">
DEFINE_IIDX(IGraphicsCaptureItemStatics, "a87ebea5-457c-5788-ab47-0cf1d3637e74")

.comdef IGraphicsCaptureItemStatics : public IInspectable
    CreateFromVisual    proc :ptr, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureItemStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureItemStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureItemStatics2 <"Windows.Graphics.Capture.IGraphicsCaptureItemStatics2">
DEFINE_IIDX(IGraphicsCaptureItemStatics2, "3b92acc9-e584-5862-bf5c-9c316c6d2dbb")

.comdef IGraphicsCaptureItemStatics2 : public IInspectable
    TryCreateFromWindowId proc :Windows::UI::WindowId, :ptr ptr
    TryCreateFromDisplayId proc :Windows::Graphics::DisplayId, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCapturePicker_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCapturePicker_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCapturePicker <"Windows.Graphics.Capture.IGraphicsCapturePicker">
DEFINE_IIDX(IGraphicsCapturePicker, "5a1711b3-ad79-4b4a-9336-1318fdde3539")

.comdef IGraphicsCapturePicker : public IInspectable
    PickSingleItemAsync proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureSession <"Windows.Graphics.Capture.IGraphicsCaptureSession">
DEFINE_IIDX(IGraphicsCaptureSession, "814e42a9-f70f-4ad7-939b-fddcc6eb880d")

.comdef IGraphicsCaptureSession : public IInspectable
    StartCapture        proc
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xa0000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession2_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureSession2 <"Windows.Graphics.Capture.IGraphicsCaptureSession2">
DEFINE_IIDX(IGraphicsCaptureSession2, "2c39ae40-7d2e-5044-804e-8b6799d4cf9e")

.comdef IGraphicsCaptureSession2 : public IInspectable
    get_IsCursorCaptureEnabled proc :ptr
    put_IsCursorCaptureEnabled proc :boolean
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession3_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureSession3 <"Windows.Graphics.Capture.IGraphicsCaptureSession3">
DEFINE_IIDX(IGraphicsCaptureSession3, "f2cdd966-22ae-5ea1-9596-3a289344c3be")

.comdef IGraphicsCaptureSession3 : public IInspectable
    get_IsBorderRequired proc :ptr
    put_IsBorderRequired proc :boolean
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x130000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession4_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureSession4 <"Windows.Graphics.Capture.IGraphicsCaptureSession4">
DEFINE_IIDX(IGraphicsCaptureSession4, "ae99813c-c257-5759-8ed0-668c9b557ed4")

.comdef IGraphicsCaptureSession4 : public IInspectable
    get_DirtyRegionMode proc :ptr
    put_DirtyRegionMode proc :Windows::Graphics::Capture::GraphicsCaptureDirtyRegionMode
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x130000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession5_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession5_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureSession5 <"Windows.Graphics.Capture.IGraphicsCaptureSession5">
DEFINE_IIDX(IGraphicsCaptureSession5, "67c0ea62-1f85-5061-925a-239be0ac09cb")

.comdef IGraphicsCaptureSession5 : public IInspectable
    get_MinUpdateInterval proc :ptr
    put_MinUpdateInterval proc :Windows::Foundation::TimeSpan
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x130000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession6_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSession6_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureSession6 <"Windows.Graphics.Capture.IGraphicsCaptureSession6">
DEFINE_IIDX(IGraphicsCaptureSession6, "d7419236-be20-5e9f-bcd6-c4e98fd6afdc")

.comdef IGraphicsCaptureSession6 : public IInspectable
    get_IncludeSecondaryWindows proc :ptr
    put_IncludeSecondaryWindows proc :boolean
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSessionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CCapture_CIGraphicsCaptureSessionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Capture_IGraphicsCaptureSessionStatics <"Windows.Graphics.Capture.IGraphicsCaptureSessionStatics">
DEFINE_IIDX(IGraphicsCaptureSessionStatics, "2224a540-5974-49aa-b232-0882536f4cb5")

.comdef IGraphicsCaptureSessionStatics : public IInspectable
    IsSupported         proc :ptr
   .ends
endif
endif

.endn
.endn
.endn

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_Graphics_Capture_Direct3D11CaptureFrame_DEFINED
define RUNTIMECLASS_Windows_Graphics_Capture_Direct3D11CaptureFrame_DEFINED
define RuntimeClass_Windows_Graphics_Capture_Direct3D11CaptureFrame <"Windows.Graphics.Capture.Direct3D11CaptureFrame">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_Graphics_Capture_Direct3D11CaptureFramePool_DEFINED
define RUNTIMECLASS_Windows_Graphics_Capture_Direct3D11CaptureFramePool_DEFINED
define RuntimeClass_Windows_Graphics_Capture_Direct3D11CaptureFramePool <"Windows.Graphics.Capture.Direct3D11CaptureFramePool">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_Graphics_Capture_GraphicsCaptureAccess_DEFINED
define RUNTIMECLASS_Windows_Graphics_Capture_GraphicsCaptureAccess_DEFINED
define RuntimeClass_Windows_Graphics_Capture_GraphicsCaptureAccess <"Windows.Graphics.Capture.GraphicsCaptureAccess">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_Graphics_Capture_GraphicsCaptureItem_DEFINED
define RUNTIMECLASS_Windows_Graphics_Capture_GraphicsCaptureItem_DEFINED
define RuntimeClass_Windows_Graphics_Capture_GraphicsCaptureItem <"Windows.Graphics.Capture.GraphicsCaptureItem">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_Graphics_Capture_GraphicsCapturePicker_DEFINED
define RUNTIMECLASS_Windows_Graphics_Capture_GraphicsCapturePicker_DEFINED
define RuntimeClass_Windows_Graphics_Capture_GraphicsCapturePicker <"Windows.Graphics.Capture.GraphicsCapturePicker">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_Graphics_Capture_GraphicsCaptureSession_DEFINED
define RUNTIMECLASS_Windows_Graphics_Capture_GraphicsCaptureSession_DEFINED
define RuntimeClass_Windows_Graphics_Capture_GraphicsCaptureSession <"Windows.Graphics.Capture.GraphicsCaptureSession">
endif
endif

endif

endif
