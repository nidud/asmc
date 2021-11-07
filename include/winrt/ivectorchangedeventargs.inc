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

ifndef __ivectorchangedeventargs_h__
define __ivectorchangedeventargs_h__

include oaidl.inc
include inspectable.inc
include asyncinfo.inc
include eventtoken.inc

.enum CollectionChange {
    CollectionChange_Reset	  = 0,
    CollectionChange_ItemInserted = ( CollectionChange_Reset + 1 ),
    CollectionChange_ItemRemoved  = ( CollectionChange_ItemInserted + 1 ),
    CollectionChange_ItemChanged  = ( CollectionChange_ItemRemoved + 1 )
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
