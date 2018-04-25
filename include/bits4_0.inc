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
ifndef __bits4_0_h__
__bits4_0_h__ equ <>

ifndef __IBitsTokenOptions_FWD_DEFINED__
__IBitsTokenOptions_FWD_DEFINED__ equ 1
endif
ifndef __IBackgroundCopyFile4_FWD_DEFINED__
__IBackgroundCopyFile4_FWD_DEFINED__ equ 1
endif
ifndef __BackgroundCopyManager4_0_FWD_DEFINED__
__BackgroundCopyManager4_0_FWD_DEFINED__ equ 1
BackgroundCopyManager4_0 typedef BackgroundCopyManager4_0
endif
include bits.inc
include bits1_5.inc
include bits2_0.inc
include bits2_5.inc
include bits3_0.inc

ifndef __IBitsTokenOptions_INTERFACE_DEFINED__
__IBitsTokenOptions_INTERFACE_DEFINED__ equ 1

BG_TOKEN_LOCAL_FILE	equ 0x0001
BG_TOKEN_NETWORK	equ 0x0002

externdef		IID_IBitsTokenOptions:IID

.comdef IBitsTokenOptions

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetHelperTokenFlags proc :DWORD
    GetHelperTokenFlags proc :ptr
    SetHelperToken	proc
    ClearHelperToken	proc
    GetHelperTokenSid	proc :ptr
    .ends

endif

ifndef __IBackgroundCopyFile4_INTERFACE_DEFINED__
__IBackgroundCopyFile4_INTERFACE_DEFINED__ equ 1

externdef		IID_IBackgroundCopyFile4:IID

.comdef IBackgroundCopyFile4

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
    GetPeerDownloadStats proc :PUINT64, :PUINT64
    .ends

endif

ifndef __BackgroundCopyManager4_0_LIBRARY_DEFINED__
__BackgroundCopyManager4_0_LIBRARY_DEFINED__ equ 1

externdef		LIBID_BackgroundCopyManager4_0:IID
externdef		CLSID_BackgroundCopyManager4_0:CLSID
ifdef __cplusplus
class DECLSPEC_UUID("bb6df56b-cace-11dc-9992-0019b93a3a84")
endif
endif

endif
