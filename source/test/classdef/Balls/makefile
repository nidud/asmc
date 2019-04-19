all: test.exe clean

test.exe:
    asmc64 -nologo -Cs test.asm graphics.asm balls.asm
    linkw system gui_64 file test, graphics, balls
    $@

clean:
    pause
    @del *.obj
    @if exist test.exe del test.exe
