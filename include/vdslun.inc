ifndef _RPC500_
include rpc500.inc
endif
ifndef __vdslun_h__
define __vdslun_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum VDS_STORAGE_IDENTIFIER_CODE_SET {
	VDSStorageIdCodeSetReserved,
	VDSStorageIdCodeSetBinary,
	VDSStorageIdCodeSetAscii,
	VDSStorageIdCodeSetUtf8
	}

.enum VDS_STORAGE_IDENTIFIER_TYPE {
	VDSStorageIdTypeVendorSpecific,
	VDSStorageIdTypeVendorId,
	VDSStorageIdTypeEUI64,
	VDSStorageIdTypeFCPHName,
	VDSStorageIdTypePortRelative,
	VDSStorageIdTypeTargetPortGroup,
	VDSStorageIdTypeLogicalUnitGroup,
	VDSStorageIdTypeMD5LogicalUnitIdentifier,
	VDSStorageIdTypeScsiNameString
	}

.enum VDS_STORAGE_BUS_TYPE {
	VDSBusTypeUnknown,
	VDSBusTypeScsi,
	VDSBusTypeAtapi,
	VDSBusTypeAta,
	VDSBusType1394,
	VDSBusTypeSsa,
	VDSBusTypeFibre,
	VDSBusTypeUsb,
	VDSBusTypeRAID,
	VDSBusTypeiScsi,
	VDSBusTypeSas,
	VDSBusTypeSata,
	VDSBusTypeSd,
	VDSBusTypeMmc,
	VDSBusTypeMax,
	VDSBusTypeVirtual = VDSBusTypeMax,
	VDSBusTypeFileBackedVirtual,
	VDSBusTypeSpaces,
	VDSBusTypeNVMe,
	VDSBusTypeScm,
	VDSBusTypeUfs,
	VDSBusTypeMaxReserved = 0x7f
	}

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

.enum VDS_INTERCONNECT_ADDRESS_TYPE {
	VDS_IA_UNKNOWN,
	VDS_IA_FCFS,
	VDS_IA_FCPH,
	VDS_IA_FCPH3,
	VDS_IA_MAC,
	VDS_IA_SCSI
	}

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

define VER_VDS_LUN_INFORMATION 1

endif

endif
