.pragma list(push, 0)
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

ifndef __amsi_h__
define __amsi_h__

include oaidl.inc
include ocidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum AMSI_RESULT {
    AMSI_RESULT_CLEAN	= 0,
    AMSI_RESULT_NOT_DETECTED	= 1,
    AMSI_RESULT_BLOCKED_BY_ADMIN_START	= 0x4000,
    AMSI_RESULT_BLOCKED_BY_ADMIN_END	= 0x4fff,
    AMSI_RESULT_DETECTED    = 32768
    }

AmsiResultIsMalware macro r
	cmp r,AMSI_RESULT_DETECTED
	mov eax,TRUE
	mov ecx,FALSE
	cmovl eax,ecx
	exitm<eax>
	endm
AmsiResultIsBlockedByAdmin macro r
	exitm<((r) GE AMSI_RESULT_BLOCKED_BY_ADMIN_START) AND (r) LE AMSI_RESULT_BLOCKED_BY_ADMIN_END>
	endm

.enum AMSI_ATTRIBUTE {
    AMSI_ATTRIBUTE_APP_NAME = 0,
    AMSI_ATTRIBUTE_CONTENT_NAME = 1,
    AMSI_ATTRIBUTE_CONTENT_SIZE = 2,
    AMSI_ATTRIBUTE_CONTENT_ADDRESS  = 3,
    AMSI_ATTRIBUTE_SESSION  = 4,
    AMSI_ATTRIBUTE_REDIRECT_CHAIN_SIZE	= 5,
    AMSI_ATTRIBUTE_REDIRECT_CHAIN_ADDRESS   = 6,
    AMSI_ATTRIBUTE_ALL_SIZE = 7,
    AMSI_ATTRIBUTE_ALL_ADDRESS	= 8
    }

.enum AMSI_UAC_REQUEST_TYPE {
    AMSI_UAC_REQUEST_TYPE_EXE	= 0,
    AMSI_UAC_REQUEST_TYPE_COM	= 1,
    AMSI_UAC_REQUEST_TYPE_MSI	= 2,
    AMSI_UAC_REQUEST_TYPE_AX	= 3,
    AMSI_UAC_REQUEST_TYPE_PACKAGED_APP	= 4,
    AMSI_UAC_REQUEST_TYPE_MAX	= 5
    }

.enum AMSI_UAC_TRUST_STATE {
    AMSI_UAC_TRUST_STATE_TRUSTED    = 0,
    AMSI_UAC_TRUST_STATE_UNTRUSTED  = 1,
    AMSI_UAC_TRUST_STATE_BLOCKED    = 2,
    AMSI_UAC_TRUST_STATE_MAX	= 3
    }

.enum AMSI_UAC_MSI_ACTION {
    AMSI_UAC_MSI_ACTION_INSTALL = 0,
    AMSI_UAC_MSI_ACTION_UNINSTALL   = 1,
    AMSI_UAC_MSI_ACTION_UPDATE	= 2,
    AMSI_UAC_MSI_ACTION_MAINTENANCE = 3,
    AMSI_UAC_MSI_ACTION_MAX = 4
    }

AMSI_UAC_REQUEST_EXE_INFO STRUC
ulLength		ULONG ?
lpwszApplicationName	LPWSTR ?
lpwszCommandLine	LPWSTR ?
lpwszDLLParameter	LPWSTR ?
AMSI_UAC_REQUEST_EXE_INFO ENDS
LPAMSI_UAC_REQUEST_EXE_INFO typedef ptr AMSI_UAC_REQUEST_EXE_INFO

AMSI_UAC_REQUEST_COM_INFO STRUC
ulLength		ULONG ?
lpwszServerBinary	LPWSTR ?
lpwszRequestor		LPWSTR ?
Clsid			GUID <>
AMSI_UAC_REQUEST_COM_INFO ENDS
LPAMSI_UAC_REQUEST_COM_INFO typedef ptr AMSI_UAC_REQUEST_COM_INFO

LPLPWSTR		typedef ptr LPWSTR
AMSI_UAC_REQUEST_MSI_INFO STRUC
ulLength		ULONG ?
MsiAction		AMSI_UAC_MSI_ACTION ?
lpwszProductName	LPWSTR ?
lpwszVersion		LPWSTR ?
lpwszLanguage		LPWSTR ?
lpwszManufacturer	LPWSTR ?
lpwszPackagePath	LPWSTR ?
lpwszPackageSource	LPWSTR ?
ulUpdates		ULONG ?
ppwszUpdates		LPLPWSTR ?
ppwszUpdateSources	LPLPWSTR ?
AMSI_UAC_REQUEST_MSI_INFO ENDS
LPAMSI_UAC_REQUEST_MSI_INFO typedef ptr AMSI_UAC_REQUEST_MSI_INFO

