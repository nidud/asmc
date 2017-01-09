include string.inc
include direct.inc
include ini.inc
include stdlib.inc
include process.inc

expcommand proto :LPSTR, :LPSTR

	.code

inicommand PROC buffer:LPSTR, filename:LPSTR, section:LPSTR
  local tmp[_MAX_PATH]:byte
	lea	edx,tmp
	strrchr( strcpy( edx, strfn( filename ) ), '.' )
	jz	@F
	xchg	eax,edx
	inc	edx
	cmp	BYTE PTR [edx],0
	jne	@F
	mov	BYTE PTR [edx-1],0
	mov	edx,eax
@@:
	inientry( section, edx )
	jz	toend
	expcommand( expenviron( strcpy( buffer, eax ) ), filename )
	strxchg( eax, ", ", "\r\n" )
toend:
	test	eax,eax
	ret
inicommand ENDP

	END
