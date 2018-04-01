ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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
__objectarray_h__ equ 1

ifndef __IObjectArray_FWD_DEFINED__
__IObjectArray_FWD_DEFINED__ equ 1
endif
ifndef __IObjectCollection_FWD_DEFINED__
__IObjectCollection_FWD_DEFINED__ equ 1
endif
include oaidl.inc
include ocidl.inc
.xlist

ifndef __IObjectArray_INTERFACE_DEFINED__
__IObjectArray_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectArray:IID
.comdef IObjectArray
    QueryInterface      proc :REFIID, :ptr
    AddRef              proc
    Release             proc
    GetCount            proc :ptr
    GetAt               proc :UINT, :REFIID, :ptr
    .ends
endif

ifndef __IObjectCollection_INTERFACE_DEFINED__
__IObjectCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectCollection:IID
.comdef IObjectCollection
    QueryInterface      proc :REFIID, :ptr
    AddRef              proc
    Release             proc
    GetCount            proc :ptr
    GetAt               proc :UINT, :REFIID, :ptr
    AddObject           proc :ptr
    AddFromArray        proc :ptr
    RemoveObjectAt      proc :UINT
    Clear               proc
    .ends
endif

.list
endif ; __objectarray_h__

