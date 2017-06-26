cl.lib:
    iddc -ml -r src\*.idd
    asmc -I..\include -r src\*.asm
    libw -q -b -n -c $@ *.obj
    del *.obj
    asmc -Fo c0l.obj -D__l__ crt.asm
    asmc -Fo w0l.obj -D__l__ -D__WCC__ crt.asm
    asmc -Fo c0fl.obj -DDEBUG -D__l__ -Zd crt.asm
