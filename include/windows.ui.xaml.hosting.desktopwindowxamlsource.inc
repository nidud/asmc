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

ifndef __windows2Eui2Examl2Ehosting2Edesktopwindowxamlsource_h__
define __windows2Eui2Examl2Ehosting2Edesktopwindowxamlsource_h__

ifndef __IDesktopWindowXamlSourceNative_FWD_DEFINED__
define __IDesktopWindowXamlSourceNative_FWD_DEFINED__
endif

ifndef __IDesktopWindowXamlSourceNative2_FWD_DEFINED__
define __IDesktopWindowXamlSourceNative2_FWD_DEFINED__
endif

include oaidl.inc

if (NTDDI_VERSION ge NTDDI_WIN10_RS5)

ifndef __IDesktopWindowXamlSourceNative_INTERFACE_DEFINED__
define __IDesktopWindowXamlSourceNative_INTERFACE_DEFINED__

DEFINE_IIDX(IDesktopWindowXamlSourceNative, "3cbcf1bf-2f76-4e9c-96ab-e84b37972554")

.comdef IDesktopWindowXamlSourceNative : public IUnknown
    AttachToWindow      proc :HWND
    get_WindowHandle    proc :ptr
   .ends

endif

endif
if (NTDDI_VERSION ge NTDDI_WIN10_19H1)

ifndef __IDesktopWindowXamlSourceNative2_INTERFACE_DEFINED__
define __IDesktopWindowXamlSourceNative2_INTERFACE_DEFINED__

DEFINE_IIDX(IDesktopWindowXamlSourceNative2, "e3dcd8c7-3057-4692-99c3-7b7720afda31")

.comdef IDesktopWindowXamlSourceNative2 : public IDesktopWindowXamlSourceNative
    PreTranslateMessage proc :ptr, :ptr
   .ends

endif

endif

endif

