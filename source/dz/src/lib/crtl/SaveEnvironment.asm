;
; BOOL SaveEnvironment(const char *__FileName);
;
; Saves [environment] + [current directory] to a file.
;
include io.inc
include direct.inc
include stdlib.inc
include string.inc
include winbase.inc
include dzlib.inc

    .code

SaveEnvironment proc uses esi edi ebx FileName:LPSTR
local CurrentDirectory[WMAXPATH]:sbyte
    xor ebx,ebx
    .if GetEnvironmentStrings()
	mov esi,eax
	push eax
	.if osopen(FileName, _A_NORMAL, M_WRONLY, A_CREATETRUNC) != -1
	    mov edi,eax
	    oswrite(edi, esi, GetEnvironmentSize(esi))
	    lea esi,CurrentDirectory
	    .if GetCurrentDirectory(WMAXPATH, esi)
		strlen(esi)
		inc eax
		oswrite(edi, esi, eax)
		inc ebx
	    .endif
	    _close(edi)
	    .if !ebx
		remove(FileName)
	    .endif
	.endif
	FreeEnvironmentStrings()
    .endif
    mov eax,ebx
    ret
SaveEnvironment endp

    END
