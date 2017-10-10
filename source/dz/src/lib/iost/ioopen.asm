include iost.inc
include io.inc
include errno.inc
include consx.inc

extrn CP_ENOMEM:byte

    .code

ioopen proc uses esi iost:ptr S_IOST, file:LPSTR, mode, bsize

    .if mode == M_RDONLY

	openfile(file, mode, A_OPEN)
    .else
	ogetouth(file, mode)
    .endif

    .ifs eax > 0	 ; -1, 0 (error, cancel), or handle

	mov esi,iost
	mov [esi].S_IOST.ios_file,eax
	.if !ioinit(esi, bsize)

	    _close([esi].S_IOST.ios_file)
	    ermsg(0, addr CP_ENOMEM)
	    xor eax,eax
	.else
	    mov eax,[esi].S_IOST.ios_file
	.endif
    .endif
    ret

ioopen endp

    END
