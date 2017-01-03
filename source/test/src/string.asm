include string.inc
include direct.inc

	.data
buf	db 4096 dup(?)
cp_A	db 'A'
cp_X	db 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx'
cp_B	db 'B'
cp_9	db 9
	db 0
	.code

main	proc c

	lea	edi,buf
	.assert strlen	("1") == 1
	.assert strcpy	(edi,"abc") == edi
	.assert strlen	(edi) == 3
	.assert strcmp	(edi,"abc") == 0
	.assert strcmp	(edi,"abc ") == -1
	.assert _stricmp(edi,"aBc") == 0
	.assert _stricmp(edi,"abc ") == -1
	.assert strcmp	(edi,"abcd") == -1
	.assert strcmp	(edi,"ab") == 1
	.assert memcmp	(edi,edi,3) == 0
	.assert memcmp	(edi,"abd",3) == 1
	.assert memcmp	(edi,"abcd",3) == 0
	.assert strncmp (edi,"abc",3) == 0
	.assert _strnicmp(edi,"AbC",3) == 0
	.assert strncmp (edi,"abc ",4) == -1
	.assert _strnicmp(edi,"abc ",4) == -1
	.assert strcat	(edi,"\\abc") == edi

	lea	esi,[edi+20]
	.assert strcpy(edi,"01234567890123456789strstr") == edi
	.assert strstr(edi,"strstr") == esi
	lea	esi,[edi+9]
	.assert strchr(edi,'9') == esi

	lea	esi,[edi+511]
	.assert memset(edi,'!',512) == edi
	.assert memcmp(esi,"!",1) == 0
	.assert memset(edi,0,512) == edi
	.assert memcmp(esi,edi,1) == 0
	.assert strcpy(edi,"String") == edi
	.assert _strrev(edi) == edi
	.assert strstr(edi,"String") == 0
	.assert _strrev(edi) == edi
	.assert strstr(edi,"String") == edi

	lea	ebx,cp_B
	lea	esi,cp_X
	.assert memchr(esi, 'A', sizeof(cp_X)) == 0
	.assert memchr(esi, 'B', sizeof(cp_X)) == 0
	.assert memchr(esi, 'B', sizeof(cp_X) + 1) == ebx
	.assert memchr(" ", 0, 1) == 0

	ret

main	endp

	end
