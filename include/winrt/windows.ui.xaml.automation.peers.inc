ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Eautomation2Epeers_h__
define __windows2Eui2Examl2Eautomation2Epeers_h__

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Automation
.namespace Peers

.enum AccessibilityView {
    AccessibilityView_Raw	= 0,
    AccessibilityView_Control	= 1,
    AccessibilityView_Content	= 2
    }

.enum AutomationControlType {
    AutomationControlType_Button	= 0,
    AutomationControlType_Calendar	= 1,
    AutomationControlType_CheckBox	= 2,
    AutomationControlType_ComboBox	= 3,
    AutomationControlType_Edit	= 4,
    AutomationControlType_Hyperlink	= 5,
    AutomationControlType_Image = 6,
    AutomationControlType_ListItem	= 7,
    AutomationControlType_List	= 8,
    AutomationControlType_Menu	= 9,
    AutomationControlType_MenuBar	= 10,
    AutomationControlType_MenuItem	= 11,
    AutomationControlType_ProgressBar	= 12,
    AutomationControlType_RadioButton	= 13,
    AutomationControlType_ScrollBar	= 14,
    AutomationControlType_Slider	= 15,
    AutomationControlType_Spinner	= 16,
    AutomationControlType_StatusBar	= 17,
    AutomationControlType_Tab	= 18,
    AutomationControlType_TabItem	= 19,
    AutomationControlType_Text	= 20,
    AutomationControlType_ToolBar	= 21,
    AutomationControlType_ToolTip	= 22,
    AutomationControlType_Tree	= 23,
    AutomationControlType_TreeItem	= 24,
    AutomationControlType_Custom	= 25,
    AutomationControlType_Group = 26,
    AutomationControlType_Thumb = 27,
    AutomationControlType_DataGrid	= 28,
    AutomationControlType_DataItem	= 29,
    AutomationControlType_Document	= 30,
    AutomationControlType_SplitButton	= 31,
    AutomationControlType_Window	= 32,
    AutomationControlType_Pane	= 33,
    AutomationControlType_Header	= 34,
    AutomationControlType_HeaderItem	= 35,
    AutomationControlType_Table = 36,
    AutomationControlType_TitleBar	= 37,
    AutomationControlType_Separator	= 38,
    AutomationControlType_SemanticZoom	= 39,
    AutomationControlType_AppBar	= 40
    }

.enum AutomationEvents {
    AutomationEvents_ToolTipOpened	= 0,
    AutomationEvents_ToolTipClosed	= 1,
    AutomationEvents_MenuOpened = 2,
    AutomationEvents_MenuClosed = 3,
    AutomationEvents_AutomationFocusChanged	= 4,
    AutomationEvents_InvokePatternOnInvoked	= 5,
    AutomationEvents_SelectionItemPatternOnElementAddedToSelection	= 6,
    AutomationEvents_SelectionItemPatternOnElementRemovedFromSelection	= 7,
    AutomationEvents_SelectionItemPatternOnElementSelected	= 8,
    AutomationEvents_SelectionPatternOnInvalidated	= 9,
    AutomationEvents_TextPatternOnTextSelectionChanged	= 10,
    AutomationEvents_TextPatternOnTextChanged	= 11,
    AutomationEvents_AsyncContentLoaded = 12,
    AutomationEvents_PropertyChanged	= 13,
    AutomationEvents_StructureChanged	= 14,
    AutomationEvents_DragStart	= 15,
    AutomationEvents_DragCancel = 16,
    AutomationEvents_DragComplete	= 17,
    AutomationEvents_DragEnter	= 18,
    AutomationEvents_DragLeave	= 19,
    AutomationEvents_Dropped	= 20,
    AutomationEvents_LiveRegionChanged	= 21
    }

.enum AutomationLiveSetting {
    AutomationLiveSetting_Off	= 0,
    AutomationLiveSetting_Polite	= 1,
    AutomationLiveSetting_Assertive	= 2
    }

.enum AutomationOrientation {
    AutomationOrientation_None	= 0,
    AutomationOrientation_Horizontal	= 1,
    AutomationOrientation_Vertical	= 2
    }

.enum PatternInterface {
    PatternInterface_Invoke	= 0,
    PatternInterface_Selection	= 1,
    PatternInterface_Value	= 2,
    PatternInterface_RangeValue = 3,
    PatternInterface_Scroll	= 4,
    PatternInterface_ScrollItem = 5,
    PatternInterface_ExpandCollapse	= 6,
    PatternInterface_Grid	= 7,
    PatternInterface_GridItem	= 8,
    PatternInterface_MultipleView	= 9,
    PatternInterface_Window	= 10,
    PatternInterface_SelectionItem	= 11,
    PatternInterface_Dock	= 12,
    PatternInterface_Table	= 13,
    PatternInterface_TableItem	= 14,
    PatternInterface_Toggle	= 15,
    PatternInterface_Transform	= 16,
    PatternInterface_Text	= 17,
    PatternInterface_ItemContainer	= 18,
    PatternInterface_VirtualizedItem	= 19,
    PatternInterface_Text2	= 20,
    PatternInterface_TextChild	= 21,
    PatternInterface_TextRange	= 22,
    PatternInterface_Annotation = 23,
    PatternInterface_Drag	= 24,
    PatternInterface_DropTarget = 25,
    PatternInterface_ObjectModel	= 26,
    PatternInterface_Spreadsheet	= 27,
    PatternInterface_SpreadsheetItem	= 28,
    PatternInterface_Styles	= 29,
    PatternInterface_Transform2 = 30,
    PatternInterface_SynchronizedInput	= 31
    }

.endn
.endn
.endn
.endn
.endn

ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.UI.Xaml.inc
include Windows.UI.Xaml.Automation.inc
include Windows.UI.Xaml.Automation.Provider.inc

ifndef ____FIIterator_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer, "1f93cd7a-8075-5ba9-bc3e-b04a94e14bc0")

.comdef __FIIterator_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer, "7f67a4e2-96e0-522b-8710-14c42d834f1e")

.comdef __FIIterable_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer, "b56a6076-19e2-50c1-930f-825bfc39635c")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer, "a8d8a409-9130-5e14-8426-0782aaf01608")

.comdef __FIVector_1_Windows__CUI__CXaml__CAutomation__CPeers__CAutomationPeer : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Automation
.namespace Peers

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIButtonAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIButtonAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IButtonAutomationPeer">
DEFINE_IIDX(IButtonAutomationPeer, "FB77EFBE-39EC-4508-8AC3-51A1424027D7")

.comdef IButtonAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIButtonAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIButtonAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IButtonAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IButtonAutomationPeerFactory">
DEFINE_IIDX(IButtonAutomationPeerFactory, "3FDB9F49-F4AB-4780-8644-03376299A175")

