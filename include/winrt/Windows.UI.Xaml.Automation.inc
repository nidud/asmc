ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Eautomation_h__
define __windows2Eui2Examl2Eautomation_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Automation

.enum AnnotationType {
    AnnotationType_Unknown  = 60000,
    AnnotationType_SpellingError    = 60001,
    AnnotationType_GrammarError = 60002,
    AnnotationType_Comment  = 60003,
    AnnotationType_FormulaError = 60004,
    AnnotationType_TrackChanges = 60005,
    AnnotationType_Header   = 60006,
    AnnotationType_Footer   = 60007,
    AnnotationType_Highlighted  = 60008
    }

.enum DockPosition {
    DockPosition_Top    = 0,
    DockPosition_Left   = 1,
    DockPosition_Bottom = 2,
    DockPosition_Right  = 3,
    DockPosition_Fill   = 4,
    DockPosition_None   = 5
    }

.enum ExpandCollapseState {
    ExpandCollapseState_Collapsed   = 0,
    ExpandCollapseState_Expanded    = 1,
    ExpandCollapseState_PartiallyExpanded   = 2,
    ExpandCollapseState_LeafNode    = 3
    }

.enum RowOrColumnMajor {
    RowOrColumnMajor_RowMajor   = 0,
    RowOrColumnMajor_ColumnMajor    = 1,
    RowOrColumnMajor_Indeterminate  = 2
    }

.enum ScrollAmount {
    ScrollAmount_LargeDecrement = 0,
    ScrollAmount_SmallDecrement = 1,
    ScrollAmount_NoAmount   = 2,
    ScrollAmount_LargeIncrement = 3,
    ScrollAmount_SmallIncrement = 4
    }

.enum SupportedTextSelection {
    SupportedTextSelection_None = 0,
    SupportedTextSelection_Single   = 1,
    SupportedTextSelection_Multiple = 2
    }

.enum SynchronizedInputType {
    SynchronizedInputType_KeyUp = 1,
    SynchronizedInputType_KeyDown   = 2,
    SynchronizedInputType_LeftMouseUp   = 4,
    SynchronizedInputType_LeftMouseDown = 8,
    SynchronizedInputType_RightMouseUp  = 16,
    SynchronizedInputType_RightMouseDown    = 32
    }

.enum ToggleState {
    ToggleState_Off = 0,
    ToggleState_On  = 1,
    ToggleState_Indeterminate   = 2
    }

.enum WindowInteractionState {
    WindowInteractionState_Running  = 0,
    WindowInteractionState_Closing  = 1,
    WindowInteractionState_ReadyForUserInteraction  = 2,
    WindowInteractionState_BlockedByModalWindow = 3,
    WindowInteractionState_NotResponding    = 4
    }

.enum WindowVisualState {
    WindowVisualState_Normal    = 0,
    WindowVisualState_Maximized = 1,
    WindowVisualState_Minimized = 2
    }

.enum ZoomUnit {
    ZoomUnit_NoAmount   = 0,
    ZoomUnit_LargeDecrement = 1,
    ZoomUnit_SmallDecrement = 2,
    ZoomUnit_LargeIncrement = 3,
    ZoomUnit_SmallIncrement = 4
    }

.endn
.endn
.endn
.endn

include Windows.UI.Xaml.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Automation


ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationProperty_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationProperty_INTERFACE_DEFINED__
DEFINE_IIDX(IAutomationProperty, "B627195B-3227-4E16-9534-DDECE30DDB46")

.comdef IAutomationProperty : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IAutomationProperties <L"Windows.UI.Xaml.Automation.IAutomationProperties">
DEFINE_IIDX(IAutomationProperties, "68D7232C-E622-48E9-AF0B-1FFA33CC5CBA")

.comdef IAutomationProperties : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationPropertiesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationPropertiesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IAutomationPropertiesStatics <L"Windows.UI.Xaml.Automation.IAutomationPropertiesStatics">
DEFINE_IIDX(IAutomationPropertiesStatics, "B618FD7B-32D0-4970-9C42-7C039AC7BE78")

