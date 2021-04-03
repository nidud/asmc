include libc.inc
include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

ifndef _APISET_PATH_VER
ifdef _APISET_MINCORE_VERSION
if _APISET_MINCORE_VERSION GE 0x0100
_APISET_PATH_VER equ 0x0100
endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

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

if 0
ifndef PATHCCH_NO_DEPRECATE

undef PathAddBackslash
undef PathAddBackslashA
undef PathAddBackslashW

undef PathAddExtension
undef PathAddExtensionA
undef PathAddExtensionW

undef PathAppend
undef PathAppendA
undef PathAppendW

undef PathCanonicalize
undef PathCanonicalizeA
undef PathCanonicalizeW

undef PathCombine
undef PathCombineA
undef PathCombineW

undef PathRenameExtension
undef PathRenameExtensionA
undef PathRenameExtensionW

ifdef DEPRECATE_SUPPORTED

pragma_deprecated macro p
	exitm<>
	endm

pragma_deprecated(PathIsRelativeWorker)
pragma_deprecated(StrIsEqualWorker)
pragma_deprecated(FindPreviousBackslashWorker)
pragma_deprecated(IsHexDigitWorker)
pragma_deprecated(StringIsGUIDWorker)
pragma_deprecated(PathIsVolumeGUIDWorker)
pragma_deprecated(IsValidExtensionWorker)

pragma_deprecated(PathAddBackslash)
pragma_deprecated(PathAddBackslashA)
pragma_deprecated(PathAddBackslashW)

pragma_deprecated(PathAddExtension)
pragma_deprecated(PathAddExtensionA)
pragma_deprecated(PathAddExtensionW)

pragma_deprecated(PathAppend)
pragma_deprecated(PathAppendA)
pragma_deprecated(PathAppendW)

pragma_deprecated(PathCanonicalize)
pragma_deprecated(PathCanonicalizeA)
pragma_deprecated(PathCanonicalizeW)

pragma_deprecated(PathCombine)
pragma_deprecated(PathCombineA)
pragma_deprecated(PathCombineW)

pragma_deprecated(PathRenameExtension)
pragma_deprecated(PathRenameExtensionA)
pragma_deprecated(PathRenameExtensionW)

else

PathIsRelativeWorker	equ <PathIsRelativeWorker_is_internal_to_pathcch>
StrIsEqualWorker	equ <StrIsEqualWorker_is_internal_to_pathcch>
FindPreviousBackslashWorker equ <FindPreviousBackslashWorker_is_internal_to_pathcch>
IsHexDigitWorker	equ <IsHexDigitWorker_is_internal_to_pathcch>
StringIsGUIDWorker	equ <StringIsGUIDWorker_is_internal_to_pathcch>
PathIsVolumeGUIDWorker	equ <PathIsVolumeGUIDWorker_is_internal_to_pathcch>
IsValidExtensionWorker	equ <IsValidExtensionWorker_is_internal_to_pathcch>

PathAddBackslash	equ <PathAddBackslash_instead_use_PathCchAddBackslash>
PathAddBackslashA	equ <PathAddBackslash_instead_use_PathCchAddBackslash>
PathAddBackslashW	equ <PathAddBackslash_instead_use_PathCchAddBackslash>

PathAddExtension	equ <PathAddExtension_instead_use_PathCchAddExtension>
PathAddExtensionA	equ <PathAddExtension_instead_use_PathCchAddExtension>
PathAddExtensionW	equ <PathAddExtension_instead_use_PathCchAddExtension>

PathAppend		equ <PathAppend_instead_use_PathCchAppend>
PathAppendA		equ <PathAppend_instead_use_PathCchAppend>
PathAppendW		equ <PathAppend_instead_use_PathCchAppend>

PathCanonicalize	equ <PathCanonicalize_instead_use_PathCchCanonicalize>
PathCanonicalizeA	equ <PathCanonicalize_instead_use_PathCchCanonicalize>
PathCanonicalizeW	equ <PathCanonicalize_instead_use_PathCchCanonicalize>

PathCombine		equ <PathCombine_instead_use_PathCchCombine>
PathCombineA		equ <PathCombine_instead_use_PathCchCombine>
PathCombineW		equ <PathCombine_instead_use_PathCchCombine>

PathRenameExtension	equ <PathRenameExtension_instead_use_PathCchRenameExtension>
PathRenameExtensionA	equ <PathRenameExtension_instead_use_PathCchRenameExtension>
PathRenameExtensionW	equ <PathRenameExtension_instead_use_PathCchRenameExtension>

endif
endif

endif

endif

