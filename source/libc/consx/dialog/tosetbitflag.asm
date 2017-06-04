include consx.inc

	.code

tosetbitflag PROC USES esi ebx tobj:PTR S_TOBJ, count, flag, bitflag

	mov ebx,tobj
	mov edx,bitflag
	mov esi,flag
	mov ecx,count
	mov eax,esi
	not eax

	.while	ecx
		;
		; Remove the flag from Object
		;
		and [ebx].S_TOBJ.to_flag,ax
		;
		; Max 32 object flags
		;
		shr edx,1
		.if CARRY?

			or [ebx].S_TOBJ.to_flag,si
		.endif

		add ebx,SIZE S_TOBJ
		dec ecx
	.endw
	ret

tosetbitflag ENDP

	END