.comdef IAutomationPropertiesStatics : public IInspectable

    get_AcceleratorKeyProperty proc :ptr
    GetAcceleratorKey   proc :ptr, :ptr
    SetAcceleratorKey   proc :ptr, :HSTRING
    get_AccessKeyProperty proc :ptr
    GetAccessKey        proc :ptr, :ptr
    SetAccessKey        proc :ptr, :HSTRING
    get_AutomationIdProperty proc :ptr
    GetAutomationId     proc :ptr, :ptr
    SetAutomationId     proc :ptr, :HSTRING
    get_HelpTextProperty proc :ptr
    GetHelpText         proc :ptr, :ptr
    SetHelpText         proc :ptr, :HSTRING
    get_IsRequiredForFormProperty proc :ptr
    GetIsRequiredForForm proc :ptr, :ptr
    SetIsRequiredForForm proc :ptr, :boolean
    get_ItemStatusProperty proc :ptr
    GetItemStatus       proc :ptr, :ptr
    SetItemStatus       proc :ptr, :HSTRING
    get_ItemTypeProperty proc :ptr
    GetItemType         proc :ptr, :ptr
    SetItemType         proc :ptr, :HSTRING
    get_LabeledByProperty proc :ptr
    GetLabeledBy        proc :ptr, :ptr
    SetLabeledBy        proc :ptr, :ptr
    get_NameProperty    proc :ptr
    GetName             proc :ptr, :ptr
    SetName             proc :ptr, :HSTRING
    get_LiveSettingProperty proc :ptr
    GetLiveSetting      proc :ptr, :ptr
    SetLiveSetting      proc :ptr, :Windows::UI::Xaml::Automation::Peers::AutomationLiveSetting
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationPropertiesStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationPropertiesStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IAutomationPropertiesStatics2 <L"Windows.UI.Xaml.Automation.IAutomationPropertiesStatics2">
DEFINE_IIDX(IAutomationPropertiesStatics2, "3976547F-7089-4801-8F1D-AAB78090D1A0")

.comdef IAutomationPropertiesStatics2 : public IInspectable

    get_AccessibilityViewProperty proc :ptr
    GetAccessibilityView proc :ptr, :ptr
    SetAccessibilityView proc :ptr, :Windows::UI::Xaml::Automation::Peers::AccessibilityView
    get_ControlledPeersProperty proc :ptr
    GetControlledPeers  proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationElementIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationElementIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IAutomationElementIdentifiersStatics <L"Windows.UI.Xaml.Automation.IAutomationElementIdentifiersStatics">
DEFINE_IIDX(IAutomationElementIdentifiersStatics, "4549399F-8340-4D67-B9BF-8C2AC6A0773A")

.comdef IAutomationElementIdentifiersStatics : public IInspectable

    get_AcceleratorKeyProperty proc :ptr
    get_AccessKeyProperty proc :ptr
    get_AutomationIdProperty proc :ptr
    get_BoundingRectangleProperty proc :ptr
    get_ClassNameProperty proc :ptr
    get_ClickablePointProperty proc :ptr
    get_ControlTypeProperty proc :ptr
    get_HasKeyboardFocusProperty proc :ptr
    get_HelpTextProperty proc :ptr
    get_IsContentElementProperty proc :ptr
    get_IsControlElementProperty proc :ptr
    get_IsEnabledProperty proc :ptr
    get_IsKeyboardFocusableProperty proc :ptr
    get_IsOffscreenProperty proc :ptr
    get_IsPasswordProperty proc :ptr
    get_IsRequiredForFormProperty proc :ptr
    get_ItemStatusProperty proc :ptr
    get_ItemTypeProperty proc :ptr
    get_LabeledByProperty proc :ptr
    get_LocalizedControlTypeProperty proc :ptr
    get_NameProperty    proc :ptr
    get_OrientationProperty proc :ptr
    get_LiveSettingProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationElementIdentifiersStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationElementIdentifiersStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IAutomationElementIdentifiersStatics2 <L"Windows.UI.Xaml.Automation.IAutomationElementIdentifiersStatics2">
DEFINE_IIDX(IAutomationElementIdentifiersStatics2, "B5CBB1E2-D55F-46A9-9EDA-1A4742515DC3")

