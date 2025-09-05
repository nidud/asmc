ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Estartscreen_h__
define __windows2Eui2Estartscreen_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.UI.inc
include Windows.UI.Popups.inc

ifndef ____FIIterator_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CStartScreen__CSecondaryTile, "391f7579-a90e-5352-9d01-fda995d7912f")

.comdef __FIIterator_1_Windows__CUI__CStartScreen__CSecondaryTile : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CStartScreen__CSecondaryTile, "75651af0-014a-5593-bc48-836ba3d1d5d4")

.comdef __FIIterable_1_Windows__CUI__CStartScreen__CSecondaryTile : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements, "bbc6e16c-cace-5230-8804-2298375168ac")

.comdef __FIIterator_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements, "6ef7c354-f153-5b53-99c2-e045c78cce08")

.comdef __FIIterable_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile, "16f89727-d811-5051-9ab5-0cb86a0f0ac3")

.comdef __FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements, "1cd2cc9b-a41c-5dc7-9d95-4cef69a293f4")

.comdef __FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTileVisualElements : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile, "b9d6d973-a089-550a-83b7-f659ea0dea04")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile, "f72d55b2-b004-5e35-b5c4-22e87619b30a")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CUI__CStartScreen__CSecondaryTile : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CStartScreen__CSecondaryTile_Windows__CUI__CStartScreen__CVisualElementsRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CStartScreen__CSecondaryTile_Windows__CUI__CStartScreen__CVisualElementsRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CStartScreen__CSecondaryTile_Windows__CUI__CStartScreen__CVisualElementsRequestedEventArgs, "02d9f968-fa76-5d77-934b-665e7c3be7cf")

.comdef __FITypedEventHandler_2_Windows__CUI__CStartScreen__CSecondaryTile_Windows__CUI__CStartScreen__CVisualElementsRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace StartScreen

.enum TileOptions {
    TileOptions_None		= 0,
    TileOptions_ShowNameOnLogo	= 0x1,
    TileOptions_ShowNameOnWideLogo	= 0x2,
    TileOptions_CopyOnDeployment	= 0x4
    }

.enum TileSize {
    TileSize_Default		= 0,
    TileSize_Square30x30	= 1,
    TileSize_Square70x70	= 2,
    TileSize_Square150x150	= 3,
    TileSize_Wide310x150	= 4,
    TileSize_Square310x310	= 5
    }

.enum ForegroundText {
    ForegroundText_Dark		= 0,
    ForegroundText_Light	= 1
    }

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTile_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTile_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_ISecondaryTile <L"Windows.UI.StartScreen.ISecondaryTile">
DEFINE_IIDX(ISecondaryTile, "9E9E51E0-2BB5-4BC0-BB8D-42B23ABCC88D")

.comdef ISecondaryTile : public IInspectable

    put_TileId		proc :HSTRING
    get_TileId		proc :ptr
    put_Arguments	proc :HSTRING
    get_Arguments	proc :ptr
    put_ShortName	proc :HSTRING
    get_ShortName	proc :ptr
    put_DisplayName	proc :HSTRING
    get_DisplayName	proc :ptr
    put_Logo		proc :ptr
    get_Logo		proc :ptr
    put_SmallLogo	proc :ptr
    get_SmallLogo	proc :ptr
    put_WideLogo	proc :ptr
    get_WideLogo	proc :ptr
    put_LockScreenBadgeLogo proc :ptr
    get_LockScreenBadgeLogo proc :ptr
    put_LockScreenDisplayBadgeAndTileText proc :boolean
    get_LockScreenDisplayBadgeAndTileText proc :ptr
    put_TileOptions	proc :Windows::UI::StartScreen::TileOptions
    get_TileOptions	proc :ptr
    put_ForegroundText	proc :Windows::UI::StartScreen::ForegroundText
    get_ForegroundText	proc :ptr
    put_BackgroundColor proc :Windows::UI::Color
    get_BackgroundColor proc :ptr
    RequestCreateAsync	proc :ptr
    RequestCreateAsyncWithPoint proc :Windows::Foundation::Point, :ptr
    RequestCreateAsyncWithRect proc :Windows::Foundation::Rect, :ptr
    RequestCreateAsyncWithRectAndPlacement proc :Windows::Foundation::Rect, :Windows::UI::Popups::Placement, :ptr
    RequestDeleteAsync	proc :ptr
    RequestDeleteAsyncWithPoint proc :Windows::Foundation::Point, :ptr
    RequestDeleteAsyncWithRect proc :Windows::Foundation::Rect, :ptr
    RequestDeleteAsyncWithRectAndPlacement proc :Windows::Foundation::Rect, :Windows::UI::Popups::Placement, :ptr
    UpdateAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTile2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTile2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_ISecondaryTile2 <L"Windows.UI.StartScreen.ISecondaryTile2">
DEFINE_IIDX(ISecondaryTile2, "B2F6CC35-3250-4990-923C-294AB4B694DD")

.comdef ISecondaryTile2 : public IInspectable

    put_PhoneticName	proc :HSTRING
    get_PhoneticName	proc :ptr
    get_VisualElements	proc :ptr
    put_RoamingEnabled	proc :boolean
    get_RoamingEnabled	proc :ptr
    add_VisualElementsRequested proc :ptr, :ptr
    remove_VisualElementsRequested proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTileVisualElements_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTileVisualElements_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_ISecondaryTileVisualElements <L"Windows.UI.StartScreen.ISecondaryTileVisualElements">
DEFINE_IIDX(ISecondaryTileVisualElements, "1D8DF333-815E-413F-9F50-A81DA70A96B2")

