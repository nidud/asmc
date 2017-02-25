ifndef __LIBC_INC
 include libc.inc
endif

.xlist
ifdef __PE__
option		dllimport:<msvcrt>
endif

memchr		PROTO :LPSTR, :SIZE_T,:SIZE_T
memcpy		PROTO :LPSTR, :LPSTR, :SIZE_T
memmove		PROTO :LPSTR, :LPSTR, :SIZE_T
memcmp		PROTO :LPSTR, :LPSTR, :SIZE_T
memset		PROTO :LPSTR, :SIZE_T,:SIZE_T
_memicmp	PROTO :LPSTR, :LPSTR, :SIZE_T

strlen		PROTO :LPSTR
strchr		PROTO :LPSTR, :SIZE_T
strcmp		PROTO :LPSTR, :LPSTR
strncmp		PROTO :LPSTR, :LPSTR, :SIZE_T
strcpy		PROTO :LPSTR, :LPSTR
strncpy		PROTO :LPSTR, :LPSTR, :SIZE_T
strcat		PROTO :LPSTR, :LPSTR
_stricmp	PROTO :LPSTR, :LPSTR
_strnicmp	PROTO :LPSTR, :LPSTR, :SIZE_T
_strupr		PROTO :LPSTR
_strrev		PROTO :LPSTR
_strlwr		PROTO :LPSTR
strrchr		PROTO :LPSTR, :SIZE_T
strstr		PROTO :LPSTR, :LPSTR
_mbspbrk	PROTO :LPSTR, :LPSTR

ifndef _WSTRING_DEFINED

wcscat		proto :ptr wchar_t, :ptr wchar_t
wcschr		proto :ptr wchar_t, :wchar_t
wcscmp		proto :ptr wchar_t, :ptr wchar_t
wcscpy		proto :ptr wchar_t, :ptr wchar_t
wcscspn		proto :ptr wchar_t, :ptr wchar_t
wcslen		proto :ptr wchar_t
wcsncat		proto :ptr wchar_t, :ptr wchar_t, :size_t
wcsncmp		proto :ptr wchar_t, :ptr wchar_t, :size_t
wcsncpy		proto :ptr wchar_t, :ptr wchar_t, :size_t
wcspbrk		proto :ptr wchar_t, :ptr wchar_t
wcsrchr		proto :ptr wchar_t, :wchar_t
wcsspn		proto :ptr wchar_t, :ptr wchar_t
wcsstr		proto :ptr wchar_t, :ptr wchar_t
wcstok		proto :ptr wchar_t, :ptr wchar_t
_wcsdup		proto :ptr wchar_t
_wcsicmp	proto :ptr wchar_t, :ptr wchar_t
_wcsnicmp	proto :ptr wchar_t, :ptr wchar_t, :size_t
_wcsnset	proto :ptr wchar_t, :wchar_t, :size_t
_wcsrev		proto :ptr wchar_t
_wcsset		proto :ptr wchar_t, :wchar_t
_wcslwr		proto :ptr wchar_t
_wcsupr		proto :ptr wchar_t
wcsxfrm		proto :ptr wchar_t, :ptr wchar_t, :size_t
wcscoll		proto :ptr wchar_t, :ptr wchar_t
_wcsicoll	proto :ptr wchar_t, :ptr wchar_t
_wcsncoll	proto :ptr wchar_t, :ptr wchar_t, :size_t
_wcsnicoll	proto :ptr wchar_t, :ptr wchar_t, :size_t

;; Old names
wcswcs		equ <wcsstr>

ifndef __STDC__

;; prototypes for oldnames.lib functions
wcsdup		proto :ptr wchar_t
wcsicmp		proto :ptr wchar_t, :ptr wchar_t
wcsnicmp	proto :ptr wchar_t, :ptr wchar_t, :size_t
wcsnset		proto :ptr wchar_t, :wchar_t, :size_t
wcsrev		proto :ptr wchar_t
wcsset		proto :ptr wchar_t, :wchar_t
wcslwr		proto :ptr wchar_t
wcsupr		proto :ptr wchar_t
wcsicoll	proto :ptr wchar_t, :ptr wchar_t

endif  ;; NOT __STDC__

_WSTRING_DEFINED equ 1
endif

;;;;;;;;;;;;;;; crtl

ifndef __PE__

memxchg		PROTO :LPSTR, :LPSTR, :SIZE_T
memstri		PROTO :LPSTR, :SIZE_T, :LPSTR, :SIZE_T
memrchr		PROTO :LPSTR, :SIZE_T, :SIZE_T
memquote	PROTO :LPSTR, :SIZE_T
memzero		PROTO :LPSTR, :SIZE_T

strfn		PROTO :LPSTR
strext		PROTO :LPSTR
setfext		PROTO :LPSTR, :LPSTR
strfcat		PROTO :LPSTR, :LPSTR, :LPSTR
strxchg		PROTO :LPSTR, :LPSTR, :LPSTR
strpath		PROTO :LPSTR
strnzcpy	PROTO :LPSTR, :LPSTR, :SIZE_T
strstart	PROTO :LPSTR
strspace	PROTO :LPSTR
strtrim		PROTO :LPSTR
strtoken	PROTO :LPSTR
strstri		PROTO :LPSTR, :LPSTR
strins		PROTO :LPSTR, :LPSTR
strtolx		PROTO :LPSTR
strmove		PROTO :LPSTR, :LPSTR
strchri		PROTO :LPSTR, :SIZE_T
streol		PROTO :LPSTR

cmpwarg		PROTO :LPSTR, :LPSTR
cmpwargs	PROTO :LPSTR, :LPSTR
dostounix	PROTO :LPSTR
unixtodos	PROTO :LPSTR

endif

.list