.comdef IAutomationElementIdentifiersStatics2 : public IInspectable

    get_ControlledPeersProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationElementIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAutomationElementIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IAutomationElementIdentifiers <L"Windows.UI.Xaml.Automation.IAutomationElementIdentifiers">
DEFINE_IIDX(IAutomationElementIdentifiers, "E68A63CF-4345-4E2D-8A6A-49CCE1FA2DCC")

.comdef IAutomationElementIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAnnotationPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAnnotationPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IAnnotationPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IAnnotationPatternIdentifiersStatics">
DEFINE_IIDX(IAnnotationPatternIdentifiersStatics, "E0E3A35D-D167-46DC-95AB-330AF61AEBB5")

.comdef IAnnotationPatternIdentifiersStatics : public IInspectable

    get_AnnotationTypeIdProperty proc :ptr
    get_AnnotationTypeNameProperty proc :ptr
    get_AuthorProperty  proc :ptr
    get_DateTimeProperty proc :ptr
    get_TargetProperty  proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAnnotationPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIAnnotationPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IAnnotationPatternIdentifiers <L"Windows.UI.Xaml.Automation.IAnnotationPatternIdentifiers">
DEFINE_IIDX(IAnnotationPatternIdentifiers, "D475A0C1-48B2-4E40-A6CF-3DC4B638C0DE")

.comdef IAnnotationPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDockPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDockPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IDockPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IDockPatternIdentifiersStatics">
DEFINE_IIDX(IDockPatternIdentifiersStatics, "2B87245C-ED80-4FE5-8EB4-708A39C841E5")

.comdef IDockPatternIdentifiersStatics : public IInspectable

    get_DockPositionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDockPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDockPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IDockPatternIdentifiers <L"Windows.UI.Xaml.Automation.IDockPatternIdentifiers">
DEFINE_IIDX(IDockPatternIdentifiers, "CCD7F4E6-E4F9-47FF-BDE7-378B11F78E09")

.comdef IDockPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDragPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDragPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IDragPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IDragPatternIdentifiersStatics">
DEFINE_IIDX(IDragPatternIdentifiersStatics, "2A05379D-1755-4082-9D90-46F1411D7986")

.comdef IDragPatternIdentifiersStatics : public IInspectable

    get_DropEffectProperty proc :ptr
    get_DropEffectsProperty proc :ptr
    get_GrabbedItemsProperty proc :ptr
    get_IsGrabbedProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDragPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDragPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IDragPatternIdentifiers <L"Windows.UI.Xaml.Automation.IDragPatternIdentifiers">
DEFINE_IIDX(IDragPatternIdentifiers, "6266E985-4D07-4E80-82EB-8F96690A1A0C")

.comdef IDragPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDropTargetPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDropTargetPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IDropTargetPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IDropTargetPatternIdentifiersStatics">
DEFINE_IIDX(IDropTargetPatternIdentifiersStatics, "1B693304-89FB-4B0A-9452-CA2C66AAF9F3")

.comdef IDropTargetPatternIdentifiersStatics : public IInspectable

    get_DropTargetEffectProperty proc :ptr
    get_DropTargetEffectsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDropTargetPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIDropTargetPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IDropTargetPatternIdentifiers <L"Windows.UI.Xaml.Automation.IDropTargetPatternIdentifiers">
DEFINE_IIDX(IDropTargetPatternIdentifiers, "11865133-A6FE-4634-BD18-0EF612B7B208")

.comdef IDropTargetPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIExpandCollapsePatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIExpandCollapsePatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IExpandCollapsePatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IExpandCollapsePatternIdentifiersStatics">
DEFINE_IIDX(IExpandCollapsePatternIdentifiersStatics, "D7816FD4-6EE0-4F38-8E14-56EF21ADACFD")

.comdef IExpandCollapsePatternIdentifiersStatics : public IInspectable

    get_ExpandCollapseStateProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIExpandCollapsePatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIExpandCollapsePatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IExpandCollapsePatternIdentifiers <L"Windows.UI.Xaml.Automation.IExpandCollapsePatternIdentifiers">
DEFINE_IIDX(IExpandCollapsePatternIdentifiers, "B006BAC0-751B-4D55-92CB-613EC1BDF5D0")

