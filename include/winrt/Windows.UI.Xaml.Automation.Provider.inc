ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eui2Examl2Eautomation2Eprovider_h__
define __windows2Eui2Examl2Eautomation2Eprovider_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.UI.inc
include Windows.UI.Xaml.inc
include Windows.UI.Xaml.Automation.Text.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Automation
.namespace Provider

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IAnnotationProvider <L"Windows.UI.Xaml.Automation.Provider.IAnnotationProvider">
DEFINE_IIDX(IAnnotationProvider, "95BA1417-4437-451B-9461-050A49B59D06")

.comdef IAnnotationProvider : public IInspectable

    get_AnnotationTypeId proc :ptr
    get_AnnotationTypeName proc :ptr
    get_Author          proc :ptr
    get_DateTime        proc :ptr
    get_Target          proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIDockProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIDockProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IDockProvider <L"Windows.UI.Xaml.Automation.Provider.IDockProvider">
DEFINE_IIDX(IDockProvider, "48C243F8-78B1-44A0-AC5F-750757BCDE3C")

.comdef IDockProvider : public IInspectable

    get_DockPosition    proc :ptr
    SetDockPosition     proc :Windows::UI::Xaml::Automation::DockPosition
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIDragProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIDragProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IDragProvider <L"Windows.UI.Xaml.Automation.Provider.IDragProvider">
DEFINE_IIDX(IDragProvider, "2E7786A9-7FFC-4F57-B965-1EF1F373F546")

.comdef IDragProvider : public IInspectable

    get_IsGrabbed       proc :ptr
    get_DropEffect      proc :ptr
    get_DropEffects     proc :ptr, :ptr
    GetGrabbedItems     proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IDropTargetProvider <L"Windows.UI.Xaml.Automation.Provider.IDropTargetProvider">
DEFINE_IIDX(IDropTargetProvider, "7A245BDD-B458-4FE0-98C8-AAC89DF56D61")

.comdef IDropTargetProvider : public IInspectable

    get_DropEffect      proc :ptr
    get_DropEffects     proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IExpandCollapseProvider <L"Windows.UI.Xaml.Automation.Provider.IExpandCollapseProvider">
DEFINE_IIDX(IExpandCollapseProvider, "49AC8399-D626-4543-94B9-A6D9A9593AF6")

.comdef IExpandCollapseProvider : public IInspectable

    get_ExpandCollapseState proc :ptr
    Collapse            proc
    Expand              proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IGridItemProvider <L"Windows.UI.Xaml.Automation.Provider.IGridItemProvider">
DEFINE_IIDX(IGridItemProvider, "FFF3683C-7407-45BB-A936-DF3ED6D3837D")

.comdef IGridItemProvider : public IInspectable

    get_Column          proc :ptr
    get_ColumnSpan      proc :ptr
    get_ContainingGrid  proc :ptr
    get_Row             proc :ptr
    get_RowSpan         proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIGridProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIGridProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IGridProvider <L"Windows.UI.Xaml.Automation.Provider.IGridProvider">
DEFINE_IIDX(IGridProvider, "8B62B7A0-932C-4490-9A13-02FDB39A8F5B")

.comdef IGridProvider : public IInspectable

    get_ColumnCount     proc :ptr
    get_RowCount        proc :ptr
    GetItem             proc :INT32, :INT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IInvokeProvider <L"Windows.UI.Xaml.Automation.Provider.IInvokeProvider">
DEFINE_IIDX(IInvokeProvider, "F7D1A187-B13C-4540-B09E-6778E2DC9BA5")

.comdef IInvokeProvider : public IInspectable

    _Invoke             proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IItemContainerProvider <L"Windows.UI.Xaml.Automation.Provider.IItemContainerProvider">
DEFINE_IIDX(IItemContainerProvider, "EF5CD845-E1D4-40F4-BAD5-C7FAD44A703E")

.comdef IItemContainerProvider : public IInspectable

    FindItemByProperty  proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IMultipleViewProvider <L"Windows.UI.Xaml.Automation.Provider.IMultipleViewProvider">
DEFINE_IIDX(IMultipleViewProvider, "D014E196-0E50-4843-A5D2-C22897C8845A")

