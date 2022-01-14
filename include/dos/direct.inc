ifndef __LIBC_INC
 include libc.inc
endif

define _MAX_PATH  260
define _MAX_DRIVE 3
define _MAX_DIR	  256
define _MAX_FNAME 256
define _MAX_EXT	  256

_getdrive proto __ctype
_chdrive  proto __ctype :sword
_chdir	  proto __ctype :ptr sbyte
_mkdir	  proto __ctype :ptr sbyte
_rmdir	  proto __ctype :ptr sbyte
_getcwd	  proto __ctype :ptr sbyte, :word
_getdcwd  proto __ctype :sword, :ptr sbyte, :sword
_wchdir	  proto __ctype :ptr word
_wmkdir	  proto __ctype :ptr word
_wrmdir	  proto __ctype :ptr word
_wgetcwd  proto __ctype :ptr word, :sword
_wgetdcwd proto __ctype :sword, :ptr word, :sword
