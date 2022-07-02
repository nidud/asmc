; GETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

getenv proc uses rsi rdi enval:string_t

    .ifd ( strlen( enval ) == 0 )
	.return
    .endif

    mov edi,eax
    mov rsi,_environ
ifdef _WIN64
    lodsq
else
    lodsd
endif

    .while( rax )

	.ifd ( _strnicmp( rax, enval, edi ) == 0 )

	    mov rax,[rsi-string_t]
	    add rax,rdi

	    .if ( byte ptr [rax] == '=' )
		.return( &[rax+1] )
	    .endif
	.endif
ifdef _WIN64
	lodsq
else
	lodsd
endif
    .endw
    ret

getenv endp

    end