.comdef IButtonAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIButtonBaseAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIButtonBaseAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IButtonBaseAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IButtonBaseAutomationPeer">
DEFINE_IIDX(IButtonBaseAutomationPeer, "A4F3B5B6-7585-4E0B-96D2-08CF6F28BEFA")

.comdef IButtonBaseAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIButtonBaseAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIButtonBaseAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IButtonBaseAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IButtonBaseAutomationPeerFactory">
DEFINE_IIDX(IButtonBaseAutomationPeerFactory, "8A04091E-E6B2-4C60-A759-C13CA45165ED")

.comdef IButtonBaseAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CICaptureElementAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CICaptureElementAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ICaptureElementAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ICaptureElementAutomationPeer">
DEFINE_IIDX(ICaptureElementAutomationPeer, "DCC44EE0-FA45-45C6-8BB7-320D808F5958")

.comdef ICaptureElementAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CICaptureElementAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CICaptureElementAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ICaptureElementAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ICaptureElementAutomationPeerFactory">
DEFINE_IIDX(ICaptureElementAutomationPeerFactory, "9B92EF48-85E9-4869-B175-8F7CF45A6D9F")

.comdef ICaptureElementAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CICheckBoxAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CICheckBoxAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ICheckBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ICheckBoxAutomationPeer">
DEFINE_IIDX(ICheckBoxAutomationPeer, "EB15BC42-C0A9-46C6-AC24-B83DE429C733")

.comdef ICheckBoxAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CICheckBoxAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CICheckBoxAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ICheckBoxAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ICheckBoxAutomationPeerFactory">
DEFINE_IIDX(ICheckBoxAutomationPeerFactory, "B75C775D-EB8F-44EF-A27C-E26AC7DE8333")

.comdef ICheckBoxAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IComboBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IComboBoxAutomationPeer">
DEFINE_IIDX(IComboBoxAutomationPeer, "7EB40D0B-75C5-4263-BA6A-D4A54FB0F239")

.comdef IComboBoxAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IComboBoxAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IComboBoxAutomationPeerFactory">
DEFINE_IIDX(IComboBoxAutomationPeerFactory, "098E5B0D-1B90-40B9-9BE3-B23267EB13CF")

.comdef IComboBoxAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IComboBoxItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IComboBoxItemAutomationPeer">
DEFINE_IIDX(IComboBoxItemAutomationPeer, "12DDC76E-9552-446A-82EE-938CC371800F")

.comdef IComboBoxItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IComboBoxItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IComboBoxItemAutomationPeerFactory">
DEFINE_IIDX(IComboBoxItemAutomationPeerFactory, "134AC7FC-397A-403F-A6EC-1CE8BEDA15E5")

.comdef IComboBoxItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxItemDataAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxItemDataAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IComboBoxItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IComboBoxItemDataAutomationPeer">
DEFINE_IIDX(IComboBoxItemDataAutomationPeer, "4FEF6DF2-289C-4C04-831B-5A668C6D7104")

.comdef IComboBoxItemDataAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIComboBoxItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IComboBoxItemDataAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IComboBoxItemDataAutomationPeerFactory">
DEFINE_IIDX(IComboBoxItemDataAutomationPeerFactory, "14A8D4F6-469A-41BA-9D93-44A1A55DA872")

.comdef IComboBoxItemDataAutomationPeerFactory : public IInspectable

    CreateInstanceWithParentAndItem proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFlipViewAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IFlipViewAutomationPeer">
DEFINE_IIDX(IFlipViewAutomationPeer, "8EC0353A-4284-4B00-AEF8-A2688EA5E3C4")

.comdef IFlipViewAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFlipViewAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IFlipViewAutomationPeerFactory">
DEFINE_IIDX(IFlipViewAutomationPeerFactory, "4395AB0D-8D83-483C-88EB-E2617B0D293F")

.comdef IFlipViewAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFlipViewItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IFlipViewItemAutomationPeer">
DEFINE_IIDX(IFlipViewItemAutomationPeer, "C83034DE-FA08-4BD3-AEB2-D2E5BFA04DF9")

.comdef IFlipViewItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFlipViewItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IFlipViewItemAutomationPeerFactory">
DEFINE_IIDX(IFlipViewItemAutomationPeerFactory, "69109356-D0E5-4C10-A09C-AD0BF1B0CB01")

.comdef IFlipViewItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewItemDataAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewItemDataAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFlipViewItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IFlipViewItemDataAutomationPeer">
DEFINE_IIDX(IFlipViewItemDataAutomationPeer, "B0986175-00BC-4118-8A6F-16EE9C15D968")

.comdef IFlipViewItemDataAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlipViewItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFlipViewItemDataAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IFlipViewItemDataAutomationPeerFactory">
DEFINE_IIDX(IFlipViewItemDataAutomationPeerFactory, "3C864393-0AEA-4E78-BC11-B775CAC4114C")

.comdef IFlipViewItemDataAutomationPeerFactory : public IInspectable

    CreateInstanceWithParentAndItem proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGridViewAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IGridViewAutomationPeer">
DEFINE_IIDX(IGridViewAutomationPeer, "1C4401A4-D951-49CA-8F82-C7F3C60681B0")

.comdef IGridViewAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGridViewAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IGridViewAutomationPeerFactory">
DEFINE_IIDX(IGridViewAutomationPeerFactory, "8ACA59DD-22A7-4800-894B-C1F485F38953")

.comdef IGridViewAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGridViewItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IGridViewItemAutomationPeer">
DEFINE_IIDX(IGridViewItemAutomationPeer, "93EF2D07-346C-4166-A4BA-BC6A181E7F33")

.comdef IGridViewItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGridViewItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IGridViewItemAutomationPeerFactory">
DEFINE_IIDX(IGridViewItemAutomationPeerFactory, "FAFEC376-F22E-466D-913C-AE24CCDB160F")

.comdef IGridViewItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewItemDataAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewItemDataAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGridViewItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IGridViewItemDataAutomationPeer">
DEFINE_IIDX(IGridViewItemDataAutomationPeer, "F3F4868F-29D4-4094-8C54-EA61A88294A4")

.comdef IGridViewItemDataAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGridViewItemDataAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IGridViewItemDataAutomationPeerFactory">
DEFINE_IIDX(IGridViewItemDataAutomationPeerFactory, "A65E7A88-770D-402C-996F-67506AF2A4AF")

.comdef IGridViewItemDataAutomationPeerFactory : public IInspectable

    CreateInstanceWithParentAndItem proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGroupItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGroupItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGroupItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IGroupItemAutomationPeer">
