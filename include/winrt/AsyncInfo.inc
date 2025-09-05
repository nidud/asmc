ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __asyncinfo_h__
define __asyncinfo_h__
ifndef __inspectable_h__
include inspectable.inc
endif

.enum AsyncStatus {
    AsyncStatus_Started,
    AsyncStatus_Completed,
    AsyncStatus_Canceled,
    AsyncStatus_Error
    }

ifndef __IAsyncInfo_INTERFACE_DEFINED__
define __IAsyncInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncInfo, "00000036-0000-0000-C000-000000000046")

.comdef IAsyncInfo : public IInspectable

    get_Id		proc :ptr
    get_Status		proc :ptr
    get_ErrorCode	proc :ptr
    Cancel		proc
    Close		proc
   .ends

endif
endif