.comdef IMultipleViewProvider : public IInspectable

    get_CurrentView     proc :ptr
    GetSupportedViews   proc :ptr, :ptr
    GetViewName         proc :INT32, :ptr
    SetCurrentView      proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IObjectModelProvider <L"Windows.UI.Xaml.Automation.Provider.IObjectModelProvider">
DEFINE_IIDX(IObjectModelProvider, "C3CA36B9-0793-4ED0-BBF4-9FF4E0F98F80")

.comdef IObjectModelProvider : public IInspectable

    GetUnderlyingObjectModel proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IRangeValueProvider <L"Windows.UI.Xaml.Automation.Provider.IRangeValueProvider">
DEFINE_IIDX(IRangeValueProvider, "838A34A8-7D5F-4079-AF03-C3D015E93413")

.comdef IRangeValueProvider : public IInspectable

    get_IsReadOnly      proc :ptr
    get_LargeChange     proc :ptr
    get_Maximum         proc :ptr
    get_Minimum         proc :ptr
    get_SmallChange     proc :ptr
    get_Value           proc :ptr
    SetValue            proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IIRawElementProviderSimple <L"Windows.UI.Xaml.Automation.Provider.IIRawElementProviderSimple">
DEFINE_IIDX(IIRawElementProviderSimple, "EC752224-9B77-4720-BB21-4AC89FDB1AFD")

.comdef IIRawElementProviderSimple : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IScrollItemProvider <L"Windows.UI.Xaml.Automation.Provider.IScrollItemProvider">
DEFINE_IIDX(IScrollItemProvider, "9A3EC090-5D2C-4E42-9EE6-9D58DB100B55")

.comdef IScrollItemProvider : public IInspectable

    ScrollIntoView      proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IScrollProvider <L"Windows.UI.Xaml.Automation.Provider.IScrollProvider">
DEFINE_IIDX(IScrollProvider, "374BF581-7716-4BBC-82EB-D997006EA999")

.comdef IScrollProvider : public IInspectable

    get_HorizontallyScrollable proc :ptr
    get_HorizontalScrollPercent proc :ptr
    get_HorizontalViewSize proc :ptr
    get_VerticallyScrollable proc :ptr
    get_VerticalScrollPercent proc :ptr
    get_VerticalViewSize proc :ptr
    Scroll              proc :Windows::UI::Xaml::Automation::ScrollAmount, :Windows::UI::Xaml::Automation::ScrollAmount
    SetScrollPercent    proc :DOUBLE, :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ISelectionItemProvider <L"Windows.UI.Xaml.Automation.Provider.ISelectionItemProvider">
DEFINE_IIDX(ISelectionItemProvider, "6A4977C1-830D-42D2-BF62-042EBDDECC19")

.comdef ISelectionItemProvider : public IInspectable

    get_IsSelected      proc :ptr
    get_SelectionContainer proc :ptr
    AddToSelection      proc
    RemoveFromSelection proc
    Select              proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ISelectionProvider <L"Windows.UI.Xaml.Automation.Provider.ISelectionProvider">
DEFINE_IIDX(ISelectionProvider, "1F018FCA-B944-4395-8DE1-88F674AF51D3")

.comdef ISelectionProvider : public IInspectable

    get_CanSelectMultiple proc :ptr
    get_IsSelectionRequired proc :ptr
    GetSelection        proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ISpreadsheetItemProvider <L"Windows.UI.Xaml.Automation.Provider.ISpreadsheetItemProvider">
DEFINE_IIDX(ISpreadsheetItemProvider, "EBDE8F92-6015-4826-B719-47521A81C67E")

.comdef ISpreadsheetItemProvider : public IInspectable

    get_Formula         proc :ptr
    GetAnnotationObjects proc :ptr, :ptr
    GetAnnotationTypes  proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ISpreadsheetProvider <L"Windows.UI.Xaml.Automation.Provider.ISpreadsheetProvider">
DEFINE_IIDX(ISpreadsheetProvider, "15359093-BD99-4CFD-9F07-3B14B315E23D")

