.pragma list(push, 0)
ifndef __STRING_INC
__STRING_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif
.pragma comment(lib, libc, msvcrt)

memchr		proto __cdecl :ptr, :int_t, :size_t
memcpy		proto __cdecl :ptr, :ptr, :size_t
memmove		proto __cdecl :ptr, :ptr, :size_t
memcmp		proto __cdecl :ptr, :ptr, :size_t
memset		proto __cdecl :ptr, :int_t, :size_t
_memicmp	proto __cdecl :ptr, :ptr, :size_t
memcpy_s	proto __cdecl :ptr, :size_t, :ptr, :size_t

strlen		proto __cdecl :LPSTR
strchr		proto __cdecl :LPSTR, :int_t
strcmp		proto __cdecl :LPSTR, :LPSTR
strncmp		proto __cdecl :LPSTR, :LPSTR, :size_t
strcpy		proto __cdecl :LPSTR, :LPSTR
strncpy		proto __cdecl :LPSTR, :LPSTR, :size_t
strcat		proto __cdecl :LPSTR, :LPSTR
_stricmp	proto __cdecl :LPSTR, :LPSTR
_strnicmp	proto __cdecl :LPSTR, :LPSTR, :size_t
_strupr		proto __cdecl :LPSTR
_strdup		proto __cdecl :LPSTR
_strrev		proto __cdecl :LPSTR
_strlwr		proto __cdecl :LPSTR
strrchr		proto __cdecl :LPSTR, :int_t
strstr		proto __cdecl :LPSTR, :LPSTR
_mbspbrk	proto __cdecl :LPSTR, :LPSTR
_strset		proto __cdecl :LPSTR, :SINT
_strnset	proto __cdecl :LPSTR, :SINT, :size_t
strtok		proto __cdecl :LPSTR, :LPSTR

strcpy_s	proto __cdecl :string_t, :size_t, :string_t
strcat_s	proto __cdecl :string_t, :size_t, :string_t
strncat_s	proto __cdecl :string_t, :size_t, :string_t, :size_t
strncpy_s	proto __cdecl :string_t, :size_t, :string_t, :size_t
strtok_s	proto __cdecl :string_t, :string_t, :ptr string_t
_strnset_s	proto __cdecl :string_t, :size_t, :uint_t, :size_t
_strset_s	proto __cdecl :string_t, :size_t, :uint_t
_strlwr_s	proto __cdecl :string_t, :size_t
_strupr_s	proto __cdecl :string_t, :size_t
_mbccpy_s	proto __cdecl :string_t, :size_t, :ptr int_t, :string_t


ifndef _WSTRING_DEFINED

wcscat		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcschr		proto __cdecl :ptr wchar_t, :wchar_t
wcscmp		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcscpy		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcscspn		proto __cdecl :ptr wchar_t, :ptr wchar_t
wcslen		proto __cdecl :ptr wchar_t
wcsnlen		proto __cdecl :ptr wchar_t, :size_t
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

wcscpy_s	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t
wcscat_s	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t
wcsncat_s	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :size_t
wcsncpy_s	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :size_t
wcstok_s	proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr ptr wchar_t
_wcsnset_s	proto __cdecl :ptr wchar_t, :size_t, :uint_t, :size_t
_wcsset_s	proto __cdecl :ptr wchar_t, :size_t, :uint_t
_wcslwr_s	proto __cdecl :ptr wchar_t, :size_t
_wcsupr_s	proto __cdecl :ptr wchar_t, :size_t

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
endif
.pragma list(pop)
