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
.xlist
ifndef __bits3_0_h__
__bits3_0_h__ equ 1

ifndef __IBitsPeerCacheRecord_FWD_DEFINED__
__IBitsPeerCacheRecord_FWD_DEFINED__ equ 1
endif
ifndef __IEnumBitsPeerCacheRecords_FWD_DEFINED__
__IEnumBitsPeerCacheRecords_FWD_DEFINED__ equ 1
endif
ifndef __IBitsPeer_FWD_DEFINED__
__IBitsPeer_FWD_DEFINED__ equ 1
endif
ifndef __IEnumBitsPeers_FWD_DEFINED__
__IEnumBitsPeers_FWD_DEFINED__ equ 1
endif
ifndef __IBitsPeerCacheAdministration_FWD_DEFINED__
__IBitsPeerCacheAdministration_FWD_DEFINED__ equ 1
endif
ifndef __IBackgroundCopyJob4_FWD_DEFINED__
__IBackgroundCopyJob4_FWD_DEFINED__ equ 1
endif
ifndef __IBackgroundCopyFile3_FWD_DEFINED__
__IBackgroundCopyFile3_FWD_DEFINED__ equ 1
endif
ifndef __IBackgroundCopyCallback2_FWD_DEFINED__
__IBackgroundCopyCallback2_FWD_DEFINED__ equ 1
endif
ifndef __BackgroundCopyManager3_0_FWD_DEFINED__
__BackgroundCopyManager3_0_FWD_DEFINED__ equ 1
BackgroundCopyManager3_0 typedef BackgroundCopyManager3_0
endif
ifndef __IBackgroundCopyJob4_FWD_DEFINED__
__IBackgroundCopyJob4_FWD_DEFINED__ equ 1
endif
include bits.inc
include bits1_5.inc
include bits2_0.inc
include bits2_5.inc
.xlist
ifndef __IBitsPeerCacheRecord_INTERFACE_DEFINED__
__IBitsPeerCacheRecord_INTERFACE_DEFINED__ equ 1

externdef		IID_IBitsPeerCacheRecord:IID

.comdef IBitsPeerCacheRecord

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetId		proc :ptr
    GetOriginUrl	proc :ptr
    GetFileSize		proc :ptr
    GetFileModificationTime proc :ptr
    GetLastAccessTime	proc :ptr
    IsFileValidated	proc
    GetFileRanges	proc :ptr, :ptr
    .ends

endif

ifndef __IEnumBitsPeerCacheRecords_INTERFACE_DEFINED__
__IEnumBitsPeerCacheRecords_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumBitsPeerCacheRecords:IID

.comdef IEnumBitsPeerCacheRecords

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    GetCount		proc :ptr
    .ends

endif

ifndef __IBitsPeer_INTERFACE_DEFINED__
__IBitsPeer_INTERFACE_DEFINED__ equ 1

externdef		IID_IBitsPeer:IID

.comdef IBitsPeer

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPeerName		proc :ptr
    IsAuthenticated	proc :ptr
    IsAvailable		proc :ptr
    .ends

endif

ifndef __IEnumBitsPeers_INTERFACE_DEFINED__
__IEnumBitsPeers_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumBitsPeers:IID

.comdef IEnumBitsPeers

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    GetCount		proc :ptr
    .ends

endif

ifndef __IBitsPeerCacheAdministration_INTERFACE_DEFINED__
__IBitsPeerCacheAdministration_INTERFACE_DEFINED__ equ 1

BG_ENABLE_PEERCACHING_CLIENT equ 0x0001
BG_ENABLE_PEERCACHING_SERVER equ 0x0002
BG_DISABLE_BRANCH_CACHE equ 0x0004

externdef		IID_IBitsPeerCacheAdministration:IID

.comdef IBitsPeerCacheAdministration

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMaximumCacheSize proc :ptr
    SetMaximumCacheSize proc :DWORD
    GetMaximumContentAge proc :ptr
    SetMaximumContentAge proc :ULONG
    GetConfigurationFlags proc :ptr
    SetConfigurationFlags proc :DWORD
    EnumRecords		proc :ptr
    GetRecord		proc :REFGUID, :ptr
    ClearRecords	proc
    DeleteRecord	proc :REFGUID
    DeleteUrl		proc :LPCWSTR
    EnumPeers		proc :ptr
    ClearPeers		proc
    DiscoverPeers	proc
    .ends

endif

ifndef __IBackgroundCopyJob4_INTERFACE_DEFINED__
__IBackgroundCopyJob4_INTERFACE_DEFINED__ equ 1

BG_JOB_ENABLE_PEERCACHING_CLIENT equ 0x0001
BG_JOB_ENABLE_PEERCACHING_SERVER equ 0x0002
BG_JOB_DISABLE_BRANCH_CACHE equ 0x0004

externdef		IID_IBackgroundCopyJob4:IID

.comdef IBackgroundCopyJob4

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
    ReplaceRemotePrefix proc :LPCWSTR, :LPCWSTR
    AddFileWithRanges	proc :LPCWSTR, :LPCWSTR, :DWORD, :BG_FILE_RANGE
    SetFileACLFlags	proc :DWORD
    GetFileACLFlags	proc :ptr
    SetPeerCachingFlags proc :DWORD
    GetPeerCachingFlags proc :ptr
    GetOwnerIntegrityLevel proc :ptr
    GetOwnerElevationState proc :ptr
    SetMaximumDownloadTime proc :ULONG
    GetMaximumDownloadTime proc :ptr
    .ends

endif

ifndef __IBackgroundCopyFile3_INTERFACE_DEFINED__
__IBackgroundCopyFile3_INTERFACE_DEFINED__ equ 1

externdef		IID_IBackgroundCopyFile3:IID

.comdef IBackgroundCopyFile3

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetRemoteName	proc :ptr
    GetLocalName	proc :ptr
    GetProgress		proc :ptr
    GetFileRanges	proc :ptr, :ptr
    SetRemoteName	proc :LPCWSTR
    GetTemporaryName	proc :ptr
    SetValidationState	proc :BOOL
    GetValidationState	proc :ptr
    IsDownloadedFromPeer proc :ptr
    .ends

endif

ifndef __IBackgroundCopyCallback2_INTERFACE_DEFINED__
__IBackgroundCopyCallback2_INTERFACE_DEFINED__ equ 1

externdef		IID_IBackgroundCopyCallback2:IID

.comdef IBackgroundCopyCallback2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    JobTransferred	proc :ptr
    JobError		proc :ptr, :ptr
    JobModification	proc :ptr, :DWORD
    FileTransferred	proc :ptr, :ptr
    .ends

endif

ifndef __BackgroundCopyManager3_0_LIBRARY_DEFINED__
__BackgroundCopyManager3_0_LIBRARY_DEFINED__ equ 1

externdef		LIBID_BackgroundCopyManager3_0:IID
externdef		CLSID_BackgroundCopyManager3_0:CLSID
ifdef __cplusplus
class DECLSPEC_UUID("659cdea7-489e-11d9-a9cd-000d56965251")
endif
endif

include bits4_0.inc

externdef __MIDL_itf_bits3_0_0000_0008_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_bits3_0_0000_0008_v0_0_s_ifspec:RPC_IF_HANDLE

.list
endif
