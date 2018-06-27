msvc = \vc12

cflags = /I$(msvc)\include
lflags = /LIBPATH:$(msvc)\lib\amd64

test.exe:
    $(msvc)\bin\amd64\cl $(cflags) $*.c /link $(lflags)
    $@
    pause