DEFINE_IIDX(IGroupItemAutomationPeer, "1914FE6D-0740-4236-9EE1-38CF19C1C388")

.comdef IGroupItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGroupItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGroupItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGroupItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IGroupItemAutomationPeerFactory">
DEFINE_IIDX(IGroupItemAutomationPeerFactory, "56A64567-F21C-4C90-B379-15A27C7F8409")

.comdef IGroupItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHyperlinkButtonAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHyperlinkButtonAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IHyperlinkButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IHyperlinkButtonAutomationPeer">
DEFINE_IIDX(IHyperlinkButtonAutomationPeer, "AA7AFCB1-0EDF-46D9-AA9E-0EB21D140097")

.comdef IHyperlinkButtonAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHyperlinkButtonAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHyperlinkButtonAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IHyperlinkButtonAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IHyperlinkButtonAutomationPeerFactory">
DEFINE_IIDX(IHyperlinkButtonAutomationPeerFactory, "59BC1661-C182-49AF-9526-44B88E628455")

.comdef IHyperlinkButtonAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIImageAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIImageAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IImageAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IImageAutomationPeer">
DEFINE_IIDX(IImageAutomationPeer, "9B0BBF8C-60A2-48BF-AB2C-1A52A451D2D4")

.comdef IImageAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIImageAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIImageAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IImageAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IImageAutomationPeerFactory">
DEFINE_IIDX(IImageAutomationPeerFactory, "90304003-687D-47BF-B3A2-4BABCAD8EF50")

.comdef IImageAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IItemAutomationPeer">
DEFINE_IIDX(IItemAutomationPeer, "953C34F6-3B31-47A7-B3BF-25D3AE99C317")

.comdef IItemAutomationPeer : public IInspectable

    get_Item		proc :ptr
    get_ItemsControlAutomationPeer proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IItemAutomationPeerFactory">
DEFINE_IIDX(IItemAutomationPeerFactory, "29065073-DE3D-4D3F-97B4-4D6F9D53444D")

.comdef IItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithParentAndItem proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIItemsControlAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIItemsControlAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IItemsControlAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IItemsControlAutomationPeer">
DEFINE_IIDX(IItemsControlAutomationPeer, "96E76BF1-37F7-4088-925D-65268E83E34D")

.comdef IItemsControlAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIItemsControlAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIItemsControlAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IItemsControlAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IItemsControlAutomationPeerFactory">
DEFINE_IIDX(IItemsControlAutomationPeerFactory, "4038A259-2E1A-49CA-A533-C64F181577E6")

.comdef IItemsControlAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListBoxAutomationPeer">
DEFINE_IIDX(IListBoxAutomationPeer, "8CD0D608-B402-4A6E-BD9A-343F8845EB32")

.comdef IListBoxAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListBoxAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListBoxAutomationPeerFactory">
DEFINE_IIDX(IListBoxAutomationPeerFactory, "E2362185-7DF6-49F7-8ABC-4C33F1A3D46E")

.comdef IListBoxAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListBoxItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListBoxItemAutomationPeer">
DEFINE_IIDX(IListBoxItemAutomationPeer, "1BC6E1C6-2997-42DF-99EB-92BC1DD149FB")

.comdef IListBoxItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListBoxItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListBoxItemAutomationPeerFactory">
DEFINE_IIDX(IListBoxItemAutomationPeerFactory, "509F9DD8-B0AA-443F-A110-41209AF44F1C")

.comdef IListBoxItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxItemDataAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxItemDataAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListBoxItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListBoxItemDataAutomationPeer">
DEFINE_IIDX(IListBoxItemDataAutomationPeer, "FD7D5FEE-FDE0-482A-8084-DCEBBA5B9806")

.comdef IListBoxItemDataAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListBoxItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListBoxItemDataAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListBoxItemDataAutomationPeerFactory">
DEFINE_IIDX(IListBoxItemDataAutomationPeerFactory, "D7924E16-BD8D-4662-A995-20FF9A056093")

.comdef IListBoxItemDataAutomationPeerFactory : public IInspectable

    CreateInstanceWithParentAndItem proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListViewAutomationPeer">
DEFINE_IIDX(IListViewAutomationPeer, "73CECC87-C0DC-4260-9148-75E9864A7230")

.comdef IListViewAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListViewAutomationPeerFactory">
DEFINE_IIDX(IListViewAutomationPeerFactory, "65F39174-EAA2-4E44-8BE6-4CCA28CD0288")

.comdef IListViewAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewBaseAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewBaseAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewBaseAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListViewBaseAutomationPeer">
DEFINE_IIDX(IListViewBaseAutomationPeer, "87EC7649-B83D-4E55-9AFD-BD835E748F5C")

.comdef IListViewBaseAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewBaseAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewBaseAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewBaseAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListViewBaseAutomationPeerFactory">
DEFINE_IIDX(IListViewBaseAutomationPeerFactory, "70D3C2BE-8950-4647-9362-FD002F8FF82E")

.comdef IListViewBaseAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListViewItemAutomationPeer">
DEFINE_IIDX(IListViewItemAutomationPeer, "CA114E70-A16D-4D09-A1CF-1856EF98A9EC")

.comdef IListViewItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListViewItemAutomationPeerFactory">
DEFINE_IIDX(IListViewItemAutomationPeerFactory, "C47DFBC0-FACC-4024-A73B-17EC4E662654")

.comdef IListViewItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewItemDataAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewItemDataAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListViewItemDataAutomationPeer">
DEFINE_IIDX(IListViewItemDataAutomationPeer, "15A8D7FD-D7A5-4A6C-963C-6F7CE464671A")

.comdef IListViewItemDataAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewItemDataAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewItemDataAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListViewItemDataAutomationPeerFactory">
DEFINE_IIDX(IListViewItemDataAutomationPeerFactory, "D0DB12BB-D715-4523-ACC0-1E1072D8E32B")

.comdef IListViewItemDataAutomationPeerFactory : public IInspectable

    CreateInstanceWithParentAndItem proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMediaElementAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMediaElementAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IMediaElementAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IMediaElementAutomationPeer">
DEFINE_IIDX(IMediaElementAutomationPeer, "BA0B9FC2-A6E2-41A5-B17A-D1594613EFBA")

.comdef IMediaElementAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMediaElementAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMediaElementAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IMediaElementAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IMediaElementAutomationPeerFactory">
DEFINE_IIDX(IMediaElementAutomationPeerFactory, "B2AD3B28-7575-4173-9BC7-80367A164ED2")

