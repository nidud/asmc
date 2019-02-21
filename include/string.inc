ifndef __STRING_INC
__STRING_INC equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
ifdef __PE__
option	dllimport:<msvcrt>
else
includelib libc.lib
endif

memchr		proto __cdecl :LPSTR, :SIZE_T,:SIZE_T
memcpy		proto __cdecl :LPSTR, :LPSTR, :SIZE_T
memmove		proto __cdecl :LPSTR, :LPSTR, :SIZE_T
memcmp		proto __cdecl :LPSTR, :LPSTR, :SIZE_T
memset		proto __cdecl :LPSTR, :SINT,:SIZE_T
_memicmp	proto __cdecl :LPSTR, :LPSTR, :SIZE_T

strlen		proto __cdecl :LPSTR
strchr		proto __cdecl :LPSTR, :SIZE_T
strcmp		proto __cdecl :LPSTR, :LPSTR
strncmp		proto __cdecl :LPSTR, :LPSTR, :SIZE_T
strcpy		proto __cdecl :LPSTR, :LPSTR
strncpy		proto __cdecl :LPSTR, :LPSTR, :SIZE_T
strcat		proto __cdecl :LPSTR, :LPSTR
_stricmp	proto __cdecl :LPSTR, :LPSTR
_strnicmp	proto __cdecl :LPSTR, :LPSTR, :SIZE_T
_strupr		proto __cdecl :LPSTR
_strdup		proto __cdecl :LPSTR
_strrev		proto __cdecl :LPSTR
_strlwr		proto __cdecl :LPSTR
strrchr		proto __cdecl :LPSTR, :SIZE_T
strstr		proto __cdecl :LPSTR, :LPSTR
_mbspbrk	proto __cdecl :LPSTR, :LPSTR
_strset		proto __cdecl :LPSTR, :SINT
_strnset	proto __cdecl :LPSTR, :SINT, :SIZE_T
strtok		proto __cdecl :LPSTR, :LPSTR

ifndef _WSTRING_DEFINED

wcscat		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcschr		proto __cdecl :ptr wchar_t, :wchar_t
wcscmp		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcscpy		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcscspn		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcslen		proto __cdecl :ptr wchar_t
wcsncat		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcsncmp		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcsncpy		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcspbrk		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcsrchr		proto __cdecl :ptr wchar_t, :wchar_t
wcsspn		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcsstr		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcstok		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wcsdup		proto __cdecl :ptr wchar_t
_wcsicmp	proto __cdecl :ptr wchar_t, :ptr wchar_t
_wcsnicmp	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
_wcsnset	proto __cdecl :ptr wchar_t, :wchar_t, :size_t
_wcsrev		proto __cdecl :ptr wchar_t
_wcsset		proto __cdecl :ptr wchar_t, :wchar_t
_wcslwr		proto __cdecl :ptr wchar_t
_wcsupr		proto __cdecl :ptr wchar_t
wcsxfrm		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcscoll		proto __cdecl :ptr wchar_t, :ptr wchar_t
_wcsicoll	proto __cdecl :ptr wchar_t, :ptr wchar_t
_wcsncoll	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
_wcsnicoll	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t

;; Old names
wcswcs		equ <wcsstr>

ifndef __STDC__

;; prototypes for oldnames.lib functions
wcsdup		proto __cdecl :ptr wchar_t
wcsicmp		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcsnicmp	proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t
wcsnset		proto __cdecl :ptr wchar_t, :wchar_t, :size_t
wcsrev		proto __cdecl :ptr wchar_t
wcsset		proto __cdecl :ptr wchar_t, :wchar_t
wcslwr		proto __cdecl :ptr wchar_t
wcsupr		proto __cdecl :ptr wchar_t
wcsicoll	proto __cdecl :ptr wchar_t, :ptr wchar_t

endif  ;; NOT __STDC__

_WSTRING_DEFINED equ 1
endif
.pragma list(pop)
endif
