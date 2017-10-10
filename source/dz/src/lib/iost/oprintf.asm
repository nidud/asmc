include io.inc
include stdio.inc
include iost.inc

    .code

oprintf proc c format:LPSTR, argptr:VARARG

    mov ecx,ftobufin(format, &argptr)
    .while 1
	movzx eax,byte ptr [edx]
	add edx,1
	.break .if !eax

	.if eax == 10

	    mov eax,STDO.ios_file
	    .if _osfile[eax] & FH_TEXT

		mov eax,13
		.break .if !oputc()

		inc ecx
	    .endif
	    mov eax,10
	.endif
	.break .if !oputc()
    .endw
    mov eax,ecx
    ret

oprintf endp

    END