.comdef IMediaElementAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIPasswordBoxAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIPasswordBoxAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IPasswordBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IPasswordBoxAutomationPeer">
DEFINE_IIDX(IPasswordBoxAutomationPeer, "684F065E-3DF3-4B9F-82AD-8819DB3B218A")

.comdef IPasswordBoxAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIPasswordBoxAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIPasswordBoxAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IPasswordBoxAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IPasswordBoxAutomationPeerFactory">
DEFINE_IIDX(IPasswordBoxAutomationPeerFactory, "AC3D7EDE-DCA4-481C-B520-4A9B3F3B179C")

.comdef IPasswordBoxAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIProgressBarAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIProgressBarAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IProgressBarAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IProgressBarAutomationPeer">
DEFINE_IIDX(IProgressBarAutomationPeer, "93F48F86-D840-4FB6-AC2F-5F779B854B0D")

.comdef IProgressBarAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIProgressBarAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIProgressBarAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IProgressBarAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IProgressBarAutomationPeerFactory">
DEFINE_IIDX(IProgressBarAutomationPeerFactory, "364679AB-B80F-41B4-8EEA-2F5251BC739C")

.comdef IProgressBarAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIProgressRingAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIProgressRingAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IProgressRingAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IProgressRingAutomationPeer">
DEFINE_IIDX(IProgressRingAutomationPeer, "BC305EEE-39D3-4EEB-AC33-2394DE123E2E")

.comdef IProgressRingAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIProgressRingAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIProgressRingAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IProgressRingAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IProgressRingAutomationPeerFactory">
DEFINE_IIDX(IProgressRingAutomationPeerFactory, "F3DB204B-157E-40BC-9593-55BC5C71A4F6")

.comdef IProgressRingAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRadioButtonAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRadioButtonAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRadioButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IRadioButtonAutomationPeer">
DEFINE_IIDX(IRadioButtonAutomationPeer, "7E6A5ED8-0B30-4743-B102-DCDF548E3131")

.comdef IRadioButtonAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRadioButtonAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRadioButtonAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRadioButtonAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IRadioButtonAutomationPeerFactory">
DEFINE_IIDX(IRadioButtonAutomationPeerFactory, "4940C4FD-3D88-49CA-8F31-924187AF0BFE")

.comdef IRadioButtonAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRangeBaseAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRangeBaseAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRangeBaseAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IRangeBaseAutomationPeer">
DEFINE_IIDX(IRangeBaseAutomationPeer, "E454B549-4B2C-42AD-B04B-D35947D1EE50")

.comdef IRangeBaseAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRangeBaseAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRangeBaseAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRangeBaseAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IRangeBaseAutomationPeerFactory">
DEFINE_IIDX(IRangeBaseAutomationPeerFactory, "827C7601-3078-4479-95EA-91374CA06207")

.comdef IRangeBaseAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRepeatButtonAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRepeatButtonAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRepeatButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IRepeatButtonAutomationPeer">
DEFINE_IIDX(IRepeatButtonAutomationPeer, "29E41AD5-A8AC-4E8A-83D8-09E37E054257")

.comdef IRepeatButtonAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRepeatButtonAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRepeatButtonAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRepeatButtonAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IRepeatButtonAutomationPeerFactory">
DEFINE_IIDX(IRepeatButtonAutomationPeerFactory, "6A6FF9D4-575E-4E60-BDD6-EC14419B4FF6")

.comdef IRepeatButtonAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichEditBoxAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichEditBoxAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRichEditBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IRichEditBoxAutomationPeer">
DEFINE_IIDX(IRichEditBoxAutomationPeer, "C69F5C04-16EE-467A-A833-C3DA8458AD64")

.comdef IRichEditBoxAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichEditBoxAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichEditBoxAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRichEditBoxAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IRichEditBoxAutomationPeerFactory">
DEFINE_IIDX(IRichEditBoxAutomationPeerFactory, "752C8399-D296-4D87-9020-A4750E885B3C")

.comdef IRichEditBoxAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichTextBlockAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichTextBlockAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRichTextBlockAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IRichTextBlockAutomationPeer">
DEFINE_IIDX(IRichTextBlockAutomationPeer, "93A01A9C-9609-41FA-82F3-909C09F49A72")

.comdef IRichTextBlockAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichTextBlockAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichTextBlockAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRichTextBlockAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IRichTextBlockAutomationPeerFactory">
DEFINE_IIDX(IRichTextBlockAutomationPeerFactory, "2038AE61-1389-467A-AED6-37334DA9622B")

.comdef IRichTextBlockAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichTextBlockOverflowAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichTextBlockOverflowAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRichTextBlockOverflowAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IRichTextBlockOverflowAutomationPeer">
DEFINE_IIDX(IRichTextBlockOverflowAutomationPeer, "8C9A409A-2736-437B-AB36-A16A202F105D")

.comdef IRichTextBlockOverflowAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichTextBlockOverflowAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIRichTextBlockOverflowAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IRichTextBlockOverflowAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IRichTextBlockOverflowAutomationPeerFactory">
DEFINE_IIDX(IRichTextBlockOverflowAutomationPeerFactory, "BD5EB663-2C14-4665-ADEF-F2B033947BEB")

.comdef IRichTextBlockOverflowAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIScrollBarAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIScrollBarAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IScrollBarAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IScrollBarAutomationPeer">
DEFINE_IIDX(IScrollBarAutomationPeer, "69E0C369-BBE7-41F2-87CA-AAD813FE550E")

.comdef IScrollBarAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIScrollBarAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIScrollBarAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IScrollBarAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IScrollBarAutomationPeerFactory">
DEFINE_IIDX(IScrollBarAutomationPeerFactory, "E1302110-AFEB-4595-8E3D-EDC0844A2B21")

.comdef IScrollBarAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIScrollViewerAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIScrollViewerAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IScrollViewerAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IScrollViewerAutomationPeer">
DEFINE_IIDX(IScrollViewerAutomationPeer, "D985F259-1B09-4E88-88FD-421750DC6B45")

.comdef IScrollViewerAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIScrollViewerAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIScrollViewerAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IScrollViewerAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IScrollViewerAutomationPeerFactory">
DEFINE_IIDX(IScrollViewerAutomationPeerFactory, "270DFF7D-D96D-48F9-A36A-C252AA9C4670")

.comdef IScrollViewerAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISelectorAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISelectorAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISelectorAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ISelectorAutomationPeer">
DEFINE_IIDX(ISelectorAutomationPeer, "162AC829-7115-43EC-B383-A7B71644069D")

