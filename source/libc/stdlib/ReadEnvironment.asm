;
; BOOL ReadEnvironment(const char *__FileName);
;
; Set [environment] + [current directory] from a file.
;
include io.inc
include direct.inc
include stdlib.inc
include string.inc
include alloc.inc

	.code

ReadEnvironment PROC USES esi edi ebx FileName:LPSTR

	local	CurrentEnvironment:PTR SBYTE,
		CurrentEnvSize:SDWORD,
		NewEnvironment:PTR SBYTE,
		NewEnvSize:SDWORD,
		Result:SDWORD

	mov	Result,0

	.if	GetEnvironmentStrings()
		;
		; Read the current environment block
		;
		mov	edi,eax
		mov	esi,GetEnvironmentSize( eax )
		mov	CurrentEnvSize,esi
		mov	CurrentEnvironment,memcpy( alloca( esi ), edi, esi )
		FreeEnvironmentStrings( edi )
		;
		; Read the new environment block
		;
		.if	osopen( FileName, _A_NORMAL, M_RDONLY, A_OPEN ) != -1

			mov	edi,eax
			mov	ebx,_filelength( eax )
			mov	esi,alloca( eax )
			mov	BYTE PTR [esi],0
			osread( edi, eax, ebx )
			xchg	eax,edi
			_close( eax )
			mov	NewEnvironment,esi

			test	ebx,ebx		; Exit on zero file or IO error
			jz	toend
			cmp	edi,ebx
			jne	toend
			;
			; Get size of new block
			;
			GetEnvironmentSize( esi )
			mov	edi,esi
			mov	esi,eax
			mov	NewEnvSize,esi
			.if	esi == CurrentEnvSize
				mov	ecx,esi
				mov	esi,CurrentEnvironment
				repz	cmpsb
				mov	esi,edi
				jz	directory	; Skip if equal
			.endif
			;
			; The new block differ from the current
			; - delete the current block
			;
			mov	esi,CurrentEnvironment
			.while	BYTE PTR [esi]
				lea	eax,[esi+1]
				.if	strchr( eax, '=' )
					mov	BYTE PTR [eax],0
					mov	ebx,eax
					SetEnvironmentVariable( esi, 0 )
					mov	BYTE PTR [ebx],'='
				.endif
				strlen( esi )
				lea	esi,[esi+eax+1]
			.endw
			;
			; - set the new block
			;
			mov	esi,NewEnvironment
			.while	BYTE PTR [esi]
				lea	eax,[esi+1]
				.if	strchr( eax, '=' )
					mov	BYTE PTR [eax],0
					lea	ebx,[eax+1]
					SetEnvironmentVariable( esi, ebx )
					mov	BYTE PTR [ebx-1],'='
				.endif
				strlen( esi )
				lea	esi,[esi+eax+1]
			.endw
			inc	esi
directory:
			SetCurrentDirectory( esi )
			inc	Result
		.endif
	.endif
toend:
	mov	eax,Result
	ret
ReadEnvironment ENDP

	END
