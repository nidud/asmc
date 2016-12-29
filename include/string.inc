ifndef __LIBC_INC
 include libc.inc
endif

.xlist

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

strfn		PROTO :LPSTR
strext		PROTO :LPSTR
setfext		PROTO :LPSTR, :LPSTR
strfcat		PROTO :LPSTR, :LPSTR, :LPSTR
memxchg		PROTO :LPSTR, :LPSTR, :SIZE_T

;;;;;;;;;;;;;;; kernel32

lstrcatA	PROTO :LPSTR, :LPSTR
lstrcatW	PROTO :LPWSTR, :LPWSTR
lstrcmpA	PROTO :LPSTR, :LPSTR
lstrcmpW	PROTO :LPWSTR, :LPWSTR
lstrcmpiA	PROTO :LPSTR, :LPSTR
lstrcmpiW	PROTO :LPWSTR, :LPWSTR
lstrcpyA	PROTO :LPSTR, :LPSTR
lstrcpyW	PROTO :LPWSTR, :LPWSTR
lstrcpynA	PROTO :LPSTR, :LPSTR, :SIZE_T
lstrcpynW	PROTO :LPWSTR, :LPWSTR, :SIZE_T
lstrlenA	PROTO :LPSTR
lstrlenW	PROTO :LPWSTR

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