.comdef ISelectorAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISelectorAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISelectorAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISelectorAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ISelectorAutomationPeerFactory">
DEFINE_IIDX(ISelectorAutomationPeerFactory, "7B525646-829B-4DCC-BD52-5A8D0399387A")

.comdef ISelectorAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISelectorItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISelectorItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISelectorItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ISelectorItemAutomationPeer">
DEFINE_IIDX(ISelectorItemAutomationPeer, "AE8B3477-860A-45BB-BF7C-E1B27419D1DD")

.comdef ISelectorItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISelectorItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISelectorItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISelectorItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ISelectorItemAutomationPeerFactory">
DEFINE_IIDX(ISelectorItemAutomationPeerFactory, "66D7EDFB-786D-4362-A964-EBFB21776C30")

.comdef ISelectorItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithParentAndItem proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISemanticZoomAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISemanticZoomAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISemanticZoomAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ISemanticZoomAutomationPeer">
DEFINE_IIDX(ISemanticZoomAutomationPeer, "3C2FAC6C-A977-47FC-B44E-2754C0B2BEA9")

.comdef ISemanticZoomAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISemanticZoomAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISemanticZoomAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISemanticZoomAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ISemanticZoomAutomationPeerFactory">
DEFINE_IIDX(ISemanticZoomAutomationPeerFactory, "F518D44D-A493-4496-B077-9674C7F4C5FA")

.comdef ISemanticZoomAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISettingsFlyoutAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISettingsFlyoutAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISettingsFlyoutAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ISettingsFlyoutAutomationPeer">
DEFINE_IIDX(ISettingsFlyoutAutomationPeer, "D0DE0CDB-30CF-47A6-A5EB-9C77F0B0D6DD")

.comdef ISettingsFlyoutAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISettingsFlyoutAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISettingsFlyoutAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISettingsFlyoutAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ISettingsFlyoutAutomationPeerFactory">
DEFINE_IIDX(ISettingsFlyoutAutomationPeerFactory, "F94762BD-8A14-40E4-94A7-3F33C922E945")

.comdef ISettingsFlyoutAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISliderAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISliderAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISliderAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ISliderAutomationPeer">
DEFINE_IIDX(ISliderAutomationPeer, "EC30015A-D611-46D0-AE4F-6ECF27DFBAA5")

.comdef ISliderAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISliderAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISliderAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISliderAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ISliderAutomationPeerFactory">
DEFINE_IIDX(ISliderAutomationPeerFactory, "971B8056-9A7A-4DF9-95FA-6F5C04C91CAC")

.comdef ISliderAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITextBlockAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITextBlockAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ITextBlockAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ITextBlockAutomationPeer">
DEFINE_IIDX(ITextBlockAutomationPeer, "BE2057F5-6715-4E69-A050-92BD0CE232A9")

.comdef ITextBlockAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITextBlockAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITextBlockAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ITextBlockAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ITextBlockAutomationPeerFactory">
DEFINE_IIDX(ITextBlockAutomationPeerFactory, "76BF924B-7CA0-4B01-BC5C-A8CF4D3691DE")

.comdef ITextBlockAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITextBoxAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITextBoxAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ITextBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ITextBoxAutomationPeer">
DEFINE_IIDX(ITextBoxAutomationPeer, "3A4F1CA0-5E5D-4D26-9067-E740BF657A9F")

.comdef ITextBoxAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITextBoxAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITextBoxAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ITextBoxAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ITextBoxAutomationPeerFactory">
DEFINE_IIDX(ITextBoxAutomationPeerFactory, "01F0C067-966B-4130-B872-469E42BD4A7F")

.comdef ITextBoxAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIThumbAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIThumbAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IThumbAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IThumbAutomationPeer">
DEFINE_IIDX(IThumbAutomationPeer, "DC2949B5-B45E-4D6D-892F-D9422C950EFB")

.comdef IThumbAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIThumbAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIThumbAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IThumbAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IThumbAutomationPeerFactory">
DEFINE_IIDX(IThumbAutomationPeerFactory, "970743FF-AF41-4600-B55D-26D43DF860E1")

.comdef IThumbAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleButtonAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleButtonAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IToggleButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IToggleButtonAutomationPeer">
DEFINE_IIDX(IToggleButtonAutomationPeer, "62DBE6C5-BC0A-45BB-BF77-EA0F1502891F")

.comdef IToggleButtonAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleButtonAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleButtonAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IToggleButtonAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IToggleButtonAutomationPeerFactory">
DEFINE_IIDX(IToggleButtonAutomationPeerFactory, "C9218CC4-AD4B-4D03-A6A4-7D59E6360004")

.comdef IToggleButtonAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleSwitchAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleSwitchAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IToggleSwitchAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IToggleSwitchAutomationPeer">
DEFINE_IIDX(IToggleSwitchAutomationPeer, "C011F174-E89E-4790-BF9A-78EBB5F59E9F")

.comdef IToggleSwitchAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleSwitchAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleSwitchAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IToggleSwitchAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IToggleSwitchAutomationPeerFactory">
DEFINE_IIDX(IToggleSwitchAutomationPeerFactory, "31F933E3-FEF8-4419-9DF5-D9EF7196EA34")

.comdef IToggleSwitchAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAppBarAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IAppBarAutomationPeer">
DEFINE_IIDX(IAppBarAutomationPeer, "8B4ACFEB-89FA-4F13-84BE-35CA5B7C9590")

.comdef IAppBarAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAppBarAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IAppBarAutomationPeerFactory">
DEFINE_IIDX(IAppBarAutomationPeerFactory, "8360F4E2-E396-4517-AF5D-F4CF34C54EDF")

.comdef IAppBarAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarButtonAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarButtonAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAppBarButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IAppBarButtonAutomationPeer">
DEFINE_IIDX(IAppBarButtonAutomationPeer, "443262B2-4F6D-4B76-9D2E-3EFF777E8864")

.comdef IAppBarButtonAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarButtonAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarButtonAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAppBarButtonAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IAppBarButtonAutomationPeerFactory">
DEFINE_IIDX(IAppBarButtonAutomationPeerFactory, "AEF0342A-ACB7-42DC-97E3-847071865FD6")

.comdef IAppBarButtonAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarToggleButtonAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarToggleButtonAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAppBarToggleButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IAppBarToggleButtonAutomationPeer">
DEFINE_IIDX(IAppBarToggleButtonAutomationPeer, "8464EFAD-9655-4AFF-9550-63AE9EC8FE9C")