.comdef ISecondaryTileVisualElements : public IInspectable

    put_Square30x30Logo proc :ptr
    get_Square30x30Logo proc :ptr
    put_Square70x70Logo proc :ptr
    get_Square70x70Logo proc :ptr
    put_Square150x150Logo proc :ptr
    get_Square150x150Logo proc :ptr
    put_Wide310x150Logo proc :ptr
    get_Wide310x150Logo proc :ptr
    put_Square310x310Logo proc :ptr
    get_Square310x310Logo proc :ptr
    put_ForegroundText	proc :Windows::UI::StartScreen::ForegroundText
    get_ForegroundText	proc :ptr
    put_BackgroundColor proc :Windows::UI::Color
    get_BackgroundColor proc :ptr
    put_ShowNameOnSquare150x150Logo proc :boolean
    get_ShowNameOnSquare150x150Logo proc :ptr
    put_ShowNameOnWide310x150Logo proc :boolean
    get_ShowNameOnWide310x150Logo proc :ptr
    put_ShowNameOnSquare310x310Logo proc :boolean
    get_ShowNameOnSquare310x310Logo proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTileFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTileFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_ISecondaryTileFactory <L"Windows.UI.StartScreen.ISecondaryTileFactory">
DEFINE_IIDX(ISecondaryTileFactory, "57F52CA0-51BC-4ABF-8EBF-627A0398B05A")

.comdef ISecondaryTileFactory : public IInspectable

    CreateTile		proc :HSTRING, :HSTRING, :HSTRING, :HSTRING, :Windows::UI::StartScreen::TileOptions, :ptr, :ptr
    CreateWideTile	proc :HSTRING, :HSTRING, :HSTRING, :HSTRING, :Windows::UI::StartScreen::TileOptions, :ptr, :ptr, :ptr
    CreateWithId	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTileFactory2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTileFactory2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_ISecondaryTileFactory2 <L"Windows.UI.StartScreen.ISecondaryTileFactory2">
DEFINE_IIDX(ISecondaryTileFactory2, "274B8A3B-522D-448E-9EB2-D0672AB345C8")

.comdef ISecondaryTileFactory2 : public IInspectable

    CreateMinimalTile	proc :HSTRING, :HSTRING, :HSTRING, :ptr, :Windows::UI::StartScreen::TileSize, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTileStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CISecondaryTileStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_ISecondaryTileStatics <L"Windows.UI.StartScreen.ISecondaryTileStatics">
DEFINE_IIDX(ISecondaryTileStatics, "99908DAE-D051-4676-87FE-9EC242D83C74")

.comdef ISecondaryTileStatics : public IInspectable

    Exists		proc :HSTRING, :ptr
    FindAllAsync	proc :ptr
    FindAllForApplicationAsync proc :HSTRING, :ptr
    FindAllForPackageAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CIVisualElementsRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CIVisualElementsRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_IVisualElementsRequestedEventArgs <L"Windows.UI.StartScreen.IVisualElementsRequestedEventArgs">
DEFINE_IIDX(IVisualElementsRequestedEventArgs, "7B6FC982-3A0D-4ECE-AF96-CD17E1B00B2D")

.comdef IVisualElementsRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CIVisualElementsRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CIVisualElementsRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_IVisualElementsRequest <L"Windows.UI.StartScreen.IVisualElementsRequest">
DEFINE_IIDX(IVisualElementsRequest, "C138333A-9308-4072-88CC-D068DB347C68")

.comdef IVisualElementsRequest : public IInspectable

    get_VisualElements	proc :ptr
    get_AlternateVisualElements proc :ptr
    get_Deadline	proc :ptr
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CStartScreen_CIVisualElementsRequestDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CStartScreen_CIVisualElementsRequestDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_StartScreen_IVisualElementsRequestDeferral <L"Windows.UI.StartScreen.IVisualElementsRequestDeferral">
DEFINE_IIDX(IVisualElementsRequestDeferral, "A1656EB0-0126-4357-8204-BD82BB2A046D")

.comdef IVisualElementsRequestDeferral : public IInspectable

    Complete		proc
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_StartScreen_SecondaryTileVisualElements_DEFINED
define RUNTIMECLASS_Windows_UI_StartScreen_SecondaryTileVisualElements_DEFINED
define RuntimeClass_Windows_UI_StartScreen_SecondaryTileVisualElements <L"Windows.UI.StartScreen.SecondaryTileVisualElements">
endif
ifndef RUNTIMECLASS_Windows_UI_StartScreen_SecondaryTile_DEFINED
define RUNTIMECLASS_Windows_UI_StartScreen_SecondaryTile_DEFINED
define RuntimeClass_Windows_UI_StartScreen_SecondaryTile <L"Windows.UI.StartScreen.SecondaryTile">
endif
ifndef RUNTIMECLASS_Windows_UI_StartScreen_VisualElementsRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_StartScreen_VisualElementsRequestedEventArgs_DEFINED
define RuntimeClass_Windows_UI_StartScreen_VisualElementsRequestedEventArgs <L"Windows.UI.StartScreen.VisualElementsRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_StartScreen_VisualElementsRequest_DEFINED
define RUNTIMECLASS_Windows_UI_StartScreen_VisualElementsRequest_DEFINED
define RuntimeClass_Windows_UI_StartScreen_VisualElementsRequest <L"Windows.UI.StartScreen.VisualElementsRequest">
endif
ifndef RUNTIMECLASS_Windows_UI_StartScreen_VisualElementsRequestDeferral_DEFINED
define RUNTIMECLASS_Windows_UI_StartScreen_VisualElementsRequestDeferral_DEFINED
define RuntimeClass_Windows_UI_StartScreen_VisualElementsRequestDeferral <L"Windows.UI.StartScreen.VisualElementsRequestDeferral">
endif

endif
