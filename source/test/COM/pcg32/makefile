all: test.exe clean

test.exe:
    asmc64 -nologo -Cs $*.asm object.asm graph.asm
    linkw sys gui_64 file $*, object, graph
    $@

clean:
    pause
    @del *.obj
    @if exist test.exe del test.exe

