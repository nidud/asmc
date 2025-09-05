ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __bits4_0_h__
define __bits4_0_h__

include bits.inc
include bits1_5.inc
include bits2_0.inc
include bits2_5.inc
include bits3_0.inc

ifndef __IBitsTokenOptions_INTERFACE_DEFINED__
define __IBitsTokenOptions_INTERFACE_DEFINED__

BG_TOKEN_LOCAL_FILE	equ 0x0001
BG_TOKEN_NETWORK	equ 0x0002

DEFINE_IIDX(IBitsTokenOptions, "9a2584c3-f7d2-457a-9a5e-22b67bffc7d2")

.comdef IBitsTokenOptions : public IUnknown

    SetHelperTokenFlags proc :DWORD
    GetHelperTokenFlags proc :ptr
    SetHelperToken	proc
    ClearHelperToken	proc
    GetHelperTokenSid	proc :ptr
   .ends

endif

ifndef __IBackgroundCopyFile4_INTERFACE_DEFINED__
define __IBackgroundCopyFile4_INTERFACE_DEFINED__

DEFINE_IIDX(IBackgroundCopyFile4, "ef7e0655-7888-4960-b0e5-730846e03492")

.comdef IBackgroundCopyFile4 : public IUnknown

    GetRemoteName	proc :ptr
    GetLocalName	proc :ptr
    GetProgress		proc :ptr
    GetFileRanges	proc :ptr, :ptr
    SetRemoteName	proc :LPCWSTR
    GetTemporaryName	proc :ptr
    SetValidationState	proc :BOOL
    GetValidationState	proc :ptr
    IsDownloadedFromPeer proc :ptr
    GetPeerDownloadStats proc :PUINT64, :PUINT64
   .ends

endif

ifndef __BackgroundCopyManager4_0_LIBRARY_DEFINED__
define __BackgroundCopyManager4_0_LIBRARY_DEFINED__
DEFINE_GUIDS(LIBID_BackgroundCopyManager4_0, "bb6df56b-cace-11dc-9992-0019b93a3a84")
DEFINE_GUIDS(CLSID_BackgroundCopyManager4_0, "bb6df56b-cace-11dc-9992-0019b93a3a84")
endif

include bits5_0.inc

endif ;; __bits4_0_h__
