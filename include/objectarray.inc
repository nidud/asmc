.pragma list(push, 0)
ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __objectarray_h__
define __objectarray_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif

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
