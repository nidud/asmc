ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __ivectorchangedeventargs_h__
define __ivectorchangedeventargs_h__
ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __inspectable_h__
include inspectable.inc
endif
ifndef __asyncinfo_h__
include asyncinfo.inc
endif
ifndef __eventtoken_h__
include eventtoken.inc
endif

.enum CollectionChange {
    CollectionChange_Reset,
    CollectionChange_ItemInserted,
    CollectionChange_ItemRemoved,
    CollectionChange_ItemChanged
    }

ifndef __IVectorChangedEventArgs_INTERFACE_DEFINED__
define __IVectorChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(IVectorChangedEventArgs, "575933df-34fe-4480-af15-07691f3d5d9b")

.comdef IVectorChangedEventArgs : public IInspectable

    get_CollectionChange proc :ptr
    get_Index		proc :dword
   .ends

endif
endif
