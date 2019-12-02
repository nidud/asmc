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
ifndef __bits2_0_h__
__bits2_0_h__ equ <>

ifndef __IBackgroundCopyJob3_FWD_DEFINED__
__IBackgroundCopyJob3_FWD_DEFINED__ equ 1
endif
ifndef __IBackgroundCopyFile2_FWD_DEFINED__
__IBackgroundCopyFile2_FWD_DEFINED__ equ 1
endif
ifndef __BackgroundCopyManager2_0_FWD_DEFINED__
__BackgroundCopyManager2_0_FWD_DEFINED__ equ 1
BackgroundCopyManager2_0 typedef BackgroundCopyManager2_0
endif
ifndef __IBackgroundCopyJob3_FWD_DEFINED__
__IBackgroundCopyJob3_FWD_DEFINED__ equ 1
endif
ifndef __IBackgroundCopyFile2_FWD_DEFINED__
__IBackgroundCopyFile2_FWD_DEFINED__ equ 1
endif
include bits.inc
include bits1_5.inc

BG_LENGTH_TO_EOF	equ (-1)
BG_FILE_RANGE		STRUC
InitialOffset		UINT64 ?
Length			UINT64 ?
BG_FILE_RANGE		ENDS

BG_COPY_FILE_OWNER	equ 1
BG_COPY_FILE_GROUP	equ 2
BG_COPY_FILE_DACL	equ 4
BG_COPY_FILE_SACL	equ 8
BG_COPY_FILE_ALL	equ 15


ifndef __IBackgroundCopyJob3_INTERFACE_DEFINED__
__IBackgroundCopyJob3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IBackgroundCopyJob3, "443c8934-90ff-48ed-bcde-26f5c7450042")

.comdef IBackgroundCopyJob3 : public IUnknown

    AddFileSet		proc :ULONG, :ptr
    AddFile		proc :LPCWSTR, :LPCWSTR
    EnumFiles		proc :ptr
    Suspend		proc
    Resume		proc
    Cancel		proc
    Complete		proc
    GetId		proc :ptr
    GetType		proc :ptr
    GetProgress		proc :ptr
    GetTimes		proc :ptr
    GetState		proc :ptr
    GetError		proc :ptr
    GetOwner		proc :ptr
    SetDisplayName	proc :LPCWSTR
    GetDisplayName	proc :ptr
    SetDescription	proc :LPCWSTR
    GetDescription	proc :ptr
    SetPriority		proc :BG_JOB_PRIORITY
    GetPriority		proc :ptr
    SetNotifyFlags	proc :ULONG
    GetNotifyFlags	proc :ptr
    SetNotifyInterface	proc :ptr
    GetNotifyInterface	proc :ptr
    SetMinimumRetryDelay proc :ULONG
    GetMinimumRetryDelay proc :ptr
    SetNoProgressTimeout proc :ULONG
    GetNoProgressTimeout proc :ptr
    GetErrorCount	proc :ptr
    SetProxySettings	proc :BG_JOB_PROXY_USAGE, :ptr, :ptr
    GetProxySettings	proc :ptr, :ptr, :ptr
    TakeOwnership	proc
    SetNotifyCmdLine	proc :LPCWSTR, :LPCWSTR
    GetNotifyCmdLine	proc :ptr, :ptr
    GetReplyProgress	proc :ptr
    GetReplyData	proc
    SetReplyFileName	proc :LPCWSTR
    GetReplyFileName	proc :ptr
    SetCredentials	proc :ptr
    RemoveCredentials	proc :BG_AUTH_TARGET, :BG_AUTH_SCHEME
    ReplaceRemotePrefix proc :LPCWSTR, :LPCWSTR
    AddFileWithRanges	proc :LPCWSTR, :LPCWSTR, :DWORD, :BG_FILE_RANGE
    SetFileACLFlags	proc :DWORD
    GetFileACLFlags	proc :ptr

    .ends

endif

ifndef __IBackgroundCopyFile2_INTERFACE_DEFINED__
__IBackgroundCopyFile2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IBackgroundCopyFile2, "83e81b93-0873-474d-8a8c-f2018b1a939c")

.comdef IBackgroundCopyFile2 : public IUnknown

    GetRemoteName	proc :ptr
    GetLocalName	proc :ptr
    GetProgress		proc :ptr
    GetFileRanges	proc :ptr, :ptr
    SetRemoteName	proc :LPCWSTR

    .ends

endif

ifndef __BackgroundCopyManager2_0_LIBRARY_DEFINED__
__BackgroundCopyManager2_0_LIBRARY_DEFINED__ equ 1

DEFINE_GUIDS(LIBID_BackgroundCopyManager2_0, "6d18ad12-bde3-4393-b311-099c346e6df9")
DEFINE_GUIDS(CLSID_BackgroundCopyManager2_0, "6d18ad12-bde3-4393-b311-099c346e6df9")

endif

include bits2_5.inc

endif
