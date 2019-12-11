
target_path = ..\..\..\lib\amd64

import.exe: $(target_path)
    asmc -q -win64 -pe $*.asm
    $@ import.inc $(target_path)
    del $@

$(target_path):
    if not exist $(target_path) md $(target_path)