.comdef ISpreadsheetProvider : public IInspectable

    GetItemByName       proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IStylesProvider <L"Windows.UI.Xaml.Automation.Provider.IStylesProvider">
DEFINE_IIDX(IStylesProvider, "1A5B7A17-7C01-4BEC-9CD4-2DFA7DC246CD")

.comdef IStylesProvider : public IInspectable

    get_ExtendedProperties proc :ptr
    get_FillColor       proc :ptr
    get_FillPatternColor proc :ptr
    get_FillPatternStyle proc :ptr
    get_Shape           proc :ptr
    get_StyleId         proc :ptr
    get_StyleName       proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ISynchronizedInputProvider <L"Windows.UI.Xaml.Automation.Provider.ISynchronizedInputProvider">
DEFINE_IIDX(ISynchronizedInputProvider, "3D60CECB-DA54-4AA3-B915-E3244427D4AC")

.comdef ISynchronizedInputProvider : public IInspectable

    Cancel              proc
    StartListening      proc :Windows::UI::Xaml::Automation::SynchronizedInputType
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITableItemProvider <L"Windows.UI.Xaml.Automation.Provider.ITableItemProvider">
DEFINE_IIDX(ITableItemProvider, "3B2C49CD-1DE2-4EE2-A3E1-FB553559D15D")

.comdef ITableItemProvider : public IInspectable

    GetColumnHeaderItems proc :ptr, :ptr
    GetRowHeaderItems   proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITableProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITableProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITableProvider <L"Windows.UI.Xaml.Automation.Provider.ITableProvider">
DEFINE_IIDX(ITableProvider, "7A8ED399-6824-4595-BAB3-464BC9A04417")

.comdef ITableProvider : public IInspectable

    get_RowOrColumnMajor proc :ptr
    GetColumnHeaders    proc :ptr, :ptr
    GetRowHeaders       proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITextChildProvider <L"Windows.UI.Xaml.Automation.Provider.ITextChildProvider">
DEFINE_IIDX(ITextChildProvider, "1133C336-A89B-4130-9BE6-55E33334F557")

.comdef ITextChildProvider : public IInspectable

    get_TextContainer   proc :ptr
    get_TextRange       proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITextRangeProvider <L"Windows.UI.Xaml.Automation.Provider.ITextRangeProvider">
DEFINE_IIDX(ITextRangeProvider, "0274688D-06E9-4F66-9446-28A5BE98FBD0")

.comdef ITextRangeProvider : public IInspectable

    Clone               proc :ptr
    Compare             proc :ptr, :ptr
    CompareEndpoints    proc :Windows::UI::Xaml::Automation::Text::TextPatternRangeEndpoint, :ptr, :Windows::UI::Xaml::Automation::Text::TextPatternRangeEndpoint, :ptr
    ExpandToEnclosingUnit proc :Windows::UI::Xaml::Automation::Text::TextUnit
    FindAttribute       proc :INT32, :ptr, :boolean, :ptr
    FindText            proc :HSTRING, :boolean, :boolean, :ptr
    GetAttributeValue   proc :INT32, :ptr
    GetBoundingRectangles proc :ptr, :ptr
    GetEnclosingElement proc :ptr
    GetText             proc :INT32, :ptr
    Move                proc :Windows::UI::Xaml::Automation::Text::TextUnit, :INT32, :ptr
    MoveEndpointByUnit  proc :Windows::UI::Xaml::Automation::Text::TextPatternRangeEndpoint, :Windows::UI::Xaml::Automation::Text::TextUnit, :INT32, :ptr
    MoveEndpointByRange proc :Windows::UI::Xaml::Automation::Text::TextPatternRangeEndpoint, :ptr, :Windows::UI::Xaml::Automation::Text::TextPatternRangeEndpoint
    Select              proc
    AddToSelection      proc
    RemoveFromSelection proc
    ScrollIntoView      proc :boolean
    GetChildren         proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITextProvider <L"Windows.UI.Xaml.Automation.Provider.ITextProvider">
DEFINE_IIDX(ITextProvider, "DB5BBC9F-4807-4F2A-8678-1B13F3C60E22")

