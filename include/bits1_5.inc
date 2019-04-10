ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
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
ifndef __bits1_5_h__
__bits1_5_h__ equ <>

ifndef __IBackgroundCopyJob2_FWD_DEFINED__
__IBackgroundCopyJob2_FWD_DEFINED__ equ 1
endif
ifndef __BackgroundCopyManager1_5_FWD_DEFINED__
__BackgroundCopyManager1_5_FWD_DEFINED__ equ 1
BackgroundCopyManager1_5 typedef BackgroundCopyManager1_5
endif
ifndef __IBackgroundCopyJob2_FWD_DEFINED__
__IBackgroundCopyJob2_FWD_DEFINED__ equ 1
endif
include bits.inc

ifndef __IBackgroundCopyJob2_INTERFACE_DEFINED__
__IBackgroundCopyJob2_INTERFACE_DEFINED__ equ 1

BG_JOB_REPLY_PROGRESS	STRUC
BytesTotal		UINT64 ?
BytesTransferred	UINT64 ?
BG_JOB_REPLY_PROGRESS	ENDS

BG_AUTH_TARGET typedef SDWORD
BG_AUTH_TARGET_SERVER	equ 1
BG_AUTH_TARGET_PROXY	equ ( BG_AUTH_TARGET_SERVER + 1 )

BG_AUTH_SCHEME typedef SDWORD
BG_AUTH_SCHEME_BASIC	equ 1
BG_AUTH_SCHEME_DIGEST	equ ( BG_AUTH_SCHEME_BASIC + 1 )
BG_AUTH_SCHEME_NTLM	equ ( BG_AUTH_SCHEME_DIGEST + 1 )
BG_AUTH_SCHEME_NEGOTIATE equ ( BG_AUTH_SCHEME_NTLM + 1 )
BG_AUTH_SCHEME_PASSPORT equ ( BG_AUTH_SCHEME_NEGOTIATE + 1 )

BG_BASIC_CREDENTIALS	STRUC
UserName		LPWSTR ?
Password		LPWSTR ?
BG_BASIC_CREDENTIALS	ENDS
PBG_BASIC_CREDENTIALS	typedef ptr BG_BASIC_CREDENTIALS

BG_AUTH_CREDENTIALS_UNION UNION
_Basic			BG_BASIC_CREDENTIALS <>
BG_AUTH_CREDENTIALS_UNION ENDS

BG_AUTH_CREDENTIALS	STRUC
Target			BG_AUTH_TARGET ?
Scheme			BG_AUTH_SCHEME ?
Credentials		BG_AUTH_CREDENTIALS_UNION <>
BG_AUTH_CREDENTIALS	ENDS
PBG_AUTH_CREDENTIALS	typedef ptr BG_AUTH_CREDENTIALS

externdef		IID_IBackgroundCopyJob2:IID

.comdef IBackgroundCopyJob2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
    .ends

endif

ifndef __BackgroundCopyManager1_5_LIBRARY_DEFINED__
__BackgroundCopyManager1_5_LIBRARY_DEFINED__ equ 1

externdef		LIBID_BackgroundCopyManager1_5:IID
externdef		CLSID_BackgroundCopyManager1_5:CLSID
ifdef __cplusplus
class DECLSPEC_UUID("f087771f-d74f-4c1a-bb8a-e16aca9124ea")
endif
endif

include bits2_0.inc

endif
