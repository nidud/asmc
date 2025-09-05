ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Epopups_h__
define __windows2Eui2Epopups_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

ifndef ____FIIterator_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CUI__CPopups__CIUICommand, "f45db3d3-7299-57ce-a73e-297cf0af3083")

.comdef __FIIterator_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CUI__CPopups__CIUICommand, "e63de42b-53c3-5e07-90d3-98172d545412")

.comdef __FIIterable_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    First proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CPopups__CIUICommand, "ed1165e6-f377-5b00-8172-93c1bd04deb4")

.comdef __FIVectorView_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    GetAt	proc :SINT, :ptr
    get_Size	proc :ptr
    IndexOf	proc :ptr, :ptr, :ptr
    GetMany	proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CUI__CPopups__CIUICommand, "105139a1-dcb8-5f65-97ef-cb1bf0b75f9d")

.comdef __FIVector_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    GetAt	proc :SINT, :ptr
    get_Size	proc :ptr
    GetView	proc :ptr
    IndexOf	proc :ptr, :ptr, :ptr
    SetAt	proc :UINT, :ptr
    InsertAt	proc :UINT, :ptr
    RemoveAt	proc :UINT
    Append	proc :ptr
    RemoveAtEnd proc
    Clear	proc
    GetMany	proc :UINT, :UINT, :ptr, :ptr
    ReplaceAll	proc :UINT, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand, "dd33fd5b-a24d-5a44-91fe-dd6441770103")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand : public IUnknown

    _Invoke proc :ptr, :LONG
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand, "b8770535-6a4b-52b1-b578-f3cdc5007a1f")

.comdef __FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    put_Completed proc :ptr
    get_Completed proc :ptr
    GetResults proc :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Popups

.enum MessageDialogOptions {
    }

.enum MessageDialogOptions {

    MessageDialogOptions_None,
    MessageDialogOptions_AcceptUserInputAfterDelay
    }

.enum Placement {

    Placement_Default,
    Placement_Above,
    Placement_Below,
    Placement_Left,
    Placement_Right
    }


ifndef ____x_ABI_CWindows_CUI_CPopups_CIUICommandInvokedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIUICommandInvokedHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IUICommandInvokedHandler, "DAF77A4F-C27A-4298-9AC6-2922C45E7DA6")

.comdef IUICommandInvokedHandler : public IUnknown

    _Invoke proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIMessageDialog_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIMessageDialog_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IMessageDialog <L"Windows.UI.Popups.IMessageDialog">

DEFINE_IIDX(IMessageDialog, "33F59B01-5325-43AB-9AB3-BDAE440E4121")

.comdef IMessageDialog : public IInspectable

    get_Title proc :ptr
    put_Title proc :HSTRING
    get_Commands proc :ptr
    get_DefaultCommandIndex proc :ptr
    put_DefaultCommandIndex proc :UINT32
    get_CancelCommandIndex proc :ptr
    put_CancelCommandIndex proc :UINT32
    get_Content proc :ptr
    put_Content proc :HSTRING
    ShowAsync proc :ptr
    get_Options proc :ptr
    put_Options proc :SINT
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIMessageDialogFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIMessageDialogFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IMessageDialogFactory <L"Windows.UI.Popups.IMessageDialogFactory">

DEFINE_IIDX(IMessageDialogFactory, "2D161777-A66F-4EA5-BB87-793FFA4941F2")

.comdef IMessageDialogFactory : public IInspectable

    Create proc :HSTRING, :ptr
    CreateWithTitle proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIUICommand_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIUICommand_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IUICommand <L"Windows.UI.Popups.IUICommand">

DEFINE_IIDX(IUICommand, "4FF93A75-4145-47FF-AC7F-DFF1C1FA5B0F")

.comdef IUICommand : public IInspectable

    get_Label proc :ptr
    put_Label proc :HSTRING
    get_Invoked proc :ptr
    put_Invoked proc :ptr
    get_Id proc :ptr
    put_Id proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIUICommandFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIUICommandFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IUICommandFactory <L"Windows.UI.Popups.IUICommandFactory">

DEFINE_IIDX(IUICommandFactory, "A21A8189-26B0-4676-AE94-54041BC125E8")

.comdef IUICommandFactory : public IInspectable

    Create proc :HSTRING, :ptr
    CreateWithHandler proc :HSTRING, :ptr, :ptr
    CreateWithHandlerAndId proc :HSTRING, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIPopupMenu_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIPopupMenu_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IPopupMenu <L"Windows.UI.Popups.IPopupMenu">

DEFINE_IIDX(IPopupMenu, "4E9BC6DC-880D-47FC-A0A1-72B639E62559")

.comdef IPopupMenu : public IInspectable

    get_Commands proc :ptr
    ShowAsync proc :ptr, :ptr
    ShowAsyncWithRect proc :ptr, :ptr
    ShowAsyncWithRectAndPlacement proc :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

define RuntimeClass_Windows_UI_Popups_MessageDialog <L"Windows.UI.Popups.MessageDialog">
define RuntimeClass_Windows_UI_Popups_UICommand <L"Windows.UI.Popups.UICommand">
define RuntimeClass_Windows_UI_Popups_UICommandSeparator <L"Windows.UI.Popups.UICommandSeparator">
define RuntimeClass_Windows_UI_Popups_PopupMenu <L"Windows.UI.Popups.PopupMenu">

endif
