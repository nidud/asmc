include io.inc
include direct.inc
include string.inc
include alloc.inc

;
; File macros:
;
;    !!	    !
;    !:	    Drive + ':'
;    !\	    Long path
;    !	    Long file name
;    .!	    Long extension
;    .!~    Short extension
;    !~\    Short path
;    ~!	    Short file name
;

	.code

expcommand PROC USES esi edi ebx string, file

  local longpath, longfile, shortpath, shortfile, S2, S1, drive

	strchr( string, '!' )
	jz	nomacros
	mov	longpath,alloca( WMAXPATH*2 )
	mov	edi,eax
	mov	ecx,WMAXPATH*2
	add	eax,WMAXPATH
	mov	shortpath,eax
	xor	eax,eax
	rep	stosb
	GetFullPathName( file, WMAXPATH, strcpy( longpath, file ), 0 )
	xor	eax,eax
	mov	drive,eax
	mov	edi,longpath
	mov	ebx,[edi]
	cmp	bl,'\'
	je	@F
	cmp	bh,':'
	je	@F
	GetCurrentDirectory( WMAXPATH, shortpath )
	test	eax,eax
	jz	toend
	strfcat( longpath, shortpath, file )
@@:
	GetShortPathName( edi, strcpy( shortpath, edi ), WMAXPATH )
	cmp	bh,':'
	jne	@F
	mov	WORD PTR drive,bx
	strcpy( edi, addr [edi+3] )
	mov	ecx,shortpath
	strcpy( ecx, addr [ecx+3] )
@@:
	lea	esi,S1
	lea	edi,S2
	mov	ebx,string
	mov	DWORD PTR [esi],"!!"
	mov	DWORD PTR [edi],"››"
	strxchg( ebx, esi, edi )
	mov	BYTE PTR [esi+1],':'		; "!:" -- drive + ':'
	strxchg( ebx, esi, addr drive )
	xor	eax,eax
	mov	[edi],eax
	mov	DWORD PTR [esi],"~!."		; ".!~" -- Short extension
	strext( shortpath )
	mov	edx,edi
	jz	@F
	mov	edx,eax
@@:
	strxchg( ebx, esi, edx )
	cmp	edx,edi				; remove ext
	je	@F
	mov	BYTE PTR [edx],0
@@:
	mov	DWORD PTR [esi],"!."		; ".!" -- Long extension
	strext( longpath )
	mov	edx,edi
	jz	@F
	mov	edx,eax
@@:
	strxchg( ebx, esi, edx )
	cmp	edx,edi				; remove ext
	je	@F
	mov	BYTE PTR [edx],0
@@:
	strfn ( shortpath )
	mov	shortfile,eax
	cmp	eax,shortpath
	je	@F
	mov	byte ptr [eax-1],0
@@:
	jne	@F
	mov	shortpath,edi
@@:
	strfn ( longpath )
	mov	longfile,eax
	cmp	eax,longpath
	je	@F
	mov	byte ptr [eax-1],0
@@:
	jne	@F
	mov	longpath,edi
@@:
	mov	DWORD PTR [esi],"\!"		; "!\" -- Long path
	strxchg( ebx, esi, longpath )
	mov	DWORD PTR [esi],"\~!"		; "!~\" -- Short path
	strxchg( ebx, esi, shortpath )
	mov	DWORD PTR [esi],"!~"		; "!~" -- Short file
	strxchg( ebx, esi, shortfile )
	mov	DWORD PTR [esi],"!"		; "!" -- Long file
	strxchg( ebx, esi, longfile )
	mov	DWORD PTR [esi],"››"
	mov	DWORD PTR [edi],"!"
	strxchg( ebx, esi, edi )
toend:
	ret
nomacros:
	lea	ebx,S1
	mov	eax,'" '
	mov	[ebx],eax
	strchr( string, ' ' )
	mov	esi,eax
	jnz	@F
	mov	[ebx+1],al
@@:
	strcat( string, ebx )
	strcat( eax, file )
	test	esi,esi
	jz	toend
	inc	ebx
	strcat( eax, ebx )
	xor	ebx,ebx
	jmp	toend
expcommand ENDP

	END
