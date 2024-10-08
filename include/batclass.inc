include poclass.inc

DEFINE_GUID(BATTERY_STATUS_WMI_GUID, 0xfc4670d1, 0xebbf, 0x416e, 0x87, 0xce, 0x37, 0x4a, 0x4e, 0xbc, 0x11, 0x1a)
DEFINE_GUID(BATTERY_RUNTIME_WMI_GUID, 0x535a3767, 0x1ac2, 0x49bc, 0xa0, 0x77, 0x3f, 0x7a, 0x02, 0xe4, 0x0a, 0xec)
DEFINE_GUID(BATTERY_TEMPERATURE_WMI_GUID, 0x1a52a14d, 0xadce, 0x4a44, 0x9a, 0x3e, 0xc8, 0xd8, 0xf1, 0x5f, 0xf2, 0xc2)
DEFINE_GUID(BATTERY_FULL_CHARGED_CAPACITY_WMI_GUID, 0x40b40565, 0x96f7, 0x4435, 0x86, 0x94, 0x97, 0xe0, 0xe4, 0x39, 0x59, 0x05)
DEFINE_GUID(BATTERY_CYCLE_COUNT_WMI_GUID, 0xef98db24, 0x0014, 0x4c25, 0xa5, 0x0b, 0xc7, 0x24, 0xae, 0x5c, 0xd3, 0x71)
DEFINE_GUID(BATTERY_STATIC_DATA_WMI_GUID, 0x05e1e463, 0xe4e2, 0x4ea9, 0x80, 0xcb, 0x9b, 0xd4, 0xb3, 0xca, 0x06, 0x55)
DEFINE_GUID(BATTERY_STATUS_CHANGE_WMI_GUID, 0xcddfa0c3, 0x7c5b, 0x4e43, 0xa0, 0x34, 0x05, 0x9f, 0xa5, 0xb8, 0x43, 0x64)
DEFINE_GUID(BATTERY_TAG_CHANGE_WMI_GUID, 0x5e1f6e19, 0x8786, 0x4d23, 0x94, 0xfc, 0x9e, 0x74, 0x6b, 0xd5, 0xd8, 0x88)

ifndef _BATCLASS_
define _BATCLASS_
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (NTDDI_VERSION LT NTDDI_WINXP)
ifndef _NTPOAPI_
BATTERY_REPORTING_SCALE STRUC
Granularity		ULONG ?
Capacity		ULONG ?
BATTERY_REPORTING_SCALE ENDS
PBATTERY_REPORTING_SCALE typedef ptr BATTERY_REPORTING_SCALE
endif
endif

ifndef _WINDOWS_

CALLBACK(PBCLASS_QUERY_TAG_CALLBACK, :PVOID, :PULONG)
CALLBACK(PBCLASS_QUERY_INFORMATION_CALLBACK, :PVOID, :ULONG, :BATTERY_QUERY_INFORMATION_LEVEL, :LONG)
CALLBACK(PBCLASS_QUERY_STATUS_CALLBACK, :PVOID, :ULONG, :PBATTERY_STATUS)

BATTERY_NOTIFY		STRUC
PowerState		ULONG ?
LowCapacity		ULONG ?
HighCapacity		ULONG ?
BATTERY_NOTIFY		ENDS
PBATTERY_NOTIFY		typedef ptr BATTERY_NOTIFY

CALLBACK(PBCLASS_SET_STATUS_NOTIFY_CALLBACK, :PVOID, :ULONG, :PBATTERY_NOTIFY)
CALLBACK(PBCLASS_SET_INFORMATION_CALLBACK, :PVOID, :ULONG, :BATTERY_SET_INFORMATION_LEVEL, :PVOID)
CALLBACK(PBCLASS_DISABLE_STATUS_NOTIFY_CALLBACK, :PVOID)


BCLASS_QUERY_TAG		typedef PBCLASS_QUERY_TAG_CALLBACK
BCLASS_QUERY_INFORMATION	typedef PBCLASS_QUERY_INFORMATION_CALLBACK
BCLASS_QUERY_STATUS		typedef PBCLASS_QUERY_STATUS_CALLBACK
BCLASS_SET_STATUS_NOTIFY	typedef PBCLASS_SET_STATUS_NOTIFY_CALLBACK
BCLASS_SET_INFORMATION		typedef PBCLASS_SET_INFORMATION_CALLBACK
BCLASS_DISABLE_STATUS_NOTIFY	typedef PBCLASS_DISABLE_STATUS_NOTIFY_CALLBACK

BATTERY_MINIPORT_INFO	STRUC
MajorVersion		USHORT ?
MinorVersion		USHORT ?
Context			PVOID ?
QueryTag		BCLASS_QUERY_TAG ?
QueryInformation	BCLASS_QUERY_INFORMATION ?
SetInformation		BCLASS_SET_INFORMATION ?
QueryStatus		BCLASS_QUERY_STATUS ?
SetStatusNotify		BCLASS_SET_STATUS_NOTIFY ?
DisableStatusNotify	BCLASS_DISABLE_STATUS_NOTIFY ?
Pdo			PVOID ? ;PDEVICE_OBJECT ?
DeviceName		PVOID ? ;PUNICODE_STRING ?
BATTERY_MINIPORT_INFO	ENDS
PBATTERY_MINIPORT_INFO	typedef ptr BATTERY_MINIPORT_INFO

