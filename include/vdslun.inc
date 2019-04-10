ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err<this stub requires an updated version of rpcndr.inc>
endif

ifndef __vdslun_h__
__vdslun_h__ equ <>

include oaidl.inc
include ocidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

VDS_STORAGE_IDENTIFIER_CODE_SET typedef SDWORD
VDSStorageIdCodeSetReserved equ 0
VDSStorageIdCodeSetBinary equ 1
VDSStorageIdCodeSetAscii equ 2
VDSStorageIdCodeSetUtf8 equ 3

VDS_STORAGE_IDENTIFIER_TYPE typedef SDWORD
VDSStorageIdTypeVendorSpecific equ 0
VDSStorageIdTypeVendorId equ 1
VDSStorageIdTypeEUI64	equ 2
VDSStorageIdTypeFCPHName equ 3
VDSStorageIdTypePortRelative equ 4
VDSStorageIdTypeTargetPortGroup equ 5
VDSStorageIdTypeLogicalUnitGroup equ 6
VDSStorageIdTypeMD5LogicalUnitIdentifier equ 7
VDSStorageIdTypeScsiNameString equ 8

VDS_STORAGE_BUS_TYPE	typedef SDWORD
VDSBusTypeUnknown	equ 0
VDSBusTypeScsi		equ 0x1
VDSBusTypeAtapi		equ 0x2
VDSBusTypeAta		equ 0x3
VDSBusType1394		equ 0x4
VDSBusTypeSsa		equ 0x5
VDSBusTypeFibre		equ 0x6
VDSBusTypeUsb		equ 0x7
VDSBusTypeRAID		equ 0x8
VDSBusTypeiScsi		equ 0x9
VDSBusTypeSas		equ 0xa
VDSBusTypeSata		equ 0xb
VDSBusTypeSd		equ 0xc
VDSBusTypeMmc		equ 0xd
VDSBusTypeMax		equ 0xe
VDSBusTypeVirtual	equ 0xe
VDSBusTypeFileBackedVirtual equ 0xf
VDSBusTypeSpaces	equ 0x10
VDSBusTypeNVMe		equ 0x11
VDSBusTypeMaxReserved	equ 0x7f

VDS_STORAGE_IDENTIFIER	STRUC
m_CodeSet		VDS_STORAGE_IDENTIFIER_CODE_SET ?
m_Type			VDS_STORAGE_IDENTIFIER_TYPE ?
m_cbIdentifier		ULONG ?
m_rgbIdentifier		LPBYTE ?
VDS_STORAGE_IDENTIFIER	ENDS
LPVDS_STORAGE_IDENTIFIER typedef ptr VDS_STORAGE_IDENTIFIER

VDS_STORAGE_DEVICE_ID_DESCRIPTOR STRUC
m_version		ULONG ?
m_cIdentifiers		ULONG ?
m_rgIdentifiers		LPVDS_STORAGE_IDENTIFIER ?
VDS_STORAGE_DEVICE_ID_DESCRIPTOR ENDS

VDS_INTERCONNECT_ADDRESS_TYPE typedef SDWORD
VDS_IA_UNKNOWN		equ 0
VDS_IA_FCFS		equ 1
VDS_IA_FCPH		equ 2
VDS_IA_FCPH3		equ 3
VDS_IA_MAC		equ 4
VDS_IA_SCSI		equ 5

VDS_INTERCONNECT	STRUC
m_addressType		VDS_INTERCONNECT_ADDRESS_TYPE ?
m_cbPort		ULONG ?
m_pbPort		LPBYTE ?
m_cbAddress		ULONG ?
m_pbAddress		LPBYTE ?
VDS_INTERCONNECT	ENDS
LPVDS_INTERCONNECT	typedef ptr VDS_INTERCONNECT

VDS_LUN_INFORMATION	STRUC
m_version		ULONG ?
m_DeviceType		db ?
m_DeviceTypeModifier	db ?
m_bCommandQueueing	BOOL ?
m_BusType		VDS_STORAGE_BUS_TYPE ?
m_szVendorId		LPSTR ?
m_szProductId		LPSTR ?
m_szProductRevision	LPSTR ?
m_szSerialNumber	LPSTR ?
m_diskSignature		GUID <>
m_deviceIdDescriptor	VDS_STORAGE_DEVICE_ID_DESCRIPTOR <>
m_cInterconnects	ULONG ?
m_rgInterconnects	LPVDS_INTERCONNECT ?
VDS_LUN_INFORMATION	ENDS

VER_VDS_LUN_INFORMATION equ ( 1 )

endif

endif
