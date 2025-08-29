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

ifndef __inputpanelconfiguration_h__
define __inputpanelconfiguration_h__

include oaidl.inc
include ocidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (NTDDI_VERSION ge NTDDI_WIN8)

ifndef __IInputPanelConfiguration_INTERFACE_DEFINED__
define __IInputPanelConfiguration_INTERFACE_DEFINED__

DEFINE_IIDX(IInputPanelConfiguration, "41C81592-514C-48BD-A22E-E6AF638521A6")

.comdef IInputPanelConfiguration : public IUnknown
    EnableFocusTracking proc
   .ends

endif

ifndef __IInputPanelInvocationConfiguration_INTERFACE_DEFINED__
define __IInputPanelInvocationConfiguration_INTERFACE_DEFINED__

DEFINE_IIDX(IInputPanelInvocationConfiguration, "A213F136-3B45-4362-A332-EFB6547CD432")

.comdef IInputPanelInvocationConfiguration : public IUnknown
    RequireTouchInEditControl proc
   .ends

endif

ifndef __InputPanelConfigurationLib_LIBRARY_DEFINED__
define __InputPanelConfigurationLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_InputPanelConfigurationLib, 0x82E4F0B2,0x5440,0x42E4,0x8E,0xD9,0xA9,0x15,0xD1,0x21,0x6C,0x79)
DEFINE_GUIDS(CLSID_InputPanelConfiguration, "2853ADD3-F096-4C63-A78F-7FA3EA837FB7")

endif

endif
endif

endif
