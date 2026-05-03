ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __servprov_h__
define __servprov_h__
ifndef __objidl_h__
include objidl.inc
endif

ifndef _LPSERVICEPROVIDER_DEFINED
define _LPSERVICEPROVIDER_DEFINED
ifndef __IServiceProvider_INTERFACE_DEFINED__
define __IServiceProvider_INTERFACE_DEFINED__
DEFINE_IIDX(IServiceProvider, "6d5140c1-7436-11ce-8034-00aa006009fa")

.comdef IServiceProvider : public IUnknown

    QueryService	proc :REFGUID, :REFIID, :ptr
    .ends
    LPSERVICEPROVIDER	typedef ptr IServiceProvider

endif
endif

endif