.comdef IExpandCollapsePatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIGridItemPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIGridItemPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IGridItemPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IGridItemPatternIdentifiersStatics">
DEFINE_IIDX(IGridItemPatternIdentifiersStatics, "217D2402-5E46-4D61-8794-B8EE8E774714")

.comdef IGridItemPatternIdentifiersStatics : public IInspectable

    get_ColumnProperty  proc :ptr
    get_ColumnSpanProperty proc :ptr
    get_ContainingGridProperty proc :ptr
    get_RowProperty     proc :ptr
    get_RowSpanProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIGridItemPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIGridItemPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IGridItemPatternIdentifiers <L"Windows.UI.Xaml.Automation.IGridItemPatternIdentifiers">
DEFINE_IIDX(IGridItemPatternIdentifiers, "757744F1-3285-4FB1-803B-2545BD431599")

.comdef IGridItemPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIGridPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIGridPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IGridPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IGridPatternIdentifiersStatics">
DEFINE_IIDX(IGridPatternIdentifiersStatics, "7BC452F3-A181-4137-8DE9-1F9B1A8320ED")

.comdef IGridPatternIdentifiersStatics : public IInspectable

    get_ColumnCountProperty proc :ptr
    get_RowCountProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIGridPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIGridPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IGridPatternIdentifiers <L"Windows.UI.Xaml.Automation.IGridPatternIdentifiers">
DEFINE_IIDX(IGridPatternIdentifiers, "C902980F-96C5-450C-9044-7E52C24F9E94")

.comdef IGridPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIMultipleViewPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIMultipleViewPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IMultipleViewPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IMultipleViewPatternIdentifiersStatics">
DEFINE_IIDX(IMultipleViewPatternIdentifiersStatics, "A9CFA66F-6B84-4D71-9E48-D764D3BCDA8E")

.comdef IMultipleViewPatternIdentifiersStatics : public IInspectable

    get_CurrentViewProperty proc :ptr
    get_SupportedViewsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIMultipleViewPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIMultipleViewPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IMultipleViewPatternIdentifiers <L"Windows.UI.Xaml.Automation.IMultipleViewPatternIdentifiers">
DEFINE_IIDX(IMultipleViewPatternIdentifiers, "5D5CD3B8-1E12-488B-B0EA-5E6CB89816E1")

.comdef IMultipleViewPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIRangeValuePatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIRangeValuePatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IRangeValuePatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IRangeValuePatternIdentifiersStatics">
DEFINE_IIDX(IRangeValuePatternIdentifiersStatics, "CE23450F-1C27-457F-B815-7A5E46863DBB")

.comdef IRangeValuePatternIdentifiersStatics : public IInspectable

    get_IsReadOnlyProperty proc :ptr
    get_LargeChangeProperty proc :ptr
    get_MaximumProperty proc :ptr
    get_MinimumProperty proc :ptr
    get_SmallChangeProperty proc :ptr
    get_ValueProperty   proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIRangeValuePatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIRangeValuePatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IRangeValuePatternIdentifiers <L"Windows.UI.Xaml.Automation.IRangeValuePatternIdentifiers">
DEFINE_IIDX(IRangeValuePatternIdentifiers, "F8760F45-33C9-467D-BC9E-D1515263ACE1")

.comdef IRangeValuePatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIScrollPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIScrollPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IScrollPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IScrollPatternIdentifiersStatics">
DEFINE_IIDX(IScrollPatternIdentifiersStatics, "4BF8E0A1-FB7F-4FA4-83B3-CFAEB103A685")

.comdef IScrollPatternIdentifiersStatics : public IInspectable

    get_HorizontallyScrollableProperty proc :ptr
    get_HorizontalScrollPercentProperty proc :ptr
    get_HorizontalViewSizeProperty proc :ptr
    get_NoScroll        proc :ptr
    get_VerticallyScrollableProperty proc :ptr
    get_VerticalScrollPercentProperty proc :ptr
    get_VerticalViewSizeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIScrollPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIScrollPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IScrollPatternIdentifiers <L"Windows.UI.Xaml.Automation.IScrollPatternIdentifiers">
