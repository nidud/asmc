include strlib.inc
include stdio.inc
include conio.inc

    .data
    cp_A db 'A'
    cp_X db 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx'
    cp_B db 'B'
    cp_9 db 9,0

    .code

main proc

  local buffer[512]:byte

    lea rdi,buffer
    lea rsi,[rdi+4]

    .assert( strfn(strcpy(rdi, "xxx\\abc")) == rsi )
    add rsi,4
    .assert( strfn(strcat( rdi,"/abc" )) == rsi )

    lea rsi,[rdi+20]
    strcpy(rdi, "%doszip%, C:/doszip, strstr")

    .assert( strxchg(rdi, "C:/doszip", "%doszip%") == rdi )
    .assert( !strcmp(rdi, "%doszip%, %doszip%, strstr") )
    .assert( strstr(rdi, "strstr") == rsi )
    .assert( !strstr(rdi, "C:/doszip") )
    .assert( strxchg(rdi, "%doszip%", "C:/doszip") == rdi )
    .assert( !strcmp(rdi, "C:/doszip, C:/doszip, strstr") )
    .assert( !_strnicmp(rdi, "C:/doszip", 9) )

    .assert( strfcat(rdi, "C:\\Documents And Settings\\DOSZIP", "Long Filename.filetype") == rdi )
    .assert( !strcmp(strfn(rdi), "Long Filename.filetype") )

    strcpy(rdi, "xx\n\t ")
    .assertd( strtrim(rdi) == 2 )

    .assertd( cmpwarg("file",     "*"        ) == 1 )
    .assertd( cmpwarg("file",     "*.*"      ) == 1 )
    .assertd( cmpwarg("file",     "f*.*"     ) == 1 )
    .assertd( cmpwarg("file",     "file*"    ) == 1 )
    .assertd( cmpwarg("file.c",   "file.?"   ) == 1 )
    .assertd( cmpwarg("file.c",   "file.??"  ) == 0 )
    .assertd( cmpwarg("file.c",   "???.?"    ) == 0 )
    .assertd( cmpwarg("file.c",   "????.?"   ) == 1 )
    .assertd( cmpwarg("file.c",   "file.c*"  ) == 1 )
    .assertd( cmpwarg("file.c",   "file.c?"  ) == 0 )
    .assertd( cmpwarg("file.x.c", "*.c"      ) == 1 )
    .assertd( cmpwarg("file.x.c", "????.*.c" ) == 1 )
    .assertd( cmpwarg("file.x.c", "????.*.b" ) == 0 )
    .assertd( cmpwarg("file.x.c", "*.?.b"    ) == 0 )
    .assertd( cmpwarg("file.x.c", "*.*.b"    ) == 0 )
    .assertd( cmpwarg("file.x.c", "*.*.c"    ) == 0 )
    .assertd( cmpwarg("file.x.c", "*.?.c"    ) == 0 )
    .assertd( cmpwarg("file.x.c", "*?x.c"    ) == 1 )
    .assertd( cmpwarg("file.ext", "*"        ) == 1 )
    .assertd( cmpwarg("file.prj", "*.*"      ) == 1 )
    .assertd( cmpwarg("file.ext", "x*.*"     ) == 0 )
    .assertd( cmpwarg("ab39.ext", "?B39.??T" ) == 1 )
    .assertd( cmpwarg("abcd.ext", "?b?.?x?"  ) == 0 )
    .assertd( cmpwarg("abcd.ext", "?b*.?x?"  ) == 1 )
    .assertd( cmpwarg("abcd.ext", "?b*.?z?"  ) == 0 )

    lea r12,cp_B
    lea r13,cp_X

    .assert( !memchr(r13, 'A', sizeof(cp_X)) )
    .assert( !memchr(r13, 'B', sizeof(cp_X)) )
    .assert( memchr(r13, 'B', sizeof(cp_X) + 1) == r12 )
    .assert( !memchr(" ", 0, 1) )
    .assert( !memstri("xxxx", 4, "yy", 2) )
    .assert( !memstri(r13, 4, r13, 5) )
    .assert( memstri(r13, 4, r13, 2) == r13 )
    .assert( memstri(r13, sizeof(cp_X) + 1, "b", 1) == r12 )
    .assert( !memstri(" ", 1, addr cp_9+1, 1) )
    .assert( !memrchr("xxxx", 'X', 4) )
    .assert( !memrchr(r13, 'B', sizeof(cp_X)) )
    .assert( memrchr(r13, 'B', sizeof(cp_X) + 1) == r12 )
    .assert( !memrchr(r13, 'A', sizeof(cp_X) + 1) )

    lea rsi,[rdi+128]
    strcpy(rdi, "abcd")
    strcpy(rsi, "abcd")
    .assert( memxchg(rdi, rsi, 4) == rdi )
    .assert( !memcmp(rsi, rdi, 4) )
    .assert( !strchr(r13, 'A') )
    .assert( strchr(r13, 'B') == r12 )
    .assert( !strchr(" ", 0) )
    .assert( !strchri(r13, 'A') )
    .assert( strchri(r13, 'B') == r12 )
    .assert( strchri(r13, 'b') == r12 )
    .assert( !strchri(" ", 0) )

    xor eax,eax
    ret

main endp

    end