.comdef IAppBarToggleButtonAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarToggleButtonAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAppBarToggleButtonAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAppBarToggleButtonAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IAppBarToggleButtonAutomationPeerFactory">
DEFINE_IIDX(IAppBarToggleButtonAutomationPeerFactory, "D6F9139D-02C1-4221-9591-7D4EFEB74701")

.comdef IAppBarToggleButtonAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIDatePickerAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIDatePickerAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IDatePickerAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IDatePickerAutomationPeer">
DEFINE_IIDX(IDatePickerAutomationPeer, "D07D357F-A0B9-45DC-991A-76C505E7D0F5")

.comdef IDatePickerAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIDatePickerAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIDatePickerAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IDatePickerAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IDatePickerAutomationPeerFactory">
DEFINE_IIDX(IDatePickerAutomationPeerFactory, "E5667D19-9157-4436-9F4D-7FB99174B48E")

.comdef IDatePickerAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlyoutPresenterAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlyoutPresenterAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFlyoutPresenterAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IFlyoutPresenterAutomationPeer">
DEFINE_IIDX(IFlyoutPresenterAutomationPeer, "A01840B4-5FCA-456F-98EA-300EB40B585E")

.comdef IFlyoutPresenterAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlyoutPresenterAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFlyoutPresenterAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFlyoutPresenterAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IFlyoutPresenterAutomationPeerFactory">
DEFINE_IIDX(IFlyoutPresenterAutomationPeerFactory, "F350155F-8924-44C0-BA44-653FE79F1EFB")

.comdef IFlyoutPresenterAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewHeaderItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewHeaderItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGridViewHeaderItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IGridViewHeaderItemAutomationPeer">
DEFINE_IIDX(IGridViewHeaderItemAutomationPeer, "E3DCEF3A-E08A-48E7-B23A-2BE5B66E474E")

.comdef IGridViewHeaderItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewHeaderItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIGridViewHeaderItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IGridViewHeaderItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IGridViewHeaderItemAutomationPeerFactory">
DEFINE_IIDX(IGridViewHeaderItemAutomationPeerFactory, "2C80B4D2-FFC2-4157-88DD-59CD92E39715")

.comdef IGridViewHeaderItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHubAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHubAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IHubAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IHubAutomationPeer">
DEFINE_IIDX(IHubAutomationPeer, "4DDEE056-4EBC-4620-A05D-903E3C9A4EAD")

.comdef IHubAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHubAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHubAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IHubAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IHubAutomationPeerFactory">
DEFINE_IIDX(IHubAutomationPeerFactory, "C762D43F-79DD-43EE-8777-8D08B39AA065")

.comdef IHubAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHubSectionAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHubSectionAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IHubSectionAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IHubSectionAutomationPeer">
DEFINE_IIDX(IHubSectionAutomationPeer, "16D91FF7-7431-4D82-83CE-CFA3192B0F18")

.comdef IHubSectionAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHubSectionAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIHubSectionAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IHubSectionAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IHubSectionAutomationPeerFactory">
DEFINE_IIDX(IHubSectionAutomationPeerFactory, "C68E27E8-17EC-4329-91AE-2D0B2339D498")

.comdef IHubSectionAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewBaseHeaderItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewBaseHeaderItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewBaseHeaderItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListViewBaseHeaderItemAutomationPeer">
DEFINE_IIDX(IListViewBaseHeaderItemAutomationPeer, "7CB8B732-C1F0-4A3C-BC14-85DD48DEDB85")

.comdef IListViewBaseHeaderItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewBaseHeaderItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewBaseHeaderItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewBaseHeaderItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListViewBaseHeaderItemAutomationPeerFactory">
DEFINE_IIDX(IListViewBaseHeaderItemAutomationPeerFactory, "40EC995F-D631-4004-832E-6D8643E51561")

.comdef IListViewBaseHeaderItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewHeaderItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewHeaderItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewHeaderItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IListViewHeaderItemAutomationPeer">
DEFINE_IIDX(IListViewHeaderItemAutomationPeer, "67AB1E4B-AD61-4C88-BA45-0F3A8D061F8F")

.comdef IListViewHeaderItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewHeaderItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIListViewHeaderItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IListViewHeaderItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IListViewHeaderItemAutomationPeerFactory">
DEFINE_IIDX(IListViewHeaderItemAutomationPeerFactory, "07668694-2CA5-4BE4-A8B9-592D48F76087")

.comdef IListViewHeaderItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMenuFlyoutItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMenuFlyoutItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IMenuFlyoutItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IMenuFlyoutItemAutomationPeer">
DEFINE_IIDX(IMenuFlyoutItemAutomationPeer, "1FC19462-21DF-456E-AA11-8FAC6B4B2AF6")

.comdef IMenuFlyoutItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMenuFlyoutItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMenuFlyoutItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IMenuFlyoutItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IMenuFlyoutItemAutomationPeerFactory">
DEFINE_IIDX(IMenuFlyoutItemAutomationPeerFactory, "D08BFCB8-20D1-45D8-A2C2-2F130DF714E0")

.comdef IMenuFlyoutItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMenuFlyoutPresenterAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMenuFlyoutPresenterAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IMenuFlyoutPresenterAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IMenuFlyoutPresenterAutomationPeer">
DEFINE_IIDX(IMenuFlyoutPresenterAutomationPeer, "E244A871-FCBB-48FC-8A93-41EA134B53CE")

.comdef IMenuFlyoutPresenterAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMenuFlyoutPresenterAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIMenuFlyoutPresenterAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IMenuFlyoutPresenterAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IMenuFlyoutPresenterAutomationPeerFactory">
DEFINE_IIDX(IMenuFlyoutPresenterAutomationPeerFactory, "07B5172D-761D-452B-9E6D-FA2A8BE0AD26")

.comdef IMenuFlyoutPresenterAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISearchBoxAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISearchBoxAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISearchBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ISearchBoxAutomationPeer">
DEFINE_IIDX(ISearchBoxAutomationPeer, "854011A4-18A6-4F30-939B-8871AFA3F5E9")

.comdef ISearchBoxAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISearchBoxAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CISearchBoxAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ISearchBoxAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ISearchBoxAutomationPeerFactory">
DEFINE_IIDX(ISearchBoxAutomationPeerFactory, "B3C01430-7FAA-41BB-8E91-7C761C5267F1")

.comdef ISearchBoxAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITimePickerAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITimePickerAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ITimePickerAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ITimePickerAutomationPeer">
DEFINE_IIDX(ITimePickerAutomationPeer, "A43D44EF-3285-4DF7-B4A4-E4CDF36A3A17")

