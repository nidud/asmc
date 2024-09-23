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

ifndef __windows2Estorage2Epickers2Eprovider_h__
define __windows2Estorage2Epickers2Eprovider_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include windows.foundation.collections.inc

ifndef ____FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileOpenPickerUI_Windows__CStorage__CPickers__CProvider__CFileRemovedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileOpenPickerUI_Windows__CStorage__CPickers__CProvider__CFileRemovedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileOpenPickerUI_Windows__CStorage__CPickers__CProvider__CFileRemovedEventArgs, "f1fb2939-695b-5f56-841a-a52a7d148572")

.comdef __FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileOpenPickerUI_Windows__CStorage__CPickers__CProvider__CFileRemovedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileOpenPickerUI_Windows__CStorage__CPickers__CProvider__CPickerClosingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileOpenPickerUI_Windows__CStorage__CPickers__CProvider__CPickerClosingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileOpenPickerUI_Windows__CStorage__CPickers__CProvider__CPickerClosingEventArgs, "2b06bdac-983b-5552-b5c9-b0990a2db3a1")

.comdef __FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileOpenPickerUI_Windows__CStorage__CPickers__CProvider__CPickerClosingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileSavePickerUI_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileSavePickerUI_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileSavePickerUI_IInspectable, "f1e6a632-f97f-54d9-9e1b-a714edc3ff06")

.comdef __FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileSavePickerUI_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileSavePickerUI_Windows__CStorage__CPickers__CProvider__CTargetFileRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileSavePickerUI_Windows__CStorage__CPickers__CProvider__CTargetFileRequestedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileSavePickerUI_Windows__CStorage__CPickers__CProvider__CTargetFileRequestedEventArgs, "d3e1f8c7-45c5-5249-b336-a111bfaa985b")

.comdef __FITypedEventHandler_2_Windows__CStorage__CPickers__CProvider__CFileSavePickerUI_Windows__CStorage__CPickers__CProvider__CTargetFileRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace Windows
.namespace Storage
.namespace Pickers
.namespace Provider

.enum AddFileResult {
    AddFileResult_Added,
    AddFileResult_AlreadyAdded,
    AddFileResult_NotAllowed,
    AddFileResult_Unavailable
    }


.enum FileSelectionMode {
    FileSelectionMode_Single,
    FileSelectionMode_Multiple
    }

.enum SetFileNameResult {
    SetFileNameResult_Succeeded,
    SetFileNameResult_NotAllowed,
    SetFileNameResult_Unavailable
    }

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIFileRemovedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIFileRemovedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_IFileRemovedEventArgs <L"Windows.Storage.Pickers.Provider.IFileRemovedEventArgs">

DEFINE_IIDX(IFileRemovedEventArgs, "13043DA7-7FCA-4C2B-9ECA-6890F9F00185")

.comdef IFileRemovedEventArgs : public IInspectable

    get_Id		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIFileOpenPickerUI_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIFileOpenPickerUI_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_IFileOpenPickerUI <L"Windows.Storage.Pickers.Provider.IFileOpenPickerUI">

DEFINE_IIDX(IFileOpenPickerUI, "DDA45A10-F9D4-40C4-8AF5-C5B6B5A61D1D")

.comdef IFileOpenPickerUI : public IInspectable

    AddFile		proc :HSTRING, :ptr, :ptr
    RemoveFile		proc :HSTRING
    ContainsFile	proc :HSTRING, :ptr
    CanAddFile		proc :ptr, :ptr
    get_AllowedFileTypes proc :ptr
    get_SelectionMode	proc :ptr
    get_SettingsIdentifier proc :ptr
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    add_FileRemoved	proc :ptr, :ptr
    remove_FileRemoved	proc :EventRegistrationToken
    add_Closing		proc :ptr, :ptr
    remove_Closing	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIPickerClosingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIPickerClosingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_IPickerClosingEventArgs <L"Windows.Storage.Pickers.Provider.IPickerClosingEventArgs">

DEFINE_IIDX(IPickerClosingEventArgs, "7E59F224-B332-4F12-8B9F-A8C2F06B32CD")

.comdef IPickerClosingEventArgs : public IInspectable

    get_ClosingOperation proc :ptr
    get_IsCanceled	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIPickerClosingOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIPickerClosingOperation_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_IPickerClosingOperation <L"Windows.Storage.Pickers.Provider.IPickerClosingOperation">

