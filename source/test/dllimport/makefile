test.exe:
    asmc64 -pe $*.asm
    asmc64 -nolib extern.asm
    linkw Format windows pe dll Library msvcrt File extern
    $@
    pause



