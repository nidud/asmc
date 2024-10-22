.pragma list(push, 0)
ifndef __STRING_INC
define __STRING_INC
ifndef __LIBC_INC
 include libc.inc
endif
.pragma comment(lib, libc, msvcrt)

ifdef __UNIX__
define _stricmp <strcasecmp>
define _memicmp <strncasecmp>
define _strdup <strdup>
endif

memchr		proto __cdecl :ptr, :int_t, :size_t
memcpy		proto __cdecl :ptr, :ptr, :size_t
memmove		proto __cdecl :ptr, :ptr, :size_t
memcmp		proto __cdecl :ptr, :ptr, :size_t
memset		proto __cdecl :ptr, :int_t, :size_t
_memicmp	proto __cdecl :ptr, :ptr, :size_t
memcpy_s	proto __cdecl :ptr, :size_t, :ptr, :size_t
memmem		proto __cdecl :ptr, :size_t, :ptr, :size_t

strlen		proto __cdecl :LPSTR
strchr		proto __cdecl :LPSTR, :int_t
strcmp		proto __cdecl :LPSTR, :LPSTR
strncmp		proto __cdecl :LPSTR, :LPSTR, :size_t
strcpy		proto __cdecl :LPSTR, :LPSTR
strncpy		proto __cdecl :LPSTR, :LPSTR, :size_t
strcat		proto __cdecl :LPSTR, :LPSTR
strncat		proto __cdecl :LPSTR, :LPSTR, :size_t
strnlen		proto __cdecl :LPSTR, :size_t
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
strpbrk		proto __cdecl :LPSTR, :LPSTR

strcpy_s	proto __cdecl :LPSTR, :size_t, :LPSTR
strcat_s	proto __cdecl :LPSTR, :size_t, :LPSTR
strncat_s	proto __cdecl :LPSTR, :size_t, :LPSTR, :size_t
strncpy_s	proto __cdecl :LPSTR, :size_t, :LPSTR, :size_t
strtok_s	proto __cdecl :LPSTR, :LPSTR, :ptr LPSTR
_strnset_s	proto __cdecl :LPSTR, :size_t, :uint_t, :size_t
_strset_s	proto __cdecl :LPSTR, :size_t, :uint_t
_strlwr_s	proto __cdecl :LPSTR, :size_t
_strupr_s	proto __cdecl :LPSTR, :size_t
_mbccpy_s	proto __cdecl :LPSTR, :size_t, :ptr int_t, :LPSTR


ifndef _WSTRING_DEFINED
define _WSTRING_DEFINED

wcscat		proto __cdecl :LPWSTR, :LPWSTR
wcschr		proto __cdecl :LPWSTR, :int_t
wcscmp		proto __cdecl :LPWSTR, :LPWSTR
wcscpy		proto __cdecl :LPWSTR, :LPWSTR
wcscspn		proto __cdecl :LPWSTR, :LPWSTR
wcslen		proto __cdecl :LPWSTR
wcsnlen		proto __cdecl :LPWSTR, :size_t
wcsncat		proto __cdecl :LPWSTR, :LPWSTR, :size_t
wcsncmp		proto __cdecl :LPWSTR, :LPWSTR, :size_t
wcsncpy		proto __cdecl :LPWSTR, :LPWSTR, :size_t
wcspbrk		proto __cdecl :LPWSTR, :LPWSTR
wcsrchr		proto __cdecl :LPWSTR, :int_t
wcsspn		proto __cdecl :LPWSTR, :LPWSTR
wcsstr		proto __cdecl :LPWSTR, :LPWSTR
wcstok		proto __cdecl :LPWSTR, :LPWSTR
_wcsdup		proto __cdecl :LPWSTR
_wcsicmp	proto __cdecl :LPWSTR, :LPWSTR
_wcsnicmp	proto __cdecl :LPWSTR, :LPWSTR, :size_t
_wcsnset	proto __cdecl :LPWSTR, :wchar_t, :size_t
_wcsrev		proto __cdecl :LPWSTR
_wcsset		proto __cdecl :LPWSTR, :wchar_t
_wcslwr		proto __cdecl :LPWSTR
_wcsupr		proto __cdecl :LPWSTR
wcsxfrm		proto __cdecl :LPWSTR, :LPWSTR, :size_t
wcscoll		proto __cdecl :LPWSTR, :LPWSTR
_wcsicoll	proto __cdecl :LPWSTR, :LPWSTR
_wcsncoll	proto __cdecl :LPWSTR, :LPWSTR, :size_t
_wcsnicoll	proto __cdecl :LPWSTR, :LPWSTR, :size_t

