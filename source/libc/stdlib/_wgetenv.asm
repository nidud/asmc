; _WGETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

_wgetenv proc uses rsi rdi enval:wstring_t
ifdef __UNIX__
    int 3
else
    ldr rcx,enval
    .ifd ( wcslen( rcx ) == 0 )
	.return
    .endif

    mov edi,eax
    mov rsi,_wenviron
ifdef _WIN64
    lodsq
else
    lodsd
endif

    .while ( rax )

	.ifd ( !_wcsnicmp( rax, enval, edi ) )

	    mov rax,[rsi-wstring_t]
	    lea rax,[rdi*2+rax]

	    .if ( word ptr [rax] == '=' )
		.return( &[rax+2] )
	    .endif
	.endif
ifdef _WIN64
	lodsq
else
	lodsd
endif
    .endw
endif
    ret

_wgetenv endp

    end
