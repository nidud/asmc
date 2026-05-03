
Win64 = 64

WscApiSample.exe:
    asmc$(Win64) -ws -pe $*.asm
    $@ -av
    $@ -fw
    $@ -as
    pause
    del $@
