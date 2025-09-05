ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __corewindow_h__
define __corewindow_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include inspectable.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

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
CreateControlInput proto WINAPI :REFIID, :ptr
endif
endif

endif
