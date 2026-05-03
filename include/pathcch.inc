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

PathIsUNCEx proto WINAPI :PCWSTR, :ptr
PathCchIsRoot proto WINAPI :PCWSTR
PathCchAddBackslashEx proto WINAPI :PWSTR, :size_t, :ptr, :ptr
PathCchAddBackslash proto WINAPI :PWSTR, :size_t
PathCchRemoveBackslashEx proto WINAPI :PWSTR, :size_t, :ptr, :ptr
PathCchRemoveBackslash proto WINAPI :PWSTR, :size_t
PathCchSkipRoot proto WINAPI :PCWSTR, :ptr
PathCchStripToRoot proto WINAPI :PWSTR, :size_t
PathCchRemoveFileSpec proto WINAPI :PWSTR, :size_t
PathCchFindExtension proto WINAPI :PCWSTR, :size_t, :ptr
PathCchAddExtension proto WINAPI :PWSTR, :size_t, :PCWSTR
PathCchRenameExtension proto WINAPI :PWSTR, :size_t, :PCWSTR
PathCchRemoveExtension proto WINAPI :PWSTR, :size_t
PathCchCanonicalizeEx proto WINAPI :PWSTR, :size_t, :PCWSTR, :DWORD
PathCchCanonicalize proto WINAPI :PWSTR, :size_t, :PCWSTR
PathCchCombineEx proto WINAPI :PWSTR, :size_t, :PCWSTR, :PCWSTR, :DWORD
PathCchCombine proto WINAPI :PWSTR, :size_t, :PCWSTR, :PCWSTR
PathCchAppendEx proto WINAPI :PWSTR, :size_t, :PCWSTR, :DWORD
PathCchAppend proto WINAPI :PWSTR, :size_t, :PCWSTR
PathCchStripPrefix proto WINAPI :PWSTR, :size_t
PathAllocCombine proto WINAPI :PCWSTR, :PCWSTR, :DWORD, :ptr
PathAllocCanonicalize proto WINAPI :PCWSTR, :DWORD, :ptr

endif