.comdef ITextProvider : public IInspectable

    get_DocumentRange   proc :ptr
    get_SupportedTextSelection proc :ptr
    GetSelection        proc :ptr, :ptr
    GetVisibleRanges    proc :ptr, :ptr
    RangeFromChild      proc :ptr, :ptr
    RangeFromPoint      proc :Windows::Foundation::Point, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextProvider2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextProvider2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITextProvider2 <L"Windows.UI.Xaml.Automation.Provider.ITextProvider2">
DEFINE_IIDX(ITextProvider2, "DF1D48BC-0487-4E7F-9D5E-F09E77E41246")

.comdef ITextProvider2 : public IInspectable

    RangeFromAnnotation proc :ptr, :ptr
    GetCaretRange       proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITextRangeProvider2 <L"Windows.UI.Xaml.Automation.Provider.ITextRangeProvider2">
DEFINE_IIDX(ITextRangeProvider2, "D3BE3DFB-9F54-4642-A7A5-5C18D5EE2A3F")

.comdef ITextRangeProvider2 : public IInspectable

    ShowContextMenu     proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IToggleProvider <L"Windows.UI.Xaml.Automation.Provider.IToggleProvider">
DEFINE_IIDX(IToggleProvider, "93B88290-656F-44F7-AEAF-78B8F944D062")

.comdef IToggleProvider : public IInspectable

    get_ToggleState     proc :ptr
    Toggle              proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITransformProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITransformProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITransformProvider <L"Windows.UI.Xaml.Automation.Provider.ITransformProvider">
DEFINE_IIDX(ITransformProvider, "79670FDD-F6A9-4A65-AF17-861DB799A2DA")

.comdef ITransformProvider : public IInspectable

    get_CanMove         proc :ptr
    get_CanResize       proc :ptr
    get_CanRotate       proc :ptr
    Move                proc :DOUBLE, :DOUBLE
    Resize              proc :DOUBLE, :DOUBLE
    Rotate              proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_ITransformProvider2 <L"Windows.UI.Xaml.Automation.Provider.ITransformProvider2">
DEFINE_IIDX(ITransformProvider2, "A8B11756-A39F-4E97-8C7D-C1EA8DD633C5")

.comdef ITransformProvider2 : public IInspectable

    get_CanZoom         proc :ptr
    get_ZoomLevel       proc :ptr
    get_MaxZoom         proc :ptr
    get_MinZoom         proc :ptr
    Zoom                proc :DOUBLE
    ZoomByUnit          proc :Windows::UI::Xaml::Automation::ZoomUnit
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIValueProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIValueProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IValueProvider <L"Windows.UI.Xaml.Automation.Provider.IValueProvider">
DEFINE_IIDX(IValueProvider, "2086B7A7-AC0E-47D1-AB9B-2A64292AFDF8")

.comdef IValueProvider : public IInspectable

    get_IsReadOnly      proc :ptr
    get_Value           proc :ptr
    SetValue            proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IVirtualizedItemProvider <L"Windows.UI.Xaml.Automation.Provider.IVirtualizedItemProvider">
DEFINE_IIDX(IVirtualizedItemProvider, "17D4A04B-D658-48E0-A574-5A516C58DFA7")

.comdef IVirtualizedItemProvider : public IInspectable

    Realize             proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Provider_IWindowProvider <L"Windows.UI.Xaml.Automation.Provider.IWindowProvider">
DEFINE_IIDX(IWindowProvider, "1BAA8B3D-38CF-415A-85D3-20E43A0EC1B1")

.comdef IWindowProvider : public IInspectable

    get_IsModal         proc :ptr
    get_IsTopmost       proc :ptr
    get_Maximizable     proc :ptr
    get_Minimizable     proc :ptr
    get_InteractionState proc :ptr
    get_VisualState     proc :ptr
    Close               proc
    SetVisualState      proc :Windows::UI::Xaml::Automation::WindowVisualState
    WaitForInputIdle    proc :INT32, :ptr
   .ends

endif

.endn
.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Provider_IRawElementProviderSimple_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Provider_IRawElementProviderSimple_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Provider_IRawElementProviderSimple <L"Windows.UI.Xaml.Automation.Provider.IRawElementProviderSimple">
endif

endif
