
dlldef.exe:
# asmc -q -D_WIN64 -win64 $*.asm
# linkw op map libpath \asmc\lib\x64 lib libc symt cstart file $*
  asmc -pe -D__PE__ -D_WIN64 $*.asm
  $@ kernel32.dll