DEFINE_IIDX(IPickerClosingOperation, "4CE9FB84-BEEE-4E39-A773-FC5F0EAE328D")

.comdef IPickerClosingOperation : public IInspectable

    GetDeferral		proc :ptr
    get_Deadline	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIPickerClosingDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIPickerClosingDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_IPickerClosingDeferral <L"Windows.Storage.Pickers.Provider.IPickerClosingDeferral">

DEFINE_IIDX(IPickerClosingDeferral, "7AF7F71E-1A67-4A31-AE80-E907708A619B")

.comdef IPickerClosingDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIFileSavePickerUI_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CIFileSavePickerUI_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_IFileSavePickerUI <L"Windows.Storage.Pickers.Provider.IFileSavePickerUI">

DEFINE_IIDX(IFileSavePickerUI, "9656C1E7-3E56-43CC-8A39-33C73D9D542B")

.comdef IFileSavePickerUI : public IInspectable

    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_AllowedFileTypes proc :ptr
    get_SettingsIdentifier proc :ptr
    get_FileName	proc :ptr
    TrySetFileName	proc :HSTRING, :ptr
    add_FileNameChanged proc :ptr, :ptr
    remove_FileNameChanged proc :EventRegistrationToken
    add_TargetFileRequested proc :ptr, :ptr
    remove_TargetFileRequested proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CITargetFileRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CITargetFileRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_ITargetFileRequestedEventArgs <L"Windows.Storage.Pickers.Provider.ITargetFileRequestedEventArgs">

DEFINE_IIDX(ITargetFileRequestedEventArgs, "B163DBC1-1B51-4C89-A591-0FD40B3C57C9")

.comdef ITargetFileRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CITargetFileRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CITargetFileRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_ITargetFileRequest <L"Windows.Storage.Pickers.Provider.ITargetFileRequest">

DEFINE_IIDX(ITargetFileRequest, "42BD3355-7F88-478B-8E81-690B20340678")

.comdef ITargetFileRequest : public IInspectable

    get_TargetFile	proc :ptr
    put_TargetFile	proc :ptr
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CPickers_CProvider_CITargetFileRequestDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CPickers_CProvider_CITargetFileRequestDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Pickers_Provider_ITargetFileRequestDeferral <L"Windows.Storage.Pickers.Provider.ITargetFileRequestDeferral">

DEFINE_IIDX(ITargetFileRequestDeferral, "4AEE9D91-BF15-4DA9-95F6-F6B7D558225B")

.comdef ITargetFileRequestDeferral : public IInspectable

    Complete		proc
   .ends

endif

.endn
.endn
.endn
.endn

define RuntimeClass_Windows_Storage_Pickers_Provider_FileRemovedEventArgs <L"Windows.Storage.Pickers.Provider.FileRemovedEventArgs">
define RuntimeClass_Windows_Storage_Pickers_Provider_FileOpenPickerUI <L"Windows.Storage.Pickers.Provider.FileOpenPickerUI">
define RuntimeClass_Windows_Storage_Pickers_Provider_PickerClosingEventArgs <L"Windows.Storage.Pickers.Provider.PickerClosingEventArgs">
define RuntimeClass_Windows_Storage_Pickers_Provider_PickerClosingOperation <L"Windows.Storage.Pickers.Provider.PickerClosingOperation">
define RuntimeClass_Windows_Storage_Pickers_Provider_PickerClosingDeferral <L"Windows.Storage.Pickers.Provider.PickerClosingDeferral">
define RuntimeClass_Windows_Storage_Pickers_Provider_FileSavePickerUI <L"Windows.Storage.Pickers.Provider.FileSavePickerUI">
define RuntimeClass_Windows_Storage_Pickers_Provider_TargetFileRequestedEventArgs <L"Windows.Storage.Pickers.Provider.TargetFileRequestedEventArgs">
define RuntimeClass_Windows_Storage_Pickers_Provider_TargetFileRequest <L"Windows.Storage.Pickers.Provider.TargetFileRequest">
define RuntimeClass_Windows_Storage_Pickers_Provider_TargetFileRequestDeferral <L"Windows.Storage.Pickers.Provider.TargetFileRequestDeferral">

HSTRING_UserSize	proto WINAPI :ptr, :DWORD, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :DWORD, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif
