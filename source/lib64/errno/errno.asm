; ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

PUBLIC	errno
PUBLIC	oserrno

	.data
	errno	dd 0
	oserrno dd 0

	END