AMSI_UAC_REQUEST_AX_INFO STRUC
ulLength		ULONG ?
lpwszLocalInstallPath	LPWSTR ?
lpwszSourceURL		LPWSTR ?
AMSI_UAC_REQUEST_AX_INFO ENDS
LPAMSI_UAC_REQUEST_AX_INFO typedef ptr AMSI_UAC_REQUEST_AX_INFO

AMSI_UAC_REQUEST_PACKAGED_APP_INFO STRUC
ulLength		ULONG ?
lpwszApplicationName	LPWSTR ?
lpwszCommandLine	LPWSTR ?
lpPackageFamilyName	LPWSTR ?
lpApplicationId		LPWSTR ?
AMSI_UAC_REQUEST_PACKAGED_APP_INFO ENDS
LPAMSI_UAC_REQUEST_PACKAGED_APP_INFO typedef ptr AMSI_UAC_REQUEST_PACKAGED_APP_INFO

AMSI_UAC_REQUEST_CONTEXT STRUC
ulLength		ULONG ?
ulRequestorProcessId	ULONG ?
UACTrustState		AMSI_UAC_TRUST_STATE ?
Type			AMSI_UAC_REQUEST_TYPE ?
union RequestType
 ExeInfo		AMSI_UAC_REQUEST_EXE_INFO <>
 ComInfo		AMSI_UAC_REQUEST_COM_INFO <>
 MsiInfo		AMSI_UAC_REQUEST_MSI_INFO <>
 ActiveXInfo		AMSI_UAC_REQUEST_AX_INFO <>
 PackagedAppInfo	AMSI_UAC_REQUEST_PACKAGED_APP_INFO <>
ENDS
bAutoElevateRequest	BOOL ?
AMSI_UAC_REQUEST_CONTEXT ENDS
LPAMSI_UAC_REQUEST_CONTEXT typedef ptr AMSI_UAC_REQUEST_CONTEXT

ifndef __IAmsiStream_INTERFACE_DEFINED__
define __IAmsiStream_INTERFACE_DEFINED__

DEFINE_IIDX(IAmsiStream, "3e47f2e5-81d4-4d3b-897f-545096770373")

.comdef IAmsiStream : public IUnknown

    GetAttribute	proc :AMSI_ATTRIBUTE, :ULONG, :ptr, :ptr
    Read		proc :ULONGLONG, :ULONG, :ptr, :ptr
   .ends

endif

ifndef __IAntimalwareProvider_INTERFACE_DEFINED__
define __IAntimalwareProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IAntimalwareProvider, "b2cabfe3-fe04-42b1-a5df-08d483d4d125")

.comdef IAntimalwareProvider : public IUnknown

    Scan		proc :ptr, :ptr
    CloseSession	proc :ULONGLONG
    DisplayName		proc :ptr
   .ends

endif

ifndef __IAntimalwareUacProvider_INTERFACE_DEFINED__
define __IAntimalwareUacProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IAntimalwareUacProvider, "b2cabfe4-fe04-42b1-a5df-08d483d4d125")

.comdef IAntimalwareUacProvider : public IUnknown

    UacScan		proc :LPAMSI_UAC_REQUEST_CONTEXT, :ptr
    DisplayName		proc :ptr
   .ends

endif

ifndef __IAntimalware_INTERFACE_DEFINED__
define __IAntimalware_INTERFACE_DEFINED__

DEFINE_IIDX(IAntimalware, "82d29c2e-f062-44e6-b5c9-3d9a2f24a2df")

.comdef IAntimalware : public IUnknown

    Scan		proc :ptr, :ptr, :ptr
    CloseSession	proc :ULONGLONG
   .ends

endif

DEFINE_GUIDS(CAntimalware, "fdb00e52-a214-4aa1-8fba-4357bb0072ec")
DEFINE_GUIDS(CLSID_Antimalware, "fdb00e52-a214-4aa1-8fba-4357bb0072ec")

DECLARE_HANDLE(HAMSICONTEXT)
DECLARE_HANDLE(HAMSISESSION)

AmsiInitialize proto __cdecl :LPCWSTR, :ptr
AmsiUninitialize proto __cdecl :HAMSICONTEXT
AmsiOpenSession proto __cdecl :HAMSICONTEXT, :ptr
AmsiCloseSession proto __cdecl :HAMSICONTEXT, :HAMSISESSION
AmsiScanBuffer proto __cdecl :HAMSICONTEXT, :ptr, :ULONG, :LPCWSTR, :HAMSISESSION, :ptr
AmsiScanString proto __cdecl :HAMSICONTEXT, :LPCWSTR, :LPCWSTR, :HAMSISESSION, :ptr

endif

endif
.pragma list(pop)