DEFINE_IIDX(IScrollPatternIdentifiers, "366B1003-425C-4951-AE83-D521E73BC696")

.comdef IScrollPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISelectionItemPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISelectionItemPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ISelectionItemPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.ISelectionItemPatternIdentifiersStatics">
DEFINE_IIDX(ISelectionItemPatternIdentifiersStatics, "A918D163-487E-4E3E-9F86-7B44ACBE27CE")

.comdef ISelectionItemPatternIdentifiersStatics : public IInspectable

    get_IsSelectedProperty proc :ptr
    get_SelectionContainerProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISelectionItemPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISelectionItemPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ISelectionItemPatternIdentifiers <L"Windows.UI.Xaml.Automation.ISelectionItemPatternIdentifiers">
DEFINE_IIDX(ISelectionItemPatternIdentifiers, "2DAFA41A-3EF8-4BB5-A02B-3EE1B2274740")

.comdef ISelectionItemPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISelectionPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISelectionPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ISelectionPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.ISelectionPatternIdentifiersStatics">
DEFINE_IIDX(ISelectionPatternIdentifiersStatics, "93035B4C-6B50-40A1-B23F-5C78DDBD479A")

.comdef ISelectionPatternIdentifiersStatics : public IInspectable

    get_CanSelectMultipleProperty proc :ptr
    get_IsSelectionRequiredProperty proc :ptr
    get_SelectionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISelectionPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISelectionPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ISelectionPatternIdentifiers <L"Windows.UI.Xaml.Automation.ISelectionPatternIdentifiers">
DEFINE_IIDX(ISelectionPatternIdentifiers, "4AA66FB0-E3F7-475F-B78D-F8A83BB730C4")

.comdef ISelectionPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITableItemPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITableItemPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITableItemPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.ITableItemPatternIdentifiersStatics">
DEFINE_IIDX(ITableItemPatternIdentifiersStatics, "24C4B923-E9A2-4DE9-B2A4-A8B22D0BE362")

.comdef ITableItemPatternIdentifiersStatics : public IInspectable

    get_ColumnHeaderItemsProperty proc :ptr
    get_RowHeaderItemsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITableItemPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITableItemPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITableItemPatternIdentifiers <L"Windows.UI.Xaml.Automation.ITableItemPatternIdentifiers">
DEFINE_IIDX(ITableItemPatternIdentifiers, "C326E5AD-8077-4C64-98E4-E83BCF1B4389")

.comdef ITableItemPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITablePatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITablePatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITablePatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.ITablePatternIdentifiersStatics">
DEFINE_IIDX(ITablePatternIdentifiersStatics, "75073D25-32C9-4903-AECF-DC3504CBD244")

.comdef ITablePatternIdentifiersStatics : public IInspectable

    get_ColumnHeadersProperty proc :ptr
    get_RowHeadersProperty proc :ptr
    get_RowOrColumnMajorProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITablePatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITablePatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITablePatternIdentifiers <L"Windows.UI.Xaml.Automation.ITablePatternIdentifiers">
DEFINE_IIDX(ITablePatternIdentifiers, "38D104FE-0D0C-412A-BF8D-51EDE683BAF5")

.comdef ITablePatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITogglePatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITogglePatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITogglePatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.ITogglePatternIdentifiersStatics">
DEFINE_IIDX(ITogglePatternIdentifiersStatics, "C7F75544-14A5-4F2F-92FC-760524DE06EA")

.comdef ITogglePatternIdentifiersStatics : public IInspectable

    get_ToggleStateProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITogglePatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITogglePatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITogglePatternIdentifiers <L"Windows.UI.Xaml.Automation.ITogglePatternIdentifiers">
DEFINE_IIDX(ITogglePatternIdentifiers, "7E191F6B-34D4-4AE7-83AC-29F88882D985")

.comdef ITogglePatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITransformPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITransformPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITransformPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.ITransformPatternIdentifiersStatics">
DEFINE_IIDX(ITransformPatternIdentifiersStatics, "4570EDAB-D705-40C4-A1DC-E9ACFCEF85F6")

