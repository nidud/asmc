msvc = \vc12
asmc = \asmc

cflags = /I$(msvc)\include
lflags = $(asmc)\lib\amd64\directxmath.lib /LIBPATH:$(msvc)\lib\amd64

test.exe:
    $(msvc)\bin\amd64\cl $(cflags) $*.c /link $(lflags)
    $@
    pause
