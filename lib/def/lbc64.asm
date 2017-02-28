include string.inc
include stdio.inc
include stdlib.inc

	.data
	__argc	 dd 0
	__argv	 SIZE_T 0
	_environ SIZE_T 0

	.code

strfn proc uses edi path:ptr sbyte

	mov edi,path
	lea eax,[edi+strlen(edi)-1]
	.repeat
		.break .if byte ptr [eax] == '\'
		.break .if byte ptr [eax] == '/'
		dec eax
	.until	eax < edi
	inc	eax
	ret

strfn endp

strext proc uses edi string:ptr sbyte

	mov edi,strfn(string)
	.if strrchr(edi, '.')
		.if eax == ecx
			xor eax,eax
		.endif
	.endif
	ret

strext	endp

setfext proc path:ptr sbyte, ext:ptr sbyte

	.if strext(path)

		mov byte ptr [eax],0
	.endif
	strcat(path, ext)
	ret

setfext ENDP

strtrim PROC string:ptr sbyte

	.if strlen(string)

		mov ecx,eax
		add ecx,string
		.repeat
			dec ecx
			.break .if byte ptr [ecx] > ' '

			mov byte ptr [ecx],0
			dec eax
		.untilz
	.endif
	ret

strtrim ENDP

main	proc

  local lbuf[256]:byte, module[256]:byte, args[64]:byte, argc, argv, environ

	__getmainargs( addr argc, addr argv, addr environ, 0, 0 )

	.repeat
		.if argc != 2

			perror("Usage: lbc <file>.def")
			.break
		.endif
		mov	esi,argv
		mov	esi,[esi+4]
		lea	edi,module

		.break .if !strrchr(strcpy(edi, strfn(esi)),'.')

		mov byte ptr [eax],0
		_strupr(edi)

		.if !fopen(esi,"rt")

			perror(esi)
			.break
		.endif

		mov ebx,eax
		strcpy(addr lbuf, ".\\")

		push strcat(addr lbuf, strfn(esi))
		setfext(eax, ".lbc")
		pop eax
		.if !fopen(eax, "wt+")

			fclose(ebx)
			perror("Target")
			.break
		.endif
		mov edi,eax
		.while fgets(addr lbuf, 256, ebx)

			.if strrchr(addr lbuf, '@')
				mov byte ptr [eax],0
			.endif
			.if strtrim(addr lbuf)
				fprintf(edi,"++%s.\'%s.dll\'\n", addr lbuf, addr module )
			.endif
		.endw
		fclose(edi)
		fclose(ebx)
	.until	1

	exit(0)

main	endp

	end	main
