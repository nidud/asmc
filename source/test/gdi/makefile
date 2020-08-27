#
# GDI samples from: http://zetcode.com/gui/winapi/gdi/
#

x64 = 0

.SUFFIXES: .exe

.asm.exe:
!if $(x64)
    asmc64 -pe -gui -ws $<
!else
    asmc -pe -gui -ws $<
!endif

targets = \
    beziercurve.exe \
    linejoins.exe   \
    lines.exe       \
    penstyles.exe   \
    pixels.exe      \
    rectangle.exe   \
    solidbrush.exe

build: $(targets)


