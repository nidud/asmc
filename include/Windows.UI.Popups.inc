ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif

ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eui2Epopups_h__
define __windows2Eui2Epopups_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

include windows.foundation.collections.inc

ifndef DEF___FIIterator_1_Windows__CUI__CPopups__CIUICommand
define DEF___FIIterator_1_Windows__CUI__CPopups__CIUICommand

ifndef ____FIIterator_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CUI__CPopups__CIUICommand, "f45db3d3-7299-57ce-a73e-297cf0af3083")

.comdef __FIIterator_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    get_Current		proc :ptr ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr ptr, :ptr
   .ends

endif

endif


ifndef DEF___FIIterable_1_Windows__CUI__CPopups__CIUICommand
define DEF___FIIterable_1_Windows__CUI__CPopups__CIUICommand

ifndef ____FIIterable_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CUI__CPopups__CIUICommand, "e63de42b-53c3-5e07-90d3-98172d545412")

.comdef __FIIterable_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    First proc :ptr ptr
   .ends

endif

endif


ifndef DEF___FIVectorView_1_Windows__CUI__CPopups__CIUICommand
define DEF___FIVectorView_1_Windows__CUI__CPopups__CIUICommand

ifndef ____FIVectorView_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CPopups__CIUICommand, "ed1165e6-f377-5b00-8172-93c1bd04deb4")

.comdef __FIVectorView_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    GetAt	proc :SINT, :ptr ptr
    get_Size	proc :ptr
    IndexOf	proc :ptr, :ptr, :ptr
    GetMany	proc :SINT, :SINT, :ptr ptr, :ptr
   .ends

endif

endif


ifndef DEF___FIVector_1_Windows__CUI__CPopups__CIUICommand
define DEF___FIVector_1_Windows__CUI__CPopups__CIUICommand

ifndef ____FIVector_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CUI__CPopups__CIUICommand, "105139a1-dcb8-5f65-97ef-cb1bf0b75f9d")

.comdef __FIVector_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    GetAt	proc :SINT, :ptr ptr
    get_Size	proc :ptr
    GetView	proc :ptr ptr
    IndexOf	proc :ptr, :ptr, :ptr
    SetAt	proc :UINT, :ptr
    InsertAt	proc :UINT, :ptr
    RemoveAt	proc :UINT
    Append	proc :ptr
    RemoveAtEnd proc
    Clear	proc
    GetMany	proc :UINT, :UINT, :ptr ptr, :ptr
    ReplaceAll	proc :UINT, :ptr ptr
   .ends

endif

endif

ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand
define DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand, "dd33fd5b-a24d-5a44-91fe-dd6441770103")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CUI__CPopups__CIUICommand : public IUnknown

    _Invoke proc :ptr, :LONG
   .ends

endif

endif

ifndef DEF___FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand
define DEF___FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand

ifndef ____FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand, "b8770535-6a4b-52b1-b578-f3cdc5007a1f")

.comdef __FIAsyncOperation_1_Windows__CUI__CPopups__CIUICommand : public IInspectable

    put_Completed proc :ptr
    get_Completed proc :ptr ptr
    GetResults proc :ptr ptr
   .ends

endif

endif

.namespace ABI
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
define InterfaceName_Windows_UI_Popups_IMessageDialog <L"Windows.UI.Popups.IMessageDialog">
endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIMessageDialog_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIMessageDialog_INTERFACE_DEFINED__

DEFINE_IIDX(IMessageDialog, "33F59B01-5325-43AB-9AB3-BDAE440E4121")

.comdef IMessageDialog : public IInspectable

    get_Title proc :ptr
    put_Title proc :HSTRING
    get_Commands proc :ptr ptr
    get_DefaultCommandIndex proc :ptr
    put_DefaultCommandIndex proc :UINT32
    get_CancelCommandIndex proc :ptr
    put_CancelCommandIndex proc :UINT32
    get_Content proc :ptr
    put_Content proc :HSTRING
    ShowAsync proc :ptr ptr
    get_Options proc :ptr
    put_Options proc :SINT
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIMessageDialogFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IMessageDialogFactory <L"Windows.UI.Popups.IMessageDialogFactory">
endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIMessageDialogFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIMessageDialogFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IMessageDialogFactory, "2D161777-A66F-4EA5-BB87-793FFA4941F2")

.comdef IMessageDialogFactory : public IInspectable

    Create proc :HSTRING, :ptr ptr
    CreateWithTitle proc :HSTRING, :HSTRING, :ptr ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIUICommand_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IUICommand <L"Windows.UI.Popups.IUICommand">
endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIUICommand_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIUICommand_INTERFACE_DEFINED__

DEFINE_IIDX(IUICommand, "4FF93A75-4145-47FF-AC7F-DFF1C1FA5B0F")

.comdef IUICommand : public IInspectable

    get_Label proc :ptr
    put_Label proc :HSTRING
    get_Invoked proc :ptr ptr
    put_Invoked proc :ptr
    get_Id proc :ptr ptr
    put_Id proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIUICommandFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IUICommandFactory <L"Windows.UI.Popups.IUICommandFactory">
endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIUICommandFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIUICommandFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IUICommandFactory, "A21A8189-26B0-4676-AE94-54041BC125E8")

.comdef IUICommandFactory : public IInspectable

    Create proc :HSTRING, :ptr ptr
    CreateWithHandler proc :HSTRING, :ptr, :ptr ptr
    CreateWithHandlerAndId proc :HSTRING, :ptr, :ptr, :ptr ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIPopupMenu_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Popups_IPopupMenu <L"Windows.UI.Popups.IPopupMenu">
endif

ifndef ____x_ABI_CWindows_CUI_CPopups_CIPopupMenu_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CPopups_CIPopupMenu_INTERFACE_DEFINED__

DEFINE_IIDX(IPopupMenu, "4E9BC6DC-880D-47FC-A0A1-72B639E62559")

.comdef IPopupMenu : public IInspectable

    get_Commands proc :ptr ptr
    ShowAsync proc :ptr, :ptr ptr
    ShowAsyncWithRect proc :ptr, :ptr ptr
    ShowAsyncWithRectAndPlacement proc :ptr, :ptr, :ptr ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Popups_MessageDialog_DEFINED
define RUNTIMECLASS_Windows_UI_Popups_MessageDialog_DEFINED
define RuntimeClass_Windows_UI_Popups_MessageDialog <L"Windows.UI.Popups.MessageDialog">
endif
ifndef RUNTIMECLASS_Windows_UI_Popups_UICommand_DEFINED
define RUNTIMECLASS_Windows_UI_Popups_UICommand_DEFINED
define RuntimeClass_Windows_UI_Popups_UICommand <L"Windows.UI.Popups.UICommand">
endif
ifndef RUNTIMECLASS_Windows_UI_Popups_UICommandSeparator_DEFINED
define RUNTIMECLASS_Windows_UI_Popups_UICommandSeparator_DEFINED
define RuntimeClass_Windows_UI_Popups_UICommandSeparator <L"Windows.UI.Popups.UICommandSeparator">
endif
ifndef RUNTIMECLASS_Windows_UI_Popups_PopupMenu_DEFINED
define RUNTIMECLASS_Windows_UI_Popups_PopupMenu_DEFINED
define RuntimeClass_Windows_UI_Popups_PopupMenu <L"Windows.UI.Popups.PopupMenu">
endif

HSTRING_UserSize	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr ULONG, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr ULONG, :ptr HSTRING

endif
