include stdio.inc
include string.inc
include direct.inc
include conio.inc

stricmp equ <_stricmp>
strnicmp equ <_strnicmp>

	.data
cp_A	db 'A'
cp_X	db 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx'
cp_B	db 'B'
cp_9	db 9
	db 0
	.code

main	proc

local	buf[4096]:byte
	lea	rdi,buf

	.assert strlen("1") == 1
	.assert strcpy(rdi,"abc") == rdi
	.assert strlen(rdi) == 3
	.assert strcmp(rdi,"abc") == 0
	.assert strcmp(rdi,"abc ") == -1
	.assert stricmp(rdi,"aBc") == 0
	.assert stricmp(rdi,"abc ") == -1
	.assert strcmp(rdi,"abcd") == -1
	.assert strcmp(rdi,"ab") == 1
	.assert memcmp(rdi,rdi,3) == 0
	.assert memcmp(rdi,"abd",3) == 1
	.assert memcmp(rdi,"abcd",3) == 0
	.assert strncmp(rdi,"abc",3) == 0
	.assert strnicmp(rdi,"AbC",3) == 0
	.assert strncmp(rdi,"abc ",4) == -1
	.assert strnicmp(rdi,"abc ",4) == -1
	.assert strcat(rdi,"\\abc") == rdi
	lea	rsi,[rdi+4]
	.assert strfn(rdi) == rsi
	strcat( rdi,"/abc" )
	add	rsi,4
	.assert strfn(rdi) == rsi
	lea	rsi,[rdi+20]
	.assert strcpy(rdi,"%doszip%, C:/doszip, strstr") == rdi
if 0
	.assert strxchg(rdi,"C:/doszip","%doszip%") == rdi
	.assert strcmp(rdi,"%doszip%, %doszip%, strstr") == 0
	.assert strstr(rdi,"strstr") == rsi
	.assert strstr(rdi,"C:/doszip") == 0
	.assert strxchg(rdi,"%doszip%","C:/doszip") == rdi
	.assert strcmp(rdi,"C:/doszip, C:/doszip, strstr") == 0
	.assert strnicmp(rdi,"C:/doszip",9) == 0
	.assert strncmp(rdi,"%doszip%",8) == 1
	.assert strnicmp(rdi,rdi,20) == 0
	.assert strrchr(rdi,',') == rsi
	lea	rsi,[rdi+9]
	.assert strchr(rdi,',') == rsi
	lea	rsi,[rdi+511]
	.assert memset(rdi,'!',512) == rdi
	.assert memcmp(rsi,"!",1) == 0
	.assert memzero(rdi,512) == rdi
	.assert memcmp(rsi,rdi,1) == 0
	.assert strcpy(rdi,"String") == rdi
	.assert _strrev(rdi) == rdi
	.assert strstr(rdi,"String") == 0
	.assert _strrev(rdi) == rdi
	.assert strstr(rdi,"String") == rdi
	.assert strshr(rdi,' ') == rdi
	.assert strfcat(rdi,"C:\\Documents And Settings\\DOSZIP","Long Filename.filetype") == rdi
	.assert strfn(rdi)
	.assert strcmp(rax,"Long Filename.filetype") == 0
	.assert strcpy( rdi,"HEXTOA and ATOHEX" )
	.assert atohex(rdi) == rdi
	.assert hextoa(rdi) == rdi
	.assert strcmp(rdi,"HEXTOA and ATOHEX") == 0
	.assert recursive("N","X:\\A\\B","X:\\A\\B") == 0
	.assert recursive("N","X:\\A\\N","X:\\A") == 0
	.assert recursive("A","X:","X:\\A\\B") == 1
	.assert recursive("N","X:\\A","X:\\A\\N") == 1
	.assert recursive("N","K:\\lib\\src\\test\\doszip\\335\\dll", "K:\\rel\\14\\334\\dll") == 0
	.assert recursive("N","K:\\rel\\14\\334\\dll", "K:\\lib\\src\\test\\doszip\\335\\dll") == 0

	.assert cmpwarg("file","*") == 1
	.assert cmpwarg("file","*.*") == 1
	.assert cmpwarg("file","f*.*") == 1
	.assert cmpwarg("file","file*") == 1
	.assert cmpwarg("file.c","file.?") == 1
	.assert cmpwarg("file.c","file.??") == 0
	.assert cmpwarg("file.c","???.?") == 0
	.assert cmpwarg("file.c","????.?") == 1
	.assert cmpwarg("file.c","file.c*") == 1
	.assert cmpwarg("file.c","file.c?") == 0
	.assert cmpwarg("file.x.c","*.c") == 1
	.assert cmpwarg("file.x.c","????.*.c") == 1
	.assert cmpwarg("file.x.c","????.*.b") == 0
	.assert cmpwarg("file.x.c","*.?.b") == 0
	.assert cmpwarg("file.x.c","*.*.b") == 0
	.assert cmpwarg("file.x.c","*.*.c") == 0
	.assert cmpwarg("file.x.c","*.?.c") == 0
	.assert cmpwarg("file.x.c","*?x.c") == 1
	.assert cmpwarg("file.ext","*") == 1
	.assert cmpwarg("file.prj","*.*") == 1
	.assert cmpwarg("file.ext","x*.*") == 0
	.assert cmpwarg("ab39.ext","?B39.??T") == 1
	.assert cmpwarg("abcd.ext","?b?.?x?") == 0
	.assert cmpwarg("abcd.ext","?b*.?x?") == 1
	.assert cmpwarg("abcd.ext","?b*.?z?") == 0

	lea	r12,cp_B
	lea	r13,cp_X
	.assert memchr(r13, 'A', sizeof(cp_X)) == 0
	.assert memchr(r13, 'B', sizeof(cp_X)) == 0
	.assert memchr(r13, 'B', sizeof(cp_X) + 1) == r12
	.assert memchr(" ", 0, 1) == 0
	.assert memstri("xxxx", 4, "yy", 2) == 0
	.assert memstri(r13, 4, r13, 5) == 0
	.assert memstri(r13, 4, r13, 2) == r13
	.assert memstri(r13, sizeof(cp_X) + 1, "b", 1) == r12
	.assert memstri(" ", 1, addr cp_9+1, 1) == 0
	.assert memrchr("xxxx", 'X', 4) == 0
	.assert memrchr(r13, 'B', sizeof(cp_X)) == 0
	.assert memrchr(r13, 'B', sizeof(cp_X) + 1) == r12
	.assert memrchr(r13, 'A', sizeof(cp_X) + 1) == 0

	lea	rsi,[rdi+128]
	.assert strcpy(rdi,"abcd") == rdi
	.assert strcpy(rsi,"abcd") == rsi
	.assert memxchg(rdi,rsi,4) == rdi
	.assert memcmp(rsi,rdi,4) == 0
	.assert strchr(r13, 'A') == 0
	.assert strchr(r13, 'B') == r12
	.assert strchr(" ", 0) == 0
	.assert strchri(r13, 'A') == 0
	.assert strchri(r13, 'B') == r12
	.assert strchri(r13, 'b') == r12
	.assert strchri(" ", 0) == 0
endif
	xor	rax,rax
	ret
main	endp

	end