.comdef ITransformPatternIdentifiersStatics : public IInspectable

    get_CanMoveProperty proc :ptr
    get_CanResizeProperty proc :ptr
    get_CanRotateProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITransformPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITransformPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITransformPatternIdentifiers <L"Windows.UI.Xaml.Automation.ITransformPatternIdentifiers">
DEFINE_IIDX(ITransformPatternIdentifiers, "E4115B8C-C3C8-4A37-B994-2709A7811665")

.comdef ITransformPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIValuePatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIValuePatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IValuePatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IValuePatternIdentifiersStatics">
DEFINE_IIDX(IValuePatternIdentifiersStatics, "C247E8F7-ADCC-440F-B123-33788A40525A")

.comdef IValuePatternIdentifiersStatics : public IInspectable

    get_IsReadOnlyProperty proc :ptr
    get_ValueProperty   proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIValuePatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIValuePatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IValuePatternIdentifiers <L"Windows.UI.Xaml.Automation.IValuePatternIdentifiers">
DEFINE_IIDX(IValuePatternIdentifiers, "425BF64C-5333-4E41-B470-2BAD14ECD085")

.comdef IValuePatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIWindowPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIWindowPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IWindowPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IWindowPatternIdentifiersStatics">
DEFINE_IIDX(IWindowPatternIdentifiersStatics, "07D0AD06-6302-4D29-878B-19DA03FC228D")

.comdef IWindowPatternIdentifiersStatics : public IInspectable

    get_CanMaximizeProperty proc :ptr
    get_CanMinimizeProperty proc :ptr
    get_IsModalProperty proc :ptr
    get_IsTopmostProperty proc :ptr
    get_WindowInteractionStateProperty proc :ptr
    get_WindowVisualStateProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIWindowPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIWindowPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IWindowPatternIdentifiers <L"Windows.UI.Xaml.Automation.IWindowPatternIdentifiers">
DEFINE_IIDX(IWindowPatternIdentifiers, "39F78BB4-7032-41E2-B79E-27B74A8628DE")

.comdef IWindowPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITransformPattern2IdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITransformPattern2IdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITransformPattern2IdentifiersStatics <L"Windows.UI.Xaml.Automation.ITransformPattern2IdentifiersStatics">
DEFINE_IIDX(ITransformPattern2IdentifiersStatics, "78963644-11F0-467C-A72B-5DAC41C1F6FE")

.comdef ITransformPattern2IdentifiersStatics : public IInspectable

    get_CanZoomProperty proc :ptr
    get_ZoomLevelProperty proc :ptr
    get_MaxZoomProperty proc :ptr
    get_MinZoomProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITransformPattern2Identifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CITransformPattern2Identifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ITransformPattern2Identifiers <L"Windows.UI.Xaml.Automation.ITransformPattern2Identifiers">
DEFINE_IIDX(ITransformPattern2Identifiers, "08AAA03D-DEA7-402F-8097-9A2783D60E5D")

.comdef ITransformPattern2Identifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISpreadsheetItemPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISpreadsheetItemPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ISpreadsheetItemPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.ISpreadsheetItemPatternIdentifiersStatics">
DEFINE_IIDX(ISpreadsheetItemPatternIdentifiersStatics, "43658779-5380-4F12-B468-B4F368AD4499")

.comdef ISpreadsheetItemPatternIdentifiersStatics : public IInspectable

    get_FormulaProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISpreadsheetItemPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CISpreadsheetItemPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_ISpreadsheetItemPatternIdentifiers <L"Windows.UI.Xaml.Automation.ISpreadsheetItemPatternIdentifiers">
DEFINE_IIDX(ISpreadsheetItemPatternIdentifiers, "84347E19-CA4B-46A2-A794-C87928A3B1AB")

.comdef ISpreadsheetItemPatternIdentifiers : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIStylesPatternIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIStylesPatternIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IStylesPatternIdentifiersStatics <L"Windows.UI.Xaml.Automation.IStylesPatternIdentifiersStatics">
DEFINE_IIDX(IStylesPatternIdentifiersStatics, "528A457A-BC3C-4D48-94AF-1F68703CA296")

