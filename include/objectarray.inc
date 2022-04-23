.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
 .err <this stub requires an updated version of rpcndr>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __objectarray_h__
define __objectarray_h__

include oaidl.inc
include ocidl.inc

ifndef __IObjectArray_INTERFACE_DEFINED__
define __IObjectArray_INTERFACE_DEFINED__

externdef IID_IObjectArray:IID

.comdef IObjectArray : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT, :REFIID, :ptr
   .ends
endif

ifndef __IObjectCollection_INTERFACE_DEFINED__
define __IObjectCollection_INTERFACE_DEFINED__

externdef IID_IObjectCollection:IID

.comdef IObjectCollection : public IObjectArray

    AddObject		proc :ptr
    AddFromArray	proc :ptr
    RemoveObjectAt	proc :UINT
    Clear		proc
   .ends
endif

endif
.pragma list(pop)
