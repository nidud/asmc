IPicture.exe:
    asmc64 -peg $*.asm
    if exist $@ (
      $@
      dir *.ico | find "result"
      pause
    )