.comdef IStylesPatternIdentifiersStatics : public IInspectable

    get_ExtendedPropertiesProperty proc :ptr
    get_FillColorProperty proc :ptr
    get_FillPatternColorProperty proc :ptr
    get_FillPatternStyleProperty proc :ptr
    get_ShapeProperty   proc :ptr
    get_StyleIdProperty proc :ptr
    get_StyleNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIStylesPatternIdentifiers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CIStylesPatternIdentifiers_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_IStylesPatternIdentifiers <L"Windows.UI.Xaml.Automation.IStylesPatternIdentifiers">
DEFINE_IIDX(IStylesPatternIdentifiers, "B0E4E201-E89D-436B-8287-4F7903466879")

.comdef IStylesPatternIdentifiers : public IInspectable

   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_AutomationProperty_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_AutomationProperty_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperty <L"Windows.UI.Xaml.Automation.AutomationProperty">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_AutomationProperties_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_AutomationProperties_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties <L"Windows.UI.Xaml.Automation.AutomationProperties">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_AutomationElementIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_AutomationElementIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_AutomationElementIdentifiers <L"Windows.UI.Xaml.Automation.AutomationElementIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_AnnotationPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_AnnotationPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_AnnotationPatternIdentifiers <L"Windows.UI.Xaml.Automation.AnnotationPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_DockPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_DockPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_DockPatternIdentifiers <L"Windows.UI.Xaml.Automation.DockPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_DragPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_DragPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_DragPatternIdentifiers <L"Windows.UI.Xaml.Automation.DragPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_DropTargetPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_DropTargetPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_DropTargetPatternIdentifiers <L"Windows.UI.Xaml.Automation.DropTargetPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_ExpandCollapsePatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_ExpandCollapsePatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_ExpandCollapsePatternIdentifiers <L"Windows.UI.Xaml.Automation.ExpandCollapsePatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_GridItemPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_GridItemPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_GridItemPatternIdentifiers <L"Windows.UI.Xaml.Automation.GridItemPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_GridPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_GridPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_GridPatternIdentifiers <L"Windows.UI.Xaml.Automation.GridPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_MultipleViewPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_MultipleViewPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_MultipleViewPatternIdentifiers <L"Windows.UI.Xaml.Automation.MultipleViewPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_RangeValuePatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_RangeValuePatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_RangeValuePatternIdentifiers <L"Windows.UI.Xaml.Automation.RangeValuePatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_ScrollPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_ScrollPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_ScrollPatternIdentifiers <L"Windows.UI.Xaml.Automation.ScrollPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_SelectionItemPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_SelectionItemPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_SelectionItemPatternIdentifiers <L"Windows.UI.Xaml.Automation.SelectionItemPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_SelectionPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_SelectionPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_SelectionPatternIdentifiers <L"Windows.UI.Xaml.Automation.SelectionPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_TableItemPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_TableItemPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_TableItemPatternIdentifiers <L"Windows.UI.Xaml.Automation.TableItemPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_TablePatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_TablePatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_TablePatternIdentifiers <L"Windows.UI.Xaml.Automation.TablePatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_TogglePatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_TogglePatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_TogglePatternIdentifiers <L"Windows.UI.Xaml.Automation.TogglePatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_TransformPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_TransformPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_TransformPatternIdentifiers <L"Windows.UI.Xaml.Automation.TransformPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_ValuePatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_ValuePatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_ValuePatternIdentifiers <L"Windows.UI.Xaml.Automation.ValuePatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_WindowPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_WindowPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_WindowPatternIdentifiers <L"Windows.UI.Xaml.Automation.WindowPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_TransformPattern2Identifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_TransformPattern2Identifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_TransformPattern2Identifiers <L"Windows.UI.Xaml.Automation.TransformPattern2Identifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_SpreadsheetItemPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_SpreadsheetItemPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_SpreadsheetItemPatternIdentifiers <L"Windows.UI.Xaml.Automation.SpreadsheetItemPatternIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_StylesPatternIdentifiers_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_StylesPatternIdentifiers_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_StylesPatternIdentifiers <L"Windows.UI.Xaml.Automation.StylesPatternIdentifiers">
endif

endif
