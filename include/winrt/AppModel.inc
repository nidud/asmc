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

;WINBASEAPI
;LONG

GetCurrentPackageId proto WINAPI \
          bufferLength: ptr UINT32,
                buffer: ptr BYTE

GetCurrentPackageFullName proto WINAPI \
 packageFullNameLength: ptr UINT32,
       packageFullName: PWSTR

GetCurrentPackageFamilyName proto WINAPI \
packageFamilyNameLength: ptr UINT32,
     packageFamilyName: PWSTR

GetCurrentPackagePath proto WINAPI \
            pathLength: ptr UINT32,
                  path: PWSTR

GetPackageId proto WINAPI \
              hProcess: HANDLE,
          bufferLength: ptr UINT32,
                buffer: ptr BYTE

GetPackageFullName proto WINAPI \
              hProcess: HANDLE,
 packageFullNameLength: ptr UINT32,
       packageFullName: PWSTR

GetPackageFamilyName proto WINAPI \
              hProcess: HANDLE,
packageFamilyNameLength: ptr UINT32,
     packageFamilyName: PWSTR

GetPackagePath proto WINAPI \
             packageId: ptr PACKAGE_ID,
              reserved: UINT32,
            pathLength: ptr UINT32,
                  path: PWSTR

if (defined(_CONTRACT_GEN) EQ 0) OR (_APISET_APPMODELRUNTIME_VER GE 0x0101)
GetPackagePathByFullName proto WINAPI \
       packageFullName: PCWSTR,
            pathLength: ptr UINT32,
                  path: PWSTR

GetStagedPackagePathByFullName proto WINAPI \
       packageFullName: PCWSTR,
            pathLength: ptr UINT32,
                  path: PWSTR
endif

GetCurrentApplicationUserModelId proto WINAPI \
applicationUserModelIdLength: ptr UINT32,
applicationUserModelId: PWSTR

GetApplicationUserModelId proto WINAPI \
              hProcess: HANDLE,
applicationUserModelIdLength: ptr UINT32,
applicationUserModelId: PWSTR

PackageIdFromFullName proto WINAPI \
       packageFullName: PCWSTR,
                 flags: UINT32,
          bufferLength: ptr UINT32,
                buffer: ptr BYTE

PackageFullNameFromId proto WINAPI \
             packageId: ptr PACKAGE_ID,
 packageFullNameLength: ptr UINT32,
       packageFullName: PWSTR

PackageFamilyNameFromId proto WINAPI \
             packageId: ptr PACKAGE_ID,
packageFamilyNameLength: ptr UINT32,
     packageFamilyName: PWSTR

PackageFamilyNameFromFullName proto WINAPI \
       packageFullName: PCWSTR,
packageFamilyNameLength: ptr UINT32,
     packageFamilyName: PWSTR

PackageNameAndPublisherIdFromFamilyName proto WINAPI \
     packageFamilyName: PCWSTR,
     packageNameLength: ptr UINT32,
           packageName: PWSTR,
packagePublisherIdLength: ptr UINT32,
    packagePublisherId: PWSTR


if (defined(_CONTRACT_GEN) EQ 0) OR (_APISET_APPMODELRUNTIME_VER GE 0x0101)
FormatApplicationUserModelId proto WINAPI \
     packageFamilyName: PCWSTR,
packageRelativeApplicationId: PCWSTR,
applicationUserModelIdLength: ptr UINT32,
applicationUserModelId: PWSTR

ParseApplicationUserModelId proto WINAPI \
applicationUserModelId: PCWSTR,
packageFamilyNameLength: ptr UINT32,
     packageFamilyName: PWSTR,
packageRelativeApplicationIdLength: ptr UINT32,
packageRelativeApplicationId: PWSTR
endif

GetPackagesByPackageFamily proto WINAPI \
     packageFamilyName: PCWSTR,
                 count: ptr UINT32,
      packageFullNames: ptr PWSTR,
          bufferLength: ptr UINT32,
                buffer: ptr WCHAR

if (defined(_CONTRACT_GEN) EQ 0) OR (_APISET_APPMODELRUNTIME_VER GE 0x0101)

FindPackagesByPackageFamily proto WINAPI \
     packageFamilyName: PCWSTR,
        packageFilters: UINT32,
                 count: ptr UINT32,
      packageFullNames: ptr PWSTR,
          bufferLength: ptr UINT32,
                buffer: ptr WCHAR,
     packageProperties: ptr UINT32


PackageOrigin           typedef SDWORD
PackageOrigin_Unknown   equ 0
PackageOrigin_Unsigned  equ 1
PackageOrigin_Inbox     equ 2
PackageOrigin_Store     equ 3
PackageOrigin_DeveloperUnsigned equ 4
PackageOrigin_DeveloperSigned equ 5
PackageOrigin_LineOfBusiness equ 6

GetStagedPackageOrigin proto WINAPI \
       packageFullName: PCWSTR,
                origin: ptr PackageOrigin

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

GetCurrentPackageInfo proto WINAPI \
                 flags: UINT32,
          bufferLength: ptr UINT32,
                buffer: ptr BYTE,
                 count: ptr UINT32

OpenPackageInfoByFullName proto WINAPI \
       packageFullName: PCWSTR,
              reserved: UINT32,
  packageInfoReference: ptr PACKAGE_INFO_REFERENCE

ClosePackageInfo proto WINAPI \
  packageInfoReference: PACKAGE_INFO_REFERENCE

GetPackageInfo proto WINAPI \
  packageInfoReference: PACKAGE_INFO_REFERENCE,
                 flags: UINT32,
          bufferLength: ptr UINT32,
                buffer: ptr BYTE,
                 count: ptr UINT32

if (defined(_CONTRACT_GEN) EQ 0) OR (_APISET_APPMODELRUNTIME_VER GE 0x0101)

GetPackageApplicationIds proto WINAPI \
  packageInfoReference: PACKAGE_INFO_REFERENCE,
          bufferLength: ptr UINT32,
                buffer: ptr BYTE,
                 count: ptr UINT32

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