.comdef ITimePickerAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITimePickerAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CITimePickerAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_ITimePickerAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.ITimePickerAutomationPeerFactory">
DEFINE_IIDX(ITimePickerAutomationPeerFactory, "978F6671-47F8-40A7-9E21-68128B16B4FD")

.comdef ITimePickerAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleMenuFlyoutItemAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleMenuFlyoutItemAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IToggleMenuFlyoutItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IToggleMenuFlyoutItemAutomationPeer">
DEFINE_IIDX(IToggleMenuFlyoutItemAutomationPeer, "6B57EAFE-6AF1-4903-8373-3437BF352345")

.comdef IToggleMenuFlyoutItemAutomationPeer : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleMenuFlyoutItemAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIToggleMenuFlyoutItemAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IToggleMenuFlyoutItemAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IToggleMenuFlyoutItemAutomationPeerFactory">
DEFINE_IIDX(IToggleMenuFlyoutItemAutomationPeerFactory, "94364B77-8F6C-4837-AAE3-94D010D8D162")

.comdef IToggleMenuFlyoutItemAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IAutomationPeer">
DEFINE_IIDX(IAutomationPeer, "35AAC87A-62EE-4D3E-A24C-2BC8432D68B7")

.comdef IAutomationPeer : public IInspectable

    get_EventsSource	proc :ptr
    put_EventsSource	proc :ptr
    GetPattern		proc :Windows::UI::Xaml::Automation::Peers::PatternInterface, :ptr
    RaiseAutomationEvent proc :Windows::UI::Xaml::Automation::Peers::AutomationEvents
    RaisePropertyChangedEvent proc :ptr, :ptr, :ptr
    GetAcceleratorKey	proc :ptr
    GetAccessKey	proc :ptr
    GetAutomationControlType proc :ptr
    GetAutomationId	proc :ptr
    GetBoundingRectangle proc :ptr
    GetChildren		proc :ptr
    GetClassName	proc :ptr
    GetClickablePoint	proc :ptr
    GetHelpText		proc :ptr
    GetItemStatus	proc :ptr
    GetItemType		proc :ptr
    GetLabeledBy	proc :ptr
    GetLocalizedControlType proc :ptr
    GetName		proc :ptr
    GetOrientation	proc :ptr
    HasKeyboardFocus	proc :ptr
    IsContentElement	proc :ptr
    IsControlElement	proc :ptr
    IsEnabled		proc :ptr
    IsKeyboardFocusable proc :ptr
    IsOffscreen		proc :ptr
    IsPassword		proc :ptr
    IsRequiredForForm	proc :ptr
    SetFocus		proc
    GetParent		proc :ptr
    InvalidatePeer	proc
    GetPeerFromPoint	proc :Windows::Foundation::Point, :ptr
    GetLiveSetting	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAutomationPeerOverrides <L"Windows.UI.Xaml.Automation.Peers.IAutomationPeerOverrides">
DEFINE_IIDX(IAutomationPeerOverrides, "BEA93E67-DBEE-4F7B-AF0D-A79AAE5333BF")

.comdef IAutomationPeerOverrides : public IInspectable

    GetPatternCore	proc :Windows::UI::Xaml::Automation::Peers::PatternInterface, :ptr
    GetAcceleratorKeyCore proc :ptr
    GetAccessKeyCore	proc :ptr
    GetAutomationControlTypeCore proc :ptr
    GetAutomationIdCore proc :ptr
    GetBoundingRectangleCore proc :ptr
    GetChildrenCore	proc :ptr
    GetClassNameCore	proc :ptr
    GetClickablePointCore proc :ptr
    GetHelpTextCore	proc :ptr
    GetItemStatusCore	proc :ptr
    GetItemTypeCore	proc :ptr
    GetLabeledByCore	proc :ptr
    GetLocalizedControlTypeCore proc :ptr
    GetNameCore		proc :ptr
    GetOrientationCore	proc :ptr
    HasKeyboardFocusCore proc :ptr
    IsContentElementCore proc :ptr
    IsControlElementCore proc :ptr
    IsEnabledCore	proc :ptr
    IsKeyboardFocusableCore proc :ptr
    IsOffscreenCore	proc :ptr
    IsPasswordCore	proc :ptr
    IsRequiredForFormCore proc :ptr
    SetFocusCore	proc
    GetPeerFromPointCore proc :Windows::Foundation::Point, :ptr
    GetLiveSettingCore	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerProtected_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerProtected_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAutomationPeerProtected <L"Windows.UI.Xaml.Automation.Peers.IAutomationPeerProtected">
DEFINE_IIDX(IAutomationPeerProtected, "F4B40E52-642F-4629-A54A-EA5D2349C448")

.comdef IAutomationPeerProtected : public IInspectable

    PeerFromProvider	proc :ptr, :ptr
    ProviderFromPeer	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAutomationPeerStatics <L"Windows.UI.Xaml.Automation.Peers.IAutomationPeerStatics">
DEFINE_IIDX(IAutomationPeerStatics, "562F7FB0-A331-4A9C-9DEC-BFB7586FFFFF")

.comdef IAutomationPeerStatics : public IInspectable

    ListenerExists	proc :Windows::UI::Xaml::Automation::Peers::AutomationEvents, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IAutomationPeerFactory">
DEFINE_IIDX(IAutomationPeerFactory, "20C27545-A88B-43C8-BC24-CEA9DAFD04A3")

.comdef IAutomationPeerFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeer2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeer2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAutomationPeer2 <L"Windows.UI.Xaml.Automation.Peers.IAutomationPeer2">
DEFINE_IIDX(IAutomationPeer2, "EA1F89C7-EBF5-4AB8-88F7-680D821DAC61")

.comdef IAutomationPeer2 : public IInspectable

    ShowContextMenu	proc
    GetControlledPeers	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerOverrides2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIAutomationPeerOverrides2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IAutomationPeerOverrides2 <L"Windows.UI.Xaml.Automation.Peers.IAutomationPeerOverrides2">
DEFINE_IIDX(IAutomationPeerOverrides2, "2603682A-9DA6-4023-B496-496E5EF228D2")

.comdef IAutomationPeerOverrides2 : public IInspectable

    ShowContextMenuCore proc
    GetControlledPeersCore proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFrameworkElementAutomationPeer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFrameworkElementAutomationPeer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFrameworkElementAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.IFrameworkElementAutomationPeer">
DEFINE_IIDX(IFrameworkElementAutomationPeer, "B90AD781-BFEB-4451-BD47-9F3A63EBD24A")

.comdef IFrameworkElementAutomationPeer : public IInspectable

    get_Owner		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFrameworkElementAutomationPeerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFrameworkElementAutomationPeerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFrameworkElementAutomationPeerStatics <L"Windows.UI.Xaml.Automation.Peers.IFrameworkElementAutomationPeerStatics">
