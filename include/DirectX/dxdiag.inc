ifndef _DXDIAG_H_
define _DXDIAG_H_
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include ole2.inc

DXDIAG_DX9_SDK_VERSION equ 111

DXDIAG_E_INSUFFICIENT_BUFFER equ 0x8007007A

DEFINE_GUID(CLSID_DxDiagProvider, 0xA65B8071, 0x3BFE, 0x4213, 0x9A, 0x5B, 0x49, 0x1D, 0xA4, 0x46, 0x1C, 0xA7)
DEFINE_GUID(IID_IDxDiagProvider, 0x9C6B4CB0, 0x23F8, 0x49CC, 0xA3, 0xED, 0x45, 0xA5, 0x50, 0x00, 0xA6, 0xD2)
DEFINE_GUID(IID_IDxDiagContainer, 0x7D0F462F, 0x4064, 0x4862, 0xBC, 0x7F, 0x93, 0x3E, 0x50, 0x58, 0xC1, 0x0F)

LPDXDIAGPROVIDER    typedef ptr IDxDiagProvider
PDXDIAGPROVIDER     typedef ptr IDxDiagProvider
LPDXDIAGCONTAINER   typedef ptr IDxDiagContainer
PDXDIAGCONTAINER    typedef ptr IDxDiagContainer

DXDIAG_INIT_PARAMS      STRUC 8
dwSize                  DWORD ?
dwDxDiagHeaderVersion   DWORD ?
bAllowWHQLChecks        BOOL ?
pReserved               PVOID ?
DXDIAG_INIT_PARAMS      ENDS

.comdef IDxDiagProvider : public IUnknown
    Initialize          proc :ptr
    GetRootContainer    proc :ptr
    .ENDS


.comdef IDxDiagContainer : public IUnknown

    GetNumberOfChildContainers proc :ptr
    EnumChildContainerNames proc :DWORD, :LPWSTR, :DWORD
    GetChildContainer       proc :LPCWSTR, :ptr
    GetNumberOfProps        proc :ptr
    EnumPropNames           proc :DWORD, :LPWSTR, :DWORD
    GetProp                 proc :LPCWSTR, :ptr
    .ENDS


endif
endif
