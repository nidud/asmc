ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __inspectable_h__
define __inspectable_h__
ifndef __unknwn_h__
include unknwn.inc
endif
ifndef __hstring_h__
include hstring.inc
endif

.enum TrustLevel {
    BaseTrust,
    PartialTrust,
    FullTrust
    }

ifndef __IInspectable_INTERFACE_DEFINED__
define __IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(IInspectable, "AF86E2E0-B12D-4c6a-9C5A-D7AA65101E90")

.comdef IInspectable : public IUnknown

    GetIids proc :ptr, :ptr
    GetRuntimeClassName proc :ptr
    GetTrustLevel proc :ptr
   .ends
    LPINSPECTABLE typedef ptr IInspectable

endif
endif
