
FlowTextMain.exe:
    asmc64 -c -q -ws -Cs FlowTextMain.asm
    asmc64 -c -q -ws -Cs LayoutToCanvasBuilder.asm
    linkw system con_64W file FlowTextMain, LayoutToCanvasBuilder
    $@
    del *.obj
