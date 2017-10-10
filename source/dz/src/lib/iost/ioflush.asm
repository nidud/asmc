include iost.inc
include io.inc
include errno.inc
include consx.inc

    .code

    assume esi:ptr S_IOST

ioflush proc uses esi edx iost:ptr S_IOST

    mov esi,iost
    mov eax,[esi].ios_i

    .if eax

	.if [esi].ios_flag & IO_USECRC

	    xor edx,edx
	    oupdcrc()
	.endif

	.if oswrite([esi].ios_file, [esi].ios_bp, [esi].ios_i) == [esi].ios_i

	    add dword ptr [esi].ios_total,eax
	    adc dword ptr [esi].ios_total[4],0
	    xor eax,eax
	    mov [esi].ios_c,eax
	    mov [esi].ios_i,eax

	    .if [esi].ios_flag & IO_USEUPD

		inc eax
		push eax
		oupdate()
		dec eax
	    .endif
	.else
	    or [esi].ios_flag,IO_ERROR
	    or eax,-1
	.endif
    .endif

    inc eax
    ret

ioflush endp

    END
