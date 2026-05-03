; AMBLKSIZ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

PUBLIC _amblksiz

	.data
	_amblksiz dd _HEAP_GROWSIZE

	END
