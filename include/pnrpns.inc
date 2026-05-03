ifndef _PNRPNS_H_
define _PNRPNS_H_
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include pnrpdef.inc

ifndef NS_PNRPNAME
NS_PNRPNAME		equ (38)
endif
ifndef NS_PNRPCLOUD
NS_PNRPCLOUD		equ (39)
endif

PNRPINFO_HINT		equ 0x00000001

PNRPINFO_V1		STRUC
dwSize			dd ?
lpwszIdentity		LPWSTR ?
nMaxResolve		dd ?
dwTimeout		dd ?
dwLifetime		dd ?
enResolveCriteria	PNRP_RESOLVE_CRITERIA ?
dwFlags			dd ?
saHint			SOCKET_ADDRESS <>
enNameState		PNRP_REGISTERED_ID_STATE ?
PNRPINFO_V1		ENDS
PPNRPINFO_V1		typedef ptr PNRPINFO_V1

PNRPINFO_V2		STRUC
dwSize			dd ?
lpwszIdentity		LPWSTR ?
nMaxResolve		dd ?
dwTimeout		dd ?
dwLifetime		dd ?
enResolveCriteria	PNRP_RESOLVE_CRITERIA ?
dwFlags			dd ?
saHint			SOCKET_ADDRESS <>
enNameState		PNRP_REGISTERED_ID_STATE ?
enExtendedPayloadType	PNRP_EXTENDED_PAYLOAD_TYPE ?
UNION
 blobPayload		BLOB <>
 pwszPayload		PWSTR ?
ENDS
PNRPINFO_V2		ENDS
PPNRPINFO_V2		typedef ptr PNRPINFO_V2

if defined(PNRP_USE_V1_API)
PNRPINFO		typedef	 PNRPINFO_V1
PPNRPINFO		typedef	 PPNRPINFO_V1
else
PNRPINFO		typedef	 PNRPINFO_V2
PPNRPINFO		typedef	 PPNRPINFO_V2
endif

PNRPCLOUDINFO		STRUC
dwSize			dd ?
Cloud			PNRP_CLOUD_ID <>
enCloudState		PNRP_CLOUD_STATE ?
enCloudFlags		PNRP_CLOUD_FLAGS ?
PNRPCLOUDINFO		ENDS
PPNRPCLOUDINFO		typedef ptr PNRPCLOUDINFO

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; _PNRPNS_H_

ifdef DEFINE_GUID

DEFINE_GUID(NS_PROVIDER_PNRPNAME,   0x03fe89cd, 0x766d, 0x4976, 0xb9, 0xc1, 0xbb, 0x9b, 0xc4, 0x2c, 0x7b, 0x4d)
DEFINE_GUID(NS_PROVIDER_PNRPCLOUD,  0x03fe89ce, 0x766d, 0x4976, 0xb9, 0xc1, 0xbb, 0x9b, 0xc4, 0x2c, 0x7b, 0x4d)
DEFINE_GUID(SVCID_PNRPCLOUD,	0xc2239ce6, 0x00c0, 0x4fbf, 0xba, 0xd6, 0x18, 0x13, 0x93, 0x85, 0xa4, 0x9a)
DEFINE_GUID(SVCID_PNRPNAME_V1,	0xc2239ce5, 0x00c0, 0x4fbf, 0xba, 0xd6, 0x18, 0x13, 0x93, 0x85, 0xa4, 0x9a)
DEFINE_GUID(SVCID_PNRPNAME_V2,	0xc2239ce7, 0x00c0, 0x4fbf, 0xba, 0xd6, 0x18, 0x13, 0x93, 0x85, 0xa4, 0x9a)

ifdef PNRP_USE_V2_API
SVCID_PNRPNAME		equ <SVCID_PNRPNAME_V2>
else
SVCID_PNRPNAME		equ <SVCID_PNRPNAME_V1>
endif

endif ;; DEFINE_GUID
