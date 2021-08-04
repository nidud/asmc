include libc.inc
include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

.pragma comment(lib, kernelbase, "api-ms-win-core-path-l1-1-0")

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum PATHCCH_OPTIONS {
    PATHCCH_NONE = 0x0,
    PATHCCH_ALLOW_LONG_PATHS = 0x01,
    PATHCCH_FORCE_ENABLE_LONG_NAME_PROCESS = 0x02,
    PATHCCH_FORCE_DISABLE_LONG_NAME_PROCESS = 0x04,
    PATHCCH_DO_NOT_NORMALIZE_SEGMENTS = 0x08,
    PATHCCH_ENSURE_IS_EXTENDED_LENGTH_PATH = 0x10,
    PATHCCH_ENSURE_TRAILING_SLASH = 0x020,
    }

PATHCCH_ALLOW_LONG_PATHS equ 0x00000001

VOLUME_PREFIX		equ <L"\\\\?\\Volume">
VOLUME_PREFIX_LEN	equ (ARRAYSIZE(VOLUME_PREFIX) - 1)

PATHCCH_MAX_CCH		equ 0x8000

;BOOL
PathIsUNCEx proto WINAPI \
	       pszPath: PCWSTR,
	    ppszServer: ptr PCWSTR


;BOOL
PathCchIsRoot proto WINAPI \
	       pszPath: PCWSTR


;HRESULT
PathCchAddBackslashEx proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t,
	       ppszEnd: ptr PWSTR,
	 pcchRemaining: ptr size_t


;HRESULT
PathCchAddBackslash proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t


;HRESULT
PathCchRemoveBackslashEx proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t,
	       ppszEnd: ptr PWSTR,
	 pcchRemaining: ptr size_t


;HRESULT
PathCchRemoveBackslash proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t


;HRESULT
PathCchSkipRoot proto WINAPI \
	       pszPath: PCWSTR,
	   ppszRootEnd: ptr PCWSTR


;HRESULT
PathCchStripToRoot proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t


;HRESULT
PathCchRemoveFileSpec proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t


;HRESULT
PathCchFindExtension proto WINAPI \
	       pszPath: PCWSTR,
	       cchPath: size_t,
	       ppszExt: ptr PCWSTR


;HRESULT
PathCchAddExtension proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t,
		pszExt: PCWSTR


;HRESULT
PathCchRenameExtension proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t,
		pszExt: PCWSTR


;HRESULT
PathCchRemoveExtension proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t


;HRESULT
PathCchCanonicalizeEx proto WINAPI \
	    pszPathOut: PWSTR,
	    cchPathOut: size_t,
	     pszPathIn: PCWSTR,
	       dwFlags: DWORD


;HRESULT
PathCchCanonicalize proto WINAPI \
	    pszPathOut: PWSTR,
	    cchPathOut: size_t,
	     pszPathIn: PCWSTR


;HRESULT
PathCchCombineEx proto WINAPI \
	    pszPathOut: PWSTR,
	    cchPathOut: size_t,
	     pszPathIn: PCWSTR,
	       pszMore: PCWSTR,
	       dwFlags: DWORD


;HRESULT
PathCchCombine proto WINAPI \
	    pszPathOut: PWSTR,
	    cchPathOut: size_t,
	     pszPathIn: PCWSTR,
	       pszMore: PCWSTR


;HRESULT
PathCchAppendEx proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t,
	       pszMore: PCWSTR,
	       dwFlags: DWORD

;HRESULT
PathCchAppend proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t,
	       pszMore: PCWSTR


;HRESULT
PathCchStripPrefix proto WINAPI \
	       pszPath: PWSTR,
	       cchPath: size_t


;HRESULT
PathAllocCombine proto WINAPI \
	     pszPathIn: PCWSTR,
	       pszMore: PCWSTR,
	       dwFlags: DWORD,
	   ppszPathOut: ptr PWSTR


;HRESULT
PathAllocCanonicalize proto WINAPI \
	     pszPathIn: PCWSTR,
	       dwFlags: DWORD,
	   ppszPathOut: ptr PWSTR

endif

