; GETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

getenv proc uses rbx enval:string_t

   .new len:int_t

    ldr rcx,enval
    .ifd ( strlen( rcx ) == 0 )
	.return
    .endif

    mov len,eax
    mov rbx,_environ
    mov rax,[rbx]
    add rbx,string_t

    .while( rax )

	.ifd ( _strnicmp( rax, enval, len ) == 0 )

	    mov eax,len
	    add rax,[rbx-string_t]

	    .if ( byte ptr [rax] == '=' )
		.return( &[rax+1] )
	    .endif
	.endif
	mov rax,[rbx]
	add rbx,string_t
    .endw
    ret

getenv endp

    end