wcscpy_s	proto __cdecl :LPWSTR, :size_t, :LPWSTR
wcscat_s	proto __cdecl :LPWSTR, :size_t, :LPWSTR
wcsncat_s	proto __cdecl :LPWSTR, :size_t, :LPWSTR, :size_t
wcsncpy_s	proto __cdecl :LPWSTR, :size_t, :LPWSTR, :size_t
wcstok_s	proto __cdecl :LPWSTR, :LPWSTR, :ptr LPWSTR
_wcsnset_s	proto __cdecl :LPWSTR, :size_t, :uint_t, :size_t
_wcsset_s	proto __cdecl :LPWSTR, :size_t, :uint_t
_wcslwr_s	proto __cdecl :LPWSTR, :size_t
_wcsupr_s	proto __cdecl :LPWSTR, :size_t

; Old names

define wcswcs	<wcsstr>

ifndef __STDC__

; prototypes for oldnames.lib functions

wcsdup		proto __cdecl :LPWSTR
wcsicmp		proto __cdecl :LPWSTR, :LPWSTR
wcsnicmp	proto __cdecl :LPWSTR, :LPWSTR, :size_t
wcsnset		proto __cdecl :LPWSTR, :wchar_t, :size_t
wcsrev		proto __cdecl :LPWSTR
wcsset		proto __cdecl :LPWSTR, :wchar_t
wcslwr		proto __cdecl :LPWSTR
wcsupr		proto __cdecl :LPWSTR
wcsicoll	proto __cdecl :LPWSTR, :LPWSTR

endif ;; NOT __STDC__
endif

ifndef strupr
strupr proto watcall :string_t {
    .for ( rcx = rax : byte ptr [rcx] : rcx++ )
	mov dl,[rcx]
	.if ( dl >= 'a' && dl <= 'z' )
	    sub dl,'a' - 'A'
	.endif
	mov [rcx],dl
    .endf
    }
strlwr proto watcall :string_t {
    .for ( rcx = rax : byte ptr [rcx] : rcx++ )
	mov dl,[rcx]
	.if ( dl >= 'A' && dl <= 'Z' )
	    add dl,'a' - 'A'
	.endif
	mov [rcx],dl
    .endf
    }
endif

ifndef _MSVCRT

memxchg		proto __cdecl :ptr, :ptr, :size_t

stristr		proto __cdecl :LPSTR, :LPSTR
strxchg		proto __cdecl :LPSTR, :LPSTR, :LPSTR
strmove		proto __cdecl :LPSTR, :LPSTR
strfn		proto __cdecl :LPSTR
strext		proto __cdecl :LPSTR
strtrim		proto __cdecl :LPSTR
strstart	proto __cdecl :LPSTR
strtrunc	proto __cdecl :LPSTR
strfcat		proto __cdecl :LPSTR, :LPSTR, :LPSTR
strfxcat	proto __cdecl :LPSTR, :LPSTR
strshr		proto __cdecl :LPSTR, :int_t
strwild		proto __cdecl :LPSTR, :LPSTR
stresc		proto __cdecl :LPSTR, :LPSTR
strdos		proto __cdecl :LPSTR
strunix		proto __cdecl :LPSTR

_wstristr	proto __cdecl :LPWSTR, :LPWSTR
_wstrxchg	proto __cdecl :LPWSTR, :LPWSTR, :LPWSTR
_wstrmove	proto __cdecl :LPWSTR, :LPWSTR
_wstrfn		proto __cdecl :LPWSTR
_wstrext	proto __cdecl :LPWSTR
_wstrtrim	proto __cdecl :LPWSTR
_wstrstart	proto __cdecl :LPWSTR
_wstrtrunc	proto __cdecl :LPWSTR
_wstrfcat	proto __cdecl :LPWSTR, :LPWSTR, :LPWSTR
_wstrfxcat	proto __cdecl :LPWSTR, :LPWSTR
_wstrshr	proto __cdecl :LPWSTR, :int_t
_wstrwild	proto __cdecl :LPTSTR, :LPTSTR
_wstresc	proto __cdecl :LPWSTR, :LPWSTR
_wstrdos	proto __cdecl :LPWSTR
_wstrunix	proto __cdecl :LPWSTR

endif

endif
.pragma list(pop)
