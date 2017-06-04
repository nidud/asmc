include consx.inc

rsunzipch PROTO
rsunzipat PROTO

	.code

wcunzip PROC USES esi edi  dest:PVOID, src:PVOID, wcount
	mov edi,dest
	inc edi
	mov esi,src
	mov eax,wcount
	and wcount,07FFh
	and eax,8000h
	mov ecx,wcount
	.if !ZERO?
		rsunzipat()
	.else
		rsunzipch()
	.endif
	mov edi,dest
	mov ecx,wcount
	rsunzipch()
	ret
wcunzip ENDP

	END
