include string.inc
include io.inc
include direct.inc
include crtl.inc
include winbase.inc
include dzlib.inc

	.data
exetype label byte
	db ".bat",0
	db ".com",0
	db ".exe",0
	db ".cmd",0
	db 0
	.code

	OPTION	PROC: PRIVATE

TestPath PROC USES esi edi ebx file:LPSTR
local	temp[_MAX_PATH*2]:SBYTE

	lea edi,temp
	mov esi,GetEnvironmentPATH()

	.if esi
		.repeat
			.if strchr( esi, ';' )
				sub eax,esi
			.else
				strlen( esi )
			.endif
			.break .if !eax
			mov ebx,eax
			memcpy( edi, esi, eax )
			mov WORD PTR [edi+ebx],'\'
			.if filexist( strcat( edi, file ) ) == 1
			    mov eax,edi
			    jmp toend
			.endif
			lea esi,[esi+ebx+1]
		.until	BYTE PTR [esi-1] == 0
	.endif
	xor eax,eax
toend:
	ret
TestPath ENDP

TestPathExt PROC USES esi edi file:LPSTR, path:LPSTR
local	temp[_MAX_PATH*2]:SBYTE

	lea edi,temp
	lea esi,exetype
	.while BYTE PTR [esi]
		.if filexist( strcat( strfcat( edi, path, file ), esi ) ) == 1
		    mov eax,edi
		    jmp toend
		.endif
		add esi,5
	.endw
	xor eax,eax
toend:
	ret
TestPathExt ENDP

	OPTION	PROC: PUBLIC

searchp PROC USES esi edi ebx fname:LPSTR

local	path[_MAX_PATH]:BYTE
local	file[_MAX_PATH]:BYTE
local	Testext:DWORD

	xor	eax,eax
	mov	ebx,fname
	test	ebx,ebx
	jz	toend
	cmp	al,[ebx]
	je	toend
	;
	; Test valid extension
	;
	mov Testext,1
	.if __isexec( ebx )
		dec Testext
	.endif
	lea esi,path
	lea edi,file
	_getcwd( esi, _MAX_PATH )
	;
	; If valid extension and exist
	;
	.if !Testext && filexist( ebx ) == 1
		.if  strfn( ebx ) == ebx
			strfcat( edi, esi, ebx )
		.else
			mov ecx,[ebx]
			xor eax,eax
			.if ch != ':'
				.if GetFullPathName( ebx, _MAX_PATH*2, edi, 0 )
					mov eax,edi
				.endif
			.endif
			.if !eax
				strcpy( edi, ebx )
			.endif
		.endif
		jmp toend
	.endif
	;
	; If full or relative path
	;
	.if strfn(ebx) != ebx

		.if !Testext
			;
			; do not exist
			;
			xor eax,eax
			jmp toend
		.endif

		strcpy( edi, eax )
		strpath( strcpy( esi, ebx ) )
		TestPathExt( edi, esi )
		jmp toend
	.endif
	;
	; Case filename
	;
	.if !Testext
		TestPath( ebx )
		jmp toend
	.endif
	;
	; case name, no ext
	;
	.if TestPathExt( ebx, esi )
		jmp toend
	.endif
	mov esi,GetEnvironmentPATH()
	.repeat
		.if strchr( esi, ';' )
		    sub eax,esi
		.else
		    strlen( esi )
		.endif
		.break .if !eax
		mov ecx,eax
		rep movsb
		mov BYTE PTR [edi],0
		lea edi,file
		.break .if TestPathExt( ebx, edi )
		lodsb
	.until	!eax
toend:
	ret
searchp ENDP

	END
