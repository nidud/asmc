include strlib.inc
include stdio.inc
include conio.inc

    .code

main proc

    .assert( cmpwarg("file",     "*"        ) == 1 )
    .assert( cmpwarg("file",     "*.*"      ) == 1 )
    .assert( cmpwarg("file",     "f*.*"     ) == 1 )
    .assert( cmpwarg("file",     "file*"    ) == 1 )
    .assert( cmpwarg("file.c",   "file.?"   ) == 1 )
    .assert( cmpwarg("file.c",   "file.??"  ) == 0 )
    .assert( cmpwarg("file.c",   "???.?"    ) == 0 )
    .assert( cmpwarg("file.c",   "????.?"   ) == 1 )
    .assert( cmpwarg("file.c",   "file.c*"  ) == 1 )
    .assert( cmpwarg("file.c",   "file.c?"  ) == 0 )
    .assert( cmpwarg("file.x.c", "*.c"      ) == 1 )
    .assert( cmpwarg("file.x.c", "????.*.c" ) == 1 )
    .assert( cmpwarg("file.x.c", "????.*.b" ) == 0 )
    .assert( cmpwarg("file.x.c", "*.?.b"    ) == 0 )
    .assert( cmpwarg("file.x.c", "*.*.b"    ) == 0 )
    .assert( cmpwarg("file.x.c", "*.*.c"    ) == 0 )
    .assert( cmpwarg("file.x.c", "*.?.c"    ) == 0 )
    .assert( cmpwarg("file.x.c", "*?x.c"    ) == 1 )
    .assert( cmpwarg("file.ext", "*"        ) == 1 )
    .assert( cmpwarg("file.prj", "*.*"      ) == 1 )
    .assert( cmpwarg("file.ext", "x*.*"     ) == 0 )
    .assert( cmpwarg("ab39.ext", "?B39.??T" ) == 1 )
    .assert( cmpwarg("abcd.ext", "?b?.?x?"  ) == 0 )
    .assert( cmpwarg("abcd.ext", "?b*.?x?"  ) == 1 )
    .assert( cmpwarg("abcd.ext", "?b*.?z?"  ) == 0 )

    xor eax,eax
    ret

main endp

    end
