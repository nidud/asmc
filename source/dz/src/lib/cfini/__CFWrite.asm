include io.inc
include cfini.inc
include iost.inc
include dzlib.inc

    .code

    assume esi:ptr S_CFINI
    assume edi:ptr S_CFINI

__CFWrite proc uses esi edi ebx __ini:PCFINI, __file:LPSTR

    .if osopen(__file, _A_NORMAL, M_WRONLY, A_CREATETRUNC) != -1

    mov STDO.ios_file,eax
    or	_osfile[eax],FH_TEXT

    .if ioinit(addr STDO, OO_MEM64K)

	mov esi,__ini
	.while	esi

	.if [esi].cf_flag == _CFSECTION

	    oprintf("\n[%s]\n", [esi].cf_name)
	.endif

	mov edi,[esi].cf_info
	.while	edi

	    .if [edi].cf_flag == _CFENTRY

	    oprintf("%s=%s\n", [edi].cf_name,
		[edi].cf_info)
	    .elseif [edi].cf_flag == _CFCOMMENT

	    oprintf("%s\n", [edi].cf_name)
	    .else
	    oprintf( ";%s\n", [edi].cf_name )
	    .endif

	    mov edi,[edi].cf_next
	.endw

	mov esi,[esi].cf_next
	.endw

	ioflush(addr STDO)
	ioclose(addr STDO)
	mov eax,1
    .else

	_close(STDO.ios_file)
	xor eax,eax
    .endif
    .else

    xor eax,eax
    .endif
    ret

__CFWrite endp

    END
