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

ifndef __bits3_0_h__
define __bits3_0_h__

include bits.inc
include bits1_5.inc
include bits2_0.inc
include bits2_5.inc

ifndef __IBitsPeerCacheRecord_INTERFACE_DEFINED__
define __IBitsPeerCacheRecord_INTERFACE_DEFINED__

DEFINE_IIDX(IBitsPeerCacheRecord, "659cdeaf-489e-11d9-a9cd-000d56965251")

.comdef IBitsPeerCacheRecord : public IUnknown

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
define __IEnumBitsPeerCacheRecords_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumBitsPeerCacheRecords, "659cdea4-489e-11d9-a9cd-000d56965251")

.comdef IEnumBitsPeerCacheRecords : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    GetCount		proc :ptr
   .ends

endif

ifndef __IBitsPeer_INTERFACE_DEFINED__
define __IBitsPeer_INTERFACE_DEFINED__

DEFINE_IIDX(IBitsPeer, "659cdea2-489e-11d9-a9cd-000d56965251")

.comdef IBitsPeer : public IUnknown

    GetPeerName		proc :ptr
    IsAuthenticated	proc :ptr
    IsAvailable		proc :ptr
   .ends

endif

ifndef __IEnumBitsPeers_INTERFACE_DEFINED__
define __IEnumBitsPeers_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumBitsPeers, "659cdea5-489e-11d9-a9cd-000d56965251")

.comdef IEnumBitsPeers : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    GetCount		proc :ptr
   .ends

endif

ifndef __IBitsPeerCacheAdministration_INTERFACE_DEFINED__
define __IBitsPeerCacheAdministration_INTERFACE_DEFINED__

BG_ENABLE_PEERCACHING_CLIENT equ 0x0001
BG_ENABLE_PEERCACHING_SERVER equ 0x0002
BG_DISABLE_BRANCH_CACHE equ 0x0004

DEFINE_IIDX(IBitsPeerCacheAdministration, "659cdead-489e-11d9-a9cd-000d56965251")

.comdef IBitsPeerCacheAdministration : public IUnknown

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
define __IBackgroundCopyJob4_INTERFACE_DEFINED__

BG_JOB_ENABLE_PEERCACHING_CLIENT equ 0x0001
BG_JOB_ENABLE_PEERCACHING_SERVER equ 0x0002
BG_JOB_DISABLE_BRANCH_CACHE equ 0x0004

DEFINE_IIDX(IBackgroundCopyJob4, "659cdeae-489e-11d9-a9cd-000d56965251")

.comdef IBackgroundCopyJob4 : public IUnknown

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
define __IBackgroundCopyFile3_INTERFACE_DEFINED__

DEFINE_IIDX(IBackgroundCopyFile3, "659cdeaa-489e-11d9-a9cd-000d56965251")

.comdef IBackgroundCopyFile3 : public IUnknown

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
define __IBackgroundCopyCallback2_INTERFACE_DEFINED__

DEFINE_IIDX(IBackgroundCopyCallback2, "659cdeac-489e-11d9-a9cd-000d56965251")

.comdef IBackgroundCopyCallback2 : public IUnknown

    JobTransferred	proc :ptr
    JobError		proc :ptr, :ptr
    JobModification	proc :ptr, :DWORD
    FileTransferred	proc :ptr, :ptr
   .ends

endif

ifndef __BackgroundCopyManager3_0_LIBRARY_DEFINED__
define __BackgroundCopyManager3_0_LIBRARY_DEFINED__
DEFINE_GUIDS(LIBID_BackgroundCopyManager3_0, "659cdea7-489e-11d9-a9cd-000d56965251")
DEFINE_GUIDS(CLSID_BackgroundCopyManager3_0, "659cdea7-489e-11d9-a9cd-000d56965251")
endif

include bits4_0.inc

endif
