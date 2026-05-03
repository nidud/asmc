ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __notificationactivationcallback_h__
define __notificationactivationcallback_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP OR WINAPI_PARTITION_SYSTEM)

if (NTDDI_VERSION GE NTDDI_WIN10)
NOTIFICATION_USER_INPUT_DATA STRUC
Key			LPCWSTR ?
Value			LPCWSTR ?
NOTIFICATION_USER_INPUT_DATA ENDS

ifndef __INotificationActivationCallback_INTERFACE_DEFINED__
define __INotificationActivationCallback_INTERFACE_DEFINED__

DEFINE_IIDX(INotificationActivationCallback, "53E31837-6600-4A81-9395-75CFFE746F94")

.comdef INotificationActivationCallback : public IUnknown

    Activate proc :LPCWSTR, :LPCWSTR
   .ends

endif
endif
endif
endif
