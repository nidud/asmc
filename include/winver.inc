ifndef _WINVER_
define _WINVER_
.pragma list(push, 0)
ifndef __LIBC_INC
include libc.inc
endif

.pragma comment(lib, version)

VS_FILE_INFO		equ RT_VERSION
VS_VERSION_INFO		equ 1
VS_USER_DEFINED		equ 100

ifndef _MAC
VS_FFI_SIGNATURE	equ 0xFEEF04BD
else
VS_FFI_SIGNATURE	equ 0xBD04EFFE
endif
VS_FFI_STRUCVERSION	equ 0x00010000
VS_FFI_FILEFLAGSMASK	equ 0x0000003F

VS_FF_DEBUG		equ 0x00000001
VS_FF_PRERELEASE	equ 0x00000002
VS_FF_PATCHED		equ 0x00000004
VS_FF_PRIVATEBUILD	equ 0x00000008
VS_FF_INFOINFERRED	equ 0x00000010
VS_FF_SPECIALBUILD	equ 0x00000020

VOS_UNKNOWN		equ 0x00000000
VOS_DOS			equ 0x00010000
VOS_OS216		equ 0x00020000
VOS_OS232		equ 0x00030000
VOS_NT			equ 0x00040000

VOS__BASE		equ 0x00000000
VOS__WINDOWS16		equ 0x00000001
VOS__PM16		equ 0x00000002
VOS__PM32		equ 0x00000003
VOS__WINDOWS32		equ 0x00000004

VOS_DOS_WINDOWS16	equ 0x00010001
VOS_DOS_WINDOWS32	equ 0x00010004
VOS_OS216_PM16		equ 0x00020002
VOS_OS232_PM32		equ 0x00030003
VOS_NT_WINDOWS32	equ 0x00040004

VFT_UNKNOWN		equ 0x00000000
VFT_APP			equ 0x00000001
VFT_DLL			equ 0x00000002
VFT_DRV			equ 0x00000003
VFT_FONT		equ 0x00000004
VFT_VXD			equ 0x00000005
VFT_STATIC_LIB		equ 0x00000007

VFT2_UNKNOWN		equ 0x00000000
VFT2_DRV_PRINTER	equ 0x00000001
VFT2_DRV_KEYBOARD	equ 0x00000002
VFT2_DRV_LANGUAGE	equ 0x00000003
VFT2_DRV_DISPLAY	equ 0x00000004
VFT2_DRV_MOUSE		equ 0x00000005
VFT2_DRV_NETWORK	equ 0x00000006
VFT2_DRV_SYSTEM		equ 0x00000007
VFT2_DRV_INSTALLABLE	equ 0x00000008
VFT2_DRV_SOUND		equ 0x00000009
VFT2_DRV_COMM		equ 0x0000000A
VFT2_DRV_INPUTMETHOD	equ 0x0000000B

VFT2_FONT_RASTER	equ 0x00000001
VFT2_FONT_VECTOR	equ 0x00000002
VFT2_FONT_TRUETYPE	equ 0x00000003

VFFF_ISSHAREDFILE	equ 0x0001

VFF_CURNEDEST		equ 0x0001
VFF_FILEINUSE		equ 0x0002
VFF_BUFFTOOSMALL	equ 0x0004

VIFF_FORCEINSTALL	equ 0x0001
VIFF_DONTDELETEOLD	equ 0x0002

VIF_TEMPFILE		equ 0x00000001
VIF_MISMATCH		equ 0x00000002
VIF_SRCOLD		equ 0x00000004

VIF_DIFFLANG		equ 0x00000008
VIF_DIFFCODEPG		equ 0x00000010
VIF_DIFFTYPE		equ 0x00000020

VIF_WRITEPROT		equ 0x00000040
VIF_FILEINUSE		equ 0x00000080
VIF_OUTOFSPACE		equ 0x00000100
VIF_ACCESSVIOLATION	equ 0x00000200
VIF_SHARINGVIOLATION	equ 0x00000400
VIF_CANNOTCREATE	equ 0x00000800
VIF_CANNOTDELETE	equ 0x00001000
VIF_CANNOTRENAME	equ 0x00002000
VIF_CANNOTDELETECUR	equ 0x00004000
VIF_OUTOFMEMORY		equ 0x00008000

VIF_CANNOTREADSRC	equ 0x00010000
VIF_CANNOTREADDST	equ 0x00020000

VIF_BUFFTOOSMALL	equ 0x00040000


VS_FIXEDFILEINFO	STRUC
dwSignature		dd ?
dwStrucVersion		dd ?
dwFileVersionMS		dd ?
dwFileVersionLS		dd ?
dwProductVersionMS	dd ?
dwProductVersionLS	dd ?
dwFileFlagsMask		dd ?
dwFileFlags		dd ?
dwFileOS		dd ?
dwFileType		dd ?
dwFileSubtype		dd ?
dwFileDateMS		dd ?
dwFileDateLS		dd ?
VS_FIXEDFILEINFO	ENDS


PUINT	typedef ptr DWORD

VerFindFileA proto WINAPI :DWORD, :LPSTR, :LPSTR, :LPSTR, :LPSTR, :PUINT, :LPSTR, :PUINT
VerFindFileW proto WINAPI :DWORD, :LPWSTR, :LPWSTR, :LPWSTR, :LPWSTR, :PUINT, :LPWSTR, :PUINT
ifdef _UNICODE
VerFindFile		equ <VerFindFileW>
else
VerFindFile		equ <VerFindFileA>
endif

VerInstallFileA proto WINAPI :DWORD, :LPSTR, :LPSTR, :LPSTR, :LPSTR, :LPSTR, :LPSTR, :PUINT
VerInstallFileW proto WINAPI :DWORD, :LPWSTR, :LPWSTR, :LPWSTR, :LPWSTR, :LPWSTR, :LPWSTR, :PUINT
ifdef _UNICODE
VerInstallFile		equ <VerInstallFileW>
else
VerInstallFile		equ <VerInstallFileA>
endif

GetFileVersionInfoSizeA proto WINAPI :LPSTR, :LPDWORD
GetFileVersionInfoSizeW proto WINAPI :LPWSTR, :LPDWORD
ifdef _UNICODE
GetFileVersionInfoSize	equ <GetFileVersionInfoSizeW>
else
GetFileVersionInfoSize	equ <GetFileVersionInfoSizeA>
endif

GetFileVersionInfoA proto WINAPI :LPSTR, :DWORD, :DWORD, :ptr
GetFileVersionInfoW proto WINAPI :LPWSTR, :DWORD, :DWORD, :ptr
ifdef _UNICODE
GetFileVersionInfo	equ <GetFileVersionInfoW>
else
GetFileVersionInfo	equ <GetFileVersionInfoA>
endif

VerLanguageNameA proto WINAPI :DWORD, :LPSTR, :DWORD
VerLanguageNameW proto WINAPI :DWORD, :LPWSTR, :DWORD
ifdef _UNICODE
VerLanguageName		equ <VerLanguageNameW>
else
VerLanguageName		equ <VerLanguageNameA>
endif

VerQueryValueA proto WINAPI :ptr, :LPSTR, :ptr, :PUINT
VerQueryValueW proto WINAPI :ptr, :LPWSTR, :ptr, :PUINT
ifdef _UNICODE
VerQueryValue		equ <VerQueryValueW>
else
VerQueryValue		equ <VerQueryValueA>
endif

.pragma list(pop)
endif
