ifndef _UNISTD_H
define _UNISTD_H
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

sleep       proto __cdecl :dword
ifndef __NO_ISOCEXT
include sys/types.inc
usleep      proto __cdecl :useconds_t
endif

ifndef FTRUNCATE_DEFINED
define FTRUNCATE_DEFINED
ftruncate64 proto __cdecl :int_t, :off64_t
truncate    proto __cdecl :ptr, :off32_t
truncate64  proto __cdecl :ptr, :off64_t
endif

ifndef _FILE_OFFSET_BITS_SET_FTRUNCATE
define _FILE_OFFSET_BITS_SET_FTRUNCATE
if (defined(_FILE_OFFSET_BITS) and (_FILE_OFFSET_BITS eq 64))
define ftruncate <ftruncate64>
endif
endif

ifndef _CRT_SWAB_DEFINED
define _CRT_SWAB_DEFINED
swab        proto __cdecl :string_t, :string_t, :int_t
endif

ifndef _CRT_GETPID_DEFINED
define _CRT_GETPID_DEFINED
getpid      proto __cdecl
endif

chroot      proto __cdecl :string_t
unlink      proto __cdecl :string_t
fsync       proto __cdecl :int_t
pipe        proto __cdecl :ptr int_t
alarm       proto __cdecl :uint_t
chown       proto __cdecl :string_t, :uid_t, :gid_t
fchown      proto __cdecl :int_t, :uid_t, :gid_t
fdatasync   proto __cdecl :int_t
fork        proto __cdecl

_dup        proto __cdecl :int_t
_dup2       proto __cdecl :int_t, :int_t

execl       proto __Cdecl :string_t, :string_t, :vararg
execle      proto __Cdecl :string_t, :string_t, :vararg
execlp      proto __Cdecl :string_t, :string_t, :vararg
execlpe     proto __Cdecl :string_t, :string_t, :vararg
execv       proto __cdecl :string_t, :array_t
execve      proto __cdecl :string_t, :array_t, :array_t
execvp      proto __cdecl :string_t, :array_t
execvpe     proto __cdecl :string_t, :array_t, :array_t

endif
