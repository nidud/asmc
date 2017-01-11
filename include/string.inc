ifndef __LIBC_INC
 include libc.inc
endif

.xlist
IFDEF __PE__
option		dllimport:<msvcrt>
ENDIF

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

; _UNICODE

wcscat		PROTO :LPWSTR, :LPWSTR
wcslen		PROTO :LPWSTR
wcschr		PROTO :LPWSTR, :SIZE_T
wcscmp		PROTO :LPWSTR, :LPWSTR
wcscpy		PROTO :LPWSTR, :LPWSTR
wcsstr		PROTO :LPWSTR, :LPWSTR
wcstok		PROTO :LPWSTR, :LPWSTR
wcsncpy		PROTO :LPWSTR, :LPWSTR, :SIZE_T
wcsncmp		PROTO :LPWSTR, :LPWSTR, :SIZE_T
wcsncat		PROTO :LPWSTR, :LPWSTR, :SIZE_T
wcsrchr		PROTO :LPWSTR, :SIZE_T
wcspbrk		PROTO :LPWSTR, :LPWSTR

;;;;;;;;;;;;;;; crtl

IFNDEF __PE__
strfn		PROTO :LPSTR
strext		PROTO :LPSTR
setfext		PROTO :LPSTR, :LPSTR
strfcat		PROTO :LPSTR, :LPSTR, :LPSTR
memxchg		PROTO :LPSTR, :LPSTR, :SIZE_T

memzero		PROTO :LPSTR, :SIZE_T
cmpwarg		PROTO :LPSTR, :LPSTR
cmpwargs	PROTO :LPSTR, :LPSTR
dostounix	PROTO :LPSTR
unixtodos	PROTO :LPSTR
strxchg		PROTO :LPSTR, :LPSTR, :LPSTR
strpath		PROTO :LPSTR
strnzcpy	PROTO :LPSTR, :LPSTR, :SIZE_T
strstart	PROTO :LPSTR
strspace	PROTO :LPSTR
strtrim		PROTO :LPSTR
strtoken	PROTO :LPSTR
strstri		PROTO :LPSTR, :LPSTR
ELSE
option		dllimport:<kernel32>
ENDIF

;;;;;;;;;;;;;;; kernel32

lstrcatA	PROTO _CType :LPSTR, :LPSTR
lstrcatW	PROTO _CType :LPWSTR, :LPWSTR
lstrcmpA	PROTO _CType :LPSTR, :LPSTR
lstrcmpW	PROTO _CType :LPWSTR, :LPWSTR
lstrcmpiA	PROTO _CType :LPSTR, :LPSTR
lstrcmpiW	PROTO _CType :LPWSTR, :LPWSTR
lstrcpyA	PROTO _CType :LPSTR, :LPSTR
lstrcpyW	PROTO _CType :LPWSTR, :LPWSTR
lstrcpynA	PROTO _CType :LPSTR, :LPSTR, :SIZE_T
lstrcpynW	PROTO _CType :LPWSTR, :LPWSTR, :SIZE_T
lstrlenA	PROTO _CType :LPSTR
lstrlenW	PROTO _CType :LPWSTR

IFDEF _UNICODE
lstrcat		equ <lstrcatW>
lstrcmp		equ <lstrcmpW>
lstrcmpi	equ <lstrcmpiW>
lstrcpy		equ <lstrcpyW>
lstrcpyn	equ <lstrcpynW>
lstrlen		equ <lstrlenW>
ELSE
lstrcat		equ <lstrcatA>
lstrcmp		equ <lstrcmpA>
lstrcmpi	equ <lstrcmpiA>
lstrcpy		equ <lstrcpyA>
lstrcpyn	equ <lstrcpynA>
lstrlen		equ <lstrlenA>
ENDIF

.list
