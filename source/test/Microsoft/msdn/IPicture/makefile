IPicture.exe:
    asmc64 -pe -gui $*.asm
    if exist $@ (
      $@
      dir *.ico | find "result"
      pause
    )
