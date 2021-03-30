ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __notificationactivationcallback_h__
__notificationactivationcallback_h__ equ <>

ifndef __INotificationActivationCallback_FWD_DEFINED__
__INotificationActivationCallback_FWD_DEFINED__ equ 1
endif

include oaidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP OR WINAPI_PARTITION_SYSTEM)

if (NTDDI_VERSION GE NTDDI_WIN10)
NOTIFICATION_USER_INPUT_DATA STRUC
Key			LPCWSTR ?
Value			LPCWSTR ?
NOTIFICATION_USER_INPUT_DATA ENDS

ifndef __INotificationActivationCallback_INTERFACE_DEFINED__
__INotificationActivationCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INotificationActivationCallback, "53E31837-6600-4A81-9395-75CFFE746F94")

.comdef INotificationActivationCallback : public IUnknown

    Activate		proc :LPCWSTR, :LPCWSTR
    .ends

endif

endif
endif

endif