DEFINE_IIDX(IFrameworkElementAutomationPeerStatics, "B9C0B997-2820-44A1-A5A8-9B801EDC269E")

.comdef IFrameworkElementAutomationPeerStatics : public IInspectable

    FromElement		proc :ptr, :ptr
    CreatePeerForElement proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFrameworkElementAutomationPeerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CAutomation_CPeers_CIFrameworkElementAutomationPeerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Automation_Peers_IFrameworkElementAutomationPeerFactory <L"Windows.UI.Xaml.Automation.Peers.IFrameworkElementAutomationPeerFactory">
DEFINE_IIDX(IFrameworkElementAutomationPeerFactory, "0DB9B8BC-B812-48E3-AF1F-DBC57600C325")

.comdef IFrameworkElementAutomationPeerFactory : public IInspectable

    CreateInstanceWithOwner proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_AutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_AutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_AutomationPeer <L"Windows.UI.Xaml.Automation.Peers.AutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FrameworkElementAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FrameworkElementAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_FrameworkElementAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.FrameworkElementAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ButtonBaseAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ButtonBaseAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ButtonBaseAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ButtonBaseAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_CaptureElementAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_CaptureElementAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_CaptureElementAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.CaptureElementAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ComboBoxItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ComboBoxItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ComboBoxItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ComboBoxItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FlipViewItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FlipViewItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_FlipViewItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.FlipViewItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GridViewItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GridViewItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_GridViewItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.GridViewItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GroupItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GroupItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_GroupItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.GroupItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ImageAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ImageAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ImageAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ImageAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListBoxItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListBoxItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListBoxItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListBoxItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListViewItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListViewItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_MediaElementAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_MediaElementAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_MediaElementAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.MediaElementAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_PasswordBoxAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_PasswordBoxAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_PasswordBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.PasswordBoxAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ProgressRingAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ProgressRingAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ProgressRingAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ProgressRingAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RichEditBoxAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RichEditBoxAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_RichEditBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.RichEditBoxAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RichTextBlockAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RichTextBlockAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_RichTextBlockAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.RichTextBlockAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RichTextBlockOverflowAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RichTextBlockOverflowAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_RichTextBlockOverflowAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.RichTextBlockOverflowAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SettingsFlyoutAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SettingsFlyoutAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_SettingsFlyoutAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.SettingsFlyoutAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_TextBlockAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_TextBlockAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_TextBlockAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.TextBlockAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_TextBoxAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_TextBoxAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_TextBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.TextBoxAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ThumbAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ThumbAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ThumbAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ThumbAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_DatePickerAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_DatePickerAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_DatePickerAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.DatePickerAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FlyoutPresenterAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FlyoutPresenterAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_FlyoutPresenterAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.FlyoutPresenterAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_HubAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_HubAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_HubAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.HubAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_HubSectionAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_HubSectionAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_HubSectionAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.HubSectionAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewBaseHeaderItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewBaseHeaderItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListViewBaseHeaderItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListViewBaseHeaderItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GridViewHeaderItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GridViewHeaderItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_GridViewHeaderItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.GridViewHeaderItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewHeaderItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewHeaderItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListViewHeaderItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListViewHeaderItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SearchBoxAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SearchBoxAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_SearchBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.SearchBoxAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_TimePickerAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_TimePickerAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_TimePickerAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.TimePickerAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ButtonAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ButtonAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ButtonAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_HyperlinkButtonAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_HyperlinkButtonAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_HyperlinkButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.HyperlinkButtonAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RepeatButtonAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RepeatButtonAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_RepeatButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.RepeatButtonAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_AppBarButtonAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_AppBarButtonAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_AppBarButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.AppBarButtonAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_MenuFlyoutItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_MenuFlyoutItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_MenuFlyoutItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.MenuFlyoutItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ItemsControlAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ItemsControlAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ItemsControlAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ItemsControlAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_MenuFlyoutPresenterAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_MenuFlyoutPresenterAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_MenuFlyoutPresenterAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.MenuFlyoutPresenterAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RangeBaseAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RangeBaseAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_RangeBaseAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.RangeBaseAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ProgressBarAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ProgressBarAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ProgressBarAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ProgressBarAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ScrollBarAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ScrollBarAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ScrollBarAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ScrollBarAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SliderAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SliderAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_SliderAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.SliderAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ScrollViewerAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ScrollViewerAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ScrollViewerAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ScrollViewerAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SelectorAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SelectorAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_SelectorAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.SelectorAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FlipViewAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FlipViewAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_FlipViewAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.FlipViewAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListBoxAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListBoxAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListBoxAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewBaseAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewBaseAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListViewBaseAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListViewBaseAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GridViewAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GridViewAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_GridViewAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.GridViewAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListViewAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListViewAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SemanticZoomAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SemanticZoomAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_SemanticZoomAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.SemanticZoomAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ToggleButtonAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ToggleButtonAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ToggleButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ToggleButtonAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_CheckBoxAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_CheckBoxAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_CheckBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.CheckBoxAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RadioButtonAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_RadioButtonAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_RadioButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.RadioButtonAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ToggleSwitchAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ToggleSwitchAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ToggleSwitchAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ToggleSwitchAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_AppBarAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_AppBarAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_AppBarAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.AppBarAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_AppBarToggleButtonAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_AppBarToggleButtonAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_AppBarToggleButtonAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.AppBarToggleButtonAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ToggleMenuFlyoutItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ToggleMenuFlyoutItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ToggleMenuFlyoutItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ToggleMenuFlyoutItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ComboBoxAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ComboBoxAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ComboBoxAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ComboBoxAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SelectorItemAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_SelectorItemAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_SelectorItemAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.SelectorItemAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ComboBoxItemDataAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ComboBoxItemDataAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ComboBoxItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ComboBoxItemDataAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FlipViewItemDataAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_FlipViewItemDataAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_FlipViewItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.FlipViewItemDataAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GridViewItemDataAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_GridViewItemDataAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_GridViewItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.GridViewItemDataAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListBoxItemDataAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListBoxItemDataAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListBoxItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListBoxItemDataAutomationPeer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewItemDataAutomationPeer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Automation_Peers_ListViewItemDataAutomationPeer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Automation_Peers_ListViewItemDataAutomationPeer <L"Windows.UI.Xaml.Automation.Peers.ListViewItemDataAutomationPeer">
endif

endif
