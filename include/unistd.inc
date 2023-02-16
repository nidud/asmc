ifndef _UNISTD_H
define _UNISTD_H
define __UNISTD_H_SOURCED__ 1

include io.inc

ifndef SEEK_SET
define SEEK_SET 0
define SEEK_CUR 1
define SEEK_END 2
endif

ifndef STDIN_FILENO
define STDIN_FILENO  0
define STDOUT_FILENO 1
define STDERR_FILENO 2
endif

ifdef _POSIX_SOURCE

ifndef SHUT_RDWR
define SHUT_RD   0x00
define SHUT_WR   0x01
define SHUT_RDWR 0x02
endif

endif

undef sleep
sleep proto __cdecl :dword

if not defined(__NO_ISOCEXT)
include sys/types.inc

usleep proto __cdecl :useconds_t
endif

ifndef FTRUNCATE_DEFINED
define FTRUNCATE_DEFINED

if not defined(NO_OLDNAMES) or defined(_POSIX)
ftruncate64 proto __cdecl :sdword, :off64_t
truncate proto __cdecl :ptr, :off32_t
truncate64 proto __cdecl :ptr, :off64_t
ifndef __CRT__NO_INLINE
;ftruncate proto __cdecl __fd:sdword, __length:off32_t {
;    _chsize(__fd, __length)
;    }
else
;ftruncate proto __cdecl :sdword, :off32_t
endif
else
ftruncate64 proto __cdecl :sdword, :_off64_t
truncate proto __cdecl :ptr, :_off_t
truncate64 proto __cdecl :ptr, :_off64_t
ifndef __CRT__NO_INLINE
;ftruncate proto __cdecl __fd:sdword, __length:_off_t {
;    _chsize(__fd, __length)
;    }
else
;ftruncate proto __cdecl :sdword, :_off_t
endif
endif
endif

ifndef _FILE_OFFSET_BITS_SET_FTRUNCATE
define _FILE_OFFSET_BITS_SET_FTRUNCATE
if (defined(_FILE_OFFSET_BITS) and (_FILE_OFFSET_BITS eq 64))
define ftruncate <ftruncate64>
endif
endif

ifndef _CRT_SWAB_DEFINED
define _CRT_SWAB_DEFINED
swab proto __cdecl :ptr sbyte, :ptr sbyte, :sdword
endif

ifndef _CRT_GETPID_DEFINED
define _CRT_GETPID_DEFINED
getpid proto __cdecl
endif
undef __UNISTD_H_SOURCED__
endif
