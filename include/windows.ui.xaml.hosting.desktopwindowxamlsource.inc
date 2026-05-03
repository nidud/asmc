ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __windows2Eui2Examl2Ehosting2Edesktopwindowxamlsource_h__
define __windows2Eui2Examl2Ehosting2Edesktopwindowxamlsource_h__

ifndef __oaidl_h__
include oaidl.inc
endif

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