BATTERY_MINIPORT_INFO_V1_1 STRUC
MajorVersion		USHORT ?
MinorVersion		USHORT ?
Context			PVOID ?
QueryTag		BCLASS_QUERY_TAG ?
QueryInformation	BCLASS_QUERY_INFORMATION ?
SetInformation		BCLASS_SET_INFORMATION ?
QueryStatus		BCLASS_QUERY_STATUS ?
SetStatusNotify		BCLASS_SET_STATUS_NOTIFY ?
DisableStatusNotify	BCLASS_DISABLE_STATUS_NOTIFY ?
Pdo			PVOID ? ;PDEVICE_OBJECT ?
DeviceName		PVOID ? ;PUNICODE_STRING ?
Fdo			PVOID ? ;PDEVICE_OBJECT ?
BATTERY_MINIPORT_INFO_V1_1 ENDS
PBATTERY_MINIPORT_INFO_V1_1 typedef ptr BATTERY_MINIPORT_INFO_V1_1

BATTERY_CLASS_MAJOR_VERSION equ 0x0001
BATTERY_CLASS_MINOR_VERSION equ 0x0000
BATTERY_CLASS_MINOR_VERSION_1 equ 0x0001

if (NTDDI_VERSION GE NTDDI_WINXP)

BATTERY_WMI_STATUS	STRUC
Tag			ULONG ?
RemainingCapacity	ULONG ?
ChargeRate		LONG ?
DischargeRate		LONG ?
Voltage			ULONG ?
PowerOnline		BOOLEAN ?
Charging		BOOLEAN ?
Discharging		BOOLEAN ?
Critical		BOOLEAN ?
BATTERY_WMI_STATUS	ENDS
PBATTERY_WMI_STATUS	typedef ptr BATTERY_WMI_STATUS

BATTERY_WMI_RUNTIME	STRUC
Tag			ULONG ?
EstimatedRuntime	ULONG ?
BATTERY_WMI_RUNTIME	ENDS
PBATTERY_WMI_RUNTIME	typedef ptr BATTERY_WMI_RUNTIME

BATTERY_WMI_TEMPERATURE STRUC
Tag			ULONG ?
Temperature		ULONG ?
BATTERY_WMI_TEMPERATURE ENDS
PBATTERY_WMI_TEMPERATURE typedef ptr BATTERY_WMI_TEMPERATURE

BATTERY_WMI_FULL_CHARGED_CAPACITY STRUC
Tag			ULONG ?
FullChargedCapacity	ULONG ?
BATTERY_WMI_FULL_CHARGED_CAPACITY ENDS
PBATTERY_WMI_FULL_CHARGED_CAPACITY typedef ptr BATTERY_WMI_FULL_CHARGED_CAPACITY

BATTERY_WMI_CYCLE_COUNT STRUC
Tag			ULONG ?
CycleCount		ULONG ?
BATTERY_WMI_CYCLE_COUNT ENDS
PBATTERY_WMI_CYCLE_COUNT typedef ptr BATTERY_WMI_CYCLE_COUNT

BATTERY_WMI_STATIC_DATA STRUC
Tag			ULONG ?
ManufactureDate		WCHAR 25 dup(?)
Granularity		BATTERY_REPORTING_SCALE 4 dup(<>)
Capabilities		ULONG ?
Technology		UCHAR ?
Chemistry		ULONG ?
DesignedCapacity	ULONG ?
DefaultAlert1		ULONG ?
DefaultAlert2		ULONG ?
CriticalBias		ULONG ?
Strings			WCHAR 1 dup(?)
BATTERY_WMI_STATIC_DATA ENDS
PBATTERY_WMI_STATIC_DATA typedef ptr BATTERY_WMI_STATIC_DATA

BATTERY_WMI_STATUS_CHANGE STRUC
Tag			ULONG ?
PowerOnline		BOOLEAN ?
Charging		BOOLEAN ?
Discharging		BOOLEAN ?
Critical		BOOLEAN ?
BATTERY_WMI_STATUS_CHANGE ENDS
PBATTERY_WMI_STATUS_CHANGE typedef ptr BATTERY_WMI_STATUS_CHANGE

BATTERY_TAG_CHANGE	STRUC
Tag			ULONG ?
BATTERY_TAG_CHANGE	ENDS
PBATTERY_TAG_CHANGE	typedef ptr BATTERY_TAG_CHANGE

endif

if NOT defined(BATTERYCLASS)
BATTERYCLASSAPI		equ <DECLSPEC_IMPORT>
else
BATTERYCLASSAPI		equ 1
endif

BatteryClassInitializeDevice proto WINAPI :PBATTERY_MINIPORT_INFO, :ptr
BatteryClassUnload proto WINAPI :ptr
BatteryClassIoctl proto WINAPI :ptr, :ptr
if (NTDDI_VERSION GE NTDDI_WINXP)
BatteryClassSystemControl proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr
BatteryClassQueryWmiDataBlock proto WINAPI :ptr, :ptr, :ptr, :ULONG, :PULONG, :ULONG, :PUCHAR
endif
BatteryClassStatusNotify proto WINAPI :PVOID

endif
endif
endif ;; _BATCLASS_

