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

ifndef __corewindow_h__
define __corewindow_h__

include oaidl.inc
include ocidl.inc
include inspectable.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if (NTDDI_VERSION GE NTDDI_WIN8)
ifndef __ICoreWindowInterop_INTERFACE_DEFINED__
define __ICoreWindowInterop_INTERFACE_DEFINED__
DEFINE_IIDX(ICoreWindowInterop, "45D64A29-A63E-4CB6-B498-5781D298CB4F")

.comdef ICoreWindowInterop : public IUnknown

    get_WindowHandle    proc :ptr
    put_MessageHandled  proc :boolean
   .ends

endif
endif

if (NTDDI_VERSION GE NTDDI_WINBLUE)
ifndef __ICoreInputInterop_INTERFACE_DEFINED__
define __ICoreInputInterop_INTERFACE_DEFINED__
DEFINE_IIDX(ICoreInputInterop, "40BFE3E3-B75A-4479-AC96-475365749BB8")

.comdef ICoreInputInterop : public IUnknown

    SetInputSource      proc :ptr
    put_MessageHandled  proc :boolean
   .ends

endif
;HRESULT
CreateControlInput proto WINAPI \
                  riid: REFIID,
                   ppv: ptr
endif
endif

endif
