; ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

PUBLIC	errno
PUBLIC	_doserrno

	.data
	errno	  errno_t 0
	_doserrno errno_t 0

	END
