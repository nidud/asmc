ifdef _CONTRACT_GEN
include nt.inc
;include ntrtl.inc
;include nturtl.inc
;include windows.inc
include minwindef.inc
endif

ifndef _APISET_APPMODELRUNTIME_VER
ifdef _APISET_TARGET_VERSION
if _APISET_TARGET_VERSION GE _APISET_TARGET_VERSION_WIN10_RS1
_APISET_APPMODELRUNTIME_VER equ 0x0102
elseif _APISET_TARGET_VERSION GE _APISET_TARGET_VERSION_WINBLUE
_APISET_APPMODELRUNTIME_VER equ 0x0101
elseif _APISET_TARGET_VERSION GE _APISET_TARGET_VERSION_WIN8
_APISET_APPMODELRUNTIME_VER equ 0x0100
endif
elseifdef _APISET_MODERNCORE_VERSION
if _APISET_MODERNCORE_VERSION GE 0x0100
_APISET_APPMODELRUNTIME_VER equ 0x0101
endif
endif
endif

;??
ifndef _APISET_APPMODELRUNTIME_VER
_APISET_APPMODELRUNTIME_VER equ 0x0100
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include minappmodel.inc

.pragma pack(push, 4)

PACKAGE_VERSION         STRUC
UNION
 Version                UINT64 ?
 STRUC
  Revision              USHORT ?
  Build                 USHORT ?
  Minor                 USHORT ?
  Major                 USHORT ?
 ENDS
ENDS
PACKAGE_VERSION         ENDS

PACKAGE_ID              STRUC
reserved                UINT32 ?
processorArchitecture   UINT32 ?
version                 PACKAGE_VERSION <>
name                    PWSTR ?
publisher               PWSTR ?
resourceId              PWSTR ?
publisherId             PWSTR ?
PACKAGE_ID              ENDS

.pragma pack(pop)

GetCurrentPackageId proto WINAPI :ptr, :ptr
GetCurrentPackageFullName proto WINAPI :ptr, :PWSTR
GetCurrentPackageFamilyName proto WINAPI :ptr, :PWSTR
GetCurrentPackagePath proto WINAPI :ptr, :PWSTR
GetPackageId proto WINAPI :HANDLE, :ptr, :ptr
GetPackageFullName proto WINAPI :HANDLE, :ptr, :PWSTR
GetPackageFamilyName proto WINAPI :HANDLE, :ptr, :PWSTR
GetPackagePath proto WINAPI :ptr, :UINT32, :ptr, :PWSTR

if (defined(_CONTRACT_GEN) EQ 0) OR (_APISET_APPMODELRUNTIME_VER GE 0x0101)
GetPackagePathByFullName proto WINAPI :PCWSTR, :ptr, :PWSTR
GetStagedPackagePathByFullName proto WINAPI :PCWSTR, :ptr, :PWSTR
endif

GetCurrentApplicationUserModelId proto WINAPI :ptr, :PWSTR
GetApplicationUserModelId proto WINAPI :HANDLE, :ptr, :PWSTR
PackageIdFromFullName proto WINAPI :PCWSTR, :UINT32, :ptr, :ptr
PackageFullNameFromId proto WINAPI :ptr, :ptr, :PWSTR
PackageFamilyNameFromId proto WINAPI :ptr, :ptr, :PWSTR
PackageFamilyNameFromFullName proto WINAPI :PCWSTR, :ptr, :PWSTR
PackageNameAndPublisherIdFromFamilyName proto WINAPI :PCWSTR, :ptr, :PWSTR, :ptr, :PWSTR

if (defined(_CONTRACT_GEN) EQ 0) OR (_APISET_APPMODELRUNTIME_VER GE 0x0101)
FormatApplicationUserModelId proto WINAPI :PCWSTR, :PCWSTR, :ptr, :PWSTR
ParseApplicationUserModelId proto WINAPI :PCWSTR, :ptr, :PWSTR, :ptr, :PWSTR
endif
GetPackagesByPackageFamily proto WINAPI :PCWSTR, :ptr, :ptr, :ptr, :ptr

if (defined(_CONTRACT_GEN) EQ 0) OR (_APISET_APPMODELRUNTIME_VER GE 0x0101)

FindPackagesByPackageFamily proto WINAPI :PCWSTR, :UINT32, :ptr, :ptr, :ptr, :ptr, :ptr

PackageOrigin           typedef SDWORD
PackageOrigin_Unknown   equ 0
PackageOrigin_Unsigned  equ 1
PackageOrigin_Inbox     equ 2
PackageOrigin_Store     equ 3
PackageOrigin_DeveloperUnsigned equ 4
PackageOrigin_DeveloperSigned equ 5
PackageOrigin_LineOfBusiness equ 6

GetStagedPackageOrigin proto WINAPI :PCWSTR, :ptr

endif

PACKAGE_PROPERTY_FRAMEWORK equ 0x00000001
PACKAGE_PROPERTY_RESOURCE equ 0x00000002
PACKAGE_PROPERTY_BUNDLE equ 0x00000004
PACKAGE_FILTER_HEAD     equ 0x00000010
PACKAGE_FILTER_DIRECT   equ 0x00000020
PACKAGE_FILTER_RESOURCE equ 0x00000040
PACKAGE_FILTER_BUNDLE   equ 0x00000080
PACKAGE_INFORMATION_BASIC equ 0x00000000
PACKAGE_INFORMATION_FULL equ 0x00000100
PACKAGE_PROPERTY_DEVELOPMENT_MODE equ 0x00010000


PACKAGE_FILTER_ALL_LOADED equ 0

_PACKAGE_INFO_REFERENCE STRUC
reserved                PVOID ?
_PACKAGE_INFO_REFERENCE ENDS
PACKAGE_INFO_REFERENCE  typedef ptr _PACKAGE_INFO_REFERENCE

.pragma pack(push, 4)

PACKAGE_INFO            STRUC
reserved                UINT32 ?
flags                   UINT32 ?
path                    PWSTR ?
packageFullName         PWSTR ?
packageFamilyName       PWSTR ?
packageId               PACKAGE_ID <>
PACKAGE_INFO            ENDS

.pragma pack(pop)

GetCurrentPackageInfo proto WINAPI :UINT32, :ptr, :ptr, :ptr
OpenPackageInfoByFullName proto WINAPI :PCWSTR, :UINT32, :ptr
ClosePackageInfo proto WINAPI :PACKAGE_INFO_REFERENCE
GetPackageInfo proto WINAPI :PACKAGE_INFO_REFERENCE, :UINT32, :ptr, :ptr, :ptr

if (defined(_CONTRACT_GEN) EQ 0) OR (_APISET_APPMODELRUNTIME_VER GE 0x0101)
GetPackageApplicationIds proto WINAPI :PACKAGE_INFO_REFERENCE, :ptr, :ptr, :ptr
endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
