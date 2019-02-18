test.exe:
    asmc64 -Cs $*.asm object.asm graph.asm
    linkw sys gui_64 file $*, object, graph
    $@

