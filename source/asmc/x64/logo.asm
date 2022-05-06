; LOGO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include asmc.inc

public cp_logo
public banner_printed

include logo.inc

.code

write_logo proc __ccall

    .if ( !banner_printed )
	mov banner_printed,1
	tprintf( &cp_logo )
	tprintf( "\n%s\n", &cp_copyright )
    .endif
    ret

write_logo endp

write_usage proc __ccall

    write_logo()
    tprintf( &cp_usage )
    ret

write_usage endp

write_options proc __ccall

    write_logo()
    tprintf( &cp_options )
    ret

write_options endp

    end
