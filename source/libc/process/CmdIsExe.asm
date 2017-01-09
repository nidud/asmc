include direct.inc
include string.inc
include stdlib.inc
include crtl.inc

	.code

CmdIsExe PROC USES esi edi ebx cmd:LPSTR
local	path[_MAX_PATH]:BYTE

	mov	ebx,' '
	lea	edi,path
	mov	esi,cmd

	.while	BYTE PTR [esi] == ' '
		add esi,1
	.endw
	.while	BYTE PTR [esi] == '"'
		add esi,1
		mov bl,'"'
	.endw
	xor	eax,eax
	mov	[edi],eax
	lodsb
	.while	al
		.break .if al == bl
		stosb
		lodsb
	.endw

	mov [edi],ah
	lea edi,path

	.if searchp(edi)
		mov edx,eax
		.if __isexec(eax) == _EXEC_EXE
			jmp IsExe
		.endif
	.endif
NotExe:
	xor	eax,eax
toend:
	ret
IsExe:
	sub	eax,_EXEC_EXE - 1
	jmp	toend
CmdIsExe ENDP

	END
