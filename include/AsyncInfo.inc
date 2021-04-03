ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __asyncinfo_h__
__asyncinfo_h__ equ <>

ifndef __IAsyncInfo_FWD_DEFINED__
__IAsyncInfo_FWD_DEFINED__ equ 1
endif

include inspectable.inc

.enum AsyncStatus {
    Started,
    Completed,
    Canceled,
    Error,
    }

ifndef __IAsyncInfo_INTERFACE_DEFINED__
__IAsyncInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAsyncInfo, "00000036-0000-0000-C000-000000000046")

.comdef IAsyncInfo : public IInspectable

    get_Id		proc :dword
    get_Status		proc :ptr
    get_ErrorCode	proc :ptr
    Cancel		proc
    Close		proc
    .ends

endif

endif
