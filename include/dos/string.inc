ifndef __STRING_INC
define __STRING_INC
ifndef __LIBC_INC
 include libc.inc
endif

memchr		proto __ctype :ptr, :sword, :word
memcpy		proto __ctype :ptr, :ptr, :word
memmove		proto __ctype :ptr, :ptr, :word
memcmp		proto __ctype :ptr, :ptr, :word
memset		proto __ctype :ptr, :sword, :word
_memicmp	proto __ctype :ptr, :ptr, :word

strlen		proto __ctype :ptr sbyte
strchr		proto __ctype :ptr sbyte, :sword
strcmp		proto __ctype :ptr sbyte, :ptr sbyte
strncmp		proto __ctype :ptr sbyte, :ptr sbyte, :word
strcpy		proto __ctype :ptr sbyte, :ptr sbyte
strncpy		proto __ctype :ptr sbyte, :ptr sbyte, :word
strcat		proto __ctype :ptr sbyte, :ptr sbyte
_stricmp	proto __ctype :ptr sbyte, :ptr sbyte
_strnicmp	proto __ctype :ptr sbyte, :ptr sbyte, :word
_strupr		proto __ctype :ptr sbyte
_strdup		proto __ctype :ptr sbyte
_strrev		proto __ctype :ptr sbyte
_strlwr		proto __ctype :ptr sbyte
strrchr		proto __ctype :ptr sbyte, :sword
strstr		proto __ctype :ptr sbyte, :ptr sbyte
_mbspbrk	proto __ctype :ptr sbyte, :ptr sbyte
_strset		proto __ctype :ptr sbyte, :sword
_strnset	proto __ctype :ptr sbyte, :sword, :word
strtok		proto __ctype :ptr sbyte, :ptr sbyte

ifndef _WSTRING_DEFINED
define _WSTRING_DEFINED
wcscat		proto __ctype :ptr word, :ptr word
wcschr		proto __ctype :ptr word, :word
wcscmp		proto __ctype :ptr word, :ptr word
wcscpy		proto __ctype :ptr word, :ptr word
wcscspn		proto __ctype :ptr word, :ptr word
wcslen		proto __ctype :ptr word
wcsnlen		proto __ctype :ptr word, :word
wcsncat		proto __ctype :ptr word, :ptr word, :word
wcsncmp		proto __ctype :ptr word, :ptr word, :word
wcsncpy		proto __ctype :ptr word, :ptr word, :word
wcspbrk		proto __ctype :ptr word, :ptr word
wcsrchr		proto __ctype :ptr word, :word
wcsspn		proto __ctype :ptr word, :ptr word
wcsstr		proto __ctype :ptr word, :ptr word
wcstok		proto __ctype :ptr word, :ptr word
_wcsdup		proto __ctype :ptr word
_wcsicmp	proto __ctype :ptr word, :ptr word
_wcsnicmp	proto __ctype :ptr word, :ptr word, :word
_wcsnset	proto __ctype :ptr word, :word, :word
_wcsrev		proto __ctype :ptr word
_wcsset		proto __ctype :ptr word, :word
_wcslwr		proto __ctype :ptr word
_wcsupr		proto __ctype :ptr word
wcsxfrm		proto __ctype :ptr word, :ptr word, :word
wcscoll		proto __ctype :ptr word, :ptr word
_wcsicoll	proto __ctype :ptr word, :ptr word
_wcsncoll	proto __ctype :ptr word, :ptr word, :word
_wcsnicoll	proto __ctype :ptr word, :ptr word, :word

ifndef __STDC__
; prototypes for oldnames.lib functions
wcsdup		proto __ctype :ptr word
wcsicmp		proto __ctype :ptr word, :ptr word
wcsnicmp	proto __ctype :ptr word, :ptr word, :word
wcsnset		proto __ctype :ptr word, :word, :word
wcsrev		proto __ctype :ptr word
wcsset		proto __ctype :ptr word, :word
wcslwr		proto __ctype :ptr word
wcsupr		proto __ctype :ptr word
wcsicoll	proto __ctype :ptr word, :ptr word
endif ; NOT __STDC__
endif

endif
