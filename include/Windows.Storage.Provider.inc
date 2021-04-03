ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __windows2Estorage2Eprovider_h__
__windows2Estorage2Eprovider_h__ equ 1

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CProvider__CFileUpdateStatus_FWD_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CProvider__CFileUpdateStatus_FWD_DEFINED__ equ 1
endif
ifndef ____FIAsyncOperation_1_Windows__CStorage__CProvider__CFileUpdateStatus_FWD_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CProvider__CFileUpdateStatus_FWD_DEFINED__ equ 1
endif
ifndef ____FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_IInspectable_FWD_DEFINED__
____FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_IInspectable_FWD_DEFINED__ equ 1
endif
ifndef ____FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_Windows__CStorage__CProvider__CFileUpdateRequestedEventArgs_FWD_DEFINED__
____FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_Windows__CStorage__CProvider__CFileUpdateRequestedEventArgs_FWD_DEFINED__ equ 1
endif
ifndef __ICachedFileUpdaterUI_FWD_DEFINED__
__ICachedFileUpdaterUI_FWD_DEFINED__ equ 1
endif
ifndef __IFileUpdateRequestedEventArgs_FWD_DEFINED__
__IFileUpdateRequestedEventArgs_FWD_DEFINED__ equ 1
endif
ifndef __IFileUpdateRequest_FWD_DEFINED__
__IFileUpdateRequest_FWD_DEFINED__ equ 1
endif
ifndef __IFileUpdateRequestDeferral_FWD_DEFINED__
__IFileUpdateRequestDeferral_FWD_DEFINED__ equ 1
endif
ifndef __ICachedFileUpdaterStatics_FWD_DEFINED__
__ICachedFileUpdaterStatics_FWD_DEFINED__ equ 1
endif

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include windows.foundation.collections.inc

FileUpdateStatus typedef LONG

ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CProvider__CFileUpdateStatus_USE
DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CProvider__CFileUpdateStatus_USE equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CProvider__CFileUpdateStatus, "bb185a07-0285-5f37-9c7d-2fc6a3e0e6e5")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CProvider__CFileUpdateStatus : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CProvider__CFileUpdateStatus_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CProvider__CFileUpdateStatus_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CProvider__CFileUpdateStatus, "8f0f439e-87d0-531f-85b1-54f4528f29c3")

.comdef __FIAsyncOperation_1_Windows__CStorage__CProvider__CFileUpdateStatus : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :LONG
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_IInspectable_INTERFACE_DEFINED__
____FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_IInspectable_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_IInspectable, "45fdd443-c0b9-57b0-a84f-7d876edc3149")

.comdef __FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_Windows__CStorage__CProvider__CFileUpdateRequestedEventArgs_INTERFACE_DEFINED__
____FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_Windows__CStorage__CProvider__CFileUpdateRequestedEventArgs_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_Windows__CStorage__CProvider__CFileUpdateRequestedEventArgs, "ed56ab72-ebd3-52c8-b0ac-987d30090351")

.comdef __FITypedEventHandler_2_Windows__CStorage__CProvider__CCachedFileUpdaterUI_Windows__CStorage__CProvider__CFileUpdateRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.enum _x_ABI_CWindows_CStorage_CProvider_CCachedFileTarget {
    CachedFileTarget_Local	= 0,
    CachedFileTarget_Remote	= 1
    }

.enum _x_ABI_CWindows_CStorage_CProvider_CUIStatus {
    UIStatus_Unavailable	= 0,
    UIStatus_Hidden	= 1,
    UIStatus_Visible	= 2,
    UIStatus_Complete	= 3
    }

.enum _x_ABI_CWindows_CStorage_CProvider_CFileUpdateStatus {
    FileUpdateStatus_Incomplete = 0,
    FileUpdateStatus_Complete	= 1,
    FileUpdateStatus_UserInputNeeded	= 2,
    FileUpdateStatus_CurrentlyUnavailable	= 3,
    FileUpdateStatus_Failed	= 4,
    FileUpdateStatus_CompleteAndRenamed = 5
    }

.enum _x_ABI_CWindows_CStorage_CProvider_CCachedFileOptions {
    CachedFileOptions_None	= 0,
    CachedFileOptions_RequireUpdateOnAccess	= 0x1,
    CachedFileOptions_UseCachedFileWhenOffline	= 0x2,
    CachedFileOptions_DenyAccessWhenOffline	= 0x4
    }

.enum _x_ABI_CWindows_CStorage_CProvider_CReadActivationMode {
    ReadActivationMode_NotNeeded	= 0,
    ReadActivationMode_BeforeAccess	= 1
    }

.enum _x_ABI_CWindows_CStorage_CProvider_CWriteActivationMode {
    WriteActivationMode_ReadOnly	= 0,
    WriteActivationMode_NotNeeded	= 1,
    WriteActivationMode_AfterWrite	= 2
    }


ifndef __ICachedFileUpdaterUI_INTERFACE_DEFINED__
__ICachedFileUpdaterUI_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICachedFileUpdaterUI, "9E6F41E6-BAF2-4A97-B600-9333F5DF80FD")

.comdef ICachedFileUpdaterUI : public IInspectable

    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_UpdateTarget	proc :ptr
    add_FileUpdateRequested proc :ptr, :ptr
    remove_FileUpdateRequested proc :EventRegistrationToken
    add_UIRequested	proc :ptr, :ptr
    remove_UIRequested	proc :EventRegistrationToken
    get_UIStatus	proc :ptr
    .ends

endif

ifndef __IFileUpdateRequestedEventArgs_INTERFACE_DEFINED__
__IFileUpdateRequestedEventArgs_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileUpdateRequestedEventArgs, "7B0A9342-3905-438D-AAEF-78AE265F8DD2")

.comdef IFileUpdateRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
    .ends

endif

ifndef __IFileUpdateRequest_INTERFACE_DEFINED__
__IFileUpdateRequest_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileUpdateRequest, "40C82536-C1FE-4D93-A792-1E736BC70837")

.comdef IFileUpdateRequest : public IInspectable

    get_ContentId	proc :ptr
    get_File		proc :ptr
    get_Status		proc :ptr
    put_Status		proc :FileUpdateStatus
    GetDeferral		proc :ptr
    UpdateLocalFile	proc :ptr
    .ends

endif

ifndef __IFileUpdateRequestDeferral_INTERFACE_DEFINED__
__IFileUpdateRequestDeferral_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileUpdateRequestDeferral, "FFCEDB2B-8ADE-44A5-BB00-164C4E72F13A")

.comdef IFileUpdateRequestDeferral : public IInspectable

    Complete		proc
    .ends

endif

ifndef __ICachedFileUpdaterStatics_INTERFACE_DEFINED__
__ICachedFileUpdaterStatics_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICachedFileUpdaterStatics, "9FC90920-7BCF-4888-A81E-102D7034D7CE")

.comdef ICachedFileUpdaterStatics : public IInspectable

    SetUpdateInformation proc :ptr, :HSTRING, :ptr, :ptr, :ptr
    .ends

endif

HSTRING_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HSTRING

HSTRING_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HSTRING


HSTRING_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HSTRING

HSTRING_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HSTRING

endif
